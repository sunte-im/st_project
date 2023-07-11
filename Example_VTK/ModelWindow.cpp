#include "ModelWindow.h"
#include "../../../CCAD/CCAD/VTK/VTKManager.h"
#include "../../../CCAD/CCAD/Polygonica/PolygonicaManager.h"

#include <QMouseEvent>
#include <qpainter.h>

#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkProperty.h>

#include <QPushButton>
#include <qpixmap.h>
#include <QLineEdit>
#include <QLabel>

#include <QComboBox>
#include <qfiledialog.h>

//#include "AxialView.h"
#include <qgridlayout.h>

ModelWindow::ModelWindow(QWidget* parent)
	: QOpenGLWidget(parent)
{
	setMouseTracking(true);


//	m_AxialView = new AxialView(this);

//	QHBoxLayout* layout = new QHBoxLayout(this);
//	layout->addWidget(m_AxialView);

//	m_AxialView->hide();
	



	m_but_right = false;
	m_but_middle = false;
	m_but_left = false;
	m_ctrl = false;
	m_alt = false;
	m_shift = false;

	m_mousePosition = QVector2D();
	m_mousePrePosition = QVector2D();
	m_mousePressPosition = QVector2D();

	QPushButton* butUpperOpen = new QPushButton(this);
	butUpperOpen->setGeometry(QRect(10, 10, 50, 20));
	butUpperOpen->setText(QStringLiteral("UPPER"));
	connect(butUpperOpen, SIGNAL(pressed()), this, SLOT(butOpenUpperSTL()));

	QPushButton* butLowerOpen = new QPushButton(this);
	butLowerOpen->setGeometry(QRect(10, 40, 50, 20));
	butLowerOpen->setText(QStringLiteral("LOWER"));
    connect(butLowerOpen, SIGNAL(pressed()), this, SLOT(butOpenLowerSTL()));

	QLabel* labelUpper = new QLabel(this);
	labelUpper->setGeometry(10, 70, 50, 20);
	labelUpper->setText("UPPER");

	sliderUpper = new QSlider(Qt::Horizontal, this);
	sliderUpper->setGeometry(60, 70, 140, 20);
	sliderUpper->setRange(0, 99);
	sliderUpper->setValue(100);

	QLabel* labelLower = new QLabel(this);
	labelLower->setGeometry(10, 100, 50, 20);
	labelLower->setText("LOWER");

	sliderLower = new QSlider(Qt::Horizontal, this);
	sliderLower->setGeometry(60, 100, 140, 20);
	sliderLower->setRange(0, 99);
	sliderLower->setValue(100);

	QLabel* labelCrown = new QLabel(this);
	labelCrown->setGeometry(10, 130, 50, 20);
	labelCrown->setText("CROWN");

	sliderCrown = new QSlider(Qt::Horizontal, this);
	sliderCrown->setGeometry(60, 130, 140, 20);
	sliderCrown->setRange(0, 99);
	sliderCrown->setValue(100);

	QLabel* labelInner = new QLabel(this);
	labelInner->setGeometry(10, 160, 50, 20);
	labelInner->setText("INNER");

	sliderInner = new QSlider(Qt::Horizontal, this);
	sliderInner->setGeometry(60, 160, 140, 20);
	sliderInner->setRange(0, 99);
	sliderInner->setValue(100);

	QObject::connect(sliderUpper, SIGNAL(valueChanged(int)), this, SLOT(valueChanged_Upper()));
	QObject::connect(sliderLower, SIGNAL(valueChanged(int)), this, SLOT(valueChanged_Lower()));
	QObject::connect(sliderCrown, SIGNAL(valueChanged(int)), this, SLOT(valueChanged_Crown()));
	QObject::connect(sliderInner, SIGNAL(valueChanged(int)), this, SLOT(valueChanged_Inner()));

	VTK_MANAGER->initVTK();
	POLYGONICA_MANAGER->initPolygonica();
}

ModelWindow::~ModelWindow()
{
	VTK_MANAGER->freeVTK();
	POLYGONICA_MANAGER->freePolygonica();

	makeCurrent();

	doneCurrent();
}

void ModelWindow::keyPressEvent(QKeyEvent* e)
{
	bool visibility = false;

	switch (e->key())
	{
	default:
		break;

	case Qt::Key_Alt:
		m_alt = true;
		break;

	case Qt::Key_Control:
		//VTK_MANAGER->createArchCenterLine();
		//VTK_MANAGER->createArchWidthLine();
		//VTK_MANAGER->createArchSegLine();

		m_ctrl = true;
		break;

	case Qt::Key_Shift:
		m_shift = true;
		break;

	case Qt::Key_Delete:
		VTK_MANAGER->deleteMarginPoint();
		POLYGONICA_MANAGER->CalcShortestPath();
		VTK_MANAGER->interpolationMarginLine();
		VTK_MANAGER->refreshMarginLine();

		VTK_MANAGER->resetClipping();

		//VTK_MANAGER->initMarginPoint();

		update();
		break;

	case Qt::Key_C:
		VTK_MANAGER->setClippingPlane();

		//VTK_MANAGER->calcCrossSectioProfile();
		break;

	case Qt::Key_D:
		VTK_MANAGER->m_bDeform = !VTK_MANAGER->m_bDeform;
		break;

	case Qt::Key_M:
		VTK_MANAGER->m_bSetMargin = !VTK_MANAGER->m_bSetMargin;
		break;

	case Qt::Key_W:
		VTK_MANAGER->m_actorUpper->GetProperty()->SetRepresentationToWireframe();
		break;

	case Qt::Key_S:
		VTK_MANAGER->m_actorUpper->GetProperty()->SetRepresentationToSurface();
		break;

	case Qt::Key_H:
		visibility = VTK_MANAGER->m_actorMarginLine->GetVisibility();

		VTK_MANAGER->m_actorMarginLine->SetVisibility(!visibility);
		VTK_MANAGER->m_actorMarginPoint->SetVisibility(!visibility);
		VTK_MANAGER->m_actorSegment->SetVisibility(!visibility);
		break;

	case Qt::Key_X:
		VTK_MANAGER->m_bScaleCrown = true;
		VTK_MANAGER->m_bScaleCrownX = true;
		VTK_MANAGER->m_bScaleCrownY = false;
		VTK_MANAGER->m_bScaleCrownZ = false;
		break;
	case Qt::Key_Y:
		VTK_MANAGER->m_bScaleCrown = true;
		VTK_MANAGER->m_bScaleCrownX = false;
		VTK_MANAGER->m_bScaleCrownY = true;
		VTK_MANAGER->m_bScaleCrownZ = false;
		break;
	case Qt::Key_Z:
		VTK_MANAGER->m_bScaleCrown = true;
		VTK_MANAGER->m_bScaleCrownX = false;
		VTK_MANAGER->m_bScaleCrownY = false;
		VTK_MANAGER->m_bScaleCrownZ = true;
		break;

	case Qt::Key_Escape:
		VTK_MANAGER->m_bScaleCrown = false;
		VTK_MANAGER->m_bScaleCrownX = false;
		VTK_MANAGER->m_bScaleCrownY = false;
		VTK_MANAGER->m_bScaleCrownZ = false;
		break;
	}

	//if (e->key() == Qt::Key_Alt)
	//	m_alt = true;
	//if (e->key() == Qt::Key_Control)
	//{
	//	//VTK_MANAGER->createArchCenterLine();
	//	//VTK_MANAGER->createArchWidthLine();
	//	//VTK_MANAGER->createArchSegLine();

	//	m_ctrl = true;
	//}
	//	
	//if (e->key() == Qt::Key_Shift)
	//	m_shift = true;
	//if (e->key() == Qt::Key_Delete)
	//{
	//	VTK_MANAGER->deleteMarginPoint();
	//	POLYGONICA_MANAGER->CalcShortestPath();
	//	VTK_MANAGER->interpolationMarginLine();
	//	VTK_MANAGER->refreshMarginLine();

	//	VTK_MANAGER->resetClipping();

	//	//VTK_MANAGER->initMarginPoint();

	//	update();
	//}

	//if (e->key() == Qt::Key_C)
	//{
	//	VTK_MANAGER->setClippingPlane();

	//	//VTK_MANAGER->calcCrossSectioProfile();
	//}

	//if (e->key() == Qt::Key_D)
	//{
	//	VTK_MANAGER->m_bDeform = !VTK_MANAGER->m_bDeform;
	//}

	//if (e->key() == Qt::Key_M)
	//{
	//	VTK_MANAGER->m_bSetMargin = !VTK_MANAGER->m_bSetMargin;
	//}

	//if (e->key() == Qt::Key_W)
	//{
	//	VTK_MANAGER->m_actorUpper->GetProperty()->SetRepresentationToWireframe();
	//}
	//if (e->key() == Qt::Key_S)
	//{
	//	VTK_MANAGER->m_actorUpper->GetProperty()->SetRepresentationToSurface();
	//}
	//if (e->key() == Qt::Key_H)
	//{
	//	bool visibility = VTK_MANAGER->m_actorMarginLine->GetVisibility();

	//	VTK_MANAGER->m_actorMarginLine->SetVisibility(!visibility);
	//	VTK_MANAGER->m_actorMarginPoint->SetVisibility(!visibility);
	//	VTK_MANAGER->m_actorSegment->SetVisibility(!visibility);
	//}

}

void ModelWindow::keyReleaseEvent(QKeyEvent* e)
{
	m_ctrl = false;
	m_alt = false;
	m_shift = false;

	switch (e->key())
	{
	case Qt::Key_Space:
		break;

	case Qt::Key_Escape:
		//VTK_MANAGER->resetObjectRotate();
		update();
		break;
	default:
		break;
	}
}


void ModelWindow::mousePressEvent(QMouseEvent* e)
{
	m_mousePosition = QVector2D(e->localPos());
	m_mousePrePosition = m_mousePosition;
	m_mousePressPosition = m_mousePosition;

	if (e->buttons() == Qt::RightButton)
	{
		m_but_right = true;
	}
	if (e->buttons() == Qt::LeftButton)
	{
		m_but_left = true;
	}
	if (e->buttons() == Qt::MidButton)
	{
		m_but_middle = true;
	}

	// work



	VTK_MANAGER->mousePressVTK(m_mousePosition, this->width(), this->height(), m_but_left, m_but_right, m_but_middle, m_ctrl, m_shift);

	update();
}



void ModelWindow::mouseMoveEvent(QMouseEvent* e)
{
	bool need_update = false;
	m_mousePosition = QVector2D(e->localPos());
	QVector2D diff = m_mousePosition - m_mousePrePosition;

	// WORK


	need_update = VTK_MANAGER->mouseMoveVTK(m_mousePrePosition, m_mousePosition, this->width(), this->height(), m_but_left, m_but_right, m_but_middle);

	if (need_update == true)
	{
		update();
	}

	m_mousePrePosition = m_mousePosition;
}


void ModelWindow::mouseReleaseEvent(QMouseEvent* e)
{
	m_mousePosition = QVector2D(e->localPos());
	m_mousePrePosition = m_mousePosition;


	// work
	if (VTK_MANAGER->mouseReleaseVTK(m_mousePosition, this->width(), this->height(), m_but_right))
	{
		update();
	}

	m_but_right = false;
	m_but_middle = false;
	m_but_left = false;
}


void ModelWindow::wheelEvent(QWheelEvent* event)
{
	VTK_MANAGER->wheelEventVTK(event->delta());

	update();
}

void ModelWindow::mouseDoubleClickEvent(QMouseEvent* e)
{
	QVector2D pos = QVector2D(e->localPos());
	VTK_MANAGER->mouseDoubleClickVTK(pos, this->width(), this->height());

	update();
}

void ModelWindow::timerEvent(QTimerEvent*)
{

}

void ModelWindow::valueChanged_Upper()
{
	slider_Upper = sliderUpper->value();

	double value = slider_Upper * 0.01f;
	if (value > 0.98) value = 1.0f;

	VTK_MANAGER->m_actorUpper->GetProperty()->SetOpacity(value);
	VTK_MANAGER->renderVTK();
}

void ModelWindow::valueChanged_Lower()
{
	slider_Lower = sliderLower->value();

	double value = slider_Lower * 0.01f;
	if (value > 0.98) value = 1.0f;

	VTK_MANAGER->m_actorLower->GetProperty()->SetOpacity(value);
	VTK_MANAGER->renderVTK();
}

void ModelWindow::valueChanged_Crown()
{
	slider_Crown = sliderCrown->value();

	double value = slider_Crown * 0.01f;
	if (value > 0.98) value = 1.0f;

	VTK_MANAGER->m_actorCrown->GetProperty()->SetOpacity(value);
	VTK_MANAGER->renderVTK();
}

void ModelWindow::valueChanged_Inner()
{
	slider_Inner = sliderInner->value();

	double value = slider_Inner * 0.01f;
	if (value > 0.98) value = 1.0f;

	VTK_MANAGER->m_actorInner->GetProperty()->SetOpacity(value);
	VTK_MANAGER->renderVTK();
}

void ModelWindow::initializeGL()
{
	initializeOpenGLFunctions();

	VTK_MANAGER->init(this);
}

void ModelWindow::resizeGL(int w, int h)
{
	VTK_MANAGER->resizeVTK(w, h);



	//QSize size = this->size();
	//m_widgetMenu->setGeometry(0, 0, 50, size.height());
}



void ModelWindow::paintGL()
{
	//int preBuffer;

	//int rgba[4];
	//m_vtkRWindow->GetColorBufferSizes(rgba);

	//glGetIntegerv(GL_FRAMEBUFFER_BINDING, &preBuffer);

	VTK_MANAGER->renderVTK();

	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	GLint currProgram;
	glGetIntegerv(GL_CURRENT_PROGRAM, &currProgram);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // For QT Painter Render

	QPainter p;
	p.begin(this);
	paintQT(&p);
	p.end();

	glUseProgram(currProgram);
}



void ModelWindow::paintQT(QPainter* p)
{
	/*p->setPen(QPen(Qt::red, 2));

	p->drawRect(10, 500, 100, 100);
*/



// Work
}

void ModelWindow::butOpenUpperSTL()
{
    //VTK_MANAGER->removeLowerSTL();
    //update();
    return;


	QString strLatest;
	int i = 0;

	const QFileDialog::Options options = QFlag(QFileDialog::ShowDirsOnly);
	QString selectedFilter;
	QString fileName = QFileDialog::getOpenFileName(this,
		QStringLiteral("UPPER STL FileOpen"),
		tr(""), 
		tr("STL File(*.stl;*.STL)"),
		&selectedFilter, 
		options); 

	if (!fileName.isEmpty())
	{
		if (VTK_MANAGER->loadUpperSTL(fileName)) update();
	}

	fileName = QFileDialog::getOpenFileName(this,
		QStringLiteral("CROWN STL FileOpen"),
		tr(""),
		tr("STL File(*.stl;*.STL)"),
		&selectedFilter,
		options);

	if (!fileName.isEmpty())
	{
		if (VTK_MANAGER->loadCrown(fileName)) update();
	}

	//if (VTK_MANAGER->loadUpperSTL(QString("G:\\STL test\\cad_maxilla.stl"))) update();
	//if (VTK_MANAGER->loadUpperSTL(QString("G:\\STL test\\upper test.stl"))) update();

	//if (VTK_MANAGER->loadCrown(QString("G:\\00.project\\CCAD\\Data\\36_2.stl"))) update();
	//if (VTK_MANAGER->loadCrown(QString("G:\\STL test\\36_2_tr.stl"))) update();
	//if (VTK_MANAGER->loadCrown(QString("G:\\STL test\\13_1_tr.stl"))) update();

	//if (VTK_MANAGER->loadInner(QString("G:\\00.project\\CCAD\\Data\\OFFSET_SOLID2.stl"))) update();

	//m_AxialView->init();
	//m_AxialView->show();
	
}

void ModelWindow::butOpenLowerSTL()
{
	QString strLatest;
	int i = 0;

	const QFileDialog::Options options = QFlag(QFileDialog::ShowDirsOnly);
	QString selectedFilter;
	QString fileName = QFileDialog::getOpenFileName(this,
		QStringLiteral("LOWER STL FileOpen"),
		tr(""),
		tr("STL File(*.stl;*.STL)"),
		&selectedFilter,
		options);

	if (!fileName.isEmpty())
	{
		if (VTK_MANAGER->loadLowerSTL(fileName)) update();
	}
}
