require 'spec_helper'

describe 'edi 835 traversal' do
  let!(:test_message) { 
    read_file("basic_835.txt")
  }

  let(:edi) { EDI835::Parser.parse(test_message)}
  let(:isa) { edi.isa_segments.first }

  it "ISA segment has no parent" do
    expect(isa.parent).to be_nil
  end

  it "can search with children method" do
    segments = isa.children
    expect(segments.length).to eq(2)
  end

  it "can search with children method and arguments" do
    segments = isa.children(:GS)
    expect(segments.length).to eq(1)
    expect(segments.first).to be_a(ChooChoo::GS)
  end

  it "can search using descendant" do
    segment = isa.descendant(:CLP)
    expect(segment).to be_a(ChooChoo::CLP)
  end

  it "can search using descendant!" do
    segment = isa.descendant!(:GS)
    expect(segment).to be_a(ChooChoo::GS)
  end

  it "asserts there is one and only one with descendant!" do
    expect { isa.descendant!(:CLP) }.to raise_error(ChooChoo::AssertedValueNotFound)
  end

  it "can search using descendants" do
    segments = isa.descendants(:CLP)
    expect(segments.all? {|clp| clp.is_a?(ChooChoo::CLP) }).to eq(true)
    expect(segments.length).to eq(10)
  end

  it "can search with child" do
    segment = isa.child(:GS)
    expect(segment).to be_a(ChooChoo::GS)
  end

  it "can search with child!" do
    segment = isa.child!(:GS)
    expect(segment).to be_a(ChooChoo::GS)
  end

  it "asserts there is one and only one with child!" do
    clp = isa.descendant(:CLP)
    parent = clp.parent
    expect { parent.child!(:CLP) }.to raise_error(ChooChoo::AssertedValueNotFound)
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

  it "asserts there is one and only one with first!" do
    clp = isa.descendant(:CLP)
    parent = clp.parent
    expect { parent.first!(:CLP02, '1') }.to raise_error(ChooChoo::AssertedValueNotFound)
  end

  it "can search using exists?" do
    expect(isa.exists?(:CLP01, '095950951285')).to eq(true)
  end
end