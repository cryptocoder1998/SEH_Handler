
// SEH_Handler.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include <vector>

// CSEHHandlerApp:
// See SEH_Handler.cpp for the implementation of this class
//

class CSEHHandlerApp : public CWinApp
{
public:
	CSEHHandlerApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CSEHHandlerApp theApp;
