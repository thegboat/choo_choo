# ChooChoo

A ruby EDI parser with C extensions.

## Installation

Add this line to your application's Gemfile:

```ruby
gem 'choo_choo'
```

And then execute:

    $ bundle

Or install it yourself as:

    $ gem install choo_choo

## Usage

ChooChoo provides a single sample 835 document.
Traversal can be via segment reference or through convenience interface.
The convenience interface uses the segment reference and casting provided by ChooChoo to represent a more Business Object model.

Segment reference example
```ruby
irb(main):004:0> doc = EDI835::Parser.parse(ChooChoo.sample)
=> #<EDI835::Document:0x007ffa735e27c8>
irb(main):005:0> isa = doc.isa
=> #<ChooChoo::ISA:0x007ffa735de8f8>
irb(main):006:0> isa.descendants(:CLP)
=> [#<ChooChoo::CLP:0x007ffa735d65b8>]
irb(main):009:0> clp = isa.descendant(:CLP)
=> #<ChooChoo::CLP:0x007ffa735d65b8>
irb(main):013:0> clp.CLP01
=> "9999999"
irb(main):012:0> clp.money(:CLP04)
=> #<BigDecimal:7f92c6a220c8,'0.0',9(18)>
irb(main):010:0> isa.where(:CLP01, "9999999")
=> [#<ChooChoo::CLP:0x007ffa735d65b8>]
irb(main):011:0> isa.exists?(:CLP01, "9999999")
=> true
```
Business Model example
```ruby
irb(main):004:0> doc = EDI835::Parser.parse(ChooChoo.sample)
=> #<EDI835::Document:0x007ffa735e27c8>
irb(main):002:0> remittance = doc.remittance
=> #<EDI835::Remittance:0x007f92c6a790a8>
irb(main):004:0> remittance.check_number
=> "0000010305"
irb(main):005:0> remittance.check_amount
=> #<BigDecimal:7f92c6a62c90,'0.0',9(18)>
irb(main):006:0> remittance.claim_payments
=> [#<EDI835::ClaimPayment:0x007f92c6a58ce0>]
irb(main):007:0> claim_payment = remittance.claim_payments.first
=> #<EDI835::ClaimPayment:0x007f92c6a58ce0>
irb(main):008:0> claim_payment.claim_number
=> "9999999"
irb(main):013:0> claim_payment.amount
=> #<BigDecimal:7f92c6a1b2c8,'0.0',9(18)>
```

## Development

To begin development, within the projects root:

    $ bundle
    $ bin/clear
    
To interact:

    $ bin/console
    
Xcode has been used to develop C extensions. See a contributor on how to set up an external build environment on Xcode if support is needed.

## Contributing

ChooChoo currently only provides support for 5010 EDI 835 documents, however its components are generic and extensible.  Feel free to provide validator/parsing instructions.

Bug reports and pull requests are welcome on GitHub at https://github.com/[USERNAME]/choo_choo.


## License

This gem is NOT open source.