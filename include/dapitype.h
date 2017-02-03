/***********************************************************************
* Name:
*        dapitype.h
*
* Function:
*        Type definitions for the sample Tivoli Storage Manager api code
*
* Environment:
*        This is a PLATFORM-INDEPENDENT source file. As such it may
*        contain no dependencies on any specific operating system
*        environment or hardware platform.
*
***********************************************************************/
#define FALSE 0
#define TRUE 1
#define RC_NO_MEMORY      222
#define RC_NOT_IN_SESSION 12
#define RC_SESSION_FAILED 13

/*------------------------------------------------------------------------.
| Dialog definition for the various input fields.
.------------------------------------------------------------------------*/
typedef struct dialog_s
  {
  dsUint16_t item_type;
  char  *item_desc;
  char  *item_buff;
  } dialog;

/*------------------------------------------------------------------------.
| Table definitions for menus and menu entries used in this application.
| These structures will be defined in the data portion of the application.
|
| These structures provide a very simple setup to offer line mode menu
| selection of items.  This way a single code segment can process all
| user input and invoke the proper routines without having to change the
| main line code.
.------------------------------------------------------------------------*/
typedef struct menu_s
  {
  struct menu_entry_s *mentry;  /* Pointer to the menu entries.          */
  char   *instructions;         /* Short instruction for menu.           */
  } menu;

typedef struct menu_entry_s
  {
  dsUint16_t selection;          /* Selection number (0 - n)                 */
  char       *sel_desc;          /* Selection description (Backup...         */
  dsInt16_t (*sel_func)(dialog *sel_dialog);
                                 /* Function to call if selection chosen     */
  menu       *next_menu;         /* Pointer to next menu if nested.          */
  dsUint8_t  exit_menu;          /* Boolean indicating if to exit from menu  */
  dialog     *sel_dialog;        /* Dialog to use.                           */
  } menu_entry;

#define MENU_END 65324        /* Arbitrary number to designate end of menu*/

/*------------------------------------------------------------------------.
| Linked list typedefs typically used for keeping multiple objects
| together within a transaction.
.------------------------------------------------------------------------*/
typedef struct s_llist
  {
  struct s_llist *next_llist;
  dsmObjName      objName;
  } llist;

/*------------------------------------------------------------------------.
| Item type definitions for dialog processing
.------------------------------------------------------------------------*/
#define DSMAPI_FILESPACE            1
#define DSMAPI_HIGHLEVEL            2
#define DSMAPI_LOWLEVEL             3
#define DSMAPI_FILESIZE             4
#define DSMAPI_NUM_FILES            5
#define DSMAPI_SEED_STRING          6
#define DSMAPI_MNTWAIT              7
#define DSMAPI_OBJOWNER             8
#define DSMAPI_OBJCOMP              9
#define DSMAPI_NODENAME            10
#define DSMAPI_OWNER               11
#define DSMAPI_PASSWORD            12
#define DSMAPI_OBJTYPE             13
#define DSMAPI_MC                  14
#define DSMAPI_DESCRIPTION         15
#define DSMAPI_ACTIVETYPE          16
#define DSMAPI_LOINSDATE           17
#define DSMAPI_HIINSDATE           18
#define DSMAPI_LOEXPDATE           19
#define DSMAPI_HIEXPDATE           20
#define DSMAPI_FASTACTIVE          21
#define DSMAPI_DETAILS             22
#define DSMAPI_CONFIG              23
#define DSMAPI_OPTIONS             24
#define DSMAPI_PITDATE             25
#define DSMAPI_PITTIME             26
#define DSMAPI_LOGEVENT            27
#define DSMAPI_LOGMESSAGE          28
#define DSMAPI_UPDFSINFO           29
#define DSMAPI_UPDFSCAPACITY       30
#define DSMAPI_UPDFSOCCUPANCY      31 
#define DSMAPI_UPDFSBACKSTARTDATE  32
#define DSMAPI_UPDFSBACKCOMPLTDATE 33
#define DSMAPI_FSINFO              34
#define DSMAPI_FSINFOLENGTH        35
#define DSMAPI_FSOCCUPANCY         36
#define DSMAPI_FSCAPACITY          37
#define DSMAPI_UPDOWNER            38
#define DSMAPI_UPDOBJINFO          39
#define DSMAPI_OBJINFO             40
#define DSMAPI_OBSIZEEST           41
#define DSMAPI_LOINSTIME           42
#define DSMAPI_HIINSTIME           43
#define DSMAPI_LOEXPTIME           44
#define DSMAPI_HIEXPTIME           45
#define DSMAPI_ACCESSTYPE          46
#define DSMAPI_ACCESSRULE          47
#define DSMAPI_DSMIDIR             48
#define DSMAPI_DSMICONFIG          49
#define DSMAPI_DSMILOG             50
#define DSMAPI_UPDDESCR            51
#define DSMAPI_OBJDESCR            52
#define DSMAPI_LOGNAME             53
#define DSMAPI_REPOSITORY          54
#define DSMAPI_USERNAME            55
#define DSMAPI_USERNAMEPWD         56
#define DSMAPI_LOGSEV              57
#define DSMAPI_APPMSG              58
#define DSMAPI_NEWHIGHLEVEL        59
#define DSMAPI_NEWLOWLEVEL         60
#define DSMAPI_MERGE               61
#define DSMAPI_OBJIDHI             62
#define DSMAPI_OBJIDLO             63
#define DSMAPI_EVENTTYPE           64
#define DSMAPI_SLEEP               65
#define DSMAPI_ENCRYPT             66
#define DSMAPI_ENCRYPTKEY          67
#define DSMAPI_DIRDELIM            68
#define DSMAPI_USEUNICODE          69
#define DSMAPI_PRXTRG              70
#define DSMAPI_END              30999

/*------------------------------------------------------------------------.
| Optional parm defs for process dialog calls
.------------------------------------------------------------------------*/
#define Archive_Send      1
#define Backup_Send       2
#define Archive_Get       3
#define Backup_Get        4
#define ABackup_Get       5
#define Restore_Get       6
#define Retrieve_Get      7
#define Backup_Delete     8
#define Archive_Delete    9
#define fs_query          10
#define fs_delete         11
#define log_event         12
#define set_access        13
#define setup             14
#define rename_obj        15
#define del_obj           16
#define ret_event         17
#define ex_signon         18

/*------------------------------------------------------------------------.
| Data structure for our object info field on object sends.
.------------------------------------------------------------------------*/
typedef struct
{
   dsUint8_t   objType;            /* Type of object sent.                   */
   dsStruct64_t  size;               /* Size of object sent.                   */
   char    eyecatcher[48];     /* Eye catcher string            */
   char    seed[1];            /* Beginning of seed string, null delimit.*/
} smpObjInfo;

/*------------------------------------------------------------------------.
| Data structure for sample preferences
.------------------------------------------------------------------------*/
typedef struct
{
   dsUint32_t  sz_send_buff;       /* Size of buffer to use for data sends.  */
   dsUint32_t  sz_recv_buff;       /* Size of buffer to use for data recvs.  */
   dsBool_t  verbose;            /* Should output be verbose or normal?    */
   dsUint32_t  max_restore_items;  /* Max num of items to restore in 1 call  */
   dsBool_t  qry_details;        /* Show details on queries?               */
   dsBool_t  use_est;            /* Give small size estimate on sends?     */
   dsBool_t  echo_in;            /* Echo input lines as they are read?     */
} preferences;

/* ******* G l o b a l s  ********  */

extern dsmApiVersionEx     apiApplVer;
extern dsmApiVersionEx     apiLibVer;
extern dsUint32_t       dsmHandle;
extern ApiSessInfo      dsmSessInfo;
extern preferences      pref;
extern char             api_eyecatcher[];
extern char           **globalArgv;
extern char             gRepos; 
#define  DSM_OBJ_WILDCARD              0xFE     /* Query all object types */
#define  DSM_OBJ_QRY_FILES_AND_DIRS    0xFF     /* Query only files/dirs  */
#define  DSM_OBJ_NQR_FILES_AND_DIRS    0x05     /* For NQR use only       */

