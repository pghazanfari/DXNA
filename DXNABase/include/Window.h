#include <windows.h>
#include <windowsx.h>
#include <string>

#pragma once

using namespace std;

class Window
{
	private:
		static int counter;
		static const string BaseName;

		HWND handle;
		WNDCLASSEX wclass;
		string classname;

		inline Window() {}

	public:
		inline Window(HINSTANCE hInstance, WNDPROC proc, string cname) : handle(0), classname(cname)
		{
			ZeroMemory(&wclass, sizeof(WNDCLASSEX));
			wclass.cbSize = sizeof(WNDCLASSEX);
			wclass.style = CS_HREDRAW | CS_VREDRAW;
			wclass.hCursor = LoadCursor(NULL, IDC_ARROW);
			wclass.hbrBackground = (HBRUSH)COLOR_WINDOW;
			wclass.lpszClassName = cname.c_str();
			wclass.hInstance = hInstance;
			wclass.lpfnWndProc = proc;

			RegisterClassEx(&wclass);

			// create the window and use the result as the handle
			handle = CreateWindowEx(NULL,
				classname.c_str(),    // name of the window class
				"",   // title of the window
				WS_OVERLAPPEDWINDOW,    // window style
				0,    // x-position of the window
				0,    // y-position of the window
				640,    // width of the window
				480,    // height of the window
				NULL,    // we have no parent window, NULL
				NULL,    // we aren't using menus, NULL
				hInstance,    // application handle
				NULL);    // used with multiple windows, NULL
		}
		inline ~Window()
		{
			SendMessage(handle, WM_DESTROY, NULL, NULL);
		}

		inline void show(const int& nCmdShow) 
		{
			ShowWindow(handle, nCmdShow);
		}

		inline HWND getHandle() { return handle; }

		int getLocationX();
		void setLocationX(const int& x);
		int getLocationY();
		void setLocationY(const int& y);

		int getWidth();
		void setWidth(const int& w);
		int getHeight();
		void setHeight(const int& h);

		string getTitle() const;
		void setTitle(const string& t);

		long getStyle();
		void setStyle(long style);
};