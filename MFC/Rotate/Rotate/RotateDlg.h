
// RotateDlg.h: 头文件
//

#pragma once


// CRotateDlg 对话框
class CRotateDlg : public CDialogEx
{
private:
	int m_left;	//左边位置
	int m_dir;	//旋转方向
	//CBitmap m_bitmap;
	// 方案二：双缓冲
	CMemoryDC m_mdc;	
	CMemoryDC m_mdcBack;
	
// 构造
public:
	CRotateDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ROTATE_DIALOG };
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
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
