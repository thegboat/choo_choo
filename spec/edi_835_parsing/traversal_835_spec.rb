require 'spec_helper'

describe 'edi 835 traversal' do
  let!(:test_message) { 
    read_file("basic_835.txt")
  }
end