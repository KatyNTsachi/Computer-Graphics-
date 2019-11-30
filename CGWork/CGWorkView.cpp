// CGWorkView.cpp : implementation of the CCGWorkView class
//
#include "stdafx.h"
#include "CGWork.h"

#include "CGWorkDoc.h"
#include "CGWorkView.h"

#include <iostream>
using std::cout;
using std::endl;
#include "MaterialDlg.h"
#include "LightDialog.h"
#include "Model.h"
#include "Transformations.h"
#include <math.h>
#include "MouseSensitivity.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#include "PngWrapper.h"
#include "iritSkel.h"

#include <sstream>
#include <iostream>
#include <string.h>

// For Status Bar access
#include "MainFrm.h"

// Use this macro to display text messages in the status bar.
#define STATUS_BAR_TEXT(str) (((CMainFrame*)GetParentFrame())->getStatusBar().SetWindowText(str))

/////////////////////////////////////////////////////////////////////////////
// CCGWorkView

IMPLEMENT_DYNCREATE(CCGWorkView, CView)

BEGIN_MESSAGE_MAP(CCGWorkView, CView)
	//{{AFX_MSG_MAP(CCGWorkView)
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()

	//our buttons
	ON_COMMAND(ID_FILE_LOAD, OnFileLoad)
	ON_COMMAND(ID_VIEW_ORTHOGRAPHIC, OnViewOrthographic)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ORTHOGRAPHIC, OnUpdateViewOrthographic)
	ON_COMMAND(ID_VIEW_PERSPECTIVE, OnViewPerspective)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PERSPECTIVE, OnUpdateViewPerspective)
	ON_COMMAND(ID_ACTION_ROTATE, OnActionRotate)
	ON_UPDATE_COMMAND_UI(ID_ACTION_ROTATE, OnUpdateActionRotate)
	ON_COMMAND(ID_ACTION_SCALE, OnActionScale)
	ON_UPDATE_COMMAND_UI(ID_ACTION_SCALE, OnUpdateActionScale)
	ON_COMMAND(ID_ACTION_SCALE_ALL, OnActionScaleAll)
	ON_UPDATE_COMMAND_UI(ID_ACTION_SCALE_ALL, OnUpdateActionScaleAll)
	ON_COMMAND(ID_ACTION_TRANSLATE, OnActionTranslate)
	ON_UPDATE_COMMAND_UI(ID_ACTION_TRANSLATE, OnUpdateActionTranslate)
	ON_COMMAND(ID_AXIS_X, OnAxisX)
	ON_UPDATE_COMMAND_UI(ID_AXIS_X, OnUpdateAxisX)
	ON_COMMAND(ID_AXIS_Y, OnAxisY)
	ON_UPDATE_COMMAND_UI(ID_AXIS_Y, OnUpdateAxisY)
	ON_COMMAND(ID_AXIS_Z, OnAxisZ)
	ON_UPDATE_COMMAND_UI(ID_AXIS_Z, OnUpdateAxisZ)
	ON_COMMAND(ID_LIGHT_SHADING_FLAT, OnLightShadingFlat)
	ON_UPDATE_COMMAND_UI(ID_LIGHT_SHADING_FLAT, OnUpdateLightShadingFlat)
	ON_COMMAND(ID_LIGHT_SHADING_GOURAUD, OnLightShadingGouraud)
	ON_UPDATE_COMMAND_UI(ID_LIGHT_SHADING_GOURAUD, OnUpdateLightShadingGouraud)
	ON_COMMAND(ID_LIGHT_CONSTANTS, OnLightConstants)
	ON_COMMAND(ID_ACTION_TRANSITIONS_MODEL, OnModelTranslations)
	ON_UPDATE_COMMAND_UI(ID_ACTION_TRANSITIONS_MODEL, OnUpdateModelTranslations)
	ON_COMMAND(ID_ACTION_TRANSITIONS_VIEW_SPACE, OnCameraTranslations)
	ON_UPDATE_COMMAND_UI(ID_ACTION_TRANSITIONS_VIEW_SPACE, OnUpdateOnCameraTranslations)
	ON_COMMAND(IDD_MOUSE_SENSITIVITY, OnAppMouseSensitivity)
	ON_COMMAND(ID_BOUNDING_BOX, OnAppBoundingBox)
	ON_UPDATE_COMMAND_UI(ID_BOUNDING_BOX, OnUpdateBoundingBox)
	ON_COMMAND(ID_COLOR_MODELCOLOR, &CCGWorkView::OnModelColerPicker)
	ON_COMMAND(ID_COLOR_BOUNDINGBOXCOLOR, &CCGWorkView::OnColorBoundingboxcolor)
	ON_COMMAND(ID_COLOR_NORMALSCOLOR, &CCGWorkView::OnColorNormalscolor)
	ON_COMMAND(ID_OPTIONS_SHOWVERTEXNORMALS, &CCGWorkView::OnOptionsShowVertexNormals)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_SHOWVERTEXNORMALS, &CCGWorkView::OnUpdateOptionsShowVertexNormals)
	ON_COMMAND(ID_OPTIONS_SHOWPOLYGONNORMALS, &CCGWorkView::OnOptionsShowPolygonNormals)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_SHOWPOLYGONNORMALS, &CCGWorkView::OnUpdateOptionsShowPolygonNormals)

	//}}AFX_MSG_MAP
	ON_WM_TIMER()
END_MESSAGE_MAP()

// A patch to fix GLaux disappearance from VS2005 to VS2008
void auxSolidCone(GLdouble radius, GLdouble height) {
        GLUquadric *quad = gluNewQuadric();
        gluQuadricDrawStyle(quad, GLU_FILL);
        gluCylinder(quad, radius, 0.0, height, 20, 20);
        gluDeleteQuadric(quad);
}

/////////////////////////////////////////////////////////////////////////////
// CCGWorkView construction/destruction

CCGWorkView::CCGWorkView()
{
	// Set default values
	m_nAxis = ID_AXIS_X;
	m_nAction = ID_ACTION_ROTATE;
	m_nView = ID_VIEW_ORTHOGRAPHIC;	
	m_translations_object = ID_ACTION_TRANSITIONS_MODEL;
	m_show_normals = 0;
	m_show_vertex_normals = 0;
	m_show_polygon_normals = 0;

	m_bIsPerspective = false;

	m_nLightShading = ID_LIGHT_SHADING_FLAT;

	m_lMaterialAmbient = 0.2;
	m_lMaterialDiffuse = 0.8;
	m_lMaterialSpecular = 1.0;
	m_nMaterialCosineFactor = 32;

	//init the first light to be enabled
	m_lights[LIGHT_ID_1].enabled=true;
	m_pDbBitMap = NULL;
	m_pDbDC = NULL;

	//add camera
	Camera camera;
	scene.AddCamera(camera);
	show_bounding_box = 0;

}

CCGWorkView::~CCGWorkView()
{
}


/////////////////////////////////////////////////////////////////////////////
// CCGWorkView diagnostics

#ifdef _DEBUG
void CCGWorkView::AssertValid() const
{
	CView::AssertValid();
}

void CCGWorkView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCGWorkDoc* CCGWorkView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCGWorkDoc)));
	return (CCGWorkDoc*)m_pDocument;
}
#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////
// CCGWorkView Window Creation - Linkage of windows to CGWork

BOOL CCGWorkView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	// An CGWork window must be created with the following
	// flags and must NOT include CS_PARENTDC for the
	// class style.

	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	return CView::PreCreateWindow(cs);
}



int CCGWorkView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	InitializeCGWork();

	return 0;
}


// This method initialized the CGWork system.
BOOL CCGWorkView::InitializeCGWork()
{
	m_pDC = new CClientDC(this);
	
	if ( NULL == m_pDC ) { // failure to get DC
		::AfxMessageBox(CString("Couldn't get a valid DC."));
		return FALSE;
	}

	CRect r;
	GetClientRect(&r);
	m_pDbDC = new CDC();
	m_pDbDC->CreateCompatibleDC(m_pDC);
	SetTimer(1, 1, NULL);
	m_pDbBitMap = CreateCompatibleBitmap(m_pDC->m_hDC, r.right, r.bottom);	
	m_pDbDC->SelectObject(m_pDbBitMap);
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CCGWorkView message handlers

void CCGWorkView::OnModelColerPicker() {
	CColorDialog colorDialog;
	if (colorDialog.DoModal() == IDOK) {
		scene.setModelColor(colorDialog.GetColor());
		RedrawWindow();
	}
}

void CCGWorkView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);

	if ( 0 >= cx || 0 >= cy ) {
		return;
	}

	// save the width and height of the current window
	m_WindowWidth = cx;
	m_WindowHeight = cy;

	// compute the aspect ratio
	// this will keep all dimension scales equal
	m_AspectRatio = (GLdouble)m_WindowWidth/(GLdouble)m_WindowHeight;

	CRect r;
	GetClientRect(&r);
	DeleteObject(m_pDbBitMap);
	m_pDbBitMap = CreateCompatibleBitmap(m_pDC->m_hDC, r.right, r.bottom);	
	m_pDbDC->SelectObject(m_pDbBitMap);
}


BOOL CCGWorkView::SetupViewingFrustum(void)
{
    return TRUE;
}


// This viewing projection gives us a constant aspect ration. This is done by
// increasing the corresponding size of the ortho cube.
BOOL CCGWorkView::SetupViewingOrthoConstAspect(void)
{
	return TRUE;
}





BOOL CCGWorkView::OnEraseBkgnd(CDC* pDC) 
{
	// Windows will clear the window with the background color every time your window 
	// is redrawn, and then CGWork will clear the viewport with its own background color.

	
	return true;
}



/////////////////////////////////////////////////////////////////////////////
// CCGWorkView drawing
/////////////////////////////////////////////////////////////////////////////

void CCGWorkView::OnDraw(CDC* pDC)
{
	CCGWorkDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CDC *pDCToUse = m_pDbDC;

	CRect r;
	GetClientRect(&r);
	pDC->FillSolidRect(&r, RGB(255, 255, 255));
	int height = r.Height();
	int width = r.Width();
	int* view_mat = new int[height*width];

	scene.Draw(pDC, 0, r, view_mat);

	pDCToUse->GetCurrentBitmap()->SetBitmapBits(width * height * 4, view_mat);
	if (pDCToUse != pDC)
	{
		pDC->BitBlt(r.left, r.top, r.Width(), r.Height(), pDCToUse, r.left, r.top, SRCCOPY);
	}

	delete[] view_mat;

}


/////////////////////////////////////////////////////////////////////////////
// CCGWorkView CGWork Finishing and clearing...

void CCGWorkView::OnDestroy() 
{
	CView::OnDestroy();

	// delete the DC
	if ( m_pDC ) {
		delete m_pDC;
	}

	if (m_pDbDC) {
		delete m_pDbDC;
	}
}



/////////////////////////////////////////////////////////////////////////////
// User Defined Functions

void CCGWorkView::RenderScene() {
	// do nothing. This is supposed to be overriden...

	return;
}


void CCGWorkView::OnFileLoad() 
{
	TCHAR szFilters[] = _T ("IRIT Data Files (*.itd)|*.itd|All Files (*.*)|*.*||");

	CFileDialog dlg(TRUE, _T("itd"), _T("*.itd"), OFN_FILEMUSTEXIST | OFN_HIDEREADONLY ,szFilters);

	if (dlg.DoModal () == IDOK) {
		m_strItdFileName = dlg.GetPathName();		// Full path and filename
		PngWrapper p;
		CGSkelProcessIritDataFiles(m_strItdFileName, 1);
		// Open the file and read it.
		// Your code here...

		Model tmp_model = model;
		scene.addModel(tmp_model);
		model = Model();

		RedrawWindow();
	} 
}


// VIEW HANDLERS ///////////////////////////////////////////

// Note: that all the following Message Handlers act in a similar way.
// Each control or command has two functions associated with it.

void CCGWorkView::OnViewOrthographic() 
{
	m_nView = ID_VIEW_ORTHOGRAPHIC;
	m_bIsPerspective = false;
	RedrawWindow();		// redraw using the new view.
}

void CCGWorkView::OnUpdateViewOrthographic(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_nView == ID_VIEW_ORTHOGRAPHIC);
}

void CCGWorkView::OnViewPerspective() 
{
	m_nView = ID_VIEW_PERSPECTIVE;
	m_bIsPerspective = true;
	RedrawWindow();
}

void CCGWorkView::OnUpdateViewPerspective(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_nView == ID_VIEW_PERSPECTIVE);
}

// ACTION HANDLERS ///////////////////////////////////////////

void CCGWorkView::OnActionRotate() 
{
	m_nAction = ID_ACTION_ROTATE;
}

void CCGWorkView::OnUpdateActionRotate(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_nAction == ID_ACTION_ROTATE);
}

void CCGWorkView::OnActionTranslate() 
{
	m_nAction = ID_ACTION_TRANSLATE;
}

void CCGWorkView::OnUpdateActionTranslate(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_nAction == ID_ACTION_TRANSLATE);
}

void CCGWorkView::OnActionScale() 
{
	m_nAction = ID_ACTION_SCALE;
}

void CCGWorkView::OnUpdateActionScale(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_nAction == ID_ACTION_SCALE);
}

void CCGWorkView::OnActionScaleAll()
{
	m_nAction = ID_ACTION_SCALE_ALL;
}

void CCGWorkView::OnUpdateActionScaleAll(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_nAction == ID_ACTION_SCALE_ALL);
}


// AXIS HANDLERS ///////////////////////////////////////////


// Gets calles when the X button is pressed or when the Axis->X menu is selected.
// The only thing we do here is set the ChildView member variable m_nAxis to the 
// selected axis.
void CCGWorkView::OnAxisX() 
{
	m_nAxis = ID_AXIS_X;
}

// Gets called when windows has to repaint either the X button or the Axis pop up menu.
// The control is responsible for its redrawing.
// It sets itself disabled when the action is a Scale action.
// It sets itself Checked if the current axis is the X axis.
void CCGWorkView::OnUpdateAxisX(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_nAxis == ID_AXIS_X);
}

void CCGWorkView::OnAxisY() 
{
	m_nAxis = ID_AXIS_Y;
}

void CCGWorkView::OnUpdateAxisY(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_nAxis == ID_AXIS_Y);
}

void CCGWorkView::OnAxisZ() 
{
	m_nAxis = ID_AXIS_Z;
}

void CCGWorkView::OnUpdateAxisZ(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_nAxis == ID_AXIS_Z);
}




// OPTIONS HANDLERS ///////////////////////////////////////////
// LIGHT SHADING HANDLERS ///////////////////////////////////////////

void CCGWorkView::OnLightShadingFlat() 
{
	m_nLightShading = ID_LIGHT_SHADING_FLAT;
}

void CCGWorkView::OnUpdateLightShadingFlat(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_nLightShading == ID_LIGHT_SHADING_FLAT);
}


void CCGWorkView::OnLightShadingGouraud() 
{
	m_nLightShading = ID_LIGHT_SHADING_GOURAUD;
}

void CCGWorkView::OnUpdateLightShadingGouraud(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_nLightShading == ID_LIGHT_SHADING_GOURAUD);
}

// LIGHT SETUP HANDLER ///////////////////////////////////////////

void CCGWorkView::OnLightConstants() 
{
	CLightDialog dlg;

	for (int id=LIGHT_ID_1;id<MAX_LIGHT;id++)
	{	    
	    dlg.SetDialogData((LightID)id,m_lights[id]);
	}
	dlg.SetDialogData(LIGHT_ID_AMBIENT,m_ambientLight);

	if (dlg.DoModal() == IDOK) 
	{
	    for (int id=LIGHT_ID_1;id<MAX_LIGHT;id++)
	    {
		m_lights[id] = dlg.GetDialogData((LightID)id);
	    }
	    m_ambientLight = dlg.GetDialogData(LIGHT_ID_AMBIENT);
	}	
	RedrawWindow();
}

void CCGWorkView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	CView::OnTimer(nIDEvent);
	//if (nIDEvent == 1)
}

void CCGWorkView::updateTransformationMatrices(double mouseDraggingDistance)
{
	Matrix transformationMatrix;

	// Rotation
	if (m_nAction == ID_ACTION_ROTATE)
	{
		transformationMatrix = Transformations::rotation(M_PI * (mouseDraggingDistance / m_WindowWidth), m_nAxis);
	}
	
	// Translation
	else if (m_nAction == ID_ACTION_TRANSLATE)
	{
		transformationMatrix = Transformations::translation(	(mouseDraggingDistance / m_WindowWidth) * (m_nAxis == ID_AXIS_X),
																(mouseDraggingDistance / m_WindowWidth) * (m_nAxis == ID_AXIS_Y),
																(mouseDraggingDistance / m_WindowWidth) * (m_nAxis == ID_AXIS_Z));
	}	

	// Scale
	else if (m_nAction == ID_ACTION_SCALE)
	{
		double factor;
		if (mouseDraggingDistance > 0)
			factor = 1 / ((m_WindowWidth - mouseDraggingDistance) / m_WindowWidth);
		else
			factor = ((m_WindowWidth + mouseDraggingDistance) / m_WindowWidth);
		
		double x = 1;
		double y = 1;
		double z = 1;
		if (m_nAxis == ID_AXIS_X)
			x = factor;
		else if (m_nAxis == ID_AXIS_Y)
			y = factor;
		else if (m_nAxis == ID_AXIS_Z)
			z = factor;

		transformationMatrix = Transformations::scale(x, y, z);
	}

	// Uniform scale
	else if (m_nAction == ID_ACTION_SCALE_ALL)
	{
		double factor;

		if (mouseDraggingDistance > 0)
			factor = 1 / ((m_WindowWidth - mouseDraggingDistance) / m_WindowWidth);
		else
			factor = ((m_WindowWidth + mouseDraggingDistance) / m_WindowWidth);

		transformationMatrix = Transformations::scale(	factor, factor, factor);
	}
	if (m_translations_object == ID_ACTION_TRANSITIONS_MODEL)
		scene.updateTransformationObjectSpaceMatricesOfAllObjects(transformationMatrix);
	else
		scene.updateTransformationViewSpaceMatricesOfAllObjects(transformationMatrix);
	

	//RedrawWindow();	// force a WM_PAINT for drawing.;
}

BOOL CCGWorkView::PreTranslateMessage(MSG * pMsg)
{
	int X = (int)pMsg->wParam;
	if (pMsg->message == WM_LBUTTONDOWN)
	{
		DWORD tempCoords = GetMessagePos();

		x_mouse_coordinate = GET_X_LPARAM(tempCoords);
		y_mouse_coordinate = GET_Y_LPARAM(tempCoords);

	}
	else if (pMsg->message == WM_LBUTTONUP)
	{
		int x_mouse_coordinate_up, y_mouse_coordinate_up;
		DWORD tempCoords = GetMessagePos();

		x_mouse_coordinate_up = GET_X_LPARAM(tempCoords);
		y_mouse_coordinate_up = GET_Y_LPARAM(tempCoords);

		//calc distance
		//double distance = sqrt( (x_mouse_coordinate - x_mouse_coordinate_up)*(x_mouse_coordinate - x_mouse_coordinate_up) + (y_mouse_coordinate - y_mouse_coordinate_up)*(y_mouse_coordinate - y_mouse_coordinate_up));
		double distance = x_mouse_coordinate_up - x_mouse_coordinate;
		
		
		updateTransformationMatrices(distance * sensitivity_scalar);
		RedrawWindow();
		//choose function
	}
	return TRUE;
}

void CCGWorkView::OnModelTranslations()
{
	m_translations_object = ID_ACTION_TRANSITIONS_MODEL;
}

void CCGWorkView::OnUpdateModelTranslations(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_translations_object == ID_ACTION_TRANSITIONS_MODEL);
}

void CCGWorkView::OnCameraTranslations()
{
	m_translations_object = ID_ACTION_TRANSITIONS_VIEW_SPACE;
}

void CCGWorkView::OnUpdateOnCameraTranslations(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_translations_object == ID_ACTION_TRANSITIONS_VIEW_SPACE);
}

void CCGWorkView::OnAppMouseSensitivity()
{
	MouseSensitivity mouse_sensitivity;
	mouse_sensitivity.DoModal();
	
	sensitivity_scalar = mouse_sensitivity.getSensitivityScalar();
}

void CCGWorkView::OnAppBoundingBox()
{
	if (show_bounding_box == ID_BOUNDING_BOX)
		show_bounding_box = 0;
	else
		show_bounding_box = ID_BOUNDING_BOX;

	scene.setSouldShowBoundingBox(show_bounding_box == ID_BOUNDING_BOX);
	RedrawWindow();
}

void CCGWorkView::OnUpdateBoundingBox(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(show_bounding_box == ID_BOUNDING_BOX);
}



void CCGWorkView::OnColorBoundingboxcolor()
{
	CColorDialog colorDialog;
	if (colorDialog.DoModal() == IDOK) {
		scene.setBoundingBoxColor(colorDialog.GetColor());
		RedrawWindow();
	}
}


void CCGWorkView::OnColorNormalscolor()
{
	CColorDialog colorDialog;
	if (colorDialog.DoModal() == IDOK) {
		scene.setNormalsColor(colorDialog.GetColor());
		RedrawWindow();
	}
}


void CCGWorkView::OnOptionsShowVertexNormals()
{
	if (m_show_vertex_normals == ID_OPTIONS_SHOWVERTEXNORMALS)
	{
		m_show_vertex_normals = 0;
	}
	else
	{
		m_show_vertex_normals = ID_OPTIONS_SHOWVERTEXNORMALS;
	}
	scene.paint_vertex_normals = !scene.paint_vertex_normals;
	RedrawWindow();
}


void CCGWorkView::OnUpdateOptionsShowVertexNormals(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_show_vertex_normals == ID_OPTIONS_SHOWVERTEXNORMALS);
}


void CCGWorkView::OnOptionsShowPolygonNormals()
{
	// TODO: Add your command handler code here
	
	if (m_show_polygon_normals == ID_OPTIONS_SHOWPOLYGONNORMALS)
	{
		m_show_polygon_normals = 0;
	}
	else
	{
		m_show_polygon_normals = ID_OPTIONS_SHOWPOLYGONNORMALS;
	}
	scene.paint_polygon_normals = !scene.paint_polygon_normals;
	RedrawWindow();
}

void CCGWorkView::OnUpdateOptionsShowPolygonNormals(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_show_polygon_normals == ID_OPTIONS_SHOWPOLYGONNORMALS);
	// TODO: Add your command update UI handler code here
}
