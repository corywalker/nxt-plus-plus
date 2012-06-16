/*!
   \file platform.h
   \brief This file contains platform-related defines.
*/
/*
   © Copyright 2005,
   National Instruments Corporation.
   All rights reserved.

   File:       platform.h
   Originated: 23 June 2005
*/


#ifndef ___fantom_platform_h___
#define ___fantom_platform_h___

#ifndef __VISATYPE_HEADER__
   #include "visatype.h"
#endif


#define nFANTOM100_kOSMacOSX             0
#define nFANTOM100_kOSWin32              0
   
#define nFANTOM100_kProcessorI386        0
#define nFANTOM100_kProcessorPPC         0
   
#define nFANTOM100_kCompilerMSVC         0
#define nFANTOM100_kCompilerApple        0


#if (( defined( __GNUG__ ) || defined( __GNUC__ )) && defined( __APPLE__ ))
   
   #undef   nFANTOM100_kOSMacOSX
   #define  nFANTOM100_kOSMacOSX         1
   
   #undef   nFANTOM100_kCompilerApple
   #define  nFANTOM100_kCompilerApple    ( __GNUC__ * 10000 \
                                       + __GNUC_MINOR__ * 100 \
                                       + __GNUC_PATCHLEVEL__ )
   
   #if   ( defined( __ppc__ ))
      #undef   nFANTOM100_kProcessorPPC
      #define  nFANTOM100_kProcessorPPC     1
      
      #define nFANTOM100_kBigEndian         1
      #define nFANTOM100_kLittleEndian      0
   #elif ( defined( __i386__ ))
      #undef   nFANTOM100_kProcessorI386
      #define  nFANTOM100_kProcessorI386    1
      
      #define nFANTOM100_kBigEndian         0
      #define nFANTOM100_kLittleEndian      1
   #else
      #error Unknown processor.
   #endif
   
   #ifdef   nFANTOM100_kExportSymbols
      #define nFANTOM100_kExport __attribute__ ((section ("__TEXT,__export")))
   #else
      #define nFANTOM100_kExport
   #endif
   
   
#elif ( defined( _MSC_VER ) && ( defined( _M_IX86 ) || defined( _M_I86 )))
   
   #undef   nFANTOM100_kOSWin32
   #define  nFANTOM100_kOSWin32          1
   
   #undef   nFANTOM100_kCompilerMSVC
   #define  nFANTOM100_kCompilerMSVC    _MSC_VER
   
   #undef   nFANTOM100_kProcessorI386
   #define  nFANTOM100_kProcessorI386    1

   #ifdef   nFANTOM100_kExportSymbols
      #define  nFANTOM100_kExport   __declspec(dllexport)
   #else
      #define  nFANTOM100_kExport   __declspec(dllimport)
   #endif
   
   #define nFANTOM100_kBigEndian         0
   #define nFANTOM100_kLittleEndian      1

#else
   
   #error Unknown platform.
   
#endif


#endif // ___fantom_platform_h___

