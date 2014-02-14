#include "glwidget.h"

#include <GL/glext.h>
#include <GL/glx.h>
#include <QtGui>
#include <iostream>
#include <algorithm>    // std::min

PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;
PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
PFNGLBINDVERTEXARRAYPROC glBindVertexArray;

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent),
    sier_lv(2), dist0(0.5), x(0.0), y(0.0) {
}

GLWidget::~GLWidget()
{
    destroyDraw();
}


void GLWidget::initializeGL()
{
    //load opengl functions that are not in QGLFunctions
    //on mac and linux use glXGetProcAddress
    //on windows use wglGetProcAddress and don't cast to const GLubyte*
    initializeDraw();
    draw();
}

void GLWidget::initializeDraw(){
    glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)glXGetProcAddress((GLubyte*)"glDeleteVertexArrays");
    glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)glXGetProcAddress((GLubyte*)"glGenVertexArrays");
    glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)glXGetProcAddress((GLubyte*)"glBindVertexArray");

    //load opengl functions
    initializeGLFunctions();

    //set the clear color to black
    glClearColor(0,0,0,1);

    //enable depth testing
    glEnable(GL_DEPTH_TEST);

    //load and initialize shaders
    //load the shaders, link the shader, and set the shader to be active
    shader = new QGLShaderProgram();
    shader->addShaderFromSourceFile(QGLShader::Vertex, ":/basic.vert");
    shader->addShaderFromSourceFile(QGLShader::Fragment, ":/basic.frag");
    shader->link();
    shader->bind();
}

void GLWidget::destroyDraw(){
    //delete the vertex array and vertex buffer
    GLuint loc = glGetAttribLocation(shader->programId(), "position");
    glDisableVertexAttribArray(loc);
    loc = glGetAttribLocation(shader->programId(), "color");
    glDisableVertexAttribArray(loc);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &vertex_buffer99);

    glBindVertexArray(0);
    glDeleteVertexArrays(1, &vertex_array99);

    //delete the shaders
    shader->release();
    shader->removeAllShaders();
    delete shader;
}

void GLWidget::paintGL()
{
    //clear the color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //draw the 3 points as a triangle or line loop
    glBindVertexArray(vertex_array99);
    glDrawArrays(GL_LINE_STRIP, 0, qlst99.size()/3 );
}

void GLWidget::resizeGL(int w, int h)
{
    //set the viewing rectangle to be the entire window
    glViewport(0,0,w,h);
}

QSize GLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize GLWidget::sizeHint() const
{
    return QSize(500, 500);
}

void GLWidget::draw() {
    qlst99.clear();
    qcol99.clear();
    minX = 0;
    maxX = 0;
    minY = 0;
    maxY = 0;

    paint();
    GLfloat midX = (maxX+minX)/2;
    GLfloat midY = (maxY+minY)/2;
    for (int i=0; i<qlst99.size()/3; i++) {
        qlst99[i*3] += -midX+1.0;
        qlst99[i*3+1] += -midY+1.0;
    }

    for (int i=0; i<qlst99.size(); i++) {
        qcol99.append(1);
    }

    //get a unique id for the vertex array
    glGenVertexArrays(1, &vertex_array99);
    //set the vertex array to be the active one
    glBindVertexArray(vertex_array99);

    //get a unique id for the vertex buffer
    glGenBuffers(1, &vertex_buffer99);
    //set the vertex buffer to be active
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer99);
    //specify the size and type of the vertex buffer

    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*qlst99.size() + sizeof(GLfloat)*qcol99.size(), NULL, GL_STATIC_DRAW);

    //load the vertex and color data into the vertex buffer (vertices in the first half, colors in the second half)
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat)*qlst99.size(), &(qlst99[0]) );

    glBufferSubData(GL_ARRAY_BUFFER, sizeof(GLfloat)*qlst99.size(), sizeof(GLfloat)*qcol99.size(), &(qcol99[0]) );

    //set the size of the vertex (3 component) and connect it to the correct shader variable
    GLuint loc = glGetAttribLocation(shader->programId(), "position");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //set the size of the color (3 component) and connect it to the correct shader variable
    loc = glGetAttribLocation(shader->programId(), "color");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(GLfloat)*qlst99.size()) );
}


void GLWidget::drawing(double x1, double y1, double x2, double y2) {
        minX = std::min(minX,std::min(x1,x2));
        maxX = std::max(maxX,std::max(x1,x2));
        minY = std::min(minY,std::min(y1,y2));
        maxY = std::max(maxY,std::max(y1,y2));
        qlst99.append(x1);
        qlst99.append(y1);
        qlst99.append(0.0);
        qlst99.append(x2);
        qlst99.append(y2);
        qlst99.append(0.0);
}

void GLWidget::to_xy(double x, double y) {
    glTranslated(x, y, 0.0);
}

void GLWidget::line_rel(double delta_x, double delta_y) {
    drawing(x, y, x+delta_x, y+delta_y);
    x += delta_x;
    y += delta_y;
}

void GLWidget::paint() {
    dist = dist0;
    for (int i=sier_lv; i > 0; i--) {
        dist /= 2;
    }
    to_xy(2*dist, dist);
    sierp_1(sier_lv);
    line_rel(+dist, +dist);
    sierp_2(sier_lv);
    line_rel(-dist, +dist);
    sierp_3(sier_lv);
    line_rel(-dist, -dist);
    sierp_4(sier_lv);
    line_rel(+dist, -dist);
}

void GLWidget::sierp_1(int lv) {
    if (lv > 0) {
        sierp_1(lv-1);
        line_rel(+dist, +dist);
        sierp_2(lv-1);
        line_rel(+2*dist, 0);
        sierp_4(lv-1);
        line_rel(+dist, -dist);
        sierp_1(lv-1);
    }
}

void GLWidget::sierp_2(int lv) {
    if (lv > 0) {
        sierp_2(lv-1);
        line_rel(-dist, +dist);
        sierp_3(lv-1);
        line_rel(0, +2*dist);
        sierp_1(lv-1);
        line_rel(+dist, +dist);
        sierp_2(lv-1);
    }
}

void GLWidget::sierp_3(int lv) {
    if (lv > 0) {
        sierp_3(lv-1);
        line_rel(-dist, -dist);
        sierp_4(lv-1);
        line_rel(-2*dist, 0);
        sierp_2(lv-1);
        line_rel(-dist, +dist);
        sierp_3(lv-1);
    }
}

void GLWidget::sierp_4(int lv) {
    if (lv > 0) {
        sierp_4(lv-1);
        line_rel(+dist, -dist);
        sierp_1(lv-1);
        line_rel(0, -2*dist);
        sierp_3(lv-1);
        line_rel(-dist, -dist);
        sierp_4(lv-1);
    }
}

void GLWidget::increase() {
    if (sier_lv < 8 && sier_lv > 0) {
        sier_lv++;
    } else {
        sier_lv = 1;
    }
    makeCurrent();
    draw();
    updateGL();

}

