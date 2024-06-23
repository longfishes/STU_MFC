// NoticeDlg.cpp: 实现文件
//

#include "pch.h"
#include "STU_MFC.h"
#include "afxdialogex.h"
#include "NoticeDlg.h"

// NoticeDlg 对话框

IMPLEMENT_DYNAMIC(NoticeDlg, CDialogEx)

NoticeDlg::NoticeDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_NOTICEDlg, pParent)
    , text_var(_T(""))
{

}

NoticeDlg::~NoticeDlg()
{
}

void NoticeDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_STATIC_TEXT, text_var);
}

BEGIN_MESSAGE_MAP(NoticeDlg, CDialogEx)
    ON_BN_CLICKED(IDCANCEL, &NoticeDlg::OnCancelButtonClicked) // 绑定取消按钮的点击事件
END_MESSAGE_MAP()

// NoticeDlg 消息处理程序

void NoticeDlg::OnOK()
{
    // 调用 EndDialog(IDOK) 以关闭对话框并返回 IDOK
    EndDialog(IDOK);
}

void NoticeDlg::OnCancelButtonClicked()
{
    // 调用 EndDialog(IDCANCEL) 以关闭对话框并返回 IDCANCEL
    EndDialog(IDCANCEL);
}
