#include "Window.h"

 int Window::x() const
{
	RECT rect;
	GetWindowRect(wHandle, &rect);
	return rect.left;
}

 void Window::setX(const int& x)
{
	MoveWindow(wHandle, x, y(), width(), height(), true);
}

 int Window::y() const
{
	RECT rect;
	GetWindowRect(wHandle, &rect);
	return rect.top;
}

 void Window::setY(const int& y)
{
	MoveWindow(wHandle, x(), y, width(), height(), true);
}

 int Window::width() const 
{
	RECT rect;
	GetWindowRect(wHandle, &rect);
	return rect.right - rect.left;
}

 void Window::setWidth(const int& w)
{
	MoveWindow(wHandle, x(), y(), w, height(), true);
}

 int Window::height() const
{
	RECT rect;
	GetWindowRect(wHandle, &rect);
	return rect.bottom - rect.top;
}

 void Window::setHeight(const int& h)
{
	MoveWindow(wHandle, x(), y(), width(), h, true);
}

 string Window::title() const
{
	int bufsize = GetWindowTextLength(wHandle) + 1;
	basic_string<TCHAR>  title(bufsize, 0);
	GetWindowText(wHandle, &title[0], bufsize + 1);

	return title;
}

 void Window::setTitle(const string& t)
{
	SetWindowText(wHandle, t.c_str());
}

 long Window::style() const
 {
	 return GetWindowLong(wHandle, GWL_STYLE);
 }
 void Window::setStyle(long style)
 {
	 SetWindowLong(wHandle, GWL_STYLE, style);
 }