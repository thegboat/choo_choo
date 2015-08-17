$LOAD_PATH.unshift File.expand_path('../../lib', __FILE__)
require 'choo_choo'
require 'benchmark'
require 'pry'
require 'pry-byebug'


module ChooChoo
  def self.test_string
    @test_string ||= "ISA*00*          *00*          *ZZ*133052274      *ZZ*264007676      *150105*0451*^*00501*000787134*0*P*<~GS*HP*133052274*264007676*20150105*0451*1*X*005010X221A1~ST*835*0006~BPR*I*479.26*C*ACH*CCP*01*082000073*DA*004163086776*1710226428*USWM     *01*082900872*DA*28452504*20150102~TRN*1*WM0009430876*1710226428*USWM~REF*F2*HCFA1500~DTM*405*20150102~N1*PR*ABCBS DBA BLUEADVANTAGE ADMIN OF AR~N3*P.O. BOX 1460~N4*LITTLE ROCK*AR*72203~REF*2U*SB520~PER*BL*EDI SERVICES*TE*5013782419*TE*8665823247*EM*EDI@ARKBLUECROSS.COM~N1*PE*OZARK URGENT CARE*XX*1487904009~N3*1706 SE WALTON BLVD STE 4~N4*BENTONVILLE*AR*72712~REF*PQ*5G896~REF*TJ*263285850~LX*1~CLP*095950951285*1*215*0*135.82*12*141230N11B94~NM1*QC*1*WALKER*LANDON*M***MI*WMB09180949W~NM1*74*1**LANDON M****C*WMB09180949W00~NM1*82*1*LAFFERTY MD*WARREN SCOTT****XX*1639118391~DTM*050*20141230~SVC*HC<99202<25*110*0~DTM*472*20141218~CAS*PR*1*89.55~CAS*CO*45*20.45~REF*LU*11~REF*6R*095950951285-1~REF*1A*5K202~AMT*B6*89.55~SVC*HC<96372*45*0~DTM*472*20141218~CAS*PR*1*32.09~CAS*CO*45*12.91~REF*LU*11~REF*6R*095950951285-2~REF*1A*5K202~AMT*B6*32.09~SVC*HC<J1100*20*0**8~DTM*472*20141218~CAS*PR*1*1.2~CAS*CO*45*18.8~REF*LU*11~REF*6R*095950951285-3~REF*1A*5K202~AMT*B6*1.2~SVC*HC<J1040*40*0**2~DTM*472*20141218~CAS*PR*1*12.98~CAS*CO*45*27.02~REF*LU*11~REF*6R*095950951285-4~REF*1A*5K202~AMT*B6*12.98~CLP*044589181013*1*135*84.22*21.05*12*141230N11BA2~NM1*QC*1*JONES*REESE*R***MI*WMW03619481W~NM1*IL*1*JONES*JENNIFER L*L***MI*WMW03619481W00~NM1*74*1**REESE R****C*WMW03619481W01~NM1*82*1*LAFFERTY MD*WARREN SCOTT****XX*1639118391~DTM*050*20141230~SVC*HC<99213*110*70.62~DTM*472*20141216~CAS*PR*2*17.65~CAS*CO*45*21.73~REF*LU*11~REF*6R*044589181013-1~REF*1A*5K202~AMT*B6*88.27~SVC*HC<87804<QW*25*13.6~DTM*472*20141216~CAS*PR*2*3.4~CAS*CO*45*8~REF*LU*11~REF*6R*044589181013-2~REF*1A*5K202~AMT*B6*17~CLP*044864486897*1*110*70.62*17.65*12*141230N11BA9~NM1*QC*1*HERRERA*ANA*A***MI*WMW07088610W~NM1*74*1**ANA A****C*WMW07088610W00~NM1*82*1*LAFFERTY MD*WARREN SCOTT****XX*1639118391~DTM*050*20141230~SVC*HC<99213*110*70.62~DTM*472*20141223~CAS*PR*2*17.65~CAS*CO*45*21.73~REF*LU*11~REF*6R*044864486897-1~REF*1A*5K202~AMT*B6*88.27~CLP*026325902315*1*292*104.6*163.15*12*141230N11BB5~NM1*QC*1*GILLEAN*LINDSEY*R***MI*WMW03735082W~NM1*74*1**LINDSEY R****C*WMW03735082W00~NM1*82*1*LAFFERTY MD*WARREN SCOTT****XX*1639118391~DTM*050*20141230~SVC*HC<99214<25*155*104.6~DTM*472*20141219~CAS*PR*2*26.15~CAS*CO*45*24.25~REF*LU*11~REF*6R*026325902315-1~REF*1A*5K202~AMT*B6*130.75~SVC*HC<84443*42*0~DTM*472*20141219~CAS*PR*204*42~REF*LU*11~REF*6R*026325902315-5~REF*1A*5K202~AMT*B6*35.21~LQ*HE*N130~SVC*HC<84481*35*0~DTM*472*20141219~CAS*PR*204*35~REF*LU*11~REF*6R*026325902315-4~REF*1A*5K202~AMT*B6*35~LQ*HE*N130~SVC*HC<84439*25*0~DTM*472*20141219~CAS*PR*204*25~REF*LU*11~REF*6R*026325902315-3~REF*1A*5K202~AMT*B6*18.9~LQ*HE*N130~SVC*HC<84480*35*0~DTM*472*20141219~CAS*PR*204*35~REF*LU*11~REF*6R*026325902315-2~REF*1A*5K202~AMT*B6*29.72~LQ*HE*N130~CLP*074055120112*1*110*89.55**12*141230N11BB8~NM1*QC*1*ESTES*MICHAEL*R***MI*WMW10317498W~NM1*74*1**MICHAEL R****C*WMW10317498W00~NM1*82*1*LAFFERTY MD*WARREN SCOTT****XX*1639118391~DTM*050*20141230~SVC*HC<99202*110*89.55~DTM*472*20141223~CAS*PR*1*89.55**187*-89.55~CAS*CO*45*20.45~REF*LU*11~REF*6R*074055120112-1~REF*1A*5K202~AMT*B6*89.55~CLP*057930662044*1*110*88.27**12*141230N11BC1~NM1*QC*1*CRAINSHAW*GARY*W***MI*WMW07011012W~NM1*74*1**GARY W****C*WMW07011012W00~NM1*82*1*LAFFERTY MD*WARREN SCOTT****XX*1639118391~DTM*050*20141230~SVC*HC<99213*110*88.27~DTM*472*20141223~CAS*PR*1*88.27**187*-88.27~CAS*CO*45*21.73~REF*LU*11~REF*6R*057930662044-1~REF*1A*5K202~AMT*B6*88.27~CLP*073277164247*1*217*0*173.72*12*141230N11BC3~NM1*QC*1*COOPER*JAMES****MI*WMW11103905W03~NM1*IL*1*COOPER*JENNIFER****MI*WMW11103905W00~NM1*74*1**JAMES B*B~NM1*82*1*LAFFERTY MD*WARREN SCOTT****XX*1639118391~DTM*050*20141230~SVC*HC<99213<25*110*0~DTM*472*20141218~CAS*PR*1*88.27~CAS*CO*45*21.73~REF*LU*11~REF*6R*073277164247-1~REF*1A*5K202~AMT*B6*88.27~SVC*HC<83036*25*0~DTM*472*20141218~CAS*PR*1*20.34~CAS*CO*45*4.66~REF*LU*11~REF*6R*073277164247-3~REF*1A*5K202~AMT*B6*20.34~SVC*HC<80061*32*0~DTM*472*20141218~CAS*PR*1*26.66~CAS*CO*45*5.34~REF*LU*11~REF*6R*073277164247-2~REF*1A*5K202~AMT*B6*26.66~SVC*HC<85025*25*0~DTM*472*20141218~CAS*PR*1*16.29~CAS*CO*45*8.71~REF*LU*11~REF*6R*073277164247-4~REF*1A*5K202~AMT*B6*16.29~SVC*HC<80053*25*0~DTM*472*20141218~CAS*PR*1*22.16~CAS*CO*45*2.84~REF*LU*11~REF*6R*073277164247-5~REF*1A*5K202~AMT*B6*22.16~CLP*027228951664*1*135*0*106.55*12*141230N11BC7~NM1*QC*1*BRASSELL*REGINA*L***MI*WMW04628629W~NM1*IL*1*BRASSELL*BRETT H*H***MI*WMW04628629W00~NM1*74*1**REGINA L****C*WMW04628629W01~NM1*82*1*LAFFERTY MD*WARREN SCOTT****XX*1639118391~DTM*050*20141230~SVC*HC<99202<25*110*0~DTM*472*20141223~CAS*PR*1*89.55~CAS*CO*45*20.45~REF*LU*11~REF*6R*027228951664-1~REF*1A*5K202~AMT*B6*89.55~SVC*HC<87804*25*0~DTM*472*20141223~CAS*PR*1*17~CAS*CO*45*8~REF*LU*11~REF*6R*027228951664-2~REF*1A*5K202~AMT*B6*17~CLP*049034371804*1*110*0*89.55*12*141231N10YR9~NM1*QC*1*SCURLOCK*WENDELL*M***MI*WMW13461323W~NM1*74*1**WENDELL M****C*WMW13461323W00~NM1*82*1*LAFFERTY MD*WARREN SCOTT****XX*1639118391~DTM*050*20141231~SVC*HC<99202*110*0~DTM*472*20141229~CAS*PR*1*89.55~CAS*CO*45*20.45~REF*LU*11~REF*6R*049034371804-1~REF*1A*5K202~AMT*B6*89.55~CLP*012720553440*1*135*42*63.27*12*141231N10YS0~NM1*QC*1*MILLER*SUZEANNA*R***MI*WMW14919669W~NM1*74*1******C*WMW14919669W00~NM1*82*1*LAFFERTY MD*WARREN SCOTT****XX*1639118391~DTM*050*20141231~SVC*HC<99213<25*110*42~DTM*472*20141219~CAS*PR*1*88.27**187*-42~CAS*CO*45*21.73~REF*LU*11~REF*6R*012720553440-1~REF*1A*5K202~AMT*B6*88.27~SVC*HC<87804<QW*25*0~DTM*472*20141219~CAS*PR*1*17~CAS*CO*45*8~REF*LU*11~REF*6R*012720553440-2~REF*1A*5K202~AMT*B6*17~SE*00*000000000~GE*0*00~IEA*0*000000000";
  end

  def self.test_string2
    @test_string2 ||= "ISA*00*          *00*          *ZZ*133052274      *ZZ*264007676      *130415*0246*^*00501*000118103*0*P*<~GS*HP*133052274*264007676*20130415*0246*1*X*005010X221A1~ST*835*0059~BPR*I*551.59*C*ACH*CCP*01*011900445*DA*0000009046*1066033492**01*111000614*DA*238721164365*20130419~TRN*1*813105550002225*1066033492*60054~REF*EV*133052274~DTM*405*20130415~N1*PR*AETNA~N3*151 FARMINGTON AVENUE~N4*HARTFORD*CT*06156~REF*2U*60054~PER*BL*Provider Service~N1*PE*CONTEMPORARY OB/GYN OF GRAPEVINE*XX*1962408062~N3*1600 W COLLEGE ST STE 340~N4*GRAPEVINE*TX*760513577~REF*PQ*788692840~REF*TJ*752710490~LX*1~TS3*1962408062*11*20131231*5*1340~CLP*83238113*1*125*49.77*25*13*EAJK6NHT30000*11*1~NM1*QC*1*ALLISON LUMPKIN*JULIA*M~NM1*IL*1*LUMPKIN*RUSSELL****MI*821189992~NM1*74*1***L**JR*C*W173066921~NM1*82*1*NEW*TROY*G***XX*1962408062~REF*1L*0326475-010-00190-AA~REF*CE*Aetna Choice  POS II NET 00338~DTM*232*20130405~DTM*233*20130405~DTM*050*20130408~PER*CX**TE*8886323862~AMT*AU*125~SVC*HC<99213*125*49.77**1~DTM*472*20130405~CAS*CO*45*50.23~CAS*PR*3*25~REF*6R*83238113-1~AMT*B6*74.77~CLP*96385257*1*175*104.25**13*EJAA6M14Q0000*11*1~NM1*QC*1*DEVINE*JILLIAN****MI*W181960503~NM1*82*1*NEW*TROY*G***XX*1962408062~REF*1L*0878752-036-00014-GB~REF*CE*Aetna Choice  POS II NET 03859~DTM*232*20130404~DTM*233*20130404~DTM*050*20130405~PER*CX**TE*8886323862~AMT*AU*175~SVC*HC<99395*175*104.25**1~DTM*472*20130404~CAS*CO*45*70.75~REF*6R*96385257-1~AMT*B6*104.25~CLP*43691534*1*575*152.09**13*EJFA6M2C30000*21*1~NM1*QC*1*LE*DUYEN~NM1*IL*1*NGUYEN*DZUNG****MI*W188654143~NM1*82*1*NEW*TROY*G***XX*1962408062~REF*1L*0878752-034-00023-ED~REF*CE*Aetna HealthFund  Aetna Choice  POS II NET 03859~DTM*232*20130404~DTM*233*20130404~DTM*050*20130405~PER*CX**TE*8886323862~AMT*AU*575~SVC*HC<59514<80*575*152.09**1~DTM*472*20130404~CAS*CO*45*422.91~REF*6R*43691534-1~AMT*B6*152.09~CLP*78288305*1*215*119.34**13*EXAA52M880000*11*1~NM1*QC*1*OSCAR*LINDA~NM1*IL*1*CLEMONS*CHRISTOPHER****MI*W104545356~NM1*74*1*CLEMENT**J~NM1*82*1*NEW*TROY*G***XX*1962408062~REF*1L*0724616-015-00001-UA~REF*CE*Aetna Choice  POS II NET 00338~DTM*232*20130403~DTM*233*20130403~DTM*050*20130404~PER*CX**TE*8886323862~AMT*AU*215~SVC*HC<99385*215*119.34**1~DTM*472*20130403~CAS*CO*45*95.66~REF*6R*78288305-1~AMT*B6*119.34~CLP*94471570*1*250*126.14**13*E8YZ55T640000*11*1~NM1*QC*1*CHOI*JIHEE****MI*W111098904~NM1*82*1*NEW*TROY*G***XX*1962408062~REF*1L*0878752-034-00012-EB~REF*CE*Aetna HealthFund  Aetna Choice  POS II NET 03859~DTM*232*20130408~DTM*233*20130408~DTM*050*20130409~PER*CX**TE*8886323862~AMT*AU*250~SVC*HC<99396*200*113.83**1~DTM*472*20130408~CAS*CO*45*86.17~REF*6R*94471570-1~AMT*B6*113.83~SVC*HC<82274*30*12.31**1~DTM*472*20130408~CAS*CO*45*17.69~REF*6R*94471570-3~AMT*B6*12.31~SVC*HC<99396*20*0***HC<81002*1~DTM*472*20130408~CAS*CO*97*20*1~REF*6R*94471570-2~LQ*HE*N19~SE*00*000000000~GE*0*00~IEA*0*000000000~"
  end

  def self.benchmark(times)
    time = Benchmark.realtime do
      ChooChoo::Parser.parse_835(test_string*times)
    end

    puts "#{time*1000} ms"
  end

  def self.to_hash
    edi = ChooChoo::Parser.parse_835(test_string)
    isa = edi.isa_segments.first
    isa.to_hash
  end

  def self.children(*names)
    edi = ChooChoo::Parser.parse_835(ChooChoo.test_string)
    isa = edi.isa_segments.first
    isa.children(*names)
  end

  def self.descendants(*names)
    edi = ChooChoo::Parser.parse_835(ChooChoo.test_string)
    isa = edi.isa_segments.first
    isa.descendants(*names)
  end
end


