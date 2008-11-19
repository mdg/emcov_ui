// emcov_uiDlg.h : header file
//

#if !defined(AFX_EMCOV_UIDLG_H__1985B5E6_588B_11D6_A85A_0000E889B646__INCLUDED_)
#define AFX_EMCOV_UIDLG_H__1985B5E6_588B_11D6_A85A_0000E889B646__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CEmcov_uiDlg dialog

class CEmcov_uiDlg : public CDialog
{
// Construction
public:
	CEmcov_uiDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CEmcov_uiDlg)
	enum { IDD = IDD_EMCOV_UI_DIALOG };
	CButton	m_Listwise;
	CButton	m_Pairwise;
	CButton	m_RES_Box;
	CButton	m_PTN_Box;
	CButton	m_DAT_Box;
	CEdit	m_ConvergeField;
	CEdit	m_MaxIterField;
	CEdit	m_MVI_Field;
	CEdit	m_MaxPatternField;
	CEdit	m_N_Field;
	CEdit	m_K_Field;
	CEdit	m_EmcovFileField;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEmcov_uiDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void LoadConfiguration();
	int m_StartType;
	void SetOutput(bool);
	bool b_RES;
	bool b_PTN;
	bool b_DAT;
	double m_Converge;
	long m_MaxIter;
	bool ValidData();
	long m_MVI;
	long m_MaxPatterns;
	void Init();
	long m_K;
	long m_N;
	CString m_EmcovFilename;
	CString m_ExecPath;
	void WriteEmcovInputFile();
	void WriteAddresInputFile();
	HICON m_hIcon;

	bool RunEmcov();
	void RunAddres();

	// Generated message map functions
	//{{AFX_MSG(CEmcov_uiDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnRun();
	afx_msg void OnEmcovBrowse();
	afx_msg void OnPtn();
	afx_msg void OnDat();
	afx_msg void OnRes();
	afx_msg void OnPairwise();
	afx_msg void OnListwise();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EMCOV_UIDLG_H__1985B5E6_588B_11D6_A85A_0000E889B646__INCLUDED_)
