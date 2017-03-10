#if !defined(AFX_FILESSTATUS_H__7286D65D_D03E_4FDF_898D_E163D68200C1__INCLUDED_)
#define AFX_FILESSTATUS_H__7286D65D_D03E_4FDF_898D_E163D68200C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FilesStatus.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// FilesStatus dialog

class FilesStatus : public CDialog
{
// Construction
public:
	FilesStatus(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(FilesStatus)
	enum { IDD = IDD_DIALOG_FILES_STATUS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(FilesStatus)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(FilesStatus)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILESSTATUS_H__7286D65D_D03E_4FDF_898D_E163D68200C1__INCLUDED_)
