// emcov_ui.h : main header file for the EMCOV_UI application
//

#if !defined(AFX_EMCOV_UI_H__1985B5E4_588B_11D6_A85A_0000E889B646__INCLUDED_)
#define AFX_EMCOV_UI_H__1985B5E4_588B_11D6_A85A_0000E889B646__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CEmcov_uiApp:
// See emcov_ui.cpp for the implementation of this class
//

class CEmcov_uiApp : public CWinApp
{
public:
	CEmcov_uiApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEmcov_uiApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEmcov_uiApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EMCOV_UI_H__1985B5E4_588B_11D6_A85A_0000E889B646__INCLUDED_)
