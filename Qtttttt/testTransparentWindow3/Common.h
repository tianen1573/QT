#ifndef COMMON_H
#define COMMON_H
#include <QStringList>
#include <QMap>
#include "CommonGlobal.h"

#define MAIN_VERSION        2
#define MINOR_VERSION       3
#define RELEASE_VERSION     10

// 全局定义
typedef enum app_id_{
    APPID_SMS = 1,
    APPID_CALLHISTORY,
    APPID_CALLCONTACTS,
    APPID_NOTES,
    APPID_VOICEMEMOS,
    APPID_SAFARIHISTORY,
    APPID_CALENDAR,
    APPID_SAFARIBOOKMARKS,
    APPID_WHATSAPP,
    APPID_WECHAT,
    APPID_LINE,
    APPID_VIBER,
    APPID_QQ,
    APPID_KIK,
    APPID_PHOTOS,
    APPID_VIDEOS,
    APPID_APPPPHOTOS,
    APPID_APPPVIDEOS,
    APPID_SMSATTACHMENTS,
    APPID_NOTEATTACHMENTS,
    APPID_WHATSAPPATTACHMENTS,
    APPID_WECHATATTACHMENTS,
    APPID_WECHATCONTACTS,
    APPID_QQATTACHMENTS,
    APPID_VIBERATTACHMENTS,
    APPID_LINEATATTACHMENTS,
    APPID_KIKATATTACHMENTS,
    APPID_ICLOUDPHOTOS,
    APPID_ICLOUDCONTACTS,
    APPID_ICLOUDCALENDAR,
    APPID_ICLOUDVIDEOS,
    APPID_ICLOUDNOTES,
    APPID_ICLOUDREMINDERS,
    APPID_REMINDERS,
    APPID_FINDIPHONE,
    APPID_ICLOUDDRIVE,
    APPID_KEYNOTE,
    APPID_NUMBER,
    APPID_PAGES
} APPID;


typedef enum backup_mode_{
    BACKUP_MODE_DEVICE,
    BACKUP_MODE_ITUNES,
    BACKUP_MODE_ICLOUD
} BACKUPMODE;

enum IOSVERSION {
    IOS_VERSION_UNKNOW = 0,
    IOS_VERSION_7      = 7,
    IOS_VERSION_8      = 8,
    IOS_VERSION_9      = 9,
    IOS_VERSION_10     = 10,
    IOS_VERSION_11     = 11,
    IOS_VERSION_12     = 12,
    IOS_VERSION_13     = 13,
    IOS_VERSION_14     = 14,
    IOS_VERSION_15     = 15,
    IOS_VERSION_16     = 16
};

///
/// \brief 应用程序名称
///
extern TIGERDR_COMMON_LIBRARY_EXPORT QString g_backupAppName;
extern TIGERDR_COMMON_LIBRARY_EXPORT QString g_recoveryAppName;
extern TIGERDR_COMMON_LIBRARY_EXPORT QString g_passwordManagerAppName;
extern TIGERDR_COMMON_LIBRARY_EXPORT QString g_virtualLocationAppName;
extern TIGERDR_COMMON_LIBRARY_EXPORT QString g_screenMirroringAppName;

extern TIGERDR_COMMON_LIBRARY_EXPORT QStringList g_photoSuffix;

extern TIGERDR_COMMON_LIBRARY_EXPORT QStringList g_videoSuffix;

extern TIGERDR_COMMON_LIBRARY_EXPORT QStringList g_audioSuffix;

///
/// \brief 文件扩展名正则表达式
///
extern TIGERDR_COMMON_LIBRARY_EXPORT QString g_photoRegExp;

extern TIGERDR_COMMON_LIBRARY_EXPORT QString g_videoRegExp;

extern TIGERDR_COMMON_LIBRARY_EXPORT QString g_audioRegExp;

extern TIGERDR_COMMON_LIBRARY_EXPORT QString g_otherRegExp;

///
/// \brief g_silkSuffix silk格式音频文件后缀
///
extern TIGERDR_COMMON_LIBRARY_EXPORT QStringList g_silkSuffix;

extern TIGERDR_COMMON_LIBRARY_EXPORT QStringList g_otherSuffix;

extern TIGERDR_COMMON_LIBRARY_EXPORT QStringList g_txtSuffix;

extern TIGERDR_COMMON_LIBRARY_EXPORT QStringList g_zipSuffix;

extern TIGERDR_COMMON_LIBRARY_EXPORT QStringList g_wordSuffix;

extern TIGERDR_COMMON_LIBRARY_EXPORT QStringList g_pptSuffix;

extern TIGERDR_COMMON_LIBRARY_EXPORT QStringList g_xlsSuffix;

extern TIGERDR_COMMON_LIBRARY_EXPORT QStringList g_pdfSuffix;

extern TIGERDR_COMMON_LIBRARY_EXPORT QStringList g_appDomianList;


///
/// \brief g_domainMap key: AppId Value: domain list
///
extern TIGERDR_COMMON_LIBRARY_EXPORT QMap<APPID,QStringList> g_domainMap;

extern TIGERDR_COMMON_LIBRARY_EXPORT QString g_dateFormat;
extern TIGERDR_COMMON_LIBRARY_EXPORT QString g_dateTimeFormat;

extern TIGERDR_COMMON_LIBRARY_EXPORT QString g_appKey;
extern TIGERDR_COMMON_LIBRARY_EXPORT QString g_appSecurity;

extern TIGERDR_COMMON_LIBRARY_EXPORT QString g_homepage;

extern TIGERDR_COMMON_LIBRARY_EXPORT QString g_englishFont;

extern TIGERDR_COMMON_LIBRARY_EXPORT QString g_chineseFont;

///
/// \brief 产品号
///
extern TIGERDR_COMMON_LIBRARY_EXPORT QString g_productBackup;
extern TIGERDR_COMMON_LIBRARY_EXPORT QString g_productRecovery;
extern TIGERDR_COMMON_LIBRARY_EXPORT QString g_productPasswordManager;
extern TIGERDR_COMMON_LIBRARY_EXPORT QString g_productVirtual;

extern TIGERDR_COMMON_LIBRARY_EXPORT QString g_applicationConfigKey;
extern TIGERDR_COMMON_LIBRARY_EXPORT QString g_applicationConfigIV;


///
/// \brief licenses保存路径
///
extern TIGERDR_COMMON_LIBRARY_EXPORT QString g_licensesPath;
#endif // COMMON_H
