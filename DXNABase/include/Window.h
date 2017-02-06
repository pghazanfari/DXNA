#include <windows.h>
#include <windowsx.h>
#include <string>

#pragma once

using namespace std;

/*
ZeroMemory(&wclass, sizeof(WNDCLASSEX));
wclass.cbSize = sizeof(WNDCLASSEX);
wclass.style = CS_HREDRAW | CS_VREDRAW;
wclass.hCursor = LoadCursor(NULL, IDC_ARROW);
wclass.hbrBackground = (HBRUSH)COLOR_WINDOW;
wclass.lpszClassName = cname.c_str();
wclass.hInstance = hInstance;
wclass.lpfnWndProc = proc;
RegisterClassEx(&wclass);
*/

class Window
{
	private:
		HWND wHandle;
		inline Window() {}

	public:
		inline Window(const HINSTANCE& hInstance, Window* const parent, const string& className, const string& title, const int& x, const int& y, const int& width, const int& height) {
			wHandle = CreateWindowEx(NULL,
				className.c_str(),    // name of the window class
				title.c_str(),   // title of the window
				WS_OVERLAPPEDWINDOW,    // window style
				x,    // x-position of the window
				y,    // y-position of the window
				width,    // width of the window
				height,    // height of the window
				parent->handle(),    // we have no parent window, NULL
				NULL,    // we aren't using menus, NULL
				hInstance,    // application handle
				NULL);    // used with multiple windows, NULL
		}

		inline Window(const HINSTANCE& hInstance, const string& className, const string& title, const int& x, const int& y, const int& width, const int& height) {
			wHandle = CreateWindowEx(NULL,
				className.c_str(),    // name of the window class
				title.c_str(),   // title of the window
				WS_OVERLAPPEDWINDOW,    // window style
				x,    // x-position of the window
				y,    // y-position of the window
				width,    // width of the window
				height,    // height of the window
				NULL,    // we have no parent window, NULL
				NULL,    // we aren't using menus, NULL
				hInstance,    // application handle
				NULL);    // used with multiple windows, NULL
		}

		inline ~Window()
		{
			SendMessage(wHandle, WM_DESTROY, NULL, NULL);
		}

		inline void show(const int& nCmdShow) 
		{
			ShowWindow(wHandle, nCmdShow);
		}

		inline HWND handle() const { return wHandle; }

		int x() const;
		void setX(const int& x);
		int y() const;
		void setY(const int& y);

		int width() const;
		void setWidth(const int& w);
		int height() const;
		void setHeight(const int& h);

		string title() const;
		void setTitle(const string& t);

		long style() const;
		void setStyle(long style);
};