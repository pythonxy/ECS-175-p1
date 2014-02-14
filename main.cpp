
#include <QApplication>
#include "window.h"
#include "window2.h"
#include "window3.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Window w;
    Window2 w2;
    Window3 w3;
    w.show();
    w2.show();
    w3.show();

    return a.exec();
}
