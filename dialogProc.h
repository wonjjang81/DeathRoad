#pragma once
#include "stdafx.h"
#include "mapTool.h"


BOOL CALLBACK newTileProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	int mapSizeX = 0;
	int mapSizeY = 0;
	mapTool* pThis = (mapTool*)GetWindowLongPtr(hDlg, GWLP_USERDATA);

	switch (iMessage)
	{
		case WM_INITDIALOG:

			SetWindowPos(hDlg, HWND_TOP, WINSIZEX / 2, WINSIZEY / 2, 0, 0, SWP_NOSIZE);
			SetWindowLongPtr(hDlg, GWLP_USERDATA, (LONG_PTR)lParam);
			pThis = (mapTool*)lParam;
			pThis->setHandleNewTile(hDlg);

		break;
		case WM_COMMAND:

			switch (LOWORD(wParam))
			{
				case IDOK:
					pThis->init();
					mapSizeX = GetDlgItemInt(hDlg, IDC_EDIT1, NULL, FALSE);
					mapSizeY = GetDlgItemInt(hDlg, IDC_EDIT2, NULL, FALSE);
					pThis->createDefaultMap(PointMake(mapSizeX, mapSizeY));
				case IDCANCEL:
				    EndDialog(pThis->getHandleNewTile(), 0);
				return TRUE;
			}

		return FALSE;
		case WM_CLOSE:

			EndDialog(hDlg, IDOK);

		return TRUE;
	}
	return FALSE;
}