require 'spec_helper'

describe 'edi 835 traversal' do
  let!(:test_message) { 
    read_file("basic_835.txt")
  }

  let(:edi) { EDI835::Parser.parse(test_message)}
  let(:isa) { edi.isa_segments.first }

  it 'should be able traverse ISA' do
    expect(isa.parent).to be_nil
    expect(isa.ISA01).to eq("00")
    expect(isa.ISA02).to eq("          ")
    expect(isa.ISA03).to eq("00")
    expect(isa.ISA04).to eq("          ")
    expect(isa.ISA05).to eq("ZZ")
    expect(isa.ISA06).to eq("133052274      ")
    expect(isa.ISA07).to eq("ZZ")
    expect(isa.ISA08).to eq("264007676      ")
    expect(isa.ISA09).to eq("150105")
    expect(isa.ISA10).to eq("0451")
    expect(isa.ISA11).to eq("^")
    expect(isa.ISA12).to eq("00501")
    expect(isa.ISA13).to eq("000787134")
    expect(isa.ISA14).to eq("0")
    expect(isa.ISA15).to eq("P")
    expect(isa.ISA16).to eq("<")
  end

  it 'should be able traverse GS' do
    gs = isa.child!(:GS)
    expect(gs).to be_a(ChooChoo::GS)
    gs = isa.descendant!(:GS)
    expect(gs).to be_a(ChooChoo::GS)
    isa = gs.parent
    expect(isa).to be_a(ChooChoo::ISA)
    expect(gs.GS01).to eq("HP")
    expect(gs.GS02).to eq("133052274")
    expect(gs.GS03).to eq("264007676")
    expect(gs.GS04).to eq("20150105")
    expect(gs.GS05).to eq("0451")
    expect(gs.GS06).to eq("1")
    expect(gs.GS07).to eq("X")
    expect(gs.GS08).to eq("005010X221A1")
  end

  it "should be able to traverse ST" do
    st = isa.descendant!(:ST)
    expect(st.ST01).to eq("835")
    expect(st.ST02).to eq("0006")
  end

  it "should be able to traverse BPR" do
    bpr = isa.descendant!(:BPR)
    expect(bpr.BPR01).to eq("I")
    expect(bpr.BPR02).to eq("479.26")
    expect(bpr.BPR03).to eq("C")
    expect(bpr.BPR04).to eq("ACH")
    expect(bpr.BPR05).to eq("CCP")
    expect(bpr.BPR06).to eq("01")
    expect(bpr.BPR07).to eq("082000073")
    expect(bpr.BPR08).to eq("DA")
    expect(bpr.BPR09).to eq("004163086776")
    expect(bpr.BPR10).to eq("1710226428")
    expect(bpr.BPR11).to eq("USWM     ")
    expect(bpr.BPR12).to eq("01")
    expect(bpr.BPR13).to eq("082900872")
    expect(bpr.BPR14).to eq("DA")
    expect(bpr.BPR15).to eq("28452504")
    expect(bpr.BPR16).to eq("20150102")
  end

  it "should be able to traverse TRN" do
    trn = isa.descendant!(:TRN)
    expect(trn.TRN01).to eq("1")
    expect(trn.TRN02).to eq("WM0009430876")
    expect(trn.TRN03).to eq("1710226428")
    expect(trn.TRN04).to eq("USWM")
  end

  it "can search using where" do
    clps = isa.where(:CLP01, '095950951285')
    clp = clps.first
    expect(clp).to_not be_nil
    expect(clp.CLP01).to eq('095950951285')
  end

  it "can search using first" do
    clp = isa.first(:CLP01, '095950951285')
    expect(clp).to_not be_nil
    expect(clp.CLP01).to eq('095950951285')
  end

  it "can search using first!" do
    clp = isa.first!(:CLP01, '095950951285')
    expect(clp.CLP01).to eq('095950951285')
  end

  it "can search using exists?" do
    expect(isa.exists?(:CLP01, '095950951285')).to eq(true)
  end

  # it "can search using descendant!" do
    
  #   expect(isa.exists?(:CLP01, '095950951285')).to eq(true)
  # end
end