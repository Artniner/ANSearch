
// ANSearchDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ANSearch.h"
#include "ANSearchDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CANSearchDlg �Ի���
CANSearchDlg::CANSearchDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ANSEARCH_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CANSearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_RESULT, list_result);
	DDX_Control(pDX, IDC_SEARCH, edit_input);
}

// CANSearchDlg ��Ϣ�������
BEGIN_MESSAGE_MAP(CANSearchDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_USER_NOTIFYICON, OnNotifyMsg)
	ON_EN_CHANGE(IDC_SEARCH, &CANSearchDlg::OnEnChangeSearch)
END_MESSAGE_MAP()

BOOL CANSearchDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// ���ڴ�С
	SetWindowPos(NULL, 0, 0, window_width, window_height, SWP_ASYNCWINDOWPOS);
	list_result.SetWindowPos(NULL, 0, 0, window_width, 100, SWP_NOMOVE);
	edit_input.SetWindowPos(NULL, 0, 0, window_width, window_height, SWP_NOMOVE);	//���һ���������ԵĻ��ý���

	GetLocalTime(&last_ctrl_time);
	GetData();

	// ��������
	CFont input_font;
	input_font.CreatePointFont(160, L"Consolas");
	edit_input.SetFont(&input_font);

	// ��������
	m_nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
	m_nid.hWnd = this->m_hWnd;
	m_nid.uID = IDR_MAINFRAME;
	m_nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	m_nid.uCallbackMessage = WM_USER_NOTIFYICON ;             // �Զ������Ϣ����
	m_nid.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	Shell_NotifyIcon(NIM_ADD, &m_nid);                // �����������ͼ��

	// ȫ���ȼ�
	::RegisterHotKey(GetSafeHwnd(), IDH_HOTKEY_1, MOD_CONTROL, NULL);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CANSearchDlg::OnPaint()
{
	// ������С��
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������
		CRgn crgn;

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		// ���ñ���
		CPaintDC dc(this);
		CRect rect;
		GetClientRect(&rect);
		dc.FillSolidRect(rect, RGB(255, 255, 255));
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CANSearchDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// ����ͼ����Ϊ
LRESULT CANSearchDlg::OnNotifyMsg(WPARAM wParam, LPARAM lParam)
{
	if (wParam != IDR_MAINFRAME) return 1;

	switch (lParam)
	{
	case WM_RBUTTONUP: //�Ҽ�����ʱ������ݲ˵�������ֻ��һ�����رա�   
	{	// �������������Ĵ��󣬿�����case�¼�{}
		LPPOINT lpoint = new    tagPOINT;
		::GetCursorPos(lpoint);//�õ����λ��   
		CMenu menu;
		menu.CreatePopupMenu();//����һ������ʽ�˵������Ӳ˵���رա������������ϢWM_DESTROY�������ڣ������أ��������������   
		menu.AppendMenu(MF_STRING, WM_DESTROY, _T("�˳�"));
		//ȷ������ʽ�˵���λ��   
		menu.TrackPopupMenu(TPM_LEFTALIGN, lpoint->x, lpoint->y, this);
		//��Դ����   
		HMENU hmenu = menu.Detach();
		menu.DestroyMenu();
		delete lpoint;
		break;
	}
	case WM_LBUTTONDBLCLK://˫������Ĵ���   
		this->ShowWindow(SW_SHOW);//�򵥵���ʾ���������¶�   
		break;
	}
	return 0;
}

// �����¼�
BOOL CANSearchDlg::PreTranslateMessage(MSG* pMsg)
{
	// ��ͨ����
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_RETURN:
			DoSearch();
			return TRUE;

		case VK_ESCAPE:
			ShowWindow(SW_HIDE); // ����С��ʱ������������              
			return TRUE;	// break���ܽض�esc���˳����ܣ�Ҫ��return

		case VK_DOWN:
			list_result.SetFocus();
			break;
		}
	}

	// ȫ���ȼ�
	if (pMsg->message == WM_HOTKEY) {
		switch (pMsg->wParam)
		{
		case IDH_HOTKEY_1:
			SYSTEMTIME sys;
			GetLocalTime(&sys);
			if (sys.wYear - last_ctrl_time.wYear == 0
				&& sys.wMonth - last_ctrl_time.wMonth == 0
				&& sys.wDay - last_ctrl_time.wDay == 0
				&& sys.wHour - last_ctrl_time.wHour == 0
				&& sys.wMinute - last_ctrl_time.wMinute == 0
				&& sys.wSecond - last_ctrl_time.wSecond == 0
				&& sys.wMilliseconds - last_ctrl_time.wMilliseconds < 400) {

				SetFocus();
				edit_input.SetFocus();
				edit_input.SetSel(0, -1); //ȫѡ
				ShowWindow(SW_SHOW);
				SetForegroundWindow();
				//SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
			}
			GetLocalTime(&last_ctrl_time);
			break;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

// ��������ݱ仯
void CANSearchDlg::OnEnChangeSearch()
{
	CString search_input;
	edit_input.GetWindowTextW(search_input);

	list_result.ResetContent();

	if (search_input.IsEmpty()) {
		SetWindowPos(NULL, 0, 0, window_width, window_height, SWP_NOMOVE | SWP_ASYNCWINDOWPOS);
		return;
	}

	// ����ת��
	if ((search_input[0] == 'b' || search_input[0] == 'o' || search_input[0] == 'd' || search_input[0] == 'x')) {
		string input_num;
		input_num = CT2A(search_input.Mid(1).GetString()); //cstringתstring

		int from = 0;
		switch (search_input[0]) {
		case 'b':
			from = 2;
			break;
		case 'o':
			from = 8;
			break;
		case 'd':
			from = 10;
			break;
		case 'x':
			from = 16;
			break;
		}
	
		AddResult(_T(" BIN: "), NumTransform(from, 2, input_num));
		AddResult(_T(" OCT: "), NumTransform(from, 8, input_num));
		AddResult(_T(" DEC: "), NumTransform(from, 10, input_num));
		AddResult(_T(" HEX: "), NumTransform(from, 16, input_num));
	}

	// ����Զ����б�
	for (int i = 0; i < key_wd.size(); ++i) {
		if (search_input.Left(3) == key_wd[i].Left(3)) {
			AddResult(_T(" ") + key_wd[i]+_T(": "), search_input.Mid(3).Trim(), 0);
		}
		else {
			AddResult(_T(" ") + key_wd[i] + _T(": "), search_input.Trim());
		}
	}

	// ��ʾ���
	if (list_result.GetCount() > 0) {
		int item_height = list_result.GetItemHeight(0);
		int item_count = list_result.GetCount();
		int list_height = item_count * item_height;
		list_result.SetWindowPos(NULL, 0, 0, window_width, list_height, SWP_NOMOVE);
		list_result.SetCurSel(0);
		SetWindowPos(NULL, 0, 0, window_width, window_height+list_height+5, SWP_NOMOVE | SWP_ASYNCWINDOWPOS);
	}
	else {
		SetWindowPos(NULL, 0, 0, window_width, window_height, SWP_NOMOVE | SWP_ASYNCWINDOWPOS);
	}
}

// ����ת��
CString CANSearchDlg::NumTransform(int from, int to, string num) {
	char res_char[64] = "";
	char* err_str;
	__int64 dec;

	// ת������
	dec = _strtoi64(num.c_str(), &err_str, from);
	_i64toa_s(dec, res_char, 64, to);

	// ת�������ؿգ�����ӵ��б�
	if (strlen(err_str)) {
		return _T("");
	}

	// ���������ʽ
	CString res(res_char);
	switch (to)
	{
	case 2:
		InsertChar(4, res, ' ');
		break;
	case 8:
		InsertChar(3, res, ' ');
		break;
	case 10:
		InsertChar(3, res, ',');
		break;
	case 16:
		InsertChar(4, res, ' ');
		break;
	}
	res.MakeUpper();
	return res;
}

// �����ַ�����ʽ��
int CANSearchDlg::InsertChar(int step, CString &str, const char c) {
	int ret = 0;
	int len = str.GetLength();

	for (int i = 1; ;++i) {
		int back_pos = i * step;
		int front_pos = len - back_pos;
		if (front_pos <= 0) return ret;

		str.Insert(front_pos, c);
	}

	return ret;
}

// ����
int CANSearchDlg::DoSearch()
{
	int ret = 0;
	CString result;
	CString	key_wd_t;
	CString input_t;

	list_result.GetText(list_result.GetCurSel(), result);
	AfxExtractSubString(key_wd_t, (LPCTSTR)result, 0, ':');
	AfxExtractSubString(input_t, (LPCTSTR)result, 1, ':');

	CString url_t = url[key_wd_t.Trim()] + input_t.Trim();
	ShellExecute(0, NULL, url_t, NULL, NULL, SW_SHOWDEFAULT);

	return ret;
}

// ����б�
int CANSearchDlg::AddResult(CString describe, CString result, int pos) {
	int ret = 0;

	// ����ת���������
	if (result == "") {
		return ret;
	}

	result = describe + result;
	if (pos == 255) {
		list_result.AddString(result);
	}
	else {
		list_result.InsertString(pos, result);
	}

	return ret;
}

int CANSearchDlg::GetData()
{
	int ret = 0;
	CStdioFile file;
	CString file_name = _T("SearchList.txt");
	CString str_line;

	if (!file.Open(file_name, CFile::modeRead)) {
		MessageBox(_T("�޷����ļ�"));
		exit(0);
	}

	for (int i = 0; file.ReadString(str_line); ++i) {
		CString key_wd_t;
		CString url_t;
		AfxExtractSubString(key_wd_t, (LPCTSTR)str_line, 0, '#');
		AfxExtractSubString(url_t, (LPCTSTR)str_line, 1, '#');
		key_wd.push_back(key_wd_t);
		url[key_wd[i]] = url_t;
	}

	file.Close();
	return ret;
}


BOOL CANSearchDlg::DestroyWindow()
{
	::UnregisterHotKey(GetSafeHwnd(), IDH_HOTKEY_1);
	Shell_NotifyIcon(NIM_DELETE, &m_nid);
	return CDialogEx::DestroyWindow();
}
