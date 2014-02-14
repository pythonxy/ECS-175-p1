#include "window3.h"

#include <QtGui>

Window3::Window3(QWidget *parent)
    : QWidget(parent) {
    this->setWindowTitle("Project 1 - Conchoid of Nicomedes");
    GLWidget3 *glwidget3 = new GLWidget3();
    QPushButton* t_button = new QPushButton();
    t_button->setText("Change Ratio");
    connect(t_button, SIGNAL(clicked()), glwidget3, SLOT(increase()));
    t_button->setShortcut(Qt::Key_Enter);
    QVBoxLayout* vbox = new QVBoxLayout();
    vbox->addWidget(glwidget3);
    vbox->addWidget(t_button);
    setLayout(vbox);
}
