#include "WindowsAPIUtil.h"

#ifdef Q_OS_WIN
#include <QSet>
#include <QDir>
#include <tlhelp32.h>
#include <QRegularExpression>
#include <QDebug>

#pragma GCC diagnostic ignored "-Wcast-function-type"

bool initOnce = false;

HMODULE user32dll = NULL;
typedef UINT (WINAPI *DefGetDpiForWindow)(HWND hwnd);
DefGetDpiForWindow FuncGetDpiForWindow = NULL;
typedef HMONITOR (WINAPI * DefMonitorFromWindow)(HWND hwnd,DWORD dwFlags);
DefMonitorFromWindow FuncMonitorFromWindow = NULL;

HMODULE dwmapidll = NULL;
typedef HRESULT (WINAPI *DefDwmIsCompositionEnabled)(BOOL *pfEnabled);
DefDwmIsCompositionEnabled FuncDwmIsCompositionEnabled = NULL;

HMODULE shcoredll = NULL;
enum MONITOR_DPI_TYPE {
    MDT_EFFECTIVE_DPI,
    MDT_ANGULAR_DPI,
    MDT_RAW_DPI,
    MDT_DEFAULT
} ;
typedef HRESULT (WINAPI * DefGetDpiForMonitor)(
        HMONITOR         hmonitor,
        MONITOR_DPI_TYPE dpiType,
        UINT             *dpiX,
        UINT             *dpiY
        );
DefGetDpiForMonitor FuncGetDpiForMonitor = NULL;


QSet<QString> WindowsAPIUtil::GetProcessList()
{
    QSet<QString> result;
    HANDLE hProcessSnap;
    HANDLE hProcess;
    PROCESSENTRY32 pe32;
    DWORD dwPriorityClass;

    // Take a snapshot of all processes in the system.
    hProcessSnap = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
    if( hProcessSnap == INVALID_HANDLE_VALUE )
    {
        qDebug() << "CreateToolhelp32Snapshot (of processes)";
        return result;
    }

    // Set the size of the structure before using it.
    pe32.dwSize = sizeof( PROCESSENTRY32 );

    // Retrieve information about the first process,
    // and exit if unsuccessful
    if( !Process32First( hProcessSnap, &pe32 ) )
    {
        qDebug() << "Process32First"; // show cause of failure
        CloseHandle( hProcessSnap );          // clean the snapshot object
        return result;
    }

    // Now walk the snapshot of processes, and
    // display information about each process in turn
    do
    {
        result.insert(QString::fromWCharArray(pe32.szExeFile));
    } while( Process32Next( hProcessSnap, &pe32 ) );

    CloseHandle( hProcessSnap );
    return  result;
}



// 为了操作系统向下兼容，动态检测和加载函数
void loadAll() {
    if (initOnce) return;
    initOnce = true;
    // usef32
    user32dll = LoadLibraryA("User32.dll");
    if (user32dll) {
        FuncGetDpiForWindow =
                (DefGetDpiForWindow)GetProcAddress(user32dll,"GetDpiForWindow");
        FuncMonitorFromWindow =
                (DefMonitorFromWindow)GetProcAddress(user32dll,"MonitorFromWindow");
    }
    //shcore
    shcoredll = LoadLibraryA("Shcore.dll");
    if (shcoredll) {
        FuncGetDpiForMonitor =
                (DefGetDpiForMonitor)GetProcAddress(shcoredll,"GetDpiForMonitor");
    }

    //dwmapi
    dwmapidll = LoadLibraryA("dwmapi.dll");
    if (dwmapidll) {
        FuncDwmIsCompositionEnabled =
                (DefDwmIsCompositionEnabled)GetProcAddress(dwmapidll,"DwmIsCompositionEnabled");
    }
}

int WindowsAPIUtil::GetWindowDPI(HWND hwnd)
{
    loadAll();
    // check windows 10 api
    if (FuncGetDpiForWindow) {
        return FuncGetDpiForWindow(hwnd);
    }
    // check windows 8.1 api
    if (FuncGetDpiForMonitor && FuncMonitorFromWindow) {
        HMONITOR monitor = FuncMonitorFromWindow(hwnd,MONITOR_DEFAULTTONEAREST);
        if (monitor) {
            UINT xdpi= 0,ydpi = 0;
            if (S_OK == FuncGetDpiForMonitor(monitor,MDT_EFFECTIVE_DPI,&xdpi,&ydpi)) {
                return xdpi;
            }

        }
    }
    return 96;
}

bool WindowsAPIUtil::isCompositionEnalbe() {
    loadAll();
    if (FuncDwmIsCompositionEnabled) {
        BOOL isEnable = FALSE;
        FuncDwmIsCompositionEnabled(&isEnable);
        return isEnable;
    }
    return false;
}

bool WindowsAPIUtil::IsUsbDevice( char letter )
{
    char volumeAccessPath[ ] = "\\\\.\\C:";
    volumeAccessPath[ 4 ] = letter;

    HANDLE deviceHandle = CreateFileA( volumeAccessPath, 0, // no access to the drive
                                       FILE_SHARE_READ | // share mode
                                       FILE_SHARE_WRITE, NULL,             // default security attributes
                                       OPEN_EXISTING,    // disposition
                                       0,                // file attributes
                                       NULL );            // do not copy file attributes

    // setup query
    STORAGE_PROPERTY_QUERY query;
    memset( &query, 0, sizeof( query ) );
    query.PropertyId = StorageDeviceProperty;
    query.QueryType = PropertyStandardQuery;

    // issue query
    DWORD bytes;
    STORAGE_DEVICE_DESCRIPTOR devd;
    STORAGE_BUS_TYPE busType = BusTypeUnknown;

    if ( DeviceIoControl( deviceHandle, IOCTL_STORAGE_QUERY_PROPERTY, &query,
                          sizeof( query ), &devd, sizeof( devd ), &bytes, NULL ) )
    {
        busType = devd.BusType;
    }
    else
    {
        qDebug() << L"Failed to define bus type for: " << letter;
    }

    CloseHandle( deviceHandle );

    return BusTypeUsb == busType;
}

QString WindowsAPIUtil::getMaxDriver()
{
    uint64_t maxFreeSpace = 0;
    QString finalDriver;
    QFileInfoList list =  QDir::drives();
    foreach(auto fileInfo, list) {
        std::string driverPath = fileInfo.path().toLocal8Bit().toStdString();
        UINT driverType = GetDriveTypeA(driverPath.c_str());
        if (DRIVE_FIXED == driverType) {

            char driverLetter = driverPath.at(0);
            if (IsUsbDevice(driverLetter))
                continue;

            uint64_t freespace = 0;
            if (GetDiskFreeSpaceExA(driverPath.c_str(),
                                    (PULARGE_INTEGER)&freespace, NULL, NULL)) {
                if (freespace > maxFreeSpace) {
                    maxFreeSpace = freespace;
                    finalDriver = fileInfo.path();
                }
            }
        }
    }
    return finalDriver;
}

QList<QString> WindowsAPIUtil::enumDisplayDevice()
{
    QList<QString> displayDevices;
    for(int i=0; ;i++) {
        DISPLAY_DEVICEA dd;
        memset(&dd,0,sizeof(dd));
        dd.cb = sizeof(dd);
        BOOL f = EnumDisplayDevicesA(NULL,i,&dd,EDD_GET_DEVICE_INTERFACE_NAME);
        if(!f)
            break;
        displayDevices.append(QString::fromUtf8(dd.DeviceString));
    }
    return displayDevices;
}

bool WindowsAPIUtil::isIntelBugDisplayDriver()
{
    QList<QString> displayDevices = WindowsAPIUtil::enumDisplayDevice();
    if (displayDevices.length() > 0) {
        QString device = displayDevices[0];
        QRegularExpression exp("Intel\\(R\\) HD Graphics P?(\\d*)",QRegularExpression::CaseInsensitiveOption);
        auto match = exp.match(device);
        if (match.hasMatch()) {
            int model = match.captured(1).toInt();
            return model >= 1000 && model < 6000;
        }
    }
    return false;
}

// ==========================================================================
// system shutdown
// nSDType: 0 - Shutdown the system
//          1 - Shutdown the system and turn off the power (if supported)
//          2 - Shutdown the system and then restart the system
void WindowsAPIUtil::SystemShutdown(UINT nSDType)
{
    HANDLE           hToken;
    TOKEN_PRIVILEGES tkp   ;

    ::OpenProcessToken(::GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY, &hToken);
    ::LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);

    tkp.PrivilegeCount          = 1                   ; // set 1 privilege
    tkp.Privileges[0].Attributes= SE_PRIVILEGE_ENABLED;

    // get the shutdown privilege for this process
    ::AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);

    switch (nSDType)
    {
        case 0: ::ExitWindowsEx(EWX_SHUTDOWN|EWX_FORCE, 0); break;
        case 1: ::ExitWindowsEx(EWX_POWEROFF|EWX_FORCE, 0); break;
        case 2: ::ExitWindowsEx(EWX_REBOOT  |EWX_FORCE, 0); break;
    }
}

#endif
