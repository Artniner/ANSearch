
// ANSearch.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CANSearchApp: 
// �йش����ʵ�֣������ ANSearch.cpp
//

class CANSearchApp : public CWinApp
{
public:
	CANSearchApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CANSearchApp theApp;