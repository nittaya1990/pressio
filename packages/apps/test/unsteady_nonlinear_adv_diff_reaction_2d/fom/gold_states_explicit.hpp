
#ifndef ROMPP_APPS_TEST_UNSTEADY_NONLIN_ADVDIFFREACTION2D_GOLD_EXPLICIT_HPP_
#define ROMPP_APPS_TEST_UNSTEADY_NONLIN_ADVDIFFREACTION2D_GOLD_EXPLICIT_HPP_

#include "ODE_ALL"

namespace rompp { namespace apps{ namespace test{

template <ode::ExplicitEnum>
struct NonLinAdvDiffReac2dExpGoldStates;

template <>
struct NonLinAdvDiffReac2dExpGoldStates<ode::ExplicitEnum::RungeKutta4>{
  using result_t = std::vector<double>;

  static result_t get(int Nx, int Ny,
		      double dt, double final_t){
    if(Nx==11 and Ny==21 and dt==0.001 and final_t==0.5){
      return{
		 -2.9333036485241e-16,
		  1.1832756653666e-10,
		 -1.6499980316952e-19,
		 -4.0840675252699e-15,
		  1.3359536871179e-09,
		 -2.6636155287304e-18,
		 -3.3887325520975e-14,
		  8.8585365462861e-09,
		 -2.5850492116827e-17,
		 -1.9923272641827e-13,
		  4.0935601467271e-08,
		 -1.7969877730689e-16,
		 -9.1050907110564e-13,
		   1.439926114583e-07,
		 -9.8276309205153e-16,
		  -3.402285047279e-12,
		  4.0323172687618e-07,
		 -4.4552872560004e-15,
		 -1.0497645902244e-11,
		  9.0467920619251e-07,
		 -1.6949407409919e-14,
		 -2.4792040771674e-11,
		  1.5446991842704e-06,
		 -5.0374974710435e-14,
		 -2.6061135516454e-11,
		  1.6496148336252e-06,
		 -7.0757533805263e-14,
		 -8.0997998554832e-16,
		  2.9371250935851e-10,
		 -5.0821927262288e-19,
		    -1.2904235842e-14,
		   3.858635945172e-09,
		 -9.5317725127386e-18,
		 -1.2667805074888e-13,
		  3.0622252065335e-08,
		 -1.1042186603895e-16,
		 -8.9997875871198e-13,
		   1.724979933835e-07,
		 -9.3681167699318e-16,
		 -5.0591952805546e-12,
		  7.4638384924912e-07,
		 -6.3819161335112e-15,
		 -2.3667890420634e-11,
		  2.5712154717081e-06,
		 -3.6820805892379e-14,
		 -9.3572583953829e-11,
		  7.0259855942613e-06,
		 -1.8318370912039e-13,
		 -2.9454776804993e-10,
		  1.4236201837174e-05,
		 -7.4022398449415e-13,
		 -3.6515011344406e-10,
		   1.732181445178e-05,
		 -1.2516588464763e-12,
		 -1.8610647769457e-15,
		  9.5308379241549e-10,
		 -1.6639396993831e-18,
		  -4.012630878066e-14,
		  1.3679850884116e-08,
		 -3.3488319013322e-17,
		 -4.4067574824603e-13,
		  1.1999889443067e-07,
		 -4.2632691721156e-16,
		 -3.4666277050293e-12,
		  7.4969418855758e-07,
		 -4.0665662938451e-15,
		 -2.2185062821518e-11,
		  3.6269071632653e-06,
		 -3.2197923504739e-14,
		 -1.2205979760844e-10,
		  1.4109861945921e-05,
		 -2.2490279987485e-13,
		 -5.9880172848668e-10,
		  4.3865239238939e-05,
		 -1.4419718816963e-12,
		 -2.7145066578611e-09,
		  9.9724090744815e-05,
		 -8.6352856801054e-12,
		  -3.823313611422e-09,
		  0.00013307410520522,
		 -1.6976881796537e-11,
		  -1.163411885867e-14,
		  1.9406815504918e-09,
		 -1.7904897909159e-18,
		 -7.1866696283263e-14,
		  2.7526464749852e-08,
		 -3.3779143448437e-17,
		 -4.7797432298414e-13,
		  2.4485662132355e-07,
		 -4.2515655069289e-16,
		  -4.694536639928e-12,
		  1.6694412376674e-06,
		 -5.1683076976429e-15,
		 -3.6213816449835e-11,
		  9.0999143624355e-06,
		 -5.2417697174474e-14,
		 -2.3853238426315e-10,
		  4.1250918824636e-05,
		 -4.6978203598652e-13,
		  -1.329223327639e-09,
		  0.00015345627214384,
		  -3.893050005613e-12,
		 -1.4567659011895e-08,
		  0.00040210157026505,
		 -6.0261445039148e-11,
		 -2.3889495552076e-08,
		  0.00059613425863197,
		 -1.4119613470911e-10,
		   8.211184497332e-14,
		  1.3518200919309e-09,
		  2.4302981418502e-18,
		  3.9661693537157e-13,
		   1.196977642643e-08,
		  7.4134199333707e-17,
		 -9.3294518525898e-13,
		  2.1635427863172e-07,
		 -4.8886441098438e-16,
		 -6.2656322177719e-12,
		  1.7154936057505e-06,
		 -6.8798385350011e-15,
		 -5.9158710496022e-11,
		  1.1253203199015e-05,
		 -8.0685152720331e-14,
		 -5.3458305689896e-10,
		  6.6946817356645e-05,
		 -8.5088345166408e-13,
		  4.6846897133048e-09,
		  0.00035183897547095,
		  2.0859962090343e-11,
		 -5.3917829573784e-08,
		   0.0011168321998748,
		 -2.9697664870739e-10,
		 -1.0681640424536e-07,
		   0.0018687254319769,
		 -8.5881811116074e-10,
		  -5.302930948968e-13,
		 -2.0475523489367e-09,
		  7.9955723802144e-18,
		 -4.4559039496976e-12,
		  7.9231374035541e-08,
		 -1.1587136327108e-15,
		   4.915923626475e-12,
		  1.2751035988584e-07,
		 -5.8450419911105e-16,
		  1.8488069564608e-12,
		  3.7765516460923e-07,
		 -4.5870832319413e-15,
		  4.4417055803797e-11,
		  2.3121991480592e-06,
		 -9.8159221825012e-14,
		 -9.1851379097255e-09,
		  3.7183175935063e-05,
		 -3.0428580578208e-11,
		  5.0262652958085e-08,
		  0.00060130577391471,
		  2.8420055745272e-10,
		 -1.5449345823989e-07,
		   0.0024235655926094,
		 -1.1477993227382e-09,
		 -3.8156361277983e-07,
		   0.0045765105738095,
		 -4.2130476270744e-09,
		   2.787644601004e-12,
		   3.200193924701e-08,
		 -3.7963516638621e-16,
		  3.8547994520249e-11,
		 -4.1730806127242e-07,
		  1.1113137776658e-14,
		 -5.9663827195123e-11,
		 -5.4123693408636e-07,
		  4.8712460609138e-15,
		 -5.6967951284234e-12,
		 -2.2676565100961e-07,
		  8.6858839056741e-15,
		  1.0069570346511e-08,
		 -1.6261757181164e-05,
		  2.8244216735659e-11,
		 -8.0870578842052e-08,
		  -0.0001333243140322,
		 -3.7969239903556e-10,
		  2.3689175744071e-07,
		  0.00092543422277406,
		  1.8198659513039e-09,
		 -3.8539144812726e-07,
		   0.0046057068256216,
		 -3.8534913280648e-09,
		  -1.182750808517e-06,
		   0.0094798296063928,
		 -1.7822679230313e-08,
		 -1.5227642264031e-11,
		   -2.21151133808e-07,
		  4.9043622105317e-15,
		 -3.1562064869979e-10,
		  2.4508467674876e-06,
		 -1.0877380899446e-13,
		  7.3392232063037e-10,
		   3.860094738091e-06,
		 -6.3988542546045e-14,
		 -1.0063218519826e-08,
		  2.0961772241712e-05,
		  -2.864888700542e-11,
		   1.258842319255e-07,
		 -8.5317019647081e-05,
		  4.3373729274854e-10,
		 -4.4819432354174e-07,
		 -0.00055555289253155,
		 -2.8898104168037e-09,
		  8.5347376688592e-07,
		   0.0017714077282537,
		  9.1266733734671e-09,
		 -9.7412438243841e-07,
		   0.0085244244157302,
		 -1.2859604046882e-08,
		  -3.412780282597e-06,
		    0.017634655174384,
		 -6.8649498838762e-08,
		   1.216168914795e-10,
		  1.3163583366429e-06,
		 -5.2163953824842e-14,
		   2.677579811776e-09,
		 -1.7198000156357e-05,
		  1.2573394850295e-12,
		 -6.1157441705635e-10,
		 -4.7933650542619e-05,
		  2.9679335346831e-11,
		 -2.1614594258077e-07,
		  0.00044518492356637,
		 -5.2769821899314e-10,
		  9.8351987337964e-07,
		 -0.00067305367256378,
		  3.4623780332081e-09,
		 -1.9860705799535e-06,
		 -0.00088120869731824,
		 -1.7869591678677e-08,
		  2.8437355068304e-06,
		   0.0051875523907667,
		  4.2347434132503e-08,
		 -2.9557761518399e-06,
		    0.016617560357017,
		 -4.9628146263307e-08,
		 -9.8052284156402e-06,
		    0.030834078889681,
		 -2.5269315293524e-07,
		 -1.8916370563408e-09,
		 -7.7461443327227e-06,
		  5.8801655266169e-13,
		 -3.5543729163778e-08,
		  0.00020431084254565,
		 -5.1519703941182e-11,
		  7.0050668035267e-07,
		  -0.0010905638522771,
		  7.2523907317813e-10,
		 -3.1305610576713e-06,
		    0.002739718331217,
		 -6.3879804266022e-09,
		  6.5783073597591e-06,
		  -0.0041075679107526,
		  1.5397539829489e-08,
		 -8.4080117696979e-06,
		   0.0050897666086347,
		 -1.0423168329673e-07,
		  1.0023264376107e-05,
		    0.019338508339038,
		   1.957170349909e-07,
		 -1.1948312633762e-05,
		    0.035084994596673,
		 -2.3657044197423e-07,
		 -3.0366968824331e-05,
		    0.052617502363221,
		 -9.2403545458666e-07,
		  1.1542148524637e-07,
		 -1.8523767292625e-05,
		  2.1183255081654e-11,
		 -2.7389861299256e-06,
		  0.00036853613596563,
		 -7.6406496946652e-10,
		   1.379753546329e-05,
		  -0.0015861276828322,
		  4.1152121380762e-09,
		 -3.3004382217287e-05,
		   0.0032916812796013,
		 -5.1623958193135e-08,
		  4.5740966739175e-05,
		  -0.0042110019034299,
		  3.8731745213762e-08,
		 -4.2103339115293e-05,
		    0.004670606488693,
		 -4.6852297361953e-07,
		    4.24607342906e-05,
		    0.018842675527088,
		  7.8325695033809e-07,
		 -6.8313269171441e-05,
		    0.034095249612807,
		 -1.2250568072092e-06,
		 -0.00011580485195273,
		    0.051378290007486,
		 -3.2715759300435e-06,
		  4.8956759181102e-07,
		 -7.7464815477657e-06,
		  6.4547443224874e-11,
		 -1.4427282273662e-05,
		  0.00020432346534693,
		 -2.6822327713866e-09,
		  8.3208951785596e-05,
		  -0.0010906564986169,
		  1.6279367832763e-08,
		 -0.00022470026577736,
		   0.0027402490112026,
		 -2.1753281383543e-07,
		  0.00034376620555136,
		    -0.00410829539599,
		  1.2614474753381e-08,
		 -0.00032147017949114,
		   0.0050939198523013,
		 -2.2127465529406e-06,
		  0.00026404562555913,
		    0.019331808958875,
		  4.1041078702896e-06,
		 -0.00072235076032353,
		    0.035100650801704,
		 -1.0622476312136e-05,
		 -0.00078886509346979,
		    0.052647004144265,
		 -1.9438866638222e-05,
		  2.8816237129997e-07,
		  1.3162184055114e-06,
		  2.7213412990886e-11,
		 -1.8361933690236e-05,
		 -1.7186755027523e-05,
		 -2.3188110717437e-09,
		  0.00016878449845264,
		 -4.8062748241688e-05,
		  2.9806456290368e-08,
		  -0.0007436744324906,
		  0.00044589269311752,
		 -1.9781951824911e-07,
		   0.0020486655806022,
		   -0.000674606309027,
		  1.7302660115556e-07,
		  -0.0042796653685224,
		 -0.00087756005047526,
		 -1.7334649017386e-06,
		   0.0086384125207005,
		   0.0051953757313558,
		  7.8859840997166e-07,
		    0.022808898772313,
		    0.016404727179075,
		  0.00014410263565283,
		   0.0071130691147846,
		    0.030693658021655,
		  9.1506363585331e-05,
		 -3.8763409066038e-08,
		  -2.211362060535e-07,
		 -2.7140755090224e-12,
		  3.0829457027325e-06,
		  2.4492937783446e-06,
		  2.9962231349338e-10,
		  -1.140615430569e-06,
		  3.8611930268436e-06,
		 -3.0788575666394e-10,
		 -0.00015278631019917,
		   2.107101473257e-05,
		 -2.3158217708772e-08,
		  0.00087697509236226,
		  -8.600914404495e-05,
		  1.4658355556863e-07,
		   -0.002245841289548,
		 -0.00055422653555402,
		 -3.6406856599887e-07,
		   0.0018708911079239,
		    0.001782045765395,
		 -3.5551584382964e-06,
		     0.01555157280806,
		   0.0083778492184459,
		  8.6344956729831e-05,
		   0.0078694304664876,
		    0.017505797571056,
		  7.6548970187118e-05,
		 -6.5270399213427e-09,
		  3.2004561050149e-08,
		 -4.4705722451986e-13,
		 -5.4724760826746e-07,
		 -4.1708115879675e-07,
		 -4.0917535456798e-11,
		  1.2117233751798e-07,
		 -5.4131594529098e-07,
		  1.7634471901963e-11,
		  2.2825678385686e-07,
		 -2.2677887619286e-07,
		  -2.332677915581e-11,
		  0.00015063883396821,
		 -1.6371860469317e-05,
		  2.4316664673421e-08,
		 -0.00088522289465741,
		 -0.00013260299134876,
		 -1.9403858671149e-07,
		     0.00116358159409,
		  0.00092687394695137,
		 -1.7610016085421e-07,
		    0.010127737333783,
		   0.0045300639976459,
		  3.9563465513685e-05,
		   0.0060725625331246,
		   0.0094067447476638,
		  3.9775796075116e-05,
		  8.5882517087326e-09,
		 -2.0497715730675e-09,
		  3.6818147376662e-13,
		  1.2314101841827e-07,
		  7.9192519057781e-08,
		  6.7648843864144e-12,
		  2.0006823007836e-07,
		  1.2744814105666e-07,
		  1.3288901582684e-11,
		  1.1101052812049e-06,
		  3.7710955809321e-07,
		  1.3564843376597e-10,
		  5.3825189340224e-06,
		  2.3070149880682e-06,
		  1.6782835142449e-09,
		 -0.00011226283266793,
		  3.7210355763406e-05,
		  9.7992374670971e-09,
		   0.0013203700856678,
		  0.00059887586896283,
		  1.0851516522243e-06,
		   0.0059565465199217,
		   0.0023915955219666,
		  1.4956472999258e-05,
		   0.0036901666160441,
		   0.0045457258196691,
		  1.5214392145386e-05,
		  6.1271504791222e-09,
		  1.3505103074839e-09,
		  2.4996741976449e-13,
		  8.6178705661154e-08,
		  1.1944491207577e-08,
		   5.137647541347e-12,
		  8.5357543165687e-07,
		  2.1600774947408e-07,
		   7.602484832694e-11,
		  5.7009063134148e-06,
		  1.7121234074271e-06,
		  8.3557849821517e-10,
		  3.2902500021071e-05,
		  1.1223886707334e-05,
		    8.33201117365e-09,
		  0.00017514056016227,
		  6.6707310058406e-05,
		  7.8783758356114e-08,
		   0.0010268111421909,
		  0.00034988876465151,
		  7.2458537502997e-07,
		   0.0028890286329898,
		   0.0011061385748777,
		  4.4420668750751e-06,
		    0.001743045668566,
		   0.0018588904862994,
		  4.3409164741192e-06,
		  1.1737425833502e-08,
		  1.9380163907759e-09,
		   4.744385328037e-13,
		  1.5004539114025e-07,
		   2.748291973641e-08,
		  8.3119671009804e-12,
		  1.2337379021331e-06,
		   2.443864189607e-07,
		  9.7319124677273e-11,
		  7.5156012256065e-06,
		   1.665578665965e-06,
		   8.776918842409e-10,
		  3.6532463540234e-05,
		  9.0738320208136e-06,
		  6.6020882999013e-09,
		  0.00014844130938819,
		  4.1099196034756e-05,
		  4.3325359727357e-08,
		   0.0005016424981695,
		  0.00015269984312496,
		  2.4478059247296e-07,
		   0.0010511923924308,
		  0.00039942998139825,
		  9.7172174204238e-07,
		   0.0006056795553578,
		  0.00059381226812638,
		  9.0100876541035e-07,
		  6.3402827196358e-09,
		   9.517719162527e-10,
		  2.2506996894591e-13,
		  8.3027388710188e-08,
		   1.365834002232e-08,
		  3.9072885812307e-12,
		  6.6027829246521e-07,
		  1.1978049524366e-07,
		  4.2401490328334e-11,
		   3.723990944295e-06,
		  7.4808626771197e-07,
		  3.3731292730567e-10,
		  1.6130656535893e-05,
		  3.6175794567736e-06,
		  2.1400944731138e-09,
		  5.5552998709024e-05,
		  1.4065504859982e-05,
		  1.1266361116686e-08,
		  0.00014886996765111,
		  4.3694438971048e-05,
		  4.8455795957174e-08,
		  0.00025786257445816,
		  9.9264081751176e-05,
		  1.4573086276851e-07,
		  0.00014132626369108,
		  0.00013269593168412,
		  1.2844123200081e-07,
		  2.0196144481431e-09,
		  2.9335942728748e-10,
		  5.7801008319575e-14,
		  2.4371207048367e-08,
		  3.8533215834418e-09,
		  9.1563159233287e-13,
		  1.7635068019561e-07,
		  3.0573570756283e-08,
		   8.890735180504e-12,
		  8.9802956585578e-07,
		   1.721788595474e-07,
		  6.2294286092623e-11,
		  3.4723526277468e-06,
		  7.4476307142113e-07,
		  3.4134382215301e-10,
		  1.0487414116478e-05,
		   2.564619764956e-06,
		  1.5139812627697e-09,
		  2.4109144805013e-05,
		  7.0048264081805e-06,
		  5.3427862036769e-09,
		  3.6212992888414e-05,
		   1.418924282683e-05,
		  1.3099830264134e-08,
		  1.8744014649777e-05,
		  1.7285486757982e-05,
		  1.0903972130702e-08,
		  8.5999687070312e-10,
		  1.1820004990485e-10,
		  2.0076581287313e-14,
		  8.9262320598993e-09,
		  1.3343222291751e-09,
		  2.6869032897206e-13,
		  5.3940756073933e-08,
		  8.8461977070299e-09,
		  2.1387106647489e-12,
		  2.2474431955869e-07,
		  4.0870193146589e-08,
		  1.2014845788599e-11,
		  7.0239146532585e-07,
		  1.4372773006225e-07,
		  5.1962494506455e-11,
		  1.7058615665642e-06,
		  4.0237949118407e-07,
		  1.8003964941138e-10,
		  3.1593398008078e-06,
		  9.0252450232188e-07,
		  4.9426460225216e-10,
		  3.9050079204435e-06,
		  1.5408905149945e-06,
		  9.5420701016741e-10,
		  1.7920320616501e-06,
		  1.6470109848532e-06,
		  7.0194835571102e-10
      };//end return
    }else{
      std::cout << "returning empty true solution" << std::endl;
      return {};
    }
  }//get
};//struct

}}}//end namespace rompp::apps::test
#endif
