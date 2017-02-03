/***********************************************************************
* Name:
*        dapidata.h
*
* Function:
*        Dialog definitions for the sample Tivoli Storage Manager api code
*
* Environment:
*        This is a PLATFORM-INDEPENDENT source file. As such it may
*        contain no dependencies on any specific operating system
*        environment or hardware platform.
*
***********************************************************************/
#ifndef _DAPIDATA_H
#define _DAPIDATA_H

/*-----------------------------------------------------------------------.
| S e t u p _ D i a l o g
|========================================================================
| Dialog definition for envSet up.
|________________________________________________________________________*/
dialog setup_dialog[]=
  {
  {DSMAPI_DSMIDIR           ,"             dsmiDir:",NULL},
  {DSMAPI_DSMICONFIG        ,"         Config file:",NULL},
  {DSMAPI_DSMILOG           ,"Error log directory :",NULL},
  {DSMAPI_LOGNAME           ,"     Error log name :",NULL},
  {DSMAPI_END,NULL,NULL}
  };

/*-----------------------------------------------------------------------.
| S e t_ A c c e s s _ D i a l o g
|========================================================================
| Dialog definition for update filespace.
|________________________________________________________________________*/
dialog set_access_dialog[]=
  {
  {DSMAPI_FILESPACE         ,"                      Filespace:",NULL},
  {DSMAPI_HIGHLEVEL         ,"                      Highlevel:",NULL},
  {DSMAPI_LOWLEVEL          ,"                       Lowlevel:",NULL},
  {DSMAPI_OBJTYPE           ,"    Object Type(Archive/Backup):",NULL},
  {DSMAPI_NODENAME          ,"                      Node name:",NULL},
  {DSMAPI_OWNER             ,"                     Owner name:",NULL},
  {DSMAPI_END,NULL,NULL}
  };

/*-----------------------------------------------------------------------.
| D e l_ A c c e s s _ D i a l o g
|========================================================================
| Dialog definition for Access rule deletion.
|________________________________________________________________________*/
dialog del_access_dialog[]=
  {
  {DSMAPI_ACCESSRULE        ,"        Acces rule id to delete:",NULL},
  {DSMAPI_END,NULL,NULL}
  };

/*-----------------------------------------------------------------------.
| U p d a t e _ F i l e s p a c e _ D i a l o g
|========================================================================
| Dialog definition for update filespace.
|________________________________________________________________________*/
dialog update_fs_dialog[]=
  {
  {DSMAPI_FILESPACE         ,"                      Filespace:",NULL},
  {DSMAPI_UPDFSINFO         ,"           Update fsinfo (Y/N)?:",NULL},
  {DSMAPI_UPDFSCAPACITY     ,"          Update capacity(Y/N)?:",NULL},
  {DSMAPI_UPDFSOCCUPANCY    ,"         Update occupancy(Y/N)?:",NULL},
  {DSMAPI_UPDFSBACKSTARTDATE,"Update backup start date (Y/N)?:",NULL},
  {DSMAPI_UPDFSBACKCOMPLTDATE,"Update backup complete date(Y/N)?:",NULL},
  {DSMAPI_FSINFO            ,"             New filespace info:",NULL},
  {DSMAPI_FSOCCUPANCY       ,"                  New occupancy:",NULL},
  {DSMAPI_FSCAPACITY        ,"                   New capacity:",NULL},
  {DSMAPI_END,NULL,NULL}
  };

/*-----------------------------------------------------------------------.
| U p d a t e _ O b j e c t _ D i a l o g
|========================================================================
| Dialog definition for update backup object.
|________________________________________________________________________*/
dialog update_obj_dialog[]=
  {
  {DSMAPI_FILESPACE  ,"                      Filespace:",NULL},
  {DSMAPI_HIGHLEVEL  ,"                      Highlevel:",NULL},
  {DSMAPI_LOWLEVEL   ,"                       Lowlevel:",NULL},
  {DSMAPI_OBJTYPE    ,"               Object Type(D/F):",NULL},
  {DSMAPI_UPDOWNER   ,"            Update owner (Y/N)?:",NULL}, 
  {DSMAPI_UPDOBJINFO ,"      Update object info (Y/N)?:",NULL}, 
  {DSMAPI_OBJOWNER   ,"          New Object Owner Name:",NULL},
  {DSMAPI_OBJINFO    ,"               New Object info :",NULL},
  {DSMAPI_OBSIZEEST  ,"              New size estimate:",NULL},
  {DSMAPI_END,NULL,NULL}
  };

/*-----------------------------------------------------------------------.
| U p d a t e _ A r c _ D i a l o g
|========================================================================
| Dialog definition for update backup object.
|________________________________________________________________________*/
dialog update_arc_dialog[]=
  {
  {DSMAPI_FILESPACE  ,"                      Filespace:",NULL},
  {DSMAPI_HIGHLEVEL  ,"                      Highlevel:",NULL},
  {DSMAPI_LOWLEVEL   ,"                       Lowlevel:",NULL},
  {DSMAPI_OBJTYPE    ,"               Object Type(D/F):",NULL},
  {DSMAPI_UPDOWNER   ,"            Update owner (Y/N)?:",NULL},
  {DSMAPI_UPDOBJINFO ,"      Update object info (Y/N)?:",NULL},
  {DSMAPI_UPDDESCR   ,"       Update description(Y/N)?:",NULL},
  {DSMAPI_OBJOWNER   ,"          New Object Owner Name:",NULL},
  {DSMAPI_OBJINFO    ,"               New Object info :",NULL},
  {DSMAPI_OBSIZEEST  ,"              New size estimate:",NULL},
  {DSMAPI_OBJDESCR   ,"                 New decription:",NULL},
  {DSMAPI_END,NULL,NULL}
  };

/*-----------------------------------------------------------------------.
| U p d a t e _ O b j e c t E x _ D i a l o g
|========================================================================
| Dialog definition for update backup object.
|________________________________________________________________________*/
dialog update_objEx_dialog[]=
  {
  {DSMAPI_FILESPACE  ,"                      Filespace:",NULL},
  {DSMAPI_HIGHLEVEL  ,"                      Highlevel:",NULL},
  {DSMAPI_LOWLEVEL   ,"                       Lowlevel:",NULL},
  {DSMAPI_REPOSITORY ,"         Backup or Archive(B/A):",NULL},
  {DSMAPI_OBJTYPE    ,"               Object Type(D/F):",NULL},
  {DSMAPI_OBJIDHI    ,"        archive Object ID (HI) :",NULL},
  {DSMAPI_OBJIDLO    ,"        archive Object ID (LOW):",NULL},
  {DSMAPI_UPDOWNER   ,"            Update owner (Y/N)?:",NULL}, 
  {DSMAPI_UPDOBJINFO ,"      Update object info (Y/N)?:",NULL}, 
  {DSMAPI_UPDDESCR   ,"       Update description(Y/N)?:",NULL},
  {DSMAPI_OBJOWNER   ,"          New Object Owner Name:",NULL},
  {DSMAPI_OBJINFO    ,"               New Object info :",NULL},
  {DSMAPI_OBSIZEEST  ,"              New size estimate:",NULL},
  {DSMAPI_OBJDESCR   ,"                 New decription:",NULL},
  {DSMAPI_END,NULL,NULL}
  };

/*-----------------------------------------------------------------------.
| L o g _ E v e n t _ D i a l o g
|========================================================================
| Dialog definition for query filespace.
|________________________________________________________________________*/
dialog log_event_dialog[]=
  {
  {DSMAPI_LOGEVENT     ,"LogFile: local(L),Server(S),Both(B)?:",NULL},
  {DSMAPI_LOGSEV       ,"Severity: (Info/Warning/Error/Severe)?:",NULL},
  {DSMAPI_LOGMESSAGE   ,"Message to log :",NULL},
  {DSMAPI_APPMSG       ,"Application message to log(APP0001) :",NULL},
  {DSMAPI_END,NULL,NULL}
  };


/*-----------------------------------------------------------------------.
| Q u e r y _ F i l e s p a c e _ D i a l o g
|========================================================================
| Dialog definition for query filespace.
|________________________________________________________________________*/
dialog query_fs_dialog[]=
  {
  {DSMAPI_FILESPACE  ,"Filespace pattern to query:",NULL},
  {DSMAPI_END,NULL,NULL}
  };

/*-----------------------------------------------------------------------.
| D e l e t e _ F i l e s p a c e _ D i a l o g
|========================================================================
| Dialog definition for query filespace.
|________________________________________________________________________*/
dialog delete_fs_dialog[]=
  {
  {DSMAPI_FILESPACE  ,"Filespace pattern to DELETE:",NULL},
  {DSMAPI_END,NULL,NULL}
  };

/*-----------------------------------------------------------------------.
| Q u e r y _ P r x_ P e e r s _ D i a l o g
|========================================================================
| Dialog definition for query proxy peers.
|________________________________________________________________________*/
dialog query_prx_peers_dialog[]=
  {
  {DSMAPI_PRXTRG         ,"Target node name:",NULL},
  {DSMAPI_END,NULL,NULL}
  };

/*-----------------------------------------------------------------------.
| Q u e r y _ M g m t C l a s s _ D i a l o g
|========================================================================
| Dialog definition for query mgmt class.
|________________________________________________________________________*/
dialog query_mc_dialog[]=
  {
  {DSMAPI_MC         ,"Mgmt. class pattern to query:",NULL},
  {DSMAPI_END,NULL,NULL}
  };

/*-----------------------------------------------------------------------.
| S i g n o n _ D i a l o g
|========================================================================
| Dialog definition for signon pannel.
|________________________________________________________________________*/
dialog signon_dialog[]=
  {
  {DSMAPI_NODENAME   ,"      Node name:",NULL},
  {DSMAPI_OWNER      ,"     Owner name:",NULL},
  {DSMAPI_PASSWORD   ,"       Password:",NULL},
  {DSMAPI_CONFIG     ,"API Config file:",NULL},
  {DSMAPI_OPTIONS    ,"Session options:",NULL},
  {DSMAPI_USERNAME   ,"      User Name:",NULL},
  {DSMAPI_USERNAMEPWD,"      User pswd:",NULL},
  {DSMAPI_END,NULL,NULL}
  };

/*-----------------------------------------------------------------------.
| S i g n o n _ E x _ D i a l o g
|========================================================================
| Dialog definition for extended signon pannel.
|________________________________________________________________________*/
dialog signon_ex_dialog[]=
  {
  {DSMAPI_NODENAME   ,"                       Node name:",NULL},
  {DSMAPI_OWNER      ,"                      Owner name:",NULL},
  {DSMAPI_PASSWORD   ,"                        Password:",NULL},
  {DSMAPI_CONFIG     ,"                 API Config file:",NULL},
  {DSMAPI_OPTIONS    ,"                 Session options:",NULL},
  {DSMAPI_USERNAME   ,"                       User Name:",NULL},
  {DSMAPI_USERNAMEPWD,"                       User pswd:",NULL},
  {DSMAPI_ENCRYPT    ,"            Use encryption?(Y/N):",NULL},
  {DSMAPI_ENCRYPTKEY ,"                  Encryption key:",NULL},
  {DSMAPI_DIRDELIM   ,"             Directory delimiter:",NULL},
  {DSMAPI_USEUNICODE ,"Create Unicode file spaces?(Y/N):",NULL},
  {DSMAPI_END,NULL,NULL}
  };

/*-----------------------------------------------------------------------.
| B a c k u p _ D i a l o g
|========================================================================
| Dialog definition for creating backup objects.
|________________________________________________________________________*/
dialog backup_dialog[]=
  {
  {DSMAPI_FILESPACE  ,"                      Filespace:",NULL},
  {DSMAPI_HIGHLEVEL  ,"                      Highlevel:",NULL},
  {DSMAPI_LOWLEVEL   ,"                       Lowlevel:",NULL},
  {DSMAPI_OBJTYPE    ,"               Object Type(D/F):",NULL},
  {DSMAPI_OBJOWNER   ,"              Object Owner Name:",NULL},
  {DSMAPI_OBJCOMP    ,"Object already compressed?(Y/N):",NULL},
  {DSMAPI_MNTWAIT    ,"           Wait for mount?(Y/N):",NULL},
  {DSMAPI_FILESIZE   ,"                      File size:",NULL},
  {DSMAPI_NUM_FILES  ,"                Number of files:",NULL},
  {DSMAPI_SEED_STRING,"                    Seed string:",NULL},
  {DSMAPI_MC         ,"            Mgmt class override:",NULL},
  {DSMAPI_END,NULL,NULL}
  };

/*-----------------------------------------------------------------------.
| A r c h i v e _ D i a l o g
|========================================================================
| Dialog definition for creating archive objects.
|________________________________________________________________________*/
dialog archive_dialog[]=
  {
  {DSMAPI_FILESPACE  ,"                      Filespace:",NULL},
  {DSMAPI_HIGHLEVEL  ,"                      Highlevel:",NULL},
  {DSMAPI_LOWLEVEL   ,"                       Lowlevel:",NULL},
  {DSMAPI_OBJTYPE    ,"               Object Type(D/F):",NULL},
  {DSMAPI_OBJOWNER   ,"              Object Owner Name:",NULL},
  {DSMAPI_OBJCOMP    ,"Object already compressed?(Y/N):",NULL},
  {DSMAPI_MNTWAIT    ,"           Wait for mount?(Y/N):",NULL},
  {DSMAPI_FILESIZE   ,"                      File size:",NULL},
  {DSMAPI_NUM_FILES  ,"                Number of files:",NULL},
  {DSMAPI_SEED_STRING,"                    Seed string:",NULL},
  {DSMAPI_DESCRIPTION,"            Archive description:",NULL},
  {DSMAPI_MC         ,"            Mgmt class override:",NULL},
  {DSMAPI_END,NULL,NULL}
  };
/*-----------------------------------------------------------------------.
| Q u e r y _ A r c h i v e _ D i a l o g
|========================================================================
| Dialog definition for querying archive objects.
|________________________________________________________________________*/
dialog query_archive_dialog[]=
  {
  {DSMAPI_FILESPACE  ,"                        Filespace:",NULL},
  {DSMAPI_HIGHLEVEL  ,"                        Highlevel:",NULL},
  {DSMAPI_LOWLEVEL   ,"                         Lowlevel:",NULL},
  {DSMAPI_OBJTYPE    ,"               Object Type(D/F/A):",NULL},
  {DSMAPI_OBJOWNER   ,"                Object Owner Name:",NULL},
  {DSMAPI_LOINSDATE  ,"       From insert date(mmddyyyy):",NULL},
  {DSMAPI_LOINSTIME  ,"           From insert time(hhmm):",NULL},
  {DSMAPI_HIINSDATE  ,"         To insert date(mmddyyyy):",NULL},
  {DSMAPI_HIINSTIME  ,"             To insert time(hhmm):",NULL},
  {DSMAPI_LOEXPDATE  ,"       From expire date(mmddyyyy):",NULL},
  {DSMAPI_LOEXPTIME  ,"           From expire time(hhmm):",NULL},
  {DSMAPI_HIEXPDATE  ,"         To expire date(mmddyyyy):",NULL},
  {DSMAPI_HIEXPTIME  ,"             To expire time(hhmm):",NULL},
  {DSMAPI_DESCRIPTION,"              Archive description:",NULL},
  {DSMAPI_DETAILS    ,"      Show detailed output? (Y/N):",NULL},
  {DSMAPI_MNTWAIT    ,"On Retrieve, Wait for mount?(Y/N):",NULL},
  {DSMAPI_END,NULL,NULL}
  };
/*-----------------------------------------------------------------------.
| Q u e r y _ B a c k u p _ D i a l o g
|========================================================================
| Dialog definition for querying backup objects.
|________________________________________________________________________*/
dialog query_backup_dialog[]=
  {
  {DSMAPI_FILESPACE  ,"                       Filespace:",NULL},
  {DSMAPI_HIGHLEVEL  ,"                       Highlevel:",NULL},
  {DSMAPI_LOWLEVEL   ,"                        Lowlevel:",NULL},
  {DSMAPI_OBJTYPE    ,"              Object Type(D/F/A):",NULL},
  {DSMAPI_ACTIVETYPE ,"   Active(A),Inactive(I),Both(B):",NULL},
  {DSMAPI_FASTACTIVE ,"If root, query all owners? (Y/N):",NULL},
  {DSMAPI_OBJOWNER   ,"               Object Owner Name:",NULL},
  {DSMAPI_PITDATE    ,"   point in time date (MMDDYYYY):",NULL}, 
  {DSMAPI_PITTIME    ,"   point in time time     (hhmm):",NULL},
  {DSMAPI_DETAILS    ,"     Show detailed output? (Y/N):",NULL},
  {DSMAPI_MNTWAIT    ,"On Restore, Wait for mount?(Y/N):",NULL},
  {DSMAPI_END,NULL,NULL}
  };

/*-----------------------------------------------------------------------.
| R e n a m e _ O b j _ D i a l o g
|========================================================================
| Dialog definition for update backup object.
|________________________________________________________________________*/
dialog rename_obj_dialog[]=
  {
  {DSMAPI_FILESPACE  ,"                      Filespace:",NULL},
  {DSMAPI_HIGHLEVEL  ,"                      Highlevel:",NULL},
  {DSMAPI_LOWLEVEL   ,"                       Lowlevel:",NULL},
  {DSMAPI_OBJTYPE    ,"               Object Type(D/F):",NULL},
  {DSMAPI_NEWHIGHLEVEL  ,"               new Highlevel:",NULL},
  {DSMAPI_NEWLOWLEVEL   ,"                new Lowlevel:",NULL},
  {DSMAPI_MERGE      ,"                    Merge?(Y/N):",NULL},
  {DSMAPI_OBJIDHI    ,"        archive Object ID (HI) :",NULL},
  {DSMAPI_OBJIDLO    ,"        archive Object ID (LOW):",NULL},
  {DSMAPI_REPOSITORY ,"         Backup or Archive(B/A):",NULL},
  {DSMAPI_END,NULL,NULL}
  };

/*-----------------------------------------------------------------------.
| D e l e t e _ O b j _ D i a l o g
|========================================================================
| Dialog definition for query filespace.
|________________________________________________________________________*/
dialog delete_obj_dialog[]=
  {
  {DSMAPI_OBJIDHI    ,"        Object ID (HI) to DELETE:",NULL},
  {DSMAPI_OBJIDLO    ,"       Object ID (LOW) to DELETE:",NULL},
  {DSMAPI_REPOSITORY ,"          Backup or Archive(B/A):",NULL},
  {DSMAPI_END,NULL,NULL}
  };

/*-----------------------------------------------------------------------.
| r e t _ e v e n t _ D i a l o g
|========================================================================
| Dialog definition for query filespace.
|________________________________________________________________________*/
dialog ret_event_dialog[]=
  {
  {DSMAPI_OBJIDHI    ,"         Object ID (HI) to signal:",NULL},
  {DSMAPI_OBJIDLO    ,"        Object ID (LOW) to signal:",NULL},
  {DSMAPI_EVENTTYPE  ,"Activate (A) Hold (H) Release (R):",NULL},
  {DSMAPI_END,NULL,NULL}
  };

/*-----------------------------------------------------------------------.
| S l e e p _ D i a l o g
|========================================================================
| Dialog definition for sleep.
|________________________________________________________________________*/
dialog sleep_dialog[]=
  {
  {DSMAPI_SLEEP     ,"       Number of seconds to sleep:",NULL},
  {DSMAPI_END,NULL,NULL}
  };

/*----------------------------------------------------------------------*/
/* Q u e r y   M e n u                                                  */
/*======================================================================*/
/* Definition for the sample API query menu.                            */
/*----------------------------------------------------------------------*/

menu_entry query_entries[]=
  {
  {0,"Access Query"          ,smpapi_qry_access     ,NULL,FALSE,NULL},
  {1,"Backup Query"          ,smpapi_qry_backup     ,NULL,FALSE,query_backup_dialog},
  {2,"Archive Query"         ,smpapi_qry_archive    ,NULL,FALSE,query_archive_dialog},
  {3,"Management Class Query",smpapi_qry_mc         ,NULL,FALSE,query_mc_dialog},
  {4,"Filespace Query"       ,smpapi_qry_fs         ,NULL,FALSE,query_fs_dialog},
  {5,"Session Info Query"    ,smpapi_qry_sess       ,NULL,FALSE,NULL},
  {6,"API Version Query"     ,smpapi_qry_version    ,NULL,FALSE,NULL},
  {7,"Option File Query"     ,smpapi_qry_cliOptions ,NULL,FALSE,NULL},
  {8,"Session Options Query" ,smpapi_qry_sessOptions,NULL,FALSE,NULL},
  {9,"Quit"                  ,smpapi_query_exit     ,NULL,TRUE ,NULL},
  {10,"Proxy Node Authority" ,smpapi_qry_prx_auth   ,NULL,FALSE,NULL},
  {11,"Proxy Node Peers"     ,smpapi_qry_prx_peers  ,NULL,FALSE,query_prx_peers_dialog},
  {MENU_END,NULL,NULL,NULL,TRUE,NULL}
  };

menu query_menu[] =
  {
  query_entries,              /* Menu entries contained in main_entries  */
  "\nChoose one of the following items to query:\n"
  };


/*----------------------------------------------------------------------*/
/* U t i l i t i e s    M e n u                                        */
/*======================================================================*/
/* Definition for the sample API utilities  menu.                           */
/*----------------------------------------------------------------------*/

menu_entry utilities_entries[]=
  {
  {0,"Access Delete"   ,smpapi_del_access ,NULL,FALSE,del_access_dialog},
  {1,"Backup Delete"   ,smpapi_del_backup ,NULL,FALSE,query_backup_dialog},
  {2,"Archive Delete"  ,smpapi_del_archive,NULL,FALSE,query_archive_dialog},
  {3,"Filespace Delete",smpapi_del_fs     ,NULL,FALSE,delete_fs_dialog},
  {4,"Backup Update"   ,smpapi_update_obj ,NULL,FALSE,update_obj_dialog},
  {5,"Filespace Update",smpapi_update_fs  ,NULL,FALSE,update_fs_dialog},
  {6,"Log Event"       ,smpapi_log_event  ,NULL,FALSE,log_event_dialog},
  {7,"Set Access"      ,smpapi_set_access ,NULL,FALSE,set_access_dialog},
  {8,"Archive Update"  ,smpapi_update_arc ,NULL,FALSE,update_arc_dialog},
  {9,"Quit"            ,smpapi_utilities_exit,NULL,TRUE ,NULL},
  {10,"Object Rename"  ,smpapi_rename_obj ,NULL,FALSE,rename_obj_dialog},
  {11,"Object Delete"  ,smpapi_del_obj ,NULL,FALSE,delete_obj_dialog},
  {12,"Retention Event" ,smpapi_ret_event  ,NULL,FALSE,ret_event_dialog},
  {13,"Sleep"          ,smpapi_sleep      ,NULL,FALSE,sleep_dialog},
  {14,"Object Update"  ,smpapi_update_objEx ,NULL,FALSE,update_objEx_dialog},
  {MENU_END,NULL,NULL,NULL,TRUE,NULL}
  };

menu utilities_menu[] =
  {
  utilities_entries,             /* Menu entries for this menu item.        */
  "\nChoose one of the following actions:\n"
  };

/*----------------------------------------------------------------------*/
/* P r e f   M e n u                                                    */
/*======================================================================*/
/* Definition for the system preferences menu.                          */
/*----------------------------------------------------------------------*/

menu_entry pref_entries[]=
  {
  {0,"Env SetUp"               ,smpapi_setup        ,NULL,FALSE,setup_dialog},
  {1,"Query Preferences"       ,smpapi_pref_query   ,NULL,FALSE,NULL},
  {2,"Set send buffer size:"   ,smpapi_pref_sendbuff,NULL,FALSE,NULL},
  {3,"Set receive buffer size:",smpapi_pref_recvbuff,NULL,FALSE,NULL},
  {4,"Use verbose output?"     ,smpapi_pref_verbose ,NULL,FALSE,NULL},
  {5,"Max restore items:"      ,smpapi_pref_restitem,NULL,FALSE,NULL},
  {6,"Show details on queries?",smpapi_pref_details ,NULL,FALSE,NULL},
  {7,"Use size est. on sends?" ,smpapi_pref_sizeest ,NULL,FALSE,NULL},
  {8,"Echo input?"             ,smpapi_pref_echoin  ,NULL,FALSE,NULL},
  {9,"Quit"                    ,smpapi_pref_exit,NULL,TRUE ,NULL},
  {MENU_END,NULL,NULL,NULL,TRUE,NULL}
  };

menu pref_menu[] =
  {
  pref_entries,               /* Menu entries for this menu item.        */
  "\nChoose one of the following preference items to change:\n"
  };

/*----------------------------------------------------------------------*/
/* O f f s e t  M e n u                                                 */
/*======================================================================*/
/* Definition for the system no offset menu.                            */
/*----------------------------------------------------------------------*/

menu_entry offset_entries[]=
  {
  {1,"Restore Without Prompt" ,smpapi_restore2 ,NULL,FALSE,query_backup_dialog},
  {2,"Retrieve Without Prompt",smpapi_retrieve2,NULL,FALSE,query_archive_dialog}
,
  {3,"Quit"                  ,smpapi_pref_exit,NULL,TRUE ,NULL},
  {MENU_END,NULL,NULL,NULL,TRUE,NULL}
  };

menu offset_menu[] =
  {
  offset_entries,               /* Menu entries for this menu item.        */
  "\nChoose either Restore or Retrieve without the offset prompt:\n"
  };

/*----------------------------------------------------------------------*/
/* M a i n   M e n u                                                    */
/*======================================================================*/
/* Definition for the sample API main menu.  The sample API is a simple */
/* table driven application that exercises the various functions of the */
/* DSM API.  This table defines the main functions that the sample      */
/* application will perform under user control.                         */
/*----------------------------------------------------------------------*/
menu_entry main_entries[]=
  {
  { 0,"Signon"          ,smpapi_signon  ,NULL      ,FALSE,signon_dialog},
  { 1,"Backup"          ,smpapi_backup  ,NULL      ,FALSE,backup_dialog},
  { 2,"Restore"         ,smpapi_restore ,NULL      ,FALSE,query_backup_dialog},
  { 3,"Archive"         ,smpapi_archive ,NULL      ,FALSE,archive_dialog},
  { 4,"Retrieve"        ,smpapi_retrieve,NULL      ,FALSE,query_archive_dialog},
  { 5,"Queries"         ,NULL           ,query_menu,FALSE,NULL},
  { 6,"Change Password" ,smpapi_chgpw   ,NULL      ,FALSE,NULL},
  { 7,"Utilities : Deletes, Updates, Logevent, SetAccess, RetentionEvent",NULL,utilities_menu,FALSE,NULL},
  { 8,"Set preferences, envSetUp" ,NULL           ,pref_menu ,FALSE,NULL},
  { 9,"Exit to system"  ,smpapi_exit    ,NULL      ,TRUE ,NULL},
  {10,"Restore/Retrieve Without Offset Prompt",NULL,offset_menu,FALSE,NULL},
  {11,"Extended Signon" ,smpapi_ex_signon,NULL     ,FALSE,signon_ex_dialog},
  {MENU_END,NULL,NULL,NULL,TRUE,NULL}
  };

menu main_menu[]=
  {
  main_entries,               /* Menu entries contained in main_entries  */
  "\nChoose one of the following actions to test:\n"
  };

#endif /* _DAPIDATA_H */

