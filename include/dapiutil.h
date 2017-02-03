/***********************************************************************
* Name:
*        dapiutil.h
***********************************************************************/
#define INPUT_BUFFER_SIZE 2048

extern void format_number(char *s_in, char *s_out);
extern void initFS(regFSData *fsDataP);
extern void ourGetS(char *buf);
extern void ourGetString(char *buf,int bufferLength);
extern void FSInfoResp(char *fs_info, qryRespFSData *fsResp);
extern void UpdateFileSpace(dsmFSUpd *fsDataP, char *fsinfo);
