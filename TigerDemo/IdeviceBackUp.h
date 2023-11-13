#ifndef IDEVICEBACKUP_H
#define IDEVICEBACKUP_H

#include <QObject>
#include <QWidget>
#include <QMessageBox>


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <dirent.h>
#include <libgen.h>
#include <ctype.h>
#include <time.h>
#include <getopt.h>
#include <libimobiledevice/libimobiledevice.h>
#include <libimobiledevice/lockdown.h>
#include <libimobiledevice/mobilebackup2.h>
#include <libimobiledevice/notification_proxy.h>
#include <libimobiledevice/afc.h>
#include <libimobiledevice/installation_proxy.h>
#include <libimobiledevice/sbservices.h>
#include <libimobiledevice/diagnostics_relay.h>
#include <plist/plist.h>
#ifdef __cplusplus
extern "C" {
#endif
#include <libimobiledevice-glue/utils.h>
#ifdef __cplusplus
}
#endif

#ifdef WIN32
#include <windows.h>
#include <conio.h>
#define sleep(x) Sleep(x*1000)
#ifndef ELOOP
#define ELOOP 114
#endif
#else
#include <termios.h>
#include <sys/statvfs.h>
#endif
#include <sys/stat.h>

// 宏
#define PACKAGE_URL "YiXuan"
#define PACKAGE_BUGREPORT "YiXuan_SH"
#define PACKAGE_VERSION "1.0"

#define TOOL_NAME "idevicebackup2"

#define LOCK_ATTEMPTS 50
#define LOCK_WAIT 200000

#define CODE_SUCCESS 0x00
#define CODE_ERROR_LOCAL 0x06
#define CODE_ERROR_REMOTE 0x0b
#define CODE_FILE_DATA 0x0c

#define OPT_SYSTEM 1
#define OPT_REBOOT 2
#define OPT_NO_REBOOT 3
#define OPT_COPY 4
#define OPT_SETTINGS 5
#define OPT_REMOVE 6
#define OPT_SKIP_APPS 7
#define OPT_PASSWORD 8
#define OPT_FULL 9

#define DEVICE_VERSION(maj, min, patch) ((((maj) & 0xFF) << 16) | (((min) & 0xFF) << 8) | ((patch) & 0xFF))
#define PRINT_VERBOSE(min_level, ...) if (1 >= min_level) { printf(__VA_ARGS__); };

enum cmd_mode {
    CMD_BACKUP,
    CMD_RESTORE,
    CMD_INFO,
    CMD_LIST,
    CMD_UNBACK,
    CMD_CHANGEPW,
    CMD_LEAVE,
    CMD_CLOUD
};

enum cmd_flags {
    CMD_FLAG_RESTORE_SYSTEM_FILES       = (1 << 1),
    CMD_FLAG_RESTORE_NO_REBOOT          = (1 << 2),
    CMD_FLAG_RESTORE_COPY_BACKUP        = (1 << 3),
    CMD_FLAG_RESTORE_SETTINGS           = (1 << 4),
    CMD_FLAG_RESTORE_REMOVE_ITEMS       = (1 << 5),
    CMD_FLAG_ENCRYPTION_ENABLE          = (1 << 6),
    CMD_FLAG_ENCRYPTION_DISABLE         = (1 << 7),
    CMD_FLAG_ENCRYPTION_CHANGEPW        = (1 << 8),
    CMD_FLAG_FORCE_FULL_BACKUP          = (1 << 9),
    CMD_FLAG_CLOUD_ENABLE               = (1 << 10),
    CMD_FLAG_CLOUD_DISABLE              = (1 << 11),
    CMD_FLAG_RESTORE_SKIP_APPS          = (1 << 12)
};

class IdeviceBackUp : public QWidget
{
    Q_OBJECT
public:
    explicit IdeviceBackUp(QWidget *parent = nullptr);

private:
    void freeBackUpVar();
signals:

private slots:
    void BackUp();



private:
    // 需要：变量
    idevice_error_t ret = IDEVICE_E_UNKNOWN_ERROR;
    lockdownd_error_t ldret = LOCKDOWN_E_UNKNOWN_ERROR;
    int i = 0;
    char* udid = NULL;
    char* source_udid = NULL;
    int use_network = 0;
    lockdownd_service_descriptor_t service = NULL;
    int cmd = CMD_BACKUP;
    int cmd_flags = 0;
    int is_full_backup = 0;
    int result_code = -1;
    char* backup_directory = "D:/TestBackUp";
    int interactive_mode = 0;
    char* backup_password = NULL;
    char* newpw = NULL;
    struct stat st;
    plist_t node_tmp = NULL;
    plist_t info_plist = NULL;
    plist_t opts = NULL;

    idevice_t device = NULL;
    afc_client_t afc = NULL;
    np_client_t np = NULL;
    lockdownd_client_t lockdown = NULL;
    mobilebackup2_client_t mobilebackup2 = NULL;
    mobilebackup2_error_t err;
    uint64_t lockfile = 0;
};

#endif // IDEVICEBACKUP_H
