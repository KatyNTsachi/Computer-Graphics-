#pragma once


// MouseSensitivity dialog

class MouseSensitivity : public CDialogEx
{
	DECLARE_DYNAMIC(MouseSensitivity)

public:
	MouseSensitivity(CWnd* pParent = nullptr);   // standard constructor
	virtual ~MouseSensitivity();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MOUSE_SENSITIVITY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	double sensitivity_scalar = 1;
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

	double getSensitivityScalar();

};
