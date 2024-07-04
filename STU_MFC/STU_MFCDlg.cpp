
// STU_MFCDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "STU_MFC.h"
#include "STU_MFCDlg.h"
#include "afxdialogex.h"
#include "INPUT_LINE.h"
#include "StudentList.h"
#include "Util.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

StudentList list;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSTUMFCDlg 对话框



CSTUMFCDlg::CSTUMFCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_STU_MFC_DIALOG, pParent)
	, query_text(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSTUMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MAIN_LIST, m_list);
	DDX_Text(pDX, IDC_SEARCH, query_text);
	DDX_Control(pDX, IDC_SEARCH, m_query);
	DDX_Control(pDX, IDC_ADD_STU, btn_add_stu);
	DDX_Control(pDX, IDC_EDIT_STU, btn_edit_stu);
	DDX_Control(pDX, IDC_DELETE_STU, btn_delete_stu);
	DDX_Control(pDX, IDC_QUERY_STU, btn_search);
	DDX_Control(pDX, IDC_SHOW_FIELD, btn_show_field);
}

BEGIN_MESSAGE_MAP(CSTUMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ADD_STU, &CSTUMFCDlg::OnBnClickedAddStuButton)
	ON_BN_CLICKED(IDC_EDIT_STU, &CSTUMFCDlg::OnBnClickedEditStuButton)
	ON_BN_CLICKED(IDC_QUERY_STU, &CSTUMFCDlg::OnBnClickedQueryStuButton)
	ON_BN_CLICKED(IDC_DELETE_STU, &CSTUMFCDlg::OnBnClickedDeleteStuButton)
	ON_BN_CLICKED(IDC_SHOW_FIELD, &CSTUMFCDlg::OnBnClickedShowFieldButton)
	ON_BN_CLICKED(IDC_CLEAR, &CSTUMFCDlg::OnClearButtonClicked)
	ON_NOTIFY(NM_DBLCLK, IDC_MAIN_LIST, &CSTUMFCDlg::OnItemDoubleClick)
END_MESSAGE_MAP()


// CSTUMFCDlg 消息处理程序

BOOL CSTUMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ModifyStyle(0, WS_MINIMIZEBOX);

	// TODO: 在此添加额外的初始化代码
	list.loads();
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	LoadList();

	if (m_query.GetSafeHwnd() != nullptr)
	{
		m_query.SendMessage(EM_SETCUEBANNER, TRUE, (LPARAM)(LPCTSTR)_T("学号/姓名(Q)"));
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSTUMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSTUMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

BOOL CSTUMFCDlg::PreTranslateMessage(MSG* pMsg)
{
	// 按下Enter键
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		if (btn_search.IsWindowEnabled())
		{
			CSTUMFCDlg::OnBnClickedQueryStuButton();
		}
		return TRUE;
	}
	// ESC键
	if (pMsg->wParam == VK_ESCAPE)
	{
		return TRUE;
	}

	// 按下DEL键
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_DELETE)
	{
		if (btn_delete_stu.IsWindowEnabled())
		{
			OnBnClickedDeleteStuButton();
		}
		else if (btn_delete_field.IsWindowEnabled())
		{
			OnBnClickedDeleteFieldButton();
		}

		return TRUE;
	}

	// 按下Tab键
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_TAB)
	{
		OnBnClickedShowFieldButton();

		return TRUE;
	}

	// 按下ctrl + A键
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == 'A' && (GetKeyState(VK_CONTROL) & 0x8000))
	{
		if (isFieldManage)
		{
			OnBnClickedAddFieldButton();
		}
		else
		{
			OnBnClickedAddStuButton();
		}

		return TRUE;
	}

	// 按下ctrl + E键
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == 'E' && (GetKeyState(VK_CONTROL) & 0x8000))
	{
		if (isFieldManage)
		{
			OnBnClickedEditFieldButton();
		}
		else
		{
			OnBnClickedEditStuButton();
		}

		return TRUE;
	}

	// 按下ctrl + Q键
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == 'Q' && (GetKeyState(VK_CONTROL) & 0x8000))
	{
		if (::GetFocus() != m_query.GetSafeHwnd())
		{
			m_query.SetFocus();
		}

		return FALSE;
	}

	// 按下ctrl + R键
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == 'R' && (GetKeyState(VK_CONTROL) & 0x8000))
	{	
		OnClearButtonClicked();

		return TRUE;
	}

	// 按下 up / down 键
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_UP || pMsg->wParam == VK_DOWN))
	{
		if (::GetFocus() != m_list.GetSafeHwnd())
		{
			m_list.SetFocus();
		}

		return FALSE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

bool containsString(const std::string& haystack, const std::string& needle) {
	return haystack.find(needle) != std::string::npos;
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CSTUMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSTUMFCDlg::OnBnClickedAddStuButton()
{
	if (isFieldManage)
	{
		OnBnClickedAddFieldButton();
		return;
	}
	string id = readLineValid("学号：", "^(20[0-9]{2})\\d{8}$");
	if (id == "cancelled")
	{
		warn("已取消！");
		return;
	}
	while (list.contains(id)) {
		warn("学生已存在！");
		id = readLineValid("学号", "^(20[0-9]{2})\\d{8}$");
		if (id == "cancelled")
		{
			warn("已取消！");
			return;
		}
	}
	string name = readLine("姓名");
	if (name == "cancelled")
	{
		warn("已取消！");
		return;
	}
	string genderStr = readLineValid("性别（1-男 2-女）", "^[1-2]$");
	if (genderStr == "cancelled")
	{
		warn("已取消！");
		return;
	}
	int gender = stoi(genderStr);
	string ageStr = readLineValid("年龄", "^([1-9][0-9]{1,2})$");
	if (ageStr == "cancelled")
	{
		warn("已取消！");
		return;
	}
	int age = stoi(ageStr);
	string province = readLine("省份");
	if (province == "cancelled")
	{
		warn("已取消！");
		return;
	}
	string major = readLine("专业");
	if (major == "cancelled")
	{
		warn("已取消！");
		return;
	}
	ExternalList temp;
	temp.loads();
	map<string, Extend> fs = temp.getData();
	vector<string> vec;
	for (auto it = fs.begin(); it != fs.end(); ++it) {
		string itm = readLineValid(it->second.name, it->second.regex);
		if (itm == "cancelled")
		{
			warn("已取消！");
			return;
		}
		vec.push_back(itm);
	}
	Student stu;
	stu.name = name;
	stu.gender = gender;
	stu.age = age;
	stu.province = province;
	stu.major = major;
	temp.setVal(vec);
	stu.elist = temp;
	list.put(id, stu);
	list.save();
	ClearAllList();
	LoadList();
	notice("操作成功！");
}

void CSTUMFCDlg::OnBnClickedEditStuButton()
{
	if (isFieldManage)
	{
		OnBnClickedEditFieldButton();
		return;
	}
	std::vector<CString> ids = GetSelectedIds();

	if (ids.size() > 1)
	{
		warn("请不要多选！");
		return;
	}

	if (ids.size() == 0) {
		warn("未选中任何学生！");
		return;
	}
	string id = string(CT2A(ids.at(0)));
	Student stu = list.get(id);
	
	string name = readLineDef("姓名", stu.name);
	if (name == "cancelled")
	{
		warn("已取消！");
		return;
	}
	string genderStr = readLineValid("性别（1-男 2-女）", "^[1-2]$", to_string(stu.gender));
	if (genderStr == "cancelled")
	{
		warn("已取消！");
		return;
	}
	int gender = stoi(genderStr);
	string ageStr = readLineValid("年龄", "^([1-9][0-9]{1,2})$", to_string(stu.age));
	if (ageStr == "cancelled")
	{
		warn("已取消！");
		return;
	}
	int age = stoi(ageStr);
	string province = readLineDef("省份", stu.province);
	if (province == "cancelled")
	{
		warn("已取消！");
		return;
	}
	string major = readLineDef("专业", stu.major);
	if (major == "cancelled")
	{
		warn("已取消！");
		return;
	}

	ExternalList temp = stu.elist;
	map<string, Extend> fs = temp.getData();
	vector<string> vec;
	for (auto it = fs.begin(); it != fs.end(); ++it) {
		string itm = readLineValid(it->second.name, it->second.regex, it->second.val);
		vec.push_back(itm);
	}
	stu.name = name;
	stu.gender = gender;
	stu.age = age;
	stu.province = province;
	stu.major = major;
	temp.setVal(vec);
	stu.elist = temp;
	list.put(id, stu);
	list.save();
	ClearAllList();
	LoadList();
	notice("操作成功！");
}

void CSTUMFCDlg::OnBnClickedDeleteStuButton()
{
	if (isFieldManage)
	{
		OnBnClickedDeleteFieldButton();
		return;
	}

	std::vector<CString> ids = GetSelectedIds();

	if (ids.size() == 0)
	{
		warn("未选中任何学生！");
		return;
	}
	INT_PTR nResponse = notice("是否确认删除？");
	if (nResponse != IDOK)
	{
		warn("已取消！");
		return;
	}
	for (auto it = ids.begin(); it != ids.end(); ++it) {
		list.del(string(CT2A(*it)));
	}
	list.save();
	ClearAllList();
	LoadList();
	notice("操作成功！");
}

void CSTUMFCDlg::OnBnClickedQueryStuButton()
{
	if (isFieldManage)
	{
		OnBnClickedQueryFieldButton();
		return;
	}
	m_query.GetWindowTextW(query_text);
	string check = string(CT2A(query_text));
	if (need_trim(check))
	{
		string trimed = trim(check);
		m_query.SetWindowTextW(CString(trimed.c_str()));
		m_query.GetWindowTextW(query_text);
	}

	if (query_text == "")
	{
		ClearAllList();
		LoadList();
		return;
	}

	m_list.DeleteAllItems();
	
	if (std::regex_search(std::string(CT2A(query_text)), regex("^(20[0-9]{2})\\d{8}$")))
	{
		if (list.contains(string(CT2A(query_text))))
		{
			Student stu = list.get(string(CT2A(query_text)));
			m_list.InsertItem(0, query_text);
			m_list.SetItemText(0, 1, CString(stu.name.c_str()));
			m_list.SetItemText(0, 2, stu.gender == 1 ? _T("男") : _T("女"));
			m_list.SetItemText(0, 3, CString(to_string(stu.age).c_str()));
			m_list.SetItemText(0, 4, CString(stu.province.c_str()));
			m_list.SetItemText(0, 5, CString(stu.major.c_str()));
			map<string, Extend> extends = stu.elist.getData();
			int k = 6;
			for (auto jt = extends.begin(); jt != extends.end(); ++jt) {
				m_list.SetItemText(0, k, CString(jt->second.val.c_str()));
				k++;
			}
		}
		else
		{
			m_list.InsertItem(1, _T("该学号不存在！"));
		}
	}
	else
	{
		map<string, Student> data = list.getData();
		for (auto it = data.begin(); it != data.end(); ++it) {
			string id = it->first;
			Student result = it->second;
			int j = 0;
			if (containsString(result.name, string(CT2A(query_text)))) {
				m_list.InsertItem(j, CString(it->first.c_str()));
				m_list.SetItemText(j, 1, CString(it->second.name.c_str()));
				m_list.SetItemText(j, 2, it->second.gender == 1 ? _T("男") : _T("女"));
				m_list.SetItemText(j, 3, CString(to_string(it->second.age).c_str()));
				m_list.SetItemText(j, 4, CString(it->second.province.c_str()));
				m_list.SetItemText(j, 5, CString(it->second.major.c_str()));
				map<string, Extend> extends = it->second.elist.getData();
				int k = 6;
				for (auto jt = extends.begin(); jt != extends.end(); ++jt) {
					m_list.SetItemText(j, k, CString(jt->second.val.c_str()));
					k++;
				}
				j++;
			}
		}
	}
}

void CSTUMFCDlg::OnBnClickedAddFieldButton()
{
	string key = readLine("英文名");
	if (key == "cancelled")
	{
		warn("已取消！");
		return;
	}
	ExternalList elist = list.getElist();
	if (elist.contains(key)) {
		warn("键已存在，请尝试其他名称！");
		key = readLine("英文名");
		if (key == "cancelled")
		{
			warn("已取消！");
			return;
		}
	}
	string name = readLine("中文名");
	if (name == "cancelled")
	{
		warn("已取消！");
		return;
	}
	string regex = readLine("正则 * 为无限制");
	if (regex == "cancelled")
	{
		warn("已取消！");
		return;
	}
	elist.put(key, Extend(name, regex));
	list.setDefaultVal(key, name, regex);
	list.save();
	elist.save();
	ClearAllList();
	LoadListFiled();
	notice("操作成功！");
}

void CSTUMFCDlg::OnBnClickedDeleteFieldButton()
{
	std::vector<CString> keys = GetSelectedIds();

	if (keys.size() == 0)
	{
		warn("未选中任何字段！");
		return;
	}
	for (auto it = keys.begin(); it != keys.end(); ++it) {
		if (string(CT2A(*it)) == "systemFieldSelected")
		{
			warn("选中字段包含系统字段，不支持删除！");
			return;
		}
	}
	ExternalList elist = list.getElist();

	INT_PTR nResponse = notice("是否确认删除？");
	if (nResponse != IDOK)
	{
		warn("已取消！");
		return;
	}
	for (auto it = keys.begin(); it != keys.end(); ++it) {
		elist.del(string(CT2A(*it)));
		list.delVals(string(CT2A(*it)));
		elist.save();
		list.save();
	}
	ClearAllList();
	LoadListFiled();
	notice("操作成功！");
}

void CSTUMFCDlg::OnBnClickedEditFieldButton()
{
	ExternalList elist = list.getElist();
	std::vector<CString> keys = GetSelectedIds();

	if (keys.size() > 1)
	{
		warn("请不要多选！");
		return;
	}

	if (keys.size() == 0)
	{
		warn("未选中任何字段！");
		return;
	}

	string key = GetSelectedId();

	if (key == "systemFieldSelected")
	{
		warn("系统字段，不支持修改！");
		return;
	}
	Extend ext = elist.get(key);
	string name = readLineDef("中文名", ext.name);
	if (name == "cancelled")
	{
		warn("已取消！");
		return;
	}
	string regex = readLineDef("正则 * 为无限制", ext.regex);
	if (regex == "cancelled")
	{
		warn("已取消！");
		return;
	}
	elist.put(key, Extend(name, regex));
	elist.save();
	ClearAllList();
	LoadListFiled();
	notice("操作成功！");
}

void CSTUMFCDlg::OnBnClickedShowFieldButton()
{
	if (!isFieldManage)
	{
		ClearAllList();
		LoadListFiled();

		isFieldManage = true;
		m_query.SendMessage(EM_SETCUEBANNER, TRUE, (LPARAM)(LPCTSTR)_T("新增字段名称(Q)"));
	}
	else
	{
		ClearAllList();
		LoadList();
		isFieldManage = false;
		m_query.SendMessage(EM_SETCUEBANNER, TRUE, (LPARAM)(LPCTSTR)_T("学号/姓名(Q)"));
	}
}

void CSTUMFCDlg::LoadStuHeader()
{
	m_list.InsertColumn(0, _T("学号"), 0, 150);
	m_list.InsertColumn(1, _T("姓名"), 0, 100);
	m_list.InsertColumn(2, _T("性别"), 0, 100);
	m_list.InsertColumn(3, _T("年龄"), 0, 100);
	m_list.InsertColumn(4, _T("省份"), 0, 100);
	m_list.InsertColumn(5, _T("专业"), 0, 100);
	map<string, Extend> more = list.getElist().getData();
	int i = 6;
	for (auto it = more.begin(); it != more.end(); ++it) {
		m_list.InsertColumn(i, CString(it->second.name.c_str()), 0, 100);
		i++;
	}
}

void CSTUMFCDlg::LoadList()
{
	LoadStuHeader();
	map<string, Student> students = list.getData();
	int j = 0;
	for (auto it = students.begin(); it != students.end(); ++it) {
		m_list.InsertItem(j, CString(it->first.c_str()));
		m_list.SetItemText(j, 1, CString(it->second.name.c_str()));
		m_list.SetItemText(j, 2, it->second.gender == 1 ? _T("男") : _T("女"));
		m_list.SetItemText(j, 3, CString(to_string(it->second.age).c_str()));
		m_list.SetItemText(j, 4, CString(it->second.province.c_str()));
		m_list.SetItemText(j, 5, CString(it->second.major.c_str()));
		map<string, Extend> extends = it->second.elist.getData();
		int k = 6;
		for (auto jt = extends.begin(); jt != extends.end(); ++jt) {
			m_list.SetItemText(j, k, CString(jt->second.val.c_str()));
			k++;
		}
		j++;
	}
}

void CSTUMFCDlg::ClearAllList()
{
	list.loads();
	m_list.DeleteAllItems();
	for (int i = m_list.GetHeaderCtrl()->GetItemCount() - 1; i >= 0; i--)
	{
		m_list.DeleteColumn(i);
	}
}

std::string CSTUMFCDlg::GetSelectedId()
{
	POSITION pos = m_list.GetFirstSelectedItemPosition();
	if (pos != nullptr) {
		if (isFieldManage)
		{
			int nItem = m_list.GetNextSelectedItem(pos);
			if (nItem <= 5)
			{
				return "systemFieldSelected";
			}
			return string(CT2A(m_list.GetItemText(nItem, 0)));
		}
	}
	if (pos != nullptr)
	{
		int nItem = m_list.GetNextSelectedItem(pos);
		return string(CT2A(m_list.GetItemText(nItem, 0)));
	}
	return "";
}

std::vector<CString> CSTUMFCDlg::GetSelectedIds()
{
	std::vector<CString> selectedItems;
	POSITION pos = m_list.GetFirstSelectedItemPosition();

	while (pos != nullptr)
	{
		int nSelectedRow = m_list.GetNextSelectedItem(pos);
		if (isFieldManage)
		{
			if (nSelectedRow <= 5)
			{
				selectedItems.push_back(_T("systemFieldSelected"));
				continue;
			}
		}
		CString strItemText = m_list.GetItemText(nSelectedRow, 0);
		selectedItems.push_back(strItemText);
	}

	return selectedItems;
}

void CSTUMFCDlg::LoadFieldHeader()
{
	m_list.InsertColumn(0, _T("英文名"), 0, 100);
	m_list.InsertColumn(1, _T("中文名"), 0, 100);
	m_list.InsertColumn(2, _T("正则"), 0, 200);
	m_list.InsertColumn(3, _T("备注"), 0, 200);
}

void CSTUMFCDlg::LoadListFiled()
{
	list.loads();
	LoadFieldHeader();
	map<string, Extend> fields = list.getElist().getData();

	m_list.InsertItem(0, _T("id"));
	m_list.SetItemText(0, 1, _T("学号"));
	m_list.SetItemText(0, 2, _T("^(20[0-9]{2})\\d{8}$"));
	m_list.SetItemText(0, 3, _T("系统预设字段"));

	m_list.InsertItem(0, _T("name"));
	m_list.SetItemText(0, 1, _T("姓名"));
	m_list.SetItemText(0, 2, _T("^.*$"));
	m_list.SetItemText(0, 3, _T("系统预设字段"));

	m_list.InsertItem(0, _T("gender"));
	m_list.SetItemText(0, 1, _T("性别"));
	m_list.SetItemText(0, 2, _T("^[0-2]$"));
	m_list.SetItemText(0, 3, _T("系统预设字段"));

	m_list.InsertItem(0, _T("age"));
	m_list.SetItemText(0, 1, _T("年龄"));
	m_list.SetItemText(0, 2, _T("^([1-9][0-9]{1,2})$"));
	m_list.SetItemText(0, 3, _T("系统预设字段"));

	m_list.InsertItem(0, _T("province"));
	m_list.SetItemText(0, 1, _T("省份"));
	m_list.SetItemText(0, 2, _T("^.*$"));
	m_list.SetItemText(0, 3, _T("系统预设字段"));

	m_list.InsertItem(0, _T("major"));
	m_list.SetItemText(0, 1, _T("专业"));
	m_list.SetItemText(0, 2, _T("^.*$"));
	m_list.SetItemText(0, 3, _T("系统预设字段"));

	int j = 6;
	for (auto it = fields.begin(); it != fields.end(); ++it) {
		m_list.InsertItem(j, CString(it->first.c_str()));
		m_list.SetItemText(j, 1, CString(it->second.name.c_str()));
		m_list.SetItemText(j, 2, CString(it->second.regex.c_str()));
		j++;
	}
}

void CSTUMFCDlg::OnClearButtonClicked()
{
	m_query.SetWindowTextW(_T(""));
}

void CSTUMFCDlg::OnBnClickedQueryFieldButton()
{
	m_query.GetWindowTextW(query_text);
	string check = string(CT2A(query_text));
	if (need_trim(check))
	{
		string trimed = trim(check);
		m_query.SetWindowTextW(CString(trimed.c_str()));
		m_query.GetWindowTextW(query_text);
	}

	if (query_text == "")
	{
		ClearAllList();
		LoadListFiled();
		return;
	}

	m_list.DeleteAllItems();
	ExternalList elist = list.getElist();
	
	map<string, Extend> data = elist.getData();
	for (auto it = data.begin(); it != data.end(); ++it) {
		string id = it->first;
		Extend result = it->second;
		int j = 0;
		if (containsString(result.name, string(CT2A(query_text)))) {
			m_list.InsertItem(j, CString(id.c_str()));
			m_list.SetItemText(j, 1, CString(result.name.c_str()));
			m_list.SetItemText(j, 2, CString(result.regex.c_str()));
		}
		j++;
	}
}

void CSTUMFCDlg::OnItemDoubleClick(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMITEMACTIVATE* pNMIA = reinterpret_cast<NMITEMACTIVATE*>(pNMHDR);

	if (pNMIA->hdr.code == NM_DBLCLK)
	{
		int nItem = pNMIA->iItem;
		string first = string(CT2A(m_list.GetItemText(nItem, 0)));

		if (isFieldManage)
		{
			OnBnClickedEditFieldButton();
			return;
		}
		OnBnClickedEditStuButton();
	}

	*pResult = 0;
}
