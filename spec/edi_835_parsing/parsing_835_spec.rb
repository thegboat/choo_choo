require 'spec_helper'

describe 'edi 835 parsing' do
  let!(:test_message) { 
    read_file("basic_835.txt")
  }

  let(:edi) { EDI835::Parser.parse(test_message)}
  let(:isa) { edi.isa_segment }

  it 'should parse without runtime error' do
    expect { edi }.to_not raise_error
  end

  it 'should yield a EDI835 instance' do
    expect(edi.is_a?(EDI835::Document)).to eq(true)
  end

  it 'should parse with file object' do
    file = File.open(file_loc("basic_835.txt"))
    from_file = nil
    expect { from_file = EDI835::Parser.parse(file) }.to_not raise_error
    from_file_isa = from_file.isa_segment
    expect(from_file_isa.is_a?(ChooChoo::ISA)).to eq(true)
  end
end

