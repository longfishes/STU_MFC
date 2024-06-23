#pragma once
#include "afxdialogex.h"

// INPUT_LINE 对话框

class INPUT_LINE : public CDialogEx
{
	DECLARE_DYNAMIC(INPUT_LINE)

public:
	INPUT_LINE(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~INPUT_LINE();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INPUT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog(); // 重载 OnInitDialog 函数

	DECLARE_MESSAGE_MAP()
public:
	CString value;
	CString text_var;

	// 声明一个公共成员函数，允许外部修改静态文本控件的值
	void SetStaticText(const CString& text);

	// 声明 Edit 控件成员变量
	CEdit m_editCtrl;
};