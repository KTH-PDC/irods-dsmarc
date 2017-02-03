
/**************************************************************************/
/* Header File Name: dapiproc.h                                           */
/*                                                                        */
/* Descriptive-name: Tivoli Storage Manager API function prototypes       */ 
/**************************************************************************/
#ifndef _H_DAPIPROC
#define _H_DAPIPROC
/*========================================================================*/
/*               P U B L I C   F U N C T I O N S                          */
/*========================================================================*/

typedef dsInt16_t (*func_proto)(dialog *, dsUint16_t );

extern dsInt16_t perform_send      (dialog *dlg,dsUint16_t parm1);
extern dsInt16_t perform_signon    (dialog *dlg,dsUint16_t parm1);
extern dsInt16_t perform_query_fs  (dialog *dlg,dsUint16_t parm1);
extern dsInt16_t perform_query_mc  (dialog *dlg,dsUint16_t parm1);
extern dsInt16_t perform_query_get (dialog *dlg,dsUint16_t parm1);
extern dsInt16_t perform_log_event (dialog *dlg,dsUint16_t parm1);
extern dsInt16_t perform_set_access(dialog *dlg,dsUint16_t parm1);
extern dsInt16_t perform_del_access(dialog *dlg,dsUint16_t parm1);
extern dsInt16_t perform_update_obj(dialog *dlg,dsUint16_t parm1);
extern dsInt16_t perform_update_objEx(dialog *dlg,dsUint16_t parm1);
extern dsInt16_t perform_update_arc(dialog *dlg,dsUint16_t parm1);
extern dsInt16_t perform_update_fs (dialog *dlg,dsUint16_t parm1);
extern dsInt16_t perform_setup     (dialog *dlg,dsUint16_t parm1);
extern dsInt16_t perform_rename_obj(dialog *dlg,dsUint16_t parm1);
extern dsInt16_t perform_del_obj   (dialog *dlg,dsUint16_t parm1);
extern dsInt16_t perform_ret_event (dialog *dlg,dsUint16_t parm1);
extern dsInt16_t perform_sleep     (dialog *dlg,dsUint16_t parm1);
extern dsInt16_t perform_query_prx (dialog *dlg,dsUint16_t parm1);
extern void  rcApiOut          (dsUint32_t dsmHandle, dsInt16_t rc); 

extern dsInt16_t smpapi_exit(dialog *sel_dialog);
extern dsInt16_t smpapi_signon(dialog *sel_dialog);
extern dsInt16_t smpapi_backup(dialog *sel_dialog);
extern dsInt16_t smpapi_restore(dialog *sel_dialog);
extern dsInt16_t smpapi_restore2(dialog *sel_dialog);
extern dsInt16_t smpapi_archive(dialog *sel_dialog);
extern dsInt16_t smpapi_retrieve(dialog *sel_dialog);
extern dsInt16_t smpapi_retrieve2(dialog *sel_dialog);
extern dsInt16_t smpapi_chgpw(dialog *sel_dialog);
extern dsInt16_t smpapi_query_exit(dialog *sel_dialog);
extern dsInt16_t smpapi_qry_access(dialog *sel_dialog);
extern dsInt16_t smpapi_qry_backup(dialog *sel_dialog);
extern dsInt16_t smpapi_qry_archive(dialog *sel_dialog);
extern dsInt16_t smpapi_qry_mc(dialog *sel_dialog);
extern dsInt16_t smpapi_qry_fs(dialog *sel_dialog);
extern dsInt16_t smpapi_qry_sess(dialog *sel_dialog);
extern dsInt16_t smpapi_qry_version(dialog *sel_dialog);
extern dsInt16_t smpapi_qry_cliOptions(dialog *sel_dialog);
extern dsInt16_t smpapi_qry_sessOptions(dialog *sel_dialog);
extern dsInt16_t smpapi_utilities_exit(dialog *sel_dialog);
extern dsInt16_t smpapi_del_backup(dialog *sel_dialog);
extern dsInt16_t smpapi_del_archive(dialog *sel_dialog);
extern dsInt16_t smpapi_update_obj(dialog *sel_dialog);
extern dsInt16_t smpapi_update_objEx(dialog *sel_dialog);
extern dsInt16_t smpapi_update_arc(dialog *sel_dialog);
extern dsInt16_t smpapi_update_fs(dialog *sel_dialog);
extern dsInt16_t smpapi_del_fs(dialog *sel_dialog);
extern dsInt16_t smpapi_del_access(dialog *sel_dialog);
extern dsInt16_t smpapi_log_event(dialog *sel_dialog);
extern dsInt16_t smpapi_set_access(dialog *sel_dialog);
extern dsInt16_t smpapi_pref_query(dialog *sel_dialog);
extern dsInt16_t smpapi_pref_sendbuff(dialog *sel_dialog);
extern dsInt16_t smpapi_pref_recvbuff(dialog *sel_dialog);
extern dsInt16_t smpapi_pref_verbose(dialog *sel_dialog);
extern dsInt16_t smpapi_pref_restitem(dialog *sel_dialog);
extern dsInt16_t smpapi_pref_details(dialog *sel_dialog);
extern dsInt16_t smpapi_pref_sizeest(dialog *sel_dialog);
extern dsInt16_t smpapi_pref_echoin(dialog *sel_dialog);
extern dsInt16_t smpapi_pref_exit(dialog *sel_dialog);
extern dsInt16_t smpapi_ret_event(dialog *sel_dialog);
extern dsInt16_t smpapi_setup(dialog *sel_dialog);
extern dsInt16_t smpapi_del_obj(dialog *sel_dialog);
extern dsInt16_t smpapi_rename_obj(dialog *sel_dialog);
extern dsInt16_t smpapi_pref_exit(dialog *sel_dialog);
extern dsInt16_t smpapi_sleep(dialog *sel_dialog);
extern dsInt16_t smpapi_ex_signon(dialog *sel_dialog);
extern dsInt16_t smpapi_qry_prx_auth(dialog *sel_dialog);
extern dsInt16_t smpapi_qry_prx_peers(dialog *sel_dialog);

#endif /* _H_DAPIPROC */
