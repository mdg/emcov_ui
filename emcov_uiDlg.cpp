// emcov_uiDlg.cpp : implementation file
//

#include "stdafx.h"
#include <fstream.h>
#include "emcov_ui.h"
#include "emcov_uiDlg.h"
#include "ConfigDlg.h"
#include <process.h>
#include <atlbase.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEmcov_uiDlg dialog

CEmcov_uiDlg::CEmcov_uiDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEmcov_uiDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEmcov_uiDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEmcov_uiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEmcov_uiDlg)
	DDX_Control(pDX, IDC_LISTWISE, m_Listwise);
	DDX_Control(pDX, IDC_PAIRWISE, m_Pairwise);
	DDX_Control(pDX, IDC_RES, m_RES_Box);
	DDX_Control(pDX, IDC_PTN, m_PTN_Box);
	DDX_Control(pDX, IDC_DAT, m_DAT_Box);
	DDX_Control(pDX, IDC_CONVERGE_FIELD, m_ConvergeField);
	DDX_Control(pDX, IDC_MAX_ITER, m_MaxIterField);
	DDX_Control(pDX, IDC_MVI_FIELD, m_MVI_Field);
	DDX_Control(pDX, IDC_MAX_PATTERN_FIELD, m_MaxPatternField);
	DDX_Control(pDX, IDC_N_FIELD, m_N_Field);
	DDX_Control(pDX, IDC_K_FIELD, m_K_Field);
	DDX_Control(pDX, IDC_EMCOV_FILE, m_EmcovFileField);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEmcov_uiDlg, CDialog)
	//{{AFX_MSG_MAP(CEmcov_uiDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RUN, OnRun)
	ON_BN_CLICKED(IDC_EMCOV_BROWSE, OnEmcovBrowse)
	ON_BN_CLICKED(IDC_PTN, OnPtn)
	ON_BN_CLICKED(IDC_DAT, OnDat)
	ON_BN_CLICKED(IDC_RES, OnRes)
	ON_BN_CLICKED(IDC_PAIRWISE, OnPairwise)
	ON_BN_CLICKED(IDC_LISTWISE, OnListwise)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEmcov_uiDlg message handlers

BOOL CEmcov_uiDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		CString strConfigure;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		strConfigure.LoadString(IDS_CONFIGURE);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_CONFIGURE, strConfigure);
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	Init();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CEmcov_uiDlg::Init() {
	LoadConfiguration();

	// replace these strings with macros or config values
	m_EmcovFilename = ".\\*.*";
	m_MaxPatternField.SetWindowText("1000");
	m_MVI_Field.SetWindowText("9");
	m_MaxIterField.SetWindowText("200");
	m_ConvergeField.SetWindowText("0.00001");
	// set listwise as the default
	OnListwise();
	// set default to no additional output
	SetOutput(false);
}

void CEmcov_uiDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else if ( nID == IDM_CONFIGURE )
	{
		ConfigDlg dlg;
		if ( dlg.DoModal() == IDOK ) {
			LoadConfiguration();
		}
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CEmcov_uiDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CEmcov_uiDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CEmcov_uiDlg::OnRun() {
	if ( RunEmcov() ) {
		RunAddres();
	}
}

bool CEmcov_uiDlg::RunEmcov() {
	if ( ValidData() ) {
		WriteEmcovInputFile();
		system(m_ExecPath + "emcov232.exe < emcov_input.txt > emcov_output.txt");
		return true;
	}
	return false;
}

void CEmcov_uiDlg::RunAddres() {
	if ( b_RES ) {
		WriteAddresInputFile();
		system(m_ExecPath + "addrs11f.exe < addres_input.txt > addres_output.txt");
	}
}

bool CEmcov_uiDlg::ValidData() {
	CString text;

	// get filename
	m_EmcovFileField.GetWindowText( m_EmcovFilename );
	// get K
	m_K_Field.GetWindowText( text );
	m_K = atol( text );
	// get N
	m_N_Field.GetWindowText( text );
	m_N = atol( text );
	// get max # of patters
	m_MaxPatternField.GetWindowText( text );
	m_MaxPatterns = atol( text );
	// MVI
	m_MVI_Field.GetWindowText( text );
	m_MVI = atol( text );
	// Convergence
	m_ConvergeField.GetWindowText( text );
	m_Converge = atof( text );
	// Max Iterations
	m_MaxIterField.GetWindowText( text );
	m_MaxIter = atol( text );
	// Output
	// PTN
	b_PTN = m_PTN_Box.GetCheck();
	// DAT
	b_DAT = m_DAT_Box.GetCheck();
	// RES
	b_RES = m_RES_Box.GetCheck();

	return true;
}

void CEmcov_uiDlg::WriteEmcovInputFile() {
	ofstream out;
	CString str;

	out.open( "emcov_input.txt", ios::out|ios::trunc );

	// filename
	out << m_EmcovFilename << endl;
	// n
	out << m_N << endl;
	// k
	out << m_K << endl;
	// maximum # of patterns
	out << m_MaxPatterns << endl;
	// missing value indicator
	out << m_MVI << endl;
	// start type
	out << m_StartType << endl;
	// maximum iterations
	out << m_MaxIter << endl;
	// convergence criterion
	str.Format("%f",m_Converge);
	out << str << endl;
	// additional output
	if ( b_RES )
		out << b_RES;
	out << endl;
	// output format
	out << endl;
	// check initial data
	out << endl;
	// summary output
	out << endl;
	// one extra
	out << endl;

	out.close();
}

void CEmcov_uiDlg::WriteAddresInputFile() {
	ofstream out;
	CString str;

	out.open("addres_input.txt", ios::out|ios::trunc );

	// just use defaults for all these
	// Data file
	out << endl;
	// res file
	out << endl;
	// output file
	out << endl;
	// n
	out << m_N << endl;
	// k
	out << m_K << endl;
	// data format
	out << endl;
	// input seed
	out << endl;
}

void CEmcov_uiDlg::OnEmcovBrowse() {
	CFileDialog dlg(TRUE,NULL,m_EmcovFilename);	// set this dialog as a file OPEN dialog

	dlg.DoModal();
	// use path name for a complete path
	m_EmcovFilename = dlg.GetPathName();

	// for testing, use the file name cuz it has less possibility of screw ups
	// m_EmcovFilename = dlg.GetFileName();
	m_EmcovFileField.SetWindowText( m_EmcovFilename );
}

void CEmcov_uiDlg::SetOutput(bool check) {
	m_PTN_Box.SetCheck( check );
	m_DAT_Box.SetCheck( check );
	m_RES_Box.SetCheck( check );
	b_PTN = b_DAT = b_RES = check;
}

void CEmcov_uiDlg::OnPtn() {
	SetOutput( m_PTN_Box.GetCheck() );
}

void CEmcov_uiDlg::OnDat() {
	SetOutput( m_DAT_Box.GetCheck() );
}

void CEmcov_uiDlg::OnRes() {
	SetOutput( m_RES_Box.GetCheck() );
}

void CEmcov_uiDlg::OnPairwise() {
	m_StartType = 2;	// replace these values with macros
	m_Listwise.SetCheck(false);
	m_Pairwise.SetCheck(true);
}

void CEmcov_uiDlg::OnListwise() {
	m_StartType = 1;	// replace these values with macros
	m_Pairwise.SetCheck(false);
	m_Listwise.SetCheck(true);
}

void CEmcov_uiDlg::LoadConfiguration() {
	CRegKey key;

	if ( key.Open(HKEY_LOCAL_MACHINE,"Software\\Emcov") == ERROR_SUCCESS ) {
		// open was successful
		// query the values
		char path[MAX_PATH];
		unsigned long size = MAX_PATH;

		key.QueryValue(path,"ExecPath",&size);
		m_ExecPath = path;

		key.Close();
	}
	else {
		// open failed
		// load defaults
		m_ExecPath = "";
	}
}
