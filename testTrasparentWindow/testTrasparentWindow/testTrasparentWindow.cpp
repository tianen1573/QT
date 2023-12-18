// testTrasparentWindow.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "testTrasparentWindow.h"

#include <atlimage.h>

#include <Objidl.h>
#include <GdiPlus.h>
#pragma comment(lib, "gdiplus.lib")

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{

    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此处放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_TESTTRASPARENTWINDOW, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TESTTRASPARENTWINDOW));

    MSG msg;

    // 主消息循环:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    Gdiplus::GdiplusShutdown(gdiplusToken);

    return (int) msg.wParam;
}


HBITMAP LoadPngToHBitmap(const wchar_t* filePath)
{
    HBITMAP hBitmap = nullptr;
    Gdiplus::Bitmap* pBitmap = Gdiplus::Bitmap::FromFile(filePath);
    if (pBitmap && pBitmap->GetLastStatus() == Gdiplus::Ok)
    {
        pBitmap->GetHBITMAP(Gdiplus::Color::Transparent, &hBitmap);
    }
    delete pBitmap;
    return hBitmap;
}



//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TESTTRASPARENTWINDOW));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_TESTTRASPARENTWINDOW);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中
   
   HWND hWnd = CreateWindowExW(
       WS_EX_LAYERED,
       szWindowClass,
       szTitle,
       0,
       100, 100, 400, 400,
       nullptr, nullptr, hInstance, nullptr);

   //HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
   //   CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   CImage img;
   img.Load(L"C:\\Users\\qlz\\Downloads\\mask2.png");

   int iWidth = img.GetWidth();
   int iHeight = img.GetHeight();

   HDC hdcScreen = GetDC(NULL);
   HDC hDC = CreateCompatibleDC(hdcScreen);
   HBITMAP hBmp = CreateCompatibleBitmap(hdcScreen, iWidth, iHeight);
   HBITMAP hBmpOld = (HBITMAP)SelectObject(hDC, hBmp);

   img.Draw(hDC, 0, 0, iWidth, iHeight, 0, 0, iWidth, iHeight);

   BLENDFUNCTION blend = { 0 };
   blend.BlendOp = AC_SRC_OVER;
   blend.BlendFlags = 0;
   blend.SourceConstantAlpha = 255;
   blend.AlphaFormat = AC_SRC_ALPHA;
   POINT ptPos = { 200, 200 };
   SIZE sizeWnd = { iWidth, iHeight };
   POINT ptSrc = { 0, 0 };
   UpdateLayeredWindow(hWnd, hdcScreen, &ptPos, &sizeWnd, hDC, &ptSrc, 0, &blend, ULW_ALPHA);
   ShowWindow(hWnd, SW_SHOW);

   SelectObject(hDC, hBmpOld);
   DeleteObject(hBmp);
   DeleteDC(hDC);
   ReleaseDC(NULL, hdcScreen);



   //// 加载PNG图片
   //HBITMAP hBitmap = LoadPngToHBitmap(L"C:\\Users\\qlz\\Downloads\\mask.png");

   ////// 获取PNG图片的大小
   //BITMAP bm;
   //GetObject(hBitmap, sizeof(BITMAP), &bm);

   //// 设置窗口大小和位置
   //SetWindowPos(hWnd, NULL, 100, 100, bm.bmWidth, bm.bmHeight, SWP_NOZORDER | SWP_SHOWWINDOW);

   ////// 创建设备上下文
   //HDC hdcScreen = GetDC(NULL);
   //HDC hdcMem = CreateCompatibleDC(hdcScreen);
   //SelectObject(hdcMem, hBitmap);


   //// 设置窗口透明属性
   //BLENDFUNCTION blend = { 0 };
   //blend.BlendOp = AC_SRC_OVER;
   //blend.SourceConstantAlpha = 255;
   //blend.AlphaFormat = AC_SRC_ALPHA;

   //// 更新窗口的图层
   //POINT ptSrc = { 0, 0 };
   //POINT ptDest = { 0, 0 };
   //SIZE wndSize = { bm.bmWidth, bm.bmHeight };
   //UpdateLayeredWindow(hWnd, hdcScreen, &ptDest, &wndSize, hdcMem, &ptSrc, RGB(0, 0, 0), &blend, ULW_ALPHA);

   //// 释放资源
   //DeleteDC(hdcMem);
   //ReleaseDC(NULL, hdcScreen);
   //DeleteObject(hBitmap);


   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 分析菜单选择:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 在此处添加使用 hdc 的任何绘图代码...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
