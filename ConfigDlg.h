#if !defined(AFX_CONFIGDLG_H__B07A1821_5C7C_11D6_A85A_0000E889B646__INCLUDED_)
#define AFX_CONFIGDLG_H__B07A1821_5C7C_11D6_A85A_0000E889B646__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ConfigDlg dialog

class ConfigDlg : public CDialog
{
// Construction
public:
	ConfigDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ConfigDlg)
	enum { IDD = IDD_CONFIG };
	CString	m_EmcovPath;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ConfigDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void LoadDialog();
	void SaveConfiguration();
	void LoadConfiguration();

	// Generated message map functions
	//{{AFX_MSG(ConfigDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSetPath();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGDLG_H__B07A1821_5C7C_11D6_A85A_0000E889B646__INCLUDED_)
