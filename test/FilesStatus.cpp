// FilesStatus.cpp : implementation file
//

#include "stdafx.h"
#include "test.h"
#include "FilesStatus.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// FilesStatus dialog


FilesStatus::FilesStatus(CWnd* pParent /*=NULL*/)
	: CDialog(FilesStatus::IDD, pParent)
{
	//{{AFX_DATA_INIT(FilesStatus)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void FilesStatus::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(FilesStatus)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(FilesStatus, CDialog)
	//{{AFX_MSG_MAP(FilesStatus)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// FilesStatus message handlers
