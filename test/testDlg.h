// testDlg.h : header file
//

#if !defined(AFX_TESTDLG_H__09CFB426_DD62_4BD9_A55E_FED68F57BDB1__INCLUDED_)
#define AFX_TESTDLG_H__09CFB426_DD62_4BD9_A55E_FED68F57BDB1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTestDlg dialog
#include <vector>
#include <io.h>
#include <iostream>


using namespace std;

class ITargetWindow;

class CTestDlg : public CDialog
{
// Construction
public:
	CTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestDlg)
	enum { IDD = IDD_TEST_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnSelectDir();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private: 

	
	int changeSingleFileName(TCHAR *filePath);

	int changeSaveName();    // 更改保存的文件名
	HWND findSaveNameWindow();     // 找到保存文件名的HWND
	
	int clickSaveButton();  // 点击save button
	HWND findSaveBtn();  // 找到save Button的wnd

	int changeSaveType();   // 设置保存文件类型为“所有文件”
	HWND findSaveTypeWindow();   // 找到保存文件类型控件

	HWND findTargetWindow(HWND hParentWnd, TCHAR *fileType, ITargetWindow *pCompareStrategy);
	HWND findRecur(HWND hWndHild, TCHAR *fileType);   // 递归查找 某个类型的控件

	void OpenWithNotepad(TCHAR* path);
	void popSaveAsDlg();  // 弹出另存为对话框
	void CloseNotepad();


	HWND mNotepad;
	CString mSrcDir;    // 保存要破解的源码路径
	void getAllFiles( CString path, vector<string>& files);
	void getFilesAll( string path, vector<string>& files);

	void removeOriginalFile(TCHAR *originalFile);
	void renameFile(TCHAR *oldNameFile, TCHAR *newNameFile);

	bool isEncrypted(TCHAR* filePath);
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTDLG_H__09CFB426_DD62_4BD9_A55E_FED68F57BDB1__INCLUDED_)
