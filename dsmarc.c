
/* DSMARC.C is an archive/retieve utility for iRODS using the TSM API. */

/* System include files. */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

/* TSM API include files. */
#include "dsmapitd.h"
#include "tsmapitd.h"
#include "dsmapifp.h"
#include "tsmapifp.h"
#include "dsmapips.h"
#include "dsmrc.h"
#include "dapitype.h"
#include "dapiproc.h"

/* Bail out if not POSIX. */
#ifndef _POSIX_VERSION
#error We do only POSIX
#endif

/* End of string character. */
#define EOS ((char) '\0')

/* Newline character. */
#define NL ((char) '\n')

/* Blank character. */
#define SPACE ((char) ' ')

/* Default debug level. */
#define DEFAULT_DEBUG_LEVEL ((int) 0)

/* Maximum path length. Hope we got the POSIX stuff. */
#ifndef PATH_MAX
#ifdef _POSIX_PATH_MAX
#define PATH_MAX _POSIX_PATH_MAX
#else
#define PATH_MAX ((int) 255)
#endif
#endif

/* Comment string length. */
#define COMMENT_STRING_MAX ((int) 255)

/* Time maximum length all long formats. */
#define TIMEMAX ((int) 128)

/* ISO standard date format string. */
#define DEFAULT_DATE_FORMAT "%Y-%m-%dT%H:%M:%S"

/* iRODS standard date format string, almost ISO. */
#define IRODS_DATE_FORMAT "%Y-%m-%d-%H.%M.%S"

/* ISO printf format to convert from TSM. */
#define ISO_PRINTF_FORMAT "%04d-%02d-%02dT%02d:%02d:%02d"

/* iRODS date format string to convert from TSM. */
#define IRODS_PRINTF_FORMAT "%04d-%02d-%02d-%02d.%02d.%02d"

/* Length of date string is 20 + 1. Tsm may return year 65535. */
#define DATE_LENGTH ((int) 32)

/* Default I/O buffer size. */
#define DEFAULT_BUFFER_SIZE ((size_t) 1048576)

/* Boolean literals. */
#ifndef true
#define true ((int) 1)
#endif
#ifndef true
#define true ((int) 0)
#endif

/* Exit codes. */
#define SUCCESS ((int) 0)
#define FAILURE ((int) 1)

/* Our objInfo structure. Contains extra information about an archive file.  */
typedef struct
{

	/* Version and magic. */
	unsigned long version;

	/* Copy of the original stat info. */
	struct stat sb;
} ourInfo;

/* Version and magic for ourInfo. */
#define OURINFO_VERSION 0xfefefefe00000001

/* Object type on the TSM server. */
typedef enum
{
	file,
	directory,
	any
} object_type_t;

/* Comment in TSM info fields. */
#define IRODS_TSM_COMMENT "iRODS TSM API"

/* Globals to store query results. */

/* Maximum number of query results. */
#define MAX_QR 1024

/* Global definitions. */

/* Debug level. */
static int debug = DEFAULT_DEBUG_LEVEL;

/* Force actions. */
static int forced = false;

/* Sort by restore order. */
static int restoreorder = false;

/* Query responses. */
static qryRespArchiveData *qr = NULL;

/* Query responses index, the number of responses returned. */
static int nqr = 0;

/* Query response array size. */
static int maxqr = MAX_QR;

/* Maximum number of TSM object handles. */
#define MAX_HANDLES 1024

/* Global end of file flag array for TSM objects.
   We think that the TSM object handle is a small integer. */
int eof_flags[MAX_HANDLES];

/* Print message. */

static void
msg (const char *format, ...)
{
	va_list args;

	va_start (args, format);
	(void) vfprintf (stdout, format, args);
	va_end (args);
	(void) fprintf (stdout, "\n");
}

/* Simple error report and exit. */

static void
error (const char *format, ...)
{
	va_list args;

	/* Print error message. */
	va_start (args, format);
	(void) vfprintf (stderr, format, args);
	va_end (args);
	(void) fprintf (stderr, "\n");

	/* Add errno info. Paranoid flush. */
	if (errno != 0)
	{
		perror ("Errno info");
	}
	(void) fflush (stderr);
	exit (FAILURE);
}

/* Allocate memory. */

static void *
allocate (size_t s)
{
	void *p;

	p = malloc (s);
	if (p == NULL)
	{
		error ("Cannot allocate memory");
	}
	return (p);
}

/* Compare strings. */

static int
seq (const char *a, const char *b)
{
	int status;

	status = strcasecmp (a, b);
	return (status == 0);
}

/* Safe copy. */

static void
scp (char *d, const char *s, size_t n)
{
	size_t len;
	char *r;
	const char *from;
	char *to;
	size_t i;
	char ch;

	/* Set up from and to pointers. */
	from = s;
	if (d == (char *) NULL)
	{

		/* Destination is NULL, allocate space for string + EOS. */
		len = strlen (s) + 1;
		if (len > n)
		{
			error ("Dynamic allocation but specified size %lu is small", n);
		}
		r = (char *) allocate (len);
		to = r;
	}
	else
	{
		len = n;
		r = d;
		to = d;
	}
	i = (size_t) 0;
	ch = *from;
	while (ch != EOS)
	{

		/* Copy. */
		*to = ch;

		/* Move forward and get the next character. */
		from++;
		to++;
		ch = *from;
		i++;

		/* Abort if it would not fit. */
		if (i >= len)
		{
			error ("Destination string cannot fit %lu characters plus EOS", i);
		}
	}

	/* All copied, append EOS. */
	*to = EOS;
}

/* String append, until eos but not more than n characters. */

static char *
sapp (char *d, const char *s, size_t n)
{
	size_t len;
	size_t dlen;
	char *r;
	const char *from;
	char *to;
	size_t i;
	char ch;

	/* Set up from and to pointers. */
	from = s;
	if (d == (char *) NULL)
	{

		error ("Destination is null for function sapp");
	}
	else
	{
		dlen = strlen (d) + 1;
		len = n - dlen;
		r = d;
		to = d + dlen - 1;
	}
	i = (size_t) 0;
	ch = *from;
	while (ch != EOS)
	{

		/* Copy. */
		*to = ch;

		/* Move forward and get the next character. */
		from++;
		to++;
		ch = *from;
		i++;

		/* Abort if it would not fit. */
		if (i > len)
		{
			error ("Destination string cannot fit %lu characters plus EOS", i);
		}
	}

	/* All copied, append EOS. */
	*to = EOS;
	return (r);
}

/* Print tsm format message. */

static void
tmsg (const char *desc, const char *format, ...)
{
	va_list args;

	fprintf (stdout, "%38s: ", desc);
	va_start (args, format);
	(void) vfprintf (stdout, format, args);
	va_end (args);
	(void) fprintf (stdout, "\n");
}

/* Open file for reading. */

static int
open_file_read (char *filename)
{
	int status;

	status = open (filename, O_RDONLY|O_NOATIME);
	if (status == -1)
	{
		error ("Could not open local file %s", filename);
	}
	return (status);
}

/* Open file for writing. */

static int
open_file_write (char *filename)
{
	int status;

	/* Old umask. */
	mode_t umold;

	/* Creation modes for files. */
	mode_t owrgron = (mode_t) 00640;
	mode_t owrgwron = (mode_t) 00660;

	/* Umasks with various protections. */
	mode_t mask_owrgwron = (mode_t) 00002;
	mode_t mask_owrgron = (mode_t) 00027;
	mode_t mask_none = (mode_t) 00777;

	/* Open as owner:rw, group:rw, others:none.
	   Create file. Do not overwrite. Lock while writing. */
	umold = umask (mask_owrgwron);
	status = open (filename, O_RDWR|O_CREAT|O_EXCL, owrgwron);
	(void) umask ((mode_t) umold);
	if (status == -1)
	{
		error ("Could not open local file %s", filename);
	}
	return (status);
}

/* Close file. */

static void
close_file (int fd)
{
	int status;

	status = close (fd);
	if (status == -1)
	{
		error ("Could not close local file %d", fd);
	}
}

/* Read from file. */

static ssize_t
read_file (int fd, void *buf, size_t len)
{
	ssize_t status;

	status = read (fd, buf, len);
	if (status == -1)
	{
		error ("Error reading local file %d", fd);
	}
	return (status);
}

/* Write file. */

static ssize_t
write_file (int fd, void *buf, size_t len)
{
	ssize_t status;

	status = write (fd, buf, len);
	if (status == -1)
	{
		error ("Error writing local file %d", fd);
	}
	if (status != (ssize_t) len)
	{
		error ("Short write on local file %d", fd);
	}
	return (status);
}

/* Stat file. */

static void
stat_file (char *filename, struct stat *sb)
{
	int status;

	status = stat (filename, sb);
	if (status == -1)
	{
		error ("Stat failed for local file %s", filename);
	}
}

/* Initialize stat block. */

static void
init_stat (struct stat *sb)
{
	time_t now;
	struct passwd *passwd;

	/* Zero fill structure. */
	(void) memset (sb, 0, sizeof (struct stat));

	/* Get current timestamp and uid/gid. */
	now = time (NULL);
	passwd = getpwuid (getuid ());
	if (passwd == NULL)
	{
		error ("getpwuid failed in init_stat");
	}

	/* Initialize. */
	sb->st_dev = 0;
	sb->st_ino = 0;
	sb->st_mode = 00660;
	sb->st_nlink = 0;
	sb->st_uid = passwd->pw_uid;
	sb->st_gid = passwd->pw_gid;
	sb->st_rdev = 0;
	sb->st_blksize = 0;
	sb->st_blocks = 0;
	sb->st_atime = now;
	sb->st_mtime = now;
	sb->st_ctime = now;

	/* TSM will need some size estimate. */
	sb->st_size = DEFAULT_BUFFER_SIZE;
}

/* Parse path name to filespace, low level name and high level name. */

static void
parse_path (char *fs, char *hl, char *ll, char *path)
{
	size_t len;
	char *p;
	int n;

	/* Check. */
	if (*path != '/')
	{
		error ("Pathname should be absolute");
	}
	len = strlen (path);
	if (len > (size_t) (PATH_MAX - 1))
	{
		error ("Pathname is too long");
	}
	if (*(path + len - 1) == '/')
	{
		error ("Trailing slash - wrong");
	}

	/* First part of the pathname will be the filespace name. */
	n = 0;
	p = path;
	*fs = *p;
	p++;
	fs++;
	n++;
	while (*p != '/')
	{
		*fs = *p;
		p++;
		fs++;
		n++;
		if (n > DSM_MAX_FSNAME_LENGTH)
		{
			error ("Filespace name too long");
		}
	}
	*fs = EOS;

	/* Second path is the high level name, which is the directory name. */
	n = 0;
	p = path;
	*hl = *p;
	p++;
	hl++;
	n++;
	while (*p != EOS)
	{
		*hl = *p;
		p++;
		hl++;
		n++;
		if (n > DSM_MAX_HL_LENGTH)
		{
			error ("HL name too long");
		}
	}
	*hl = EOS;

	/* Copied the whole thing now scan from the back to find the slash.
	   Overwrite the slash with EOS. */
	while (*hl != '/')
	{
		hl--;
	}
	*hl = EOS;

	/* Now copy out the low level name. Should start with a slash. */
	n = 0;
	*ll = '/';
	hl++;
	ll++;
	n++;
	*ll = *hl;
	hl++;
	ll++;
	n++;
	while (*hl != EOS)
	{
		*ll = *hl;
		hl++;
		ll++;
		n++;
		if (n > DSM_MAX_LL_LENGTH)
		{
			error ("LL name too long");
		}
	}
	*ll = EOS;
}

/* Print error message and exit TSM API. */

static void
tsm_error (dsUint32_t handle, dsInt16_t status, const char *format, ...)
{
	dsUint16_t reason = DSM_RS_ABORT_SYSTEM_ERROR;
	va_list args;
	dsInt16_t rcmsg_status;
	char rcmsg[DSM_MAX_RC_MSG_LENGTH];
	char *cp;

	/* Terminate the transaction if any. */
	(void) dsmEndTxn (handle, DSM_VOTE_ABORT, &reason);

	/* Get TSM status message. Cut newline at start and at the end. */
	*rcmsg = EOS;
	rcmsg_status = dsmRCMsg (handle, status, rcmsg);
	cp = (char *) rcmsg;
	*cp = SPACE;
	cp = (char *) (rcmsg + strlen (rcmsg) - 1);
	*cp = SPACE;

	/* Finish with TSM. */
	(void) dsmTerminate (handle);
	(void) dsmCleanUp(DSM_MULTITHREAD);

	/* Print error message and quit. */
	va_start (args, format);
	(void) vfprintf (stderr, format, args);
	va_end (args);
	(void) fprintf (stderr, "\n");
	if (status != (dsInt16_t) 0)
	{
		if (rcmsg_status == 0)
		{

			/* Quit with message retrieved from TSM. */
			error ("TSM API error: %s", rcmsg);
		}
		else
		{

			/* Could not retrieve message for non-zero status code. */
			error ("TSM API error status: %d", (int) status);
		}
	}
	else
	{

		/* TSM status was success error was for other reasons. */
		error ("TSM API was successful but error exit was requested");
	}
}

/* TSM setup. */

static void
tsm_setup (char *argv[])
{

	/* Threaded initialization / setup. We need this only to have
	   multiple streams. */

	/* Environment info for the dsmSetUp call. */
	envSetUp envsetup;

	/* TSM status. */
	dsInt16_t status;

	/* For dsmSetUp. */
	(void) memset (&envsetup, 0, sizeof(envSetUp));
	envsetup.stVersion = envSetUpVersion;
	strcpy (envsetup.dsmiDir, "");
	strcpy (envsetup.dsmiConfig, "");
	strcpy (envsetup.dsmiLog, "");
	strcpy (envsetup.logName, "");
	envsetup.argv = argv;

	/* Initialize. */
	status = dsmSetUp (DSM_MULTITHREAD, &envsetup);
	if (status != DSM_RC_OK)
	{
		(void) dsmCleanUp (DSM_MULTITHREAD);
		error ("Calling dsmSetUp failed with %d", status);
	}
}

/* Initialize the TSM API. */

static dsUint32_t
tsm_init (void)
{
	dsmInitExIn_t exin;
	dsmInitExOut_t exout;
	dsmApiVersionEx exver;
	dsUint32_t handle;
	dsInt16_t status;
	ApiSessInfo sessinfo;

	/* Checks. */
	if (sizeof (off_t) * CHAR_BIT != 64)
	{
		error ("Offsets should be 64-bit");
	}
	if (sizeof (unsigned long) * CHAR_BIT != 64)
	{
		error ("Word size should be 64-bit");
	}
	if (sizeof (ourInfo) > DSM_MAX_OBJINFO_LENGTH)
	{
		error ("ourInfo structure became too big");
	}

	/* Zero and load parameter blocks. */
	(void) memset (&exver, 0, sizeof (dsmApiVersionEx));
	exver.stVersion  = apiVersionExVer;
	exver.version = DSM_API_VERSION;
	exver.release = DSM_API_RELEASE;
	exver.level = DSM_API_LEVEL;
	exver.subLevel = DSM_API_SUBLEVEL;
	(void) memset (&exin, 0, sizeof (dsmInitExIn_t));
	exin.stVersion = dsmInitExInVersion;
	exin.apiVersionExP = &exver;
	exin.clientNodeNameP = NULL;
	exin.clientOwnerNameP = NULL;
	exin.clientPasswordP = NULL;
	exin.applicationTypeP = NULL;
	exin.configfile = NULL;
	exin.options = NULL;
	exin.userNameP = NULL;
	exin.userPasswordP = NULL;
	exin.dirDelimiter = '\0';
	exin.useUnicode = dsmFalse;
	exin.bEncryptKeyEnabled = dsmFalse;
	exin.encryptionPasswordP = NULL;
	(void) memset (&exout, 0, sizeof (dsmInitExOut_t));
	exout.stVersion = dsmInitExOutVersion;

	/* Initialize and get handle. */
	status = dsmInitEx (&handle, &exin, &exout);
	if (status != DSM_RC_OK)
	{

		/* Failure, bail out. */
		tsm_error (handle, status, "dsmInitEx failed");
	}

	/* Get session info. */
	(void) memset (&sessinfo, 0, sizeof (ApiSessInfo));
	sessinfo.stVersion = ApiSessInfoVersion;
	status = dsmQuerySessInfo (handle, &sessinfo);
	if (status != DSM_RC_OK)
	{

		/* Failure, bail out. */
		tsm_error (handle, status, "dsmQuerySessInfo failed");
	}

	/* Success, return handle. */
	return (handle);
}

/* Finish using the TSM API. */

static void
tsm_exit (dsUint32_t handle)
{

	/* Reason code for dsmEndTxn. */
	dsUint16_t reason;

	/* Close transaction with commit just to be on the safe side. */
	reason = 0;
	(void) dsmEndTxn (handle, DSM_VOTE_COMMIT, &reason);
	(void) dsmCleanUp (DSM_MULTITHREAD);
	(void) dsmTerminate (handle);
}

/* Send data to the server. */

static void
tsm_send_data (dsUint32_t handle, void *buffer, size_t bufsize)
{
	DataBlk data;
	dsInt16_t status;

	/* Fill out data block structure. */
	data.stVersion = DataBlkVersion;
	data.bufferLen = bufsize;
	data.numBytes  = 0;
	data.bufferPtr = (char *) buffer;

	/* Call API. */
	status = dsmSendData (handle, &data);
	if (status != DSM_RC_OK)
	{
		tsm_error (handle, status, "Cannot send data");
	}

	/* Number of bytes transferred returned in numBytes, check. */
	if (data.numBytes != data.bufferLen)
	{
		tsm_error (handle, status, "Short send to TSM");
	}
}

/* Create object conforming to a local file. */

static void
tsm_create_object (dsUint32_t handle, object_type_t o,
	struct stat *s, char *path)
{

	/* Type of filespace and info, used when filespace is to be created. */
	char filespace_type[COMMENT_STRING_MAX];
	char filespace_info[COMMENT_STRING_MAX];

	/* TSM object name structure. */
	dsmObjName name;

	/* TSM filespace, high level and low level names. */
	char fs[DSM_MAX_FSNAME_LENGTH + 1];
	char hl[DSM_MAX_HL_LENGTH + 1];
	char ll[DSM_MAX_LL_LENGTH + 1];

	/* TSM object attributes structure. */
	ObjAttr attr;

	/* Passwd entry. */
	struct passwd *passwd;

	/* Status block local copy. */
	struct stat sb;

	/* Current time. */
	time_t now;

	/* Object info. */
	ourInfo objinfo;

	/* Archive description. */
	char archive_descr[COMMENT_STRING_MAX];

	/* Filespace data. */
	regFSData fsdata;

	/* TSM status. */
	dsInt16_t status;

	/* Management class bind info. */
	mcBindKey mcinfo;

	/* Archive extra data. */
	sndArchiveData archdata;

	/* Initialize comment fields. */
	scp (filespace_type, IRODS_TSM_COMMENT, COMMENT_STRING_MAX);
	scp (filespace_info, IRODS_TSM_COMMENT, COMMENT_STRING_MAX);

	/* Initialize object name structure.
	   Get the path. We think it's a mounted file system so the
	   filespace name is the same as the first word of the path. */
	(void) memset (&name, 0, sizeof (dsmObjName));
	parse_path (fs, hl, ll, path);
	scp (name.fs, fs, DSM_MAX_FSNAME_LENGTH);
	scp (name.hl, hl, DSM_MAX_HL_LENGTH);
	scp (name.ll, ll, DSM_MAX_LL_LENGTH);
	switch (o)
	{
	case file:
		name.objType = DSM_OBJ_FILE;
		break;
	case directory:
		name.objType = DSM_OBJ_DIRECTORY;
		break;
	case any:
		error ("Archive object %s can not have type ANY", path);
		break;
	}

	/* Now the attributes structure. */
	(void) memset (&attr, 0, sizeof (ObjAttr));
	attr.stVersion = ObjAttrVersion;

	/* Object owner is our username string. */
	passwd = getpwuid (getuid ());
	if (passwd == NULL)
	{
		error ("getpwuid failed");
	}
	scp (attr.owner, passwd->pw_name, 32);

	/* Deal with the size estimate and get status block if any. */
	if (s != NULL)
	{

		/* Copy the status block and set the size attributes. */
		(void) memcpy (&sb, s, sizeof (struct stat));
		attr.sizeEstimate.hi = sb.st_size >> 32;
		attr.sizeEstimate.lo = sb.st_size & 0x00000000ffffffff;
	}
	else
	{
		/* Just zero for attributes. */
		attr.sizeEstimate.hi = 0;
		attr.sizeEstimate.lo = 0;

		/* No status block given, reasonable defaults. */
		(void) memset (&sb, 0, sizeof (struct stat));
		now = time (NULL);
		sb.st_dev = 0;
		sb.st_ino = 0;
		sb.st_mode = 00660;
		sb.st_nlink = 0;
		sb.st_uid = passwd->pw_uid;
		sb.st_gid = passwd->pw_gid;
		sb.st_rdev = 0;
		sb.st_size = (off_t) 0;
		sb.st_blksize = (u_long) 0;
		sb.st_blocks = (u_long) 0;
		sb.st_atime = now;
		sb.st_mtime = now;
		sb.st_ctime = now;
	}

	/* Load our object info block into the attr structure. */
	(void) memset (&objinfo, 0, sizeof (ourInfo));
	objinfo.version = OURINFO_VERSION;
	(void) memcpy (&objinfo.sb, &sb, sizeof (struct stat));
	attr.objInfo = (char *) &objinfo;
	attr.objInfoLength = sizeof (ourInfo);

	/* Others. */
	attr.mcNameP = NULL;

	/* Register the file space if needed. */
	(void) memset (&fsdata, 0, sizeof (regFSData));
	fsdata.stVersion = regFSDataVersion;
	fsdata.fsName = fs;
	fsdata.fsType = filespace_type;
	(void) strcpy(fsdata.fsAttr.unixFSAttr.fsInfo, filespace_info);
	fsdata.fsAttr.unixFSAttr.fsInfoLength =
		strlen(filespace_info) + 1;
	fsdata.occupancy.hi = 0;
	fsdata.occupancy.lo = 0;
	fsdata.capacity.hi = 0;
	fsdata.capacity.lo = 1073741824;
	status = dsmRegisterFS (handle, &fsdata);
	if (status != DSM_RC_OK)
	{
		if (status != DSM_RC_FS_ALREADY_REGED)
		{
			tsm_error (handle, status, "Cannot register filespace %s", fs);
		}
	}

	/* Open the transaction. */
	status = dsmBeginTxn (handle);
	if (status != DSM_RC_OK)
	{
		tsm_error (handle, status, "dsmBeginTxn failed");
	}

	/* Bind management class and check. */
	(void) memset (&mcinfo, 0, sizeof (mcBindKey));
	mcinfo.stVersion = mcBindKeyVersion;
	status = dsmBindMC (handle, &name, stArchive, &mcinfo);
	if (status != DSM_RC_OK)
	{
		tsm_error (handle, status, "Cannot bind management class for %s", path);
	}
	if (!mcinfo.archive_cg_exists)
	{
		tsm_error (handle, status, "Cannot find archive copygroup");
	}

	/* Set description. */
	(void) memset (&archdata, 0, sizeof (sndArchiveData));
	archdata.stVersion = sndArchiveDataVersion;
	scp (archive_descr, "", COMMENT_STRING_MAX);
	archdata.descr = archive_descr;

	/* Create object reference. */
	status = dsmSendObj (handle, stArchive, (void *) &archdata,
		&name, &attr, NULL);
	if (status != DSM_RC_OK)
	{
		tsm_error (handle, status, "dsmSendObj failed for %s", path);
	}
}

/* Finish with the object. End sending the object and close transaction. */

static void
tsm_finish_with_object (dsUint32_t handle)
{

	/* TSM status. */
	dsInt16_t status;

	/* Reason code for dsmEndTxn. */
	dsUint16_t reason;

	/* Object finished. */
	status = dsmEndSendObj (handle);
	if (status != DSM_RC_OK)
	{
		tsm_error (handle, status, "dsmEndSendObj failed");
	}

	/* Close transaction assuming success. */
	reason = (dsUint16_t) 0;
	status = dsmEndTxn (handle, DSM_VOTE_COMMIT, &reason);
	if (status != DSM_RC_OK)
	{
		tsm_error (handle, status, "dsmEndTxn failed");
	}
	if (reason != 0)
	{
		tsm_error (handle, status, "dsmEndTxn failed on reason %d", reason);
	}
}

/* Archive an object. */

static void
tsm_archive (dsUint32_t handle, object_type_t o, unsigned long blocksize,
	char *localpath, char *path)
{

	/* File stat block info. */
	struct stat sb;

	/* TSM status. */
	dsInt16_t status;

	/* File handle. */
	int fd;

	/* Buffer size. */
	size_t bufsize;

	/* Buffer. */
	char *buffer;

	/* Number of bytes transferred. */
	ssize_t nbytes;

	/* Reason code for dsmEndTxn. */
	dsUint16_t reason;

	/* Write file or create directory. */
	if (o == file)
	{

		/* Read through the file and send. */
		bufsize = (size_t) blocksize;
		buffer = (char *) allocate (bufsize);
		if (seq (localpath, "-"))
		{

			/* Streaming from stdin, init stat block. */
			init_stat (&sb);
			fd = (int) 0;
		}
		else
		{

			/* Local file, get stat block and open. */
			stat_file (localpath, &sb);
			fd = open_file_read (localpath);
		}
		tsm_create_object (handle, o, &sb, path);
		nbytes = read_file (fd, buffer, bufsize);
		while (nbytes != 0)
		{
			tsm_send_data (handle, buffer, nbytes);
			nbytes = read_file (fd, buffer, bufsize);
		}
		free (buffer);
		close_file (fd);
	}
	else if (o == directory)
	{
		tsm_create_object (handle, o, NULL, path);
	}
	else
	{

		/* Can't happen. */
		error ("Dodgy object type for %s - confused", path);
	}

	/* Call dsmEndSendObj and close transaction. */
	tsm_finish_with_object (handle);
}

/* Convert internal time to ISO character string. */

static char *
isotime (char *iso, time_t t)
{
	time_t time;
	struct tm *timestruct;
	const char *date_format;
	size_t strftime_status;

	time = t;
	timestruct = localtime (&time);
	if (timestruct == NULL)
	{
		error ("Cannot convert binary time");
	}
	date_format = DEFAULT_DATE_FORMAT;
	strftime_status = strftime (iso, (size_t) TIMEMAX,
		date_format, timestruct);
	if (strftime_status == (size_t) 0)
	{
		error ("Cannot convert time to ISO");
	}
	return (iso);
}

/* Return ISO date from TSM date. */

static char *
tsm2iso (char *iso, dsmDate dsmdate)
{
	static char date[DATE_LENGTH];
	dsmDate *d;

	d = &dsmdate;
	snprintf (date, (size_t) DATE_LENGTH,
		ISO_PRINTF_FORMAT,
		d->year, d->month, d->day, d->hour, d->minute, d->second);
	scp (iso, date, DATE_LENGTH);
	return (date);
}

/* Convert internal time to iRODS format character string. */

static char *
irotime (char *iro, time_t t)
{
	time_t time;
	struct tm *timestruct;
	const char *date_format;
	size_t strftime_status;

	time = t;
	timestruct = localtime (&time);
	if (timestruct == NULL)
	{
		error ("Cannot convert binary time");
	}
	date_format = IRODS_DATE_FORMAT;
	strftime_status = strftime (iro, (size_t) TIMEMAX,
		date_format, timestruct);
	if (strftime_status == (size_t) 0)
	{
		error ("Cannot convert time to iRODS ISO");
	}
	return (iro);
}

/* Return iRODS format date string from TSM date. */

static char *
tsm2iro (char *iro, dsmDate dsmdate)
{
	static char date[DATE_LENGTH];
	dsmDate *d;

	d = &dsmdate;
	snprintf (date, (size_t) DATE_LENGTH,
		IRODS_PRINTF_FORMAT,
		d->year, d->month, d->day, d->hour, d->minute, d->second);
	scp (iro, date, DATE_LENGTH);
	return (date);
}

/* Print archive metadata response. */

static void
tsm_print_archive (qryRespArchiveData *r)
{
	dsStruct64_t s;
	ourInfo *info;
	struct stat *sb;
	char date[DATE_LENGTH];
	char iso[TIMEMAX];

	/* Check. */
	if (r == NULL)
	{
		error ("Argument is NULL for tsm_print_archive");
	}

	/* Print. */
	s = r->sizeEstimate;
	msg ("");
	tmsg ("path", "%s%s%s", r->objName.fs, r->objName.hl, r->objName.ll);
	tmsg ("type", "%d", r->objName.objType);
	tmsg ("filespace", "%s", r->objName.fs);
	tmsg ("management class", "%s", r->mcName);
	tmsg ("copy group", "%lu", r->copyGroup);
	tmsg ("owner", "%s", r->owner);
	tmsg ("objid", "%lu-%lu", r->objId.hi, r->objId.lo);
	tmsg ("description", "%s", r->descr);
	tmsg ("size estimate", "%lu-%lu", s.hi, s.lo);
	tmsg ("insertion date", "%s", tsm2iso (date, r->insDate));
	tmsg ("expiry date", "%s", tsm2iso (date, r->expDate));
	tmsg ("restore order", "%lu-%lu-%lu-%lu-%lu",
		r->restoreOrderExt.top,
		r->restoreOrderExt.hi_hi,
		r->restoreOrderExt.hi_lo,
		r->restoreOrderExt.lo_hi,
		r->restoreOrderExt.lo_lo);

	/* Print our info data. */
	info = (ourInfo *) r->objInfo;
	if (info->version == OURINFO_VERSION)
	{

		/* It is the stat block. */
		sb = (struct stat *) &(info->sb);
		tmsg ("device id", "%lu", sb->st_dev);
		tmsg ("inode", "%lu", sb->st_ino);
		tmsg ("mode", "%04o", sb->st_mode);
		tmsg ("nlink", "%lu", sb->st_nlink);
		tmsg ("uid", "%lu", sb->st_uid);
		tmsg ("gid", "%lu", sb->st_gid);
		tmsg ("device type", "%lu", sb->st_rdev);
		tmsg ("size", "%lu", sb->st_size);
		tmsg ("blocksize", "%lu", sb->st_blksize);
		tmsg ("blocks", "%lu", sb->st_blocks);
		tmsg ("access time", "%s", isotime (iso, sb->st_atime));
		tmsg ("modification time", "%s", isotime (iso, sb->st_atime));
		tmsg ("status change time", "%s", isotime (iso, sb->st_atime));
	}
	else
	{
		tmsg ("ourinfo", "%s", "NULL");
	}
}

/* Print status info as required by iRODS. */

static void
print_stat (qryRespArchiveData *r)
{
	ourInfo *info;
	struct stat *sb;
	char iro[TIMEMAX];

	/* Print our info data. */
	info = (ourInfo *) r->objInfo;
	if (info->version == OURINFO_VERSION)
	{

		/* It is the stat block we need. */
		sb = (struct stat *) &(info->sb);

		/* Print info in iRODS stat format. */
		(void) printf ("%lu:%lu:%04o:%lu:%lu:%lu:%lu:%lu:%lu:%lu:%s:%s:%s\n",
			sb->st_dev,
			sb->st_ino,
			sb->st_mode,
			sb->st_nlink,
			sb->st_uid,
			sb->st_gid,
			sb->st_rdev,
			sb->st_size,
			sb->st_blksize,
			sb->st_blocks,
			irotime (iro, sb->st_atime),
			irotime (iro, sb->st_mtime),
			irotime (iro, sb->st_ctime));
	}
	else
	{
		if (debug > 0 || forced)
		{

			/* Complain but continue. */
			msg ("Wrong magic in stat record");
		}
		else
		{
			error ("Wrong magic in stat record");
		}
	}
}

/* Compare query records by restore order. */

static int
cmprestoreorderext (const void *r1, const void *r2)
{
	qryRespArchiveData *q1;
	qryRespArchiveData *q2;
	dsUint160_t *ro1;
	dsUint160_t *ro2;

	q1 = (qryRespArchiveData *) r1;
	q2 = (qryRespArchiveData *) r2;
	ro1 = &q1->restoreOrderExt;
	ro2 = &q2->restoreOrderExt;
	if (ro1->top < ro2->top)
	{
		return (-1);
	}
	else if (ro1->top > ro2->top)
	{
		return (1);
	}
	else if (ro1->hi_hi < ro2->hi_hi)
	{
		return (-1);
	}
	else if (ro1->hi_hi > ro2->hi_hi)
	{
		return (1);
	}
	else if (ro1->hi_lo < ro2->hi_lo)
	{
		return (-1);
	}
	else if (ro1->hi_lo > ro2->hi_lo)
	{
		return (1);
	}
	else if (ro1->lo_hi < ro2->lo_hi)
	{
		return (-1);
	}
	else if (ro1->lo_hi > ro2->lo_hi)
	{
		return (1);
	}
	else if (ro1->lo_lo > ro2->lo_lo)
	{
		return (-1);
	}
	else if (ro1->lo_lo < ro2->lo_lo)
	{
		return (1);
	}
	return (0);
}

/* Compare query records by insertion date. */

static int
cmprespinsdate (const void *r1, const void *r2)
{
	qryRespArchiveData *q1;
	qryRespArchiveData *q2;
	dsmDate *d1;
	dsmDate *d2;
	int r;

	q1 = (qryRespArchiveData *) r1;
	q2 = (qryRespArchiveData *) r2;
	d1 = &q1->insDate;
	d2 = &q2->insDate;
	if (d1->year < d2->year)
	{
		return (-1);
	}
	else if (d1->year > d2->year)
	{
		return (1);
	}
	else if (d1->month < d2->month)
	{
		return (-1);
	}
	else if (d1->month > d2->month)
	{
		return (1);
	}
	else if (d1->day < d2->day)
	{
		return (-1);
	}
	else if (d1->day > d2->day)
	{
		return (1);
	}
	else if (d1->hour < d2->hour)
	{
		return (-1);
	}
	else if (d1->hour > d2->hour)
	{
		return (1);
	}
	else if (d1->minute < d2->minute)
	{
		return (-1);
	}
	else if (d1->minute > d2->minute)
	{
		return (1);
	}
	else if (d1->second < d2->second)
	{
		return (-1);
	}
	else if (d1->second > d2->second)
	{
		return (1);
	}
	return (0);
}

/* Compare for the reverse sort. */

static int
rcmprespinsdate (const void *r1, const void *r2)
{
	int r;

	/* Compare proper. */
	r = cmprespinsdate (r1, r2);

	/* Reverse sort, return the opposite. */
	if (r != 0)
	{
		r = -r;
	}
	return (r);
}

/* Sort query result by restore order field. */

static void
sort_query_result_by_restore_order (void)
{
	qsort (qr, (size_t) nqr, sizeof (qryRespArchiveData), cmprestoreorderext);
}

/* Sort query records by insertion date. */

static void
sort_query_result (void)
{
	qsort (qr, (size_t) nqr, sizeof (qryRespArchiveData), cmprespinsdate);
}

/* Reverse sort query records by insertion date. */

static void
reverse_sort_query_result (void)
{
	qsort (qr, (size_t) nqr, sizeof (qryRespArchiveData), rcmprespinsdate);
}

/* Restore order to string. */

static char *
ro2str (char *s, size_t l, dsUint160_t *ro)
{
	int n;

	n = snprintf (s, l, "%lu-%lu-%lu-%lu-%lu",
		ro->top,
		ro->hi_hi,
		ro->hi_lo,
		ro->lo_hi,
		ro->lo_lo);
	return (s);
}

/* Length of restore order string. */
#define MAX_RSS ((size_t) 28)

/* Print result object list returned by the query. */

static void
print_query_result (void)
{
	int i;
	qryRespArchiveData *r;
	dsUint8_t ot;
	dsUint160_t *ro;
	char otc;
	char date[DATE_LENGTH];
	char rss[MAX_RSS + 1];

	/* Number of responses returned. */
	if (nqr == 1)
	{
		msg ("%d result", nqr);
	}
	else
	{
		msg ("%d results", nqr);
	}
	for (i=0; i<nqr; i++)
	{
		r = &qr[i];
		ot = r->objName.objType;
		switch (ot)
		{
		case DSM_OBJ_FILE:
			otc = 'f';
			break;
		case DSM_OBJ_DIRECTORY:
			otc = 'd';
			break;
		default:
			otc = 'x';
			break;
		}
		ro = &r->restoreOrderExt;
		msg ("%s %-24s %s %c %14lu %s%s",
			tsm2iso (date, r->insDate),
			ro2str (rss, MAX_RSS, ro),
			r->objName.fs,
			otc,
			(((unsigned long) r->sizeEstimate.hi) << 32) +
				((unsigned long) r->sizeEstimate.lo),
			r->objName.hl,
			r->objName.ll);
	}
}

/* Print result object list returned by the query. */

static void
print_query_stat (void)
{
	int i;
	qryRespArchiveData *r;

	for (i=0; i<nqr; i++)
	{
		r = &qr[i];
		print_stat (r);
	}
}

/* Convert mode to sring. */

static char *
strmode (char *modestring, mode_t mode)
{
	char *p;

	p = modestring;
	(void) strcpy (p, "----------");
	if (S_ISREG (mode))
	{
		*p = '-';
	}
	if (S_ISSOCK (mode))
	{
		*p = 's';
	}
	if (S_ISLNK (mode))
	{
		*p = 'l';
	}
	if (S_ISBLK (mode))
	{
		*p = 'b';
	}
	if (S_ISDIR (mode))
	{
		*p = 'd';
	}
	if (S_ISCHR (mode))
	{
		*p = 'c';
	}
	if (S_ISFIFO (mode))
	{
		*p = 'p';
	}
	p++;
	if (mode & S_IRUSR)
	{
		*p = 'r';
	}
	p++;
	if (mode & S_IWUSR)
	{
		*p = 'w';
	}
	p++;
	if (mode & S_IXUSR)
	{
		*p = 'x';
	}
	p++;
	if (mode & S_IRGRP)
	{
		*p = 'r';
	}
	p++;
	if (mode & S_IWGRP)
	{
		*p = 'w';
	}
	p++;
	if (mode & S_IXGRP)
	{
		*p = 'x';
	}
	p++;
	if (mode & S_IROTH)
	{
		*p = 'r';
	}
	p++;
	if (mode & S_IWOTH)
	{
		*p = 'w';
	}
	p++;
	if (mode & S_IXOTH)
	{
		*p = 'x';
	}
	p++;
	*p = EOS;
	return (modestring);
}

/* Mode string max length. */
#define MODEMAX 24

/* Print one query record like ls. */

static void
print_ls (qryRespArchiveData *r)
{
	ourInfo *info;
	struct stat *sb;
	char iro[TIMEMAX];
	char ms[MODEMAX];
	struct passwd *p;
	struct group *g;
	char ub[15];
	char gb[15];
	char *user;
	char *group;

	/* Print our info data. */
	info = (ourInfo *) r->objInfo;
	if (info->version == OURINFO_VERSION)
	{

		/* It is the stat block we need. */
		sb = (struct stat *) &(info->sb);

		/* Deal with username and group name. */
		p = getpwuid (sb->st_uid);
		if (p == NULL)
		{
			(void) snprintf (ub, 14, "%d", sb->st_uid);
			user = ub;
		}
		else
		{
			user = p->pw_name;
		}
		g = getgrgid (sb->st_gid);
		if (g == NULL)
		{
			(void) snprintf (gb, 14, "%d", sb->st_gid);
			group = gb;
		}
		else
		{
			group = g->gr_name;
		}

		/* Print stat. */
		(void) printf ("%s %s %s %14lu %s %s%s\n",
			strmode (ms, sb->st_mode),
			user, group,
			sb->st_size,
			irotime (iro, sb->st_mtime),
			r->objName.hl, r->objName.ll);
	}
	else
	{
		if (debug > 0 || forced)
		{

			/* Complain but continue. */
			msg ("Wrong magic in stat record");
		}
		else
		{
			error ("Wrong magic in stat record");
		}
	}
}

/* Print query like ls. */

static void
print_query_ls (void)
{
	int i;
	qryRespArchiveData *r;

	for (i=0; i<nqr; i++)
	{
		r = &qr[i];
		print_ls (r);
	}
}

/* Query the TSM server for archive data. */

static int
tsm_query_archive (dsUint32_t handle, object_type_t o, char *path)
{
	dsmObjName oname;
	qryArchiveData ad;
	DataBlk db;
	qryRespArchiveData adr;
	dsInt16_t status;
	qryRespArchiveData *resp;

	/* Filespace, HL and LL names. */
	char fs[DSM_MAX_FSNAME_LENGTH + 1];
	char hl[DSM_MAX_HL_LENGTH + 1];
	char ll[DSM_MAX_LL_LENGTH + 1];

	/* Number of query records. */
	int n;

	/* Object name for query. */
	parse_path (fs, hl, ll, path);
	(void) memset (&oname, 0, sizeof (dsmObjName));
	scp (oname.fs, fs, DSM_MAX_FSNAME_LENGTH);
	scp (oname.hl, hl, DSM_MAX_HL_LENGTH);
	scp (oname.ll, ll, DSM_MAX_LL_LENGTH);
	switch (o)
	{
	case file:
		oname.objType = DSM_OBJ_FILE;
		break;
	case directory:
		oname.objType = DSM_OBJ_DIRECTORY;
		break;
	case any:
		oname.objType = DSM_OBJ_ANY_TYPE;
		break;
	}

	/* Fill out archive data structure. */
	(void) memset (&ad, 0, sizeof (qryArchiveData));
	ad.stVersion = qryArchiveDataVersion;
	ad.objName = &oname;
	ad.owner = strdup ("*");
	ad.insDateLowerBound.year = DATE_MINUS_INFINITE;
	ad.insDateUpperBound.year = DATE_PLUS_INFINITE;
	ad.expDateLowerBound.year = DATE_MINUS_INFINITE;
	ad.expDateUpperBound.year = DATE_PLUS_INFINITE;
	ad.descr = strdup ("*");

	/* Response from query. */
	(void) memset (&adr, 0, sizeof (qryRespArchiveData));
	adr.stVersion = qryRespArchiveDataVersion;

	/* Data block returned from query. */
	(void) memset (&db, 0, sizeof (DataBlk));
	db.stVersion = DataBlkVersion;
	db.bufferLen = (dsUint32_t) sizeof (qryRespArchiveData);
	db.bufferPtr = (char *) &adr;

	/* Make an archive query. */
	status = dsmBeginQuery (handle, qtArchive, (dsmQueryBuff *) &ad);
	if (status != DSM_RC_OK)
	{
		tsm_error (handle, status, "dsmBeginQuery failed");
	}

	/* Get responses. Report if no match. */
	nqr = 0;
	n = 0;
	status = dsmGetNextQObj (handle, &db);
	if (status == DSM_RS_ABORT_NO_MATCH)
	{

		/* No match found, we don't quit.
		tsm_error (handle, status, "No match for %s", path);
		*/
	}
	while (status == DSM_RC_MORE_DATA)
	{
			if (n >= maxqr)
			{
				error ("Too many query responses - limit is %ld",
					maxqr);
			}
			resp = (qryRespArchiveData *) db.bufferPtr;
			(void) memcpy (&qr[n], resp, sizeof (qryRespArchiveData));
			if (debug > 4)
			{
				tsm_print_archive (resp);
				print_stat (resp);
			}
			n++;
			status = dsmGetNextQObj (handle, &db);
	}
	if (status != DSM_RC_FINISHED && status != DSM_RS_ABORT_NO_MATCH)
	{

		/* Quit when error. */
		tsm_error (handle, status,
			"dsmGetNextQObj returned strange status");
	}

	/* The variable n is index from 0 to n showing the next entry position.
	   The last index is one less. Global variable nqr is the number of array
	   elements, the array goes as [0 .. nqr - 1]. */
	nqr = n;

	/* Finished. */
	status = dsmEndQuery (handle);
	if (status != DSM_RC_OK)
	{
		tsm_error (handle, status, "dsmEndQuery failed");
	}
	return (n);
}

/* Initialize eof flags. */

void
init_eof_flags (void)
{
	int i;

	for (i=0; i<MAX_HANDLES; i++)
	{
		eof_flags[i] = -1;
	}
}

/* Signal end of file on TSM object receive. */

int
tsm_receive_eof (dsUint32_t handle)
{
	int e;

	e = eof_flags[(int) handle];
	if (e == -1)
	{

		/* Something horrible happened. */
		error ("Strange eof flag for handle %d - confused", (int) handle);
	}
	return (eof_flags[handle]);
}

/* Receive data. */

static ssize_t
tsm_receive_data (dsUint32_t handle, void *buffer, size_t bufsize)
{
	DataBlk data;
	dsInt16_t status;
	ssize_t nbytes;

	/* Fill out data block structure. */
	data.stVersion = DataBlkVersion;
	data.bufferLen = bufsize;
	data.numBytes  = 0;
	data.bufferPtr = (char *) buffer;

	/* Call API. */
	status = dsmGetData (handle, &data);
	if (status != DSM_RC_OK)
	{
		if (status == DSM_RC_MORE_DATA)
		{

			/* That's ok, return the number of bytes. */
			if (handle >= MAX_HANDLES)
			{
				error ("Too large handle %d", (int) handle);
			}
			eof_flags[handle] = false;
			nbytes = (ssize_t) data.numBytes;
			return (nbytes);
		}
		else if (status == DSM_RC_FINISHED)
		{

			/* Finished. We are like at EOF. */
			if (handle >= MAX_HANDLES)
			{
				error ("Too large handle %d", (int) handle);
			}
			eof_flags[handle] = true;
			nbytes = (ssize_t) data.numBytes;

			/* To signal EOF we return _negative_ number
			   of bytes transferred. */
			return (nbytes);
		}
		else
		{

			/* We have got a problem. */
			eof_flags[handle] = -1;
			tsm_error (handle, status,
				"dsmGetData failed, cannot receive data");
		}
	}

	/* We should not get here really. */
	tsm_error (handle, status,
		"Logic failed me in tsm_receive_data - confused");
	nbytes = (ssize_t) data.numBytes;
	return (nbytes);
}

/* Retrieve from the archive. */

static void
tsm_retrieve (dsUint32_t handle, unsigned long blocksize, int n,
	const char *path, const char *localpath)
{

	/* It assumes that we already have a query result on the global list.
	   If n is 1, then only the first object would be retrieved, with the
	   name in localpath. Otherwise, the first n object on the list would
	   be retrieved and in this case we use localpath as a prefix for
	   the local names. */

	dsmGetList objlist;
	int i;
	qryRespArchiveData *q;
	dsInt16_t status;
	dsStruct64_t *op;
	ssize_t nbytes;
	int fd;
	char *buffer;
	size_t bufsize;
	dsmObjName *objname;
	char localname[PATH_MAX + 1];

	/* Retrieve files returned by a previous query and saved on the
	   global files list. Checks. */
	if (nqr < 1)
	{
		error ("File %s not found to retrieve - confused", path);
	}
	if (n > nqr)
	{
		error ("Too many files requested - the maximum is %d", nqr);
	}
	if (n > DSM_MAX_GET_OBJ)
	{
		error ("dsmBeginGetData cannot take more than %d objects",
			DSM_MAX_GET_OBJ);
	}
	if (n < 0)
	{
		error ("Wrong n in tsm_retrieve (%d) - confused", n);
	}
	if (seq (localpath, "-"))
	{

		/* Standard output specified, we can take only one file. */
		if (nqr > 1)
		{
			error ("More than one file for stdout - cannot do that");
		}
	}

	/* Initialize and load the object list structure. */
	(void) memset (&objlist, 0, sizeof (dsmGetList));
	objlist.stVersion = dsmGetListVersion;
	objlist.numObjId = n;
	objlist.objId = (ObjID *) allocate (sizeof(ObjID) * objlist.numObjId);

	/* Build object list with the first n files on the global list. */
	for (i=0; i<n; i++)
	{
		q = &qr[i];
		objlist.objId[i].hi = q->objId.hi;
		objlist.objId[i].lo = q->objId.lo;
	}

	/* Initiate retrieval. */
	status = dsmBeginGetData (handle, dsmTrue, gtArchive, &objlist);
	if (status != DSM_RC_OK)
	{
		tsm_error (handle, status, "dsmBeginGetData failed");
	}

	/* Get the first n object. */
	bufsize = (size_t) blocksize;
	buffer = (char *) allocate (bufsize);
	for (i=0; i<n; i++)
	{

		/* From our list. */
		q = &qr[i];
		objname = &(q->objName);

		/* Get object i from the object list, started with 0. */
		op = &(objlist.objId[i]);
		if (debug > 5)
		{
			msg ("Retrieve %s%s id %lu-%lu", objname->hl, objname->ll,
				op->hi, op->lo);
		}
		status = dsmGetObj (handle, op, NULL);
		if (status != DSM_RC_OK)
		{
			if (status != DSM_RC_MORE_DATA)
			{
				tsm_error (handle, status, "dsmGetObj failed");
			}
		}

		/* Figure out path in the local file system. If there was only one
		   object asked for, the full local pathname will be used.
		   Otherwise, we use the same path as the archived path and we use
		   the local path as a _prefix_. */
		if (n > 1)
		{

			/* Retrieving multiple files. */
			*localname = EOS;
			if (*localpath != EOS)
			{

				/* Local path actually specified. */
				scp (localname, localpath, PATH_MAX);
				sapp (localname, "/", PATH_MAX);
			}

			/* Actually, no need for filespace.
			sapp (localname, objname->fs, PATH_MAX);
			*/
			sapp (localname, objname->hl, PATH_MAX);
			sapp (localname, objname->ll, PATH_MAX);
		}
		else
		{

			/* One file, use localpath as it is. */
			scp (localname, localpath, PATH_MAX);
		}

		/* Get the data, read through the file. */
		if (seq (localname, "-"))
		{

			/* Writing to stdout. */
			fd = (int) 1;
		}
		else
		{

			/* Normal file open. */
			fd = open_file_write (localname);
		}
		nbytes = tsm_receive_data (handle, buffer, bufsize);
		write_file (fd, buffer, nbytes);
		while (! tsm_receive_eof(handle))
		{
			nbytes = tsm_receive_data (handle, buffer, bufsize);
			write_file (fd, buffer, nbytes);
		}
		close_file (fd);

		/* Finish the retrieval of an object. */
		status = dsmEndGetObj (handle);
		if (status != DSM_RC_OK)
		{
			tsm_error (handle, status, "dsmEndGetObj failed");
		}
	}
	free (buffer);

	/* Finish. */
	status = dsmEndGetData (handle);
	if (status != DSM_RC_OK)
	{
		tsm_error (handle, status, "dsmEndGetData failed");
	}
	free (objlist.objId);
}

/* Remove object(s). */

static void
tsm_remove_file (dsUint32_t handle, char *path)
{
	int n;
	dsInt16_t status;
	int i;
	qryRespArchiveData *r;
	dsmDelInfo d;
	dsUint16_t reason;

	/* Get file list. */
	n = tsm_query_archive (handle, any, path);
	if (n == 0)
	{

		/* No files found. We did quit early, so no status yet. */
		status = (dsInt16_t) 0;

		/* And quit. */
		tsm_error (handle, status, "No match for %s", path);
	}

	/* Open transaction. */
	status = dsmBeginTxn (handle);
	if (status != DSM_RC_OK)
	{
		tsm_error (handle, status,
			"dsmBeginTxn failed in tsm_remove_file for %s", path);
	}

	/* Delete them. */
	for (i=0; i<nqr; i++)
	{
		r = &qr[i];

		/* Delete object by object id. */
		d.archInfo.stVersion = delArchVersion;
		d.archInfo.objId.hi = r->objId.hi;
		d.archInfo.objId.lo = r->objId.lo;
		status = dsmDeleteObj (handle, dtArchive, d);
		if (status != DSM_RC_OK)
		{
			tsm_error (handle, status, "dsmDeleteObj failed for %s", path);
		}
	}

	/* Close transaction. */
	reason = 0;
	status = dsmEndTxn (handle, DSM_VOTE_COMMIT, &reason);
	if (status != DSM_RC_OK)
	{
		tsm_error (handle, status, "dsmEndTxn failed in tsm_remove_file for %s",
			path);
	}
}

/* Purge objects back to n versions. */

static void
tsm_purge_file (dsUint32_t handle, int n, char *path)
{
	char *found;
	int nn;
	dsInt16_t status;
	int i;
	qryRespArchiveData *r;
	dsmDelInfo d;
	dsUint16_t reason;

	/* Version has to be > 1. */
	if (n < 1)
	{
		error ("Version %d for purge is not legal", n);
	}

	/* Check, since it is not intended for wildcards. */
	found = index (path, '*');
	if (found != NULL)
	{

		/* Wildcard found, no good. */
		error ("Wildcard %s for purge is not legal", path);
	}

	/* Get file list and reverse sort. */
	nn = tsm_query_archive (handle, any, path);
	if (nn == 0)
	{
		tsm_error (handle, status, "No match for %s", path);
	}
	reverse_sort_query_result ();

	/* If only one found then nothing to do. */
	if (nqr > 1)
	{

		/* Open transaction. */
		status = dsmBeginTxn (handle);
		if (status != DSM_RC_OK)
		{
			tsm_error (handle, status,
				"dsmBeginTxn failed in tsm_remove_file for %s", path);
		}

		/* Skip the first n and delete the rest. */
		for (i=n; i<nqr; i++)
		{
			r = &qr[i];

			/* Delete object by object id. */
			d.archInfo.stVersion = delArchVersion;
			d.archInfo.objId.hi = r->objId.hi;
			d.archInfo.objId.lo = r->objId.lo;
			status = dsmDeleteObj (handle, dtArchive, d);
			if (status != DSM_RC_OK)
			{
				tsm_error (handle, status, "dsmDeleteObj failed for %s", path);
			}
		}

		/* Close transaction. */
		reason = 0;
		status = dsmEndTxn (handle, DSM_VOTE_COMMIT, &reason);
		if (status != DSM_RC_OK)
		{
			tsm_error (handle, status,
				"dsmEndTxn failed in tsm_remove_file for %s", path);
		}
	}
}

/* Archive file copy. */

static void
tsm_copy_file (dsUint32_t handle, dsUint32_t handle2,
	char *oldpath, char *newpath)
{
	int n;
	int i;
	qryRespArchiveData *q;
	ourInfo *info;
	struct stat *sb;
	dsmGetList objlist;
	dsInt16_t status;
	dsStruct64_t *op;
	ssize_t nbytes;
	char *buffer;
	size_t bufsize;

	/* Search for the file to retrieve and reverse sort results. */
	n = tsm_query_archive (handle, file, oldpath);
	if (n == 0)
	{
		tsm_error (handle, status, "No match for %s", oldpath);
	}
	if (restoreorder)
	{
		sort_query_result_by_restore_order ();
	}
	else
	{
		reverse_sort_query_result ();
	}

	/* Copy all matching objects. */
	if (nqr < 1)
	{
		error ("File %s not found to copy - confused", oldpath);
	}
	for (i=0; i<nqr; i++)
	{
		q = &qr[i];

		/* Get the status block from the query. */
		info = (ourInfo *) q->objInfo;
		if (info->version != OURINFO_VERSION)
		{
			if (forced)
			{
				msg ("Wrong info record returned for %s, continuing", oldpath);
			}
			else
			{
				error ("Wrong info record returned for %s", oldpath);
			}
		}
		sb = (struct stat *) &(info->sb);

		/* Initialize and load the object list structure. */
		(void) memset (&objlist, 0, sizeof (dsmGetList));
		objlist.stVersion = dsmGetListVersion;
		objlist.numObjId = 1;
		objlist.objId = (ObjID *) allocate (sizeof(ObjID) *objlist.numObjId);
		objlist.objId[0].hi = q->objId.hi;
		objlist.objId[0].lo = q->objId.lo;

		/* Initiate retrieval. */
		status = dsmBeginGetData (handle, dsmTrue, gtArchive, &objlist);
		if (status != DSM_RC_OK)
		{
			tsm_error (handle, status, "dsmBeginGetData failed");
		}

		/* Get object. */
		op = &(objlist.objId[0]);
		status = dsmGetObj (handle, op, NULL);
		if (status != DSM_RC_OK)
		{
			if (status != DSM_RC_MORE_DATA)
			{
				tsm_error (handle, status, "dsmGetObj failed");
			}
		}

		/* Create the new object using the status block from the query. */
		tsm_create_object (handle2, file, sb, newpath);

		/* Read through the archive and write copy. */
		bufsize = (size_t) DEFAULT_BUFFER_SIZE;
		buffer = (char *) allocate (bufsize);
		nbytes = tsm_receive_data (handle, buffer, bufsize);
		tsm_send_data (handle2, buffer, nbytes);
		while (! tsm_receive_eof (handle))
		{
			nbytes = tsm_receive_data (handle, buffer, bufsize);
			tsm_send_data (handle2, buffer, nbytes);
		}
		free (buffer);

		/* Finish writing. */
		tsm_finish_with_object (handle2);

		/* Finish with the retrieve. */
		status = dsmEndGetObj (handle);
		if (status != DSM_RC_OK)
		{
			tsm_error (handle, status, "dsmEndGetObj failed");
		}
		status = dsmEndGetData (handle);
		if (status != DSM_RC_OK)
		{
			tsm_error (handle, status, "dsmEndGetData failed");
		}
		free (objlist.objId);
	}
}

/* Archive file move. */

static void
tsm_move_file (dsUint32_t handle, dsUint32_t handle2,
	char *oldpath, char *newpath)
{

	/* It is not possible to rename files using the object update
	   call. So we have to copy the file and delete the old one. */

	/* Copy the file first. */
	tsm_copy_file (handle, handle2, oldpath, newpath);

	/* Remove the old file(s) when finished. */
	tsm_remove_file (handle, oldpath);
}

/* Print help. */

static void
print_help (void)
{
	(void) fprintf (stdout, "\
This program is for the iRODS Universal MSS interface.\n\
It also can be used to access an archive using the TSM API.\n\
Usage:\n\
    dsmarc -h][-d n][-f][-n n][-b blocksize][-h]\n\
        [function][argument...]\n\
where\n\
    -h              prints this help.\n\
    -b blocksize    is the block size in bytes for I/O.\n\
                    The default is 1048576 (1M).\n\
    -d n            Sets the debug level. Higher number for more details.\n\
    -f              Force actions when there is an error.\n\
    -n n            Limit on number of query records returned.\n\
    -o              Order multiple files by TSM restore order.\n\
    function        is the operation to do, one of the followings:\n\
        syncToArch f     to copy from cache to MSS.\n\
        stageToCache f   to stage from MSS to cache.\n\
        mkdir dir        to create a directory in the MSS.\n\
        chmod f mode    to modify ACLs in the MSS for a given\n\
                         directory. There is no functionality\n\
                         for this in TSM. It is ignored.\n\
        rm file          to remove a file from the MSS.\n\
        mv f1 f2         to rename a file in the MSS.\n\
                         It is not possible to rename an archive\n\
                         object in TSM. The file will be copied and\n\
                         then the old one removed\n\
        stat file        to do a stat on a file. Return result in iRODS\n\
                         format.\n\
        sync             synonym of syncToArch.\n\
        stage            synonym of stageToCache.\n\
        retr             retrieve multiple files.\n\
        stream f         stream from standard input and store as f.\n\
        upstream f       synonym for stream.\n\
        downstream f     retrieve f and stream on stdout.\n\
");
    exit (FAILURE);
}

/* Main program. */

int
main (int argc, char *argv[])
{

	/* First argument. */
	char *a = NULL;

	/* Getopt return value. */
	int ch;

	/* Option string for getopt. */
	const char *options = "b:d:fn:o";

	/* Blocksize. */
	unsigned long blocksize = DEFAULT_BUFFER_SIZE;

	/* For strtoul. */
	char *endptr;

	/* Operation name. */
	char *op = NULL;

	/* Pathname. */
	char *path = NULL;

	/* Local path. */
	char *localpath = NULL;

	/* Archive paths. */
	char *oldarch = NULL;
	char *newarch = NULL;

	/* API status. */
	dsInt16_t status;

	/* TSM handle. */
	dsUint32_t handle;

	/* TSM second handle. */
	dsUint32_t handle2;

	/* Number of versions to purge back. */
	int pn;

	/* Number of files found for ls. */
	int n;

	/* Print help when asked. */
	if (argc >= 2)
	{
		a = argv[1];
		if (seq (a, "-h") ||
			seq (a, "--help") ||
			seq (a, "-help") ||
			seq (a, "help"))
		{
			print_help ();
		}
	}

	/* We report error ourselves. */
	opterr = 0;

	/* Process options. */
	ch = getopt (argc, argv, options);
	while (ch != -1)
	{
		switch (ch)
		{
		case 'b':

			/* Block size / buffer size. */
			blocksize = strtoul (optarg, &endptr, 10);
			if (blocksize == (unsigned long) 0 || *endptr != EOS)
			{
				error ("Invalid blocksize %s", optarg);
			}
			break;
		case 'd':

			/* Set debug level. */
			debug = (int) strtol (optarg, &endptr, 10);
			if (*endptr != EOS)
			{
				error ("Unsuitable debug level %s", optarg);
			}
			break;
		case 'f':
			forced = true;
			break;
		case 'n':

			/* Limit on number of query records. */
			maxqr = (int) strtol (optarg, &endptr, 10);
			if (*endptr != EOS)
			{
				error ("Wrong number %s for query limit", optarg);
			}
			break;
		case 'o':

			/* Sort by restore order. */
			restoreorder = true;
			break;
		case '?':
			error ("Wrong option");
			break;
		default:
			error ("Wrong option - confused");
			break;
		}
		ch = getopt (argc, argv, options);
	}

	/* Allocate array for the query results. */
	qr = (qryRespArchiveData *) allocate (sizeof (qryRespArchiveData) * maxqr);

	/* Initialize and get handle. */
	init_eof_flags ();
	tsm_setup (argv);
	handle = tsm_init ();

	/* To have two streams (for the copy) TSM needs two handles.
	   it is possiblly only with threading, so we need an additional
	   tsm_init to get a second handle. One for the read, one for the
	   write */
	handle2 = tsm_init ();

	/* Now the arguments. */
	while (optind < argc)
	{
		op = argv[optind];

		/* Main processing. */
		if (seq (op, "sync") || seq (op, "syncToArch"))
		{

			/* Archive the file. */
			optind++;
			if (optind >= argc)
			{
				error ("You have to specify local path for %s", op);
			}
			localpath = argv[optind];
			optind++;
			if (optind >= argc)
			{
				error ("You have to specify archive path for %s", op);
			}
			path = argv[optind];
			tsm_archive (handle, file, blocksize, localpath, path);
			msg ("UNIVMSS syncToArch %s %s", localpath, path);
			break;
		}
		else if (seq (op, "stage") || seq (op, "stageToCache"))
		{

			/* Retrieve file. */
			optind++;
			if (optind >= argc)
			{
				error ("You have to specify archive path for %s", op);
			}
			path = argv[optind];
			optind++;
			if (optind >= argc)
			{
				error ("You have to specify local path for %s", op);
			}
			localpath = argv[optind];
			optind++;

			/* Search for the file to retrieve and reverse sort results. */
			n = tsm_query_archive (handle, file, path);
			if (n == 0)
			{
				tsm_error (handle, status, "No match for %s", path);
			}
			reverse_sort_query_result ();

			/* Retrieve one file, the first one in the global list of files
			   matching the query,  which is the last one inserted by date. */
			tsm_retrieve (handle, blocksize, 1, path, localpath);
			msg ("UNIVMSS stageToCache %s %s", path, localpath);
		}
		else if (seq (op, "mkdir"))
		{

			/* Create a directory entry. */
			optind++;
			if (optind >= argc)
			{
				error ("You have to specify archive path for %s", op);
			}
			path = argv[optind];
			tsm_archive (handle, directory, 0, NULL, path);
		}
		else if (seq (op, "chmod"))
		{

			/* We can't actually do this.
			   But it's all owned by irods anyway.
			   So this is ignored. */
			break;
		}
		else if (seq (op, "rm"))
		{

			/* Remove object from archive. */
			optind++;
			if (optind >= argc)
			{
				error ("You have to specify archive path for %s", op);
			}
			path = argv[optind];
			tsm_remove_file (handle, path);
			break;
		}
		else if (seq (op, "mv"))
		{

			/* Move archive file. */
			optind++;
			if (optind >= argc)
			{
				error ("You have to specify old archive path for %s", op);
			}
			oldarch = argv[optind];
			optind++;
			if (optind >= argc)
			{
				error ("You have to specify new archive path for %s", op);
			}
			newarch = argv[optind];

			/* This is not directly possible in TSM.
			   Copy the file and then remove the old one. */
			tsm_move_file (handle, handle2, oldarch, newarch);
			break;
		}
		else if (seq (op, "stat"))
		{

			/* Query the archive. */
			optind++;
			if (optind >= argc)
			{
				error ("You have to specify archive path for %s", op);
			}
			path = argv[optind];
			n = tsm_query_archive (handle, any, path);
			if (n == 0)
			{
				tsm_error (handle, status, "No match for %s", path);
			}
			if (debug > 0)
			{
				msg ("Query result");
				print_query_result ();
			}
			if (debug > 4)
			{
				msg ("Query result sorted by date");
				sort_query_result ();
				print_query_result ();
				msg ("Query result reverse sorted");
				reverse_sort_query_result ();
				print_query_result ();
				msg ("Query result sorted by restore order");
				sort_query_result_by_restore_order ();
				print_query_result ();
			}

			/* Print results in iRODS format. */
			print_query_stat ();
			break;
		}
		else if (seq (op, "retr"))
		{

			/* Retrieve files. */
			optind++;
			if (optind >= argc)
			{
				error ("You have to specify archive path for %s", op);
			}
			path = argv[optind];
			optind++;
			if (optind >= argc)
			{
				error ("You have to specify local path for %s", op);
			}
			localpath = argv[optind];
			optind++;

			/* Query for the files. */
			n = tsm_query_archive (handle, file, path);
			if (n == 0)
			{
				tsm_error (handle, status, "No match for %s", path);
			}

			/* Sort files by restore order. */
			sort_query_result_by_restore_order ();

			/* Retrieve multiple files. */
			tsm_retrieve (handle, blocksize, nqr, path, "");
		}
		else if (seq (op, "stream") || seq (op, "upstream"))
		{

			/* Archive file from stdin. */
			optind++;
			if (optind >= argc)
			{
				error ("You have to specify archive path for %s", op);
			}
			path = argv[optind];
			tsm_archive (handle, file, blocksize, (char *) "-", path);
			break;
		}
		else if (seq (op, "downstream"))
		{

			/* Retieve file to stdout. */
			optind++;
			if (optind >= argc)
			{
				error ("You have to specify archive path for %s", op);
			}
			path = argv[optind];

			/* Query for the files. */
			n = tsm_query_archive (handle, file, path);
			if (n == 0)
			{
				tsm_error (handle, status, "No match for %s", path);
			}
			if (n > 1)
			{
				tsm_error (handle, status,
				"More than one match for %s - not for %s", path, op);
			}

			/* Retrieve to stdout. */
			tsm_retrieve (handle, blocksize, nqr, path, "-");
			break;
		}
		else if (seq (op, "purge"))
		{

			/* Purge back to n versions. */
			optind++;
			if (optind >= argc)
			{
				error ("You have to specify versions and path for %s", op);
			}
			pn = atoi (argv[optind]);
			if (pn == 0)
			{
				error ("Version number is wrong");
			}
			optind++;
			if (optind >= argc)
			{
				error ("You have to specify versions and also path for %s", op);
			}
			path = argv[optind];
			tsm_purge_file (handle, pn, path);
		}
		else if (seq (op, "ls"))
		{

			/* List file metadata. */
			optind++;
			if (optind >= argc)
			{
				error ("You have to specify path selector for %s", op);
			}
			path = argv[optind];
			n = tsm_query_archive (handle, file, path);
			if (n > 0)
			{
				print_query_ls ();
			}
		}
		else
		{
	
			/* Wrong op. */
			error ("Unknown operation %s", op);
			break;
		}
		optind++;
	}

	/* Release query results global array. */
	free (qr);

	/* Release handle. */
	tsm_exit (handle);

	/* Release the second handle. */
	tsm_exit (handle2);

	/* Finish. */
	exit (SUCCESS);
}

/* End of file DSMARC.C. */

