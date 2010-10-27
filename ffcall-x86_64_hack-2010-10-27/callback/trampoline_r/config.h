/* config.h.  Generated from config.h.in by configure.  */
/* config.h.in.  Generated from configure.in by autoheader.  */

/* symbols are prefixed by an underscore in assembly language */
#define ASM_UNDERSCORE /**/

/* whether code in malloc()ed memory is executable */
/* #undef CODE_EXECUTABLE */

/* Define to 1 if you have the <dlfcn.h> header file. */
#define HAVE_DLFCN_H 1

/* have getpagesize() */
#define HAVE_GETPAGESIZE /**/

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* have vm_allocate() and task_self() functions */
/* #undef HAVE_MACH_VM */

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* have <sys/mmap.h> and the mmap() function */
#define HAVE_MMAP /**/

/* <sys/mman.h> defines MAP_ANON and mmaping with MAP_ANON works */
/* #undef HAVE_MMAP_ANON */

/* <sys/mman.h> defines MAP_ANONYMOUS and mmaping with MAP_ANONYMOUS works */
/* #undef HAVE_MMAP_ANONYMOUS */

/* mmaping of the special device /dev/zero works */
/* #undef HAVE_MMAP_DEVZERO */

/* mmaping of the special device /dev/zero works, but only on addresses < 2^29
   */
/* #undef HAVE_MMAP_DEVZERO_SUN4_29 */

/* Define to 1 if you have the `mprotect' function. */
#define HAVE_MPROTECT 1

/* have <sys/shm.h> and <sys/ipc.h> and shared memory works */
/* #undef HAVE_SHM */

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the <sys/cachectl.h> header file. */
/* #undef HAVE_SYS_CACHECTL_H */

/* Define to 1 if you have the <sys/ipc.h> header file. */
#define HAVE_SYS_IPC_H 1

/* Define to 1 if you have the <sys/m88kbcs.h> header file. */
/* #undef HAVE_SYS_M88KBCS_H */

/* Define to 1 if you have the <sys/param.h> header file. */
/* #undef HAVE_SYS_PARAM_H */

/* Define to 1 if you have the <sys/shm.h> header file. */
#define HAVE_SYS_SHM_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/sysmacros.h> header file. */
/* #undef HAVE_SYS_SYSMACROS_H */

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <unistd_h> header file. */
#define HAVE_UNISTD_H 1

/* have a working mprotect() function */
#define HAVE_WORKING_MPROTECT /**/

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT ""

/* Define to the full name of this package. */
#define PACKAGE_NAME "libffcall/trampoline_r"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "libffcall/trampoline_r 0x010B"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "libffcall-trampoline_r"

/* Define to the version of this package. */
#define PACKAGE_VERSION "0x010B"

/* return type of getpagesize() */
#define RETGETPAGESIZETYPE int

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1
