require 'spec_helper'

describe 'edi 835 validation' do
  let!(:test_message) { 
    read_file("basic_835.txt")
  }

  it 'should have no errors' do
    edi = EDI835::Parser.parse(test_message)
    isa = edi.isa_segment
    expect(isa.doc.errors.empty?).to eq(true)
  end

  # it "handles ISA_SEGMENT_NOT_DETECTED_FIRST" do
  #   string = "HISA*00*          *00*          *ZZ*133052274      *ZZ*264007676      *150105*0451*^*00501*000787134*0*P*<"
  #   isa = edit_835_line(test_message, 1, string)
  #   expect(isa.doc.errors.include?("ISA_SEGMENT_NOT_DETECTED_FIRST")).to eq(true)
  # end

  it "handles INVALID_COMPONENT_SEPARATOR" do
    string = "ISA*00*          *00*          *ZZ*133052274      *ZZ*264007676      *150105*0451*^*00501*000787134*0*P*XX"
    isa = edit_835_line(test_message, 1, string)
    expect(isa.doc.errors.include?("INVALID_COMPONENT_SEPARATOR")).to eq(true)
  end

  it "handles INVALID_ISA_SEGMENT" do
    string = "ISA*00*          *00*          *ZZ*133052274      *ZZ*264007676      *150105*0451*^*00501*000787134*0*P*<~ISA*00"
    isa = edit_835_line(test_message, 1, string)
    expect(isa.doc.errors.include?("INVALID_ISA_SEGMENT")).to eq(true)
  end

  it "handles INVALID_BPR_SEGMENT" do
    string = "ISA*00*          *00*          *ZZ*133052274      *ZZ*264007676      *150105*0451*^*00501*000787134*0*P*<~BPR*00"
    isa = edit_835_line(test_message, 1, string)
    expect(isa.doc.errors.include?("INVALID_BPR_SEGMENT")).to eq(true)
  end

  it "handles INVALID_TRN_SEGMENT" do
    string = "ISA*00*          *00*          *ZZ*133052274      *ZZ*264007676      *150105*0451*^*00501*000787134*0*P*<~TRN*00"
    isa = edit_835_line(test_message, 1, string)
    expect(isa.doc.errors.include?("INVALID_TRN_SEGMENT")).to eq(true)
  end

  it "handles INVALID_CUR_SEGMENT" do
    string = "ISA*00*          *00*          *ZZ*133052274      *ZZ*264007676      *150105*0451*^*00501*000787134*0*P*<~CUR*00"
    isa = edit_835_line(test_message, 1, string)
    expect(isa.doc.errors.include?("INVALID_CUR_SEGMENT")).to eq(true)
  end

  it "handles INVALID_PER_SEGMENT" do
    string = "ISA*00*          *00*          *ZZ*133052274      *ZZ*264007676      *150105*0451*^*00501*000787134*0*P*<~PER*00"
    isa = edit_835_line(test_message, 1, string)
    expect(isa.doc.errors.include?("INVALID_PER_SEGMENT")).to eq(true)
  end

  it "handles INVALID_MIA_SEGMENT" do
    string = "ISA*00*          *00*          *ZZ*133052274      *ZZ*264007676      *150105*0451*^*00501*000787134*0*P*<~MIA*00"
    isa = edit_835_line(test_message, 1, string)
    expect(isa.doc.errors.include?("INVALID_MIA_SEGMENT")).to eq(true)
  end

  it "handles INVALID_CAS_SEGMENT" do
    string = "ISA*00*          *00*          *ZZ*133052274      *ZZ*264007676      *150105*0451*^*00501*000787134*0*P*<~CAS*00"
    isa = edit_835_line(test_message, 1, string)
    expect(isa.doc.errors.include?("INVALID_CAS_SEGMENT")).to eq(true)
  end

  it "handles INVALID_IEA_SEGMENT" do
    string = "ISA*00*          *00*          *ZZ*133052274      *ZZ*264007676      *150105*0451*^*00501*000787134*0*P*<~IEA*00"
    isa = edit_835_line(test_message, 1, string)
    expect(isa.doc.errors.include?("INVALID_IEA_SEGMENT")).to eq(true)
  end

  it "handles INVALID_QTY_SEGMENT" do
    string = "ISA*00*          *00*          *ZZ*133052274      *ZZ*264007676      *150105*0451*^*00501*000787134*0*P*<~QTY*00"
    isa = edit_835_line(test_message, 1, string)
    expect(isa.doc.errors.include?("INVALID_QTY_SEGMENT")).to eq(true)
  end

  it "handles INVALID_SVC_SEGMENT" do
    string = "ISA*00*          *00*          *ZZ*133052274      *ZZ*264007676      *150105*0451*^*00501*000787134*0*P*<~SVC*00"
    isa = edit_835_line(test_message, 1, string)
    expect(isa.doc.errors.include?("INVALID_SVC_SEGMENT")).to eq(true)
  end

  it "handles INVALID_CLP_SEGMENT" do
    string = "ISA*00*          *00*          *ZZ*133052274      *ZZ*264007676      *150105*0451*^*00501*000787134*0*P*<~CLP*00"
    isa = edit_835_line(test_message, 1, string)
    expect(isa.doc.errors.include?("INVALID_CLP_SEGMENT")).to eq(true)
  end

  it "handles INVALID_PLB_SEGMENT" do
    string = "ISA*00*          *00*          *ZZ*133052274      *ZZ*264007676      *150105*0451*^*00501*000787134*0*P*<~PLB*00"
    isa = edit_835_line(test_message, 1, string)
    expect(isa.doc.errors.include?("INVALID_PLB_SEGMENT")).to eq(true)
  end

  it "handles INVALID_TS3_SEGMENT" do
    string = "ISA*00*          *00*          *ZZ*133052274      *ZZ*264007676      *150105*0451*^*00501*000787134*0*P*<~TS3*00"
    isa = edit_835_line(test_message, 1, string)
    expect(isa.doc.errors.include?("INVALID_TS3_SEGMENT")).to eq(true)
  end

  it "handles INVALID_TS2_SEGMENT" do
    string = "ISA*00*          *00*          *ZZ*133052274      *ZZ*264007676      *150105*0451*^*00501*000787134*0*P*<~TS2*00"
    isa = edit_835_line(test_message, 1, string)
    expect(isa.doc.errors.include?("INVALID_TS2_SEGMENT")).to eq(true)
  end

  it "handles INVALID_MOA_SEGMENT" do
    string = "ISA*00*          *00*          *ZZ*133052274      *ZZ*264007676      *150105*0451*^*00501*000787134*0*P*<~MOA*00"
    isa = edit_835_line(test_message, 1, string)
    expect(isa.doc.errors.include?("INVALID_MOA_SEGMENT")).to eq(true)
  end

  it "handles INVALID_RDM_SEGMENT" do
    string = "ISA*00*          *00*          *ZZ*133052274      *ZZ*264007676      *150105*0451*^*00501*000787134*0*P*<~RDM*00"
    isa = edit_835_line(test_message, 1, string)
    expect(isa.doc.errors.include?("INVALID_RDM_SEGMENT")).to eq(true)
  end

  it "handles INVALID_LX_SEGMENT" do
    string = "ISA*00*          *00*          *ZZ*133052274      *ZZ*264007676      *150105*0451*^*00501*000787134*0*P*<~LX*00"
    isa = edit_835_line(test_message, 1, string)
    expect(isa.doc.errors.include?("INVALID_LX_SEGMENT")).to eq(true)
  end

  it "handles INVALID_LQ_SEGMENT" do
    string = "ISA*00*          *00*          *ZZ*133052274      *ZZ*264007676      *150105*0451*^*00501*000787134*0*P*<~LQ*00"
    isa = edit_835_line(test_message, 1, string)
    expect(isa.doc.errors.include?("INVALID_LQ_SEGMENT")).to eq(true)
  end

  it "handles INVALID_N1_SEGMENT" do
    string = "ISA*00*          *00*          *ZZ*133052274      *ZZ*264007676      *150105*0451*^*00501*000787134*0*P*<~N1*00"
    isa = edit_835_line(test_message, 1, string)
    expect(isa.doc.errors.include?("INVALID_N1_SEGMENT")).to eq(true)
  end

  it "handles INVALID_N3_SEGMENT" do
    string = "ISA*00*          *00*          *ZZ*133052274      *ZZ*264007676      *150105*0451*^*00501*000787134*0*P*<~N3*00"
    isa = edit_835_line(test_message, 1, string)
    expect(isa.doc.errors.include?("INVALID_N3_SEGMENT")).to eq(true)
  end

  it "handles INVALID_N4_SEGMENT" do
    string = "ISA*00*          *00*          *ZZ*133052274      *ZZ*264007676      *150105*0451*^*00501*000787134*0*P*<~N4*00"
    isa = edit_835_line(test_message, 1, string)
    expect(isa.doc.errors.include?("INVALID_N4_SEGMENT")).to eq(true)
  end

  it "handles INVALID_GS_SEGMENT" do
    string = "GS*HP*133052274*264007676*20150105*0451*1*X*005010X221A1~GS*00"
    isa = edit_835_line(test_message, 2, string)
    expect(isa.doc.errors.include?("INVALID_GS_SEGMENT")).to eq(true)
  end

  it "handles INVALID_ST_SEGMENT" do
    string = "ISA*00*          *00*          *ZZ*133052274      *ZZ*264007676      *150105*0451*^*00501*000787134*0*P*<~ST*00"
    isa = edit_835_line(test_message, 1, string)
    expect(isa.doc.errors.include?("INVALID_ST_SEGMENT")).to eq(true)
  end

  it "handles INVALID_GE_SEGMENT" do
    string = "ISA*00*          *00*          *ZZ*133052274      *ZZ*264007676      *150105*0451*^*00501*000787134*0*P*<~GE*00"
    isa = edit_835_line(test_message, 1, string)
    expect(isa.doc.errors.include?("INVALID_GE_SEGMENT")).to eq(true)
  end

  it "handles INVALID_SE_SEGMENT" do
    string = "ISA*00*          *00*          *ZZ*133052274      *ZZ*264007676      *150105*0451*^*00501*000787134*0*P*<~SE*00"
    isa = edit_835_line(test_message, 1, string)
    expect(isa.doc.errors.include?("INVALID_SE_SEGMENT")).to eq(true)
  end

  it "handles INVALID_NM1_SEGMENT" do
    string = "ISA*00*          *00*          *ZZ*133052274      *ZZ*264007676      *150105*0451*^*00501*000787134*0*P*<~NM1*00"
    isa = edit_835_line(test_message, 1, string)
    expect(isa.doc.errors.include?("INVALID_NM1_SEGMENT")).to eq(true)
  end

  it "handles WRONG_NUMBER_OF_ELEMENTS_FOR_ISA_SEGMENT" do
    string = "ISA*00*          *00*          *ZZ*133052274      *ZZ*264007676      *150105*0451*^*00501*000787134*0*P*<* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * "
    isa = edit_835_line(test_message, 1, string)
    expect(isa.doc.errors.include?("WRONG_NUMBER_OF_ELEMENTS_FOR_ISA_SEGMENT")).to eq(true)
  end

  it "handles WRONG_NUMBER_OF_ELEMENTS_FOR_BPR_SEGMENT" do
    string = "BPR*I*479.26*C*ACH*CCP*01*082000073*DA*004163086776*1710226428*USWM     *01*082900872*DA*28452504*20150102* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * "
    isa = edit_835_line(test_message, 4, string)
    expect(isa.doc.errors.include?("WRONG_NUMBER_OF_ELEMENTS_FOR_BPR_SEGMENT")).to eq(true)
  end

  it "handles WRONG_NUMBER_OF_ELEMENTS_FOR_TRN_SEGMENT" do
    string = "TRN*1*WM0009430876*1710226428*USWM* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * "
    isa = edit_835_line(test_message, 5, string)
    expect(isa.doc.errors.include?("WRONG_NUMBER_OF_ELEMENTS_FOR_TRN_SEGMENT")).to eq(true)
  end

  it "handles WRONG_NUMBER_OF_ELEMENTS_FOR_DTM_SEGMENT" do
    string = "DTM*405*20150102* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * "
    isa = edit_835_line(test_message, 7, string)
    expect(isa.doc.errors.include?("WRONG_NUMBER_OF_ELEMENTS_FOR_DTM_SEGMENT")).to eq(true)
  end

  it "handles WRONG_NUMBER_OF_ELEMENTS_FOR_PER_SEGMENT" do
    string = "PER*BL*EDI SERVICES*TE*5013782419*TE*8665823247*EM*EDI@ARKBLUECROSS.COM* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * "
    isa = edit_835_line(test_message, 12, string)
    expect(isa.doc.errors.include?("WRONG_NUMBER_OF_ELEMENTS_FOR_PER_SEGMENT")).to eq(true)
  end

  it "handles WRONG_NUMBER_OF_ELEMENTS_FOR_REF_SEGMENT" do
    string = "REF*F2*HCFA1500* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * "
    isa = edit_835_line(test_message, 6, string)
    expect(isa.doc.errors.include?("WRONG_NUMBER_OF_ELEMENTS_FOR_REF_SEGMENT")).to eq(true)
  end

  it "handles WRONG_NUMBER_OF_ELEMENTS_FOR_CAS_SEGMENT" do
    string = "CAS*PR*1*89.55* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * "
    isa = edit_835_line(test_message, 26, string)
    expect(isa.doc.errors.include?("WRONG_NUMBER_OF_ELEMENTS_FOR_CAS_SEGMENT")).to eq(true)
  end

  it "handles WRONG_NUMBER_OF_ELEMENTS_FOR_IEA_SEGMENT" do
    string = "IEA*0*000000000* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * "
    isa = edit_835_line(test_message, 266, string)
    expect(isa.doc.errors.include?("WRONG_NUMBER_OF_ELEMENTS_FOR_IEA_SEGMENT")).to eq(true)
  end

  it "handles WRONG_NUMBER_OF_ELEMENTS_FOR_SVC_SEGMENT" do
    string = "SVC*HC<99202<25*110*0* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * "
    isa = edit_835_line(test_message, 24, string)
    expect(isa.doc.errors.include?("WRONG_NUMBER_OF_ELEMENTS_FOR_SVC_SEGMENT")).to eq(true)
  end

  it "handles WRONG_NUMBER_OF_ELEMENTS_FOR_CLP_SEGMENT" do
    string = "CLP*095950951285*1*215*0*135.82*12*141230N11B94* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * "
    isa = edit_835_line(test_message, 19, string)
    expect(isa.doc.errors.include?("WRONG_NUMBER_OF_ELEMENTS_FOR_CLP_SEGMENT")).to eq(true)
  end

  it "handles WRONG_NUMBER_OF_ELEMENTS_FOR_LX_SEGMENT" do
    string = "LX*1* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * "
    isa = edit_835_line(test_message, 18, string)
    expect(isa.doc.errors.include?("WRONG_NUMBER_OF_ELEMENTS_FOR_LX_SEGMENT")).to eq(true)
  end

  it "handles WRONG_NUMBER_OF_ELEMENTS_FOR_LQ_SEGMENT" do
    string = "LQ*HE*N130* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * "
    isa = edit_835_line(test_message, 111, string)
    expect(isa.doc.errors.include?("WRONG_NUMBER_OF_ELEMENTS_FOR_LQ_SEGMENT")).to eq(true)
  end

  it "handles WRONG_NUMBER_OF_ELEMENTS_FOR_N1_SEGMENT" do
    string = "N1*PR*ABCBS DBA BLUEADVANTAGE ADMIN OF AR* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * "
    isa = edit_835_line(test_message, 8, string)
    expect(isa.doc.errors.include?("WRONG_NUMBER_OF_ELEMENTS_FOR_N1_SEGMENT")).to eq(true)
  end

  it "handles WRONG_NUMBER_OF_ELEMENTS_FOR_N3_SEGMENT" do
    string = "N3*P.O. BOX 1460* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * "
    isa = edit_835_line(test_message, 9, string)
    expect(isa.doc.errors.include?("WRONG_NUMBER_OF_ELEMENTS_FOR_N3_SEGMENT")).to eq(true)
  end

  it "handles WRONG_NUMBER_OF_ELEMENTS_FOR_N4_SEGMENT" do
    string = "N4*LITTLE ROCK*AR*72203* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * "
    isa = edit_835_line(test_message, 10, string)
    expect(isa.doc.errors.include?("WRONG_NUMBER_OF_ELEMENTS_FOR_N4_SEGMENT")).to eq(true)
  end

  it "handles WRONG_NUMBER_OF_ELEMENTS_FOR_GS_SEGMENT" do
    string = "GS*HP*133052274*264007676*20150105*0451*1*X*005010X221A1* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * "
    isa = edit_835_line(test_message, 2, string)
    expect(isa.doc.errors.include?("WRONG_NUMBER_OF_ELEMENTS_FOR_GS_SEGMENT")).to eq(true)
  end

  it "handles WRONG_NUMBER_OF_ELEMENTS_FOR_ST_SEGMENT" do
    string = "ST*835*0006* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * "
    isa = edit_835_line(test_message, 3, string)
    expect(isa.doc.errors.include?("WRONG_NUMBER_OF_ELEMENTS_FOR_ST_SEGMENT")).to eq(true)
  end

  it "handles WRONG_NUMBER_OF_ELEMENTS_FOR_GE_SEGMENT" do
    string = "GE*0*00* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * "
    isa = edit_835_line(test_message, 265, string)
    expect(isa.doc.errors.include?("WRONG_NUMBER_OF_ELEMENTS_FOR_GE_SEGMENT")).to eq(true)
  end

  it "handles WRONG_NUMBER_OF_ELEMENTS_FOR_SE_SEGMENT" do
    string = "SE*00*000000000* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * "
    isa = edit_835_line(test_message, 264, string)
    expect(isa.doc.errors.include?("WRONG_NUMBER_OF_ELEMENTS_FOR_SE_SEGMENT")).to eq(true)
  end

  it "handles WRONG_NUMBER_OF_ELEMENTS_FOR_NM1_SEGMENT" do
    string = "NM1*QC*1*WALKER*LANDON*M***MI*WMB09180949W* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * "
    isa = edit_835_line(test_message, 20, string)
    expect(isa.doc.errors.include?("WRONG_NUMBER_OF_ELEMENTS_FOR_NM1_SEGMENT")).to eq(true)
  end

  it "handles WRONG_NUMBER_OF_ELEMENTS_FOR_AMT_SEGMENT" do
    string = "AMT*B6*89.55* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * "
    isa = edit_835_line(test_message, 31, string)
    expect(isa.doc.errors.include?("WRONG_NUMBER_OF_ELEMENTS_FOR_AMT_SEGMENT")).to eq(true)
  end
end