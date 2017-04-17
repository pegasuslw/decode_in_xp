// testDlg.cpp : implementation file
//

#include "stdafx.h"
#include "test.h"
#include "testDlg.h"
#include <shlwapi.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define Edit_Window        (_T("Edit"))
#define ComboBox_Window    (_T("ComboBox"))
#define ListBox_Window    (_T("ListBox"))
#define Button_Window      (_T("Button"))
#define Static_Window      (_T("Static"))

#define BACKUP_SUFFIX      ".backup"
#define H_SUFFIX           ".h"
#define C_SUFFIX           ".c"
#define CPP_SUFFIX         ".cpp"
#define JAVA_SUFFIX        ".java"

#define SAVE_BUTTON_TEXT (_T("保存(&S)"))

#pragma comment(lib,"Shlwapi.lib")

static HWND sfoundWindow[100];
static int sIndex = 0;

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class ITargetWindow{
public:
	virtual bool IsTargetWindow(HWND hWnd, CString strText) = 0;
};

class IsSaveNameEdit : public ITargetWindow{
	bool IsTargetWindow(HWND hWnd, CString strText){
		if(NULL == hWnd){
			return false;
		}

	CWnd* pEdit = CWnd::FromHandle(hWnd);
	TCHAR BUF[512];
	for(int i=0;i<3;i++){
		memset(BUF,0,512);
		pEdit->SendMessage(WM_GETTEXT,sizeof(BUF)/sizeof(TCHAR),(LPARAM)(void*)BUF);
		CString str = BUF;
		str.TrimRight();
		if(str.Right(2) == ".c" || str.Right(4) == ".cpp" || str.Right(2) == ".h" ||  str.Right(5)==".java"){
			return true;
		}
	}

	return false;
	}
};

class IsSaveButton : public ITargetWindow{
	bool IsTargetWindow(HWND hWnd, CString strText){
		if(NULL == hWnd){
			return false;
		}
		
		CString saveBtnText(SAVE_BUTTON_TEXT);
		strText = strText.Right(saveBtnText.GetLength());
		if(0 == strText.Compare(saveBtnText)){
			return true;
		}
		return false;
	}
	
};

class IsSaveTypeWindow : public ITargetWindow{
	bool IsTargetWindow(HWND hWnd, CString strText){
		if(NULL == hWnd){
			return false;
		}

		/*
		int   count   =  SendMessage(hWnd,CB_GETCOUNT ,0 ,0);
		char buf[100];
		memset(buf,0,100);
		itoa(count,buf,100);
		MessageBox(NULL,buf,"none",MB_OK);
		*/

		
		TCHAR szBuff[100] = "所有文件";
		
		int index = SendMessage(hWnd,CB_FINDSTRING,0 ,(LPARAM)szBuff);
		if(index >= 0){
			return true;
		}
		//SendMessage(hWnd,CB_SELECTSTRING,0 ,(LPARAM)szBuff);
		//SendMessage(hWnd,CB_SETCURSEL, 1, 0);

		/*
		SendMessage(hWnd, CB_SHOWDROPDOWN, 1, 0);//打开列表 

		SendMessage(hWnd, CB_SELECTSTRING, 0, (LPARAM)szBuff );//选择 
		SendMessage(hWnd, WM_KEYDOWN, VK_RETURN, 0);  //响应回车键 
		SendMessage(hWnd, CB_SHOWDROPDOWN,0, 0); //关闭列表  
		*/
		return false;
	}
	
};

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
// CTestDlg dialog

CTestDlg::CTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestDlg, CDialog)
	//{{AFX_MSG_MAP(CTestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SELECT_DIR, OnSelectDir)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestDlg message handlers

BOOL CTestDlg::OnInitDialog()
{
	AfxGetMainWnd()->SetWindowText(_T("显示svn源码小工具"));
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTestDlg::OnPaint() 
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
HCURSOR CTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTestDlg::OnOK() 
{
	//TCHAR *filePath = _T("C:\\Documents and Settings\\Administrator\\桌面\\1\\456.txt");
	//TCHAR *filePath = _T("C:\\Documents and Settings\\Administrator\\桌面\\1");
	TCHAR *filePath = mSrcDir.GetBuffer(mSrcDir.GetLength());
	if(NULL==filePath || strlen(filePath)<=0 ){
		MessageBox("请选择源码目录",NULL,MB_OK);
		return;
	}
	int result = -1;
	TCHAR result_buf[1024] = "";

	vector<string> files;  
	getAllFiles(filePath, files);
	int size = files.size(); 
	int nums_of_decode_files = 0;
	TCHAR tmpFile[1024];
	TCHAR backupFile[1024];
	for (int i = 0;i<size;i++)  
	{  
		//const TCHAR *tmp = files[i].data();
		
		memset(tmpFile,0,1024);
		memset(backupFile,0,1024);

		strncpy(tmpFile,files[i].data(),1023);
		strncpy(backupFile,tmpFile,1023);
		strncat(backupFile,BACKUP_SUFFIX,1023);
		/*
		if(!isEncrypted(tmpFile)){    // 如果是加密文件，才进行解密， 否则就不用解了，浪费时间
			continue;	
		}*/
		int retry = 0;
		while(retry<3){
			result = changeSingleFileName(tmpFile, true);
			Sleep(100);
			if (0 == result && PathFileExists(tmpFile)){   // result 等于0 ， 说明另存为改名为"*.backup"成功
				removeOriginalFile(tmpFile);
				Sleep(100);
				if (PathFileExists(backupFile))
				{
					renameFile(backupFile,tmpFile);
					nums_of_decode_files++;           // 修改成功的文件数量+1
					break;
				}else{
					retry++;	
				}
			}
		} // end while (失败，尝试3次)

		if (retry>=3){    // 尝试3次后仍然失败，则弹出另存问，手动保存
			char buf[1024];
			memset(buf,0,1024);
			sprintf(buf,"back文件%s不存在,点ok后会弹出notepad另存为，请手动保存",backupFile);
			MessageBox(buf,NULL,MB_OK);
	
			changeSingleFileName(tmpFile,false);   // 弹出notepad对话框， 更改文件名为*.backup, 但是不自动保存，需要手动点击保存
			Sleep(100);
			if (PathFileExists(backupFile)){
				removeOriginalFile(tmpFile);
				renameFile(backupFile,tmpFile);
				nums_of_decode_files++;        
			}
			
		}

		if (0 != result){
			char buf[1024];
			memset(buf,0,1024);
			sprintf(buf,"解密%s出错",tmpFile);
			MessageBox(buf,NULL,MB_OK);
			return;
		}
	}

	CString str;
	memset(result_buf,0,1024);
	//str = "一共有" + itoa(size) + "个文件,解密了" + itoa(nums_of_decode_files) + "个文件"。

	sprintf(result_buf,"一共有%d个文件,解密了%d个文件",size,nums_of_decode_files);
	MessageBox(_T(result_buf),_T("结果"));
	CDialog::OnOK();
}

bool CTestDlg::isEncrypted(TCHAR* filePath) 
{
	CFile file;
	CFileException fe;
	TCHAR *lpBuf = new char[30];
	memset(lpBuf,0,30);

	bool bResult = file.Open(filePath, CFile::modeRead, &fe);
	if(!bResult){
		return false;
	}
    file.Read(lpBuf,30);
	int count = 0;
	for(int i=10;i<30;i++){
		if(lpBuf[i] > 127 || lpBuf[i] < 0 ){
			count++;
		}
	}
	file.Close();
	
	if(count>2){
		return true;
	}else{
		return false;
	}

}

int CTestDlg::changeSingleFileName(TCHAR *filePath, bool isSave) {
	int result = -1;
	OpenWithNotepad(filePath);
	popSaveAsDlg();
	

	if (0 !=changeSaveName()){
		goto err;
	}
	

	Sleep(200);
	if (0 !=changeSaveType()){
	}
	
	Sleep(200);
	//Sleep(10);
	if(isSave){
		clickSaveButton();
		Sleep(200);  
	}

	CloseNotepad();
	return 0;

err:
	CloseNotepad();
	return -1;
}

void CTestDlg::popSaveAsDlg(){
		// 1. 找到 notepad 窗口
	HWND hNotepad = NULL;
		::FindWindow("Notepad",NULL);

	int retry = 50;
	while(retry > 0  && hNotepad==NULL) {
		Sleep(100);
		hNotepad = ::FindWindow("Notepad",NULL);
		retry--;
	}
	if(NULL == hNotepad){
		MessageBox("没有找到notepad窗口",NULL, MB_OK);
		exit(0);
	}
	mNotepad = hNotepad;

	HMENU hMenu = (HMENU) ::GetMenu(hNotepad);
	
	char buf[100] = "";

	// 2 找到另存为菜单item 的id
	HMENU menuFile = GetSubMenu(hMenu,0);
	int count = ::GetMenuItemCount(menuFile);
	int saveAsMenuItemID = -1;
	for (int i=0;i<count;i++)
	{
		::GetMenuString(menuFile, i, buf,100, MF_BYPOSITION);
		char* tmp = strstr(buf,"另存为");   // 查找是不是另存为 menu item
		if(NULL != tmp && strlen(tmp) > 0){
			saveAsMenuItemID = ::GetMenuItemID(menuFile,i);   // 找到“另存为”，得到 id
			break;
		//MessageBox(tmp,NULL, MB_OK);
		}
	}
	
	
	if( -1 == saveAsMenuItemID){
		MessageBox("没有找到另存为id",NULL, MB_OK);
		exit(0);
	}
	

    // 3  弹出另存为对话框
	::PostMessage(hNotepad,WM_COMMAND, saveAsMenuItemID,0);   
	Sleep(100);
}


int CTestDlg::changeSaveName(){

	TCHAR BUF[512];
	memset(BUF,0,512);
	HWND hWnd = NULL;
	CWnd *pEdit = NULL;
	hWnd = findSaveNameWindow();

/*	char buf[100];
	memset(buf,0,100);
	itoa(sIndex,buf,100);
	::MessageBox(NULL,buf,"none",MB_OK);
	*/

	if(NULL == hWnd){
		::MessageBox(NULL,"没有找到保存文件名控件","none",MB_OK);
		return -1;
	}

	/* 改变保存的文件名，加了后缀.back */
	pEdit = CWnd::FromHandle(hWnd);
	CString str = BUF;
	pEdit->SendMessage(WM_GETTEXT,sizeof(BUF)/sizeof(TCHAR),(LPARAM)(void*)BUF);
	while(str.Right(strlen(BACKUP_SUFFIX)) != BACKUP_SUFFIX){
		pEdit->SendMessage(WM_GETTEXT,sizeof(BUF)/sizeof(TCHAR),(LPARAM)(void*)BUF);
		
		str = BUF;
		str.Insert(str.GetLength(),BACKUP_SUFFIX);
		pEdit->SendMessage(WM_SETTEXT,0,(LPARAM) str.GetBuffer(str.GetLength()));
		Sleep(100);
		pEdit->SendMessage(WM_GETTEXT,sizeof(BUF)/sizeof(TCHAR),(LPARAM)(void*)BUF);
		str = BUF;
	}
	return 0;
}

int CTestDlg::changeSaveType(){

	TCHAR szBuff[100] = "所有文件";
	HWND hWnd = NULL;
	hWnd = findSaveTypeWindow();


	if(NULL == hWnd){
		return -1;
	}

	/* 改变保存类型为"所有文件" */
	::SendMessage(hWnd, CB_SHOWDROPDOWN, 1, 0);//打开列表 

	::SendMessage(hWnd, CB_SELECTSTRING, 0, (LPARAM)szBuff );//选择 
	::SendMessage(hWnd, WM_KEYDOWN, VK_RETURN, 0);  //响应回车键 
	::SendMessage(hWnd, CB_SHOWDROPDOWN,0, 0); //关闭列表  	
	
	return 0;
}

int CTestDlg::clickSaveButton(){

	HWND hSaveBtn = findSaveBtn();
	if(NULL == hSaveBtn){
		MessageBox("没有找到save button",NULL,MB_OK);
		return -1;
	}

	CWnd *pWnd = CWnd::FromHandle(hSaveBtn);
	
	::SendMessage(pWnd->GetSafeHwnd(),WM_LBUTTONDOWN,0,0);
    ::SendMessage(pWnd->GetSafeHwnd(),WM_LBUTTONUP,0,0);
	return 0;
}

HWND CTestDlg::findSaveBtn(){
	HWND hSaveAsWindow = ::FindWindow(NULL,"另存为");
	HWND hSaveBtn = NULL;

	hSaveBtn = findTargetWindow(hSaveAsWindow, Button_Window, new IsSaveButton());
	return hSaveBtn;

}

HWND CTestDlg::findTargetWindow(HWND hParentWnd, TCHAR* fileType,ITargetWindow *pCompareStrategy){

	sIndex = 0;
	findRecur(hParentWnd, fileType);
	
	HWND hWnd = NULL;
	CWnd *pWnd = NULL;
	TCHAR BUF[512];
	CString strBuf;

	for(int i=0;i<sIndex;i++){
		pWnd = CWnd::FromHandle(sfoundWindow[i]);
		pWnd->SendMessage(WM_GETTEXT,sizeof(BUF)/sizeof(TCHAR),(LPARAM)(void*)BUF);
		strBuf = BUF;
		if(true == pCompareStrategy->IsTargetWindow(sfoundWindow[i], strBuf)){
			hWnd = sfoundWindow[i];
			break;
		}
	}

    
	return hWnd;
}

HWND CTestDlg::findSaveTypeWindow(){

	HWND hSaveAsWindow = ::FindWindow(NULL,"另存为");
	HWND hSaveType = NULL;
	hSaveType = findTargetWindow(hSaveAsWindow, ComboBox_Window, new IsSaveTypeWindow());

	return hSaveType;
}

HWND CTestDlg::findSaveNameWindow(){
	// 1 找到 另存为对话框
	//HWND saveAsHwnd = FindWindowEx(parent,NULL,"另存为",NULL);
	
	HWND saveAsHwnd = NULL;
	HWND hEditWnd = NULL;
	int count = 0;
	while(NULL==saveAsHwnd && count<10){
		Sleep(100);
		count++;
		saveAsHwnd = ::FindWindow(NULL,"另存为");
	}
	
	count = 0;
	while(NULL==hEditWnd && count<10){
		Sleep(100);
		count++;
		hEditWnd = findTargetWindow(saveAsHwnd, Edit_Window, new IsSaveNameEdit());
	}

	//hEditWnd = findTargetWindow(saveAsHwnd, Edit_Window, new IsSaveNameEdit());
	return hEditWnd;
}

HWND CTestDlg::findRecur(HWND hParent, TCHAR* fileType){
	HWND hWndChild =::GetWindow(hParent,GW_CHILD); 

	char type[101] = "";
	memset(type,0,sizeof(type));

	while(NULL != hWndChild){
		memset(type,0,sizeof(type));
		::GetClassName(hWndChild,type,100);
		if(0 == strcmp(fileType,type)){
			sfoundWindow[sIndex] = hWndChild;
			sIndex++;
		}
		findRecur(hWndChild, fileType);
		hWndChild = ::GetWindow(hWndChild, GW_HWNDNEXT);
	}

	return NULL;
}


void CTestDlg::OpenWithNotepad(TCHAR* path){
	//ShellExecute(this->m_hWnd, "find",path,NULL,NULL,SW_SHOW);
	SHELLEXECUTEINFO ShExecInfo = {0};
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShExecInfo.hwnd = NULL;
	ShExecInfo.lpVerb = NULL;
	TCHAR buf[100] = "";
	::GetSystemDirectory(buf,100);
	CString notepadPath = buf;
	notepadPath += "\\notepad.exe";
	
	ShExecInfo.lpFile = notepadPath.GetBuffer(notepadPath.GetLength());
	ShExecInfo.lpParameters = path;
	ShExecInfo.lpDirectory = NULL;
	ShExecInfo.nShow = SW_SHOW;
	ShExecInfo.hInstApp = NULL;
	ShellExecuteEx(&ShExecInfo);

	return;
}

void CTestDlg::CloseNotepad(){
	::SendMessage(mNotepad, WM_CLOSE, 0 , 0);
	mNotepad = NULL;
}

void CTestDlg::OnSelectDir() 
{
	HWND hwnd= GetSafeHwnd();   //得到窗口句柄
	CString filePath= "";	//得到文件路径
	LPMALLOC pMalloc;
	if (::SHGetMalloc(&pMalloc) == NOERROR)	//取得IMalloc分配器接口
	{   
	BROWSEINFO bi;
	TCHAR pszBuffer[MAX_PATH];
	LPITEMIDLIST pidl;   
	bi.hwndOwner = hwnd;
	bi.pidlRoot	= NULL;
	bi.pszDisplayName = pszBuffer;
	bi.lpszTitle = _T("选择文件夹"); //选择目录对话框的上部分的标题
	//添加新建文件夹按钮 BIF_NEWDIALOGSTYLE
	bi.ulFlags =  BIF_RETURNONLYFSDIRS | BIF_RETURNFSANCESTORS;
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;
	if ((pidl = ::SHBrowseForFolder(&bi)) != NULL)  //取得IMalloc分配器接口
	{   
		if (::SHGetPathFromIDList(pidl, pszBuffer)) //获得一个文件系统路径
		{
			filePath = pszBuffer;
			SetDlgItemText(IDC_EDIT_SRC,filePath);
		}
		pMalloc->Free(pidl);	//释放内存
		//MessageBox(filePath);
		mSrcDir = filePath;
	}
	pMalloc->Release();	//释放接口
	}	
}

void CTestDlg::getAllFiles( CString path, vector<string>& files)
{  
	if(path.GetLength()==0){
		return;
	}
	CString tmp;
	int index;
    //文件句柄  
    long   hFile   =   0;  
    //文件信息  
    struct _finddata_t fileinfo;  //很少用的文件信息读取结构
    string p;  //string类很有意思的一个赋值函数:assign()，有很多重载版本
    if((hFile = _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo)) !=  -1)  
    {  
        do  
        {   
            if((fileinfo.attrib &  _A_SUBDIR))  //比较文件类型是否是文件夹
            {  
                if(strcmp(fileinfo.name,".") != 0  &&  strcmp(fileinfo.name,"..") != 0)  
                {
                    //files.push_back(p.assign(path).append("\\").append(fileinfo.name) );
                    getFilesAll( p.assign(path).append("\\").append(fileinfo.name), files ); 
                }
            }  
            else  
            {  
				tmp = fileinfo.name;
				index = tmp.ReverseFind('.');
				CString tt = tmp.Right(tmp.GetLength()-index);
				if (!tmp.Right(tmp.GetLength()-index).CompareNoCase(H_SUFFIX)
					|| !tmp.Right(tmp.GetLength()-index).CompareNoCase(C_SUFFIX)
					|| !tmp.Right(tmp.GetLength()-index).CompareNoCase(CPP_SUFFIX)
					|| !tmp.Right(tmp.GetLength()-index).CompareNoCase(JAVA_SUFFIX)
					){
					files.push_back(p.assign(path).append("\\").append(fileinfo.name) );  
				}
                
            }  
        }while(_findnext(hFile, &fileinfo)  == 0);  //寻找下一个，成功返回0，否则-1
        _findclose(hFile); 
    } 
}


void CTestDlg::getFilesAll( string path, vector<string>& files)
{  
	CString tmp;
	int index;
    //文件句柄  
    long   hFile   =   0;  
    //文件信息  
    struct _finddata_t fileinfo;  
    string p;  
    if((hFile = _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo)) !=  -1)  
    {  
        do  
        {    
            if((fileinfo.attrib &  _A_SUBDIR))  
            {  
                if(strcmp(fileinfo.name,".") != 0  &&  strcmp(fileinfo.name,"..") != 0)  
                {
                    //files.push_back(p.assign(path).append("\\").append(fileinfo.name) );
                    getFilesAll( p.assign(path).append("\\").append(fileinfo.name), files ); 
                }
            }  
            else  
            {  
				
				tmp = fileinfo.name;
				index = tmp.ReverseFind('.');
				CString tt = tmp.Right(tmp.GetLength()-index);
				if (!tmp.Right(tmp.GetLength()-index).CompareNoCase(H_SUFFIX)
					|| !tmp.Right(tmp.GetLength()-index).CompareNoCase(C_SUFFIX)
					|| !tmp.Right(tmp.GetLength()-index).CompareNoCase(CPP_SUFFIX)
					|| !tmp.Right(tmp.GetLength()-index).CompareNoCase(JAVA_SUFFIX)
					)
				{
					files.push_back(p.assign(path).append("\\").append(fileinfo.name) );  
				}

                
            }  
        }while(_findnext(hFile, &fileinfo)  == 0);  
        _findclose(hFile); 
    } 
}


void CTestDlg::removeOriginalFile(TCHAR *originalFile){
	CFile    tempFile;
	tempFile.Remove(originalFile);
}

void CTestDlg::renameFile(TCHAR *oldNameFile, TCHAR *newNameFile){
	CFile    tempFile;
	tempFile.Rename(oldNameFile,newNameFile);
}

