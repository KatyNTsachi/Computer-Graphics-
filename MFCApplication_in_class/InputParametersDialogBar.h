#pragma once


// InputParametersDialogBar dialog

class InputParametersDialogBar : public CDialog
{
	DECLARE_DYNAMIC(InputParametersDialogBar)

public:
	InputParametersDialogBar(CWnd* pParent = nullptr);   // standard constructor
	virtual ~InputParametersDialogBar();
	int a, b, s, color;
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
