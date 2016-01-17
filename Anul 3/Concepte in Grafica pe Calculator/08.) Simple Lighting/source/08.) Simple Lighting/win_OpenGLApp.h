#pragma once

#include "openGLControl.h"

class COpenGLWinApp
{
public:
	HWND hWnd; // Handle to application window
	COpenGLControl oglControl; // OpenGL Control

	void resetTimer();
	void updateTimer();
	float sof(float fVal);

	bool initializeApp(string a_sAppName);
	void registerAppClass(HINSTANCE hAppInstance);
	bool createWindow(string sTitle);
	
	void appBody();
	void shutdown();

	HINSTANCE getInstance();

	LRESULT CALLBACK msgHandlerMain(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam);

private:
	HINSTANCE hInstance; // Application's instance
	string sAppName;
	HANDLE hMutex;

	bool bAppActive; // To check if application is active (not minimized)
	clock_t tLastFrame;
	float fFrameInterval;
};

namespace Keys
{
	int key(int iKey);
	int onekey(int iKey);
	extern char kp[256];
}

extern COpenGLWinApp appMain;

void initScene(LPVOID), renderScene(LPVOID), releaseScene(LPVOID);