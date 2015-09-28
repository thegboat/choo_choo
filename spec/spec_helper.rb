$LOAD_PATH.unshift File.expand_path('../../lib', __FILE__)
require 'choo_choo'
require 'benchmark'
require 'pry'
require 'pry-byebug'


module ChooChoo
  def self.test_string
    @test_string ||= %{
ISA*00*          *00*          *01*030240928      *ZZ*AV09311993     *140505*1730*^*00501*855460856*0*P*:~GS*HP*592015694*AV01101957*20140505*1730*1*X*005010X221A1~ST*835*1001~BPR*I*2481.28*C*ACH*CCP*01*063101454*DA*0218274901*1592015694*BC BS  FL*01*063000047*DA*898008544026*20140505~TRN*1*201406657*1592015694~REF*EV*030240928~DTM*405*20140505~N1*PR*FLORIDA BLUE~N3*4800 DEERWOOD CAMPUS PARKWAY~N4*JACKSONVILLE*FL*32246~PER*BL**TE*8007272227~PER*IC**UR*MCGS.BCBSFL.COM~N1*PE*ORTHO FLORIDA LLC*XX*1437302817~N3*PO BOX 100988~N4*ATLANTA*GA*30384~REF*PQ*89153~REF*TJ*208032857~LX*1~CLP*06215404*22*-343.0*0**12*Q100000401628077~NM1*QC*1*MINERVINI II*JOSEPH*A***MI*H67650427~NM1*IL*1*MINERVINI*****MI*H67650427~NM1*82*1*TOMAN*CHARLES*V***XX*1326167230~REF*1L*7640210101~REF*F8*Q100000401628077~DTM*050*20140402~SVC*HC:99203*-343.0*0**1~DTM*472*20140325~CAS*CO*B16*-343~REF*6R*06215404-1~AMT*B6*128.01~LQ*HE*N381~LX*2~CLP*1359949870*1*339*101.49*25*12*Q100000406464391~NM1*QC*1*VANDERVORST*ROBERT*C***MI*H12035160~NM1*IL*1******MI*H12035160~NM1*82*1*KOLETTIS*GEORGE*J***XX*1821198490~REF*1L*7640210101~REF*F8*Q100000406464391~DTM*050*20140501~SVC*HC:99214*339*101.49**1~DTM*472*20140425~CAS*CO*45*212.51~CAS*PR*3*25~REF*6R*1359949870-1~AMT*B6*126.49~LQ*HE*N381~LX*3~CLP*19115740*2*244*0*244*12*Q100000400908766~NM1*QC*1*HASON*ROBERTA****MI*H15343245~NM1*IL*1******MI*H15343245~NM1*82*1*KOLETTIS*GEORGE*J***XX*1821198490~REF*1L*7644210201~REF*F8*Q100000400908766~DTM*050*20140328~SVC*HC:97110*200*0**0**2~DTM*472*20140317~CAS*PR*22*200~REF*6R*19115740-1~AMT*B6*74.34~LQ*HE*N381~LQ*HE*N598~SVC*HC:G0283*44*0**0**1~DTM*472*20140317~CAS*PR*22*44~REF*6R*19115740-2~AMT*B6*16.32~LQ*HE*N381~LQ*HE*N598~LX*4~CLP*1921608251*1*339*101.49*25*12*Q100000406275130~NM1*QC*1*WILSON*SARAH*J***MI*H74676458~NM1*IL*1******MI*H74676458~NM1*82*1*GUPTA*MANISH*K***XX*1770687386~REF*1L*7640210101~REF*F8*Q100000406275130~DTM*050*20140430~SVC*HC:99214*339*101.49**1~DTM*472*20140422~CAS*CO*45*212.51~CAS*PR*3*25~REF*6R*1921608251-1~AMT*B6*126.49~LQ*HE*N381~LX*5~CLP*2245956459*2*1168*77.89**12*Q100000406492080~NM1*QC*1*TENNANT*JEFFREY*S***MI*H15426612~NM1*IL*1**JEANIE*L***MI*H15426612~NM1*82*1*LEVIN*LARRY*P***XX*1134109325~REF*1L*7644210401~REF*F8*Q100000406492080~DTM*050*20140501~SVC*HC:23600:RT*1066*71.07**1~DTM*472*20140407~CAS*OA*23*994.93~REF*6R*2245956459-1~AMT*B6*397.98~LQ*HE*N381~SVC*HC:73030:LT*102*6.82**1~DTM*472*20140407~CAS*OA*23*95.18~REF*6R*2245956459-2~AMT*B6*38.17~LQ*HE*N381~LX*6~CLP*2564769459*2*401*21.89**12*Q100000406593185~NM1*QC*1*MARQUES*AMALIA****MI*H47191221~NM1*IL*1******MI*H47191221~NM1*82*1*CEBALLOS*CESAR*E***XX*1952366502~REF*1L*7644210201~REF*F8*Q100000406593185~DTM*050*20140501~SVC*HC:97110:GP*202*10.12**2~DTM*472*20140409~CAS*OA*23*191.88~REF*6R*2564769459-1~AMT*B6*74.34~LQ*HE*N381~SVC*HC:97112:GP*105*7**1~DTM*472*20140409~CAS*OA*23*98~REF*6R*2564769459-2~AMT*B6*38.84~LQ*HE*N381~SVC*HC:97140:GP*94*4.77**1~DTM*472*20140409~CAS*OA*23*89.23~REF*6R*2564769459-3~AMT*B6*34.7~LQ*HE*N381~LX*7~CLP*2623296296*2*400*21.89**12*Q100000405605845~NM1*QC*1*MARQUES*AMALIA****MI*H47191221~NM1*IL*1******MI*H47191221~NM1*82*1*CEBALLOS*CESAR*E***XX*1952366502~REF*1L*7644210201~REF*F8*Q100000405605845~DTM*050*20140425~SVC*HC:97110:GP*201*10.12**2~DTM*472*20140403~CAS*OA*23*190.88~REF*6R*2623296296-1~AMT*B6*74.34~LQ*HE*N381~SVC*HC:97112:GP*105*7**1~DTM*472*20140403~CAS*OA*23*98~REF*6R*2623296296-2~AMT*B6*38.84~LQ*HE*N381~SVC*HC:97140:GP*94*4.77**1~DTM*472*20140403~CAS*OA*23*89.23~REF*6R*2623296296-3~AMT*B6*34.7~LQ*HE*N381~LX*8~CLP*2941493856*2*371*77.23**12*Q100000405928152~NM1*QC*1*HAWKINS*BRAD*J***MI*H5396129204~NM1*IL*1******MI*261634305~NM1*74*1*HAWKINS*ALENA*D***C*H53961292~NM1*82*1*STEWART*CHARLES*E***XX*1255440848~REF*1L*7640210101~REF*F8*Q100000405928152~DTM*050*20140411~AMT*I*.1~SVC*HC:99213*230*66.87**1~DTM*472*20140331~CAS*CO*252*163.13~REF*6R*2941493856-1~AMT*B6*85.88~LQ*HE*MA04~LQ*HE*N381~SVC*HC:73564:LT*141*10.36**1~DTM*472*20140331~CAS*CO*252*130.64~REF*6R*2941493856-2~AMT*B6*52.73~LQ*HE*MA04~LQ*HE*N381~LX*9~CLP*3272651104*1*430.09*63.86*25*12*Q100000406464380~NM1*QC*1*DAY*MARGARET*M***MI*H11294974~NM1*IL*1******MI*H11294974~NM1*82*1*KREBSBACH*MICHAEL*J***XX*1003916677~REF*1L*7640210101~REF*F8*Q100000406464380~DTM*050*20140501~SVC*HC:99213:25*230*60.88**1~DTM*472*20140425~CAS*CO*45*144.12~CAS*PR*3*25~REF*6R*3272651104-1~AMT*B6*85.88~LQ*HE*N381~SVC*HC:20550:RT*188*0**0**1~DTM*472*20140425~CAS*CO*11*188~REF*6R*3272651104-2~REF*0K*05-20550~AMT*B6*70.27~LQ*HE*N381~LQ*HE*N657~SVC*HC:J1030*12.09*2.98**1~DTM*472*20140425~CAS*CO*45*9.11~REF*6R*3272651104-3~AMT*B6*2.98~LQ*HE*N381~LX*10~CLP*3350212795*2*400*21.89**12*Q100000406027246~NM1*QC*1*MARQUES*AMALIA****MI*H47191221~NM1*IL*1******MI*H47191221~NM1*82*1*CEBALLOS*CESAR*E***XX*1952366502~REF*1L*7644210201~REF*F8*Q100000406027246~DTM*050*20140429~SVC*HC:97110:GP*201*10.12**2~DTM*472*20140408~CAS*OA*23*190.88~REF*6R*3350212795-1~AMT*B6*74.34~LQ*HE*N381~SVC*HC:97112:GP*105*7**1~DTM*472*20140408~CAS*OA*23*98~REF*6R*3350212795-2~AMT*B6*38.84~LQ*HE*N381~SVC*HC:97140:GP*94*4.77**1~DTM*472*20140408~CAS*OA*23*89.23~REF*6R*3350212795-3~AMT*B6*34.7~LQ*HE*N381~LX*11~CLP*4442644730*1*873.52*252.62*25*12*Q100000405540127~NM1*QC*1*KUMAR*VERONICA****MI*H84833001~NM1*IL*1**KULDEEP****MI*H84833001~NM1*82*1*WILLIAMS*HEATHER*C***XX*1003852880~REF*1L*7640210401~REF*F8*Q100000405540127~DTM*050*20140425~SVC*HC:99203:25*355*103.01**1~DTM*472*20140414~CAS*CO*45*226.99~CAS*PR*3*25~REF*6R*4442644730-1~AMT*B6*128.01~LQ*HE*N381~SVC*HC:20526:59:51*259*92.47**1~DTM*472*20140414~CAS*CO*45*166.53~REF*6R*4442644730-2~AMT*B6*92.47~LQ*HE*N381~SVC*HC:20610:59:51*206*36.64**1~DTM*472*20140414~CAS*CO*45*169.36~REF*6R*4442644730-3~AMT*B6*36.64~LQ*HE*N381~SVC*HC:J3301*20.04*7.92**4~DTM*472*20140414~CAS*CO*45*12.12~REF*6R*4442644730-4~AMT*B6*7.92~LQ*HE*N381~SVC*HC:J0702*33.48*12.58**2~DTM*472*20140414~CAS*CO*45*20.9~REF*6R*4442644730-5~AMT*B6*12.58~LQ*HE*N381~LX*12~CLP*4760494387*1*186*55.52*13.88*12*Q100000406274313~NM1*QC*1*POWELL*KATHERINE*C***MI*H14003090~NM1*IL*1******MI*H14003090~NM1*82*1*KOLETTIS*GEORGE*J***XX*1821198490~REF*1L*7640210101~REF*F8*Q100000406274313~DTM*050*20140430~SVC*HC:97140*186*55.52**2~DTM*472*20140423~CAS*CO*45*116.6~CAS*PR*2*13.88~REF*6R*4760494387-1~AMT*B6*69.4~LQ*HE*N381~LX*13~CLP*4899663951*1*764.37*0*155.64*12*Q100000406048911~NM1*QC*1*BERNS*TERRI*L***MI*H40741182~NM1*IL*1******MI*H40741182~NM1*82*1*BROMSON*MARK*S***XX*1942319538~REF*1L*7640210101~REF*F8*Q100000406048911~DTM*050*20140429~SVC*HC:L4360:LT*764.37*0**1~DTM*472*20140416~CAS*CO*45*608.73~CAS*PR*1*155.64~REF*6R*4899663951-1~AMT*B6*155.64~LQ*HE*N381~LX*14~CLP*5246909666*1*244*72.53*18.13*12*Q100000406275116~NM1*QC*1*VANDERVORST*ROBERT*C***MI*H12035160~NM1*IL*1******MI*H12035160~NM1*82*1*KOLETTIS*GEORGE*J***XX*1821198490~REF*1L*7640210101~REF*F8*Q100000406275116~DTM*050*20140430~SVC*HC:97110*200*59.47**2~DTM*472*20140424~CAS*CO*45*125.66~CAS*PR*2*14.87~REF*6R*5246909666-1~AMT*B6*74.34~LQ*HE*N381~SVC*HC:G0283*44*13.06**1~DTM*472*20140424~CAS*CO*45*27.68~CAS*PR*2*3.26~REF*6R*5246909666-2~AMT*B6*16.32~LQ*HE*N381~LX*15~CLP*5496831610*1*339*101.49*25*12*Q100000406048475~NM1*QC*1*RUSSELL*VALERIE*E***MI*H74783170~NM1*IL*1******MI*H74783170~NM1*82*1*GUPTA*MANISH*K***XX*1770687386~REF*1L*7640210101~REF*F8*Q100000406048475~DTM*050*20140429~SVC*HC:99214*339*101.49**1~DTM*472*20140421~CAS*CO*45*212.51~CAS*PR*3*25~REF*6R*5496831610-1~AMT*B6*126.49~LQ*HE*N381~LX*16~CLP*55830426*2*629*0*629*12*Q100000401397988~NM1*QC*1*DONNELLY*JOSEPH*R***MI*H96689081~NM1*IL*1**MARGARET*B***MI*H96689081~NM1*82*1*LEVIN*LARRY*P***XX*1134109325~REF*1L*7640210101~REF*F8*Q100000401397988~DTM*050*20140401~SVC*HC:99204*527*0**0**1~DTM*472*20140210~CAS*PR*A1*527~REF*6R*55830426-1~AMT*B6*196.93~LQ*HE*MA92~LQ*HE*N245~LQ*HE*N381~SVC*HC:73030:RT*102*0**0**1~DTM*472*20140210~CAS*PR*A1*102~REF*6R*55830426-2~AMT*B6*38.17~LQ*HE*MA92~LQ*HE*N245~LQ*HE*N381~LX*17~CLP*6057162767*1*429*128.05*32.01*12*Q100000405540658~NM1*QC*1*POWELL*KATHERINE*C***MI*H14003090~NM1*IL*1******MI*H14003090~NM1*82*1*KOLETTIS*GEORGE*J***XX*1821198490~REF*1L*7640210101~REF*F8*Q100000405540658~DTM*050*20140425~SVC*HC:97001:59*236*70.55**1~DTM*472*20140421~CAS*CO*45*147.81~CAS*PR*2*17.64~REF*6R*6057162767-1~AMT*B6*88.19~LQ*HE*N381~SVC*HC:97110*100*29.74**1~DTM*472*20140421~CAS*CO*45*62.83~CAS*PR*2*7.43~REF*6R*6057162767-2~AMT*B6*37.17~LQ*HE*N381~SVC*HC:97140*93*27.76**1~DTM*472*20140421~CAS*CO*45*58.3~CAS*PR*2*6.94~REF*6R*6057162767-3~AMT*B6*34.7~LQ*HE*N381~LX*18~CLP*6129168511*1*527*171.93*25*12*Q100000405540701~NM1*QC*1*RAMIL*AURELIO*L***MI*H91833607~NM1*IL*1******MI*H91833607~NM1*82*1*KAZDAN*SCOTT*D***XX*1285812511~REF*1L*7640210101~REF*F8*Q100000405540701~DTM*050*20140425~SVC*HC:99204*527*171.93**1~DTM*472*20140424~CAS*CO*45*330.07~CAS*PR*3*25~REF*6R*6129168511-1~AMT*B6*196.93~LQ*HE*N381~LX*19~CLP*6173306660*1*338*101.34*25*12*Q100000406048363~NM1*QC*1*BERNS*TERRI*L***MI*H40741182~NM1*IL*1******MI*H40741182~NM1*82*1*BROMSON*MARK*S***XX*1942319538~REF*1L*7640210101~REF*F8*Q100000406048363~DTM*050*20140429~SVC*HC:99213*230*60.88**1~DTM*472*20140423~CAS*CO*45*144.12~CAS*PR*3*25~REF*6R*6173306660-1~AMT*B6*85.88~LQ*HE*N381~SVC*HC:73610:LT*108*40.46**1~DTM*472*20140423~CAS*CO*45*67.54~REF*6R*6173306660-2~AMT*B6*40.46~LQ*HE*N381~LX*20~CLP*7421152914*2*400*21.89**12*Q100000405741074~NM1*QC*1*MARQUES*AMALIA****MI*H47191221~NM1*IL*1******MI*H47191221~NM1*82*1*CEBALLOS*CESAR*E***XX*1952366502~REF*1L*7644210201~REF*F8*Q100000405741074~DTM*050*20140426~SVC*HC:97110:GP*201*10.12**2~DTM*472*20140404~CAS*OA*23*190.88~REF*6R*7421152914-1~AMT*B6*74.34~LQ*HE*N381~SVC*HC:97112:GP*105*7**1~DTM*472*20140404~CAS*OA*23*98~REF*6R*7421152914-2~AMT*B6*38.84~LQ*HE*N381~SVC*HC:97140:GP*94*4.77**1~DTM*472*20140404~CAS*OA*23*89.23~REF*6R*7421152914-3~AMT*B6*34.7~LQ*HE*N381~LX*21~CLP*7529865953*2*230*0*230*12*Q100000402553928~NM1*QC*1*HASON*ROBERTA****MI*H15343245~NM1*IL*1******MI*H15343245~NM1*82*1*KOLETTIS*GEORGE*J***XX*1821198490~REF*1L*7644210201~REF*F8*Q100000402553928~DTM*050*20140408~SVC*HC:99213*230*0**0**1~DTM*472*20140325~CAS*PR*22*230~REF*6R*7529865953-1~AMT*B6*85.88~LQ*HE*N381~LQ*HE*N598~LX*22~CLP*7658163725*1*461*147.2*25*12*Q100000405815658~NM1*QC*1*BERNS*TERRI*L***MI*H40741182~NM1*IL*1******MI*H40741182~NM1*82*1*BROMSON*MARK*S***XX*1942319538~REF*1L*7640210101~REF*F8*Q100000405815658~DTM*050*20140428~SVC*HC:99203:25*343*103.01**1~DTM*472*20140416~CAS*CO*45*214.99~CAS*PR*3*25~REF*6R*7658163725-1~AMT*B6*128.01~LQ*HE*N381~SVC*HC:29540:LT*118*44.19**1~DTM*472*20140416~CAS*CO*45*73.81~REF*6R*7658163725-2~AMT*B6*44.19~LQ*HE*N381~LX*23~CLP*7685662467*1*441*139.45*25*12*Q100000406463823~NM1*QC*1*COHEN*MARK*H***MI*H93920077~NM1*IL*1******MI*H93920077~NM1*82*1*BROMSON*MARK*S***XX*1942319538~REF*1L*7640210101~REF*F8*Q100000406463823~DTM*050*20140501~SVC*HC:99214*339*101.49**1~DTM*472*20140424~CAS*CO*45*212.51~CAS*PR*3*25~REF*6R*7685662467-1~AMT*B6*126.49~LQ*HE*N381~SVC*HC:73630:RT*102*37.96**1~DTM*472*20140424~CAS*CO*45*64.04~REF*6R*7685662467-2~AMT*B6*37.96~LQ*HE*N381~LX*24~CLP*80707516*2*497*21.49*93*12*Q100000399144664~NM1*QC*1*LACMAN*LOUIS****MI*H99502156~NM1*IL*1******MI*H99502156~NM1*82*1*GUPTA*MANISH*K***XX*1770687386~REF*1L*7644210201~REF*F8*Q100000399144664~DTM*050*20140318~AMT*I*.2~SVC*HC:97110:GP*300*14.69**3~DTM*472*20140227~CAS*OA*23*285.31~AMT*B6*111.51~LQ*HE*N381~SVC*HC:97112:GP*104*6.8**1~DTM*472*20140227~CAS*OA*23*97.2~AMT*B6*38.84~LQ*HE*N381~SVC*HC:97140:GP*93*0**0**1~DTM*472*20140227~CAS*PR*119*93~AMT*B6*34.7~LQ*HE*N130~LQ*HE*N362~LQ*HE*N381~LX*25~CLP*8759315586*1*339*0**12*M00001R590124027~NM1*QC*1*MINERVINI II*JOSEPH*A***MI*H67650427~NM1*IL*1*MINERVINI*****MI*H67650427~NM1*82*1*TOMAN*CHARLES*V***XX*1326167230~REF*1L*7640210101~REF*F8*Q100000401628077~DTM*050*20140501~SVC*HC:99214*339*0**0**1~DTM*472*20140325~CAS*OA*18*339~REF*6R*8759315586-1~AMT*B6*126.49~LQ*HE*N381~LQ*HE*N552~LX*26~CLP*8759315586*1*339*0**12*Q100000406464108~NM1*QC*1*MINERVINI II*JOSEPH*A***MI*H67650427~NM1*IL*1*MINERVINI*****MI*H67650427~NM1*82*1*TOMAN*CHARLES*V***XX*1326167230~REF*1L*7640210101~REF*F8*Q100000406464108~DTM*050*20140501~SVC*HC:99214*339*0**0**1~DTM*472*20140325~CAS*CO*97*339~REF*6R*8759315586-1~AMT*B6*126.49~LQ*HE*N111~LQ*HE*N381~LX*27~CLP*9250857480*1*629*209.89*25*12*Q100000406274693~NM1*QC*1*MILLER*BART*E***MI*H12113118~NM1*IL*1******MI*H12113118~NM1*82*1*GUPTA*MANISH*K***XX*1770687386~REF*1L*7640210101~REF*F8*Q100000406274693~DTM*050*20140430~SVC*HC:99204*527*171.93**1~DTM*472*20140422~CAS*CO*45*330.07~CAS*PR*3*25~REF*6R*9250857480-1~AMT*B6*196.93~LQ*HE*N381~SVC*HC:73630*102*37.96**1~DTM*472*20140422~CAS*CO*45*64.04~REF*6R*9250857480-2~AMT*B6*37.96~LQ*HE*N381~LX*28~CLP*9381637181*1*343*103.01*25*12*Q100000405815495~NM1*QC*1*KLEIN*DONALD*M***MI*H80200539~NM1*IL*1******MI*H80200539~NM1*82*1*BROMSON*MARK*S***XX*1942319538~REF*1L*7640210101~REF*F8*Q100000405815495~DTM*050*20140428~SVC*HC:99203*343*103.01**1~DTM*472*20140423~CAS*CO*45*214.99~CAS*PR*3*25~REF*6R*9381637181-1~AMT*B6*128.01~LQ*HE*N381~LX*29~CLP*9720773309*1*1193*420.87*25*12*Q100000405815552~NM1*QC*1*WALKER*CHANDELLA*T***MI*H15257791~NM1*IL*1******MI*H15257791~NM1*82*1*GUPTA*MANISH*K***XX*1770687386~REF*1L*7640210101~REF*F8*Q100000405815552~DTM*050*20140428~SVC*HC:99204:25*527*171.93**1~DTM*472*20140418~CAS*CO*45*330.07~CAS*PR*3*25~REF*6R*9720773309-1~AMT*B6*196.93~LQ*HE*N381~SVC*HC:76881*376*140.5**1~DTM*472*20140418~CAS*CO*45*235.5~REF*6R*9720773309-2~AMT*B6*140.5~LQ*HE*N381~SVC*HC:20550*188*70.27**1~DTM*472*20140418~CAS*CO*45*117.73~REF*6R*9720773309-3~AMT*B6*70.27~LQ*HE*N381~SVC*HC:73030*102*38.17**1~DTM*472*20140418~CAS*CO*45*63.83~REF*6R*9720773309-4~AMT*B6*38.17~LQ*HE*N381~LX*30~CLP*9818146855*2*690.02*46.07**12*Q100000406464433~NM1*QC*1*MISSITA JR*GEORGE****MI*H10099620~NM1*IL*1******MI*H10099620~NM1*82*1*KOLETTIS*GEORGE*J***XX*1821198490~REF*1L*7644210201~REF*F8*Q100000406464433~DTM*050*20140501~SVC*HC:99203:25*343*22.86**1~DTM*472*20140402~CAS*OA*23*320.14~REF*6R*9818146855-1~AMT*B6*128.01~LQ*HE*N381~SVC*HC:20610:LT*196*13.08**1~DTM*472*20140402~CAS*OA*23*182.92~REF*6R*9818146855-2~AMT*B6*73.27~LQ*HE*N381~SVC*HC:73564:LT*141*9.42**1~DTM*472*20140402~CAS*OA*23*131.58~REF*6R*9818146855-3~AMT*B6*52.73~LQ*HE*N381~SVC*HC:J3301*10.02*.71**2~DTM*472*20140402~CAS*OA*23*9.31~REF*6R*9818146855-4~AMT*B6*3.96~LQ*HE*N381~PLB*1437302817*20140505*L6:INTEREST*-.3~SE*00*000000000~GE*0*00~IEA*0*000000000~
  }
end

  def self.test_string2
    @test_string2 ||= "ISA*00*          *00*          *ZZ*133052274      *ZZ*264007676      *130415*0246*^*00501*000118103*0*P*<~GS*HP*133052274*264007676*20130415*0246*1*X*005010X221A1~ST*835*0059~BPR*I*551.59*C*ACH*CCP*01*011900445*DA*0000009046*1066033492**01*111000614*DA*238721164365*20130419~TRN*1*813105550002225*1066033492*60054~REF*EV*133052274~DTM*405*20130415~N1*PR*AETNA~N3*151 FARMINGTON AVENUE~N4*HARTFORD*CT*06156~REF*2U*60054~PER*BL*Provider Service~N1*PE*CONTEMPORARY OB/GYN OF GRAPEVINE*XX*1962408062~N3*1600 W COLLEGE ST STE 340~N4*GRAPEVINE*TX*760513577~REF*PQ*788692840~REF*TJ*752710490~LX*1~TS3*1962408062*11*20131231*5*1340~CLP*83238113*1*125*49.77*25*13*EAJK6NHT30000*11*1~NM1*QC*1*ALLISON LUMPKIN*JULIA*M~NM1*IL*1*LUMPKIN*RUSSELL****MI*821189992~NM1*74*1***L**JR*C*W173066921~NM1*82*1*NEW*TROY*G***XX*1962408062~REF*1L*0326475-010-00190-AA~REF*CE*Aetna Choice  POS II NET 00338~DTM*232*20130405~DTM*233*20130405~DTM*050*20130408~PER*CX**TE*8886323862~AMT*AU*125~SVC*HC<99213*125*49.77**1~DTM*472*20130405~CAS*CO*45*50.23~CAS*PR*3*25~REF*6R*83238113-1~AMT*B6*74.77~CLP*96385257*1*175*104.25**13*EJAA6M14Q0000*11*1~NM1*QC*1*DEVINE*JILLIAN****MI*W181960503~NM1*82*1*NEW*TROY*G***XX*1962408062~REF*1L*0878752-036-00014-GB~REF*CE*Aetna Choice  POS II NET 03859~DTM*232*20130404~DTM*233*20130404~DTM*050*20130405~PER*CX**TE*8886323862~AMT*AU*175~SVC*HC<99395*175*104.25**1~DTM*472*20130404~CAS*CO*45*70.75~REF*6R*96385257-1~AMT*B6*104.25~CLP*43691534*1*575*152.09**13*EJFA6M2C30000*21*1~NM1*QC*1*LE*DUYEN~NM1*IL*1*NGUYEN*DZUNG****MI*W188654143~NM1*82*1*NEW*TROY*G***XX*1962408062~REF*1L*0878752-034-00023-ED~REF*CE*Aetna HealthFund  Aetna Choice  POS II NET 03859~DTM*232*20130404~DTM*233*20130404~DTM*050*20130405~PER*CX**TE*8886323862~AMT*AU*575~SVC*HC<59514<80*575*152.09**1~DTM*472*20130404~CAS*CO*45*422.91~REF*6R*43691534-1~AMT*B6*152.09~CLP*78288305*1*215*119.34**13*EXAA52M880000*11*1~NM1*QC*1*OSCAR*LINDA~NM1*IL*1*CLEMONS*CHRISTOPHER****MI*W104545356~NM1*74*1*CLEMENT**J~NM1*82*1*NEW*TROY*G***XX*1962408062~REF*1L*0724616-015-00001-UA~REF*CE*Aetna Choice  POS II NET 00338~DTM*232*20130403~DTM*233*20130403~DTM*050*20130404~PER*CX**TE*8886323862~AMT*AU*215~SVC*HC<99385*215*119.34**1~DTM*472*20130403~CAS*CO*45*95.66~REF*6R*78288305-1~AMT*B6*119.34~CLP*94471570*1*250*126.14**13*E8YZ55T640000*11*1~NM1*QC*1*CHOI*JIHEE****MI*W111098904~NM1*82*1*NEW*TROY*G***XX*1962408062~REF*1L*0878752-034-00012-EB~REF*CE*Aetna HealthFund  Aetna Choice  POS II NET 03859~DTM*232*20130408~DTM*233*20130408~DTM*050*20130409~PER*CX**TE*8886323862~AMT*AU*250~SVC*HC<99396*200*113.83**1~DTM*472*20130408~CAS*CO*45*86.17~REF*6R*94471570-1~AMT*B6*113.83~SVC*HC<82274*30*12.31**1~DTM*472*20130408~CAS*CO*45*17.69~REF*6R*94471570-3~AMT*B6*12.31~SVC*HC<99396*20*0***HC<81002*1~DTM*472*20130408~CAS*CO*97*20*1~REF*6R*94471570-2~LQ*HE*N19~SE*00*000000000~GE*0*00~IEA*0*000000000~"
  end

  def self.benchmark(times)
    time = Benchmark.realtime do
      EDI835::Parser.parse(test_string*times)
    end

    puts "#{time*1000} ms"
  end

  def self.to_hash
    edi = EDI835::Parser.parse(ChooChoo.test_string)
    isa = edi.isa_segment
    isa.to_hash
  end

  def self.isa
    edi = EDI835::Parser.parse(test_string)
    edi.isa_segment
  end

  def self.children(*names)
    edi = EDI835::Parser.parse(ChooChoo.test_string)
    isa = edi.isa_segment
    isa.children(*names)
  end

  def self.descendants(*names)
    edi = EDI835::Parser.parse(ChooChoo.test_string)
    isa = edi.isa_segment
    isa.descendants(*names)
  end
end

def file_loc(name)
  "./spec/support/#{name}"
end

def read_file(name)
  File.read(file_loc(name))
end

def edit_835_line(message, line, string)
  array = message.split('~')
  array[line -1] = string
  edi = EDI835::Parser.parse(array.join('~'))
  edi.isa_segment
end

