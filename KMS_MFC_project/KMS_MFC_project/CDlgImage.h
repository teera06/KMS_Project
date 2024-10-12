#pragma once
#include "afxdialogex.h"


// CDlgImage 대화 상자

class CDlgImage : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgImage)

public:
	CDlgImage(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgImage();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CDlgImage };
#endif

public:
	void DrawCircle(int _x, int _y, int _radius, int _Color);
	void ImageClear();
	void UpdateDisPlay();
	void MoveCircle(int& _x1, int& _y1, const int _x2, const int _y2, const int _radius);
	void SaveImage(const CString& _path);
	void Load(const CString& _path);
	bool ValidImgPos(int _x, int _y);
	
	CImage GetCImage()
	{
		return m_image;
	}
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
private:
	CWnd* m_pParent=nullptr;
	CImage m_image;

	bool m_ImageLoadCheck = false;

	void InitImage();
	bool IsInCircle(int _x, int _y, int _CenterX, int _CenterY, int _radius);
	
};
