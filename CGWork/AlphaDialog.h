#pragma once


// AlphaDialog dialog

class AlphaDialog : public CDialogEx
{
	DECLARE_DYNAMIC(AlphaDialog)
	double alpha = 1;

public:
	AlphaDialog(CWnd* pParent = nullptr);   // standard constructor
	virtual ~AlphaDialog();
	double getAlpha();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
};
