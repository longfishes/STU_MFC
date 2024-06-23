#include "pch.h"
#include "NewDialog.h"
#include "afxdialogex.h"

IMPLEMENT_DYNAMIC(CNewDialog, CDialogEx)

CNewDialog::CNewDialog(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_NEW_DIALOG, pParent)
{
}

void CNewDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CNewDialog, CDialogEx)
END_MESSAGE_MAP()
