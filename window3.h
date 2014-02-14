#ifndef WINDOW3_H
#define WINDOW3_H

#include <QtGui/QWidget>

#include "glwidget3.h"

class Window3 : public QWidget
{
    Q_OBJECT

public:
    Window3(QWidget *parent = 0);
    GLWidget3* glwidget3;
};

#endif // WINDOW3_H
