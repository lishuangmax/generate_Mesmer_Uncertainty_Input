
// Mesmer_Uncertainty_Files.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMesmer_Uncertainty_FilesApp:
// �йش����ʵ�֣������ Mesmer_Uncertainty_Files.cpp
//

class CMesmer_Uncertainty_FilesApp : public CWinApp
{
public:
	CMesmer_Uncertainty_FilesApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMesmer_Uncertainty_FilesApp theApp;