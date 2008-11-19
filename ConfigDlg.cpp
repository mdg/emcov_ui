// ConfigDlg.cpp : implementation file
//

#include "stdafx.h"
#include "emcov_ui.h"
#include "ConfigDlg.h"
#include <atlbase.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ConfigDlg dialog


ConfigDlg::ConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(ConfigDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(ConfigDlg)
	m_EmcovPath = _T("");
	//}}AFX_DATA_INIT
}


void ConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ConfigDlg)
	DDX_Text(pDX, IDC_EMCOV_PATH, m_EmcovPath);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ConfigDlg, CDialog)
	//{{AFX_MSG_MAP(ConfigDlg)
	ON_BN_CLICKED(IDC_SET_PATH, OnSetPath)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ConfigDlg message handlers

BOOL ConfigDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	LoadConfiguration();

	UpdateData(false);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void ConfigDlg::OnSetPath() {
	BROWSEINFO info;
	char path[MAX_PATH];
	LPITEMIDLIST item_list;

	info.hwndOwner = m_hWnd;
	info.pidlRoot = NULL;
	info.pszDisplayName = path;
	info.lpszTitle = "Select Emcov Path";
	info.ulFlags = 0;
	info.lpfn = NULL;
	info.lParam = NULL;
    info.iImage = 0;
	item_list = SHBrowseForFolder(&info);

	SHGetPathFromIDList(item_list,path);

	if ( path[0] ) {
		m_EmcovPath = path;
		m_EmcovPath += "\\";

		UpdateData(false);
	}
}

void ConfigDlg::OnOK() {
	SaveConfiguration();

	CDialog::OnOK();
}

void ConfigDlg::LoadConfiguration() {
	CRegKey key;

	if ( key.Open(HKEY_LOCAL_MACHINE,"Software\\Emcov") == ERROR_SUCCESS ) {
		// open was successful
		// query the values
		char path[MAX_PATH];
		unsigned long size = MAX_PATH;

		key.QueryValue(path,"ExecPath",&size);
		m_EmcovPath = path;

		key.Close();
	}
	else {
		// open failed
		// load defaults
		m_EmcovPath = "";
	}
}

void ConfigDlg::SaveConfiguration() {
	CRegKey key;

	key.Create(HKEY_LOCAL_MACHINE,"SOFTWARE\\Emcov");
	key.SetValue(m_EmcovPath,"ExecPath");
	key.Close();
}
