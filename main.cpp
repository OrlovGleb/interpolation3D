#include "scene3D.h"
#include <QApplication>
#include <QMainWindow>
#include <QMenuBar>
#include <QPainter>
#include <QAction>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QtOpenGL>

int main(int argc, char** argv)
{
    QApplication app(argc,
        argv); // создаём приложение, инициализация оконной системы
    //QMainWindow *window = new QMainWindow;
    //QMenuBar *tool_bar = new QMenuBar(window);
    //QWidget *widget = new QWidget(window);
    //QAction *action;
    Scene3D scene1; // создаём виджет класса Scene3D
    scene1.setWindowTitle("3DInterpolation"); // название окна
    //action = tool_bar->addAction("&Change function", scene1, SLOT(q1()))

    //    scene1.drawText(0, 20, "TEST");
    scene1.resize(500, 500); // размеры (nWidth, nHeight) окна
    //    scene1.renderText(20,20, "TEST");
    scene1.show(); // изобразить виджет
    // scene1.showFullScreen();
    // scene1.showMaximized();

    return app.exec();
}
