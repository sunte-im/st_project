#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QSlider>

class QCloseEvent;
class QLineEdit;
class AxialView;

class ModelWindow : public QOpenGLWidget, protected QOpenGLFunctions
{
	Q_OBJECT

public:
	ModelWindow(QWidget* parent = Q_NULLPTR);
	~ModelWindow();

public:
    //AxialView* m_AxialView;

protected:
	void mousePressEvent(QMouseEvent* e) override;
	void mouseReleaseEvent(QMouseEvent* e) override;
	void wheelEvent(QWheelEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mouseDoubleClickEvent(QMouseEvent* event) override;
	void keyPressEvent(QKeyEvent* e) override;
	void keyReleaseEvent(QKeyEvent* e) override;

	void timerEvent(QTimerEvent* e) override;


	void initializeGL() override;
	void resizeGL(int w, int h) override;
	void paintGL() override;
	void paintQT(QPainter* p);

private:

	QVector2D							m_mousePosition;
	QVector2D							m_mousePrePosition;
	QVector2D							m_mousePressPosition;

	bool								m_but_right;
	bool								m_but_middle;
	bool								m_but_left;
	bool								m_ctrl;
	bool								m_alt;
	bool								m_shift;

	QWidget* m_widgetFile;

public:
	QSlider* sliderUpper;
	QSlider* sliderLower;
	QSlider* sliderCrown;
	QSlider* sliderInner;

	int slider_Upper;
	int slider_Lower;
	int slider_Crown;
	int slider_Inner;

private slots:
	void								butOpenUpperSTL();
	void								butOpenLowerSTL();
	void								valueChanged_Upper();
	void								valueChanged_Lower();
	void								valueChanged_Crown();
	void								valueChanged_Inner();
};

