# Makefile for trampoline

#### Start of system configuration section. ####

HOST = x86_64-apple-darwin10.4.0
CPU = x86_64
OS = darwin10.4.0

# Directories used by "make":
srcdir = .

# Directories used by "make install":
prefix = /usr/local
local_prefix = /usr/local
exec_prefix = ${prefix}
libdir = ${exec_prefix}/lib
includedir = ${prefix}/include
mandir = ${datarootdir}/man
datadir = ${datarootdir}
datarootdir = ${prefix}/share
htmldir = $(datadir)/html

# Programs used by "make":
CC = /usr/bin/cc
CFLAGS = -O3 -w -pipe
CPP = /usr/bin/cc -E
INCLUDES = -I. -I$(srcdir)
ASPFLAGS = `if test true = true; then echo '-DASM_UNDERSCORE'; fi`
LIBTOOL = $(SHELL) $(top_builddir)/libtool
LIBTOOL_COMPILE = $(LIBTOOL) --mode=compile
LIBTOOL_LINK = $(LIBTOOL) --mode=link
LIBTOOL_INSTALL = $(LIBTOOL) --mode=install
LIBTOOL_UNINSTALL = $(LIBTOOL) --mode=uninstall
AR = ar
AR_FLAGS = rc
RANLIB = ranlib
RM = rm -f
LN_S = ln -s


# Programs used by "make install":
INSTALL = /usr/bin/install -c
INSTALL_PROGRAM = ${INSTALL}
INSTALL_DATA = ${INSTALL} -m 644

#### End of system configuration section. ####

SHELL = /bin/sh

# Needed by $(LIBTOOL).
top_builddir = .

OBJECTS = trampoline.lo 

all : $(OBJECTS) libtrampoline.la trampoline_r.h $(srcdir)/trampoline_r.3 $(srcdir)/trampoline_r.html

trampoline_r.h : $(srcdir)/trampoline_r.h.in
	-$(LN_S) $(srcdir)/trampoline_r.h.in trampoline_r.h

trampoline.lo : $(srcdir)/trampoline.c trampoline_r.h
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS) $(INCLUDES) -c $(srcdir)/trampoline.c

tramp-hppa.lo : $(srcdir)/tramp-hppa.s
	$(LIBTOOL_COMPILE) $(CC) -x none -c $(srcdir)/tramp-hppa.s

tramp-s390.lo : $(srcdir)/tramp-s390.s
	$(LIBTOOL_COMPILE) $(CC) -x none -c $(srcdir)/tramp-s390.s

tramp-powerpc.lo : tramp-powerpc.s
	$(LIBTOOL_COMPILE) $(CC) -x none -c tramp-powerpc.s

tramp-powerpc.s : $(srcdir)/tramp-powerpc.old.S $(srcdir)/tramp-powerpc.new.S
	case "$(OS)" in \
	  aix3*) syntax=old;; \
	  *) syntax=new;; \
	esac; \
	$(CPP) $(srcdir)/tramp-powerpc.$${syntax}.S > tramp-powerpc.s

tramp-powerpc64.lo : tramp-powerpc64.s
	$(LIBTOOL_COMPILE) $(CC) -x none -c tramp-powerpc64.s

tramp-powerpc64.s : $(srcdir)/tramp-powerpc64.new.S
	$(CPP) $(srcdir)/tramp-powerpc64.new.S > tramp-powerpc64.s

tramp-ia64.lo : $(srcdir)/tramp-ia64.s
	$(LIBTOOL_COMPILE) $(CC) -x none -c $(srcdir)/tramp-ia64.s

cache-sparc.lo : cache-sparc.s
	$(LIBTOOL_COMPILE) $(CC) -x none -c cache-sparc.s

cache-sparc.s : $(srcdir)/cache-sparc.S
	$(CPP) $(ASPFLAGS) $(srcdir)/cache-sparc.S | grep -v '^ *#line' | grep -v '^#' | sed -e 's,% ,%,g' -e 's,//.*$$,,' -e 's,\$$,#,g' > cache-sparc.s

cache-sparc64.lo : cache-sparc64.s
	$(LIBTOOL_COMPILE) $(CC) -x none -c cache-sparc64.s

cache-sparc64.s : $(srcdir)/cache-sparc.S
	$(CPP) $(ASPFLAGS) $(srcdir)/cache-sparc.S | grep -v '^ *#line' | grep -v '^#' | sed -e 's,% ,%,g' -e 's,//.*$$,,' -e 's,\$$,#,g' > cache-sparc64.s

cache-alpha.lo : $(srcdir)/cache-alpha.s
	$(LIBTOOL_COMPILE) $(CC) -x none -c $(srcdir)/cache-alpha.s

cache-arm.lo : $(srcdir)/cache-arm.s
	$(LIBTOOL_COMPILE) $(CC) -x none -c $(srcdir)/cache-arm.s

cache-armel.lo : $(srcdir)/cache-armel.s
	$(LIBTOOL_COMPILE) $(CC) -x none -c $(srcdir)/cache-armel.s

cache-hppa.lo : $(srcdir)/cache-hppa.s
	$(LIBTOOL_COMPILE) $(CC) -x none -c $(srcdir)/cache-hppa.s

cache-powerpc.lo : $(srcdir)/cache-powerpc-sysv4.s $(srcdir)/cache-powerpc-macos.s
	case "$(OS)" in \
	  macos* | darwin*) syntax=macos;; \
	  *) syntax=sysv4;; \
	esac; \
	$(LIBTOOL_COMPILE) $(CC) -x none -c $(srcdir)/cache-powerpc-$${syntax}.s ; \
	cp cache-powerpc-$${syntax}.lo cache-powerpc.lo ; rm -f cache-powerpc-$${syntax}.lo ; \
	if test -f cache-powerpc-$${syntax}.o; then cp cache-powerpc-$${syntax}.o cache-powerpc.o; fi
# Note that cache-powerpc-${syntax}.o is kept in place, because in some cases
# cache-powerpc-${syntax}.lo contains a symbolic reference to it and therefore
# libtool may want to access it.

cache-convex.lo : $(srcdir)/cache-convex.s
	$(LIBTOOL_COMPILE) $(CC) -x none -c $(srcdir)/cache-convex.s

libtrampoline.la : $(OBJECTS)
	$(LIBTOOL_LINK) $(CC) -o libtrampoline.la -rpath $(libdir) $(OBJECTS)

# Installs the library and include files only. Typically called with only
# $(libdir) and $(includedir) - don't use $(prefix) and $(exec_prefix) here.
install-lib : all force
	mkdir -p $(includedir)
	$(INSTALL_DATA) trampoline_r.h $(includedir)/trampoline_r.h

install : all force
	mkdir -p $(DESTDIR)$(prefix)
	mkdir -p $(DESTDIR)$(exec_prefix)
#	mkdir -p $(DESTDIR)$(libdir)
#	$(LIBTOOL_INSTALL) $(INSTALL_DATA) libtrampoline.la $(DESTDIR)$(libdir)/libtrampoline.la
	mkdir -p $(DESTDIR)$(includedir)
	$(INSTALL_DATA) trampoline_r.h $(DESTDIR)$(includedir)/trampoline_r.h
	mkdir -p $(DESTDIR)$(mandir)
	mkdir -p $(DESTDIR)$(mandir)/man3
	$(INSTALL_DATA) $(srcdir)/trampoline_r.3 $(DESTDIR)$(mandir)/man3/trampoline_r.3
	mkdir -p $(DESTDIR)$(datadir)
	mkdir -p $(DESTDIR)$(htmldir)
	$(INSTALL_DATA) $(srcdir)/trampoline_r.html $(DESTDIR)$(htmldir)/trampoline_r.html

installdirs : force
	mkdir -p $(DESTDIR)$(prefix)
	mkdir -p $(DESTDIR)$(exec_prefix)
#	mkdir -p $(DESTDIR)$(libdir)
	mkdir -p $(DESTDIR)$(includedir)
	mkdir -p $(DESTDIR)$(mandir)
	mkdir -p $(DESTDIR)$(mandir)/man3
	mkdir -p $(DESTDIR)$(datadir)
	mkdir -p $(DESTDIR)$(htmldir)

uninstall : force
#	$(LIBTOOL_UNINSTALL) $(RM) $(DESTDIR)$(libdir)/libtrampoline.la
	$(RM) $(DESTDIR)$(includedir)/trampoline_r.h
	$(RM) $(DESTDIR)$(mandir)/man3/trampoline_r.3
	$(RM) $(DESTDIR)$(htmldir)/trampoline_r.html

test1.o : $(srcdir)/test1.c trampoline_r.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $(srcdir)/test1.c

test1 : test1.o $(OBJECTS)
	$(LIBTOOL_LINK) $(CC) $(CFLAGS) -x none test1.o $(OBJECTS) -o test1

test2.o : $(srcdir)/test2.c trampoline_r.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $(srcdir)/test2.c

test2 : test2.o $(OBJECTS)
	$(LIBTOOL_LINK) $(CC) $(CFLAGS) -x none test2.o $(OBJECTS) -o test2

check1 : all test1
	./test1

check : all test1 test2
	./test1
	./test2
	touch tests.passed.$(HOST)

extracheck : check

mostlyclean : clean

clean : force
	$(RM) $(OBJECTS) `echo $(OBJECTS) | sed -e 's/\.lo/.o/g'` tramp-powerpc.s cache-sparc.s cache-sparc64.s libtrampoline.* core
	$(RM) -r .libs _libs
	$(RM) test1.o test1 test2.o test2

distclean : clean
	$(RM) config.status config.log config.cache Makefile config.h trampoline_r.h libtool tests.passed.*

maintainer-clean : distclean

force :


