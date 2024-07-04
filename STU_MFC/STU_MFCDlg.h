
// STU_MFCDlg.h: 头文件
//

#pragma once


// CSTUMFCDlg 对话框
class CSTUMFCDlg : public CDialogEx
{
// 构造
public:
	CSTUMFCDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STU_MFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnItemDoubleClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedAddStuButton();
	afx_msg void OnBnClickedEditStuButton();
	afx_msg void OnBnClickedQueryStuButton();
	afx_msg void OnBnClickedQueryFieldButton();
	afx_msg void OnBnClickedDeleteStuButton();
	afx_msg void OnBnClickedAddFieldButton();
	afx_msg void OnBnClickedDeleteFieldButton();
	afx_msg void OnBnClickedEditFieldButton();
	afx_msg void OnBnClickedShowFieldButton();
	afx_msg void OnClearButtonClicked();
	CListCtrl m_list;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void LoadList();
	afx_msg void LoadListFiled();
	afx_msg void LoadStuHeader();
	afx_msg void LoadFieldHeader();
	afx_msg void ClearAllList();
	std::string GetSelectedId();
	std::vector<CString> GetSelectedIds();
	CString query_text;
	CEdit m_query;
	CButton btn_add_stu;
	CButton btn_edit_stu;
	CButton btn_delete_stu;
	CButton btn_search;
	CButton btn_show_field;
	CButton btn_add_field;
	CButton btn_edit_field;
	CButton btn_delete_field;
	bool isFieldManage = 0;
};


