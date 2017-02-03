/***********************************************************************
* Tivoli Storage Manager                                               *
* API Client Component                                                 *
*                                                                      *
* (C) Copyright IBM Corporation 1993,2010                              *
***********************************************************************/

/**************************************************************************
* Header File Name: dsmapips.h
*
* Environment:      *********************************************
*                   ** This is a platform-specific source file **
*                   ** versioned for UNIX                      **
*
*                   *********************************************
*
* Design Notes:     This file includes platform dependent definitions
*
* Descriptive-name: Definitions for Tivoli Storage Manager typedefs and LINKAGE
*-------------------------------------------------------------------------*/

#ifndef _H_DSMAPIPS
#define _H_DSMAPIPS



/*<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>*/
/*                     T Y P E D E F S                                    */
/*<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>*/

#if !defined(DSMAPILIB) || defined(XOPEN_BUILD)

/* support for linkage */
#define DSMLINKAGE

#if defined(_MAC)

   #if __LP64__
   #   define CLC64BIT
   #   define INT_LONG_64
   #else
   #   define _LONG_LONG
   #   define INT_LONG_32
   #endif

#else

   #if defined(_API64) || defined(_AIX5064bit) || defined(_LINUX64)
   #define INT_LONG_64
   #else
   #define INT_LONG_32
   #endif
#endif

#define DS_MACOS    18
#define DS_AIX      12
#if defined(_MAC)

#pragma options align=packed

#define _OPSYS_TYPE DS_MACOS

#else
#define _OPSYS_TYPE DS_AIX
#endif
   typedef          char  dsInt8_t;
   typedef unsigned char  dsUint8_t;
   typedef          short dsInt16_t;
   typedef unsigned short dsUint16_t;
   typedef          int   dsInt32_t;
   typedef unsigned int   dsUint32_t;
   
   typedef unsigned long  dsULong_t;
   typedef          long  dsLong_t;

/*=== Character and string types ===*/
#ifdef UNICODE
  typedef wchar_t dsChar_t;
  #define dsTEXT(x)       L##x
#else
  typedef char dsChar_t;
  #define dsTEXT(x)       x
#endif  /* !UNICODE */

/*=== Common typedefs and defines derived from dsChar_t ===*/
typedef dsChar_t            *dsString_t;

  /* added for the extended restore order */
#ifndef _H_ANSMACH
   typedef struct
   {
      dsUint32_t top;
      dsUint32_t hi_hi;
      dsUint32_t hi_lo;
      dsUint32_t lo_hi;
      dsUint32_t lo_lo;
   } dsUint160_t ;
#endif


/*-------------------------------------------------------------------------+
| Type definition for bool_t                                               |
+-------------------------------------------------------------------------*/
/*
 *  Had to create a Boolean type that didn't clash with any other predefined
 *  version in any operating system or windowing system.
 */
#ifndef _H_ANSMACH
typedef enum
{
      dsmFalse = 0x00,
      dsmTrue  = 0x01
} dsmBool_t ;
#endif


/*===  for backward compatability  ===*/
#define uint8    dsUint8_t
#define int8     dsInt8_t
#define uint16   dsUint16_t
#define int16    dsInt16_t
#define uint32   dsUint32_t
#define int32    dsInt32_t
#ifndef BUILDVMWARE
#define uint64   dsStruct64_t
#endif
#define bool_t   dsBool_t
#define dsBool_t dsmBool_t

#if defined(bTrue)
#undef bTrue
#endif
#define bTrue    dsmTrue

#if defined(bFalse)
#undef bFalse
#endif
#define bFalse   dsmFalse

#ifndef _H_ANSMACH

#if defined(INT_LONG_64)
   typedef long                    dsInt64_t;
   typedef unsigned long           dsUint64_t;
#elif defined(INT_LONG_32)
   typedef long long               dsInt64_t;
   typedef unsigned long long      dsUint64_t;
#else
   typedef struct
   {
      dsUint32_t hi;        /* Most significant 32 bits. */
      dsUint32_t lo;        /* Least significant 32 bits. */
   } dsUint64_t ;
#endif      /* _LONG_LONG  */

typedef struct
   {
      dsUint32_t hi;        /* Most significant 32 bits. */
      dsUint32_t lo;        /* Least significant 32 bits. */
   }dsStruct64_t ;
#endif

#ifdef _MAC
#pragma options align=reset
#endif

#endif /* DSMAPILIB */

#endif  /* _H_DSMAPIPS */

