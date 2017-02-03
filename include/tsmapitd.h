/***********************************************************************
* Tivoli Storage Manager                                               *
* API Client Component                                                 *
*                                                                      *
* (C) Copyright IBM Corporation 1993,2010                              *
***********************************************************************/

/**************************************************************************
* Header File Name: tsmapitd.h
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

#ifndef _H_TSMAPITD
#define _H_TSMAPITD


/*=== set the structure alignment to pack the structures ===*/
#if _OPSYS_TYPE == DS_WINNT
#ifdef _WIN64
#pragma pack(8)
#else
#pragma pack(1)
#endif
#endif

#ifdef _MAC
#pragma options align = packed
#endif

/*==============================================================
   Win32 applications using the tsm interface must use the
   -DUNICODE flag during compilation.
==============================================================*/
#if _OPSYS_TYPE == DS_WINNT && !defined(DSMAPILIB)
#ifndef UNICODE
#error "Win32 applications using the TSM interface MUST be compiled with the -DUNICODE flag"
#endif
#endif

/*==============================================================
   Mac OS X applications using the tsm interface must use the
   -DUNICODE flag during compilation.
==============================================================*/
#if _OPSYS_TYPE == DS_MACOS && !defined(DSMAPILIB)
#ifndef UNICODE
#error "Mac OS X applications using the TSM interface MUST be compiled with the -DUNICODE flag"
#endif
#endif

/*-------------------------------------------------------------------------+
| Type definition for dsmGetType parameter on tsmBeginGetData()            |
+-------------------------------------------------------------------------*/
typedef enum
{
    gtTsmBackup = 0x00,                     /* Backup processing type    */
    gtTsmArchive                            /* Archive processing type   */
} tsmGetType ;

/*-------------------------------------------------------------------------+
|  Type definition for dsmQueryType parameter on tsmBeginQuery()           |
+-------------------------------------------------------------------------*/
typedef enum
{
    qtTsmArchive = 0x00,                     /* Archive query type        */
    qtTsmBackup,                             /* Backup query type         */
    qtTsmBackupActive,                       /* Fast query for active backup files */
    qtTsmFilespace,                          /* Filespace query type      */
    qtTsmMC,                                 /* Mgmt. class query type    */
    qtTsmReserved1,                          /* future use                */
    qtTsmReserved2,                          /* future use                */
    qtTsmReserved3,                          /* future use                */
    qtTsmReserved4,                          /* future use                */
    qtTsmBackupGroups,                       /* All group leaders in a specific filespace */
    qtTsmOpenGroups,                         /* All group members associated with a leader */
    qtTsmReserved5,                          /* future use                */
    qtTsmProxyNodeAuth,                      /* nodes that this node can proxy to   */ 
    qtTsmProxyNodePeer                       /* peer nodes under this target node  */ 
} tsmQueryType ;

/*-------------------------------------------------------------------------+
|  Type definition sendType parameter on tsmBindMC() and tsmSendObj()      |
+-------------------------------------------------------------------------*/
typedef enum
{
    stTsmBackup = 0x00,                         /* Backup processing type    */
    stTsmArchive,                               /* Archive processing type   */
    stTsmBackupMountWait,           /* Backup processing with mountwait on   */
    stTsmArchiveMountWait           /* Archive processing with mountwait on  */
} tsmSendType ;

/*-------------------------------------------------------------------------+
|  Type definition for delType parameter on tsmDeleteObj()                 |
+-------------------------------------------------------------------------*/
typedef enum
{
    dtTsmArchive = 0x00,                              /* Archive delete type */
    dtTsmBackup,                           /* Backup delete (deactivate) type */
    dtTsmBackupID                         /* Backup delete (remove)     type */
} tsmDelType ;

/*-------------------------------------------------------------------------+
|  Type definition sendType parameter on tsmSetAccess()                    |
+-------------------------------------------------------------------------*/
typedef enum
{
    atTsmBackup = 0x00,                         /* Backup processing type    */
    atTsmArchive                               /* Archive processing type   */
}tsmAccessType;

/*-------------------------------------------------------------------------+
|  Type definition for Overwrite  parameter on tsmSendObj()                              |
+-------------------------------------------------------------------------*/
typedef enum
{
    owIGNORE = 0x00,
    owYES,
    owNO
}tsmOwType;


/*-------------------------------------------------------------------------+
|  Type definition for API Version on tsmInit() and tsmQueryApiVersion()   |
+-------------------------------------------------------------------------*/
typedef struct
{
        dsUint16_t stVersion;     /* Structure version                */
        dsUint16_t version;       /* API version                      */
        dsUint16_t release;       /* API release                      */
        dsUint16_t level;         /* API level                        */
        dsUint16_t subLevel;      /* API sub level                    */
        dsmBool_t  unicode;       /* API unicode?                     */
} tsmApiVersionEx;


#define tsmApiVersionExVer       2

/*-------------------------------------------------------------------------+
|  Type definition for object name used on BindMC, Send, Delete, Query     |
+-------------------------------------------------------------------------*/

typedef struct tsmObjName
{
    dsChar_t   fs[DSM_MAX_FSNAME_LENGTH + 1] ;              /* Filespace name */
    dsChar_t   hl[DSM_MAX_HL_LENGTH + 1] ;                 /* High level name */
    dsChar_t   ll[DSM_MAX_LL_LENGTH + 1] ;                  /* Low level name */
    dsUint8_t  objType;          /* for object type values, see defines above */
    dsChar_t   dirDelimiter;
} tsmObjName;

/*-------------------------------------------------------------------------+
|  Type definition for Backup delete info on dsmDeleteObj()                |
+-------------------------------------------------------------------------*/
typedef struct tsmDelBack
{
    dsUint16_t       stVersion ;                    /* structure version      */
    tsmObjName       *objNameP ;                    /* object name            */
    dsUint32_t       copyGroup ;                    /* copy group             */
} tsmDelBack ;

#define  tsmDelBackVersion    1

/*-------------------------------------------------------------------------+
|  Type definition for Archive delete info on dsmDeleteObj()               |
+-------------------------------------------------------------------------*/
typedef struct
{
    dsUint16_t       stVersion ;                    /* structure version      */
    dsStruct64_t     objId ;                        /* object ID              */
} tsmDelArch ;

#define  tsmDelArchVersion  1

/*-------------------------------------------------------------------------+
|  Type definition for Backup ID delete info on dsmDeleteObj()             |
+-------------------------------------------------------------------------*/
typedef struct
{
    dsUint16_t       stVersion ;                    /* structure version      */
    dsStruct64_t       objId ;                        /* object ID              */
} tsmDelBackID;

#define  tsmDelBackIDVersion  1


/*-------------------------------------------------------------------------+
|  Type definition for delete info on dsmDeleteObj()                       |
+-------------------------------------------------------------------------*/
typedef union
{
    tsmDelBack   backInfo ;
    tsmDelArch   archInfo ;
    tsmDelBackID backIDInfo;
} tsmDelInfo ;

/*-------------------------------------------------------------------------+
|  Type definition for Object Attribute parameter on dsmSendObj()          |
+-------------------------------------------------------------------------*/
typedef struct tsmObjAttr
{
    dsUint16_t   stVersion;                /* Structure version                 */
    dsChar_t     owner[DSM_MAX_OWNER_LENGTH + 1];      /* object owner          */
    dsStruct64_t sizeEstimate;             /* Size estimate in bytes of the object */
    dsmBool_t    objCompressed;            /* Is object already compressed?     */
    dsUint16_t   objInfoLength;            /* length of object-dependent info   */
    char         *objInfo;                 /* object-dependent info byte buffer */
    dsChar_t     *mcNameP;                 /* mgmnt class name for override     */
    tsmOwType    reserved1;                /* for future use                    */
    tsmOwType    reserved2;                /* for future use                    */
    dsmBool_t    disableDeduplication;         /* force no dedup for this object    */
} tsmObjAttr;

#define tsmObjAttrVersion 4
/*-------------------------------------------------------------------------+
| Type definition for mcBindKey returned on dsmBindMC()                    |
+-------------------------------------------------------------------------*/
typedef struct tsmMcBindKey
{
    dsUint16_t  stVersion;                   /* structure version          */
    dsChar_t    mcName[DSM_MAX_MC_NAME_LENGTH + 1];
                                            /* Name of mc bound to object. */
    dsmBool_t   backup_cg_exists;                            /* True/false */
    dsmBool_t   archive_cg_exists;                           /* True/false */
    dsChar_t    backup_copy_dest[DSM_MAX_CG_DEST_LENGTH + 1];
                                                 /* Backup copy dest. name */
    dsChar_t    archive_copy_dest[DSM_MAX_CG_DEST_LENGTH + 1];
                                                     /* Arch copy dest.name */
} tsmMcBindKey;

#define tsmMcBindKeyVersion  1


/*-------------------------------------------------------------------------+
|  Type definition for Mgmt Class queryBuffer on dsmBeginQuery()           |
+-------------------------------------------------------------------------*/
typedef struct tsmQryMCData
{
    dsUint16_t   stVersion;                              /* structure version */
    dsChar_t     *mcName;                       /* Mgmt class name */
                          /* single name to get one or empty string to get all*/
    dsmBool_t    mcDetail;                            /* Want details or not? */
} tsmQryMCData;

#define tsmQryMCDataVersion  1


/*-------------------------------------------------------------------------+
|  Type definition for Archive Copy Group details on Query MC response     |
+-------------------------------------------------------------------------*/
typedef struct tsmArchDetailCG
{
   dsChar_t     cgName[DSM_MAX_CG_NAME_LENGTH + 1];     /* Copy group name */
   dsUint16_t   frequency;                     /* Copy (archive) frequency */
   dsUint16_t   retainVers;                              /* Retain version */
   dsUint8_t    copySer;     /* for copy serialization values, see defines */
   dsUint8_t    copyMode;       /* for copy mode values, see defines above */
   dsChar_t     destName[DSM_MAX_CG_DEST_LENGTH + 1];    /* Copy dest name */
   dsmBool_t    bLanFreeDest;         /* Destination has lan free path?    */
   dsmBool_t    reserved;                            /* Not currently used */
   dsUint8_t    retainInit;             /* possible values see dsmapitd.h  */
   dsUint16_t   retainMin;              /* if retInit is EVENT num of days */
   dsmBool_t    bDeduplicate;             /* destination has dedup enabled  */
}tsmArchDetailCG;

/*-------------------------------------------------------------------------+
|  Type definition for Backup Copy Group details on Query MC response      |
+-------------------------------------------------------------------------*/
typedef struct tsmBackupDetailCG
{
   dsChar_t     cgName[DSM_MAX_CG_NAME_LENGTH + 1];       /* Copy group name */
   dsUint16_t   frequency;                               /* Backup frequency */
   dsUint16_t   verDataExst;                         /* Versions data exists */
   dsUint16_t   verDataDltd;                        /* Versions data deleted */
   dsUint16_t   retXtraVers;                        /* Retain extra versions */
   dsUint16_t   retOnlyVers;                         /* Retain only versions */
   dsUint8_t    copySer;       /* for copy serialization values, see defines */
   dsUint8_t    copyMode;         /* for copy mode values, see defines above */
   dsChar_t     destName[DSM_MAX_CG_DEST_LENGTH + 1];      /* Copy dest name */
   dsmBool_t    bLanFreeDest;           /* Destination has lan free path?    */
   dsmBool_t    reserved;                              /* Not currently used */
   dsmBool_t    bDeduplicate;             /* destination has dedup enabled   */
}tsmBackupDetailCG;


/*-------------------------------------------------------------------------+
|  Type definition for Query Mgmt Class detail response on dsmGetNextQObj()|
+-------------------------------------------------------------------------*/
typedef struct tsmQryRespMCDetailData
{
    dsUint16_t      stVersion;                       /* structure version */
    dsChar_t        mcName[DSM_MAX_MC_NAME_LENGTH + 1];        /* mc name */
    dsChar_t        mcDesc[DSM_MAX_MC_DESCR_LENGTH + 1]; /*mc description */
    archDetailCG    archDet;                 /* Archive copy group detail */
    backupDetailCG  backupDet;                /* Backup copy group detail */
} tsmQryRespMCDetailData;

#define tsmQryRespMCDetailDataVersion  4

/*-------------------------------------------------------------------------+
| Type definition for Query Mgmt Class summary response on dsmGetNextQObj()|
+-------------------------------------------------------------------------*/
typedef struct tsmQryRespMCData
{
    dsUint16_t   stVersion;                              /* structure version */
    dsChar_t     mcName[DSM_MAX_MC_NAME_LENGTH + 1];               /* mc name */
    dsChar_t     mcDesc[DSM_MAX_MC_DESCR_LENGTH + 1];       /* mc description */
}tsmQryRespMCData;

#define tsmQryRespMCDataVersion  1

/*-------------------------------------------------------------------------+
|  Type definition for Archive queryBuffer on tsmBeginQuery()              |
+-------------------------------------------------------------------------*/
typedef struct tsmQryArchiveData
{
    dsUint16_t   stVersion;                          /* structure version */
    tsmObjName   *objName;                     /* Full dsm name of object */
    dsChar_t     *owner;                                    /* owner name */
                        /* for maximum date boundaries, see defines above */
    dsmDate      insDateLowerBound;      /* low bound archive insert date */
    dsmDate      insDateUpperBound;       /* hi bound archive insert date */
    dsmDate      expDateLowerBound;          /* low bound expiration date */
    dsmDate      expDateUpperBound;           /* hi bound expiration date */
    dsChar_t     *descr;                /* archive description */
} tsmQryArchiveData;

#define tsmQryArchiveDataVersion  1

/*-------------------------------------------------------------------------+
| Type definition for Query Archive response on dsmGetNextQObj()           |
+-------------------------------------------------------------------------*/
typedef struct tsmQryRespArchiveData
{
    dsUint16_t      stVersion;                           /* structure version */
    tsmObjName      objName;                      /* Filespace name qualifier */
    dsUint32_t      copyGroup;                           /* copy group number */
    dsChar_t        mcName[DSM_MAX_MC_NAME_LENGTH + 1];            /* mc name */
    dsChar_t        owner[DSM_MAX_OWNER_LENGTH + 1];            /* owner name */
    dsStruct64_t    objId;                                  /* Unique copy id */
    dsStruct64_t    reserved;                       /* backward compatability */
    dsUint8_t       mediaClass;                         /* media access class */
    dsmDate         insDate;                        /* archive insertion date */
    dsmDate         expDate;                    /* expiration date for object */
    dsChar_t        descr[DSM_MAX_DESCR_LENGTH + 1];   /* archive description */
    dsUint16_t      objInfolen;            /* length of object-dependent info */
    dsUint8_t       objInfo[DSM_MAX_OBJINFO_LENGTH];  /*object-dependent info */
    dsUint160_t     restoreOrderExt;                         /* restore order */
    dsStruct64_t    sizeEstimate;             /* size estimate stored by user */
    dsUint8_t       compressType;                         /* Compression flag */
    dsUint8_t       retentionInitiated;   /* object waiting on retention event*/
    dsUint8_t       objHeld; /* object is on "hold" see dsmapitd.h for values */  
    dsUint8_t       encryptionType;                     /* type of encryption */
    dsmBool_t       clientDeduplicated;             /* obj deduplicated by API*/      
} tsmQryRespArchiveData;

#define tsmQryRespArchiveDataVersion  6

/*-------------------------------------------------------------------------+
|  Type definition for Archive sendBuff parameter on dsmSendObj()          |
+-------------------------------------------------------------------------*/
typedef struct tsmSndArchiveData
{
    dsUint16_t   stVersion;                   /* structure version */
    dsChar_t     *descr;                    /* archive description */
} tsmSndArchiveData;

#define tsmSndArchiveDataVersion  1

/*-------------------------------------------------------------------------+
|  Type definition for Backup queryBuffer on dsmBeginQuery()               |
+-------------------------------------------------------------------------*/
typedef struct tsmQryBackupData
{
    dsUint16_t  stVersion;         /* structure version */
    tsmObjName  *objName;          /* full dsm name of object */
    dsChar_t    *owner;            /* owner name */
    dsUint8_t   objState;          /* object state selector */
    dsmDate     pitDate;           /* Date value for point in time restore */
                                   /* for possible values, see defines above */
    dsUint32_t  reserved1;
    dsUint32_t  reserved2;
} tsmQryBackupData;

#define tsmQryBackupDataVersion  3

/*-------------------------------------------------------------------------+
| Type definition for Query Backup response on dsmGetNextQObj()            |
+-------------------------------------------------------------------------*/
typedef struct tsmQryRespBackupData
{
    dsUint16_t      stVersion;                           /* structure version */
    tsmObjName      objName;                       /* full dsm name of object */
    dsUint32_t      copyGroup;                           /* copy group number */
    dsChar_t        mcName[DSM_MAX_MC_NAME_LENGTH + 1];            /* mc name */
    dsChar_t        owner[DSM_MAX_OWNER_LENGTH + 1];            /* owner name */
    dsStruct64_t    objId;                                /* Unique object id */
    dsStruct64_t    reserved;                       /* backward compatability */
    dsUint8_t       mediaClass;                         /* media access class */
    dsUint8_t       objState;                      /* Obj state, active, etc. */
    dsmDate         insDate;                         /* backup insertion date */
    dsmDate         expDate;                    /* expiration date for object */
    dsUint16_t      objInfolen;             /* length of object-dependent info*/
    dsUint8_t       objInfo[DSM_MAX_OBJINFO_LENGTH];  /*object-dependent info */
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
} tsmQryRespBackupData;

#define tsmQryRespBackupDataVersion  7

/*-------------------------------------------------------------------------+
|  Type definition for Active Backup queryBuffer on dsmBeginQuery()
|
|  Notes:  For the active backup query, only the fs (filespace) and objType
|          fields of objName need be set.  objType can only be set to
|          DSM_OBJ_FILE or DSM_OBJ_DIRECTORY.  DSM_OBJ_ANY_TYPE will not
|          find a match on the query.
+-------------------------------------------------------------------------*/
typedef struct tsmQryABackupData
{
    dsUint16_t      stVersion;                           /* structure version */
    tsmObjName      *objName;                     /* Only fs and objtype used */
} tsmQryABackupData;

#define tsmQryABackupDataVersion  1

/*-------------------------------------------------------------------------+
| Type definition for Query Active Backup response on dsmGetNextQObj()     |
+-------------------------------------------------------------------------*/
typedef struct tsmQryARespBackupData
{
    dsUint16_t  stVersion;                           /* structure version */
    tsmObjName  objName;                       /* full dsm name of object */
    dsUint32_t  copyGroup;                           /* copy group number */
    dsChar_t    mcName[DSM_MAX_MC_NAME_LENGTH + 1];/*management class name*/
    dsChar_t    owner[DSM_MAX_OWNER_LENGTH + 1];            /* owner name */
    dsmDate     insDate;                         /* backup insertion date */
    dsUint16_t  objInfolen;             /* length of object-dependent info*/
    dsUint8_t   objInfo[DSM_MAX_OBJINFO_LENGTH];  /*object-dependent info */
} tsmQryARespBackupData;

#define tsmQryARespBackupDataVersion  1

/*-------------------------------------------------------------------------+
|  Type definition for Backup queryBuffer on dsmBeginQuery()               |
+-------------------------------------------------------------------------*/
typedef struct tsmQryBackupGroups
{
    dsUint16_t   stVersion;         /* structure version */
    dsUint8_t    groupType;
    dsChar_t     *fsName;
    dsChar_t     *owner;
    dsStruct64_t groupLeaderObjId;
    dsUint8_t    objType;
    dsUint32_t   reserved1;
    dsUint32_t   reserverd2;
} tsmQryBackupGroups;

#define tsmQryBackupGroupsVersion 2

/*-------------------------------------------------------------------------+
|  Type definition for proxynode queryBuffer on tsmBeginQuery()            |
+-------------------------------------------------------------------------*/
typedef struct tsmQryProxyNodeData
{
   dsUint16_t  stVersion;                   /* structure version */
   dsChar_t    *targetNodeName;             /* target node name      */
}tsmQryProxyNodeData;

#define tsmQryProxyNodeDataVersion  1

/*-------------------------------------------------------------------------+
| Type definition for qryRespProxyNodeData  parameter used on tsmGetNextQObj()|
+-------------------------------------------------------------------------*/

typedef struct tsmQryRespProxyNodeData
{
   dsUint16_t        stVersion ;                           /* structure version */
   dsChar_t          targetNodeName[DSM_MAX_ID_LENGTH+1];  /* target node name  */
   dsChar_t          peerNodeName[DSM_MAX_ID_LENGTH+1];    /* peer node name    */
   dsChar_t          hlAddress[DSM_MAX_ID_LENGTH+1];       /* peer hlAddress    */
   dsChar_t          llAddress[DSM_MAX_ID_LENGTH+1];       /* peer llAddress    */
}tsmQryRespProxyNodeData;

#define tsmQryRespProxyNodeDataVersion  1

/*-------------------------------------------------------------------------+
|  Type definition for WINNT and OS/2 Filespace attributes                 |
+-------------------------------------------------------------------------*/
typedef struct tsmDosFSAttrib
{
    osChar_t     driveLetter ;          /* drive letter for filespace    */
    dsUint16_t   fsInfoLength;          /* fsInfo length used            */
    osChar_t     fsInfo[DSM_MAX_FSINFO_LENGTH];/*caller-determined data  */
} tsmDosFSAttrib ;

/*-------------------------------------------------------------------------+
|  Type definition for UNIX Filespace attributes                           |
+-------------------------------------------------------------------------*/
typedef struct tsmUnixFSAttrib
{
    dsUint16_t   fsInfoLength;          /* fsInfo length used            */
    osChar_t     fsInfo[DSM_MAX_FSINFO_LENGTH];/*caller-determined data  */
} tsmUnixFSAttrib ;

/*-------------------------------------------------------------------------+
|  Type definition for NetWare Filespace attributes                        |
+-------------------------------------------------------------------------*/
typedef tsmUnixFSAttrib tsmNetwareFSAttrib;

/*-------------------------------------------------------------------------+
|  Type definition for Filespace attributes on all Filespace calls         |
+-------------------------------------------------------------------------*/
typedef union
{
    tsmNetwareFSAttrib  netwareFSAttr;
    tsmUnixFSAttrib     unixFSAttr ;
    tsmDosFSAttrib      dosFSAttr ;
} tsmFSAttr ;

/*-------------------------------------------------------------------------+
|  Type definition for fsUpd parameter on dsmUpdateFS()
+-------------------------------------------------------------------------*/
typedef struct   tsmFSUpd
{
    dsUint16_t      stVersion ;             /* structure version              */
    dsChar_t        *fsType ;               /* filespace type                 */
    dsStruct64_t    occupancy ;             /* occupancy estimate             */
    dsStruct64_t    capacity  ;             /* capacity estimate              */
    tsmFSAttr       fsAttr ;                /* platform specific attributes   */
} tsmFSUpd ;

#define tsmFSUpdVersion  1

/*-------------------------------------------------------------------------+
|  Type definition for Filespace queryBuffer on dsmBeginQuery()            |
+-------------------------------------------------------------------------*/
typedef struct tsmQryFSData
{
    dsUint16_t  stVersion;                 /* structure version */
    dsChar_t    *fsName;                   /* File space name */
} tsmQryFSData;

#define tsmQryFSDataVersion  1

/*-------------------------------------------------------------------------+
| Type definition for Query Filespace response on dsmGetNextQObj()         |
+-------------------------------------------------------------------------*/
typedef struct tsmQryRespFSData
{
    dsUint16_t     stVersion;                          /* structure version */
    dsChar_t       fsName[DSM_MAX_FSNAME_LENGTH + 1];     /* Filespace name */
    dsChar_t       fsType[DSM_MAX_FSTYPE_LENGTH + 1] ;     /* Filespace type */
    dsStruct64_t   occupancy;                   /* Occupancy est. in bytes. */
    dsStruct64_t   capacity;                     /* Capacity est. in bytes. */
    tsmFSAttr      fsAttr ;                /* platform specific attributes  */
    dsmDate        backStartDate;           /* start backup date             */
    dsmDate        backCompleteDate;        /* end backup Date               */
    dsmDate        reserved1    ;           /* For future use                */
    dsmBool_t      bIsUnicode;
    dsUint32_t     fsID;
} tsmQryRespFSData;

#define tsmQryRespFSDataVersion 4

/*-------------------------------------------------------------------------+
|  Type definition for regFilespace parameter on dsmRegisterFS()
+-------------------------------------------------------------------------*/
typedef struct tsmRegFSData
{
    dsUint16_t      stVersion;                      /* structure version */
    dsChar_t        *fsName;                        /* Filespace name */
    dsChar_t        *fsType;                        /* Filespace type */
    dsStruct64_t    occupancy;                  /* Occupancy est. in bytes. */
    dsStruct64_t    capacity;                    /* Capacity est. in bytes. */
    tsmFSAttr       fsAttr ;                 /* platform specific attributes */
} tsmRegFSData;

#define tsmRegFSDataVersion  1

/*-------------------------------------------------------------------------+
|  Type definition for session info response on dsmQuerySessionInfo()      |
+-------------------------------------------------------------------------*/
typedef struct
{
  dsUint16_t     stVersion;           /* Structure version                */
     /*------------------------------------------------------------------*/
     /*           Server information                                     */
     /*------------------------------------------------------------------*/
  dsChar_t       serverHost[DSM_MAX_SERVERNAME_LENGTH+1];
                                     /* Network host name of DSM server  */
  dsUint16_t     serverPort;             /* Server comm port on host         */
  dsmDate        serverDate;             /* Server's date/time               */
  dsChar_t       serverType[DSM_MAX_SERVERTYPE_LENGTH+1];
                                     /* Server's execution platform      */
  dsUint16_t     serverVer;              /* Server's version number          */
  dsUint16_t     serverRel;              /* Server's release number          */
  dsUint16_t     serverLev;              /* Server's level number            */
  dsUint16_t     serverSubLev;           /* Server's sublevel number         */
     /*------------------------------------------------------------------*/
     /*           Client Defaults                                        */
     /*------------------------------------------------------------------*/
  dsChar_t       nodeType[DSM_MAX_PLATFORM_LENGTH+1]; /*node/application type*/
  dsChar_t       fsdelim;                /* File space delimiter             */
  dsChar_t       hldelim;                /* Delimiter betw highlev & lowlev  */
  dsUint8_t      compression;            /* Compression flag                 */
  dsUint8_t      archDel;                /* Archive delete permission        */
  dsUint8_t      backDel;                /* Backup  delete permission        */
  dsUint32_t     maxBytesPerTxn;         /* for future use                   */
  dsUint16_t     maxObjPerTxn;           /* The max objects allowed in a txn */
     /*------------------------------------------------------------------*/
     /*           Session Information                                    */
     /*------------------------------------------------------------------*/
  dsChar_t       id[DSM_MAX_ID_LENGTH+1];    /* Sign-in id node name         */
  dsChar_t       owner[DSM_MAX_OWNER_LENGTH+1]; /* Sign-in owner             */
                                     /*   (for multi-user platforms)     */
  dsChar_t       confFile[DSM_PATH_MAX + DSM_NAME_MAX +1];
                                     /* len is platform dep              */
                                     /* dsInit name of appl config file  */
  dsUint8_t      opNoTrace;              /* dsInit option - NoTrace = 1      */
     /*------------------------------------------------------------------*/
     /*           Policy Data                                            */
     /*------------------------------------------------------------------*/
  dsChar_t       domainName[DSM_MAX_DOMAIN_LENGTH+1]; /* Domain name         */
  dsChar_t       policySetName[DSM_MAX_PS_NAME_LENGTH+1];
                                     /* Active policy set name           */
  dsmDate        polActDate;             /* Policy set activation date       */
  dsChar_t       dfltMCName[DSM_MAX_MC_NAME_LENGTH+1];/* Default Mgmt Class  */
  dsUint16_t     gpBackRetn;             /* Grace-period backup retention    */
  dsUint16_t     gpArchRetn;             /* Grace-period archive retention   */
  dsChar_t       adsmServerName[DSM_MAX_SERVERNAME_LENGTH+1]; /* adsm server name */
  dsmBool_t      archiveRetentionProtection; /* is server Retention protection enabled */
  dsUint64_t     maxBytesPerTxn_64;         /* for future use                   */
  dsmBool_t      lanFreeEnabled;            /* lan free option is set         */
  dsmDedupType   dedupType;                 /* server or clientOrServer       */
  dsChar_t       accessNode[DSM_MAX_ID_LENGTH+1];    /* as node node name         */
} tsmApiSessInfo;

#define tsmApiSessInfoVersion  5


/*-------------------------------------------------------------------------+
| Type definition for Query options response on dsmQueryCliOptions()       |
|      and dsmQuerySessOptions()                                           |
+-------------------------------------------------------------------------*/

typedef struct
{
  dsUint16_t  stVersion;
  dsChar_t    dsmiDir[DSM_PATH_MAX + DSM_NAME_MAX +1];
  dsChar_t    dsmiConfig[DSM_PATH_MAX + DSM_NAME_MAX +1];
  dsChar_t    serverName[DSM_MAX_SERVERNAME_LENGTH+1];
  dsInt16_t   commMethod;
  dsChar_t    serverAddress[DSM_MAX_SERVER_ADDRESS];
  dsChar_t    nodeName[DSM_MAX_NODE_LENGTH+1];
  dsmBool_t   compression;
  dsmBool_t   compressalways;
  dsmBool_t   passwordAccess;
  }tsmOptStruct ;

#define tsmOptStructVersion  1

/*-------------------------------------------------------------------------+
| Type definition for qryRespAccessData  parameter used on dsmQueryAccess()|
+-------------------------------------------------------------------------*/

typedef struct
{
    dsUint16_t        stVersion ;                    /* structure version      */
    dsChar_t          node[DSM_MAX_ID_LENGTH+1];     /* node name              */
    dsChar_t          owner[DSM_MAX_OWNER_LENGTH+1]; /* owner                  */
    tsmObjName        objName ;                      /* object name            */
    dsmAccessType     accessType;                    /* archive or backup     */
    dsUint32_t        ruleNumber ;                   /* Access rule id         */

}tsmQryRespAccessData;

#define tsmQryRespAccessDataVersion  1

/*-------------------------------------------------------------------------+
|  Type definition for envSetUp parameter on dsmSetUp()
+-------------------------------------------------------------------------*/
typedef struct tsmEnvSetUp
{
    dsUint16_t      stVersion;                      /* structure version */
    dsChar_t        dsmiDir[DSM_PATH_MAX + DSM_NAME_MAX +1];
    dsChar_t        dsmiConfig[DSM_PATH_MAX + DSM_NAME_MAX +1];
    dsChar_t        dsmiLog[DSM_PATH_MAX + DSM_NAME_MAX +1];
    char            **argv;  /* for executables name argv[0] */
    dsChar_t        logName[DSM_NAME_MAX +1];
    dsmBool_t       reserved1;         /* for future use */
    dsmBool_t       reserved2;                  /* for future use */
} tsmEnvSetUp;

#define tsmEnvSetUpVersion  4

/*-------------------------------------------------------------------------+
|  Type definition for dsmInitExIn_t
+-------------------------------------------------------------------------*/
typedef struct tsmInitExIn_t
{
    dsUint16_t         stVersion;                      /* structure version */
    tsmApiVersionEx    *apiVersionExP;
    dsChar_t           *clientNodeNameP;
    dsChar_t           *clientOwnerNameP;
    dsChar_t           *clientPasswordP;
    dsChar_t           *userNameP;
    dsChar_t           *userPasswordP;
    dsChar_t           *applicationTypeP;
    dsChar_t           *configfile;
    dsChar_t           *options;
    dsChar_t           dirDelimiter;
    dsmBool_t          useUnicode;
    dsmBool_t          bCrossPlatform;
    dsmBool_t          bService;
    dsmBool_t          bEncryptKeyEnabled;
    dsChar_t           *encryptionPasswordP;
    dsmBool_t          useTsmBuffers;
    dsUint8_t          numTsmBuffers;
} tsmInitExIn_t;

#define tsmInitExInVersion 4

/*-------------------------------------------------------------------------+
|  Type definition for dsmInitExOut_t
+-------------------------------------------------------------------------*/
typedef struct tsmInitExOut_t
{
    dsUint16_t         stVersion;                      /* structure version */
    dsInt16_t          userNameAuthorities;
    dsInt16_t          infoRC;        /* error return code if encountered */
                                      /* adsm server name                 */
    dsChar_t           adsmServerName[DSM_MAX_SERVERNAME_LENGTH+1];
    dsUint16_t         serverVer;     /* Server's version number          */
    dsUint16_t         serverRel;     /* Server's release number          */
    dsUint16_t         serverLev;     /* Server's level number            */
    dsUint16_t         serverSubLev;  /* Server's sublevel number         */
} tsmInitExOut_t;

#define tsmInitExOutVersion 2

/*-------------------------------------------------------------------------+
|  Type definition for dsmLogExIn_t
+-------------------------------------------------------------------------*/
typedef struct tsmLogExIn_t
{
    dsUint16_t         stVersion;  /* structure version */
    dsmLogSeverity     severity;
    dsChar_t           appMsgID[8];
    dsmLogType         logType;    /* log type : local, server, both */
    dsChar_t           *message;   /* text of message to be logged */
    dsChar_t           appName[DSM_MAX_PLATFORM_LENGTH];
    dsChar_t           osPlatform[DSM_MAX_PLATFORM_LENGTH];
    dsChar_t           appVersion[DSM_MAX_PLATFORM_LENGTH];

} tsmLogExIn_t;

#define tsmLogExInVersion 2

/*-------------------------------------------------------------------------+
|  Type definition for dsmlogExOut_t
+-------------------------------------------------------------------------*/
typedef struct tsmLogExOut_t
{
    dsUint16_t         stVersion;  /* structure version */
} tsmLogExOut_t;

#define tsmLogExOutVersion 1

/*-------------------------------------------------------------------------+
|  Type definition for dsmRenameIn_t
+-------------------------------------------------------------------------*/
typedef struct tsmRenameIn_t
{
    dsUint16_t       stVersion;                     /* structure version  */
    dsUint32_t       tsmHandle;                     /* handle for session */
    dsUint8_t        repository;                    /* Backup or Archive  */
    tsmObjName       *objNameP ;                    /* object name */
    dsChar_t         newHl[DSM_MAX_HL_LENGTH + 1];  /* new High level name */
    dsChar_t         newLl[DSM_MAX_LL_LENGTH + 1];  /* new Low level name */
    dsmBool_t        merge;                        /* merge into existing name*/
    ObjID            objId;                         /* objId for Archive */
} tsmRenameIn_t;

#define tsmRenameInVersion 1

/*-------------------------------------------------------------------------+
|  Type definition for dsmRenameOut_t
+-------------------------------------------------------------------------*/
typedef struct tsmRenameOut_t
{
    dsUint16_t         stVersion;                      /* structure version */
} tsmRenameOut_t;

#define tsmRenameOutVersion 1

/*-------------------------------------------------------------------------+
|  Type definition for tsmEndSendObjExIn_t
+-------------------------------------------------------------------------*/
typedef struct tsmEndSendObjExIn_t
{
    dsUint16_t       stVersion;                     /* structure version  */
    dsUint32_t       tsmHandle;                     /* handle for session */
} tsmEndSendObjExIn_t;

#define tsmEndSendObjExInVersion 1

/*-------------------------------------------------------------------------+
|  Type definition for dsmEndSendObjExOut_t
+-------------------------------------------------------------------------*/
typedef struct tsmEndSendObjExOut_t
{
   dsUint16_t         stVersion;           /* structure version */
   dsStruct64_t       totalBytesSent;      /* total bytes read from app */
   dsmBool_t          objCompressed;       /* was object compressed */
   dsStruct64_t       totalCompressSize;   /* total size after compress */
   dsStruct64_t       totalLFBytesSent;    /* total bytes sent Lan Free */
   dsUint8_t          encryptionType;      /* type of encryption used   */
   dsmBool_t          objDeduplicated;     /* was object processed for dist. data dedup */
   dsStruct64_t       totalDedupSize;      /* total size after de-dup */
}tsmEndSendObjExOut_t;

#define tsmEndSendObjExOutVersion 3

/*-------------------------------------------------------------------------+
|  Type definition for tsmGroupHandlerIn_t
+-------------------------------------------------------------------------*/
typedef struct tsmGroupHandlerIn_t
{
    dsUint16_t       stVersion;        /* structure version                        */
    dsUint32_t       tsmHandle;        /* handle for session                       */
    dsUint8_t        groupType;        /* Type of group                            */
    dsUint8_t        actionType;       /* Type of group operation                  */
    dsUint8_t        memberType;       /* Type of member: Leader or member         */
    dsStruct64_t     leaderObjId;      /* OBJID of the groupleader                 */
    dsChar_t         *uniqueGroupTagP; /* Unique group identifier                  */
    tsmObjName       *objNameP ;       /* group leader object name                 */
    dsmGetList       memberObjList;    /* list of objects to remove, assign        */
} tsmGroupHandlerIn_t;

#define tsmGroupHandlerInVersion 1

/*-------------------------------------------------------------------------+
|  Type definition for tsmGroupHandlerExOut_t
+-------------------------------------------------------------------------*/
typedef struct tsmGroupHandlerOut_t
{
    dsUint16_t         stVersion;                      /* structure version */
} tsmGroupHandlerOut_t;

#define tsmGroupHandlerOutVersion 1

/*-------------------------------------------------------------------------+
|  Type definition for tsmEndTxnExIn_t
+-------------------------------------------------------------------------*/
typedef struct tsmEndTxnExIn_t
{
    dsUint16_t       stVersion;                     /* structure version  */
    dsUint32_t       tsmHandle;                     /* handle for session */
    dsUint8_t        vote;
} tsmEndTxnExIn_t;

#define tsmEndTxnExInVersion 1

/*-------------------------------------------------------------------------+
|  Type definition for tsmEndTxnExOut_t
+-------------------------------------------------------------------------*/
typedef struct tsmEndTxnExOut_t
{
    dsUint16_t         stVersion;               /* structure version              */
    dsUint16_t         reason;                  /* reason code                    */
    dsStruct64_t       groupLeaderObjId;        /* groupLeader obj id returned on */
                                                /* DSM_ACTION_OPEN                */
    dsUint8_t          reserved1;               /* future use                     */
    dsUint16_t         reserved2;               /* future use                     */
} tsmEndTxnExOut_t;

#define tsmEndTxnExOutVersion 1

/*-------------------------------------------------------------------------+
|  Type definition for tsmEndGetDataExIn_t
+-------------------------------------------------------------------------*/
typedef struct tsmEndGetDataExIn_t
{
   dsUint16_t     stVersion;   /* structure version  */
   dsUint32_t     tsmHandle;   /* handle for session */
}tsmEndGetDataExIn_t;

#define tsmEndGetDataExInVersion 1

/*-------------------------------------------------------------------------+
|  Type definition for tsmEndGetDataExOut_t
+-------------------------------------------------------------------------*/
typedef struct tsmEndGetDataExOut_t
{
   dsUint16_t     stVersion;         /* structure version             */
   dsUint16_t     reason;            /* reason code                   */
   dsStruct64_t   totalLFBytesRecv;  /* total lan free bytes recieved */
}tsmEndGetDataExOut_t;

#define tsmEndGetDataExOutVersion 1

/*-------------------------------------------------------------------------+
|  Type definition for  on tsmRetentionEvent()                             |
+-------------------------------------------------------------------------*/
typedef struct tsmRetentionEventIn_t
{
   dsUint16_t         stVersion;                    /* structure version  */
   dsUint32_t         tsmHandle;                    /* session Handle     */
   dsmEventType_t     eventType;                    /* Event type         */
   dsmObjList_t       objList;                      /* object ID          */
}tsmRetentionEventIn_t;

#define tsmRetentionEventInVersion 1

/*-------------------------------------------------------------------------+
|  Type definition for  on tsmRetentionEvent()               |
+-------------------------------------------------------------------------*/
typedef struct tsmRetentionEventOut_t
{
   dsUint16_t       stVersion ;                    /* structure version      */
}tsmRetentionEventOut_t;

#define tsmRetentionEventOutVersion 1

/*-------------------------------------------------------------------------+
|  Type definition for tsmUpdateObjExIn_t
+-------------------------------------------------------------------------*/
typedef struct tsmUpdateObjExIn_t
{
   dsUint16_t      stVersion;            /* structure version   */
   dsUint32_t      tsmHandle;            /* session Handle      */ 
   tsmSendType     sendType;             /* send type back/arch */
   dsChar_t        *descrP;              /* archive description */
   tsmObjName      *objNameP;            /* objName             */
   tsmObjAttr      *objAttrPtr;          /* attribute           */
   dsUint32_t      objUpdAct;            /* update action       */
   ObjID           archObjId;            /* objId for archive   */
}tsmUpdateObjExIn_t;

#define tsmUpdateObjExInVersion 1

/*-------------------------------------------------------------------------+
|  Type definition for tsmUpdateObjExOut_t
+-------------------------------------------------------------------------*/
typedef struct tsmUpdateObjExOut_t
{
    dsUint16_t         stVersion;        /* structure version */               
}tsmUpdateObjExOut_t;

#define tsmUpdateObjExOutVersion 1

#if _OPSYS_TYPE == DS_WINNT
#pragma pack()
#endif


#ifdef _MAC
#pragma options align = reset
#endif
#endif /* _H_TSMAPITD */



