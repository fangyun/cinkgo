ifeq ($(shell uname -o), Cygwin)
	INCLUDES=-I. -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include
else
	INCLUDES=-I.. -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include
endif

OBJS := transposition_table.o mc_runnable.o simple_search_node.o time_descender.o tree_updater.o copyable_struct.o

all: lib.a
lib.a: $(OBJS)


-include ../Makefile.lib
