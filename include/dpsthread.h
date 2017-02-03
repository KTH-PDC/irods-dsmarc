/***********************************************************************
* Tivoli Storage Manager                                               *
* API Client Component                                                 *
*                                                                      *
* (C) Copyright IBM Corporation 1993,2003                              *
***********************************************************************/

/**************************************************************************
* Header File Name: dpsthread.h
*
* Environment:     ************************************************
*                  ** This is a platform-independent source file **
*
*                  ************************************************
*
* Design Notes:    This file contains basic data types and constants
*                  includable by all client source files. The constants
*                  within this file should be set properly for the
*                  particular machine and operating system on which the
*                  client software is to be run.
*
*                  Platform specific definitions are included in dsmapips.h
*
* Descriptive-name: Definitions for Tivoli Storage manager API constants
*-------------------------------------------------------------------------*/
/* threading /mutex functions */

#if _OPSYS_TYPE == DS_WINNT
   /*=== Use native mutexes ===*/
   typedef HANDLE    dpsMutex_t;
   /*=== Windows event handle - a.k.a. condition variables ===*/
   typedef HANDLE    dpsCondition_t;
#elif _OPSYS_TYPE == DS_NETWARE
   #if defined(__NOVELL_LIBC__)
      #include <pthread.h>
      typedef pthread_mutex_t   dpsMutex_t;
      typedef pthread_cond_t    dpsCondition_t;

   #else
   typedef int               dpsMutex_t;
   typedef dsmBool_t         dpsCondition_t;
   #endif
#else
   #include <pthread.h>
   #include <unistd.h>
   typedef pthread_mutex_t   dpsMutex_t;
   typedef pthread_cond_t    dpsCondition_t;
#endif

extern int dpsMutexInit(dpsMutex_t *mutex);
extern int dpsMutexDestroy(dpsMutex_t *mutex);
extern int dpsMutexLock(dpsMutex_t *mutex);
extern int dpsMutexUnlock(dpsMutex_t *mutex);
extern int dpsCreateCondition(dpsCondition_t *condP);
extern int dpsDestroyCondition(dpsCondition_t *condP);
extern int dpsWaitCondition(dpsCondition_t *condP, dpsMutex_t *mutexP);
extern int dpsSignalCondition(dpsCondition_t *condP);
extern int dpsThreadCreate(void *(*func)(void *), void *arg);
