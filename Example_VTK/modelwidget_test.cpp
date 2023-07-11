#include "modelwidget_test.h"
#include "../../../CCAD/CCAD/VTK/VTKManager.h"
#include "../../../CCAD/CCAD/Polygonica/PolygonicaManager.h"
#include <QMouseEvent>
#include <QPushButton>
#include <QFileDialog>
#include <QDebug>

ModelWidget_Test::ModelWidget_Test(QWidget *parent)
    : QOpenGLWidget(parent)
{
    setMouseTracking(true);

    m_vtkManager = nullptr;
    //m_polygonicaManager = nullptr;

    init();
}

ModelWidget_Test::~ModelWidget_Test()
{
    if (m_vtkManager)
        m_vtkManager->freeVTK();

    //if (m_polygonicaManager)
    //    m_polygonicaManager->freePolygonica();
}

void ModelWidget_Test::init()
{
    QPushButton* butUpperOpen = new QPushButton(this);
    butUpperOpen->setGeometry(QRect(10, 10, 50, 20));
    butUpperOpen->setText(QStringLiteral("UPPER"));
    connect(butUpperOpen, SIGNAL(pressed()), this, SLOT(butOpenUpperSTL()));

    m_vtkManager = new VTKManager();
    m_vtkManager->initVTK();

    //m_polygonicaManager = new PolygonicaManager();
    //m_polygonicaManager->initPolygonica();
}

void ModelWidget_Test::initializeGL()
{
    initializeOpenGLFunctions();

    m_vtkManager->init(nullptr);
}

void ModelWidget_Test::resizeGL(int w, int h)
{
    m_vtkManager->resizeVTK(w, h);
}

void ModelWidget_Test::paintGL()
{
    m_vtkManager->renderVTK();

    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);

    GLint currProgram;
    glGetIntegerv(GL_CURRENT_PROGRAM, &currProgram);

    glBindBuffer(GL_ARRAY_BUFFER, 0); // For QT Painter Render

//	QPainter p;
//	p.begin(this);
//	paintQT(&p);
//	p.end();

    glUseProgram(currProgram);
}

void ModelWidget_Test::butOpenUpperSTL()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Upper case"),
        QDir::homePath(),
        "STL File(*.stl;*.STL)",
        Q_NULLPTR,
        QFileDialog::ShowDirsOnly);

    qDebug() << "ModelWidget_Test::butOpenUpperSTL fileName: " << fileName;

    if (!fileName.isEmpty())
    {
        if (m_vtkManager->loadUpperSTL(fileName))
            update();
    }
}
