#include "Window.h"

int Window::counter = 0;
const string Window::BaseName = "WC";

 int Window::getLocationX()
{
	RECT rect;
	GetWindowRect(handle, &rect);
	return rect.left;
}

 void Window::setLocationX(const int& x)
{
	MoveWindow(handle, x, getLocationY(), getWidth(), getHeight(), true);
}

 int Window::getLocationY()
{
	RECT rect;
	GetWindowRect(handle, &rect);
	return rect.top;
}

 void Window::setLocationY(const int& y)
{
	MoveWindow(handle, getLocationY(), y, getWidth(), getHeight(), true);
}

 int Window::getWidth()
{
	RECT rect;
	GetWindowRect(handle, &rect);
	return rect.right - rect.left;
}

 void Window::setWidth(const int& w)
{
	MoveWindow(handle, getLocationX(), getLocationY(), w, getHeight(), true);
}

 int Window::getHeight()
{
	RECT rect;
	GetWindowRect(handle, &rect);
	return rect.bottom - rect.top;
}

 void Window::setHeight(const int& h)
{
	MoveWindow(handle, getLocationX(), getLocationY(), getWidth(), h, true);
}

 string Window::getTitle() const
{
	int bufsize = GetWindowTextLength(handle) + 1;
	basic_string<TCHAR>  title(bufsize, 0);
	GetWindowText(handle, &title[0], bufsize + 1);

	return title;
}

 void Window::setTitle(const string& t)
{
	SetWindowText(handle, t.c_str());
}

 long Window::getStyle()
 {
	 return GetWindowLong(handle, GWL_STYLE);
 }
 void Window::setStyle(long style)
 {
	 SetWindowLong(handle, GWL_STYLE, style);
 }