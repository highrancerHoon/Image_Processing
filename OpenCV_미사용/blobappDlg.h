
// blobappDlg.h: 헤더 파일
//

#pragma once


// CblobappDlg 대화 상자
class CblobappDlg : public CDialogEx
{
// 생성입니다.
private:
	CImage mainimage; // 원본이미지
	CImage grayimage; // 그레이이미지
	CImage thresholdimage; // 이진화이미지
	CImage edgeimage; // 관심영역이미지
	CImage combinedimage; //원본과 관심영역을 합친 이미지
public:
	CblobappDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BLOBAPP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedOk2();
	afx_msg void OnBnClickedOk3();
	afx_msg void OnBnClickedOk4();
	afx_msg void OnBnClickedOk5();
};
