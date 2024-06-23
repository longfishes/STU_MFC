#include "INPUT_LINE.h"
#include "WarnDlg.h"
#include "NoticeDlg.h"

std::string trim(const std::string& str)
{
	size_t first = str.find_first_not_of(' ');
	if (first == std::string::npos) {
		return "";
	}
	size_t last = str.find_last_not_of(' ');
	return str.substr(first, last - first + 1);
}

bool need_trim(const std::string& str)
{
	if (str.empty())
	{
		return false;
	}
	if (std::isspace(static_cast<unsigned char>(str.front())))
	{
		return true;
	}
	if (std::isspace(static_cast<unsigned char>(str.back())))
	{
		return true;
	}
	return false;
}

INT_PTR notice(std::string text)
{
	NoticeDlg dlg;
	dlg.text_var = text.c_str();
	return dlg.DoModal();
}

void warn(std::string text)
{
	WarnDlg dlg;
	dlg.text_var = text.c_str();
	dlg.DoModal();
}

string readLine(std::string notice)
{
	INPUT_LINE dlg;
	dlg.SetStaticText(CString(notice.c_str()));
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse != IDOK)
	{
		return "cancelled";
	}
	while (dlg.value == "")
	{
		warn("输入不能为空！");
		nResponse = dlg.DoModal();
		if (nResponse != IDOK)
		{
			return "cancelled";
		}
	}
	return string(CT2A(dlg.value));
}

string readLineDef(std::string notice, std::string defaultValue)
{
	INPUT_LINE dlg;
	dlg.text_var = notice.c_str();
	dlg.value = CString(defaultValue.c_str());
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse != IDOK)
	{
		return "cancelled";
	}
	if (dlg.value == "") {
		return defaultValue;
	}
	return string(CT2A(dlg.value));
}

string readLineValid(std::string notice, std::string regex)
{
	INPUT_LINE dlg;
	dlg.text_var = notice.c_str();
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse != IDOK)
	{
		return "cancelled";
	}
	while (!std::regex_search(std::string(CT2A(dlg.value)), std::regex(regex)))
	{
		warn("输入不合法！");
		dlg.value = "";
		INT_PTR nResponse = dlg.DoModal();
		if (nResponse != IDOK)
		{
			return "cancelled";
		}
	}
	return string(CT2A(dlg.value));
}

string readLineValid(std::string notice, std::string regex, std::string defaultValue)
{
	INPUT_LINE dlg;
	dlg.value = CString(defaultValue.c_str());
	dlg.text_var = notice.c_str();
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse != IDOK)
	{
		return "cancelled";
	}
	if (dlg.value == "") {
		return defaultValue;
	}
	std::regex pattern(regex);
	while (!std::regex_search(std::string(CT2A(dlg.value)), pattern)) {
		warn("输入不合法！");
		dlg.value = "";
		INT_PTR nResponse = dlg.DoModal();
		if (nResponse != IDOK)
		{
			return "cancelled";
		}
	}
	return string(CT2A(dlg.value));
}