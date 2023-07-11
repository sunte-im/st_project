#ifndef MODELWIDGET_TEST_H
#define MODELWIDGET_TEST_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class VTKManager;
//class PolygonicaManager;
class ModelWidget_Test : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
private:
    VTKManager* m_vtkManager;
    //PolygonicaManager* m_polygonicaManager;

public:
    explicit ModelWidget_Test(QWidget *parent = nullptr);
    ~ModelWidget_Test();

    void init();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

signals:

private slots:
    void butOpenUpperSTL();

};

#endif // MODELWIDGET_TEST_H
