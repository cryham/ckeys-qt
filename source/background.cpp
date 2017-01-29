#include "Background.h"
#include <QtQuick/qquickwindow.h>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLContext>
#include <QThread>

//  shader glsl
//-------------------------------------------------------------------------------------------------------------------------------------
const char* csVert =
    "attribute highp vec4 vertices;"
    "varying highp vec2 coords;"
    "void main() {"
    "    gl_Position = vertices;"
    "    coords = vertices.xy;"
    "}",
*csFrag =
    "uniform lowp float t;"
    "varying highp vec2 coords;"
    "void main() {"
    "    lowp float i = 0.4 - 0.2 * (pow(abs(coords.x), 6.) + pow(abs(coords.y), 8.));"
    //"    i = smoothstep(t - 0.8, t + 0.8, i);"
    "    gl_FragColor = vec4( (coords * 0.1 + 0.1)*i, i*i, 1.);"
    "}";
const float values[] = { -1, -1,  1, -1,  -1, 1,  1, 1 };


//  paint
//-------------------------------------------------------------------------------------------------------------------------------------
void BackgroundRenderer::paint()
{
    paintBackground();

    //  update Fps  ----
    //tim.iv1 = 0.2;
    tim.update();
    if (m_Fps)
        m_Fps->setProperty("text", "Fps: "+ QString::number(tim.FR, 'g', 4));
                            //QString("Fps: %1").arg(tim.FR));

    //  sleep  ...
    QThread::msleep(10);  // param..
}

//  background
void BackgroundRenderer::paintBackground()
{
    if (!shader) {
        initializeOpenGLFunctions();

        shader = new QOpenGLShaderProgram();
        shader->addShaderFromSourceCode(QOpenGLShader::Vertex, csVert);
        shader->addShaderFromSourceCode(QOpenGLShader::Fragment, csFrag);

        shader->bindAttributeLocation("vertices", 0);
        shader->link();
    }

    shader->bind();
    shader->enableAttributeArray(0);

    shader->setAttributeArray(0, GL_FLOAT, values, 2);
    shader->setUniformValue("t", (float) m_t);

    glViewport(0, 0, m_viewportSize.width(), m_viewportSize.height());

    glDisable(GL_DEPTH_TEST);

    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    shader->disableAttributeArray(0);
    shader->release();

    //  not strictly needed
    //m_window->resetOpenGLState();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
Background::Background()
    : m_t(0), m_renderer(0), m_Fps(0)
{
    connect(this, &QQuickItem::windowChanged, this, &Background::handleWindowChanged);
}

void Background::setT(qreal t)
{
    if (t == m_t)
        return;
    m_t = t;
    emit tChanged();
    if (window())
        window()->update();
}

void Background::handleWindowChanged(QQuickWindow *win)
{
    if (win) {
        connect(win, &QQuickWindow::beforeSynchronizing, this, &Background::sync, Qt::DirectConnection);
        connect(win, &QQuickWindow::sceneGraphInvalidated, this, &Background::cleanup, Qt::DirectConnection);
        win->setClearBeforeRendering(false);
    }
}

void Background::cleanup()
{
    if (m_renderer) {  delete m_renderer;  m_renderer = 0;  }
}

BackgroundRenderer::~BackgroundRenderer()
{
    delete shader;
}


void Background::sync()
{
    if (!m_renderer) {
        m_renderer = new BackgroundRenderer();
        connect(window(), &QQuickWindow::beforeRendering, m_renderer, &BackgroundRenderer::paint, Qt::DirectConnection);
    }
    m_renderer->setFps(m_Fps);
    m_renderer->setViewportSize(window()->size() * window()->devicePixelRatio());
    m_renderer->setT(m_t);
    m_renderer->setWindow(window());
}
