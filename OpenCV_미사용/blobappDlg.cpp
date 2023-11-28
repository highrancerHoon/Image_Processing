
// blobappDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "blobapp.h"
#include "blobappDlg.h"
#include "afxdialogex.h"
#include <atlimage.h>

#ifdef _DEBUG
#define new DEBUG_NEW
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


// CblobappDlg 대화 상자



CblobappDlg::CblobappDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BLOBAPP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CblobappDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CblobappDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CblobappDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDOK2, &CblobappDlg::OnBnClickedOk2)
	ON_BN_CLICKED(IDOK3, &CblobappDlg::OnBnClickedOk3)
	ON_BN_CLICKED(IDOK4, &CblobappDlg::OnBnClickedOk4)
	ON_BN_CLICKED(IDOK5, &CblobappDlg::OnBnClickedOk5)
END_MESSAGE_MAP()


// CblobappDlg 메시지 처리기

BOOL CblobappDlg::OnInitDialog()
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

	//[원본이미지]
	mainimage.Load(L"blob.jpg"); //원본이미지 로드

	//[그레이이미지]
	grayimage.Create(mainimage.GetWidth(), mainimage.GetHeight(), mainimage.GetBPP(), 0); //원본이미지에서 이미지 크기와 비트 정보를 가져와 이미지 공간 생성

	//[이진화이미지]
	thresholdimage.Create(grayimage.GetWidth(),grayimage.GetHeight(),grayimage.GetBPP(),0); //그레이이미지에서 크기와 비트 정보를 가져와 공간 생성

	//[관심영역이미지]
	edgeimage.Create(thresholdimage.GetWidth(), thresholdimage.GetHeight(), thresholdimage.GetBPP(), 0); //이진화이미지에서 크기와 비트 정보를 가져와 공간 생성

	//[원본과 관심영역이미지를 합친 이미지]
	combinedimage.Create(edgeimage.GetWidth(), edgeimage.GetHeight(), edgeimage.GetBPP(), 0); //관심영역이미지에서 크기와 비트 정보를 가져와 공간 생성

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CblobappDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CblobappDlg::OnPaint()
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
HCURSOR CblobappDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



// 버튼 
void CblobappDlg::OnBnClickedOk()
{
	CClientDC dc(this);

	//CImage출력을 위한 Draw
	mainimage.Draw(dc, 0, 0);

	//크기를 줄이기 위해 사용할 코드
	/*int originalWidth = mainimage.GetWidth();
	int originalHeight = mainimage.GetHeight();

	int newWidth = originalWidth / 1;
	int newHeight = originalHeight / 1;

	StretchBlt(dc.m_hDC, 0, 0, newWidth, newHeight, mainimage.GetDC(), 0, 0, mainimage.GetWidth(), mainimage.GetHeight(), SRCCOPY);*/
}


void CblobappDlg::OnBnClickedOk2()
{
	
	CClientDC dc(this);
	
	COLORREF temp_color;

	int grayvalue;
	int x, y;

	//이미지의 폭, 높이정보를 가져온후 SetPixel을 통해 이미지 색을 다시 칠함
	for (y = 0; y < mainimage.GetHeight(); y++) {
		for (x = 0; x < mainimage.GetWidth(); x++) {
			temp_color = mainimage.GetPixel(x, y);
			grayvalue = (GetRValue(temp_color) + GetGValue(temp_color) + GetBValue(temp_color)) / 3;

			grayimage.SetPixel(x, y, RGB(grayvalue, grayvalue, grayvalue));
		}
	}
	grayimage.Draw(dc, 0, 0);
	/*
	//속도를 빠르게 하기 위해 SetPixel을 사용하지 않으려고 한 코드 
	CClientDC dc(this);

	int R = 0, G = 0, B = 0;
	int grayscale = 0;
	BYTE* byte = (BYTE*)mainimage.GetBits();

	int pitch = mainimage.GetPitch();

	for (int i = 0; i < mainimage.GetWidth(); i++)
		for (int j = 0; j < mainimage.GetHeight(); j++)
		{
			// 이미지의 비트값을 포인터로 저장하여 포인터를 통해 R,G,B값을 가져옴 
			R = *(byte + pitch * j + 3 * i);
			G = *(byte + pitch * j + 3 * i + 1);
			B = *(byte + pitch * j + 3 * i + 2);

			grayscale = (R + G + B) / 3;

			//포인터값을 변경
			*(byte + pitch * j + 3 * i) = grayscale;
			*(byte + pitch * j + 3 * i + 1) = grayscale;
			*(byte + pitch * j + 3 * i + 2) = grayscale;

			grayimage.SetPixel(i, j, RGB(R, G, B));
		}
	grayimage.Draw(dc, 0, 0);
	*/
}


void CblobappDlg::OnBnClickedOk3()
{
	CClientDC dc(this);


	COLORREF temp_color;
	int grayvalue;
	int x, y;

	for (y = 0; y < grayimage.GetHeight(); y++) {
		for (x = 0; x < grayimage.GetWidth(); x++) {
			temp_color = grayimage.GetPixel(x, y);
			grayvalue = temp_color;

			//임계값 범위내에 속하면 흰색으로 색상을 변경하고 그외라면 검정색으로 변경
			if (grayvalue <= RGB(255,255,255)&& grayvalue > RGB(213, 213, 213)) {
				thresholdimage.SetPixel(x, y, RGB(255, 255, 255));
			}
			else {
				thresholdimage.SetPixel(x, y, RGB(0,0,0));
			}
		}
	}
	thresholdimage.Draw(dc, 0, 0);

	/*
	//속도를 빠르게 하기 위해 SetPixel을 사용하지 않으려고 한 코드 
	
	int R = 0, G = 0, B = 0;
	int grayscale = 0;
	BYTE* byte = (BYTE*)grayimage.GetBits();

	int pitch = grayimage.GetPitch();

	for (int i = 0; i < grayimage.GetWidth(); i++)
		for (int j = 0; j < grayimage.GetHeight(); j++)
		{
			R = *(byte + pitch * j + 3 * i);
			G = *(byte + pitch * j + 3 * i + 1);
			B = *(byte + pitch * j + 3 * i + 2);

			grayscale = (R + G + B) / 3;

			//임계값 범위내에 속하면 흰색으로 색상을 변경하고 그외라면 검정색으로 변경
			if (grayscale <= 255 && grayscale > 213) {
				*(byte + pitch * j + 3 * i) = 255;
				*(byte + pitch * j + 3 * i + 1) = 255;
				*(byte + pitch * j + 3 * i + 2) = 255;
			}
			else {
				*(byte + pitch * j + 3 * i) = 0;
				*(byte + pitch * j + 3 * i + 1) = 0;
				*(byte + pitch * j + 3 * i + 2) = 0;
			}
		}

	thresholdimage.Draw(dc, 0, 0);
	*/
}


void CblobappDlg::OnBnClickedOk4()
{
	CClientDC dc(this);

	for (int y = 1; y < thresholdimage.GetHeight() - 1; ++y) {
		for (int x = 1; x < thresholdimage.GetWidth() - 1; ++x) {
			COLORREF currentPixel = thresholdimage.GetPixel(x, y);

			// 주변 픽셀 값 가져오기
			COLORREF leftPixel = thresholdimage.GetPixel(x - 1, y);
			COLORREF rightPixel = thresholdimage.GetPixel(x + 1, y);
			COLORREF upPixel = thresholdimage.GetPixel(x, y - 1);
			COLORREF downPixel = thresholdimage.GetPixel(x, y + 1);

			// 경계를 찾아 외곽선 픽셀로 설정
			if (currentPixel != leftPixel || currentPixel != rightPixel || currentPixel != upPixel || currentPixel != downPixel) {
				edgeimage.SetPixel(x, y, RGB(255, 0, 0)); 
			}
			else {
				edgeimage.SetPixel(x, y, RGB(255, 255, 255));  
			}
		}
	}
	edgeimage.Draw(dc, 0, 0);

	/*
	//속도를 빠르게 하기 위해 SetPixel을 사용하지 않으려고 한 코드 
	int R = 0, G = 0, B = 0;
	int grayscale = 0;
	int leftPixel = 0, rightPixel = 0, upPixel = 0, downPixel = 0;
	BYTE* byte = (BYTE*)thresholdimage.GetBits();

	int pitch = thresholdimage.GetPitch();

	for (int i = 0; i < thresholdimage.GetWidth(); i++)
		for (int j = 0; j < thresholdimage.GetHeight(); j++)
		{
			leftPixel = *(byte + pitch * j + 3 % i);
			rightPixel = *(byte + pitch * j + 3 * i);
			upPixel = *(byte + pitch * j + 3 * i);
			downPixel = *(byte + pitch % j + 3 * i);

			R = *(byte + pitch * j + 3 * i);
			G = *(byte + pitch * j + 3 * i + 1);
			B = *(byte + pitch * j + 3 * i + 2);

			grayscale = (R + G + B) / 3;
		}

	edgeimage.Draw(dc, 0, 0);
	*/
}


void CblobappDlg::OnBnClickedOk5()
{
	CClientDC dc(this);

	double mainWeight = 0.8;  // mainimage에 대한 가중치
	double edgeWeight = 0.2;  // edgeimage에 대한 가중치

	// 이미지 크기가 동일한지 확인
	if (mainimage.GetWidth() == edgeimage.GetWidth() && mainimage.GetHeight() == edgeimage.GetHeight()) {
		

		for (int y = 0; y < mainimage.GetHeight(); ++y) {
			for (int x = 0; x < mainimage.GetWidth(); ++x) {
				// 각 픽셀에 대해 가중치를 적용하여 두 이미지를 합침
				COLORREF mainPixel = mainimage.GetPixel(x, y);
				COLORREF edgePixel = edgeimage.GetPixel(x, y);

				int combinedRed = static_cast<int>(mainWeight * GetRValue(mainPixel) + edgeWeight * GetRValue(edgePixel));
				int combinedGreen = static_cast<int>(mainWeight * GetGValue(mainPixel) + edgeWeight * GetGValue(edgePixel));
				int combinedBlue = static_cast<int>(mainWeight * GetBValue(mainPixel) + edgeWeight * GetBValue(edgePixel));

				combinedimage.SetPixel(x, y, RGB(combinedRed, combinedGreen, combinedBlue));
			}
		}

		// 합쳐진 이미지를 출력
		combinedimage.Draw(dc, 0, 0);
	}
	else {
		// 이미지 크기가 다를 경우 예외 처리
		AfxMessageBox(_T("이미지의 크기가 다릅니다."));
	}
}


