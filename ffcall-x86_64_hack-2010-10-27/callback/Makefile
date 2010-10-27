# Makefile for callback

#### Start of system configuration section. ####

HOST = x86_64-apple-darwin10.4.0
CPU = x86_64

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
LIBTOOL = $(SHELL) $(top_builddir)/libtool
LIBTOOL_LINK = $(LIBTOOL) --mode=link
LIBTOOL_INSTALL = $(LIBTOOL) --mode=install
LIBTOOL_UNINSTALL = $(LIBTOOL) --mode=uninstall
AR = ar
AR_FLAGS = rc
RANLIB = ranlib
LN_S = ln -s
RM = rm -f


# Programs used by "make install":
INSTALL = /usr/bin/install -c
INSTALL_PROGRAM = ${INSTALL}
INSTALL_DATA = ${INSTALL} -m 644

#### End of system configuration section. ####

SHELL = /bin/sh

# Needed by $(LIBTOOL).
top_builddir = .

all : all-subdirs callback.h vacall_r.h trampoline_r.h libcallback.la $(srcdir)/callback.3 $(srcdir)/callback.html

all-subdirs : force
	cd vacall_r && $(MAKE) all
	cd trampoline_r && $(MAKE) all

callback.h :
	$(LN_S) $(srcdir)/callback.h.in callback.h

vacall_r.h :
	$(LN_S) vacall_r/vacall_r.h vacall_r.h

trampoline_r.h :
	$(LN_S) trampoline_r/trampoline_r.h trampoline_r.h

libcallback.la : vacall_r/libvacall.la trampoline_r/libtrampoline.la
	$(LIBTOOL_LINK) $(CC) -o libcallback.la -rpath $(libdir) vacall_r/vacall.lo vacall_r/misc.lo vacall_r/structcpy.lo trampoline_r/*.lo

# Installs the library and include files only. Typically called with only
# $(libdir) and $(includedir) - don't use $(prefix) and $(exec_prefix) here.
install-lib : all force
	cd vacall_r && $(MAKE) install-lib libdir='$(libdir)' includedir='$(includedir)'
	cd trampoline_r && $(MAKE) install-lib libdir='$(libdir)' includedir='$(includedir)'
	mkdir -p $(libdir)
	$(LIBTOOL_INSTALL) $(INSTALL_DATA) libcallback.la $(libdir)/libcallback.la
	mkdir -p $(includedir)
	$(INSTALL_DATA) callback.h $(includedir)/callback.h

install : force
	cd vacall_r && $(MAKE) install
	cd trampoline_r && $(MAKE) install
	mkdir -p $(DESTDIR)$(prefix)
	mkdir -p $(DESTDIR)$(exec_prefix)
	mkdir -p $(DESTDIR)$(libdir)
	$(LIBTOOL_INSTALL) $(INSTALL_DATA) libcallback.la $(DESTDIR)$(libdir)/libcallback.la
	mkdir -p $(DESTDIR)$(includedir)
	$(INSTALL_DATA) callback.h $(DESTDIR)$(includedir)/callback.h
	mkdir -p $(DESTDIR)$(mandir)
	mkdir -p $(DESTDIR)$(mandir)/man3
	$(INSTALL_DATA) $(srcdir)/callback.3 $(DESTDIR)$(mandir)/man3/callback.3
	mkdir -p $(DESTDIR)$(datadir)
	mkdir -p $(DESTDIR)$(htmldir)
	$(INSTALL_DATA) $(srcdir)/callback.html $(DESTDIR)$(htmldir)/callback.html

installdirs : force
	cd vacall_r && $(MAKE) installdirs
	cd trampoline_r && $(MAKE) installdirs
	mkdir -p $(DESTDIR)$(prefix)
	mkdir -p $(DESTDIR)$(exec_prefix)
	mkdir -p $(DESTDIR)$(libdir)
	mkdir -p $(DESTDIR)$(includedir)
	mkdir -p $(DESTDIR)$(mandir)
	mkdir -p $(DESTDIR)$(mandir)/man3
	mkdir -p $(DESTDIR)$(datadir)
	mkdir -p $(DESTDIR)$(htmldir)

uninstall : force
	cd vacall_r && $(MAKE) uninstall
	cd trampoline_r && $(MAKE) uninstall
	$(LIBTOOL_UNINSTALL) $(RM) $(DESTDIR)$(libdir)/libcallback.la
	$(RM) $(DESTDIR)$(includedir)/callback.h
	$(RM) $(DESTDIR)$(mandir)/man3/callback.3
	$(RM) $(DESTDIR)$(htmldir)/callback.html

minitests.o : $(srcdir)/minitests.c $(srcdir)/tests.c callback.h vacall_r.h trampoline_r.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $(srcdir)/minitests.c

minitests.s : $(srcdir)/minitests.c $(srcdir)/tests.c callback.h vacall_r.h trampoline_r.h
	$(CC) $(CFLAGS) $(INCLUDES) -S $(srcdir)/minitests.c

minitests : minitests.o libcallback.la
	$(LIBTOOL_LINK) $(CC) $(CFLAGS) -x none minitests.o libcallback.la -o minitests

check-subdirs : force
	cd vacall_r && $(MAKE) check
	cd trampoline_r && $(MAKE) check

check : all check-subdirs minitests
	./minitests > minitests.out
	LC_ALL=C uniq -u < minitests.out > minitests.output.$(HOST)
	test '!' -s minitests.output.$(HOST)

tests.o : $(srcdir)/tests.c callback.h vacall_r.h trampoline_r.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $(srcdir)/tests.c

tests.s : $(srcdir)/tests.c callback.h vacall_r.h trampoline_r.h
	$(CC) $(CFLAGS) $(INCLUDES) -S $(srcdir)/tests.c

tests : tests.o libcallback.la
	$(LIBTOOL_LINK) $(CC) $(CFLAGS) -x none tests.o libcallback.la -o tests

extracheck-subdirs : force
	cd vacall_r && $(MAKE) extracheck
	cd trampoline_r && $(MAKE) extracheck

extracheck : all extracheck-subdirs tests
	./tests > tests.out
	LC_ALL=C uniq -u < tests.out > tests.output.$(HOST)
	test '!' -s tests.output.$(HOST)

mostlyclean : force
	cd vacall_r && $(MAKE) mostlyclean
	cd trampoline_r && $(MAKE) mostlyclean

clean-subdirs : force
	cd vacall_r && $(MAKE) clean
	cd trampoline_r && $(MAKE) clean

clean : clean-subdirs
	$(RM) *.o *.lo core
	$(RM) callback.h vacall_r.h trampoline_r.h libcallback.*
	$(RM) -r .libs _libs
	$(RM) minitests.o minitests.s minitests minitests.out
	$(RM) tests.o tests.s tests tests.out

distclean-subdirs : force
	cd vacall_r && if test -f Makefile; then $(MAKE) distclean; fi
	cd trampoline_r && if test -f Makefile; then $(MAKE) distclean; fi

distclean : clean distclean-subdirs
	$(RM) config.status config.log config.cache Makefile libtool minitests.output.* tests.output.*

maintainer-clean-subdirs : force
	cd vacall_r && if test -f Makefile; then $(MAKE) maintainer-clean; fi
	cd trampoline_r && if test -f Makefile; then $(MAKE) maintainer-clean; fi

maintainer-clean : distclean maintainer-clean-subdirs
	$(RM) config.status config.log config.cache Makefile

force :

