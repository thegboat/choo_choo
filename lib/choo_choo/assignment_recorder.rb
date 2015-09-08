module ChooChoo
  class AssignmentRecorder

    def initialize(obj)
      @assignments = []
      @delayed_setters = []
      @target = obj
    end

    def method_missing(symbol, *args)
      if target_setter?(symbol)
        delayed_setters << [symbol, *args]
      else
        super
      end
    end

    def respond_to?(symbol)
      super || target_setter?(symbol)
    end

    def each_assignment(&blk)
      assignments.each(&blk)
    end

    def each_setter(&blk)
      delayed_setters.each(&blk)
    end

    def boolean(key, *args)
      assign(:boolean, key, *args)
    end
    alias :bool :boolean

    def integer(key, *args)
      assign(:integer, key, *args)
    end
    alias :int :integer

    def upper(key, *args)
      assign(:string, key, *add_options(args, apply: :upcase))
    end
    alias :up :upper

    def lower(key, *args)
      assign(:string, key, *add_options(args, apply: :downcase))
    end
    alias :low :lower

    def string(key, *args)
      assign(:string, key, *args)
    end
    alias :str :string
    alias :raw :string

    def date(key, *args)
      assign(:date, key, *args)
    end

    def money(key, *args)
      assign(:decimal, key, *add_options(args, precision: 2))
    end

    def decimal(key, *args)
      assign(:decimal, key, *args)
    end
    alias :dec :decimal

    def boolean_enum(key, var, *args)
      assign_enum(:boolean, key, var, *args)
    end
    alias :bool_enum :boolean_enum

    def integer_enum(key, var, *args)
      assign_enum(:integer, key, var, *args)
    end
    alias :int_enum :integer_enum

    def string_enum(key, var, *args)
      assign_enum(:string, key, var, *args)
    end
    alias :str_enum :string_enum

    def upper_enum(key, var, *args)
      assign_enum(:string, key, var, *add_options(args, apply: :upcase))
    end
    alias :up_enum :upper_enum

    def lower_enum(key, var, *args)
      assign_enum(:string, key, var, *add_options(args, apply: :downcase))
    end
    alias :low_enum :lower_enum

    def date_enum(key, var, *args)
      assign_enum(:date, key, var, *args)
    end

    def money_enum(key, var, *args)
      assign_enum(:decimal, key, var, *add_options(args, precision: 2))
    end

    def decimal_enum(key, var, *args)
      assign_enum(:decimal, key, var, *args)
    end
    alias :dec_enum :decimal_enum

    private

    attr_reader :target, :assignments, :delayed_setters

    def add_options(args, hash)
      options = extract_options(args)
      args.push(options.merge(hash))
    end

    def extract_options(args)
      args.last.is_a?(Hash) ? args.pop : {}
    end

    def target_setter?(symbol)
      symbol.to_s =~ /=$/ && (target.is_a?(Branch) || target.respond_to?(symbol))
    end

    def assign(assign_type, key, *args)
      args = args.dup
      options = extract_options(args)
      alt = args.pop

      [key].flatten.each do |meth|
        assignments << [assign_type, meth.to_sym, (alt || options[:alt] || meth).to_sym, options]
      end
    end

    def assign_enum(assign_type, key, var, *args)
      args = args.dup
      options = extract_options(args)
      alt = key
      limit = 1
      start = [options[:start].to_i, 1].max

      if args.empty?
        limit = [var.to_i, 1].max
      else
        alt = var
        limit = [args.first.to_i,1].max
      end

      start.upto(limit).each do |n|
        methn = key.to_s.gsub('XX', n.to_s)
        altn = alt.to_s.gsub('XX', n.to_s)
        assign(assign_type, methn, altn, options)
      end
    end
    
  end
end