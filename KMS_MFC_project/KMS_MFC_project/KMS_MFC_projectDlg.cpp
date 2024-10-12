
// KMS_MFC_projectDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "KMS_MFC_project.h"
#include "KMS_MFC_projectDlg.h"

#include <iostream>
#include "DebugHelper.h"
#include "CDlgImage.h"
#include "RandomHelper.h"


#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#pragma comment(linker, "/entry:WinmainCRTStartup /subsystem:console") // 디버그 모드일때 콘솔창 사용
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CKMSMFCprojectDlg 대화 상자



CKMSMFCprojectDlg::CKMSMFCprojectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_KMS_MFC_PROJECT_DIALOG, pParent)
	, m_nx1(0), m_ny1(0), m_nx2(0), m_ny2(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CKMSMFCprojectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_x1, m_nx1);
	DDX_Text(pDX, IDC_y1, m_ny1);
	DDX_Text(pDX, IDC_x2, m_nx2);
	DDX_Text(pDX, IDC_y2, m_ny2);
}

BEGIN_MESSAGE_MAP(CKMSMFCprojectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_Draw_BT, &CKMSMFCprojectDlg::OnBnClickedDrawBt)
	ON_BN_CLICKED(IDC_Action_BT, &CKMSMFCprojectDlg::OnBnClickedActionBt)
	ON_BN_CLICKED(IDC_Open_BT, &CKMSMFCprojectDlg::OnBnClickedOpenBt)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CKMSMFCprojectDlg 메시지 처리기

BOOL CKMSMFCprojectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_pDlgImage = new CDlgImage;
	m_pDlgImage->Create(IDD_CDlgImage, this);
	m_pDlgImage->ShowWindow(SW_SHOW);

	MoveWindow(0, 0, 1280, 720);
	InitSavePath();
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CKMSMFCprojectDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CKMSMFCprojectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);

	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CKMSMFCprojectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CKMSMFCprojectDlg::OnBnClickedDrawBt()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(true); // 수정된 값 처리


	std::cout << "X1 : " << m_nx1 << ", Y1 : " << m_ny1 << "\n";
	std::cout << "X2 : " << m_nx2 << ", Y2 : " << m_ny2 << "\n";


	UpdateData(false); // 이걸 해줘야 업데이트 됨
	
	if (nullptr == m_pDlgImage)
	{
		return;
	}
	
	int nGray = 100;
	
	m_nRadius = CRandomHelper::MainRandom.RandomInt(10, 150);

	//unsigned char* fm = (unsigned char*)m_image.GetBits();
	m_pDlgImage->ImageClear();
	m_pDlgImage->DrawCircle(m_nx1, m_ny1, m_nRadius, nGray);

	m_pDlgImage->UpdateDisPlay();

	
}


void CKMSMFCprojectDlg::OnBnClickedActionBt()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// 이미지 저장용
	UpdateData(true); // 수정된 값 처리


	std::cout << "X1 : " << m_nx1 << ", Y1 : " << m_ny1 << "\n";
	std::cout << "X2 : " << m_nx2 << ", Y2 : " << m_ny2 << "\n";


	UpdateData(false); // 이걸 해줘야 업데이트 됨

	if (nullptr == m_pDlgImage)
	{
		return;
	}

	m_pDlgImage->ImageClear();
	CString Result = SavePath.GetCurPath();
	
	//m_image.Save(_T("D:\\save.png"));
	while (true)
	{
		if (m_nx1 == m_nx2 && m_ny1 == m_ny2)
		{
			break;
		}

		if(false == m_pDlgImage->ValidImgPos(m_nx2, m_ny2))
		{
			MsgBoxLog("x2, y2 범위를 초과했습니다.");
			break;
		}
		m_pDlgImage->MoveCircle(m_nx1, m_ny1, m_nx2, m_ny2, m_nRadius);
		Sleep(10);

		if (m_nImageCount % 2 == 0) // 이미지가 너무 많이 저장되서 절반으로 줄임
		{
			m_pDlgImage->SaveImage(GetImageName());
			++m_nImageCount;
		}
		else
		{
			++m_nImageCount;
		}
		//m_pDlgImage->SaveImage(GetImageName());
	}
}



void CKMSMFCprojectDlg::OnBnClickedOpenBt()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	//ShellExecute(NULL, _T("open"), SavePath.GetCurPath(), NULL, NULL, SW_SHOW);

	static TCHAR BASED_CODE szFilter[] = _T("이미지 파일(*.BMP, *.GIF, *.JPG) | *.BMP;*.GIF;*.JPG;*.bmp;*.jpg;*.gif |모든파일(*.*)|*.*||");

	CFileDialog dlg(TRUE, _T("*.bmp"), _T("image"), OFN_HIDEREADONLY, szFilter);

	if (IDOK == dlg.DoModal())

	{

		CString pathName = dlg.GetPathName();



		//MessageBox(pathName);
	
		
		m_pDlgImage->Load(pathName);

	}
	//[출처] [MFC] 파일열기 대화상자(CFileDialog) | 작성자 꼬꼬꼬
	/*if (m_image != nullptr)
	{
		m_image.Destroy();
	}*/

	//UpdateDisPlay();


}


void CKMSMFCprojectDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	delete m_pDlgImage;
	m_pDlgImage = nullptr;
}

void CKMSMFCprojectDlg::InitSavePath()
{
	SavePath.MoveToSearchChild(_T("KMS_MFC_project"));
	SavePath.Move(_T("CreateImage"));
}

CString CKMSMFCprojectDlg::GetImageName()
{
	CString Result;
	Result.Format(_T("\\SaveImage%d.bmp"),m_nImageCount);
	Result = SavePath.GetCurPath() + Result;
	return Result;
}
