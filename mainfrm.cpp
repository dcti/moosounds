// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "MooSounds.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define	WM_ICON_NOTIFY			WM_USER+10


/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_ICON_NOTIFY, OnTrayNotification)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
}

CMainFrame::~CMainFrame()
{
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// Create the tray icon
	if (!m_TrayIcon.Create(this, WM_ICON_NOTIFY, _T("MooSounds"), NULL, IDR_POPUP_MENU))
		return -1;

	//m_TrayIcon.SetIcon(IDR_MAINFRAME);
	HICON hIcon = (HICON) ::LoadImage(AfxGetApp()->m_hInstance, 
		MAKEINTRESOURCE(IDR_MAINFRAME), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
	m_TrayIcon.SetIcon(hIcon);
	
	SetTimer(1,30*1000,NULL);

	return 0;
}

LRESULT CMainFrame::OnTrayNotification(WPARAM wParam, LPARAM lParam)
{
	// Ignore double-clicks on the tray icon.
	//if (LOWORD(lParam)==WM_LBUTTONDBLCLK) return 1;

	// Delegate all the work back to the default implementation in
	// CTrayIcon.
	return m_TrayIcon.OnTrayNotification(wParam, lParam);
}

/////////////////////////////////////////////////////////////////////////////


void CMainFrame::OnTimer(UINT nIDEvent) 
{
	for (int contest = 0; contest < 4; contest++)
	{
		int newcount = theApp.GetBufferBlockCount(theApp.szBufferFilename[contest]);
		if (theApp.iLastBlockCount[contest] >= 0 && newcount >= 0 &&
		   newcount > theApp.iLastBlockCount[contest])
			  theApp.PlayRandomMoo();
		theApp.iLastBlockCount[contest] = newcount;
	}

	CFrameWnd::OnTimer(nIDEvent);
}
