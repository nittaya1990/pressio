// Copyright(c) 2015-present, Gabi Melman & spdlog contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef UTILS_LOGGER_SPDLOG_PATTERN_FORMATTER_HPP_
#define UTILS_LOGGER_SPDLOG_PATTERN_FORMATTER_HPP_

#include "./common.hpp"
#include "./details/log_msg.hpp"
#include "./details/os.hpp"
#include "./formatter.hpp"

#include "./details/fmt_helper.hpp"
#include "./details/log_msg.hpp"
#include "./details/os.hpp"
#include "./fmt/fmt.hpp"
#include "./formatter.hpp"

#include <chrono>
#include <ctime>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

namespace spdlog {
namespace details {

// padding information.
struct padding_info
{
    enum class pad_side
    {
        left,
        right,
        center
    };

    padding_info() = default;
    padding_info(size_t width, padding_info::pad_side side, bool truncate)
        : width_(width)
        , side_(side)
        , truncate_(truncate)
        , enabled_(true)
    {}

    bool enabled() const
    {
        return enabled_;
    }
    size_t width_ = 0;
    pad_side side_ = pad_side::left;
    bool truncate_ = false;
    bool enabled_ = false;
};

class flag_formatter
{
public:
    explicit flag_formatter(padding_info padinfo)
        : padinfo_(padinfo)
    {}
    flag_formatter() = default;
    virtual ~flag_formatter() = default;
    virtual void format(const details::log_msg &msg, const std::tm &tm_time, memory_buf_t &dest) = 0;

protected:
    padding_info padinfo_;
};

} // namespace details

class custom_flag_formatter : public details::flag_formatter
{
public:
    virtual std::unique_ptr<custom_flag_formatter> clone() const = 0;

    void set_padding_info(details::padding_info padding)
    {
        flag_formatter::padinfo_ = padding;
    }
};

namespace details{
class full_formatter;
}

class pattern_formatter final : public formatter
{
public:
  using custom_flags = std::unordered_map<char, std::unique_ptr<custom_flag_formatter>>;

  explicit pattern_formatter(std::string pattern,
			     pattern_time_type time_type = pattern_time_type::local,
			     std::string eol = spdlog::details::os::default_eol,
			     custom_flags custom_user_flags = custom_flags())
    : pattern_(std::move(pattern))
    , eol_(std::move(eol))
    , pattern_time_type_(time_type)
    , last_log_secs_(0)
    , custom_handlers_(std::move(custom_user_flags))
  {
    std::memset(&cached_tm_, 0, sizeof(cached_tm_));
    compile_pattern_(pattern_);
  }

  // use default pattern is not given
  explicit pattern_formatter(pattern_time_type time_type = pattern_time_type::local,
			     std::string eol = spdlog::details::os::default_eol);
  //   : pattern_("%+")
  //   , eol_(std::move(eol))
  //   , pattern_time_type_(time_type)
  //   , last_log_secs_(0)
  // {
  //   std::memset(&cached_tm_, 0, sizeof(cached_tm_));
  //   formatters_.push_back(details::make_unique<details::full_formatter>(details::padding_info{}));
  // }

  pattern_formatter(const pattern_formatter &other) = delete;
  pattern_formatter &operator=(const pattern_formatter &other) = delete;

public:
  std::unique_ptr<formatter> clone() const override
  {
    custom_flags cloned_custom_formatters;
    for (auto &it : custom_handlers_)
      {
        cloned_custom_formatters[it.first] = it.second->clone();
      }
    return details::make_unique<pattern_formatter>(pattern_, pattern_time_type_, eol_, std::move(cloned_custom_formatters));
  }

  void format(const details::log_msg &msg, memory_buf_t &dest) override
  {
    auto secs = std::chrono::duration_cast<std::chrono::seconds>(msg.time.time_since_epoch());
    if (secs != last_log_secs_)
      {
        cached_tm_ = get_time_(msg);
        last_log_secs_ = secs;
      }

    for (auto &f : formatters_)
      {
        f->format(msg, cached_tm_, dest);
      }
    details::fmt_helper::append_string_view(eol_, dest);
  }

  template<typename T, typename... Args>
  pattern_formatter &add_flag(char flag, Args&&...args)
  {
    custom_handlers_[flag] = details::make_unique<T>(std::forward<Args>(args)...);
    return *this;
  }

  void set_pattern(std::string pattern)
  {
    pattern_ = std::move(pattern);
    compile_pattern_(pattern_);
  }


private:
  std::string pattern_;
  std::string eol_;
  pattern_time_type pattern_time_type_;
  std::tm cached_tm_;
  std::chrono::seconds last_log_secs_;
  std::vector<std::unique_ptr<details::flag_formatter>> formatters_;
  custom_flags custom_handlers_;

  std::tm get_time_(const details::log_msg &msg);
  template<typename Padder>
  void handle_flag_(char flag, details::padding_info padding);

  // Extract given pad spec (e.g. %8X)
  // Advance the given it pass the end of the padding spec found (if any)
  // Return padding.
  static details::padding_info handle_padspec_(std::string::const_iterator &it, std::string::const_iterator end);

  void compile_pattern_(const std::string &pattern);
};
} // namespace spdlog

#ifdef SPDLOG_HEADER_ONLY
#include "pattern_formatter-inl.hpp"
#endif
#endif  // UTILS_LOGGER_SPDLOG_PATTERN_FORMATTER_HPP_
