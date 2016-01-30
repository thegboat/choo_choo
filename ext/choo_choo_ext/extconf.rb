require 'mkmf'

$CFLAGS << ' -g'

create_makefile "choo_choo/choo_choo_ext"