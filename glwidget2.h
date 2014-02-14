#ifndef GLWIDGET2_H
#define GLWIDGET2_H

#include <QGLWidget>
#include <QtOpenGL>
#include <QGLFunctions>
#include <QVector>

class GLWidget2 : public QGLWidget, protected QGLFunctions
{
    Q_OBJECT
public:
    explicit GLWidget2(QWidget *parent = 0);
    ~GLWidget2();
    QSize minimumSizeHint() const;
    QSize sizeHint() const;

signals:

public slots:
    void increase();
    void makeCurve(QVector<GLfloat> &old_qlst);


protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

private:
    int level;
    QGLShaderProgram* shader;


    void destroyDraw();
    void initializeDraw();

    void draw();

    GLuint draw_mode;

    GLuint vertex_array;
    GLuint vertex_buffer;
    GLuint vertex_array2;
    GLuint vertex_buffer2;
    GLuint vertex_array3;
    GLuint vertex_buffer3;
    GLuint vertex_array4;
    GLuint vertex_buffer4;
    GLuint vertex_array42;
    GLuint vertex_buffer42;
    GLuint vertex_array43;
    GLuint vertex_buffer43;
    GLuint vertex_array44;
    GLuint vertex_buffer44;
    GLuint vertex_array45;
    GLuint vertex_buffer45;
    GLuint vertex_array5;
    GLuint vertex_buffer5;
    GLuint vertex_array6;
    GLuint vertex_buffer6;
    GLuint vertex_array7;
    GLuint vertex_buffer7;

    GLuint vertex_array52;
    GLuint vertex_buffer52;
    GLuint vertex_array53;
    GLuint vertex_buffer53;
    GLuint vertex_array54;
    GLuint vertex_buffer54;
    GLuint vertex_array55;
    GLuint vertex_buffer55;

    QVector<GLfloat> qlst1;
    QVector<GLfloat> qcol1;

    QVector<GLfloat> qlst2;
    QVector<GLfloat> qcol2;

    QVector<GLfloat> qlst3;
    QVector<GLfloat> qcol3;

    QVector<GLfloat> qlst4;
    QVector<GLfloat> qcol4;


    QVector<GLfloat> qlst43;
    QVector<GLfloat> qcol43;
    QVector<GLfloat> qlst44;
    QVector<GLfloat> qcol44;
    QVector<GLfloat> qlst45;
    QVector<GLfloat> qcol45;

    QVector<GLfloat> qlst5;
    QVector<GLfloat> qcol5;

    QVector<GLfloat> qlst53;
    QVector<GLfloat> qcol53;
    QVector<GLfloat> qlst54;
    QVector<GLfloat> qcol54;
    QVector<GLfloat> qlst55;
    QVector<GLfloat> qcol55;

    QVector<GLfloat> qlst6;
    QVector<GLfloat> qcol6;

    QVector<GLfloat> qlst7;
    QVector<GLfloat> qcol7;

    QVector<GLfloat> qlst42;
    QVector<GLfloat> qcol42;

    QVector<GLfloat> qlst52;
    QVector<GLfloat> qcol52;

};

#endif // GLWIDGET2_H
