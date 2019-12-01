#pragma once


// PrespectiveParametersDialog dialog

class PrespectiveParametersDialog : public CDialogEx
{
	DECLARE_DYNAMIC(PrespectiveParametersDialog)

public:
	PrespectiveParametersDialog(CWnd* pParent = nullptr);   // standard constructor
	virtual ~PrespectiveParametersDialog();
	double getAlpha();
	double getD();


// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	double alpha;
	double d;
};
