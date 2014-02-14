#include "window.h"

#include <QtGui>

Window::Window(QWidget *parent)
    : QWidget(parent) {
    this->setWindowTitle("Project 1 - Sierpinski Curve");
    glwidget = new GLWidget();
    QPushButton* t_button = new QPushButton();
    t_button->setText("Change Level");
    connect(t_button, SIGNAL(clicked()), glwidget, SLOT(increase()));
    QVBoxLayout* vbox = new QVBoxLayout();
    vbox->addWidget(glwidget);
    vbox->addWidget(t_button);
    setLayout(vbox);
}
