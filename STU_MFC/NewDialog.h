#pragma once

class CNewDialog : public CDialogEx
{
public:
    CNewDialog(CWnd* pParent = nullptr);   // 标准构造函数

    // 对话框数据
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_NEW_DIALOG };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

protected:
    DECLARE_MESSAGE_MAP()
};
