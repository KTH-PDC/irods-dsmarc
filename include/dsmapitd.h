/***********************************************************************
* Tivoli Storage Manager                                               *
* API Client Component                                                 *
*                                                                      *
* (C) Copyright IBM Corporation 1993,2010                              *
***********************************************************************/

/**************************************************************************
* Header File Name: dsmapitd.h
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

#ifndef _H_DSMAPITD
#define _H_DSMAPITD


#include "dsmapips.h"      /* Platform specific definitions*/
#include "release.h"

/*=== set the structure alignment to pack the structures ===*/
#if (_OPSYS_TYPE == DS_WINNT) && !defined(_WIN64)
#pragma pack(1)
#endif

#ifdef _MAC
/*=============================================================================
  choices are:
http://developer.apple.com/documentation/DeveloperTools/Conceptual/PowerPCRuntime/Data/chapter_2_section_3.html

#pragma option align=<mode>
where <mode> is power, mac68k, natural, or packed.
=============================================================================*/
#pragma options align=packed
#endif

typedef char osChar_t;

/*<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>*/
/*                     D E F I N E S                                      */
/*<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>*/
/*-------------------------------------------------------------------------+
|  API Version, Release, and Level to use in dsmApiVersion on dsmInit()    |
+-------------------------------------------------------------------------*/
#define DSM_API_VERSION     COMMON_VERSION
#define DSM_API_RELEASE     COMMON_RELEASE
#define DSM_API_LEVEL       COMMON_LEVEL
#define DSM_API_SUBLEVEL    COMMON_SUBLEVEL

/*-------------------------------------------------------------------------+
| Maximum field lengths                                                    |
+-------------------------------------------------------------------------*/
#define DSM_MAX_CG_DEST_LENGTH        30        /* copy group destination */
#define DSM_MAX_CG_NAME_LENGTH        30        /* copy group name        */
#define DSM_MAX_DESCR_LENGTH          255       /* archive description    */
#define DSM_MAX_DOMAIN_LENGTH         30        /* policy domain name     */
#define DSM_MAX_FSINFO_LENGTH         500       /* filespace info         */
#define DSM_MAX_USER_FSINFO_LENGTH    480       /* max user filespace info*/
#define DSM_MAX_FSNAME_LENGTH         1024      /* filespace name         */
#define DSM_MAX_FSTYPE_LENGTH         32        /* filespace type         */
#define DSM_MAX_HL_LENGTH             1024      /* object high level name */
#define DSM_MAX_ID_LENGTH             64        /* session node name      */
#define DSM_MAX_LL_LENGTH             256       /* object low level name  */
#define DSM_MAX_MC_NAME_LENGTH        30        /* management class name  */
#define DSM_MAX_OBJINFO_LENGTH        255       /* object info            */
#define DSM_MAX_OWNER_LENGTH          64        /* object owner name      */
#define DSM_MAX_PLATFORM_LENGTH       16        /* application type       */
#define DSM_MAX_PS_NAME_LENGTH        30        /* policy set name        */
#define DSM_MAX_SERVERTYPE_LENGTH     32        /* server platform type   */
#define DSM_MAX_VERIFIER_LENGTH       64        /* password               */
#define DSM_PATH_MAX                  1024      /* API config file path   */
#define DSM_NAME_MAX                  255       /* API config file name   */
#define DSM_MAX_NODE_LENGTH           64        /* node/machine name      */
#define DSM_MAX_RC_MSG_LENGTH         1024      /* msg parm for dsmRCMsg  */
#define DSM_MAX_SERVER_ADDRESS        1024     /* server address */

#define DSM_MAX_MC_DESCR_LENGTH       DSM_MAX_DESCR_LENGTH /* mgmt class  */
#define DSM_MAX_SERVERNAME_LENGTH     DSM_MAX_ID_LENGTH /* server name    */
#define DSM_MAX_GET_OBJ               4080     /* max objs on BeginGetData */
#define DSM_MAX_PARTIAL_GET_OBJ       1300 /* max partial objs on BeginGetData */
/*-------------------------------------------------------------------------+
| Minimum field lengths                                                    |
+-------------------------------------------------------------------------*/
#define DSM_MIN_COMPRESS_SIZE  2048 /* minimum number of bytes an object  */
                                    /* needs before compression is allowed*/

/*-------------------------------------------------------------------------+
|  Values for mtFlag in dsmSetup call                                      |
+-------------------------------------------------------------------------*/
#define DSM_MULTITHREAD      bTrue
#define DSM_SINGLETHREAD     bFalse

/*-------------------------------------------------------------------------+
|  Values for object type in dsmObjName structure                          |
|  Note: These values must be kept in sync with dsmcomm.h                  |
+-------------------------------------------------------------------------*/
#define DSM_OBJ_FILE                  0x01 /*object has attrib info & data*/
#define DSM_OBJ_DIRECTORY             0x02 /*obj has only attribute info  */
#define DSM_OBJ_RESERVED1             0x04 /* for future use              */
#define DSM_OBJ_RESERVED2             0x05 /* for future use              */
#define DSM_OBJ_RESERVED3             0x06 /* for future use              */
#define DSM_OBJ_WILDCARD              0xFE /* Any object type             */
#define DSM_OBJ_ANY_TYPE              0xFF /* for future use              */

/*-------------------------------------------------------------------------+
| Type definition for compressedState in QryResp                           |
+-------------------------------------------------------------------------*/
#define DSM_OBJ_COMPRESSED_UNKNOWN    0
#define DSM_OBJ_COMPRESSED_YES        1
#define DSM_OBJ_COMPRESSED_NO         2

/*---------------------------------------------------------------------+
| Definitions for "group type" field in tsmGrouphandlerIn_t            |
+---------------------------------------------------------------------*/

#define  DSM_GROUPTYPE_NONE         0x00   /* Not a group member            */
#define  DSM_GROUPTYPE_RESERVED1    0x01   /* for future use                */
#define  DSM_GROUPTYPE_PEER         0x02   /* Peer group                    */
#define  DSM_GROUPTYPE_RESERVED2    0x03   /* for future use                */

/*---------------------------------------------------------------------+
| Definitions for "member type" field in tsmGrouphandlerIn_t           |
+---------------------------------------------------------------------*/

#define  DSM_MEMBERTYPE_LEADER      0x01   /* group leader  */
#define  DSM_MEMBERTYPE_MEMBER      0x02   /* group member  */

/*---------------------------------------------------------------------+
| Definitions for "operation type" field in tsmGrouphandlerIn_t         |
+---------------------------------------------------------------------*/
#define DSM_GROUP_ACTION_BEGIN         0x01
#define DSM_GROUP_ACTION_OPEN          0x02 /* create new group             */
#define DSM_GROUP_ACTION_CLOSE         0x03 /* commit and save an open group */
#define DSM_GROUP_ACTION_ADD           0x04 /* Append to a group */
#define DSM_GROUP_ACTION_ASSIGNTO      0x05 /* Assign to a another group */
#define DSM_GROUP_ACTION_REMOVE        0x06 /* remove a member from a group */

/*-------------------------------------------------------------------------+
| Values for copySer in DetailCG structures for Query Mgmt Class response  |
+-------------------------------------------------------------------------*/
#define Copy_Serial_Static          1   /*Copy Serialization Static       */
#define Copy_Serial_Shared_Static   2   /*Copy Serialization Shared Static*/
#define Copy_Serial_Shared_Dynamic  3   /*Copy Serialization Shared Dynamic*/
#define Copy_Serial_Dynamic         4   /*Copy Serialization Dynamic      */

/*-------------------------------------------------------------------------+
| Values for copyMode in DetailCG structures for Query Mgmt Class response |
+-------------------------------------------------------------------------*/
#define Copy_Mode_Modified          1   /*Copy Mode Modified              */
#define Copy_Mode_Absolute          2   /*Copy Mode Absolute              */

/*-------------------------------------------------------------------------+
|  Values for objState in qryBackupData structure                          |
+-------------------------------------------------------------------------*/
#define DSM_ACTIVE            0x01      /* query only active objects      */
#define DSM_INACTIVE          0x02      /* query only inactive objects    */
#define DSM_ANY_MATCH         0xFF      /* query all backup objects       */

/*-------------------------------------------------------------------------+
| Boundary values for dsmDate.year field in qryArchiveData structure       |
+-------------------------------------------------------------------------*/
#define DATE_MINUS_INFINITE         0x0000      /* lowest boundary        */
#define DATE_PLUS_INFINITE          0xFFFF      /* highest upper boundary */

/*-------------------------------------------------------------------------+
| Bits masks for update action parameter on dsmUpdateFS()                  |
+-------------------------------------------------------------------------*/
#define DSM_FSUPD_FSTYPE              ((unsigned) 0x00000002)
#define DSM_FSUPD_FSINFO              ((unsigned) 0x00000004)
#define DSM_FSUPD_BACKSTARTDATE       ((unsigned) 0x00000008)
#define DSM_FSUPD_BACKCOMPLETEDATE    ((unsigned) 0x00000010)
#define DSM_FSUPD_OCCUPANCY           ((unsigned) 0x00000020)
#define DSM_FSUPD_CAPACITY            ((unsigned) 0x00000040)
#define DSM_FSUPD_RESERVED1           ((unsigned) 0x00000100)

/*-------------------------------------------------------------------------+
| Bits mask  for backup update action parameter on dsmUpdateObj()          |
+-------------------------------------------------------------------------*/
#define DSM_BACKUPD_OWNER              ((unsigned) 0x00000001)
#define DSM_BACKUPD_OBJINFO            ((unsigned) 0x00000002)
#define DSM_BACKUPD_MC                 ((unsigned) 0x00000004)

#define DSM_ARCHUPD_OWNER              ((unsigned) 0x00000001)
#define DSM_ARCHUPD_OBJINFO            ((unsigned) 0x00000002)
#define DSM_ARCHUPD_DESCR              ((unsigned) 0x00000004)

/*-------------------------------------------------------------------------+
|  Values for repository parameter on dsmDeleteFS()                        |
+-------------------------------------------------------------------------*/
#define DSM_ARCHIVE_REP       0x0A      /* archive repository             */
#define DSM_BACKUP_REP        0x0B      /* backup repository              */
#define DSM_REPOS_ALL         0x01      /* all respository types          */

/*-------------------------------------------------------------------------+
|  Values for vote parameter on dsmEndTxn()                                |
+-------------------------------------------------------------------------*/
#define DSM_VOTE_COMMIT  1             /* commit current transaction      */
#define DSM_VOTE_ABORT   2             /* roll back current transaction   */

/*-------------------------------------------------------------------------+
|  Values for various flags returned in ApiSessInfo structure.             |
+-------------------------------------------------------------------------*/
/* Client compression field codes */
#define COMPRESS_YES    1    /* client must compress data             */
#define COMPRESS_NO     2    /* client must NOT compress data         */
#define COMPRESS_CD     3    /* client determined                     */

/* Archive delete permission codes. */
#define ARCHDEL_YES     1    /* archive delete allowed                */
#define ARCHDEL_NO      2    /* archive delete NOT allowed            */

/* Backup delete permission codes. */
#define BACKDEL_YES     1    /* backup delete allowed                 */
#define BACKDEL_NO      2    /* backup delete NOT allowed             */


/*-------------------------------------------------------------------------+
  Values for various flags returned in optStruct structure.             |
-------------------------------------------------------------------------*/
#define DSM_PASSWD_GENERATE  1
#define DSM_PASSWD_PROMPT    0

#define DSM_COMM_TCP        1    /* tcpip         */ 
#define DSM_COMM_NAMEDPIPE  2    /* Named pipes   */
#define DSM_COMM_SHM        3    /* Shared Memory */

/* obsolete commmethods */
#define DSM_COMM_PVM_IUCV   12
#define DSM_COMM_3270       12
#define DSM_COMM_IUCV       12
#define DSM_COMM_PWSCS      12
#define DSM_COMM_SNA_LU6_2  12
#define DSM_COMM_IPXSPX     12    /* For IPX/SPX support */
#define DSM_COMM_NETBIOS    12    /* NETBIOS */
#define DSM_COMM_400COMM    12
#define DSM_COMM_CLIO       12    /* CLIO/S */
/*-------------------------------------------------------------------------+
|  Values for userNameAuthorities in dsmInitEx for future use              |
+-------------------------------------------------------------------------*/
#define DSM_USERAUTH_NONE     ((dsInt16_t)0x0000)
#define DSM_USERAUTH_ACCESS   ((dsInt16_t)0x0001)
#define DSM_USERAUTH_OWNER    ((dsInt16_t)0x0002)
#define DSM_USERAUTH_POLICY   ((dsInt16_t)0x0004)
#define DSM_USERAUTH_SYSTEM   ((dsInt16_t)0x0008)

/*-------------------------------------------------------------------------+
|  Values for encryptionType on dsmEndSendObjEx, queryResp                 |
+-------------------------------------------------------------------------*/
#define DSM_ENCRYPT_NO              ((dsUint8_t)0x00)
#define DSM_ENCRYPT_USER            ((dsUint8_t)0x01)
#define DSM_ENCRYPT_CLIENTENCRKEY   ((dsUint8_t)0x02)
#define DSM_ENCRYPT_DES_56BIT       ((dsUint8_t)0x04)
#define DSM_ENCRYPT_AES_128BIT      ((dsUint8_t)0x08)
/*---------------------------------------------------------------------+
| Definitions for mediaClass field.                                    |
+---------------------------------------------------------------------*/
/*
 *  The following constants define a hierarchy of media access classes.
 *  Lower numbers indicate media which can supply faster access to data.
 */

/* Fixed: represents the class of on-line, fixed media (such as
          hard disks). */
#define  MEDIA_FIXED          0x10

/* Library: represents the class of mountable media accessible
            through a mechanical mounting device. */
#define  MEDIA_LIBRARY        0x20

/* future use */
#define  MEDIA_NETWORK        0x30

/* future use */
#define  MEDIA_SHELF          0x40

/* future use */
#define  MEDIA_OFFSITE        0x50

/* future use */
#define  MEDIA_UNAVAILABLE    0xF0


/*-------------------------------------------------------------------------+
| Type definition for partial object data for dsmBeginGetData()            |
+-------------------------------------------------------------------------*/
typedef struct
{
    dsUint16_t     stVersion;          /* Structure version                     */
    dsStruct64_t   partialObjOffset;   /* offset into object to begin reading   */
    dsStruct64_t   partialObjLength;   /* amount of object to read              */
} PartialObjData ;               /* partial object data                   */

#define PartialObjDataVersion 1  /*                                       */

/*-------------------------------------------------------------------------+
|  Type definition for date structure                                      |
+-------------------------------------------------------------------------*/
typedef struct
{
   dsUint16_t    year;                  /* year, 16-bit integer (e.g., 1990) */
   dsUint8_t     month;                 /* month, 8-bit integer (1 - 12)     */
   dsUint8_t     day;                   /* day. 8-bit integer (1 - 31)       */
   dsUint8_t     hour;                  /* hour, 8-bit integer (0 - 23)      */
   dsUint8_t     minute;                /* minute, 8-bit integer (0 - 59)    */
   dsUint8_t     second;                /* second, b-bit integer (0 - 59)    */
}dsmDate ;

/*-------------------------------------------------------------------------+
|  Type definition for Object ID on dsmGetObj() and in dsmGetList structure|
+-------------------------------------------------------------------------*/
typedef dsStruct64_t  ObjID ;

/*-------------------------------------------------------------------------+
| Type definition for dsmQueryBuff on dsmBeginQuery()                      |
+-------------------------------------------------------------------------*/
typedef void dsmQueryBuff ;

/*-------------------------------------------------------------------------+
| Type definition for dsmGetType parameter on dsmBeginGetData()            |
+-------------------------------------------------------------------------*/
typedef enum
{
        gtBackup = 0x00,                     /* Backup processing type    */
        gtArchive                            /* Archive processing type   */
} dsmGetType ;

/*-------------------------------------------------------------------------+
|  Type definition for dsmQueryType parameter on dsmBeginQuery()           |
+-------------------------------------------------------------------------*/
typedef enum
{
   qtArchive = 0x00,                  /* Archive query type                 */
   qtBackup,                          /* Backup query type                  */
   qtBackupActive,                    /* Fast query for active backup files */
   qtFilespace,                       /* Filespace query type               */
   qtMC,                              /* Mgmt. class query type             */
   qtReserved1,                       /* future use                         */
   qtReserved2,                       /* future use                         */
   qtReserved3,                       /* future use                         */
   qtReserved4,                       /* future use                         */
   qtBackupGroups,                    /* group leaders in a specific fs     */
   qtOpenGroups,                      /* Open groups in a specific fs       */
   qtReserved5,                       /* future use                         */
   qtProxyNodeAuth,                   /* nodes that his node can proxy to   */ 
   qtProxyNodePeer                    /* Peer nodes with the same target    */ 
}dsmQueryType ;

/*-------------------------------------------------------------------------+
|  Type definition sendType parameter on dsmBindMC() and dsmSendObj()      |
+-------------------------------------------------------------------------*/
typedef enum
{
   stBackup = 0x00,                         /* Backup processing type    */
   stArchive,                               /* Archive processing type   */
   stBackupMountWait,           /* Backup processing with mountwait on   */
   stArchiveMountWait           /* Archive processing with mountwait on  */
}dsmSendType ;

/*-------------------------------------------------------------------------+
|  Type definition for delType parameter on dsmDeleteObj()                 |
+-------------------------------------------------------------------------*/
typedef enum
{
   dtArchive = 0x00,                              /* Archive delete type */
   dtBackup,                           /* Backup delete (deactivate) type */
   dtBackupID                         /* Backup delete (remove)     type */
}dsmDelType ;

/*-------------------------------------------------------------------------+
|  Type definition sendType parameter on dsmSetAccess()                    |
+-------------------------------------------------------------------------*/
typedef enum
{
   atBackup = 0x00,                         /* Backup processing type    */
   atArchive                               /* Archive processing type   */
}dsmAccessType;

/*-------------------------------------------------------------------------+
|  Type definition for API Version on dsmInit() and dsmQueryApiVersion()   |
+-------------------------------------------------------------------------*/
typedef struct
{
   dsUint16_t version;       /* API version                      */
   dsUint16_t release;       /* API release                      */
   dsUint16_t level;         /* API level                        */
}dsmApiVersion;

/*-------------------------------------------------------------------------+
|  Type definition for API Version on dsmInit() and dsmQueryApiVersion()   |
+-------------------------------------------------------------------------*/
typedef struct
{
   dsUint16_t stVersion;     /* Structure version                */
   dsUint16_t version;       /* API version                      */
   dsUint16_t release;       /* API release                      */
   dsUint16_t level;         /* API level                        */
   dsUint16_t subLevel;      /* API sub level                    */
   dsmBool_t  unicode;       /* API unicode?                     */
}dsmApiVersionEx;


#define apiVersionExVer       2
/*-------------------------------------------------------------------------+
|  Type definition for object name used on BindMC, Send, Delete, Query     |
+-------------------------------------------------------------------------*/
typedef struct S_dsmObjName
{
   char       fs[DSM_MAX_FSNAME_LENGTH + 1] ;              /* Filespace name */
   char       hl[DSM_MAX_HL_LENGTH + 1] ;                 /* High level name */
   char       ll[DSM_MAX_LL_LENGTH + 1] ;                  /* Low level name */
   dsUint8_t  objType;          /* for object type values, see defines above */
}dsmObjName;


/*-------------------------------------------------------------------------+
|  Type definition for Backup delete info on dsmDeleteObj()                |
+-------------------------------------------------------------------------*/
typedef struct
{
   dsUint16_t       stVersion ;                    /* structure version      */
   dsmObjName       *objNameP ;                    /* object name            */
   dsUint32_t       copyGroup ;                    /* copy group             */
}delBack ;

#define  delBackVersion    1

/*-------------------------------------------------------------------------+
|  Type definition for Archive delete info on dsmDeleteObj()               |
+-------------------------------------------------------------------------*/
typedef struct
{
   dsUint16_t       stVersion ;                    /* structure version      */
   dsStruct64_t       objId ;                        /* object ID              */
}delArch ;

#define  delArchVersion  1

/*-------------------------------------------------------------------------+
|  Type definition for Backup ID delete info on dsmDeleteObj()             |
+-------------------------------------------------------------------------*/
typedef struct
{
   dsUint16_t       stVersion ;                    /* structure version      */
   dsStruct64_t       objId ;                        /* object ID              */
}delBackID;

#define  delBackIDVersion  1

/*-------------------------------------------------------------------------+
|  Type definition for delete info on dsmDeleteObj()                       |
+-------------------------------------------------------------------------*/
typedef union
{
   delBack   backInfo ;
   delArch   archInfo ;
   delBackID backIDInfo ;
}dsmDelInfo ;

/*-------------------------------------------------------------------------+
|  Type definition for Object Attribute parameter on dsmSendObj()          |
+-------------------------------------------------------------------------*/
typedef struct
{
   dsUint16_t   stVersion;                       /* Structure version */
   char         owner[DSM_MAX_OWNER_LENGTH + 1]; /* object owner */
   dsStruct64_t sizeEstimate;                    /* Size estimate in bytes of the object */
   dsmBool_t    objCompressed;                   /* Is object already compressed? */
   dsUint16_t   objInfoLength;                   /* length of object-dependent info */
   char         *objInfo;                        /* object-dependent info */
   char         *mcNameP;                        /* mgmnt class name for override  */
   dsmBool_t    disableDeduplication;                /* force no dedup for this object */
}ObjAttr;

#define ObjAttrVersion  3


/*-------------------------------------------------------------------------+
| Type definition for mcBindKey returned on dsmBindMC()                    |
+-------------------------------------------------------------------------*/
typedef struct
{
   dsUint16_t  stVersion;                   /* structure version          */
   char        mcName[DSM_MAX_MC_NAME_LENGTH + 1];
                                           /* Name of mc bound to object. */
   dsmBool_t   backup_cg_exists;                            /* True/false */
   dsmBool_t   archive_cg_exists;                           /* True/false */
   char        backup_copy_dest[DSM_MAX_CG_DEST_LENGTH + 1];
                                                /* Backup copy dest. name */
   char        archive_copy_dest[DSM_MAX_CG_DEST_LENGTH + 1];
                                                    /* Arch copy dest.name */
}mcBindKey;

#define mcBindKeyVersion  1


/*-------------------------------------------------------------------------+
| Type definition for object list on dsmBeginGetData()                     |
+-------------------------------------------------------------------------*/
typedef struct
{
   dsUint16_t       stVersion ;         /* structure version            */
   dsUint32_t       numObjId ;          /* number of object IDs in the list */
   ObjID           *objId ;             /* list of object IDs to restore*/
   PartialObjData  *partialObjData;     /*list of partial obj data info */
}dsmGetList ;

#define dsmGetListVersion     2  /* default if not using Partial Obj data */
#define dsmGetListPORVersion  3  /* version if using Partial Obj data     */

/*-------------------------------------------------------------------------+
|  Type definition for DataBlk used to Get or Send data                    |
+-------------------------------------------------------------------------*/
typedef struct
{
   dsUint16_t stVersion ;                /* structure version            */
   dsUint32_t bufferLen;                 /* Length of buffer passed below */
   dsUint32_t numBytes;                  /* Actual number of bytes read from */
                                         /* or written to the buffer */
   char       *bufferPtr;                /* Data buffer */
   dsUint32_t numBytesCompressed;        /* on send actual bytes compressed */
}DataBlk;

#define DataBlkVersion  2


/*-------------------------------------------------------------------------+
|  Type definition for Mgmt Class queryBuffer on dsmBeginQuery()           |
+-------------------------------------------------------------------------*/
typedef struct S_qryMCData
{
   dsUint16_t   stVersion;                              /* structure version */
   char         *mcName;                       /* Mgmt class name */
                         /* single name to get one or empty string to get all*/
   dsmBool_t    mcDetail;                            /* Want details or not? */
}qryMCData;

#define qryMCDataVersion  1

/*=== values for RETINIT ===*/
#define ARCH_RETINIT_CREATE 0
#define ARCH_RETINIT_EVENT  1

/*-------------------------------------------------------------------------+
|  Type definition for Archive Copy Group details on Query MC response     |
+-------------------------------------------------------------------------*/
typedef struct S_archDetailCG
{
   char         cgName[DSM_MAX_CG_NAME_LENGTH + 1];       /* Copy group name */
   dsUint16_t   frequency;                       /* Copy (archive) frequency */
   dsUint16_t   retainVers;                                /* Retain version */
   dsUint8_t    copySer;       /* for copy serialization values, see defines */
   dsUint8_t    copyMode;         /* for copy mode values, see defines above */
   char         destName[DSM_MAX_CG_DEST_LENGTH + 1];      /* Copy dest name */
   dsmBool_t    bLanFreeDest;            /* Destination has lan free path?   */
   dsmBool_t    reserved;                /* Not currently used               */
   dsUint8_t    retainInit;              /* possible values see above        */
   dsUint16_t   retainMin;               /* if retInit is EVENT num of days  */
   dsmBool_t    bDeduplicate;            /* destination has dedup enabled    */
}archDetailCG;

/*-------------------------------------------------------------------------+
|  Type definition for Backup Copy Group details on Query MC response      |
+-------------------------------------------------------------------------*/
typedef struct S_backupDetailCG
{
   char         cgName[DSM_MAX_CG_NAME_LENGTH + 1];       /* Copy group name */
   dsUint16_t   frequency;                               /* Backup frequency */
   dsUint16_t   verDataExst;                         /* Versions data exists */
   dsUint16_t   verDataDltd;                        /* Versions data deleted */
   dsUint16_t   retXtraVers;                        /* Retain extra versions */
   dsUint16_t   retOnlyVers;                         /* Retain only versions */
   dsUint8_t    copySer;       /* for copy serialization values, see defines */
   dsUint8_t    copyMode;         /* for copy mode values, see defines above */
   char         destName[DSM_MAX_CG_DEST_LENGTH + 1];      /* Copy dest name */
   dsmBool_t    bLanFreeDest;            /* Destination has lan free path?   */
   dsmBool_t    reserved;                /* Not currently used               */
   dsmBool_t    bDeduplicate;            /* destination has dedup enabled    */
}backupDetailCG;


/*-------------------------------------------------------------------------+
|  Type definition for Query Mgmt Class detail response on dsmGetNextQObj()|
+-------------------------------------------------------------------------*/
typedef struct S_qryRespMCDetailData
{
   dsUint16_t      stVersion;                       /* structure version */
   char            mcName[DSM_MAX_MC_NAME_LENGTH + 1];        /* mc name */
   char            mcDesc[DSM_MAX_MC_DESCR_LENGTH + 1]; /*mc description */
   archDetailCG    archDet;                 /* Archive copy group detail */
   backupDetailCG  backupDet;                /* Backup copy group detail */
}qryRespMCDetailData;

#define qryRespMCDetailDataVersion  4

/*-------------------------------------------------------------------------+
| Type definition for Query Mgmt Class summary response on dsmGetNextQObj()|
+-------------------------------------------------------------------------*/
typedef struct S_qryRespMCData
{
   dsUint16_t   stVersion;                              /* structure version */
   char         mcName[DSM_MAX_MC_NAME_LENGTH + 1];               /* mc name */
   char         mcDesc[DSM_MAX_MC_DESCR_LENGTH + 1];       /* mc description */
}qryRespMCData;

#define qryRespMCDataVersion  1



/*-------------------------------------------------------------------------+
|  Type definition for Archive queryBuffer on dsmBeginQuery()              |
+-------------------------------------------------------------------------*/
typedef struct S_qryArchiveData
{
   dsUint16_t   stVersion;                          /* structure version */
   dsmObjName   *objName;                     /* Full dsm name of object */
   char         *owner;                                    /* owner name */
                       /* for maximum date boundaries, see defines above */
   dsmDate      insDateLowerBound;      /* low bound archive insert date */
   dsmDate      insDateUpperBound;       /* hi bound archive insert date */
   dsmDate      expDateLowerBound;          /* low bound expiration date */
   dsmDate      expDateUpperBound;           /* hi bound expiration date */
   char         *descr;                /* archive description */
} qryArchiveData;

#define qryArchiveDataVersion  1



/*=== values for retentionInitiated field ===*/
#define DSM_ARCH_RETINIT_UNKNOWN 0 /* ret init is unknown (down-level srv)  */
#define DSM_ARCH_RETINIT_STARTED 1 /* retention clock is started            */
#define DSM_ARCH_RETINIT_PENDING 2 /* retention clock is not started        */


/*=== Values for objHeld ===*/
#define DSM_ARCH_HELD_UNKNOWN 0    /* unknown hold status (down-level srv)  */
#define DSM_ARCH_HELD_FALSE   1    /* object is NOT in a delete hold state  */
#define DSM_ARCH_HELD_TRUE    2    /* object is in a delete hold state      */

/*-------------------------------------------------------------------------+
| Type definition for Query Archive response on dsmGetNextQObj()           |
+-------------------------------------------------------------------------*/
typedef struct S_qryRespArchiveData
{
   dsUint16_t      stVersion;                           /* structure version */
   dsmObjName      objName;                      /* Filespace name qualifier */
   dsUint32_t      copyGroup;                           /* copy group number */
   char            mcName[DSM_MAX_MC_NAME_LENGTH + 1];            /* mc name */
   char            owner[DSM_MAX_OWNER_LENGTH + 1];            /* owner name */
   dsStruct64_t    objId;                                  /* Unique copy id */
   dsStruct64_t    reserved;                       /* backward compatability */
   dsUint8_t       mediaClass;                         /* media access class */
   dsmDate         insDate;                        /* archive insertion date */
   dsmDate         expDate;                    /* expiration date for object */
   char            descr[DSM_MAX_DESCR_LENGTH + 1];   /* archive description */
   dsUint16_t      objInfolen;             /* length of object-dependent info*/
   char            objInfo[DSM_MAX_OBJINFO_LENGTH];  /*object-dependent info */
   dsUint160_t     restoreOrderExt;                         /* restore order */
   dsStruct64_t    sizeEstimate;              /* size estimate stored by user*/
   dsUint8_t       compressType;                          /* Compression flag*/
   dsUint8_t       retentionInitiated;   /* object waiting on retention event*/
   dsUint8_t       objHeld;  /*object is on retention "hold" see values above*/   
   dsUint8_t       encryptionType;                     /* type of encryption */
   dsmBool_t       clientDeduplicated;             /* obj deduplicated by API*/      
}qryRespArchiveData;

#define qryRespArchiveDataVersion  6

/*-------------------------------------------------------------------------+
|  Type definition for Archive sendBuff parameter on dsmSendObj()          |
+-------------------------------------------------------------------------*/
typedef struct S_sndArchiveData
{
   dsUint16_t   stVersion;                   /* structure version */
   char         *descr;                    /* archive description */
}sndArchiveData;

#define sndArchiveDataVersion  1

/*-------------------------------------------------------------------------+
|  Type definition for Backup queryBuffer on dsmBeginQuery()               |
+-------------------------------------------------------------------------*/
typedef struct S_qryBackupData
{
   dsUint16_t  stVersion;         /* structure version */
   dsmObjName  *objName;          /* full dsm name of object */
   char        *owner;            /* owner name */
   dsUint8_t   objState;          /* object state selector */
   dsmDate     pitDate;           /* Date value for point in time restore */
                                  /* for possible values, see defines above */
}qryBackupData;

#define qryBackupDataVersion  2

typedef struct                             
{
  dsUint8_t    reserved1;
  dsStruct64_t reserved2;
} reservedInfo_t;                 /* for future use */

/*-------------------------------------------------------------------------+
| Type definition for Query Backup response on dsmGetNextQObj()            |
+-------------------------------------------------------------------------*/
typedef struct S_qryRespBackupData
{
   dsUint16_t      stVersion;                           /* structure version */
   dsmObjName      objName;                       /* full dsm name of object */
   dsUint32_t      copyGroup;                           /* copy group number */
   char            mcName[DSM_MAX_MC_NAME_LENGTH + 1];            /* mc name */
   char            owner[DSM_MAX_OWNER_LENGTH + 1];            /* owner name */
   dsStruct64_t    objId;                                /* Unique object id */
   dsStruct64_t    reserved;                       /* backward compatability */
   dsUint8_t       mediaClass;                         /* media access class */
   dsUint8_t       objState;                      /* Obj state, active, etc. */
   dsmDate         insDate;                         /* backup insertion date */
   dsmDate         expDate;                    /* expiration date for object */
   dsUint16_t      objInfolen;             /* length of object-dependent info*/
   char            objInfo[DSM_MAX_OBJINFO_LENGTH];  /*object-dependent info */
   dsUint160_t     restoreOrderExt;                         /* restore order */
   dsStruct64_t    sizeEstimate;             /* size estimate stored by user */
   dsStruct64_t    baseObjId;
   dsUint16_t      baseObjInfolen;             /* length of base object-dependent info*/
   dsUint8_t       baseObjInfo[DSM_MAX_OBJINFO_LENGTH];  /* base object-dependent info */
   dsUint160_t     baseRestoreOrder;                         /* restore order */
   dsUint32_t      fsID;
   dsUint8_t       compressType;
   dsmBool_t       isGroupLeader;
   dsmBool_t       isOpenGroup;
   dsUint8_t       reserved1;               /* for future use */
   dsmBool_t       reserved2;               /* for future use */
   dsUint16_t      reserved3;               /* for future use */
   reservedInfo_t  *reserved4;              /* for future use */
   dsUint8_t       encryptionType;          /* type of encryption */
   dsmBool_t       clientDeduplicated;      /* obj deduplicated by API*/      
}qryRespBackupData;

#define qryRespBackupDataVersion  7

/*-------------------------------------------------------------------------+
|  Type definition for Active Backup queryBuffer on dsmBeginQuery()
|
|  Notes:  For the active backup query, only the fs (filespace) and objType
|          fields of objName need be set.  objType can only be set to
|          DSM_OBJ_FILE or DSM_OBJ_DIRECTORY.  DSM_OBJ_ANY_TYPE will not
|          find a match on the query.
+-------------------------------------------------------------------------*/
typedef struct S_qryABackupData
{
   dsUint16_t      stVersion;                           /* structure version */
   dsmObjName      *objName;                     /* Only fs and objtype used */
}qryABackupData;

#define qryABackupDataVersion  1

/*-------------------------------------------------------------------------+
| Type definition for Query Active Backup response on dsmGetNextQObj()     |
+-------------------------------------------------------------------------*/
typedef struct S_qryARespBackupData
{
   dsUint16_t  stVersion;                           /* structure version */
   dsmObjName  objName;                       /* full dsm name of object */
   dsUint32_t  copyGroup;                           /* copy group number */
   char        mcName[DSM_MAX_MC_NAME_LENGTH + 1];/*management class name*/
   char        owner[DSM_MAX_OWNER_LENGTH + 1];            /* owner name */
   dsmDate     insDate;                         /* backup insertion date */
   dsUint16_t  objInfolen;             /* length of object-dependent info*/
   char        objInfo[DSM_MAX_OBJINFO_LENGTH];  /*object-dependent info */
}qryARespBackupData;

#define qryARespBackupDataVersion  1

/*-------------------------------------------------------------------------+
|  Type definition for Backup queryBuffer on dsmBeginQuery()               |
+-------------------------------------------------------------------------*/
typedef struct qryBackupGroups
{
   dsUint16_t   stVersion;         /* structure version */
   dsUint8_t    groupType;
   char         *fsName;
   char         *owner;
   dsStruct64_t groupLeaderObjId;
   dsUint8_t    objType;
}qryBackupGroups;

#define qryBackupGroupsVersion 1


/*-------------------------------------------------------------------------+
|  Type definition for proxynode queryBuffer on dsmBeginQuery()            |
+-------------------------------------------------------------------------*/
typedef struct qryProxyNodeData
{
   dsUint16_t  stVersion;                   /* structure version */
   char        *targetNodeName;             /* target node name  */
}qryProxyNodeData;

#define qryProxyNodeDataVersion  1

/*-------------------------------------------------------------------------+
| Type definition for qryRespProxyNodeData  parameter used on dsmGetNextQObj()|
+-------------------------------------------------------------------------*/

typedef struct
{
   dsUint16_t      stVersion ;                          /* structure version */
   char            targetNodeName[DSM_MAX_ID_LENGTH+1]; /* target node name  */
   char            peerNodeName[DSM_MAX_ID_LENGTH+1];   /* Peer node name    */
   char            hlAddress[DSM_MAX_ID_LENGTH+1];      /* peer hlAddress    */
   char            llAddress[DSM_MAX_ID_LENGTH+1];      /* peer hlAddress    */ 
}qryRespProxyNodeData;

#define qryRespProxyNodeDataVersion  1


/*-------------------------------------------------------------------------+
|  Type definition for WINNT and OS/2 Filespace attributes                 |
+-------------------------------------------------------------------------*/
typedef struct
{
   char         driveLetter ;          /* drive letter for filespace    */
   dsUint16_t   fsInfoLength;          /* fsInfo length used            */
   char         fsInfo[DSM_MAX_FSINFO_LENGTH];/*caller-determined data  */
}dsmDosFSAttrib ;

/*-------------------------------------------------------------------------+
|  Type definition for UNIX Filespace attributes                           |
+-------------------------------------------------------------------------*/
typedef struct
{
   dsUint16_t   fsInfoLength;          /* fsInfo length used            */
   char         fsInfo[DSM_MAX_FSINFO_LENGTH];/*caller-determined data  */
}dsmUnixFSAttrib ;

/*-------------------------------------------------------------------------+
|  Type definition for NetWare Filespace attributes                        |
+-------------------------------------------------------------------------*/
typedef dsmUnixFSAttrib dsmNetwareFSAttrib;

/*-------------------------------------------------------------------------+
|  Type definition for Filespace attributes on all Filespace calls         |
+-------------------------------------------------------------------------*/
typedef union
{
   dsmNetwareFSAttrib  netwareFSAttr;
   dsmUnixFSAttrib     unixFSAttr ;
   dsmDosFSAttrib      dosFSAttr ;
}dsmFSAttr ;

/*-------------------------------------------------------------------------+
|  Type definition for fsUpd parameter on dsmUpdateFS()
+-------------------------------------------------------------------------*/
typedef struct S_dsmFSUpd
{
   dsUint16_t      stVersion ;             /* structure version              */
   char            *fsType ;               /* filespace type                 */
   dsStruct64_t    occupancy ;             /* occupancy estimate             */
   dsStruct64_t    capacity  ;             /* capacity estimate              */
   dsmFSAttr       fsAttr ;                /* platform specific attributes   */
}dsmFSUpd ;

#define dsmFSUpdVersion  1

/*-------------------------------------------------------------------------+
|  Type definition for Filespace queryBuffer on dsmBeginQuery()            |
+-------------------------------------------------------------------------*/
typedef struct S_qryFSData
{
   dsUint16_t  stVersion;                 /* structure version */
   char        *fsName;                   /* File space name */
}qryFSData;

#define qryFSDataVersion  1

/*-------------------------------------------------------------------------+
| Type definition for Query Filespace response on dsmGetNextQObj()         |
+-------------------------------------------------------------------------*/
typedef struct S_qryRespFSData
{
   dsUint16_t     stVersion;                              /* structure version */
   char           fsName[DSM_MAX_FSNAME_LENGTH + 1];         /* Filespace name */
   char           fsType[DSM_MAX_FSTYPE_LENGTH + 1] ;        /* Filespace type */
   dsStruct64_t   occupancy;                       /* Occupancy est. in bytes. */
   dsStruct64_t   capacity;                         /* Capacity est. in bytes. */
   dsmFSAttr      fsAttr ;                    /* platform specific attributes  */
   dsmDate        backStartDate;              /* start backup date             */
   dsmDate        backCompleteDate;           /* end backup Date               */
   dsmDate        reserved1;                   /* For future use                */
}qryRespFSData;

#define qryRespFSDataVersion 3

/*-------------------------------------------------------------------------+
|  Type definition for regFilespace parameter on dsmRegisterFS()
+-------------------------------------------------------------------------*/
typedef struct S_regFSData
{
   dsUint16_t      stVersion;                             /* structure version */
   char            *fsName;                        /* Filespace name */
   char            *fsType;                        /* Filespace type */
   dsStruct64_t    occupancy;                      /* Occupancy est. in bytes. */
   dsStruct64_t    capacity;                        /* Capacity est. in bytes. */
   dsmFSAttr       fsAttr ;                    /* platform specific attributes */
}regFSData;

#define regFSDataVersion  1

/*-------------------------------------------------------------------------+
| Type definition for dedupType used in apisessInfo                          |
+-------------------------------------------------------------------------*/
typedef enum
{
   dedupServerOnly= 0x00,             /* dedup only done on server    */
   dedupClientOrServer               /* dedup can be done on client or server */
}dsmDedupType ;
/*-------------------------------------------------------------------------+
|  Type definition for session info response on dsmQuerySessionInfo()      |
+-------------------------------------------------------------------------*/
typedef struct
{
   dsUint16_t     stVersion;              /* Structure version                */
      /*------------------------------------------------------------------*/
      /*           Server information                                     */
      /*------------------------------------------------------------------*/
   char           serverHost[DSM_MAX_SERVERNAME_LENGTH+1];
                                      /* Network host name of DSM server  */
   dsUint16_t     serverPort;             /* Server comm port on host         */
   dsmDate        serverDate;             /* Server's date/time               */
   char           serverType[DSM_MAX_SERVERTYPE_LENGTH+1];
                                     /* Server's execution platform      */
   dsUint16_t     serverVer;              /* Server's version number          */
   dsUint16_t     serverRel;              /* Server's release number          */
   dsUint16_t     serverLev;              /* Server's level number            */
   dsUint16_t     serverSubLev;           /* Server's sublevel number         */
      /*------------------------------------------------------------------*/
      /*           Client Defaults                                        */
      /*------------------------------------------------------------------*/
   char           nodeType[DSM_MAX_PLATFORM_LENGTH+1]; /*node/application type*/
   char           fsdelim;                /* File space delimiter             */
   char           hldelim;                /* Delimiter betw highlev & lowlev  */
   dsUint8_t      compression;            /* Compression flag                 */
   dsUint8_t      archDel;                /* Archive delete permission        */
   dsUint8_t      backDel;                /* Backup  delete permission        */
   dsUint32_t     maxBytesPerTxn;         /* for future use                   */
   dsUint16_t     maxObjPerTxn;           /* The max objects allowed in a txn */
      /*------------------------------------------------------------------*/
      /*           Session Information                                    */
      /*------------------------------------------------------------------*/
   char       id[DSM_MAX_ID_LENGTH+1];    /* Sign-in id node name         */
   char       owner[DSM_MAX_OWNER_LENGTH+1]; /* Sign-in owner             */
                                      /*   (for multi-user platforms)     */
   char       confFile[DSM_PATH_MAX + DSM_NAME_MAX +1];
                                     /* len is platform dep              */
                                     /* dsInit name of appl config file  */
   dsUint8_t  opNoTrace;              /* dsInit option - NoTrace = 1      */
      /*------------------------------------------------------------------*/
      /*           Policy Data                                            */
      /*------------------------------------------------------------------*/
   char           domainName[DSM_MAX_DOMAIN_LENGTH+1]; /* Domain name         */
   char           policySetName[DSM_MAX_PS_NAME_LENGTH+1];
                                      /* Active policy set name           */
   dsmDate        polActDate;             /* Policy set activation date       */
   char           dfltMCName[DSM_MAX_MC_NAME_LENGTH+1];/* Default Mgmt Class  */
   dsUint16_t     gpBackRetn;             /* Grace-period backup retention    */
   dsUint16_t     gpArchRetn;             /* Grace-period archive retention   */
   char           adsmServerName[DSM_MAX_SERVERNAME_LENGTH+1]; /* adsm server name */
   dsmBool_t      archiveRetentionProtection; /* is server Retention protection enabled */
   dsStruct64_t   maxBytesPerTxn_64;         /* for future use                 */
   dsmBool_t      lanFreeEnabled;            /* lan free option is set         */
   dsmDedupType   dedupType;                 /* server or clientOrServer       */
   char           accessNode[DSM_MAX_ID_LENGTH+1];    /* as node node name         */
}ApiSessInfo;

#define ApiSessInfoVersion  5

/*-------------------------------------------------------------------------+
| Type definition for Query options response on dsmQueryCliOptions()       |
|      and dsmQuerySessOptions()                                           |
+-------------------------------------------------------------------------*/

typedef struct
{
   char        dsmiDir[DSM_PATH_MAX + DSM_NAME_MAX +1];
   char        dsmiConfig[DSM_PATH_MAX + DSM_NAME_MAX +1];
   char        serverName[DSM_MAX_SERVERNAME_LENGTH+1];
   dsInt16_t   commMethod;
   char        serverAddress[DSM_MAX_SERVER_ADDRESS];
   char        nodeName[DSM_MAX_NODE_LENGTH+1];
   dsmBool_t   compression;
   dsmBool_t   compressalways;
   dsmBool_t   passwordAccess;
}optStruct ;

/*-------------------------------------------------------------------------+
| Type definition for LogType used in logInfo                              |
+-------------------------------------------------------------------------*/
typedef enum
{
   logServer = 0x00,             /* log msg only to server    */
   logLocal,                     /* log msg only to local error log */
   logBoth,                       /* log msg to server and to local error log */
   logNone
}dsmLogType ;

/*-------------------------------------------------------------------------+
| Type definition for logInfo parameter used on dsmLogEvent()              |
+-------------------------------------------------------------------------*/

typedef struct
{
   char        *message;   /* text of message to be logged */
   dsmLogType  logType;    /* log type : local, server, both */
}logInfo;

/*-------------------------------------------------------------------------+
| Type definition for qryRespAccessData  parameter used on dsmQueryAccess()|
+-------------------------------------------------------------------------*/

typedef struct
{
   dsUint16_t        stVersion ;                    /* structure version      */
   char              node[DSM_MAX_ID_LENGTH+1];     /* node name              */
   char              owner[DSM_MAX_OWNER_LENGTH+1]; /* owner                  */
   dsmObjName        objName ;                      /* object name            */
   dsmAccessType     accessType;                    /* archive or backup     */
   dsUint32_t        ruleNumber ;                   /* Access rule id         */
}qryRespAccessData;

#define qryRespAccessDataVersion  1

/*-------------------------------------------------------------------------+
|  Type definition for envSetUp parameter on dsmSetUp()
+-------------------------------------------------------------------------*/
typedef struct S_envSetUp
{
   dsUint16_t      stVersion;                      /* structure version */
   char            dsmiDir[DSM_PATH_MAX + DSM_NAME_MAX +1];
   char            dsmiConfig[DSM_PATH_MAX + DSM_NAME_MAX +1];
   char            dsmiLog[DSM_PATH_MAX + DSM_NAME_MAX +1];
   char          **argv;  /* for executables name argv[0] */
   char            logName[DSM_NAME_MAX +1];
   dsmBool_t       reserved1;         /* for future use */
   dsmBool_t       reserved2;                  /* for future use */
}envSetUp;

#define envSetUpVersion  4

/*-------------------------------------------------------------------------+
|  Type definition for dsmInitExIn_t
+-------------------------------------------------------------------------*/
typedef struct dsmInitExIn_t
{
   dsUint16_t         stVersion;                      /* structure version */
   dsmApiVersionEx    *apiVersionExP;
   char               *clientNodeNameP;
   char               *clientOwnerNameP;
   char               *clientPasswordP;
   char               *userNameP;
   char               *userPasswordP;
   char               *applicationTypeP;
   char               *configfile;
   char               *options;
   char               dirDelimiter;
   dsmBool_t          useUnicode;
   dsmBool_t          bCrossPlatform;
   dsmBool_t          bService;
   dsmBool_t          bEncryptKeyEnabled;
   char               *encryptionPasswordP;
   dsmBool_t          useTsmBuffers;
   dsUint8_t          numTsmBuffers;
}dsmInitExIn_t;

#define dsmInitExInVersion 4

/*-------------------------------------------------------------------------+
|  Type definition for dsmInitExOut_t
+-------------------------------------------------------------------------*/
typedef struct dsmInitExOut_t
{
   dsUint16_t         stVersion;                    /* structure version */
   dsInt16_t          userNameAuthorities;
   dsInt16_t          infoRC;        /* error return code if encountered */
   char               adsmServerName[DSM_MAX_SERVERNAME_LENGTH+1];
   dsUint16_t         serverVer;     /* Server's version number          */
   dsUint16_t         serverRel;     /* Server's release number          */
   dsUint16_t         serverLev;     /* Server's level number            */
   dsUint16_t         serverSubLev;  /* Server's sublevel number         */
}dsmInitExOut_t;

#define dsmInitExOutVersion 2

/*-------------------------------------------------------------------------+
| Type definition for LogType used in logInfo                              |
+-------------------------------------------------------------------------*/
typedef enum
{
   logSevInfo = 0x00,       /* information ANE4991 */
   logSevWarning,           /* warning     ANE4992 */
   logSevError,             /* Error       ANE4993 */
   logSevSevere,            /* severe      ANE4994 */
   logSevLicense,           /* License     ANE4995 */
   logSevTryBuy             /* try Buy     ANE4996 */
}dsmLogSeverity ;


/*-------------------------------------------------------------------------+
|  Type definition for dsmLogExIn_t
+-------------------------------------------------------------------------*/
typedef struct dsmLogExIn_t
{
   dsUint16_t         stVersion;  /* structure version */
   dsmLogSeverity     severity;
   char               appMsgID[8];
   dsmLogType         logType;    /* log type : local, server, both */
   char               *message;   /* text of message to be logged */
   char               appName[DSM_MAX_PLATFORM_LENGTH];
   char               osPlatform[DSM_MAX_PLATFORM_LENGTH];
   char               appVersion[DSM_MAX_PLATFORM_LENGTH];
}dsmLogExIn_t;

#define dsmLogExInVersion 2

/*-------------------------------------------------------------------------+
|  Type definition for dsmlogExOut_t
+-------------------------------------------------------------------------*/
typedef struct dsmLogExOut_t
{
   dsUint16_t         stVersion;  /* structure version */
}dsmLogExOut_t;

#define dsmLogExOutVersion 1

/*-------------------------------------------------------------------------+
|  Type definition for dsmRenameIn_t
+-------------------------------------------------------------------------*/
typedef struct dsmRenameIn_t
{
   dsUint16_t       stVersion;                     /* structure version  */
   dsUint32_t       dsmHandle;                     /* handle for session */
   dsUint8_t        repository;                    /* Backup or Archive  */
   dsmObjName       *objNameP ;                    /* object name */
   char             newHl[DSM_MAX_HL_LENGTH + 1];  /* new High level name */
   char             newLl[DSM_MAX_LL_LENGTH + 1];  /* new Low level name */
   dsmBool_t        merge;                        /* merge into existing name*/
   ObjID            objId;                         /* objId for Archive */
}dsmRenameIn_t;

#define dsmRenameInVersion 1

/*-------------------------------------------------------------------------+
|  Type definition for dsmRenameOut_t
+-------------------------------------------------------------------------*/
typedef struct dsmRenameOut_t
{
   dsUint16_t         stVersion;                      /* structure version */
}dsmRenameOut_t;

#define dsmRenameOutVersion 1

/*-------------------------------------------------------------------------+
|  Type definition for dsmEndSendObjExIn_t
+-------------------------------------------------------------------------*/
typedef struct dsmEndSendObjExIn_t
{
   dsUint16_t       stVersion;                     /* structure version  */
   dsUint32_t       dsmHandle;                     /* handle for session */
}dsmEndSendObjExIn_t;

#define dsmEndSendObjExInVersion 1

/*-------------------------------------------------------------------------+
|  Type definition for dsmEndSendObjExOut_t
+-------------------------------------------------------------------------*/
typedef struct dsmEndSendObjExOut_t
{
   dsUint16_t         stVersion;           /* structure version */
   dsStruct64_t       totalBytesSent;      /* total bytes read from app */
   dsmBool_t          objCompressed;       /* was object compressed */
   dsStruct64_t       totalCompressSize;   /* total size after compress */
   dsStruct64_t       totalLFBytesSent;    /* total bytes sent Lan Free */
   dsUint8_t          encryptionType;      /* type of encryption used   */
   dsmBool_t          objDeduplicated;     /* was object processed for dist. data dedup */
   dsStruct64_t       totalDedupSize;      /* total size after de-dup */
}dsmEndSendObjExOut_t;

#define dsmEndSendObjExOutVersion 3
/*-------------------------------------------------------------------------+
|  Type definition for dsmGroupHandlerIn_t
+-------------------------------------------------------------------------*/
typedef struct dsmGroupHandlerIn_t
{
   dsUint16_t      stVersion;        /* structure version  */
   dsUint32_t      dsmHandle;        /* handle for session */
   dsUint8_t       groupType;        /* Type of group                            */
   dsUint8_t       actionType;       /* Type of group operation                  */
   dsUint8_t       memberType;       /* Type of member: Leader or member         */
   dsStruct64_t    leaderObjId;      /* OBJID of the groupleader when manipulating a member */
   char            *uniqueGroupTagP; /* Unique group identifier                  */
   dsmObjName      *objNameP ;       /* group leader object name */
   dsmGetList      memberObjList;    /* list of objects to remove, assign        */
}dsmGroupHandlerIn_t;

#define dsmGroupHandlerInVersion 1

/*-------------------------------------------------------------------------+
|  Type definition for dsmGroupHandlerExOut_t
+-------------------------------------------------------------------------*/
typedef struct dsmGroupHandlerOut_t
{
   dsUint16_t         stVersion;                      /* structure version */
}dsmGroupHandlerOut_t;

#define dsmGroupHandlerOutVersion 1

/*-------------------------------------------------------------------------+
|  Type definition for dsmEndTxnExIn_t
+-------------------------------------------------------------------------*/
typedef struct dsmEndTxnExIn_t
{
   dsUint16_t       stVersion;                     /* structure version  */
   dsUint32_t       dsmHandle;                     /* handle for session */
   dsUint8_t        vote;
}dsmEndTxnExIn_t;

#define dsmEndTxnExInVersion 1

/*-------------------------------------------------------------------------+
|  Type definition for dsmEndTxnExOut_t
+-------------------------------------------------------------------------*/
typedef struct dsmEndTxnExOut_t
{
   dsUint16_t         stVersion;               /* structure version              */
   dsUint16_t         reason;                  /* reason code                    */
   dsStruct64_t       groupLeaderObjId;        /* groupLeader obj id returned on */
                                               /* DSM_ACTION_OPEN                */
   dsUint8_t          reserved1;               /* future use                     */
   dsUint16_t         reserved2;               /* future use                     */
}dsmEndTxnExOut_t;

#define dsmEndTxnExOutVersion 1

/*-------------------------------------------------------------------------+
|  Type definition for dsmEndGetDataExIn_t
+-------------------------------------------------------------------------*/
typedef struct dsmEndGetDataExIn_t
{
   dsUint16_t     stVersion;     /* structure version  */
   dsUint32_t     dsmHandle;     /* handle for session */
}dsmEndGetDataExIn_t;

#define dsmEndGetDataExInVersion 1

/*-------------------------------------------------------------------------+
|  Type definition for dsmEndGetDataExOut_t
+-------------------------------------------------------------------------*/
typedef struct dsmEndGetDataExOut_t
{
   dsUint16_t     stVersion;         /* structure version             */
   dsUint16_t     reason;            /* reason code                   */
   dsStruct64_t   totalLFBytesRecv;  /* total lan free bytes recieved */
}dsmEndGetDataExOut_t;

#define dsmEndGetDataExOutVersion 1

/*-------------------------------------------------------------------------+
| Type definition for object list on dsmRetentionEvent()                   |
+-------------------------------------------------------------------------*/
typedef struct dsmObjList
{
   dsUint16_t       stVersion;         /* structure version                */
   dsUint32_t       numObjId;          /* number of object IDs in the list */
   ObjID            *objId;            /* list of object IDs to signal     */
}dsmObjList_t ;

#define dsmObjlistVersion 1

/*-------------------------------------------------------------------------+
| Type definition eventType used on dsmRetentionEvent                      |
+--------------------------------------------------------------------------*/
typedef enum
{
   eventRetentionActivate = 0x00,   /* signal the server that the event has occured */
   eventHoldObj,                    /* suspend delete/expire of the object          */
   eventReleaseObj                  /* Resume normal delete/expire processing       */
}dsmEventType_t;

/*-------------------------------------------------------------------------+
|  Type definition for  on dsmRetentionEvent()                             |
+-------------------------------------------------------------------------*/
typedef struct dsmRetentionEventIn_t
{
   dsUint16_t         stVersion;                    /* structure version  */
   dsUint32_t         dsmHandle;                    /* session Handle     */
   dsmEventType_t     eventType;                    /* Event type         */
   dsmObjList_t       objList;                      /* object ID          */
}dsmRetentionEventIn_t;

#define dsmRetentionEventInVersion 1

/*-------------------------------------------------------------------------+
|  Type definition for  on dsmRetentionEvent()               |
+-------------------------------------------------------------------------*/
typedef struct dsmRetentionEventOut_t
{
   dsUint16_t       stVersion ;                    /* structure version      */
}dsmRetentionEventOut_t;

#define dsmRetentionEventOutVersion 1


/*-------------------------------------------------------------------------+
|  Type definition for  on dsmRequestBuffer()                                  |
+-------------------------------------------------------------------------*/
typedef struct requestBufferIn_t
{
   dsUint16_t         stVersion;                    /* structure version  */
   dsUint32_t         dsmHandle;                    /* session Handle     */
}requestBufferIn_t;

#define requestBufferInVersion 1

/*-------------------------------------------------------------------------+
|  Type definition for  on dsmRequestBuffer()                                  |
+-------------------------------------------------------------------------*/
typedef struct requestBufferOut_t
{
   dsUint16_t       stVersion ;                /* structure version */
   dsUint8_t        tsmBufferHandle;           /* handle to tsm Data buffer */
   char             *dataPtr;                  /* Address to write data to */
   dsUint32_t       bufferLen;                 /* Max length of data to be written */
}requestBufferOut_t;

#define requestBufferOutVersion 1

/*-------------------------------------------------------------------------+
|  Type definition for  on dsmReleaseBuffer()                               |
+-------------------------------------------------------------------------*/
typedef struct releaseBufferIn_t
{
   dsUint16_t         stVersion;                    /* structure version  */
   dsUint32_t         dsmHandle;                    /* session Handle     */
   dsUint8_t          tsmBufferHandle;              /* handle to tsm Data buffer */
   char               *dataPtr;                     /* Address to write data to */
}releaseBufferIn_t;

#define releaseBufferInVersion 1

/*-------------------------------------------------------------------------+
|  Type definition for  on dsmReleaseBuffer()                               |
+-------------------------------------------------------------------------*/
typedef struct releaseBufferOut_t
{
   dsUint16_t       stVersion ;                    /* structure version */
}releaseBufferOut_t;

#define releaseBufferOutVersion 1

/*-------------------------------------------------------------------------+
|  Type definition for  on dsmGetBufferData()                                  |
+-------------------------------------------------------------------------*/
typedef struct getBufferDataIn_t
{
   dsUint16_t         stVersion;                    /* structure version  */
   dsUint32_t         dsmHandle;                    /* session Handle     */
}getBufferDataIn_t;

#define getBufferDataInVersion 1

/*-------------------------------------------------------------------------+
|  Type definition for  on dsmGetBufferData()                                    |
+-------------------------------------------------------------------------*/
typedef struct getBufferDataOut_t
{
   dsUint16_t       stVersion ;            /* structure version */
   dsUint8_t        tsmBufferHandle;       /* handle to tsm Data buffer */
   char             *dataPtr;              /* Address of actual data to read */
   dsUint32_t       numBytes;              /* Actual number of bytes to read from dataPtr*/
}getBufferDataOut_t;

#define getBufferDataOutVersion 1

/*-------------------------------------------------------------------------+
|  Type definition for  on dsmSendBufferData()                                 |
+-------------------------------------------------------------------------*/
typedef struct sendBufferDataIn_t
{
   dsUint16_t         stVersion;             /* structure version  */
   dsUint32_t         dsmHandle;             /* session Handle     */
   dsUint8_t          tsmBufferHandle;       /* handle to tsm Data buffer */
   char               *dataPtr;              /* Address of actual data to send */
   dsUint32_t         numBytes;              /* Actual number of bytes to send from dataPtr*/
}sendBufferDataIn_t;

#define sendBufferDataInVersion 1

/*-------------------------------------------------------------------------+
|  Type definition for  on dsmSendBufferData()                                 |
+-------------------------------------------------------------------------*/
typedef struct sendBufferDataOut_t
{
   dsUint16_t       stVersion ;            /* structure version */
}sendBufferDataOut_t;

#define sendBufferDataOutVersion 1

/*-------------------------------------------------------------------------+
|  Type definition for dsmUpdateObjExIn_t
+-------------------------------------------------------------------------*/
typedef struct dsmUpdateObjExIn_t
{
   dsUint16_t      stVersion;            /* structure version */
   dsUint32_t      dsmHandle;            /* session Handle      */ 
   dsmSendType     sendType;             /* send type back/arch */
   char            *descrP;              /* archive description */
   dsmObjName      *objNameP;            /* objName             */
   ObjAttr         *objAttrPtr;          /* attribute           */
   dsUint32_t      objUpdAct;            /* update action       */
   ObjID           archObjId;            /* objId for archive   */
}dsmUpdateObjExIn_t;

#define dsmUpdateObjExInVersion 1

/*-------------------------------------------------------------------------+
|  Type definition for dsmUpdateObjExOut_t
+-------------------------------------------------------------------------*/
typedef struct dsmUpdateObjExOut_t
{
    dsUint16_t         stVersion;        /* structure version */ 
}dsmUpdateObjExOut_t;

#define dsmUpdateObjExOutVersion 1

#if (_OPSYS_TYPE == DS_WINNT) && !defined(_WIN64)
#pragma pack()
#endif


#ifdef _MAC
#pragma options align=reset
#endif
#endif /* _H_DSMAPITD */



