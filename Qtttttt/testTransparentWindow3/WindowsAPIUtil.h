#ifndef WINDOWSAPIUTIL_H
#define WINDOWSAPIUTIL_H

#include "UtilsGlobal.h"

#ifdef Q_OS_WIN
#include <QObject>
#include <QSet>
#include <QString>
#include <qt_windows.h>
#include <windowsx.h>

///
/// \brief Windows 平台相关API封装
///
class UTILS_EXPORT WindowsAPIUtil : public QObject
{
public:
    static int GetWindowDPI(HWND hwnd);
    static bool isCompositionEnalbe();
    ///
    /// \brief GetProcessList Get all process name
    /// \return The process name set
    ///
    static QSet<QString> GetProcessList();
    ///
    /// \brief 传入盘符，检查驱动器是否是USB驱动器
    ///
    static bool IsUsbDevice(char letter);
    ///
    /// \brief 选择磁盘空间最大的驱动器
    ///
    static QString getMaxDriver();
    ///
    /// \brief 枚举系统上的显卡
    ///
    static QList<QString> enumDisplayDevice();
    ///
    /// \brief 判断是否是intel 5000 系或更早的核显
    ///
    static bool isIntelBugDisplayDriver();
    /// system shutdown
    /// nSDType: 0 - Shutdown the system
    ///          1 - Shutdown the system and turn off the power (if supported)
    ///          2 - Shutdown the system and then restart the system
    static void SystemShutdown(UINT nSDType);
};

#endif

#endif // WINDOWSAPIUTIL_H
