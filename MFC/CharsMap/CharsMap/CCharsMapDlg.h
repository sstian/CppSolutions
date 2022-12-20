#pragma once

constexpr int TIMER_CODE = 2019;		//定时器点击触发ID
constexpr UINT START_ALPHA = 0xF8A0;	//0xF8A0 自定义起始字符的Unicode编码值 A = 0xF8A1

// CCharsMapDlg 对话框

class CCharsMapDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCharsMapDlg)

public:
	CCharsMapDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CCharsMapDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHARSMAP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:

	enum Alpha							//字母序号
	{
		A = 1, B, C, D, E, F, G, H, I, 
		J, K, L, M, N, O, P, Q, 
		R, S, T, U, V, W, X, Y, Z
	};
	CStringArray m_alphas;				//自定义字符的字符串数组，0: Space, 1-26:A-Z, 27: all
	CRichEditCtrl* m_prich;				//获得视图指针，引用的operator=被删除

	CFont m_font;						//字体设置
	//CArray<CMFCButton*> m_pmfcbtns;		//控件关联变量动态数组
	CUIntArray m_ids;					//控件IDs
	CMap<int, int, CMFCButton*, CMFCButton*> m_mapidbtn;	//映射：控件ID - 关联变量
	CMFCButton m_mfcbtnA;
	CMFCButton m_mfcbtnB;
	CMFCButton m_mfcbtnC;
	CMFCButton m_mfcbtnD;
	CMFCButton m_mfcbtnE;
	CMFCButton m_mfcbtnF;
	CMFCButton m_mfcbtnG;
	CMFCButton m_mfcbtnH;
	CMFCButton m_mfcbtnI;

	CMFCButton m_mfcbtnJ;
	CMFCButton m_mfcbtnK;
	CMFCButton m_mfcbtnL;
	CMFCButton m_mfcbtnM;
	CMFCButton m_mfcbtnN;
	CMFCButton m_mfcbtnO;
	CMFCButton m_mfcbtnP;
	CMFCButton m_mfcbtnQ;

	CMFCButton m_mfcbtnR;
	CMFCButton m_mfcbtnS;
	CMFCButton m_mfcbtnT;
	CMFCButton m_mfcbtnU;
	CMFCButton m_mfcbtnV;
	CMFCButton m_mfcbtnW;
	CMFCButton m_mfcbtnX;
	CMFCButton m_mfcbtnY;
	CMFCButton m_mfcbtnZ;

	CMFCButton m_mfcbtnSpace;
	CMFCButton m_mfcbtnEnter;


	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnBnClickedMfcbtnA();
//	afx_msg void OnSetfocusMfcbtnA();
//	afx_msg void OnKillfocusMfcbtnA();	
	afx_msg void OnBnClickedMfcbtnB();
	afx_msg void OnBnClickedMfcbtnC();
	afx_msg void OnBnClickedMfcbtnD();
	afx_msg void OnBnClickedMfcbtnE();
	afx_msg void OnBnClickedMfcbtnF();
	afx_msg void OnBnClickedMfcbtnG();
	afx_msg void OnBnClickedMfcbtnH();
	afx_msg void OnBnClickedMfcbtnI();
	afx_msg void OnBnClickedMfcbtnJ();
	afx_msg void OnBnClickedMfcbtnK();
	afx_msg void OnBnClickedMfcbtnL();
	afx_msg void OnBnClickedMfcbtnM();
	afx_msg void OnBnClickedMfcbtnN();
	afx_msg void OnBnClickedMfcbtnO();
	afx_msg void OnBnClickedMfcbtnP();
	afx_msg void OnBnClickedMfcbtnQ();
	afx_msg void OnBnClickedMfcbtnR();
	afx_msg void OnBnClickedMfcbtnS();
	afx_msg void OnBnClickedMfcbtnT();
	afx_msg void OnBnClickedMfcbtnU();
	afx_msg void OnBnClickedMfcbtnV();
	afx_msg void OnBnClickedMfcbtnW();
	afx_msg void OnBnClickedMfcbtnX();
	afx_msg void OnBnClickedMfcbtnY();
	afx_msg void OnBnClickedMfcbtnZ();
	afx_msg void OnBnClickedMfcbtnSpace();
	afx_msg void OnBnClickedMfcbtnEnter();
};
