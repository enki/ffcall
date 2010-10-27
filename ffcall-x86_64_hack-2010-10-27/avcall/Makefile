# Makefile for avcall

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
MV = mv
LN = ln
RM = rm -f


# Programs used by "make install":
INSTALL = /usr/bin/install -c
INSTALL_PROGRAM = ${INSTALL}
INSTALL_DATA = ${INSTALL} -m 644

#### End of system configuration section. ####

SHELL = /bin/sh

# Needed by $(LIBTOOL).
top_builddir = .

OBJECTS = avcall.lo structcpy.lo

all : $(OBJECTS) libavcall.la avcall.h $(srcdir)/avcall.3 $(srcdir)/avcall.html

avcall.lo : avcall-$(CPU).lo
	$(RM) avcall.lo avcall.o
	$(LN) avcall-$(CPU).lo avcall.lo
	if test -f avcall-$(CPU).o; then $(LN) avcall-$(CPU).o avcall.o; fi

avcall-i386.lo : avcall-i386.s
	$(LIBTOOL_COMPILE) $(CC) -x none -c avcall-i386.s

avcall-i386.s : $(srcdir)/avcall-i386-macro.S
	$(CPP) $(ASPFLAGS) $(srcdir)/avcall-i386-macro.S | grep -v '^ *#line' | grep -v '^#ident' | grep -v '^#' | sed -e 's,% ,%,g' -e 's,% ,%,g' -e 's,\. ,.,g' > avcall-i386.s

avcall-sparc.lo : avcall-sparc.s
	$(LIBTOOL_COMPILE) $(CC) -x none -c avcall-sparc.s

avcall-sparc.s : $(srcdir)/avcall-sparc.S
	$(CPP) $(ASPFLAGS) $(srcdir)/avcall-sparc.S | grep -v '^ *#line' | grep -v '^#' | sed -e 's,% ,%,g' -e 's,//.*$$,,' -e 's,\$$,#,g' > avcall-sparc.s

avcall-sparc64.lo : avcall-sparc64.s
	$(LIBTOOL_COMPILE) $(CC) -x none -c avcall-sparc64.s

avcall-sparc64.s : $(srcdir)/avcall-sparc64.S
	$(CPP) $(ASPFLAGS) $(srcdir)/avcall-sparc64.S | grep -v '^ *#line' | grep -v '^#' | sed -e 's,% ,%,g' -e 's,//.*$$,,' -e 's,\$$,#,g' > avcall-sparc64.s

avcall-m68k.lo : avcall-m68k.s
	$(LIBTOOL_COMPILE) $(CC) -x none -c avcall-m68k.s

avcall-m68k.s : $(srcdir)/avcall-m68k.mit.S $(srcdir)/avcall-m68k.mot.s
	$(CPP) $(ASPFLAGS) $(srcdir)/avcall-m68k.mit.S | grep -v '^ *#line' | grep -v '^#' | sed -e 's,% ,%,g' -e 's,//.*$$,,' | if test true = true; then sed -e 's/\$$//g'; else sed -e 's/\$$/%/g'; fi > avcall-m68k.s

avcall-mips.lo : avcall-mips.s
	$(LIBTOOL_COMPILE) $(CC) -x none -c avcall-mips.s

avcall-mips.s : $(srcdir)/avcall-mips.S
	$(CPP) $(ASPFLAGS) $(srcdir)/avcall-mips.S | grep -v '^ *#line' | grep -v '^#' | sed -e 's,% ,%,g' -e 's,//.*$$,,' > avcall-mips.s

avcall-mipsn32.lo : avcall-mipsn32.s
	$(LIBTOOL_COMPILE) $(CC) -x none -c avcall-mipsn32.s

avcall-mipsn32.s : $(srcdir)/avcall-mipsn32.S
	$(CPP) $(ASPFLAGS) $(srcdir)/avcall-mipsn32.S | grep -v '^ *#line' | grep -v '^#' | sed -e 's,% ,%,g' -e 's,//.*$$,,' > avcall-mipsn32.s

avcall-mips64.lo : avcall-mips64.s
	$(LIBTOOL_COMPILE) $(CC) -x none -c avcall-mips64.s

avcall-mips64.s : $(srcdir)/avcall-mips64.S
	$(CPP) $(ASPFLAGS) $(srcdir)/avcall-mips64.S | grep -v '^ *#line' | grep -v '^#' | sed -e 's,% ,%,g' -e 's,//.*$$,,' > avcall-mips64.s

avcall-alpha.lo : $(srcdir)/avcall-alpha.s
	$(LIBTOOL_COMPILE) $(CC) -x none -c $(srcdir)/avcall-alpha.s

avcall-hppa.lo : $(srcdir)/avcall-hppa.s
	$(LIBTOOL_COMPILE) $(CC) -x none -c $(srcdir)/avcall-hppa.s

avcall-s390.lo : $(srcdir)/avcall-s390.s
	$(LIBTOOL_COMPILE) $(CC) -x none -c $(srcdir)/avcall-s390.s

avcall-arm.lo : avcall-arm.s
	$(LIBTOOL_COMPILE) $(CC) -x none -c avcall-arm.s

avcall-arm.s : $(srcdir)/avcall-arm.S
	$(CPP) $(ASPFLAGS) $(srcdir)/avcall-arm.S | grep -v '^ *#line' | grep -v '^#' | sed -e 's,% ,%,g' -e 's,//,@,g' -e 's,\$$,#,g' > avcall-arm.s

avcall-armel.lo : avcall-armel.s
	$(LIBTOOL_COMPILE) $(CC) -x none -c avcall-armel.s

avcall-armel.s : $(srcdir)/avcall-armel.S
	cp $(srcdir)/avcall-armel.S avcall-armel.s

avcall-powerpc.lo : $(srcdir)/avcall-powerpc-aix.old.s $(srcdir)/avcall-powerpc-aix.new.s $(srcdir)/avcall-powerpc-sysv4.s $(srcdir)/avcall-powerpc-macos.s
	case "$(OS)" in \
	  aix3*) syntax=aix.old;; \
	  aix*) syntax=aix.new;; \
	  linux* | netbsd*) syntax=linux;; \
	  macos* | darwin*) syntax=macos;; \
	  *) syntax=sysv4;; \
	esac; \
	$(LIBTOOL_COMPILE) $(CC) -x none -c $(srcdir)/avcall-powerpc-$${syntax}.s ; \
	cp avcall-powerpc-$${syntax}.lo avcall-powerpc.lo ; rm -f avcall-powerpc-$${syntax}.lo ; \
	if test -f avcall-powerpc-$${syntax}.o; then cp avcall-powerpc-$${syntax}.o avcall-powerpc.o; fi
# Note that avcall-powerpc-${syntax}.o is kept in place, because in some cases
# avcall-powerpc-${syntax}.lo contains a symbolic reference to it and therefore
# libtool may want to access it.

avcall-powerpc64.lo : $(srcdir)/avcall-powerpc64.s
	$(LIBTOOL_COMPILE) $(CC) -x none -c $(srcdir)/avcall-powerpc64.s

avcall-m88k.lo : $(srcdir)/avcall-m88k.s
	$(LIBTOOL_COMPILE) $(CC) -x none -c $(srcdir)/avcall-m88k.s

avcall-convex.lo : $(srcdir)/avcall-convex.s
	$(LIBTOOL_COMPILE) $(CC) -x none -c $(srcdir)/avcall-convex.s

avcall-ia64.lo : $(srcdir)/avcall-ia64.s
	$(LIBTOOL_COMPILE) $(CC) -x none -c $(srcdir)/avcall-ia64.s

avcall-x86_64.lo : $(srcdir)/avcall-x86_64.s
	$(LIBTOOL_COMPILE) $(CC) -x none -c $(srcdir)/avcall-x86_64.s

structcpy.lo : $(srcdir)/structcpy.c
	$(LIBTOOL_COMPILE) $(CC) $(CFLAGS) -c $(srcdir)/structcpy.c

libavcall.la : $(OBJECTS)
	$(LIBTOOL_LINK) $(CC) -o libavcall.la -rpath $(libdir) $(OBJECTS)

# Installs the library and include files only. Typically called with only
# $(libdir) and $(includedir) - don't use $(prefix) and $(exec_prefix) here.
install-lib : all force
	mkdir -p $(libdir)
	$(LIBTOOL_INSTALL) $(INSTALL_DATA) libavcall.la $(libdir)/libavcall.la
	mkdir -p $(includedir)
	$(INSTALL_DATA) avcall.h $(includedir)/avcall.h

install : all force
	mkdir -p $(DESTDIR)$(prefix)
	mkdir -p $(DESTDIR)$(exec_prefix)
	mkdir -p $(DESTDIR)$(libdir)
	$(LIBTOOL_INSTALL) $(INSTALL_DATA) libavcall.la $(DESTDIR)$(libdir)/libavcall.la
	mkdir -p $(DESTDIR)$(includedir)
	$(INSTALL_DATA) avcall.h $(DESTDIR)$(includedir)/avcall.h
	mkdir -p $(DESTDIR)$(mandir)
	mkdir -p $(DESTDIR)$(mandir)/man3
	$(INSTALL_DATA) $(srcdir)/avcall.3 $(DESTDIR)$(mandir)/man3/avcall.3
	mkdir -p $(DESTDIR)$(datadir)
	mkdir -p $(DESTDIR)$(htmldir)
	$(INSTALL_DATA) $(srcdir)/avcall.html $(DESTDIR)$(htmldir)/avcall.html

installdirs : force
	mkdir -p $(DESTDIR)$(prefix)
	mkdir -p $(DESTDIR)$(exec_prefix)
	mkdir -p $(DESTDIR)$(libdir)
	mkdir -p $(DESTDIR)$(includedir)
	mkdir -p $(DESTDIR)$(mandir)
	mkdir -p $(DESTDIR)$(mandir)/man3
	mkdir -p $(DESTDIR)$(datadir)
	mkdir -p $(DESTDIR)$(htmldir)

uninstall : force
	$(LIBTOOL_UNINSTALL) $(RM) $(DESTDIR)$(libdir)/libavcall.la
	$(RM) $(DESTDIR)$(includedir)/avcall.h
	$(RM) $(DESTDIR)$(mandir)/man3/avcall.3
	$(RM) $(DESTDIR)$(htmldir)/avcall.html

minitests.o : $(srcdir)/minitests.c $(srcdir)/tests.c avcall.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $(srcdir)/minitests.c

minitests.s : $(srcdir)/minitests.c $(srcdir)/tests.c avcall.h
	$(CC) $(CFLAGS) $(INCLUDES) -S $(srcdir)/minitests.c

minitests : minitests.o libavcall.la
	$(LIBTOOL_LINK) $(CC) $(CFLAGS) -x none minitests.o libavcall.la -o minitests

check : all minitests
	./minitests > minitests.out
	LC_ALL=C uniq -u < minitests.out > minitests.output.$(HOST)
	test '!' -s minitests.output.$(HOST)

tests.o : $(srcdir)/tests.c avcall.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $(srcdir)/tests.c

tests.s : $(srcdir)/tests.c avcall.h
	$(CC) $(CFLAGS) $(INCLUDES) -S $(srcdir)/tests.c

tests : tests.o libavcall.la
	$(LIBTOOL_LINK) $(CC) $(CFLAGS) -x none tests.o libavcall.la -o tests

extracheck : all tests
	./tests > tests.out
	LC_ALL=C uniq -u < tests.out > tests.output.$(HOST)
	test '!' -s tests.output.$(HOST)

mostlyclean : clean

clean : force
	$(RM) *.o *.lo *.a libavcall.* core
	$(RM) avcall-i386.s avcall-sparc.s avcall-sparc64.s avcall-m68k.s avcall-mips.s avcall-mipsn32.s avcall-mips64.s avcall-arm.s avcall-armel.s
	$(RM) -r .libs _libs
	$(RM) minitests.o minitests.s minitests minitests.out
	$(RM) tests.o tests.s tests tests.out

distclean : clean
	$(RM) config.status config.log config.cache Makefile avcall.h libtool minitests.output.* tests.output.*

maintainer-clean : distclean

force :

