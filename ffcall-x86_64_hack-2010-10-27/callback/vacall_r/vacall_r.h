/* vacall_r.h.  Generated from vacall_r.h.in by configure.  */
#ifndef _VACALL_R_H                             /*-*- C -*-*/
#define _VACALL_R_H

/*
 * Copyright 1995-2006 Bruno Haible, <bruno@clisp.org>
 *
 * This is free software distributed under the GNU General Public Licence
 * described in the file COPYING. Contact the author if you don't have this
 * or can't live with it. There is ABSOLUTELY NO WARRANTY, explicit or implied,
 * on this software.
 */

#if !defined(LIBFFCALL_VERSION)
# define LIBFFCALL_VERSION 0x010B
#endif

/* These definitions are adjusted by `configure' automatically. */

/* CPU */
#ifndef __i386__
/* #undef __i386__ */
#endif
#ifndef __m68k__
/* #undef __m68k__ */
#endif
#ifndef __mips__
/* #undef __mips__ */
#endif
#ifndef __mipsn32__
/* #undef __mipsn32__ */
#endif
#ifndef __mips64__
/* #undef __mips64__ */
#endif
#ifndef __sparc__
/* #undef __sparc__ */
#endif
#ifndef __sparc64__
/* #undef __sparc64__ */
#endif
#ifndef __alpha__
/* #undef __alpha__ */
#endif
#ifndef __hppa__
/* #undef __hppa__ */
#endif
#ifndef __arm__
/* #undef __arm__ */
#endif
#ifndef __powerpc__
/* #undef __powerpc__ */
#endif
#ifndef __powerpc64__
/* #undef __powerpc64__ */
#endif
#ifndef __s390__
/* #undef __s390__ */
#endif
#ifndef __m88k__
/* #undef __m88k__ */
#endif
#ifndef __convex__
/* #undef __convex__ */
#endif
#ifndef __ia64__
/* #undef __ia64__ */
#endif
#ifndef __x86_64__
#define __x86_64__ 1
#endif

/* Calling convention */
/* Define if using pcc non-reentrant struct return convention */
/* #undef __PCC_STRUCT_RETURN__ */
/* Define if small structs are returned in registers */
#define __SMALL_STRUCT_RETURN__ /**/
/* Define if floating-point results are returned in the integer registers */
/* #undef __IREG_FLOAT_RETURN__ */

/* AC_TYPE_LONG_LONG_INT */
/* Define if your compiler supports the 'long long' type. */
#ifndef HAVE_LONG_LONG_INT
#define HAVE_LONG_LONG_INT 1
#endif

/* AC_C_CHAR_UNSIGNED */
#ifndef __CHAR_UNSIGNED__
/* #undef __CHAR_UNSIGNED__ */
#endif

/* End of definitions adjusted by `configure'. */


/* Max # words in argument-list and temporary structure storage.
 */
#ifndef __VA_ALIST_WORDS
#define __VA_ALIST_WORDS  256
#endif

/* Determine the alignment of a type at compile time.
 */
#if defined(__GNUC__)
#define __VA_alignof __alignof__
#else
#if defined(__mips__) || defined(__mipsn32__) || defined(__mips64__) /* SGI compiler */
#define __VA_alignof __builtin_alignof
#else
#define __VA_offsetof(type,ident)  ((unsigned long)&(((type*)0)->ident))
#define __VA_alignof(type)  __VA_offsetof(struct { char __slot1; type __slot2; }, __slot2)
#endif
#endif

/* C builtin types.
 */
#if defined(__mipsn32__)
typedef long long __vaword;
#else
typedef long __vaword;
#endif

enum __VAtype
{
  __VAvoid,
  __VAchar,
  __VAschar,
  __VAuchar,
  __VAshort,
  __VAushort,
  __VAint,
  __VAuint,
  __VAlong,
  __VAulong,
  __VAlonglong,
  __VAulonglong,
  __VAfloat,
  __VAdouble,
  __VAvoidp,
  __VAstruct
};

enum __VA_alist_flags
{

  /* how to return structs */
  /* There are basically 3 ways to return structs:
   * a. The called function returns a pointer to static data. Not reentrant.
   * b. The caller passes the return structure address in a dedicated register
   *    or as a first (or last), invisible argument. The called function stores
   *    its result there.
   * c. Like b, and the called function also returns the return structure
   *    address in the return value register. (This is not very distinguishable
   *    from b.)
   * Independently of this,
   * r. small structures (<= 4 or <= 8 bytes) may be returned in the return
   *    value register(s), or
   * m. even small structures are passed in memory.
   */
  /* gcc-2.6.3 employs the following strategy:
   *   - If PCC_STATIC_STRUCT_RETURN is defined in the machine description
   *     it uses method a, else method c.
   *   - If flag_pcc_struct_return is set (either by -fpcc-struct-return or if
   *     DEFAULT_PCC_STRUCT_RETURN is defined to 1 in the machine description)
   *     it uses method m, else (either by -freg-struct-return or if
   *     DEFAULT_PCC_STRUCT_RETURN is defined to 0 in the machine description)
   *     method r.
   */
  __VA_PCC_STRUCT_RETURN	= 1<<0,	/* a: need to copy the struct */
  __VA_SMALL_STRUCT_RETURN	= 1<<1,	/* r: special case for small structs */
  __VA_GCC_STRUCT_RETURN	= 1<<2,	/* consider 8 byte structs as small */
#if defined(__sparc__) && !defined(__sparc64__)
  __VA_SUNCC_STRUCT_RETURN	= 1<<3,
  __VA_SUNPROCC_STRUCT_RETURN	= 1<<4,
#else
  __VA_SUNCC_STRUCT_RETURN	= 0,
  __VA_SUNPROCC_STRUCT_RETURN	= 0,
#endif
#if defined(__i386__)
  __VA_NEXTGCC_STRUCT_RETURN	= 1<<3,
  __VA_MSVC_STRUCT_RETURN	= 1<<4,
#endif
#if defined(__hppa__)
  __VA_OLDGCC_STRUCT_RETURN	= 1<<3,
#endif
  /* the default way to return structs */
  /* This choice here is based on the assumption that the function you are
   * going to call has been compiled with the same compiler you are using to
   * include this file.
   * If you want to call functions with another struct returning convention,
   * just  #define __VA_STRUCT_RETURN ...
   * before or after #including <vacall_r.h>.
   */
#ifndef __VA_STRUCT_RETURN
  __VA_STRUCT_RETURN		=
#if defined(__sparc__) && !defined(__sparc64__) && defined(sun) && defined(__SUNPRO_C) /* SUNWspro cc */
				  __VA_SUNPROCC_STRUCT_RETURN,
#else
#if defined(__PCC_STRUCT_RETURN__) /* defined through configure, see above */
				  __VA_PCC_STRUCT_RETURN,
#else
#if defined(__SMALL_STRUCT_RETURN__) || defined(__mipsn32__) || defined(__mips64__) || defined(__ARMEL__)/* defined through configure, see above */
				  __VA_SMALL_STRUCT_RETURN |
#endif
#if defined(__GNUC__)
				  __VA_GCC_STRUCT_RETURN |
#endif
#if defined(__i386__) && defined(NeXT) && defined(__GNUC__) /* NeXT gcc-2.5.8 */
				  __VA_NEXTGCC_STRUCT_RETURN |
#endif
#if defined(__i386__) && defined(_MSC_VER) /* MSVC 4.0 */
				  __VA_MSVC_STRUCT_RETURN |
#endif
#if defined(__hppa__) && defined(__GNUC__) && (__GNUC__ < 3) && (__GNUC_MINOR__ < 7)
				  __VA_OLDGCC_STRUCT_RETURN |
#endif
  				  0,
#endif
#endif
#endif

  /* how to return floats */
#if defined(__m68k__) || (defined(__sparc__) && !defined(__sparc64__))
  __VA_SUNCC_FLOAT_RETURN	= 1<<5,
#endif
#if defined(__m68k__)
  __VA_FREG_FLOAT_RETURN	= 1<<6,
#endif
  /* the default way to return floats */
  /* This choice here is based on the assumption that the function you are
   * going to call has been compiled with the same compiler you are using to
   * include this file.
   * If you want to call functions with another float returning convention,
   * just  #define __VA_FLOAT_RETURN ...
   * before or after #including <vacall_r.h>.
   */
#ifndef __VA_FLOAT_RETURN
#if (defined(__m68k__) || (defined(__sparc__) && !defined(__sparc64__))) && !defined(__GNUC__) && defined(sun) && !defined(__SUNPRO_C)  /* sun cc */
  __VA_FLOAT_RETURN		= __VA_SUNCC_FLOAT_RETURN,
#elif (defined(__m68k__) && !defined(__IREG_FLOAT_RETURN__))
  __VA_FLOAT_RETURN		= __VA_FREG_FLOAT_RETURN,
#else
  __VA_FLOAT_RETURN		= 0,
#endif
#endif

  /* how to pass structs */
#if defined(__mips__) || defined(__mipsn32__) || defined(__mips64__)
  __VA_SGICC_STRUCT_ARGS	= 1<<7,
#endif
#if defined(__powerpc__) && !defined(__powerpc64__)
  __VA_AIXCC_STRUCT_ARGS	= 1<<7,
#endif
  /* the default way to pass floats */
  /* This choice here is based on the assumption that the function you are
   * going to call has been compiled with the same compiler you are using to
   * include this file.
   * If you want to call functions with another float passing convention,
   * just  #define __VA_STRUCT_ARGS ...
   * before or after #including <vacall_r.h>.
   */
#ifndef __VA_STRUCT_ARGS
#if (defined(__mips__) || defined(__mipsn32__) || defined(__mips64__)) && !defined(__GNUC__) /* SGI mips cc */
  __VA_STRUCT_ARGS		= __VA_SGICC_STRUCT_ARGS,
#else
#if defined(__powerpc__) && !defined(__powerpc64__) && defined(_AIX) && !defined(__GNUC__) /* AIX cc, xlc */
  __VA_STRUCT_ARGS		= __VA_AIXCC_STRUCT_ARGS,
#else
  __VA_STRUCT_ARGS		= 0,
#endif
#endif
#endif

  /* how to pass floats */
  /* ANSI C compilers and GNU gcc pass floats as floats.
   * K&R C compilers pass floats as doubles. We don't support them any more.
   */

  /* how to pass and return small integer arguments */
  __VA_ANSI_INTEGERS		= 0, /* no promotions */
  __VA_TRADITIONAL_INTEGERS	= 0, /* promote [u]char, [u]short to [u]int */
  /* Fortunately these two methods are compatible. Our macros work with both. */

  /* stack cleanup policy */
  __VA_CDECL_CLEANUP		= 0, /* caller pops args after return */
  __VA_STDCALL_CLEANUP		= 1<<9, /* callee pops args before return */
				     /* currently only supported on __i386__ */
#ifndef __VA_CLEANUP
  __VA_CLEANUP			= __VA_CDECL_CLEANUP,
#endif

  /* These are for internal use only */
#if defined(__i386__) || defined(__m68k__) || defined(__mipsn32__) || defined(__mips64__) || defined(__sparc64__) || defined(__alpha__) || defined(__arm__) || (defined(__powerpc__) && !defined(__powerpc64__)) || defined(__convex__) || defined(__ia64__) || defined(__x86_64__) || defined(__s390__)
  __VA_REGISTER_STRUCT_RETURN	= 1<<10,
#endif
#if defined(__mips__) && !defined(__mipsn32__) && !defined(__mips64__)
  __VA_FLOAT_1			= 1<<11,
  __VA_FLOAT_2			= 1<<12,
#endif
#if defined(__mipsn32__) || defined(__mips64__)
  __VA_REGISTER_FLOATSTRUCT_RETURN	= 1<<13,
  __VA_REGISTER_DOUBLESTRUCT_RETURN	= 1<<14,
#endif

  __VA_flag_for_broken_compilers_that_dont_like_trailing_commas
};

/*
 * Definition of the `va_alist' type.
 */
typedef struct
{
  /* some va_... macros need these flags */
  int            flags;
  /* current pointer into the argument array */
  unsigned long  aptr;
  /* structure return pointer, return type, return type size */
  void*          raddr;
  enum __VAtype  rtype;
  unsigned long  rsize;
#if defined(__i386__) || (defined(__powerpc__) && !defined(__powerpc64__) && defined(__MACH__) && defined(__APPLE__))
  /* Filler word, needed if the numbers of words up to now in this structure */
  /* is odd (because on MSVC, alignof(double) = 8, normally = 4; similarly,  */
  /* on MacOS X, the Apple compiler has alignof(double) = 8 whereas the      */
  /* standard GCC has alignof(double) = 4.                                   */
  __vaword       filler1;
#endif
  /* temporary storage for return value */
  union {
    char                _char;
    signed char         _schar;
    unsigned char       _uchar;
    short               _short;
    unsigned short      _ushort;
    int                 _int;
    unsigned int        _uint;
    long                _long;
    unsigned long       _ulong;
#if !(defined(__mips64__) || defined(__alpha__) || defined(__powerpc64__)) && defined(HAVE_LONG_LONG_INT)
    long long           _longlong;
    unsigned long long  _ulonglong;
#endif
    float               _float;
    double              _double;
    void*               _ptr;
    __vaword            _words[2];
  }              tmp;
#if defined(__i386__) || defined(__m68k__) || (defined(__sparc__) && !defined(__sparc64__)) || defined(__hppa__) || defined(__m88k__) || defined(__ia64__)
  void*          structraddr;
#endif
#if defined(__mips__) || defined(__mipsn32__) || defined(__mips64__) || defined(__alpha__) || defined(__hppa__)
  long           memargptr;
#endif
#if defined(__hppa__)
  long           farg_offset;
  long           darg_offset;
  float          farg[4];
  double         darg[2];
#endif
#if defined(__mips__) && !defined(__mipsn32__) && !defined(__mips64__)
  int            anum;
  float          farg[2];
  double         darg[2];
#endif
#if defined(__mipsn32__) || defined(__mips64__)
  int            anum;
  float          farg[8];
  double         darg[8];
#endif
#if defined(__sparc64__)
  int            anum;
  float          farg[16];
  double         darg[16];
#endif
#if defined(__powerpc__) || defined(__powerpc64__)
  double*        memfargptr;
  double         farg[13];
#if !(defined(_AIX) || (defined(__MACH__) && defined(__APPLE__)))
  __vaword       regarg[8];
  unsigned long  saptr;
  int            onstack;
#endif
#endif
#if defined(__s390__)
  float*         memfargptr;
  double*        memdargptr;
  float          farg[2];
  double         darg[2];
  __vaword       regarg[5];
  unsigned long  saptr;
  int            onstack;
#endif
#if defined(__ia64__)
  __vaword*      saptr;
  double*        memfargptr;
  double         farg[8];
#endif
#if defined(__x86_64__)
  double*        memfargptr;
  double         farg[8];
  __vaword*      memiargptr;
  __vaword       iarg[6];
#endif
} __va_alist;

typedef __va_alist* va_alist;


/*
 * Definition of the va_start_xxx macros.
 */
#define __VA_START_FLAGS  \
  __VA_STRUCT_RETURN | __VA_FLOAT_RETURN | __VA_STRUCT_ARGS | __VA_CLEANUP
#define __va_start(LIST,RETTYPE)  \
  ((LIST)->flags = __VA_START_FLAGS,					\
   (LIST)->rtype = (RETTYPE)						\
  )
#define va_start_void(LIST)	 __va_start(LIST,__VAvoid)
#define va_start_char(LIST)	 __va_start(LIST,__VAchar)
#define va_start_schar(LIST)	 __va_start(LIST,__VAschar)
#define va_start_uchar(LIST)	 __va_start(LIST,__VAuchar)
#define va_start_short(LIST)	 __va_start(LIST,__VAshort)
#define va_start_ushort(LIST)	 __va_start(LIST,__VAushort)
#define va_start_int(LIST)	 __va_start(LIST,__VAint)
#define va_start_uint(LIST)	 __va_start(LIST,__VAuint)
#define va_start_long(LIST)	 __va_start(LIST,__VAlong)
#define va_start_ulong(LIST)	 __va_start(LIST,__VAulong)
#define va_start_longlong(LIST)	 __va_start(LIST,__VAlonglong)
#define va_start_ulonglong(LIST) __va_start(LIST,__VAulonglong)
#define va_start_float(LIST)	 __va_start(LIST,__VAfloat)
#define va_start_double(LIST)	 __va_start(LIST,__VAdouble)
#define va_start_ptr(LIST,TYPE)	 __va_start(LIST,__VAvoidp)

/*
 * va_start_struct: Preparing structure return.
 */
#define va_start_struct(LIST,TYPE,TYPE_SPLITTABLE)  \
  _va_start_struct(LIST,sizeof(TYPE),__VA_alignof(TYPE),TYPE_SPLITTABLE)
/* _va_start_struct() is like va_start_struct(), except that you pass
 * the type's size and alignment instead of the type itself.
 */
#define _va_start_struct(LIST,TYPE_SIZE,TYPE_ALIGN,TYPE_SPLITTABLE)  \
  (__va_start(LIST,__VAstruct),						\
   (LIST)->rsize = (TYPE_SIZE),						\
   ((LIST)->flags & __VA_SUNPROCC_STRUCT_RETURN				\
    ? __va_start_struct2(LIST)						\
    : ((LIST)->flags & (__VA_PCC_STRUCT_RETURN | __VA_SUNCC_STRUCT_RETURN) \
       ? ((TYPE_SIZE) <= sizeof(__va_struct_buffer) || __va_error2(TYPE_SIZE), \
          (LIST)->raddr = &__va_struct_buffer,				\
          0								\
         )								\
       : (((LIST)->flags & __VA_SMALL_STRUCT_RETURN)			\
          && __va_reg_struct_return(LIST,TYPE_SIZE,TYPE_SPLITTABLE)	\
          ? ((LIST)->raddr = &(LIST)->tmp,				\
             __va_start_struct1(LIST,TYPE_SIZE,TYPE_ALIGN,TYPE_SPLITTABLE) \
            )								\
          : __va_start_struct2(LIST)					\
  ))  )  )
/* Determines whether a structure is returned in registers,
 * depending on its size and its word-splittable flag.
 */
#if (defined(__i386__) && defined(_WIN32))
#define __va_reg_struct_return(LIST,TYPE_SIZE,TYPE_SPLITTABLE)  \
  ((TYPE_SIZE) == 1 || (TYPE_SIZE) == 2 || (TYPE_SIZE) == 4		\
   || ((TYPE_SIZE) == 8							\
       && (((LIST)->flags & __VA_MSVC_STRUCT_RETURN)			\
           || ((TYPE_SPLITTABLE)					\
               && ((LIST)->flags & __VA_GCC_STRUCT_RETURN)		\
  )   )   )   )
/* Turn on __VA_REGISTER_STRUCT_RETURN if __VA_SMALL_STRUCT_RETURN was set
 * and the struct will actually be returned in registers.
 */
#define __va_start_struct1(LIST,TYPE_SIZE,TYPE_ALIGN,TYPE_SPLITTABLE)  \
  ((LIST)->flags |= __VA_REGISTER_STRUCT_RETURN, 0)
#endif
#if (defined(__i386__) && !defined(_WIN32)) || defined(__m68k__) || (defined(__arm__) && !defined(__ARMEL__)) || (defined(__powerpc__) && !defined(__powerpc64__)) || defined(__convex__) || defined(__s390__)
#define __va_reg_struct_return(LIST,TYPE_SIZE,TYPE_SPLITTABLE)  \
  ((TYPE_SIZE) == 1 || (TYPE_SIZE) == 2 || (TYPE_SIZE) == 4		\
   || ((TYPE_SIZE) == 8 && (TYPE_SPLITTABLE)				\
       && ((LIST)->flags & __VA_GCC_STRUCT_RETURN)			\
  )   )
/* Turn on __VA_REGISTER_STRUCT_RETURN if __VA_SMALL_STRUCT_RETURN was set
 * and the struct will actually be returned in registers.
 */
#define __va_start_struct1(LIST,TYPE_SIZE,TYPE_ALIGN,TYPE_SPLITTABLE)  \
  ((LIST)->flags |= __VA_REGISTER_STRUCT_RETURN, 0)
#endif

#if defined(__ARMEL__)
/* structs of size 3 also will be returned in register */
#define __va_reg_struct_return(LIST,TYPE_SIZE,TYPE_SPLITTABLE)  \
    ((TYPE_SIZE) <= 4)
/* Turn on __VA_REGISTER_STRUCT_RETURN if __VA_SMALL_STRUCT_RETURN was set
 * and the struct will actually be returned in registers.
 */
#define __va_start_struct1(LIST,TYPE_SIZE,TYPE_ALIGN,TYPE_SPLITTABLE)  \
  ((LIST)->flags |= __VA_REGISTER_STRUCT_RETURN, 0)
#endif
#if defined(__alpha__)
#define __va_reg_struct_return(LIST,TYPE_SIZE,TYPE_SPLITTABLE)  \
  ((TYPE_SIZE) == 1 || (TYPE_SIZE) == 2 || (TYPE_SIZE) == 4 || (TYPE_SIZE) == 8	\
   || ((TYPE_SIZE) == 16 && (TYPE_SPLITTABLE)				\
       && ((LIST)->flags & __VA_GCC_STRUCT_RETURN)			\
  )   )
/* Turn on __VA_REGISTER_STRUCT_RETURN if __VA_SMALL_STRUCT_RETURN was set
 * and the struct will actually be returned in registers.
 */
#define __va_start_struct1(LIST,TYPE_SIZE,TYPE_ALIGN,TYPE_SPLITTABLE)  \
  ((LIST)->flags |= __VA_REGISTER_STRUCT_RETURN, 0)
#endif
#if defined(__hppa__)
#define __va_reg_struct_return(LIST,TYPE_SIZE,TYPE_SPLITTABLE)  \
  ((LIST)->flags & __VA_OLDGCC_STRUCT_RETURN				\
   ? ((TYPE_SIZE) == 1 || (TYPE_SIZE) == 2 || (TYPE_SIZE) == 4)		\
   : ((TYPE_SIZE) <= 8)							\
  )
/* Test both __VA_OLDGCC_STRUCT_RETURN and __VA_SMALL_STRUCT_RETURN at run time. */
#define __va_start_struct1(LIST,TYPE_SIZE,TYPE_ALIGN,TYPE_SPLITTABLE)  \
  0
#endif
#if defined(__mips__) && !defined(__mipsn32__) && !defined(__mips64__) || (defined(__sparc__) && !defined(__sparc64__)) || defined(__m88k__)
#define __va_reg_struct_return(LIST,TYPE_SIZE,TYPE_SPLITTABLE)  \
  ((TYPE_SIZE) == 1 || (TYPE_SIZE) == 2 || (TYPE_SIZE) == 4)
/* Test __VA_SMALL_STRUCT_RETURN instead of __VA_REGISTER_STRUCT_RETURN. */
#if defined(__mips__) && !defined(__mipsn32__) && !defined(__mips64__)
#define __va_start_struct1(LIST,TYPE_SIZE,TYPE_ALIGN,TYPE_SPLITTABLE)  \
  ((LIST)->anum++,							\
   0									\
  )
#else
#define __va_start_struct1(LIST,TYPE_SIZE,TYPE_ALIGN,TYPE_SPLITTABLE)  \
  0
#endif
#endif
#if defined(__mipsn32__) || defined(__mips64__)
#define __va_reg_struct_return(LIST,TYPE_SIZE,TYPE_SPLITTABLE)  \
  ((LIST)->flags & __VA_GCC_STRUCT_RETURN				\
   ? ((TYPE_SIZE) == 1 || (TYPE_SIZE) == 2 || (TYPE_SIZE) == 4 || (TYPE_SIZE) == 8) \
   : ((TYPE_SIZE) <= 16)						\
  )
/* Turn on __VA_REGISTER_STRUCT_RETURN if __VA_SMALL_STRUCT_RETURN was set
 * and the struct will actually be returned in registers. Also turn on
 * __VA_REGISTER_FLOATSTRUCT_RETURN or __VA_REGISTER_DOUBLESTRUCT_RETURN if
 * the struct will be returned in floating-point registers.
 */
#define __va_start_struct1(LIST,TYPE_SIZE,TYPE_ALIGN,TYPE_SPLITTABLE)  \
  ((LIST)->flags |= __VA_REGISTER_STRUCT_RETURN,				\
   (TYPE_ALIGN) == sizeof(float) && (TYPE_SPLITTABLE)				\
    && ((TYPE_SIZE) == sizeof(float) || (TYPE_SIZE) == 2*sizeof(float))		\
    && ((LIST)->flags |= __VA_REGISTER_FLOATSTRUCT_RETURN),			\
   (TYPE_ALIGN) == sizeof(double) && (TYPE_SPLITTABLE)				\
    && ((TYPE_SIZE) == sizeof(double) || (TYPE_SIZE) == 2*sizeof(double))	\
    && ((LIST)->flags |= __VA_REGISTER_DOUBLESTRUCT_RETURN),			\
   0)
#endif
#if defined(__powerpc64__)
#define __va_reg_struct_return(LIST,TYPE_SIZE,TYPE_SPLITTABLE)  \
  0
#define __va_start_struct1(LIST,TYPE_SIZE,TYPE_ALIGN,TYPE_SPLITTABLE)  \
  0
#endif
#if defined(__sparc64__) || defined(__ia64__)
#define __va_reg_struct_return(LIST,TYPE_SIZE,TYPE_SPLITTABLE)  \
  ((TYPE_SIZE) <= 32)
/* Turn on __VA_REGISTER_STRUCT_RETURN if __VA_SMALL_STRUCT_RETURN was set
 * and the struct will actually be returned in registers.
 */
#define __va_start_struct1(LIST,TYPE_SIZE,TYPE_ALIGN,TYPE_SPLITTABLE)  \
  ((LIST)->flags |= __VA_REGISTER_STRUCT_RETURN,				\
   0)
#endif
#if defined(__x86_64__)
#define __va_reg_struct_return(LIST,TYPE_SIZE,TYPE_SPLITTABLE)  \
  ((TYPE_SIZE) <= 16)
/* Turn on __VA_REGISTER_STRUCT_RETURN if __VA_SMALL_STRUCT_RETURN was set
 * and the struct will actually be returned in registers.
 */
#define __va_start_struct1(LIST,TYPE_SIZE,TYPE_ALIGN,TYPE_SPLITTABLE)  \
  ((LIST)->flags |= __VA_REGISTER_STRUCT_RETURN,				\
   0)
#endif
/*
 * Preparing structure return in memory.
 */
#if defined(__i386__)
/* Return structure pointer is passed in a special register or as first arg. */
#define __va_start_struct2(LIST)  \
  ((LIST)->flags & __VA_NEXTGCC_STRUCT_RETURN				\
   ? ((LIST)->raddr = (LIST)->structraddr, 0)	 /* special register */	\
   : ((LIST)->raddr = *(void* *)((LIST)->aptr),		/* first arg */	\
      (LIST)->aptr += sizeof(void*),					\
      0									\
  )  )
#endif
#if defined(__alpha__) || defined(__arm__) || defined(__powerpc__) || defined(__powerpc64__) || defined(__convex__)  || defined(__s390__)
/* Return structure pointer is passed as first arg. */
#define __va_start_struct2(LIST)  \
  ((LIST)->raddr = *(void* *)((LIST)->aptr),				\
   (LIST)->aptr += sizeof(void*),					\
   0									\
  )
#endif
#if defined(__mips__) || defined(__mipsn32__) || defined(__mips64__) || defined(__sparc64__)
/* Return structure pointer is passed as first arg. */
#define __va_start_struct2(LIST)  \
  ((LIST)->raddr = *(void* *)((LIST)->aptr),				\
   (LIST)->aptr += sizeof(void*),					\
   (LIST)->anum++,							\
   0									\
  )
#endif
#if defined(__x86_64__)
/* Return structure pointer is passed as first arg. */
#define __va_start_struct2(LIST)  \
  ((LIST)->raddr = (void *)(*(LIST)->memiargptr++),			\
   0									\
  )
#endif
#if defined(__m68k__) || (defined(__sparc__) && !defined(__sparc64__)) || defined(__hppa__) || defined(__m88k__) || defined(__ia64__)
/* Return structure pointer is passed in a special register. */
#define __va_start_struct2(LIST)  \
  ((LIST)->raddr = (LIST)->structraddr, 0)
#endif


/*
 * Definition of the va_arg_xxx macros.
 */

/* Padding of non-struct arguments. */
#define __va_argsize(TYPE_SIZE)  \
  (((TYPE_SIZE) + sizeof(__vaword)-1) & -(long)sizeof(__vaword))
#if defined(__i386__) || defined(__m68k__) || (defined(__mips__) && !defined(__mipsn32__) && !defined(__mips64__)) || (defined(__sparc__) && !defined(__sparc64__)) || defined(__alpha__) || defined(__arm__) || (defined(__powerpc__) && !defined(__powerpc64__) && (defined(_AIX) || (defined(__MACH__) && defined(__APPLE__)))) || defined(__powerpc64__) || defined(__m88k__) || defined(__convex__) || defined(__ia64__) || defined(__x86_64__)
/* args grow up */
/* small structures < 1 word are adjusted depending on compiler */
#define __va_arg_leftadjusted(LIST,TYPE_SIZE,TYPE_ALIGN)  \
  ((LIST)->aptr += __va_argsize(TYPE_SIZE),				\
   (LIST)->aptr - __va_argsize(TYPE_SIZE)				\
  )
#define __va_arg_rightadjusted(LIST,TYPE_SIZE,TYPE_ALIGN)  \
  ((LIST)->aptr += __va_argsize(TYPE_SIZE),				\
   (LIST)->aptr - ((TYPE_SIZE) < sizeof(__vaword)			\
		   ? (TYPE_SIZE)					\
		   : __va_argsize(TYPE_SIZE)				\
		  )							\
  )
#endif
#if defined(__powerpc__) && !defined(__powerpc64__) && !(defined(_AIX) || (defined(__MACH__) && defined(__APPLE__)))
/* args grow up */
/* small structures < 1 word are adjusted depending on compiler */
/* Also make sure we switch to the stack pointer after 8 args */
#define __va_arg_leftadjusted(LIST,TYPE_SIZE,TYPE_ALIGN)  \
  ((((LIST)->onstack == 0 && (LIST)->aptr >= (long)&(LIST)->regarg[8])	\
    ? ((LIST)->onstack=1, (LIST)->aptr = (LIST)->saptr) : 0),		\
   (LIST)->aptr += __va_argsize(TYPE_SIZE),				\
   (LIST)->aptr - __va_argsize(TYPE_SIZE)				\
  )
#define __va_arg_rightadjusted(LIST,TYPE_SIZE,TYPE_ALIGN)  \
  ((((LIST)->onstack == 0 && (LIST)->aptr >= (long)&(LIST)->regarg[8])	\
    ? ((LIST)->onstack=1, (LIST)->aptr = (LIST)->saptr) : 0),		\
   (LIST)->aptr += __va_argsize(TYPE_SIZE),				\
   (LIST)->aptr - ((TYPE_SIZE) < sizeof(__vaword)			\
		   ? (TYPE_SIZE)					\
		   : __va_argsize(TYPE_SIZE)				\
		  )							\
  )
#endif
#if defined(__s390__)
/* args grow up */
/* small structures < 1 word are adjusted depending on compiler */
/* Also make sure we switch to the stack pointer after 5 args */
#define __va_arg_leftadjusted(LIST,TYPE_SIZE,TYPE_ALIGN)  \
  ((((LIST)->onstack == 0 && (LIST)->aptr >= (long)&(LIST)->regarg[5])	\
    ? ((LIST)->onstack=1, (LIST)->aptr = (LIST)->saptr) : 0),		\
   (LIST)->aptr += __va_argsize(TYPE_SIZE),				\
   (LIST)->aptr - __va_argsize(TYPE_SIZE)				\
  )
#define __va_arg_rightadjusted(LIST,TYPE_SIZE,TYPE_ALIGN)  \
  (((((LIST)->onstack == 0 && ((LIST)->aptr >= (long)&(LIST)->regarg[5])) \
   || ((TYPE_SIZE) > sizeof(__vaword) && (LIST)->aptr >= (long)&(LIST)->regarg[4])) \
    ? ((LIST)->onstack=1, (LIST)->aptr = (LIST)->saptr) : 0),		\
   (LIST)->aptr += __va_argsize(TYPE_SIZE),				\
   (LIST)->aptr - ((TYPE_SIZE) < sizeof(__vaword)			\
		   ? (TYPE_SIZE)					\
		   : __va_argsize(TYPE_SIZE)				\
		  )							\
  )
#endif
#if defined(__mipsn32__) || defined(__mips64__) || defined(__sparc64__)
/* args grow up */
/* small structures < 1 word are adjusted depending on compiler */
#define __va_arg_leftadjusted(LIST,TYPE_SIZE,TYPE_ALIGN)  \
  ((LIST)->anum += __va_argsize(TYPE_SIZE)/sizeof(__vaword),		\
   (LIST)->aptr += __va_argsize(TYPE_SIZE),				\
   (LIST)->aptr - __va_argsize(TYPE_SIZE)				\
  )
#define __va_arg_rightadjusted(LIST,TYPE_SIZE,TYPE_ALIGN)  \
  ((LIST)->anum += __va_argsize(TYPE_SIZE)/sizeof(__vaword),		\
   (LIST)->aptr += __va_argsize(TYPE_SIZE),				\
   (LIST)->aptr - ((TYPE_SIZE) < sizeof(__vaword)			\
		   ? (TYPE_SIZE)					\
		   : __va_argsize(TYPE_SIZE)				\
		  )							\
  )
#endif
#if defined(__hppa__)
/* args grow down */
#define __va_arg_leftadjusted(LIST,TYPE_SIZE,TYPE_ALIGN)  \
  ((LIST)->aptr = (LIST)->aptr - __va_argsize(TYPE_SIZE),		\
   ((TYPE_SIZE) > 4 && ((LIST)->aptr &= -8)),				\
   (LIST)->aptr								\
  )
#define __va_arg_rightadjusted(LIST,TYPE_SIZE,TYPE_ALIGN)  \
  ((LIST)->aptr = (LIST)->aptr - __va_argsize(TYPE_SIZE),		\
   ((TYPE_SIZE) > 4 && ((LIST)->aptr &= -8)),				\
   (LIST)->aptr + ((-(TYPE_SIZE)) & 3)					\
  )
#endif
#if defined(__i386__) || defined(__alpha__) || defined(__ia64__) || defined(__ARMEL__) || ((defined(__mipsn32__) || defined(__mips64__)) && defined(_MIPSEL))
/* little endian -> small args < 1 word are adjusted to the left */
#define __va_arg_adjusted(LIST,TYPE_SIZE,TYPE_ALIGN)  \
  __va_arg_leftadjusted(LIST,TYPE_SIZE,TYPE_ALIGN)
#endif
#if defined(__m68k__) || ((defined(__mipsn32__) || defined(__mips64__)) && defined(_MIPSEB)) || defined(__sparc__) || defined(__sparc64__) || defined(__hppa__) || (defined(__arm__) && !defined(__ARMEL__)) || defined(__powerpc__) || defined(__powerpc64__) || defined(__m88k__) || defined(__convex__) || defined(__s390__)
/* big endian -> small args < 1 word are adjusted to the right */
#define __va_arg_adjusted(LIST,TYPE_SIZE,TYPE_ALIGN)  \
  __va_arg_rightadjusted(LIST,TYPE_SIZE,TYPE_ALIGN)
#endif
#if defined(__mips__) && !defined(__mipsn32__) && !defined(__mips64__)
#ifdef _MIPSEB
/* big endian -> small args < 1 word are adjusted to the right */
#define __va_arg_adjusted(LIST,TYPE_SIZE,TYPE_ALIGN)  \
  ((LIST)->anum++, __va_arg_rightadjusted(LIST,TYPE_SIZE,TYPE_ALIGN))
#else /* _MIPSEL */
/* little endian -> small args < 1 word are adjusted to the left */
#define __va_arg_adjusted(LIST,TYPE_SIZE,TYPE_ALIGN)  \
  ((LIST)->anum++, __va_arg_leftadjusted(LIST,TYPE_SIZE,TYPE_ALIGN))
#endif
#endif
#if defined(__x86_64__)
/* the first 6 argument words are passed in registers */
#define __va_arg_adjusted(LIST,TYPE_SIZE,TYPE_ALIGN)  \
  ((LIST)->memiargptr + ((TYPE_SIZE) + sizeof(__vaword)-1) / sizeof(__vaword) <= &(LIST)->iarg[6] \
   ? ((LIST)->memiargptr += ((TYPE_SIZE) + sizeof(__vaword)-1) / sizeof(__vaword), \
      (LIST)->memiargptr - ((TYPE_SIZE) + sizeof(__vaword)-1) / sizeof(__vaword) \
     )									\
   : (void*)__va_arg_leftadjusted(LIST,TYPE_SIZE,TYPE_ALIGN)		\
  )
#endif
#define __va_arg(LIST,TYPE)  \
  *(TYPE*)__va_arg_adjusted(LIST,sizeof(TYPE),__VA_alignof(TYPE))

/* Integer arguments. */

#define va_arg_char(LIST)	__va_arg(LIST,char)
#define va_arg_schar(LIST)	__va_arg(LIST,signed char)
#define va_arg_uchar(LIST)	__va_arg(LIST,unsigned char)
#define va_arg_short(LIST)	__va_arg(LIST,short)
#define va_arg_ushort(LIST)	__va_arg(LIST,unsigned short)
#define va_arg_int(LIST)	__va_arg(LIST,int)
#define va_arg_uint(LIST)	__va_arg(LIST,unsigned int)
#define va_arg_long(LIST)	__va_arg(LIST,long)
#define va_arg_ulong(LIST)	__va_arg(LIST,unsigned long)

#if defined(__mips64__) || defined(__sparc64__) || defined(__alpha__) || defined(__powerpc64__) || defined(__ia64__) || defined(__x86_64__)
/* `long long' and `long' are identical. */
#define va_arg_longlong		va_arg_long
#define va_arg_ulonglong	va_arg_ulong
#elif defined(__mipsn32__)
/* `long long' fits in __vaword. */
#define va_arg_longlong(LIST)	__va_arg(LIST,long long)
#define va_arg_ulonglong(LIST)	__va_arg(LIST,unsigned long long)
#elif defined(__i386__) || defined(__m68k__) || defined(__mips__) || (defined(__sparc__) && !defined(__sparc64__)) || defined(__hppa__) || defined(__arm__) || defined(__powerpc__) || defined(__m88k__) || defined(__convex__) || defined(__s390__)
/* `long long's are passed embedded on the arg stack. */
#define va_arg_longlong(LIST)	__va_arg_longlong(LIST,long long)
#define va_arg_ulonglong(LIST)	__va_arg_longlong(LIST,unsigned long long)
#if defined(__i386__) || defined(__m68k__) || (defined(__arm__) && !defined(__ARMEL__)) || (defined(__powerpc__) && (defined(_AIX) || (defined(__MACH__) && defined(__APPLE__)))) || defined(__convex__)
/* `long long's are (at most) word-aligned. */
#define __va_arg_longlong(LIST,TYPE)	__va_arg(LIST,TYPE)
#endif
#if defined(__mips__) || (defined(__powerpc__) && !(defined(_AIX) || (defined(__MACH__) && defined(__APPLE__)))) || defined(__m88k__) || defined(__ARMEL__)
/* `long long's have alignment 8. */
#define __va_arg_longlong(LIST,TYPE)					\
  ((LIST)->aptr = (((LIST)->aptr+__VA_alignof(TYPE)-1) & -(long)__VA_alignof(TYPE)), \
   __va_arg(LIST,TYPE))
#endif
#if (defined(__sparc__) && !defined(__sparc64__)) || defined(__s390__)
/* Within the arg stack, the alignment is only 4, not 8. */
/* Beware against unaligned accesses! */
#define __va_arg_longlong(LIST,TYPE)					\
  ((LIST)->tmp._words[0] = ((__vaword*)((LIST)->aptr))[0],		\
   (LIST)->tmp._words[1] = ((__vaword*)((LIST)->aptr))[1],		\
   (LIST)->aptr += sizeof(TYPE),					\
   (TYPE)((LIST)->tmp._longlong)					\
  )
#endif
#if defined(__hppa__)
/* `long long's have alignment 8. */
#define __va_arg_longlong(LIST,TYPE)					\
  ((LIST)->aptr = ((LIST)->aptr & -(long)__VA_alignof(TYPE)),		\
   __va_arg(LIST,TYPE))
#endif
#endif

/* Floating point arguments. */

#if defined(__i386__) || defined(__m68k__) || defined(__mipsn32__) || defined(__mips64__) || defined(__sparc__) || defined(__sparc64__) || defined(__alpha__) || (defined(__arm__) && !defined(__ARMEL__)) || defined(__powerpc__) || defined(__powerpc64__) || defined(__convex__) || defined(__ia64__) || defined(__x86_64__) || defined(__s390__)
#define __va_align_double(LIST)
#endif
#if defined(__mips__) && !defined(__mipsn32__) && !defined(__mips64__) || defined(__m88k__) || defined(__ARMEL__)
/* __VA_alignof(double) > sizeof(__vaword) */
#define __va_align_double(LIST)  \
  (LIST)->aptr = ((LIST)->aptr + sizeof(double)-1) & -(long)sizeof(double),
#endif
#if defined(__hppa__)
#define __va_align_double(LIST)  \
  (LIST)->aptr = (LIST)->aptr & -(long)sizeof(double),
#endif

#if defined(__sparc__) && !defined(__sparc64__)
/* Beware against unaligned `double' accesses! */
#define va_arg_double(LIST)  \
  (__va_align_double(LIST)						\
   (LIST)->tmp._words[0] = ((__vaword*)((LIST)->aptr))[0],		\
   (LIST)->tmp._words[1] = ((__vaword*)((LIST)->aptr))[1],		\
   (LIST)->aptr += sizeof(double),					\
   (LIST)->tmp._double							\
  )
#endif
#if defined(__alpha__)
/* The first 6 floating point registers have been stored in another place. */
#define va_arg_double(LIST)  \
  (((LIST)->aptr += sizeof(double)) <= (LIST)->memargptr		\
   ? *(double*)((LIST)->aptr - sizeof(double) - 6*sizeof(double))	\
   : *(double*)((LIST)->aptr - sizeof(double))				\
  )
#define va_arg_float(LIST)  \
  (((LIST)->aptr += sizeof(double)) <= (LIST)->memargptr		\
   ? /* The first 6 args have been put into memory by "stt" instructions */\
     /* (see vacall-alpha.s!). Therefore load them as doubles. */	\
     /* When viewed as floats, the value will be the correct one. */	\
     (float)*(double*)((LIST)->aptr - sizeof(double) - 6*sizeof(double)) \
   : /* These args have been put into memory by "sts" instructions, */	\
     /* therefore load them as floats. */				\
     *(float*)((LIST)->aptr - sizeof(double))				\
  )
#endif
#if defined(__hppa__)
/* The first 4 float registers and the first 2 double registers are stored
 * elsewhere.
 */
#if 1 /* gcc-2.5.2 passes these args in general registers! A bug, I think. */
#define va_arg_float(LIST)  \
  (*(float*)((LIST)->aptr -= sizeof(float)))
#define va_arg_double(LIST)  \
  (__va_align_double(LIST)						\
   *(double*)((LIST)->aptr -= sizeof(double))				\
  )
#else /* this would be correct if the args were passed in float registers. */
#define va_arg_float(LIST)  \
  (((LIST)->aptr -= sizeof(float)) >= (LIST)->memargptr			\
   ? /* The first 4 float args are stored separately. */		\
     *(float*)((LIST)->aptr + (LIST)->farg_offset)			\
   : *(float*)((LIST)->aptr)						\
  )
#define va_arg_double(LIST)  \
  (__va_align_double(LIST)						\
   (((LIST)->aptr -= sizeof(double)) >= (LIST)->memargptr		\
    ? /* The first 2 double args are stored separately. */		\
      *(double*)((LIST)->aptr + (LIST)->darg_offset)			\
    : *(double*)((LIST)->aptr)						\
  ))
#endif
#endif
#if defined(__mips__) && !defined(__mipsn32__) && !defined(__mips64__)
/* The first 0,1,2 registers are stored elsewhere if they are floating-point
 * parameters.
 */
#define va_arg_float(LIST)  \
  ((LIST)->aptr += sizeof(float),					\
   (LIST)->anum++,							\
   ((LIST)->anum == 1							\
    ? ((LIST)->flags |= __VA_FLOAT_1, (LIST)->farg[0])			\
    : ((LIST)->anum == 2 && ((LIST)->flags & __VA_FLOAT_1)		\
       ? (/* (LIST)->flags |= __VA_FLOAT_2, */ (LIST)->farg[1])		\
       : *(float*)((LIST)->aptr - sizeof(float))			\
  ))  )
#define va_arg_double(LIST)  \
  (__va_align_double(LIST)						\
   (LIST)->aptr += sizeof(double),					\
   (LIST)->anum++,							\
   ((LIST)->anum == 1							\
    ? ((LIST)->flags |= __VA_FLOAT_1, (LIST)->darg[0])			\
    : ((LIST)->anum == 2 && ((LIST)->flags & __VA_FLOAT_1)		\
       ? (/* (LIST)->flags |= __VA_FLOAT_2, */ (LIST)->darg[1])		\
       : *(double*)((LIST)->aptr - sizeof(double))			\
  ))  )
#endif
#if defined(__mipsn32__) || defined(__mips64__)
/* The first 0,..,8 registers are stored elsewhere if they are floating-point
 * parameters.
 */
#define va_arg_float(LIST)  \
  (__va_align_double(LIST)						\
   (LIST)->aptr += sizeof(double),					\
   (++(LIST)->anum <= 8							\
    ? (LIST)->farg[(LIST)->anum - 1]					\
    : *(float*)((LIST)->aptr - sizeof(double))				\
  ))
#define va_arg_double(LIST)  \
  (__va_align_double(LIST)						\
   (LIST)->aptr += sizeof(double),					\
   (++(LIST)->anum <= 8							\
    ? (LIST)->darg[(LIST)->anum - 1]					\
    : *(double*)((LIST)->aptr - sizeof(double))				\
  ))
#endif
#if defined(__sparc64__)
/* The first 0,..,16 registers are stored elsewhere if they are floating-point
 * parameters.
 */
#define va_arg_float(LIST)  \
  (__va_align_double(LIST)						\
   (LIST)->aptr += sizeof(double),					\
   (++(LIST)->anum <= 16						\
    ? (LIST)->farg[(LIST)->anum - 1]					\
    : *(float*)((LIST)->aptr - sizeof(double))				\
  ))
#define va_arg_double(LIST)  \
  (__va_align_double(LIST)						\
   (LIST)->aptr += sizeof(double),					\
   (++(LIST)->anum <= 16						\
    ? (LIST)->darg[(LIST)->anum - 1]					\
    : *(double*)((LIST)->aptr - sizeof(double))				\
  ))
#endif
#if defined(__powerpc__) && !defined(__powerpc64__) && (defined(_AIX) || (defined(__MACH__) && defined(__APPLE__)))
/* The first 13 floating-point args have been stored elsewhere. */
#define va_arg_float(LIST)  \
  ((LIST)->aptr += sizeof(float),					\
   ((LIST)->memfargptr < &(LIST)->farg[13]				\
    ? (float) *((LIST)->memfargptr++)					\
    : *(float*)((LIST)->aptr - sizeof(float))				\
  ))
#define va_arg_double(LIST)  \
  (__va_align_double(LIST)						\
   (LIST)->aptr += sizeof(double),					\
   ((LIST)->memfargptr < &(LIST)->farg[13]				\
    ? *((LIST)->memfargptr++)						\
    : *(double*)((LIST)->aptr - sizeof(double))				\
  ))
#endif
#if defined(__powerpc__) && !defined(__powerpc64__) && !(defined(_AIX) || (defined(__MACH__) && defined(__APPLE__)))
/* The first 8 floating-point args have been stored elsewhere. */
#define va_arg_float(LIST)  \
  ((LIST)->memfargptr < &(LIST)->farg[8]				\
   ? (float) *((LIST)->memfargptr++)					\
   : ((LIST)->aptr = ((LIST)->onstack == 0                              \
                       ? ((LIST)->onstack=1, (LIST)->saptr)             \
                       : (LIST)->aptr                                   \
                      ),                                                \
      (LIST)->aptr += sizeof(float),					\
      *(float*)((LIST)->aptr - sizeof(float))				\
  ))
#define va_arg_double(LIST)  \
  ((LIST)->memfargptr < &(LIST)->farg[8]				\
    ? *((LIST)->memfargptr++)						\
    : ((LIST)->aptr = ((LIST)->onstack == 0                             \
                       ? ((LIST)->onstack=1, (LIST)->saptr)             \
                       : (LIST)->aptr                                   \
                      ),                                                \
       __va_align_double(LIST)						\
       (LIST)->aptr += sizeof(double),					\
       *(double*)((LIST)->aptr - sizeof(double))			\
  ))
#endif
#if defined(__powerpc64__)
/* The first 13 floating-point args have been stored elsewhere. */
#define va_arg_float(LIST)  \
  ((LIST)->aptr += sizeof(__vaword),					\
   ((LIST)->memfargptr < &(LIST)->farg[13]				\
    ? (float) *((LIST)->memfargptr++)					\
    : *(float*)((LIST)->aptr - sizeof(float))				\
  ))
#define va_arg_double(LIST)  \
  (__va_align_double(LIST)						\
   (LIST)->aptr += sizeof(double),					\
   ((LIST)->memfargptr < &(LIST)->farg[13]				\
    ? *((LIST)->memfargptr++)						\
    : *(double*)((LIST)->aptr - sizeof(double))				\
  ))
#endif
#if defined(__s390__)
/* The first 2 floating-point args have been stored elsewhere. */
#define va_arg_float(LIST)  \
  ((LIST)->memfargptr < &(LIST)->farg[2]				\
   ? (LIST)->memdargptr++, (float) *((LIST)->memfargptr++)		\
   : ((LIST)->aptr = ((LIST)->onstack == 0                              \
                       ? ((LIST)->onstack=1, (LIST)->saptr)             \
                       : (LIST)->aptr                                   \
                      ),                                                \
      (LIST)->aptr += sizeof(float),					\
      *(float*)((LIST)->aptr - sizeof(float))				\
  ))
#define va_arg_double(LIST)  \
  ((LIST)->memdargptr < &(LIST)->darg[2]				\
    ? (LIST)->memfargptr++, *((LIST)->memdargptr++)			\
    : ((LIST)->aptr = ((LIST)->onstack == 0                             \
                       ? ((LIST)->onstack=1, (LIST)->saptr)             \
                       : (LIST)->aptr                                   \
                      ),                                                \
       __va_align_double(LIST)						\
       (LIST)->aptr += sizeof(double),					\
       *(double*)((LIST)->aptr - sizeof(double))			\
  ))
#endif
#if defined(__ia64__)
/* The first 8 floating-point args have been stored elsewhere. */
#define va_arg_float(LIST)  \
  ((LIST)->aptr += sizeof(__vaword),					\
   ((LIST)->memfargptr < &(LIST)->farg[8]				\
    ? (float) *((LIST)->memfargptr++)					\
    : *(float*)((LIST)->aptr - sizeof(__vaword))			\
  ))
#define va_arg_double(LIST)  \
  (__va_align_double(LIST)						\
   (LIST)->aptr += sizeof(double),					\
   ((LIST)->memfargptr < &(LIST)->farg[8]				\
    ? *((LIST)->memfargptr++)						\
    : *(double*)((LIST)->aptr - sizeof(double))				\
  ))
#endif
#if defined(__x86_64__)
/* The first 8 floating-point args have been stored elsewhere. */
#define va_arg_float(LIST)  \
  ((LIST)->memfargptr < &(LIST)->farg[8]				\
   ? ((LIST)->memfargptr++,						\
      *(float*)((LIST)->memfargptr - 1)					\
     )									\
   : ((LIST)->aptr += sizeof(__vaword),					\
      *(float*)((LIST)->aptr - sizeof(__vaword))			\
  )  )
#define va_arg_double(LIST)  \
  ((LIST)->memfargptr < &(LIST)->farg[8]				\
   ? *(LIST)->memfargptr++						\
   : ((LIST)->aptr += sizeof(__vaword),					\
      *(double*)((LIST)->aptr - sizeof(__vaword))			\
  )  )
#endif
#ifndef va_arg_float
#define va_arg_float(LIST)	__va_arg(LIST,float)
#endif
#ifndef va_arg_double
#define va_arg_double(LIST)  \
  (__va_align_double(LIST) __va_arg(LIST,double))
#endif

/* Pointer arguments. */
#define va_arg_ptr(LIST,TYPE)	__va_arg(LIST,TYPE)

/* Structure arguments. */
#define va_arg_struct(LIST,TYPE)  \
  *(TYPE*)__va_arg_struct(LIST,sizeof(TYPE),__VA_alignof(TYPE))
/* _va_arg_struct() is like va_arg_struct(), except that you pass the type's
 * size and alignment instead of the type and get the value's address instead
 * of the value itself.
 */
#define _va_arg_struct(LIST,TYPE_SIZE,TYPE_ALIGN)  \
  (void*)__va_arg_struct(LIST,TYPE_SIZE,TYPE_ALIGN)
/* Structure argument alignment. */
#if defined(__i386__) && defined(_MSC_VER)
/* In MSVC, doubles inside structures have alignment 8, i.e.
 * __VA_alignof(double) = 8, but doubles (and also structures containing
 * doubles) are passed on the stack with alignment 4. Looks really weird.
 */
#define __va_struct_alignment(TYPE_ALIGN)  \
  ((TYPE_ALIGN) <= 4 ? (TYPE_ALIGN) : 4)
#else
#define __va_struct_alignment(TYPE_ALIGN)  \
  (TYPE_ALIGN)
#endif
#define __va_align_struct(LIST,TYPE_SIZE,TYPE_ALIGN)  \
  (LIST)->aptr = ((LIST)->aptr + __va_struct_alignment(TYPE_ALIGN)-1) & -(long)__va_struct_alignment(TYPE_ALIGN),
#if defined(__i386__) || defined(__m68k__) || defined(__alpha__) || defined(__arm__) || defined(__powerpc64__) || defined(__m88k__) || defined(__convex__) || defined(__x86_64__) || (defined(__ia64__) && defined(__GNUC__) && (__GNUC__ >= 3))
#define __va_arg_struct(LIST,TYPE_SIZE,TYPE_ALIGN)  \
  (__va_align_struct(LIST,TYPE_SIZE,TYPE_ALIGN)				\
   __va_arg_adjusted(LIST,TYPE_SIZE,TYPE_ALIGN)				\
  )
#endif
#if defined(__mips__) && !defined(__mipsn32__) && !defined(__mips64__)
/* small structures < 1 word are adjusted depending on compiler */
#define __va_arg_struct(LIST,TYPE_SIZE,TYPE_ALIGN)  \
  (__va_align_struct(LIST,TYPE_SIZE,TYPE_ALIGN)				\
   ((LIST)->flags & __VA_SGICC_STRUCT_ARGS				\
    ? /* SGI MIPS cc passes small structures left-adjusted, although big-endian! */\
      __va_arg_leftadjusted(LIST,TYPE_SIZE,TYPE_ALIGN)			\
    : /* SGI MIPS gcc passes small structures within the first four words left-	   \
       * adjusted, for compatibility with cc. But structures in memory are passed  \
       * right-adjusted!! See gcc-2.6.3/config/mips/mips.c:function_arg().	   \
       */									   \
      ((LIST)->aptr < (LIST)->memargptr					\
       ? __va_arg_leftadjusted(LIST,TYPE_SIZE,TYPE_ALIGN)		\
       : __va_arg_rightadjusted(LIST,TYPE_SIZE,TYPE_ALIGN)		\
  ))  )
#endif
#if defined(__mipsn32__) || defined(__mips64__)
/* small structures < 1 word are adjusted depending on compiler */
#define __va_arg_struct(LIST,TYPE_SIZE,TYPE_ALIGN)  \
  (__va_align_struct(LIST,TYPE_SIZE,TYPE_ALIGN)				\
   ((LIST)->flags & __VA_SGICC_STRUCT_ARGS				\
    ? /* SGI MIPS cc passes small structures left-adjusted, although big-endian! */\
      __va_arg_leftadjusted(LIST,TYPE_SIZE,TYPE_ALIGN)			\
    : /* SGI MIPS gcc passes small structures right-adjusted. */	\
      __va_arg_rightadjusted(LIST,TYPE_SIZE,TYPE_ALIGN)			\
  ))
#endif
#if defined(__powerpc__) && !defined(__powerpc64__) && (defined(_AIX) || (defined(__MACH__) && defined(__APPLE__)))
/* small structures < 1 word are adjusted depending on compiler */
#define __va_arg_struct(LIST,TYPE_SIZE,TYPE_ALIGN)  \
  (__va_align_struct(LIST,TYPE_SIZE,TYPE_ALIGN)				\
   ((LIST)->flags & __VA_AIXCC_STRUCT_ARGS				\
    ? /* AIX cc and xlc pass small structures left-adjusted, although big-endian! */\
      __va_arg_leftadjusted(LIST,TYPE_SIZE,TYPE_ALIGN)			\
    : /* gcc passes small structures right-adjusted. */			\
      __va_arg_rightadjusted(LIST,TYPE_SIZE,TYPE_ALIGN)			\
  ))
#endif
#if defined(__powerpc__) && !defined(__powerpc64__) && !(defined(_AIX) || (defined(__MACH__) && defined(__APPLE__)))
/* Structures are passed as pointers to caller-made local copies. */
#define __va_arg_struct(LIST,TYPE_SIZE,TYPE_ALIGN)  \
  va_arg_ptr(LIST,void*)
#endif
#if defined(__sparc__) && !defined(__sparc64__)
/* Structures are passed as pointers to caller-made local copies. */
#define __va_arg_struct(LIST,TYPE_SIZE,TYPE_ALIGN)  \
  va_arg_ptr(LIST,void*)
#endif
#if defined(__sparc64__)
/* Small structures are passed left-adjusted, although big-endian! */
/* Big structures are passed as pointers to caller-made local copies. */
#define __va_arg_struct(LIST,TYPE_SIZE,TYPE_ALIGN)  \
  ((TYPE_SIZE) <= 16							\
   ? (__va_align_struct(LIST,TYPE_SIZE,TYPE_ALIGN)			\
      __va_arg_leftadjusted(LIST,TYPE_SIZE,TYPE_ALIGN))			\
   : va_arg_ptr(LIST,void*)						\
  )
#endif
#if defined(__s390__)
/* Structures <= 8 bytes are passed as embedded copies on the arg stack.
 * Big structures are passed as pointers to caller-made local copies.
 */
#define __va_arg_struct(LIST,TYPE_SIZE,TYPE_ALIGN)  \
  ((TYPE_SIZE) != 1 && (TYPE_SIZE) != 2 && (TYPE_SIZE) != 4 && (TYPE_SIZE) != 8 \
   ? va_arg_ptr(LIST,void*)						\
   : (void*)__va_arg_rightadjusted(LIST,TYPE_SIZE,TYPE_ALIGN)		\
  )
#endif
#if defined(__hppa__)
/* Structures <= 8 bytes are passed as embedded copies on the arg stack.
 * Big structures are passed as pointers to caller-made local copies.
 */
#define __va_arg_struct(LIST,TYPE_SIZE,TYPE_ALIGN)  \
  ((TYPE_SIZE) > 8							\
   ? va_arg_ptr(LIST,void*)						\
   : /* FIXME: gcc-2.6.3 passes structures <= 4 bytes in memory left-adjusted! ?? */\
     (void*)__va_arg_rightadjusted(LIST,TYPE_SIZE,TYPE_ALIGN)		\
  )
#endif
#if defined(__ia64__) && (!defined(__GNUC__) || (__GNUC__ < 3))
/* Types larger than a word have 2-word alignment. */
#define __va_arg_struct(LIST,TYPE_SIZE,TYPE_ALIGN)  \
  (__va_align_struct(LIST,TYPE_SIZE,TYPE_ALIGN)				\
   ((TYPE_SIZE) > sizeof(__vaword) && (((__vaword*)(LIST)->aptr - (LIST)->saptr) & 1) ? (LIST)->aptr += sizeof(__vaword) : 0), \
   __va_arg_adjusted(LIST,TYPE_SIZE,TYPE_ALIGN)				\
  )
#endif


/*
 * Definition of the va_return_xxx macros.
 */
#define __va_return(LIST,RETTYPE)  \
  (((LIST)->rtype == (RETTYPE)) || __va_error1((LIST)->rtype,RETTYPE))
#define va_return_void(LIST)  \
  __va_return(LIST,__VAvoid)
#define va_return_char(LIST,VAL)  \
  (__va_return(LIST,__VAchar), (LIST)->tmp._char = (VAL))
#define va_return_schar(LIST,VAL)  \
  (__va_return(LIST,__VAschar), (LIST)->tmp._schar = (VAL))
#define va_return_uchar(LIST,VAL)  \
  (__va_return(LIST,__VAuchar), (LIST)->tmp._uchar = (VAL))
#define va_return_short(LIST,VAL)  \
  (__va_return(LIST,__VAshort), (LIST)->tmp._short = (VAL))
#define va_return_ushort(LIST,VAL)  \
  (__va_return(LIST,__VAushort), (LIST)->tmp._ushort = (VAL))
#define va_return_int(LIST,VAL)  \
  (__va_return(LIST,__VAint), (LIST)->tmp._int = (VAL))
#define va_return_uint(LIST,VAL)  \
  (__va_return(LIST,__VAuint), (LIST)->tmp._uint = (VAL))
#define va_return_long(LIST,VAL)  \
  (__va_return(LIST,__VAlong), (LIST)->tmp._long = (VAL))
#define va_return_ulong(LIST,VAL)  \
  (__va_return(LIST,__VAulong), (LIST)->tmp._ulong = (VAL))
#if defined(__mips64__) || defined(__sparc64__) || defined(__alpha__) || defined(__powerpc64__) || defined(__ia64__) || defined(__x86_64__)
#define va_return_longlong(LIST,VAL)  \
  (__va_return(LIST,__VAlonglong), (LIST)->tmp._long = (VAL))
#define va_return_ulonglong(LIST,VAL)  \
  (__va_return(LIST,__VAulonglong), (LIST)->tmp._ulong = (VAL))
#else
#define va_return_longlong(LIST,VAL)  \
  (__va_return(LIST,__VAlonglong), (LIST)->tmp._longlong = (VAL))
#define va_return_ulonglong(LIST,VAL)  \
  (__va_return(LIST,__VAulonglong), (LIST)->tmp._ulonglong = (VAL))
#endif
#define va_return_float(LIST,VAL)  \
  (__va_return(LIST,__VAfloat), (LIST)->tmp._float = (VAL))
#define va_return_double(LIST,VAL)  \
  (__va_return(LIST,__VAdouble), (LIST)->tmp._double = (VAL))
#define va_return_ptr(LIST,TYPE,VAL)  \
  (__va_return(LIST,__VAvoidp), (LIST)->tmp._ptr = (void*)(TYPE)(VAL))
#define va_return_struct(LIST,TYPE,VAL)  \
  (__va_return(LIST,__VAstruct), *(TYPE*)((LIST)->raddr) = (VAL))
#define _va_return_struct(LIST,TYPE_SIZE,TYPE_ALIGN,VAL_ADDR)  \
  (__va_return(LIST,__VAstruct),					\
   __structcpy((void*)((LIST)->raddr),VAL_ADDR,TYPE_SIZE,TYPE_ALIGN)	\
  )


/* Determine whether a struct type is word-splittable, i.e. whether each of
 * its components fit into a register.
 * The entire computation is done at compile time.
 */
#define va_word_splittable_1(slot1)  \
  (__va_offset1(slot1)/sizeof(__vaword) == (__va_offset1(slot1)+sizeof(slot1)-1)/sizeof(__vaword))
#define va_word_splittable_2(slot1,slot2)  \
  ((__va_offset1(slot1)/sizeof(__vaword) == (__va_offset1(slot1)+sizeof(slot1)-1)/sizeof(__vaword)) \
   && (__va_offset2(slot1,slot2)/sizeof(__vaword) == (__va_offset2(slot1,slot2)+sizeof(slot2)-1)/sizeof(__vaword)) \
  )
#define va_word_splittable_3(slot1,slot2,slot3)  \
  ((__va_offset1(slot1)/sizeof(__vaword) == (__va_offset1(slot1)+sizeof(slot1)-1)/sizeof(__vaword)) \
   && (__va_offset2(slot1,slot2)/sizeof(__vaword) == (__va_offset2(slot1,slot2)+sizeof(slot2)-1)/sizeof(__vaword)) \
   && (__va_offset3(slot1,slot2,slot3)/sizeof(__vaword) == (__va_offset3(slot1,slot2,slot3)+sizeof(slot3)-1)/sizeof(__vaword)) \
  )
#define va_word_splittable_4(slot1,slot2,slot3,slot4)  \
  ((__va_offset1(slot1)/sizeof(__vaword) == (__va_offset1(slot1)+sizeof(slot1)-1)/sizeof(__vaword)) \
   && (__va_offset2(slot1,slot2)/sizeof(__vaword) == (__va_offset2(slot1,slot2)+sizeof(slot2)-1)/sizeof(__vaword)) \
   && (__va_offset3(slot1,slot2,slot3)/sizeof(__vaword) == (__va_offset3(slot1,slot2,slot3)+sizeof(slot3)-1)/sizeof(__vaword)) \
   && (__va_offset4(slot1,slot2,slot3,slot4)/sizeof(__vaword) == (__va_offset4(slot1,slot2,slot3,slot4)+sizeof(slot4)-1)/sizeof(__vaword)) \
  )
#define __va_offset1(slot1)  \
  0
#define __va_offset2(slot1,slot2)  \
  ((__va_offset1(slot1)+sizeof(slot1)+__VA_alignof(slot2)-1) & -(long)__VA_alignof(slot2))
#define __va_offset3(slot1,slot2,slot3)  \
  ((__va_offset2(slot1,slot2)+sizeof(slot2)+__VA_alignof(slot3)-1) & -(long)__VA_alignof(slot3))
#define __va_offset4(slot1,slot2,slot3,slot4)  \
  ((__va_offset3(slot1,slot2,slot3)+sizeof(slot3)+__VA_alignof(slot4)-1) & -(long)__VA_alignof(slot4))


/*
 * Miscellaneous declarations.
 */
#ifdef __cplusplus
extern "C" void __vacall_r (); /* the return type is variable, not void! */
#else
extern void __vacall_r (); /* the return type is variable, not void! */
#endif
extern int __va_error1 (enum __VAtype, enum __VAtype);
extern int __va_error2 (unsigned int);
extern void __structcpy (void* dest, const void* src, unsigned long size, unsigned long alignment);
typedef union { __vaword room[__VA_ALIST_WORDS]; double align; } __va_struct_buffer_t;
extern __va_struct_buffer_t __va_struct_buffer;


#endif /* _VACALL_R_H */
