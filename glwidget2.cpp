#include "glwidget2.h"

#include <GL/glext.h>
#include <GL/glx.h>
#include <QtGui>
#include <iostream>
#include <algorithm>    // std::min

PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays2;
PFNGLGENVERTEXARRAYSPROC glGenVertexArrays2;
PFNGLBINDVERTEXARRAYPROC glBindVertexArray2;

GLWidget2::GLWidget2(QWidget *parent) :
    QGLWidget(parent), level(5) {
}

GLWidget2::~GLWidget2() {
    //delete the vertex array and vertex buffer
    destroyDraw();
}


void GLWidget2::initializeGL()
{
    //load opengl functions that are not in QGLFunctions
    //on mac and linux use glXGetProcAddress
    //on windows use wglGetProcAddress and don't cast to const GLubyte*

    initializeDraw();
    draw();
}

void GLWidget2::initializeDraw(){

    glDeleteVertexArrays2 = (PFNGLDELETEVERTEXARRAYSPROC)glXGetProcAddress((GLubyte*)"glDeleteVertexArrays");
    glGenVertexArrays2 = (PFNGLGENVERTEXARRAYSPROC)glXGetProcAddress((GLubyte*)"glGenVertexArrays");
    glBindVertexArray2 = (PFNGLBINDVERTEXARRAYPROC)glXGetProcAddress((GLubyte*)"glBindVertexArray");

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

void GLWidget2::destroyDraw(){
    //delete the vertex array and vertex buffer
    GLuint loc = glGetAttribLocation(shader->programId(), "position");
    glDisableVertexAttribArray(loc);
    loc = glGetAttribLocation(shader->programId(), "color");
    glDisableVertexAttribArray(loc);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &vertex_buffer);

    glBindVertexArray2(0);
    glDeleteVertexArrays2(1, &vertex_array);

    //delete the shaders
    shader->release();
    shader->removeAllShaders();
    delete shader;
}


void GLWidget2::paintGL()
{
    //clear the color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //draw the 3 points as a triangle or line loop
    glBindVertexArray2(vertex_array);
    glDrawArrays(GL_LINE_STRIP, 0, qlst1.size()/3 );
    glBindVertexArray2(vertex_array2);
    glDrawArrays(GL_LINE_STRIP, 0, qlst2.size()/3 );
    glBindVertexArray2(vertex_array3);
    glDrawArrays(GL_LINE_STRIP, 0, qlst3.size()/3 );
    glBindVertexArray2(vertex_array4);
    glDrawArrays(GL_LINE_STRIP, 0, qlst4.size()/3 );
    glBindVertexArray2(vertex_array5);
    glDrawArrays(GL_LINE_STRIP, 0, qlst5.size()/3 );
    glBindVertexArray2(vertex_array6);
    glDrawArrays(GL_LINE_STRIP, 0, qlst6.size()/3 );
    glBindVertexArray2(vertex_array7);
    glDrawArrays(GL_LINE_STRIP, 0, qlst7.size()/3 );
    glBindVertexArray2(vertex_array42);
    glDrawArrays(GL_LINE_STRIP, 0, qlst42.size()/3 );
    glBindVertexArray2(vertex_array52);
    glDrawArrays(GL_LINE_STRIP, 0, qlst52.size()/3 );
    glBindVertexArray2(vertex_array43);
    glDrawArrays(GL_LINE_STRIP, 0, qlst43.size()/3 );
    glBindVertexArray2(vertex_array44);
    glDrawArrays(GL_LINE_STRIP, 0, qlst44.size()/3 );
    glBindVertexArray2(vertex_array45);
    glDrawArrays(GL_LINE_STRIP, 0, qlst45.size()/3 );
    glBindVertexArray2(vertex_array53);
    glDrawArrays(GL_LINE_STRIP, 0, qlst53.size()/3 );
    glBindVertexArray2(vertex_array54);
    glDrawArrays(GL_LINE_STRIP, 0, qlst54.size()/3 );
    glBindVertexArray2(vertex_array55);
    glDrawArrays(GL_LINE_STRIP, 0, qlst55.size()/3 );
}

void GLWidget2::resizeGL(int w, int h)
{
    //set the viewing rectangle to be the entire window
    glViewport(0,0,w,h);
}

QSize GLWidget2::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize GLWidget2::sizeHint() const
{
    return QSize(500, 500);
}

void GLWidget2::draw() {
    qlst1.clear();
    qcol1.clear();

    qlst2.clear();
    qcol2.clear();

    qlst3.clear();
    qcol3.clear();

    qlst4.clear();
    qcol4.clear();

    qlst5.clear();
    qcol5.clear();

    qlst6.clear();
    qcol6.clear();

    qlst7.clear();
    qcol7.clear();

    qlst42.clear();
    qcol42.clear();
    qlst43.clear();
    qcol43.clear();
    qlst44.clear();
    qcol44.clear();
    qlst45.clear();
    qcol45.clear();

    qlst52.clear();
    qcol52.clear();
    qlst53.clear();
    qcol53.clear();
    qlst54.clear();
    qcol54.clear();
    qlst55.clear();
    qcol55.clear();


    for(float i=0.0;i<=1.2;i+=0.1) {
        qlst1.append(0.01); qlst1.append(i); qlst1.append(0.0);
    }
    for(float i=0.0;i<=1.2;i+=0.1) {
        qlst2.append(1.99); qlst2.append(i); qlst2.append(0.0);
    }

    //U
    qlst3.append(0.01); qlst3.append(0.0); qlst3.append(0.0);

    qlst3.append(0.01); qlst3.append(2.0); qlst3.append(0.0);

    qlst3.append(1.99); qlst3.append(2.0); qlst3.append(0.0);

    qlst3.append(1.99); qlst3.append(0.0); qlst3.append(0.0);

    //O
    qlst4.append(0.25); qlst4.append(1.15); qlst4.append(0.0);

    qlst4.append(0.25); qlst4.append(1.65); qlst4.append(0.0);

    qlst4.append(0.75); qlst4.append(1.65); qlst4.append(0.0);

    qlst4.append(0.75); qlst4.append(1.15); qlst4.append(0.0);

    qlst4.append(0.25); qlst4.append(1.15); qlst4.append(0.0);

    //|||
    qlst43.append(0.35); qlst43.append(1.53); qlst43.append(0.0);

    qlst43.append(0.30);  qlst43.append(1.65); qlst43.append(0.0);

    qlst43.append(0.35);  qlst43.append(1.75); qlst43.append(0.0);

    qlst44.append(0.45); qlst44.append(1.55); qlst44.append(0.0);

    qlst44.append(0.40); qlst44.append(1.70); qlst44.append(0.0);

    qlst44.append(0.45); qlst44.append(1.85); qlst44.append(0.0);

    qlst45.append(0.55); qlst45.append(1.58); qlst45.append(0.0);

    qlst45.append(0.60); qlst45.append(1.70); qlst45.append(0.0);

    qlst45.append(0.55); qlst45.append(1.83); qlst45.append(0.0);

    //|||
    qlst53.append(1.65); qlst53.append(1.53); qlst53.append(0.0);

    qlst53.append(1.70); qlst53.append(1.65); qlst53.append(0.0);

    qlst53.append(1.65); qlst53.append(1.75); qlst53.append(0.0);

    qlst54.append(1.55); qlst54.append(1.55); qlst54.append(0.0);

    qlst54.append(1.60); qlst54.append(1.70); qlst54.append(0.0);

    qlst54.append(1.55); qlst54.append(1.85); qlst54.append(0.0);

    qlst55.append(1.45); qlst55.append(1.58); qlst55.append(0.0);

    qlst55.append(1.40); qlst55.append(1.70); qlst55.append(0.0);

    qlst55.append(1.45); qlst55.append(1.83); qlst55.append(0.0);

    //O
    qlst5.append(1.25); qlst5.append(1.15); qlst5.append(0.0);

    qlst5.append(1.25); qlst5.append(1.65); qlst5.append(0.0);

    qlst5.append(1.75); qlst5.append(1.65); qlst5.append(0.0);

    qlst5.append(1.75); qlst5.append(1.15); qlst5.append(0.0);

    qlst5.append(1.25); qlst5.append(1.15); qlst5.append(0.0);

    //(___)
    qlst6.append(0.25); qlst6.append(0.5); qlst6.append(0.0);

    qlst6.append(0.25); qlst6.append(1.0); qlst6.append(0.0);

    qlst6.append(1.75); qlst6.append(1.0); qlst6.append(0.0);

    qlst6.append(1.75); qlst6.append(0.5); qlst6.append(0.0);

    qlst6.append(0.25); qlst6.append(0.5); qlst6.append(0.0);

    //.
    qlst42.append(0.48); qlst42.append(1.38); qlst42.append(0.0);

    qlst42.append(0.48); qlst42.append(1.42); qlst42.append(0.0);

    qlst42.append(0.52); qlst42.append(1.42); qlst42.append(0.0);

    qlst42.append(0.52); qlst42.append(1.38); qlst42.append(0.0);

    qlst42.append(0.48); qlst42.append(1.38); qlst42.append(0.0);

    //.
    qlst52.append(1.48); qlst52.append(1.38); qlst52.append(0.0);

    qlst52.append(1.48); qlst52.append(1.42); qlst52.append(0.0);

    qlst52.append(1.52); qlst52.append(1.42); qlst52.append(0.0);

    qlst52.append(1.52); qlst52.append(1.38); qlst52.append(0.0);

    qlst52.append(1.48); qlst52.append(1.38); qlst52.append(0.0);


    //---
    /*for(float i=0.20;i<1.81;i+=0.1){
        qlst7.append(i);
        qlst7.append(0.75);
        qlst7.append(0.0);
    }*/

    qlst7.append(0.20);
    qlst7.append(0.75);
    qlst7.append(0.0);
    qlst7.append(0.30);
    qlst7.append(0.85);
    qlst7.append(0.0);
    qlst7.append(1.00);
    qlst7.append(0.75);
    qlst7.append(0.0);
    qlst7.append(1.70);
    qlst7.append(0.85);
    qlst7.append(0.0);
    qlst7.append(1.80);
    qlst7.append(0.75);
    qlst7.append(0.0);

    int i = abs(level-5);
    while(i-- > 0) {
        makeCurve(qlst1);
        makeCurve(qlst2);
        makeCurve(qlst3);
        makeCurve(qlst4);
        makeCurve(qlst5);
        makeCurve(qlst6);
        makeCurve(qlst7);
        makeCurve(qlst42);
        makeCurve(qlst52);
        makeCurve(qlst43);
        makeCurve(qlst44);
        makeCurve(qlst45);
        makeCurve(qlst53);
        makeCurve(qlst54);
        makeCurve(qlst55);
    }

    for (int i=0; i<qlst1.size(); i++) {
        qcol1.append(1);
    }

    //get a unique id for the vertex array
    glGenVertexArrays2(1, &vertex_array);
    //set the vertex array to be the active one
    glBindVertexArray2(vertex_array);

    //get a unique id for the vertex buffer
    glGenBuffers(1, &vertex_buffer);
    //set the vertex buffer to be active
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    //specify the size and type of the vertex buffer

    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors), NULL, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*qlst1.size() + sizeof(GLfloat)*qcol1.size(), NULL, GL_STATIC_DRAW);

    //load the vertex and color data into the vertex buffer (vertices in the first half, colors in the second half)
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat)*qlst1.size(), &(qlst1[0]) );

    glBufferSubData(GL_ARRAY_BUFFER, sizeof(GLfloat)*qlst1.size(), sizeof(GLfloat)*qcol1.size(), &(qcol1[0]) );

    //set the size of the vertex (3 component) and connect it to the correct shader variable
    GLuint loc = glGetAttribLocation(shader->programId(), "position");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //set the size of the color (3 component) and connect it to the correct shader variable
    loc = glGetAttribLocation(shader->programId(), "color");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(GLfloat)*qlst1.size()) );


    for (int i=0; i<qlst2.size(); i++) {
        qcol2.append(1);
    }

    //get a unique id for the vertex array
    glGenVertexArrays2(1, &vertex_array2);
    //set the vertex array to be the active one
    glBindVertexArray2(vertex_array2);

    //get a unique id for the vertex buffer
    glGenBuffers(1, &vertex_buffer2);
    //set the vertex buffer to be active
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer2);
    //specify the size and type of the vertex buffer

    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors), NULL, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*qlst2.size() + sizeof(GLfloat)*qcol2.size(), NULL, GL_STATIC_DRAW);

    //load the vertex and color data into the vertex buffer (vertices in the first half, colors in the second half)
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat)*qlst2.size(), &(qlst2[0]) );

    glBufferSubData(GL_ARRAY_BUFFER, sizeof(GLfloat)*qlst2.size(), sizeof(GLfloat)*qcol2.size(), &(qcol2[0]) );

    //set the size of the vertex (3 component) and connect it to the correct shader variable
    loc = glGetAttribLocation(shader->programId(), "position");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //set the size of the color (3 component) and connect it to the correct shader variable
    loc = glGetAttribLocation(shader->programId(), "color");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(GLfloat)*qlst2.size()) );


    for (int i=0; i<qlst3.size(); i++) {
        qcol3.append(1);
    }

    //get a unique id for the vertex array
    glGenVertexArrays2(1, &vertex_array3);
    //set the vertex array to be the active one
    glBindVertexArray2(vertex_array3);

    //get a unique id for the vertex buffer
    glGenBuffers(1, &vertex_buffer3);
    //set the vertex buffer to be active
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer3);
    //specify the size and type of the vertex buffer

    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors), NULL, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*qlst3.size() + sizeof(GLfloat)*qcol3.size(), NULL, GL_STATIC_DRAW);

    //load the vertex and color data into the vertex buffer (vertices in the first half, colors in the second half)
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat)*qlst3.size(), &(qlst3[0]) );

    glBufferSubData(GL_ARRAY_BUFFER, sizeof(GLfloat)*qlst3.size(), sizeof(GLfloat)*qcol3.size(), &(qcol3[0]) );

    //set the size of the vertex (3 component) and connect it to the correct shader variable
    loc = glGetAttribLocation(shader->programId(), "position");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //set the size of the color (3 component) and connect it to the correct shader variable
    loc = glGetAttribLocation(shader->programId(), "color");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(GLfloat)*qlst3.size()) );

    for (int i=0; i<qlst4.size(); i++) {
        qcol4.append(1);
    }

    //get a unique id for the vertex array
    glGenVertexArrays2(1, &vertex_array4);
    //set the vertex array to be the active one
    glBindVertexArray2(vertex_array4);

    //get a unique id for the vertex buffer
    glGenBuffers(1, &vertex_buffer4);
    //set the vertex buffer to be active
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer4);
    //specify the size and type of the vertex buffer

    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors), NULL, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*qlst4.size() + sizeof(GLfloat)*qcol4.size(), NULL, GL_STATIC_DRAW);

    //load the vertex and color data into the vertex buffer (vertices in the first half, colors in the second half)
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat)*qlst4.size(), &(qlst4[0]) );

    glBufferSubData(GL_ARRAY_BUFFER, sizeof(GLfloat)*qlst4.size(), sizeof(GLfloat)*qcol4.size(), &(qcol4[0]) );

    //set the size of the vertex (3 component) and connect it to the correct shader variable
    loc = glGetAttribLocation(shader->programId(), "position");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //set the size of the color (3 component) and connect it to the correct shader variable
    loc = glGetAttribLocation(shader->programId(), "color");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(GLfloat)*qlst4.size()) );

    for (int i=0; i<qlst5.size(); i++) {
        qcol5.append(1);
    }

    //get a unique id for the vertex array
    glGenVertexArrays2(1, &vertex_array5);
    //set the vertex array to be the active one
    glBindVertexArray2(vertex_array5);

    //get a unique id for the vertex buffer
    glGenBuffers(1, &vertex_buffer5);
    //set the vertex buffer to be active
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer5);
    //specify the size and type of the vertex buffer

    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors), NULL, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*qlst5.size() + sizeof(GLfloat)*qcol5.size(), NULL, GL_STATIC_DRAW);

    //load the vertex and color data into the vertex buffer (vertices in the first half, colors in the second half)
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat)*qlst5.size(), &(qlst5[0]) );

    glBufferSubData(GL_ARRAY_BUFFER, sizeof(GLfloat)*qlst5.size(), sizeof(GLfloat)*qcol5.size(), &(qcol5[0]) );

    //set the size of the vertex (3 component) and connect it to the correct shader variable
    loc = glGetAttribLocation(shader->programId(), "position");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //set the size of the color (3 component) and connect it to the correct shader variable
    loc = glGetAttribLocation(shader->programId(), "color");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(GLfloat)*qlst5.size()) );

    for (int i=0; i<qlst6.size()/3; i++) {
        qcol6.append(1);
        qcol6.append(1);
        qcol6.append(0);
    }

    //get a unique id for the vertex array
    glGenVertexArrays2(1, &vertex_array6);
    //set the vertex array to be the active one
    glBindVertexArray2(vertex_array6);

    //get a unique id for the vertex buffer
    glGenBuffers(1, &vertex_buffer6);
    //set the vertex buffer to be active
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer6);
    //specify the size and type of the vertex buffer

    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors), NULL, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*qlst6.size() + sizeof(GLfloat)*qcol6.size(), NULL, GL_STATIC_DRAW);

    //load the vertex and color data into the vertex buffer (vertices in the first half, colors in the second half)
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat)*qlst6.size(), &(qlst6[0]) );

    glBufferSubData(GL_ARRAY_BUFFER, sizeof(GLfloat)*qlst6.size(), sizeof(GLfloat)*qcol6.size(), &(qcol6[0]) );

    //set the size of the vertex (3 component) and connect it to the correct shader variable
    loc = glGetAttribLocation(shader->programId(), "position");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //set the size of the color (3 component) and connect it to the correct shader variable
    loc = glGetAttribLocation(shader->programId(), "color");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(GLfloat)*qlst6.size()) );

    for (int i=0; i<qlst7.size()/3; i++) {
        qcol7.append(1);
        qcol7.append(1);
        qcol7.append(0);
    }

    //get a unique id for the vertex array
    glGenVertexArrays2(1, &vertex_array7);
    //set the vertex array to be the active one
    glBindVertexArray2(vertex_array7);

    //get a unique id for the vertex buffer
    glGenBuffers(1, &vertex_buffer7);
    //set the vertex buffer to be active
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer7);
    //specify the size and type of the vertex buffer

    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors), NULL, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*qlst7.size() + sizeof(GLfloat)*qcol7.size(), NULL, GL_STATIC_DRAW);

    //load the vertex and color data into the vertex buffer (vertices in the first half, colors in the second half)
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat)*qlst7.size(), &(qlst7[0]) );

    glBufferSubData(GL_ARRAY_BUFFER, sizeof(GLfloat)*qlst7.size(), sizeof(GLfloat)*qcol7.size(), &(qcol7[0]) );

    //set the size of the vertex (3 component) and connect it to the correct shader variable
    loc = glGetAttribLocation(shader->programId(), "position");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //set the size of the color (3 component) and connect it to the correct shader variable
    loc = glGetAttribLocation(shader->programId(), "color");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(GLfloat)*qlst7.size()) );

    for (int i=0; i<qlst42.size(); i++) {
        qcol42.append(1);
    }

    //get a unique id for the vertex array
    glGenVertexArrays2(1, &vertex_array42);
    //set the vertex array to be the active one
    glBindVertexArray2(vertex_array42);

    //get a unique id for the vertex buffer
    glGenBuffers(1, &vertex_buffer42);
    //set the vertex buffer to be active
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer42);
    //specify the size and type of the vertex buffer

    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors), NULL, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*qlst42.size() + sizeof(GLfloat)*qcol42.size(), NULL, GL_STATIC_DRAW);

    //load the vertex and color data into the vertex buffer (vertices in the first half, colors in the second half)
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat)*qlst42.size(), &(qlst42[0]) );

    glBufferSubData(GL_ARRAY_BUFFER, sizeof(GLfloat)*qlst42.size(), sizeof(GLfloat)*qcol42.size(), &(qcol42[0]) );

    //set the size of the vertex (3 component) and connect it to the correct shader variable
    loc = glGetAttribLocation(shader->programId(), "position");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //set the size of the color (3 component) and connect it to the correct shader variable
    loc = glGetAttribLocation(shader->programId(), "color");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(GLfloat)*qlst42.size()) );

    for (int i=0; i<qlst52.size(); i++) {
        qcol52.append(1);
    }

    //get a unique id for the vertex array
    glGenVertexArrays2(1, &vertex_array52);
    //set the vertex array to be the active one
    glBindVertexArray2(vertex_array52);

    //get a unique id for the vertex buffer
    glGenBuffers(1, &vertex_buffer52);
    //set the vertex buffer to be active
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer52);
    //specify the size and type of the vertex buffer

    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors), NULL, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*qlst52.size() + sizeof(GLfloat)*qcol52.size(), NULL, GL_STATIC_DRAW);

    //load the vertex and color data into the vertex buffer (vertices in the first half, colors in the second half)
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat)*qlst52.size(), &(qlst52[0]) );

    glBufferSubData(GL_ARRAY_BUFFER, sizeof(GLfloat)*qlst52.size(), sizeof(GLfloat)*qcol52.size(), &(qcol52[0]) );

    //set the size of the vertex (3 component) and connect it to the correct shader variable
    loc = glGetAttribLocation(shader->programId(), "position");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //set the size of the color (3 component) and connect it to the correct shader variable
    loc = glGetAttribLocation(shader->programId(), "color");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(GLfloat)*qlst52.size()) );


    for (int i=0; i<qlst43.size(); i++) {
        qcol43.append(1);
    }

    //get a unique id for the vertex array
    glGenVertexArrays2(1, &vertex_array43);
    //set the vertex array to be the active one
    glBindVertexArray2(vertex_array43);

    //get a unique id for the vertex buffer
    glGenBuffers(1, &vertex_buffer43);
    //set the vertex buffer to be active
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer43);
    //specify the size and type of the vertex buffer

    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors), NULL, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*qlst43.size() + sizeof(GLfloat)*qcol43.size(), NULL, GL_STATIC_DRAW);

    //load the vertex and color data into the vertex buffer (vertices in the first half, colors in the second half)
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat)*qlst43.size(), &(qlst43[0]) );

    glBufferSubData(GL_ARRAY_BUFFER, sizeof(GLfloat)*qlst43.size(), sizeof(GLfloat)*qcol43.size(), &(qcol43[0]) );

    //set the size of the vertex (3 component) and connect it to the correct shader variable
    loc = glGetAttribLocation(shader->programId(), "position");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //set the size of the color (3 component) and connect it to the correct shader variable
    loc = glGetAttribLocation(shader->programId(), "color");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(GLfloat)*qlst43.size()) );

    for (int i=0; i<qlst53.size(); i++) {
        qcol53.append(1);
    }

    //get a unique id for the vertex array
    glGenVertexArrays2(1, &vertex_array53);
    //set the vertex array to be the active one
    glBindVertexArray2(vertex_array53);

    //get a unique id for the vertex buffer
    glGenBuffers(1, &vertex_buffer53);
    //set the vertex buffer to be active
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer53);
    //specify the size and type of the vertex buffer

    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors), NULL, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*qlst53.size() + sizeof(GLfloat)*qcol53.size(), NULL, GL_STATIC_DRAW);

    //load the vertex and color data into the vertex buffer (vertices in the first half, colors in the second half)
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat)*qlst53.size(), &(qlst53[0]) );

    glBufferSubData(GL_ARRAY_BUFFER, sizeof(GLfloat)*qlst53.size(), sizeof(GLfloat)*qcol53.size(), &(qcol53[0]) );

    //set the size of the vertex (3 component) and connect it to the correct shader variable
    loc = glGetAttribLocation(shader->programId(), "position");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //set the size of the color (3 component) and connect it to the correct shader variable
    loc = glGetAttribLocation(shader->programId(), "color");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(GLfloat)*qlst53.size()) );

    for (int i=0; i<qlst44.size(); i++) {
        qcol44.append(1);
    }

    //get a unique id for the vertex array
    glGenVertexArrays2(1, &vertex_array44);
    //set the vertex array to be the active one
    glBindVertexArray2(vertex_array44);

    //get a unique id for the vertex buffer
    glGenBuffers(1, &vertex_buffer44);
    //set the vertex buffer to be active
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer44);
    //specify the size and type of the vertex buffer

    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors), NULL, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*qlst44.size() + sizeof(GLfloat)*qcol44.size(), NULL, GL_STATIC_DRAW);

    //load the vertex and color data into the vertex buffer (vertices in the first half, colors in the second half)
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat)*qlst44.size(), &(qlst44[0]) );

    glBufferSubData(GL_ARRAY_BUFFER, sizeof(GLfloat)*qlst44.size(), sizeof(GLfloat)*qcol44.size(), &(qcol44[0]) );

    //set the size of the vertex (3 component) and connect it to the correct shader variable
    loc = glGetAttribLocation(shader->programId(), "position");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //set the size of the color (3 component) and connect it to the correct shader variable
    loc = glGetAttribLocation(shader->programId(), "color");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(GLfloat)*qlst44.size()) );

    for (int i=0; i<qlst45.size(); i++) {
        qcol45.append(1);
    }

    //get a unique id for the vertex array
    glGenVertexArrays2(1, &vertex_array45);
    //set the vertex array to be the active one
    glBindVertexArray2(vertex_array45);

    //get a unique id for the vertex buffer
    glGenBuffers(1, &vertex_buffer45);
    //set the vertex buffer to be active
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer45);
    //specify the size and type of the vertex buffer

    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors), NULL, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*qlst45.size() + sizeof(GLfloat)*qcol45.size(), NULL, GL_STATIC_DRAW);

    //load the vertex and color data into the vertex buffer (vertices in the first half, colors in the second half)
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat)*qlst45.size(), &(qlst45[0]) );

    glBufferSubData(GL_ARRAY_BUFFER, sizeof(GLfloat)*qlst45.size(), sizeof(GLfloat)*qcol45.size(), &(qcol45[0]) );

    //set the size of the vertex (3 component) and connect it to the correct shader variable
    loc = glGetAttribLocation(shader->programId(), "position");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //set the size of the color (3 component) and connect it to the correct shader variable
    loc = glGetAttribLocation(shader->programId(), "color");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(GLfloat)*qlst45.size()) );

    for (int i=0; i<qlst43.size(); i++) {
        qcol43.append(1);
    }

    //get a unique id for the vertex array
    glGenVertexArrays2(1, &vertex_array43);
    //set the vertex array to be the active one
    glBindVertexArray2(vertex_array43);

    //get a unique id for the vertex buffer
    glGenBuffers(1, &vertex_buffer43);
    //set the vertex buffer to be active
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer43);
    //specify the size and type of the vertex buffer

    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors), NULL, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*qlst43.size() + sizeof(GLfloat)*qcol43.size(), NULL, GL_STATIC_DRAW);

    //load the vertex and color data into the vertex buffer (vertices in the first half, colors in the second half)
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat)*qlst43.size(), &(qlst43[0]) );

    glBufferSubData(GL_ARRAY_BUFFER, sizeof(GLfloat)*qlst43.size(), sizeof(GLfloat)*qcol43.size(), &(qcol43[0]) );

    //set the size of the vertex (3 component) and connect it to the correct shader variable
    loc = glGetAttribLocation(shader->programId(), "position");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //set the size of the color (3 component) and connect it to the correct shader variable
    loc = glGetAttribLocation(shader->programId(), "color");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(GLfloat)*qlst43.size()) );

    for (int i=0; i<qlst54.size(); i++) {
        qcol54.append(1);
    }

    //get a unique id for the vertex array
    glGenVertexArrays2(1, &vertex_array54);
    //set the vertex array to be the active one
    glBindVertexArray2(vertex_array54);

    //get a unique id for the vertex buffer
    glGenBuffers(1, &vertex_buffer54);
    //set the vertex buffer to be active
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer54);
    //specify the size and type of the vertex buffer

    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors), NULL, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*qlst54.size() + sizeof(GLfloat)*qcol54.size(), NULL, GL_STATIC_DRAW);

    //load the vertex and color data into the vertex buffer (vertices in the first half, colors in the second half)
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat)*qlst54.size(), &(qlst54[0]) );

    glBufferSubData(GL_ARRAY_BUFFER, sizeof(GLfloat)*qlst54.size(), sizeof(GLfloat)*qcol54.size(), &(qcol44[0]) );

    //set the size of the vertex (3 component) and connect it to the correct shader variable
    loc = glGetAttribLocation(shader->programId(), "position");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //set the size of the color (3 component) and connect it to the correct shader variable
    loc = glGetAttribLocation(shader->programId(), "color");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(GLfloat)*qlst44.size()) );

    for (int i=0; i<qlst55.size(); i++) {
        qcol55.append(1);
    }

    //get a unique id for the vertex array
    glGenVertexArrays2(1, &vertex_array55);
    //set the vertex array to be the active one
    glBindVertexArray2(vertex_array55);

    //get a unique id for the vertex buffer
    glGenBuffers(1, &vertex_buffer55);
    //set the vertex buffer to be active
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer55);
    //specify the size and type of the vertex buffer

    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors), NULL, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*qlst55.size() + sizeof(GLfloat)*qcol55.size(), NULL, GL_STATIC_DRAW);

    //load the vertex and color data into the vertex buffer (vertices in the first half, colors in the second half)
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat)*qlst55.size(), &(qlst55[0]) );

    glBufferSubData(GL_ARRAY_BUFFER, sizeof(GLfloat)*qlst55.size(), sizeof(GLfloat)*qcol55.size(), &(qcol55[0]) );

    //set the size of the vertex (3 component) and connect it to the correct shader variable
    loc = glGetAttribLocation(shader->programId(), "position");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //set the size of the color (3 component) and connect it to the correct shader variable
    loc = glGetAttribLocation(shader->programId(), "color");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(GLfloat)*qlst55.size()) );
}

void GLWidget2::increase() {
    level++;
    level%=9;
    makeCurrent();
    draw();
    updateGL();
}

void GLWidget2::makeCurve(QVector<GLfloat> &old_qlst){
    QVector<GLfloat> &new_qlst = *(new QVector<GLfloat>);
    for(int i=1;i<old_qlst.size()/3;i++){
        GLfloat point1X = 3.0/4.0*old_qlst[i*3-3]+1.0/4.0*old_qlst[i*3+0];
        GLfloat point2X = 1.0/4.0*old_qlst[i*3-3]+3.0/4.0*old_qlst[i*3+0];
        GLfloat point1Y = 3.0/4.0*old_qlst[i*3-2]+1.0/4.0*old_qlst[i*3+1];
        GLfloat point2Y = 1.0/4.0*old_qlst[i*3-2]+3.0/4.0*old_qlst[i*3+1];
        new_qlst.append(point1X);
        new_qlst.append(point1Y);
        new_qlst.append(0);
        new_qlst.append(point2X);
        new_qlst.append(point2Y);
        new_qlst.append(0);

    }
    if((old_qlst[0]==old_qlst[old_qlst.size()-3])
            &&(old_qlst[1]==old_qlst[old_qlst.size()-2])){
        new_qlst.append(new_qlst[0]);
        new_qlst.append(new_qlst[1]);
        new_qlst.append(0);
    }
    new_qlst.swap(old_qlst);
    delete &new_qlst;
}
