#ifndef GLWIDGET3_H
#define GLWIDGET3_H

#define PI 3.14159268

#include <QGLWidget>
#include <QtOpenGL>
#include <QGLFunctions>
#include <QVector>
#include <QThread>

class GLWidget3 : public QGLWidget, protected QGLFunctions
{
    Q_OBJECT
public:
    explicit GLWidget3(QWidget *parent = 0);
    ~GLWidget3();
    QSize minimumSizeHint() const;
    QSize sizeHint() const;


signals:

public slots:
    void increase();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

private:
    QGLShaderProgram* shader;
    GLuint vertex_array;
    GLuint vertex_buffer;
    GLuint draw_mode;
    GLfloat b;
    GLfloat a;

    void destroyDraw();
    void initializeDraw();
    void draw();

    QVector<GLfloat> qvect;
    QVector<GLfloat> qcol;
    void circle();
    void line();
    void drawU();
};
#endif // GLWIDGET3_H
