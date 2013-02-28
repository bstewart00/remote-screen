#include "stdafx.h"
#include "ContentPane.h"
#include "Win32Framework/SystemWindowBuilder.h"
#include "../Win32Framework/Utils/StringResource.h"
#include "../Win32Framework/Canvas.h"
#include "../../resource.h"

#include <iostream>

std::unique_ptr<ContentPane> ContentPane::Create(HINSTANCE hInstance, const Window& parent)
{
   return WindowBuilder<ContentPane>(hInstance)
      .ClassName(StringResource(IDC_CONTENTPANE))
      .Style(WS_CHILD | WS_VISIBLE)
      .Parent(parent)
      .Register()
      .Create();
}

LRESULT CALLBACK ContentPane::ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
   switch (message) {
   case WM_CREATE:
      OnCreate();
      break;
   case WM_PAINT:
      OnPaint();
      break;
   case WM_SIZE:
      OnResize();
   }

   return Window::ProcessMessage(message, wParam, lParam);
}

void ContentPane::OnCreate()
{

}

void ContentPane::OnPaint() const
{
   std::cout << "Painting screen" << std::endl;

      // Get screen size
   int nWidth = GetSystemMetrics(SM_CXSCREEN);
   int nHeight = GetSystemMetrics(SM_CYSCREEN);

   // Get desktop DC, create a compatible dc, create a comaptible bitmap and select into compatible dc.
   HDC hdcWindow = GetDC( GetDesktopWindow() );
   HDC hdcMemDC = CreateCompatibleDC(hdcWindow);
   HBITMAP hBitmap =CreateCompatibleBitmap(hdcWindow,nWidth,nHeight);
   SelectObject(hdcMemDC,hBitmap); 
   BitBlt(hdcMemDC,0,0,nWidth,nHeight,hdcWindow,0,0,SRCCOPY|CAPTUREBLT);

   /* save hBitmap to stream of byte as you mentioned */
   RECT rcClient = GetClientRect();
   PaintCanvas canvas(*this);
   StretchBlt(canvas, 0, 0, nWidth,nHeight, hdcMemDC, 0, 0, nWidth,nHeight, SRCCOPY);


   /* Save */
   // Create a compatible bitmap from the Window DC
    HBITMAP hbmScreen = CreateCompatibleBitmap(hdcWindow, nWidth, nHeight);
    
    if(!hbmScreen)
    {
        MessageBox(hWnd, L"CreateCompatibleBitmap Failed",L"Failed", MB_OK);
    }

    // Select the compatible bitmap into the compatible memory DC.
    SelectObject(hdcMemDC,hbmScreen);
    
    // Bit block transfer into our compatible memory DC.
    if(!BitBlt(hdcMemDC, 
               0,0,
           nWidth, nHeight, 
               hdcWindow, 
               0,0,
               SRCCOPY))
    {
        MessageBox(hWnd, L"BitBlt has failed", L"Failed", MB_OK);
    }

    // Get the BITMAP from the HBITMAP
    BITMAP bmpScreen;
    GetObject(hbmScreen,sizeof(BITMAP),&bmpScreen);
     
    BITMAPFILEHEADER   bmfHeader;    
    BITMAPINFOHEADER   bi;
     
    bi.biSize = sizeof(BITMAPINFOHEADER);    
    bi.biWidth = bmpScreen.bmWidth;    
    bi.biHeight = bmpScreen.bmHeight;  
    bi.biPlanes = 1;    
    bi.biBitCount = 32;    
    bi.biCompression = BI_RGB;    
    bi.biSizeImage = 0;  
    bi.biXPelsPerMeter = 0;    
    bi.biYPelsPerMeter = 0;    
    bi.biClrUsed = 0;    
    bi.biClrImportant = 0;

    DWORD dwBmpSize = ((bmpScreen.bmWidth * bi.biBitCount + 31) / 32) * 4 * bmpScreen.bmHeight;

    // Starting with 32-bit Windows, GlobalAlloc and LocalAlloc are implemented as wrapper functions that 
    // call HeapAlloc using a handle to the process's default heap. Therefore, GlobalAlloc and LocalAlloc 
    // have greater overhead than HeapAlloc.
    HANDLE hDIB = GlobalAlloc(GHND,dwBmpSize); 
    char *lpbitmap = (char *)GlobalLock(hDIB);    

    // Gets the "bits" from the bitmap and copies them into a buffer 
    // which is pointed to by lpbitmap.
    GetDIBits(hdcWindow, hbmScreen, 0,
        (UINT)bmpScreen.bmHeight,
        lpbitmap,
        (BITMAPINFO *)&bi, DIB_RGB_COLORS);

    // A file is created, this is where we will save the screen capture.
    HANDLE hFile = CreateFile(L"captureqwsx.bmp",
        GENERIC_WRITE,
        0,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL, NULL);   
    
    // Add the size of the headers to the size of the bitmap to get the total file size
    DWORD dwSizeofDIB = dwBmpSize + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
 
    //Offset to where the actual bitmap bits start.
    bmfHeader.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER); 
    
    //Size of the file
    bmfHeader.bfSize = dwSizeofDIB; 
    
    //bfType must always be BM for Bitmaps
    bmfHeader.bfType = 0x4D42; //BM   
 
    DWORD dwBytesWritten = 0;
    WriteFile(hFile, (LPSTR)&bmfHeader, sizeof(BITMAPFILEHEADER), &dwBytesWritten, NULL);
    WriteFile(hFile, (LPSTR)&bi, sizeof(BITMAPINFOHEADER), &dwBytesWritten, NULL);
    WriteFile(hFile, (LPSTR)lpbitmap, dwBmpSize, &dwBytesWritten, NULL);
    
    //Unlock and Free the DIB from the heap
    GlobalUnlock(hDIB);    
    GlobalFree(hDIB);

    //Close the handle for the file that was created
    CloseHandle(hFile);



   // Release the objects
   ReleaseDC( GetDesktopWindow(),hdcWindow);
   DeleteDC(hdcMemDC);
   DeleteObject(hBitmap);
}

void ContentPane::OnResize() const
{
}