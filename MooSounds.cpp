// SystemTray.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "MooSounds.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define ntohl(x) ((((x)&0xff)<<24) | (((x)>>24)&0xff) | \
	(((x)&0xff00)<<8) | (((x)>>8)&0xff00))


/////////////////////////////////////////////////////////////////////////////
// CSystemTrayApp

BEGIN_MESSAGE_MAP(CSystemTrayApp, CWinApp)
	//{{AFX_MSG_MAP(CSystemTrayApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSystemTrayApp construction

CSystemTrayApp::CSystemTrayApp()
{
	for (int contest = 0; contest < 4; contest++)
	{
		iLastBlockCount[contest] = -1;
		szBufferFilename[contest][0] = 0;
	}
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSystemTrayApp object

CSystemTrayApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CSystemTrayApp initialization

BOOL CSystemTrayApp::InitInstance()
{
	// Standard initialization

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Don't allow multiplex instances.
	if (::CreateMutex(NULL, TRUE, "MooSounds Mutex") == NULL ||
		::GetLastError() == ERROR_ALREADY_EXISTS)
		return FALSE;

	// Create main frame.
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Determine the filename of the outbuffer.
	FindBuffers("rc5", szBufferFilename[0], sizeof(szBufferFilename[0]));
	FindBuffers("des", szBufferFilename[1], sizeof(szBufferFilename[1]));
	FindBuffers("csc", szBufferFilename[2], sizeof(szBufferFilename[2]));
	FindBuffers("ogr", szBufferFilename[3], sizeof(szBufferFilename[3]));

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
//	int PlaySound(int resid);
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
		// No message handlers
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

// App command to run the dialog
void CSystemTrayApp::OnAppAbout()
{
	PlayRandomMoo();
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();

}

/////////////////////////////////////////////////////////////////////////////
// CSystemTrayApp commands


int CSystemTrayApp::PlayRandomMoo()

{
	int resid;
	int sound = 1 + GetTickCount() % 5;
	switch (sound)
	{
		case 1: resid = RCDATA_1; break;
		case 2: resid = RCDATA_2; break;
		case 3: resid = RCDATA_3; break;
		case 4: resid = RCDATA_4; break;
		case 5: resid = RCDATA_5; break;
		default: return 0;
	}
	PlayResourceSound(resid);
	return 0;
}


void CSystemTrayApp::PlayResourceSound(int soundres)
{
	HGLOBAL hResource = LoadResource( 0,
		FindResource(NULL, MAKEINTRESOURCE(soundres), "WAVE"));
	if (hResource)
	{
		LPCSTR sound = ( LPCSTR )LockResource( hResource );
		if (sound)
		sndPlaySound( sound, SND_MEMORY | SND_ASYNC);
		UnlockResource( hResource );
		FreeResource( hResource );
   }
}

int CSystemTrayApp::FindBuffers(const char *szExtension, char *szFilename, int cbLength)
{
	CRegKey mrupath;
	if (mrupath.Open(HKEY_LOCAL_MACHINE,
		"Software\\Distributed Computing Technologies, Inc.") == ERROR_SUCCESS)
	{
		DWORD dwLength = cbLength;
		if (mrupath.QueryValue(szFilename,"MRUClient", &dwLength) == ERROR_SUCCESS)
		{
			CString mruclient(szFilename);
			int slashpos=mruclient.ReverseFind('\\');
			if(slashpos>=0)
			{
				mruclient=mruclient.Left(slashpos +1) + "buff-out." + szExtension;
				lstrcpyn(szFilename, mruclient.GetBuffer(0), cbLength);
				return 1;
			}
		}
	}
	lstrcpyn(szFilename, "buff-out.", cbLength);
	lstrcat(szFilename, szExtension);
	return 1;
}

int CSystemTrayApp::GetBufferBlockCount(const char *szFilename)
{
	TRY
	{
		CFile filebuff(szFilename, CFile::modeRead|CFile::typeBinary);
		filebuff.Seek(4, CFile::begin);
		DWORD dwCount;
		if (filebuff.Read(&dwCount, sizeof(DWORD))==sizeof(DWORD))
			return (int) ntohl(dwCount);
	}
	CATCH(CFileException, e)
	{
		#ifdef _DEBUG
			afxDump  << "File could not be opened" <<e->m_cause <<"\n";
		#endif
	}
	END_CATCH

	return -1;
}
