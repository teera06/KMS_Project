// CDlgImage.cpp: 구현 파일
//

#include "pch.h"
#include "KMS_MFC_project.h"
#include "afxdialogex.h"
#include <iostream>
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
			if (i == m_image.GetWidth())
			{
				break;
			}

			if (j == m_image.GetHeight())
			{
				AreaCheck = true;
				return;
			}

			if (true == IsInCircle(i, j, nCenterX, nCenterY, _radius))
			{
				fm[j * nPitch + i] = _Color;
			}
		}
	}
}

void CDlgImage::ImageClear()
{
	if (true == m_ImageLoadCheck)
	{
		m_image.Destroy();
		m_ImageLoadCheck=false;
		InitImage();
		//UpdateDisPlay();
	}
	else
	{
		int nWidth = m_image.GetWidth();
		int nHeight = m_image.GetHeight();
		unsigned char* fm = (unsigned char*)m_image.GetBits();

		memset(fm, 0xff, nWidth * nHeight); // 전체를 초기화 하는 방법이라 부담이 큼

	}
}

void CDlgImage::UpdateDisPlay()
{
	CClientDC dc(this);
	m_image.Draw(dc, 0, 0); // 그려주는 위치
}

void CDlgImage::MoveCircle(int& _x1, int& _y1, const int _x2, const int _y2, const int _radius)
{
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	int nPitch = m_image.GetPitch();

	unsigned char* fm = (unsigned char*)m_image.GetBits();


	//memset(fm, 0xff, nWidth * nHeight); // 전체를 초기화 하는 방법이라 부담이 큼
	DrawCircle(_x1, _y1, _radius, 0xff); // 그전꺼 화면을 초기화

	if (_x1 != _x2)
	{
		if (_x1 > _x2)
		{
			--_x1;
		}
		else if (_x1 < _x2)
		{
			++_x1;
		}
	}


	if (_y1 != _y2)
	{
		if (_y1 > _y2)
		{
			--_y1;
		}
		else if (_y1 < _y2)
		{
			++_y1;
		}
	}

	if (true == AreaCheck)
	{
		return;
	}

	DrawCircle(_x1, _y1, _radius, m_nGray); // 그리기




	UpdateDisPlay();
}

void CDlgImage::SaveImage(const CString& _path)
{
	m_image.Save(_path);
}

void CDlgImage::Load(const CString& _path)
{
	if (nullptr != m_image)
	{
		m_image.Destroy();
	}

	m_image.Load(_path);
	UpdateDisPlay();
	m_ImageLoadCheck = true;
}

void CDlgImage::LoadImageEdit(int x, int y)
{
	
	CClientDC dc(this);

	// X 모양의 선 길이와 두께 설정
	int Len = 5;  // X의 선 길이
	int Area = 2;    // 선의 두께

	// 빨간색 X를 그리기 위한 펜 설정
	CPen pen(PS_SOLID, Area, RGB(255, 0, 255));  
	CPen* pOldPen = dc.SelectObject(&pen);

	// X 모양의 대각선 그리기
	dc.MoveTo(x - Len, y - Len);
	dc.LineTo(x + Len, y + Len);

	dc.MoveTo(x - Len, y + Len);
	dc.LineTo(x + Len, y - Len);

	CString Text;
	Text.Format(_T("(X : %d, Y : %d)"), x, y);
	dc.TextOut(x-30, y+10, Text);

	// 원래 펜으로 복원
	dc.SelectObject(pOldPen);
}

bool CDlgImage::ValidImgPos(int _x, int _y)
{
	

	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();

	CRect rect(0, 0, nWidth, nHeight); // 체크 범위를 만듬

	return rect.PtInRect(CPoint(_x, _y)); // 해당 범위안에 있는지 체크
}

bool CDlgImage::CenterXYCheck(int& centerX, int& centerY)
{
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	int nPitch = m_image.GetPitch();
	int bpp = m_image.GetBPP();  // 이미지 비트 깊이를 가져옴

	unsigned char* fm = (unsigned char*)m_image.GetBits();

	int nCount = 0;  // 원의 픽셀 수
	int nSumX = 0;
	int nSumY = 0;  // 원 픽셀의 x, y 좌표 합

	if (bpp == 8) {  
		for (int y = 0; y < nHeight; y++) {
			for (int x = 0; x < nWidth; x++) {
				int pixelValue = fm[y * nPitch + x];

				if (pixelValue == m_nGray) 
				{  // 회색 픽셀 범위 조정
					nSumX += x;
					nSumY += y;
					nCount++;
				}
			}
		}
	}

	if (nCount > 0)
	{
		centerX = nSumX / nCount;
		centerY = nSumY / nCount;
		return true;  // 중심 찾기 성공
	}

	return false;  // 원을 찾지 못함
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
