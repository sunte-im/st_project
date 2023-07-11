#include "dialog.h"
#include "ui_dialog.h"
#include "orbittransformcontroller.h"

#include <Qt3DExtras/Qt3DExtras>
#include <Qt3DExtras/QExtrudedTextMesh>
#include <QPropertyAnimation>
#include <QTimer>
#include <QDebug>


Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);   

    m_angle = 0;
    init();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::init()
{
    Qt3DExtras::Qt3DWindow *view = new Qt3DExtras::Qt3DWindow();
    view->defaultFrameGraph()->setClearColor(QColor(QRgb(0x4d4d4f)));

    QWidget *container = QWidget::createWindowContainer(view);

    ui->verticalLayout->addWidget(container);

    // Root entity
    Qt3DCore::QEntity *rootEntity = new Qt3DCore::QEntity();


    // Camera
    Qt3DRender::QCamera *cameraEntity = view->camera();
    cameraEntity->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    cameraEntity->setPosition(QVector3D(0, 0, 20.0f));
    cameraEntity->setUpVector(QVector3D(0, 1, 0));
    cameraEntity->setViewCenter(QVector3D(0, 0, 0));

    auto *textMaterial = new Qt3DExtras::QPhongMaterial(rootEntity);
    auto *text = new Qt3DCore::QEntity(rootEntity);
    auto *textMesh = new Qt3DExtras::QExtrudedTextMesh();

    m_textTransform = new Qt3DCore::QTransform();
    QFont font("Roboto", 32, -1, false);
    m_textTransform->setTranslation(QVector3D(0,0,0));
    m_textTransform->setScale(.2f);
    textMesh->setDepth(.45f);
    textMesh->setFont(font);
    textMesh->setText("Huvitz");
    textMaterial->setDiffuse(QColor(111, 150, 255));

    OrbitTransformController *controller1 = new OrbitTransformController(m_textTransform);
    controller1->setTarget(m_textTransform);
    controller1->setRadius(2.0f);

    QPropertyAnimation *sphereRotateTransformAnimation1 = new QPropertyAnimation(m_textTransform);
    sphereRotateTransformAnimation1->setTargetObject(controller1);
    sphereRotateTransformAnimation1->setPropertyName("angle");
    sphereRotateTransformAnimation1->setStartValue(QVariant::fromValue(0));
    sphereRotateTransformAnimation1->setEndValue(QVariant::fromValue(360));
    sphereRotateTransformAnimation1->setDuration(10000);
    sphereRotateTransformAnimation1->setLoopCount(-1);
    sphereRotateTransformAnimation1->start();

    text->addComponent(textMaterial);
    text->addComponent(textMesh);
    text->addComponent(m_textTransform);

    // For camera controls
    Qt3DExtras::QFirstPersonCameraController *camController = new Qt3DExtras::QFirstPersonCameraController(rootEntity);
    camController->setCamera(cameraEntity);

    // Set root object of the scene
    view->setRootEntity(rootEntity);

    //QTimer* timer = new QTimer(this);
    //connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));
    //timer->start(500);
}

void Dialog::timeout()
{
    qDebug() << "Dialog::timeout..1";
    m_matrix.setToIdentity();
    m_matrix.rotate(m_angle++, QVector3D(0.0f, 1.0f, 0.0f));
    m_matrix.translate(2.0f, 0.0f, 0.0f);
    m_textTransform->setMatrix(m_matrix);
}
