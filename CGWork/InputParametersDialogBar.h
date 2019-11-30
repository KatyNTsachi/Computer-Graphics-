#pragma once


// InputParametersDialogBar dialog

class InputParametersDialogBar : public CDialogEx
{
	DECLARE_DYNAMIC(InputParametersDialogBar)

public:
	InputParametersDialogBar(CWnd* pParent = nullptr);   // standard constructor
	virtual ~InputParametersDialogBar();
	int getNumber();
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	int num_of_polygons;

	DECLARE_MESSAGE_MAP()
};
