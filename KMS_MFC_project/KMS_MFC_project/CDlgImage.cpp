// CDlgImage.cpp: 구현 파일
//

#include "pch.h"
#include "KMS_MFC_project.h"
#include "afxdialogex.h"
#include "CDlgImage.h"


// CDlgImage 대화 상자

IMPLEMENT_DYNAMIC(CDlgImage, CDialogEx)

CDlgImage::CDlgImage(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CDlgImage, pParent)
{
	m_pParent = pParent;
}

CDlgImage::~CDlgImage()
{
}

void CDlgImage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

void CDlgImage::InitImage()
{
	int nWidth = 640;
	int nHeight = 480;
	int nBpp = 8;

	m_image.Create(nWidth, -nHeight, nBpp);

	// 기본 옵션 코드
	if (nBpp == 8)
	{
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
		{
			rgb[i].rgbRed = rgb[i].rgbBlue = rgb[i].rgbGreen = i;
		}

		m_image.SetColorTable(0, 256, rgb);
	}

	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();


	memset(fm, 0xff, nWidth * nHeight);
}

bool CDlgImage::IsInCircle(int _x, int _y, int _CenterX, int _CenterY, int _radius)
{
	bool bRet = false;

	double dX = _x - _CenterX;
	double dY = _y - _CenterY;
	double dDist = dX * dX + dY * dY;

	if (dDist < _radius * _radius)
	{
		bRet = true;
	}

	return bRet;
}

void CDlgImage::DrawCircle(int _x, int _y, int _radius, int _Color)
{
	unsigned char* fm = (unsigned char*)m_image.GetBits();
	int nCenterX = _x + _radius;
	int nCenterY = _y + _radius;
	int nPitch = m_image.GetPitch();

	for (int j = _y; j < _y + _radius * 2; j++)
	{
		for (int i = _x; i < _x + _radius * 2; i++)
		{
			if (true == IsInCircle(i, j, nCenterX, nCenterY, _radius))
			{
				fm[j * nPitch + i] = _Color;
			}
		}
	}
}

void CDlgImage::ImageClear()
{
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	memset(fm, 0xff, nWidth * nHeight); // 전체를 초기화 하는 방법이라 부담이 큼
}

void CDlgImage::UpdateDisPlay()
{
	CClientDC dc(this);
	m_image.Draw(dc, 0, 0); // 그려주는 위치
}

void CDlgImage::MoveCircle(int& _x1, int& _y1, const int _x2, const int _y2, const int _radius)
{
	int nGray = 100;
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	int nPitch = m_image.GetPitch();
	int nRadius = _radius;

	unsigned char* fm = (unsigned char*)m_image.GetBits();


	//memset(fm, 0xff, nWidth * nHeight); // 전체를 초기화 하는 방법이라 부담이 큼
	DrawCircle(_x1, _y1, nRadius, 0xff); // 그전꺼 화면을 초기화

	if (_x1 != _x2)
	{
		++_x1;
	}

	if (_y1 != _y2)
	{
		++_y1;
	}

	DrawCircle(_x1, _y1, nRadius, nGray); // 그리기




	UpdateDisPlay();
}

bool CDlgImage::ValidImgPos(int _x, int _y)
{
	

	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();

	CRect rect(0, 0, nWidth, nHeight); // 체크 범위를 만듬

	return rect.PtInRect(CPoint(_x, _y)); // 해당 범위안에 있는지 체크
}


BEGIN_MESSAGE_MAP(CDlgImage, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CDlgImage 메시지 처리기


BOOL CDlgImage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	MoveWindow(0, 0, 640, 480);
	InitImage();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CDlgImage::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.

	if (m_image)
	{
		m_image.Draw(dc, 0, 0);
	}
}
