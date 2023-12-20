#include "common.h"
#include <QObject>
#include <QString>
#include <QObject>
#include <utils/OSUtils.h>
#include <QDir>

QStringList g_photoSuffix = {
    ".bmp",".jpg",".jpeg",".png",".tif",".gif",
    ".pcx",".tga",".exif",".fpx",".svg",".cdr",
    ".pcd",".dxf",".ufo",".eps",".raw",".wmf",
    ".webp",".avif",".apng",".heic", ".thumb",
    ".video_thum",".pic",".pic_thum",".pic_hd"};

QStringList g_videoSuffix = {
    ".mov", ".mp4", ".wmv", ".flv", ".rm", ".rmvb",
    ".mkv", ".avi", ".webm", ".3gp"};

QStringList g_audioSuffix = {
    ".m4a", ".mp3", ".opus", ".amr", ".aud", ".slk", ".flac",
    ".wma", ".mid", ".wav", ".cda", ".caf"};

QStringList g_silkSuffix = {
    ".amr", ".aud", ".slk"
};

QStringList g_txtSuffix = {
    ".txt",".rtf",".csv"
};

QStringList g_zipSuffix = {
    ".zip", ".7z", ".rar", ".tar", ".gz", ".xz", ".bz", ".bz2"
};

QStringList g_wordSuffix = {
    ".doc", ".docx", ".docm", ".dot", ".wps"
};

QStringList g_pptSuffix = {
    ".ppt", ".ppsx", ".pptm", ".pptx"
};

QStringList g_xlsSuffix = {
    ".xls", ".xlsx", ".xlsm", ".xlsb", ".xltx"
};

QStringList g_pdfSuffix = {
    ".pdf"
};

QStringList g_programmingSuffix = {
    ".h",".c",".cpp",".java",".php",".htm",
    ".html",".xml",".py",".sh",".cs"
};

QStringList g_docSuffix = {
    ".md",".u3d",".prc",".vsd",".url",
    ".psd",".ai",".proj",".aep",".au",".rp",".lrcat", //adobe
    ".dwg", //autodesk
};

QStringList g_otherSuffix = g_txtSuffix + g_zipSuffix + g_wordSuffix +
                            g_pptSuffix + g_xlsSuffix + g_pdfSuffix +
                            g_programmingSuffix + g_docSuffix;

QStringList g_appDomianList = {"MediaDomain",
                               "AppDomainGroup-group.com.apple.notes",
                               "CameraRollDomain"};

QMap<APPID,QStringList> g_domainMap = {{APPID_SMSATTACHMENTS, {"MediaDomain"}},
                                   {APPID_NOTEATTACHMENTS, {"AppDomainGroup-group.com.apple.notes"}},
                                   {APPID_WHATSAPPATTACHMENTS, {"AppDomainGroup-group.net.whatsapp.WhatsApp.shared"}},
                                   {APPID_WECHATATTACHMENTS, {"AppDomain-com.tencent.xin"}},
                                   {APPID_QQATTACHMENTS, {"AppDomain-com.tencent.mqq"}},
                                   {APPID_VIBERATTACHMENTS, {"AppDomainGroup-group.viber.share.container",
                                                             "AppDomain-com.viber"}},
                                   {APPID_LINEATATTACHMENTS,{"AppDomain-jp.naver.line",
                                                             "AppDomainGroup-group.com.linecorp.line"}}};

QString g_dateFormat = "MM/dd/yyyy";
QString g_dateTimeFormat = "MM/dd/yyyy hh:mm:ss";

QString g_appKey = "tigerRecover001";
QString g_appSecurity = "p$bJGX7tXW52DiAOQJw#";

#ifdef APPLICATION_TIGER
QString g_homepage = "https://www.tigerdr.com";
#endif
#ifdef APPLICATION_HUHU
QString g_homepage = "https://www.pocketechshare.com";
#endif



///
/// \brief 文件扩展名正则表达式
///
QString g_photoRegExp = "\\.(bmp|jpg|jpeg|png|tif|gif|tga|exif|fpx|svg|cdr|pcd|dxf|ufo|eps|raw|wmf|webp|avif|apng|HEIC|thumb|video_thum|pic|pic_thum|pic_hd)$";

QString g_videoRegExp = "\\.(MOV|mp4|wmv|flv|rm|rmvb|mkv|avi|webm|3gp)$";

QString g_audioRegExp = "\\.(m4a|mp3|opus|amr|aud|slk|flac|wma|mid|wav|cda)$";

QString g_otherRegExp = "\\.(txt|rtf|csv|zip|7z|rar|tar|gz|xz|bz|bz2|doc|docx|docm|dot|wps|ppt|ppsx|pptm|pptx|xls|xlsx|xlsm|xlsb|xltx|pdf|"
                        "h|c|cpp|java|php|htm|html|xml|py|sh|cs|md|u3d|prc|vsd|url|psd|ai|proj|aep|au|rp|lrcat|dwg)$";

#if defined (Q_OS_WIN)
QString g_englishFont = "Segoe UI";
QString g_chineseFont = "Microsoft YaHei";
#elif defined(Q_OS_MACX)
QString g_englishFont = "PingFangSC-Regular";
QString g_chineseFont = "PingFang SC";
#endif

QString g_backupAppName = "Backup_2.0";
QString g_recoveryAppName = "Recovery_2.0";
QString g_passwordManagerAppName = "PasswordManager_2.0";
QString g_virtualLocationAppName = "VirtualLocation_2.0";
QString g_screenMirroringAppName = "ScreenMirroring_2.0";

QString g_productBackup = "BK20230109";
QString g_productRecovery = "r20210001";
QString g_productPasswordManager = "PM20230414";
QString g_productVirtual = "VL20230803";
QString g_productMirror = "SM20230908";

QString g_applicationConfigKey = "659B01FF85B910A5";
QString g_applicationConfigIV = "FD09B27D5B11ABA2";

#if defined (Q_OS_WIN)
QString g_licensesPath = OSUtils::pathJoin({QDir::homePath(), "AppData", "Roaming", "TigerDr2"});
#elif defined(Q_OS_MACX)
QString g_licensesPath = OSUtils::pathJoin({QDir::homePath(), "Library", "Application Support", "TigerDr2"});
#endif


