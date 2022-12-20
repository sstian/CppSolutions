
// PageDlg.h: 头文件
//

#pragma once


// CPageDlg 对话框
class CPageDlg : public CDialogEx
{
private:
	enum {PAGE_COUNT = 3};			//图像个数
	int m_index;					//位图数组索引
	CBitmap m_bitmaps[PAGE_COUNT];	//方法1.1 位图数组对象，只能加.bmp图像
	CRect m_rects[PAGE_COUNT];

	CString m_strImages[PAGE_COUNT];//文件路径 .jpg
	CBitmap* m_pBitmaps[PAGE_COUNT];//方法2.1 加载其它图像指针数组，如：.jpg

	HCURSOR m_hCursor;				//光标
	//// 屏蔽虚函数OnOk()的消息响应（似乎没什么用？按下Enter或Esc键仍能退出对话框）
	//void OnOk() {}

// 构造
public:
	CPageDlg(CWnd* pParent = nullptr);	// 标准构造函数
	virtual ~CPageDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PAGE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
