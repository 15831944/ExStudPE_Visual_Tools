// ExStudPE���ʾ����ʽ.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "ExStudPE���ʾ����ʽ.h"
#include "../include/plugindef_sdk.h"


WNDPROC g_pfnMainWndProc = NULL;
BOOL g_blnIsLoaded = FALSE;

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			{
				g_pfnMainWndProc = NULL;
			}break;
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}


LRESULT CALLBACK MainWndProc_NewHooked(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if(uMsg==WM_COMMAND && LOWORD(wParam)==9001)
	{
		//
		// ����һ����Ϣ�����
		//
		MessageBox(hWnd,_T("���x���˲������ӵĲˆ��!"),_T("^_^!"),MB_OK);
		return TRUE;
	}
	else if(uMsg == WM_CLOSE)
	{
		//
		// ߀ԭ����̎����
		//
		SetWindowLong(hWnd,GWL_WNDPROC,(LONG)g_pfnMainWndProc);
		PostMessage(hWnd,WM_CLOSE,0,0);
		return TRUE;
	}
	return g_pfnMainWndProc(hWnd,uMsg,wParam,lParam);
}

extern "C" EXSTUDPE_API BOOL PLUGIN_MAIN_CALLBACK PluginMain(PPLUGIN_PARAM_STRUCT pParams)
{
	switch(pParams->dwMessage)
	{
	case WM_CREATE:
		//
		// �O�ÃH���S���dһ��(���}���d�����������y�Ե��e�`�l��)
		//
		if(g_blnIsLoaded) 
			return FALSE;
		g_blnIsLoaded = TRUE;
		// 
		// �O��̎����
		//
		g_pfnMainWndProc = (WNDPROC)SetWindowLong(pParams->hMainFrame,GWL_WNDPROC,(LONG)MainWndProc_NewHooked);
		//
		// ��̎��횷���TRUE
		//
		return TRUE;
		break;
	case WM_CLOSE:
		break;
	case WM_NOTIFY:
		break;
	case WM_CONTEXTMENU:
		if(pParams->v143.hContextWnd==pParams->hTreeView
			|| pParams->v143.hContextWnd==pParams->hDeASMList
			|| pParams->v143.hContextWnd==pParams->hMainFrame)
		{
			//
			// ��������I�ˆ�
			//
			AppendMenu(pParams->v143.hContextMenu,MF_SEPARATOR,0,0);
			AppendMenu(pParams->v143.hContextMenu,MF_STRING,9001,_T("�@��ʾ���������ӵĲˆ�! ^_^!"));
		}
		break;
	default:
		break;
	}
	return FALSE;
}

