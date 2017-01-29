#pragma once
#include <QtQuick/QQuickItem>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLFunctions>


class BackgroundRenderer : public QObject, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    BackgroundRenderer() : m_t(0), shader(0) { }
    ~BackgroundRenderer();

    void setT(qreal t) { m_t = t; }
    void setViewportSize(const QSize &size) { m_viewportSize = size; }
    void setWindow(QQuickWindow *window) { m_window = window; }

public slots:
    void paint();
    void paintBackground();

private:
    QSize m_viewportSize;
    qreal m_t;
    QOpenGLShaderProgram *shader;
    QQuickWindow *m_window;

public:
    //  keys
    std::vector<QObject*> keys;
};


class Background : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(qreal t READ t WRITE setT NOTIFY tChanged)

public:
    Background();

    qreal t() const { return m_t; }
    void setT(qreal t);

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

public:
    BackgroundRenderer *getRenderer() {  return m_renderer;  }
};
