#pragma once
#include "afxdialogex.h"


// WarnDlg 对话框

class WarnDlg : public CDialogEx
{
	DECLARE_DYNAMIC(WarnDlg)

public:
	WarnDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~WarnDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WARN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString text_var;
};
