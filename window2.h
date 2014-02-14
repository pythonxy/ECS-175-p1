#ifndef WINDOW2_H
#define WINDOW2_H

#include <QtGui/QWidget>

#include "glwidget2.h"

class Window2 : public QWidget
{
    Q_OBJECT

public:
    Window2(QWidget *parent = 0);
    GLWidget2* glwidget2;
};

#endif // WINDOW2_H

