#pragma once
#include "afxdialogex.h"

// NoticeDlg 对话框

class NoticeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(NoticeDlg)

public:
	NoticeDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~NoticeDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NOTICEDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	CString text_var;

protected:
	virtual void OnOK(); // 重写 OnOK 函数
	afx_msg void OnCancelButtonClicked(); // 声明取消按钮的消息处理函数
};
