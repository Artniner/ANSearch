
// ANSearchDlg.h : ͷ�ļ�
//

#pragma once

#include <string>
#include <vector>
#include <map>
#include "afxwin.h"
using namespace std;

#define WM_USER_NOTIFYICON WM_USER+1
#define IDH_HOTKEY_1 4001
// CANSearchDlg �Ի���
class CANSearchDlg : public CDialogEx
{
// ����
public:
	CANSearchDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ANSEARCH_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

private:
	CString NumTransform(int from, int to, string num);
	int InsertChar(int step, CString &str, char c);
	int DoSearch();
	int AddResult(CString describe, CString result, int pos = 255);
	int GetData();

private:
	int window_width = 500;
	int window_height = 40;
	vector<CString> key_wd;
	map<CString, CString> url;
	SYSTEMTIME last_ctrl_time;
	NOTIFYICONDATA m_nid;
	afx_msg LRESULT OnNotifyMsg(WPARAM wParam, LPARAM lParam);

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	virtual BOOL DestroyWindow();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeSearch();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CListBox list_result;
	CEdit edit_input;
};
