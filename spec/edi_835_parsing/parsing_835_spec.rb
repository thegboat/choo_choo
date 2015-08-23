require 'spec_helper'

describe 'edi 835 parsing' do
  let!(:test_message) { 
    read_file("basic_835.txt")
  }

  let(:edi) { ChooChoo::Parser.parse_835(test_message)}
  let(:isa) { edi.isa_segments.first }

  it 'should parse without runtime error' do
    expect { edi }.to_not raise_error
  end

  it 'should yield a EDI835 instance' do
    expect(edi.is_a?(ChooChoo::EDI835)).to eq(true)
  end

  it 'should have only corrent number of isa_segments' do
    expect(edi.isa_segments.length).to eq(1)
    expect(isa.is_a?(ChooChoo::InterchangeLoop)).to eq(true)
  end

  it 'should parse with file object' do
    file = File.open(file_loc("basic_835.txt"))
    from_file = nil
    expect { from_file = ChooChoo::Parser.parse_835(file) }.to_not raise_error
    expect(from_file.isa_segments.length).to eq(1)
    from_file_isa = from_file.isa_segments.first
    expect(from_file_isa.is_a?(ChooChoo::InterchangeLoop)).to eq(true)
  end
end

