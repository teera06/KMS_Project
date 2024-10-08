
// KMS_MFC_projectDlg.h: 헤더 파일
//

#pragma once


// CKMSMFCprojectDlg 대화 상자
class CKMSMFCprojectDlg : public CDialogEx
{
	
// 생성입니다.
public:
	CKMSMFCprojectDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_KMS_MFC_PROJECT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

public:
	afx_msg void OnBnClickedX1y1Input();
	afx_msg void OnBnClickedX2y2Input();
	afx_msg void OnBnClickedDrawBt();
	afx_msg void OnBnClickedActionBt();
	afx_msg void OnBnClickedOpenBt();

	void UpdateDisPlay(); // 화면 그리기 기능
	void MoveCircle();
// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	CImage m_image;

	int m_nx1 = 0;
	int m_ny1 = 0;
	int m_nx2 = 0;
	int m_ny2 = 0;


	
	

};
