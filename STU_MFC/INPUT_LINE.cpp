#include "pch.h"
#include "STU_MFC.h"
#include "afxdialogex.h"
#include "INPUT_LINE.h"

// INPUT_LINE 对话框

IMPLEMENT_DYNAMIC(INPUT_LINE, CDialogEx)

INPUT_LINE::INPUT_LINE(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_INPUT, pParent)
	, value(_T(""))
	, text_var(_T(""))
{
}

INPUT_LINE::~INPUT_LINE()
{
}

void INPUT_LINE::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT, value);
	DDX_Text(pDX, IDC_STATIC_TEXT, text_var);
	DDX_Control(pDX, IDC_EDIT, m_editCtrl);  // 绑定 Edit 控件
}

BEGIN_MESSAGE_MAP(INPUT_LINE, CDialogEx)
END_MESSAGE_MAP()

// 实现设置静态文本控件值的函数
void INPUT_LINE::SetStaticText(const CString& text)
{
	text_var = text;
}

// 重载 OnInitDialog 函数
BOOL INPUT_LINE::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置默认焦点到 Edit 控件
	m_editCtrl.SetFocus();

	// 返回 FALSE 以指示我们已手动设置焦点
	return FALSE;
}