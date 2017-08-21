/*
File: Win32Config.h
Author: Lars Vidar Magnusson
*/

#pragma once

#define DEFAULT_WIDTH 800
#define DEFAULT_HEIGHT 600
#define DEFAULT_FULLSCREEN false

class Win32Config : public PlatformConfig {

private:

	int width;
	int height;
	bool fullscreen;

	Win32Config() : PlatformConfig(true) {}

public:

	static Win32Config *Load(xercesc::DOMElement *element);

	int GetWidth();
	int GetHeight();
	bool GetFullscreen();
	void SetFullscreen(bool fullscreen);

};