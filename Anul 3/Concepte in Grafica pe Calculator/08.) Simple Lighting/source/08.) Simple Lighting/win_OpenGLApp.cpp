#include "common_header.h"

#include "win_OpenGLApp.h"

COpenGLWinApp appMain;

char Keys::kp[256] = {0};

/*-----------------------------------------------

Name:		key

Params:	iKey - virtual key code

Result:	Return true if key is pressed.

/*---------------------------------------------*/

int Keys::key(int iKey)
{
	return (GetAsyncKeyState(iKey)>>15)&1;
}

/*-----------------------------------------------

Name:		onekey

Params:	iKey - virtual key code

Result:	Return true if key was pressed, but only
			once (the key must be released).

/*---------------------------------------------*/

int Keys::onekey(int iKey)
{
	if(key(iKey) && !kp[iKey]){kp[iKey] = 1; return 1;}
	if(!key(iKey))kp[iKey] = 0;
	return 0;
}

/*-----------------------------------------------

Name:	resetTimer

Params:	none

Result:	Resets application timer (for example
			after re-activation of application).

/*---------------------------------------------*/

void COpenGLWinApp::resetTimer()
{
	tLastFrame = clock();
	fFrameInterval = 0.0f;
}

/*-----------------------------------------------

Name:		updateTimer

Params:	none

Result:	Updates application timer.

/*---------------------------------------------*/

void COpenGLWinApp::updateTimer()
{
	clock_t tCur = clock();
	fFrameInterval = float(tCur-tLastFrame)/float(CLOCKS_PER_SEC);
	tLastFrame = tCur;
}

/*-----------------------------------------------

Name:		sof

Params:	fVal

Result:	Stands for speed optimized float.

/*---------------------------------------------*/

float COpenGLWinApp::sof(float fVal)
{
	return fVal*fFrameInterval;
}

/*-----------------------------------------------

Name:		initializeApp

Params:	a_sAppName

Result:	Initializes app with specified (unique)
			application identifier.

/*---------------------------------------------*/

bool COpenGLWinApp::initializeApp(string a_sAppName)
{
	sAppName = a_sAppName;
	hMutex = CreateMutex(NULL, 1, sAppName.c_str());
	if(GetLastError() == ERROR_ALREADY_EXISTS)
	{
		MessageBox(NULL, "This application already runs!", "Multiple Instances Found.", MB_ICONINFORMATION | MB_OK);
		return 0;
	}
	return 1;
}

/*-----------------------------------------------

Name:		registerAppClass

Params:	a_hInstance - application instance handle

Result:	Registers application window class.

/*---------------------------------------------*/

LRESULT CALLBACK globalMessageHandler(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
	return appMain.msgHandlerMain(hWnd, uiMsg, wParam, lParam);
}

void COpenGLWinApp::registerAppClass(HINSTANCE a_hInstance)
{
	WNDCLASSEX wcex;
	memset(&wcex, 0, sizeof(WNDCLASSEX));
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_OWNDC;

	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);

	wcex.hIcon = LoadIcon(hInstance, IDI_WINLOGO);
	wcex.hIconSm = LoadIcon(hInstance, IDI_WINLOGO);
	wcex.hCursor = LoadCursor(hInstance, IDC_ARROW);
	wcex.hInstance = hInstance;

	wcex.lpfnWndProc = 
		globalMessageHandler;
	wcex.lpszClassName = sAppName.c_str();

	wcex.lpszMenuName = NULL;

	RegisterClassEx(&wcex);
}

/*-----------------------------------------------

Name:		createWindow

Params:	sTitle - title of created window

Result:	Creates main application window.

/*---------------------------------------------*/

bool COpenGLWinApp::createWindow(string sTitle)
{
	if(MessageBox(NULL, "Would you like to run in fullscreen?", "Fullscreen", MB_ICONQUESTION | MB_YESNO) == IDYES)
	{
		DEVMODE dmSettings = {0};
		EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dmSettings); // Get current display settings

		hWnd = CreateWindowEx(0, sAppName.c_str(), sTitle.c_str(), WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, // This is the commonly used style for fullscreen
		0, 0, dmSettings.dmPelsWidth, dmSettings.dmPelsHeight, NULL,
		NULL, hInstance, NULL);
	}
	else hWnd = CreateWindowEx(0, sAppName.c_str(), sTitle.c_str(), WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
		0, 0, CW_USEDEFAULT, CW_USEDEFAULT, NULL,
		NULL, hInstance, NULL);

	if(!oglControl.initOpenGL(hInstance, &hWnd, 3, 3, initScene, renderScene, releaseScene, &oglControl))return false;

	ShowWindow(hWnd, SW_SHOW);

	// Just to send WM_SIZE message again
	ShowWindow(hWnd, SW_SHOWMAXIMIZED);
	UpdateWindow(hWnd);

	return true;
}

/*-----------------------------------------------

Name:		appBody

Params:	none

Result:	Main application body infinite loop.

/*---------------------------------------------*/

void COpenGLWinApp::appBody()
{
	MSG msg;
	while(1)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)break; // If the message was WM_QUIT then exit application
			else
			{
				TranslateMessage(&msg); // Otherwise send message to appropriate window
				DispatchMessage(&msg);
			}
		}
		else if(bAppActive)
		{
			updateTimer();
			oglControl.render(&oglControl);
		}
		else Sleep(200); // Do not consume processor power if application isn't active
	}
}

/*-----------------------------------------------

Name:		shutdown

Params:	none

Result:	Shuts down application and releases used
			memory.

/*---------------------------------------------*/

void COpenGLWinApp::shutdown()
{
	oglControl.releaseOpenGLControl(&oglControl);

	DestroyWindow(hWnd);
	UnregisterClass(sAppName.c_str(), hInstance);
	COpenGLControl::unregisterSimpleOpenGLClass(hInstance);
	ReleaseMutex(hMutex);
}

/*-----------------------------------------------

Name:		msgHandlerMain

Params:	whatever

Result:	Application messages handler.

/*---------------------------------------------*/

LRESULT CALLBACK COpenGLWinApp::msgHandlerMain(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;

	switch(uiMsg)
	{
		case WM_PAINT:
			BeginPaint(hWnd, &ps);					
			EndPaint(hWnd, &ps);
			break;

		case WM_CLOSE:
			PostQuitMessage(0);
			break;

		case WM_ACTIVATE:
		{
			switch(LOWORD(wParam))
			{
				case WA_ACTIVE:
				case WA_CLICKACTIVE:
					bAppActive = true;
					resetTimer();
					break;
				case WA_INACTIVE:
					bAppActive = false;
					break;
			}
			break;
		}

		case WM_SIZE:
			oglControl.resizeOpenGLViewportFull();
			oglControl.setProjection3D(45.0f, float(LOWORD(lParam))/float(HIWORD(lParam)), 0.001f, 1000.0f);
			break;

		default:
			return DefWindowProc(hWnd, uiMsg, wParam, lParam);
	}
	return 0;
}

/*-----------------------------------------------

Name:	getInstance

Params:	none

Result:	Returns application instance.

/*---------------------------------------------*/

HINSTANCE COpenGLWinApp::getInstance()
{
	return hInstance;
}

/*-----------------------------------------------

Name:	msgHandlerMain

Params:	whatever

Result:	Application messages handler.

/*---------------------------------------------*/

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR sCmdLine, int iShow)
{
	if(!appMain.initializeApp("08_opengl_3_3"))
		return 0;
	appMain.registerAppClass(hInstance);

	if(!appMain.createWindow("08.) Simple Lighting - Tutorial by Michal Bubnar (www.mbsoftworks.sk)"))
		return 0;
	appMain.resetTimer();

	appMain.appBody();
	appMain.shutdown();

	return 0;
}

