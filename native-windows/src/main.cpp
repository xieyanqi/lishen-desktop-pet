#include <windows.h>
#include <windowsx.h>
#include <shellapi.h>
#include <objidl.h>
#include <gdiplus.h>
#include <cstdlib>
#include "GdiCanvas.hpp"
#include <algorithm>
#include <cmath>
#include <memory>
#include <string>
using namespace Gdiplus;
constexpr UINT TrayMessage=WM_APP+1;
constexpr int Width=300, Height=340;
HWND windowHandle{};
NOTIFYICONDATAW tray{};
lishen::Animation animation;
HDC bufferDC=nullptr; HBITMAP bufferBitmap=nullptr; HGDIOBJ oldBitmap=nullptr;
void* bufferPixels=nullptr; ULONGLONG lastTick=0; UINT taskbarCreated=0;
HWND menuOwner=nullptr;
ULONGLONG lastKey=0;
bool dragging=false, resting=false, inputEnabled=true, passThrough=false;
POINT grab{};

void draw() {
  HDC screen=GetDC(nullptr);
  if(!bufferDC) {
    bufferDC=CreateCompatibleDC(screen);
    BITMAPINFO bi{}; bi.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
    bi.bmiHeader.biWidth=Width; bi.bmiHeader.biHeight=-Height;
    bi.bmiHeader.biPlanes=1; bi.bmiHeader.biBitCount=32; bi.bmiHeader.biCompression=BI_RGB;
    bufferBitmap=CreateDIBSection(screen,&bi,DIB_RGB_COLORS,&bufferPixels,nullptr,0);
    if(!bufferBitmap) {DeleteDC(bufferDC);bufferDC=nullptr;ReleaseDC(nullptr,screen);return;}
    oldBitmap=SelectObject(bufferDC,bufferBitmap);
  }
  {
    Graphics g(bufferDC); g.Clear(Color(0,0,0,0));
    g.SetSmoothingMode(SmoothingModeAntiAlias);g.SetPixelOffsetMode(PixelOffsetModeHighQuality);
    g.ScaleTransform(0.90f,0.90f);g.TranslateTransform(7,8);
    lishen::GdiCanvas canvas(g);lishen::character(canvas,animation);
  }
  POINT src{0,0}; SIZE size{Width,Height}; RECT r{}; GetWindowRect(windowHandle,&r); POINT dst{r.left,r.top};
  BLENDFUNCTION blend{AC_SRC_OVER,0,255,AC_SRC_ALPHA};
  UpdateLayeredWindow(windowHandle,screen,&dst,&size,bufferDC,&src,0,&blend,ULW_ALPHA);
  ReleaseDC(nullptr,screen);
}
void setThrough(bool enabled) {
  passThrough=enabled;
  LONG_PTR style=GetWindowLongPtrW(windowHandle,GWL_EXSTYLE);
  SetWindowLongPtrW(windowHandle,GWL_EXSTYLE,enabled?(style|WS_EX_TRANSPARENT):(style&~WS_EX_TRANSPARENT));
}
void menu() {
  HMENU m=CreatePopupMenu();
  AppendMenuW(m,MF_STRING|(resting?MF_CHECKED:0),1,L"休息形象预览");
  AppendMenuW(m,MF_STRING|(inputEnabled?MF_CHECKED:0),2,L"响应打字动作（不记录文字）");
  AppendMenuW(m,MF_STRING|(passThrough?MF_CHECKED:0),3,L"鼠标穿透（快捷键恢复）");
  AppendMenuW(m,MF_STRING,7,L"预览：推眼镜");
  AppendMenuW(m,MF_SEPARATOR,0,nullptr); AppendMenuW(m,MF_STRING,4,L"退出小黎");
  POINT p; GetCursorPos(&p); SetForegroundWindow(menuOwner);
  int choice=TrackPopupMenu(m,TPM_RETURNCMD|TPM_RIGHTBUTTON,p.x,p.y,0,menuOwner,nullptr);
  if(choice==1) {resting=!resting;animation.rest=resting;}
  if(choice==2) { inputEnabled=!inputEnabled; animation.enabled=inputEnabled; lastKey=0; }
  if(choice==3) setThrough(!passThrough);
  if(choice==4) DestroyWindow(windowHandle);
  if(choice==7) animation.preview(lishen::Action::Glasses);
  DestroyMenu(m); PostMessageW(windowHandle,WM_NULL,0,0);
}
LRESULT CALLBACK procedure(HWND h,UINT message,WPARAM w,LPARAM l) {
  if(taskbarCreated && message==taskbarCreated) {Shell_NotifyIconW(NIM_ADD,&tray);return 0;}
  switch(message) {
    case WM_TIMER: {
      POINT cursor; RECT r; GetCursorPos(&cursor); GetWindowRect(h,&r);
      float targetX=(cursor.x-(r.left+Width/2))/320.0f;
      float targetY=(cursor.y-(r.top+130))/260.0f;
      ULONGLONG now=GetTickCount64();
      animation.tick((now-lastTick)/1000.0,targetX,targetY);lastTick=now;
      draw(); return 0;
    }
    case WM_INPUT: {
      RAWINPUT input{}; UINT size=sizeof(input);
      if(GetRawInputData(reinterpret_cast<HRAWINPUT>(l),RID_INPUT,&input,&size,sizeof(RAWINPUTHEADER))!=UINT(-1)
          && input.header.dwType==RIM_TYPEKEYBOARD && !(input.data.keyboard.Flags&RI_KEY_BREAK) && inputEnabled)
        { lastKey=GetTickCount64(); animation.key(); }
      // No key codes or typed contents are persisted.
      return DefWindowProcW(h,message,w,l);
    }
    case WM_NCHITTEST: {
      if(!bufferPixels) return HTTRANSPARENT;
      POINT p{GET_X_LPARAM(l),GET_Y_LPARAM(l)};ScreenToClient(h,&p);
      if(p.x<0 || p.y<0 || p.x>=Width || p.y>=Height)return HTTRANSPARENT;
      auto pixels=static_cast<const unsigned*>(bufferPixels);
      return ((pixels[p.y*Width+p.x]>>24)>20)?HTCLIENT:HTTRANSPARENT;
    }
    case WM_DISPLAYCHANGE: {
      RECT r;GetWindowRect(h,&r);HMONITOR mon=MonitorFromRect(&r,MONITOR_DEFAULTTONEAREST);
      MONITORINFO info{sizeof(info)};if(GetMonitorInfoW(mon,&info))SetWindowPos(h,nullptr,
        std::clamp(r.left,info.rcWork.left,info.rcWork.right-Width),
        std::clamp(r.top,info.rcWork.top,info.rcWork.bottom-Height),0,0,SWP_NOSIZE|SWP_NOZORDER|SWP_NOACTIVATE);
      return 0;
    }
    case WM_LBUTTONDOWN: grab={GET_X_LPARAM(l),GET_Y_LPARAM(l)}; dragging=true; SetCapture(h); return 0;
    case WM_MOUSEMOVE:
      if(dragging) { POINT p; GetCursorPos(&p); SetWindowPos(h,nullptr,p.x-grab.x,p.y-grab.y,0,0,SWP_NOSIZE|SWP_NOZORDER|SWP_NOACTIVATE); }
      return 0;
    case WM_LBUTTONUP: dragging=false; ReleaseCapture(); return 0;
    case WM_CAPTURECHANGED: dragging=false; return 0;
    case WM_RBUTTONUP: menu(); return 0;
    case WM_HOTKEY: setThrough(false); ShowWindow(h,SW_SHOWNOACTIVATE); return 0;
    case TrayMessage: if(l==WM_RBUTTONUP) menu(); if(l==WM_LBUTTONUP) {setThrough(false); ShowWindow(h,SW_SHOWNOACTIVATE);} return 0;
    case WM_DESTROY: KillTimer(h,1); UnregisterHotKey(h,1); Shell_NotifyIconW(NIM_DELETE,&tray); PostQuitMessage(0); return 0;
  }
  return DefWindowProcW(h,message,w,l);
}
int WINAPI wWinMain(HINSTANCE instance,HINSTANCE,PWSTR,int) {
  HANDLE singleton=CreateMutexW(nullptr,TRUE,L"Local\\Astrizaynie.LiShen.NativePreview");
  if(GetLastError()==ERROR_ALREADY_EXISTS) {CloseHandle(singleton); return 0;}
  SetProcessDPIAware();
  GdiplusStartupInput startup; ULONG_PTR token; if(GdiplusStartup(&token,&startup,nullptr)!=Ok) return 1;
  WNDCLASSW wc{}; wc.lpfnWndProc=procedure; wc.hInstance=instance; wc.lpszClassName=L"LiShenNative"; wc.hCursor=LoadCursorW(nullptr,IDC_ARROW); RegisterClassW(&wc);
  RECT area; SystemParametersInfoW(SPI_GETWORKAREA,0,&area,0);
  windowHandle=CreateWindowExW(WS_EX_LAYERED|WS_EX_TOPMOST|WS_EX_TOOLWINDOW|WS_EX_NOACTIVATE,wc.lpszClassName,L"小黎",WS_POPUP,area.right-Width,area.bottom-Height,Width,Height,nullptr,nullptr,instance,nullptr);
  if(!windowHandle) {GdiplusShutdown(token);CloseHandle(singleton);return 1;}
  menuOwner=CreateWindowExW(WS_EX_TOOLWINDOW,L"STATIC",L"LiShenMenu",WS_POPUP,0,0,0,0,nullptr,nullptr,instance,nullptr);
  taskbarCreated=RegisterWindowMessageW(L"TaskbarCreated");
  RAWINPUTDEVICE keyboard{1,6,RIDEV_INPUTSINK,windowHandle};
  if(!RegisterRawInputDevices(&keyboard,1,sizeof(keyboard))) {inputEnabled=false; animation.enabled=false; MessageBoxW(nullptr,L"打字响应注册失败。其他功能仍然可用。",L"小黎",MB_OK);}
  tray.cbSize=sizeof(tray); tray.hWnd=windowHandle; tray.uID=1; tray.uFlags=NIF_MESSAGE|NIF_ICON|NIF_TIP;
  tray.uCallbackMessage=TrayMessage; tray.hIcon=LoadIconW(nullptr,IDI_APPLICATION); lstrcpynW(tray.szTip,L"小黎 · 右键设置，单击恢复交互",128); Shell_NotifyIconW(NIM_ADD,&tray);
  if(!RegisterHotKey(windowHandle,1,MOD_CONTROL|MOD_ALT|MOD_SHIFT|MOD_NOREPEAT,'L')) MessageBoxW(nullptr,L"恢复快捷键已被占用，可单击系统托盘图标退出穿透。",L"小黎",MB_OK);
  lastTick=GetTickCount64(); SetTimer(windowHandle,1,33,nullptr); draw(); ShowWindow(windowHandle,SW_SHOWNOACTIVATE);
  MSG msg; while(GetMessageW(&msg,nullptr,0,0)>0) {TranslateMessage(&msg); DispatchMessageW(&msg);}
  if(bufferDC){SelectObject(bufferDC,oldBitmap);DeleteObject(bufferBitmap);DeleteDC(bufferDC);}
  if(menuOwner)DestroyWindow(menuOwner);
  GdiplusShutdown(token); CloseHandle(singleton); return 0;
}
