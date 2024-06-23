// WarnDlg.cpp: 实现文件
//

#include "pch.h"
#include "STU_MFC.h"
#include "afxdialogex.h"
#include "WarnDlg.h"


// WarnDlg 对话框

IMPLEMENT_DYNAMIC(WarnDlg, CDialogEx)

WarnDlg::WarnDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_WARN, pParent)
	, text_var(_T(""))
{

}

WarnDlg::~WarnDlg()
{
}

void WarnDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_TEXT, text_var);
}


BEGIN_MESSAGE_MAP(WarnDlg, CDialogEx)
END_MESSAGE_MAP()


// WarnDlg 消息处理程序
