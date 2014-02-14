#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QtOpenGL>
#include <QGLFunctions>
#include <QVector>

class GLWidget : public QGLWidget, protected QGLFunctions {

    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);
    ~GLWidget();
    QSize minimumSizeHint() const;
    QSize sizeHint() const;

   double minX;
   double maxX;
   double minY;
   double maxY;
    
signals:
    
public slots:
    void increase();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

private:
    QGLShaderProgram* shader;
    GLuint vertex_array99;
    GLuint vertex_buffer99;

    void initializeDraw();
    void destroyDraw();
    void draw();

    GLuint draw_mode;

    QVector<GLfloat> qlst99;
    QVector<GLfloat> qcol99;


    int sier_lv;
    double dist, dist0, x, y;

    void drawing(double x1, double y1, double x2, double y2);
    void paint();
    void to_xy(double x, double y);

    void line_rel(double delta_x, double delta_y);
    void sierp_1(int lv);
    void sierp_2(int lv);
    void sierp_3(int lv);
    void sierp_4(int lv);
};

#endif // GLWIDGET_H
