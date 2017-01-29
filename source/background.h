#pragma once
#include <QtQuick/QQuickItem>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLFunctions>
#include <HQTimer.h>


class BackgroundRenderer : public QObject, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    BackgroundRenderer() : m_t(0), shader(0) {  }
    ~BackgroundRenderer();

    void setT(qreal t) {  m_t = t;  }
    void setViewportSize(const QSize &size) {  m_viewportSize = size;  }
    void setWindow(QQuickWindow *window) {  m_window = window;  }

    void setFps(QObject* obj) {  m_Fps = obj;  }

public slots:
    void paint();
    void paintBackground();

private:
    QSize m_viewportSize;
    qreal m_t;
    QOpenGLShaderProgram *shader;
    QQuickWindow *m_window;

    QObject* m_Fps;
    HQTimer tim;
};


class Background : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(qreal t READ t WRITE setT NOTIFY tChanged)

public:
    Background();
    ~Background() {  m_renderer->setFps(0);  }

    qreal t() const { return m_t; }
    void setT(qreal t);

    void setFps(QObject* obj) {  m_Fps = obj;  }

signals:
    void tChanged();

public slots:
    void sync();
    void cleanup();

private slots:
    void handleWindowChanged(QQuickWindow *win);

private:
    qreal m_t;
    BackgroundRenderer *m_renderer;

    QObject* m_Fps;

public:
    BackgroundRenderer *getRenderer() {  return m_renderer;  }
};
