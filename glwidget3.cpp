#include "glwidget3.h"

#include <GL/glext.h>
#include <GL/glx.h>
#include <QtGui>
#include <iostream>
#include <cmath>


PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays3;
PFNGLGENVERTEXARRAYSPROC glGenVertexArrays3;
PFNGLBINDVERTEXARRAYPROC glBindVertexArray3;

GLWidget3::GLWidget3(QWidget *parent) :
    QGLWidget(parent), draw_mode(GL_LINES), a(-0.5) {
}

GLWidget3::~GLWidget3()
{
    destroyDraw();
}

void GLWidget3::initializeGL()
{
    //load opengl functions that are not in QGLFunctions
    //on mac and linux use glXGetProcAddress
    //on windows use wglGetProcAddress and don't cast to const GLubyte*
    initializeDraw();
    draw();
}

void GLWidget3::initializeDraw(){
    glDeleteVertexArrays3 = (PFNGLDELETEVERTEXARRAYSPROC)glXGetProcAddress((GLubyte*)"glDeleteVertexArrays");
    glGenVertexArrays3 = (PFNGLGENVERTEXARRAYSPROC)glXGetProcAddress((GLubyte*)"glGenVertexArrays");
    glBindVertexArray3 = (PFNGLBINDVERTEXARRAYPROC)glXGetProcAddress((GLubyte*)"glBindVertexArray");

    //load opengl functions
    initializeGLFunctions();

    //set the clear color to black
    glClearColor(0,0,0,1);

    //enable depth testing
    glEnable(GL_DEPTH_TEST);

    //load and initialize shaders
    //load the shaders, link the shader, and set the shader to be active
    shader = new QGLShaderProgram();
    shader->addShaderFromSourceFile(QGLShader::Vertex, ":/basic2.vert");
    shader->addShaderFromSourceFile(QGLShader::Fragment, ":/basic.frag");
    shader->link();
    shader->bind();
}

void GLWidget3::destroyDraw(){
    //delete the vertex array and vertex buffer
    GLuint loc = glGetAttribLocation(shader->programId(), "position");
    glDisableVertexAttribArray(loc);
    loc = glGetAttribLocation(shader->programId(), "color");
    glDisableVertexAttribArray(loc);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &vertex_buffer);

    glBindVertexArray3(0);
    glDeleteVertexArrays3(1, &vertex_array);

    //delete the shaders
    shader->release();
    shader->removeAllShaders();
    delete shader;
}


void GLWidget3::paintGL()
{
    //clear the color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //draw the 3 points as a triangle or line loop
    glBindVertexArray3(vertex_array);
    glDrawArrays(draw_mode, 0, qvect.size()/3 );
}

void GLWidget3::resizeGL(int w, int h)
{
    //set the viewing rectangle to be the entire window
    glViewport(0,0,w,h);
}

QSize GLWidget3::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize GLWidget3::sizeHint() const
{
    return QSize(500, 500);
}

void GLWidget3::draw()
{
    qvect.clear();
    qcol.clear();
    b=0.25;
    //a=0.0;

    //circle();
    //line();
    drawU();

    for (int i=0; i<qvect.size(); i++) {
        qcol.append(1);
    }

    //get a unique id for the vertex array
    glGenVertexArrays3(1, &vertex_array);
    //set the vertex array to be the active one
    glBindVertexArray3(vertex_array);

    //get a unique id for the vertex buffer
    glGenBuffers(1, &vertex_buffer);
    //set the vertex buffer to be active
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    //specify the size and type of the vertex buffer

    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*qvect.size() + sizeof(GLfloat)*qcol.size(), NULL, GL_STATIC_DRAW);

    //load the vertex and color data into the vertex buffer (vertices in the first half, colors in the second half)
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat)*qvect.size(), &(qvect[0]) );

    glBufferSubData(GL_ARRAY_BUFFER, sizeof(GLfloat)*qvect.size(), sizeof(GLfloat)*qcol.size(), &(qcol[0]) );

    //set the size of the vertex (3 component) and connect it to the correct shader variable
    GLuint loc = glGetAttribLocation(shader->programId(), "position");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //set the size of the color (3 component) and connect it to the correct shader variable
    loc = glGetAttribLocation(shader->programId(), "color");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(GLfloat)*qvect.size()) );
}

void GLWidget3::increase() {
    makeCurrent();
    if (a>=-0.5&&a<0.5) a +=0.01;
    else a -=0.01;
    draw();
    updateGL();
}

void GLWidget3::circle() {
    GLfloat x=0, y=0;

    float t=0.0;
    x = b * cos(M_PI/180 * t);
    y = b * sin(M_PI/180 * t);
    qvect.append(x);
    qvect.append(y);
    qvect.append(0.0);
    for (t=1; t<360; t++) {
        x = b * cos(M_PI/180 * t);
        y = b * sin(M_PI/180 * t);
        qvect.append(x);
        qvect.append(y);
        qvect.append(0.0);
        qvect.append(x);
        qvect.append(y);
        qvect.append(0.0);
    }
    x = b * cos(M_PI/180 * t);
    y = b * sin(M_PI/180 * t);
    qvect.append(x);
    qvect.append(y);
    qvect.append(0.0);
}

void GLWidget3::line() {
    GLfloat x=0, y=0;

    float t=0.0;

    x = 2.0;
    y = a;
    qvect.append(x);
    qvect.append(y);
    qvect.append(0.0);

    for (t=1; t<180; t++) {
        x = a / tan(M_PI/180 * t);
        y = a;
        qvect.append(x);
        qvect.append(y);
        qvect.append(0.0);
        qvect.append(x);
        qvect.append(y);
        qvect.append(0.0);
    }

    x = -2.0;
    y = a;
    qvect.append(x);
    qvect.append(y);
    qvect.append(0.0);

    /*for (float t=181; t<359; t++) {
        x = a / sin(M_PI/180 * (t-180));
        y = a;
        qvect.append(x);
        qvect.append(y);
        qvect.append(0.0);
    }*/
}

void GLWidget3::drawU() {
    GLfloat Cx,Cy,Fx,Fy;

    float t;
    t=1.0;
    Cx = b * cos(M_PI/180 * t);
    Cy = b * sin(M_PI/180 * t);
    Fx = a / tan(M_PI/180 * t);
    Fy = a;
    qvect.append(Fx-Cx);
    qvect.append(Fy-Cy);
    qvect.append(0.0);

    for (t=1.0; t<180.0; t++) {
        Cx = b * cos(M_PI/180 * t);
        Cy = b * sin(M_PI/180 * t);
        Fx = a / tan(M_PI/180 * t);
        Fy = a;
        qvect.append(Fx-Cx);
        qvect.append(Fy-Cy);
        qvect.append(0.0);
        qvect.append(Fx-Cx);
        qvect.append(Fy-Cy);
        qvect.append(0.0);
    }

    qvect.append(Fx-Cx);
    qvect.append(Fy-Cy);
    qvect.append(0.0);

    t=181.0;
    Cx = b * cos(M_PI/180 * t);
    Cy = b * sin(M_PI/180 * t);
    Fx = a / tan(M_PI/180 * t);
    Fy = a;
    qvect.append(Fx-Cx);
    qvect.append(Fy-Cy);
    qvect.append(0.0);

    for (t=181.0; t<360.0; t++) {
        Cx = b * cos(M_PI/180 * t);
        Cy = b * sin(M_PI/180 * t);
        Fx = a / tan(M_PI/180 * t);
        Fy = a;
        qvect.append(Fx-Cx);
        qvect.append(Fy-Cy);
        qvect.append(0.0);
        qvect.append(Fx-Cx);
        qvect.append(Fy-Cy);
        qvect.append(0.0);
    }

    qvect.append(Fx-Cx);
    qvect.append(Fy-Cy);
    qvect.append(0.0);
}


