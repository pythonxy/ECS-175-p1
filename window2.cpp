#include "window2.h"

#include <QtGui>

Window2::Window2(QWidget *parent)
    : QWidget(parent) {
    this->setWindowTitle("Project 1 - Chaikin\'s curves: Erizabesu");
    glwidget2 = new GLWidget2();
    QPushButton* t_button = new QPushButton();
    t_button->setText("Increase");
    connect(t_button, SIGNAL(clicked()), glwidget2, SLOT(increase()));
    QVBoxLayout* vbox = new QVBoxLayout();
    vbox->addWidget(glwidget2);
    vbox->addWidget(t_button);
    setLayout(vbox);
}
