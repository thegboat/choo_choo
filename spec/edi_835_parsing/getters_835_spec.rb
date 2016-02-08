require 'spec_helper'

describe 'edi 835 getters' do
  let!(:test_message) { 
    read_file("basic_835.txt")
  }

  let(:edi) { EDI835::Parser.parse(test_message)}
  let(:isa) { edi.isa_segment }
  let(:clp) { isa.first!(:CLP01, '095950951285') }
  let(:nm1) { clp.first!(:NM101, 'QC')}
  let(:dtm) { clp.first!(:DTM01, '050')}

  it 'should be able access via native properties' do
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

  it "should return native value with str" do
    expect(isa.ISA06).to eq("133052274      ")
  end

  it 'should be able to cast with int' do
    expect(isa.int(:ISA06)).to eq(133052274)
  end

  it 'should be able to cast with strip' do
    expect(isa.strip(:ISA06)).to eq("133052274")
  end

  it 'should be able to cast with upper' do
    expect(nm1.str(:NM103)).to eq("walker")
    expect(nm1.up(:NM103)).to eq("WALKER")
  end

  it 'should be able to cast with lower' do
    expect(isa.ISA15).to eq("P")
    expect(isa.lower(:ISA15)).to eq("p")
  end

  it 'should be able to cast with money' do
    expect(clp.str(:CLP05)).to eq('135.821')
    expect(clp.money(:CLP05)).to eq(BigDecimal('135.82'))
  end

  it 'should be able to cast with decimal' do
    expect(clp.str(:CLP05)).to eq('135.821')
    expect(clp.dec(:CLP05)).to eq(BigDecimal('135.821'))
  end

  it 'should be able to cast with date' do
    expect(dtm.int(:DTM02)).to eq(20141230)
    expect(dtm.date(:DTM02)).to eq(Date.parse('2014-12-30'))
  end

  it "should be able to cast from a child!" do
    expect(isa.str(:GS01)).to eq('HP')
  end

  it "asserts one and only one child when accessing non native method" do
    expect {clp.str!(:NM101) }.to raise_error(ChooChoo::MultipleChildrenFound)
  end


  it "asserts one child when accessing non native method" do
    expect {clp.str(:NM101) }.to raise_error(ChooChoo::MultipleChildrenFound)
  end
end