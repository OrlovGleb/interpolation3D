#ifndef SCENE3D_H
#define SCENE3D_H

#include <QGLWidget> // подключаем класс QGLWidget

class Scene3D
    : public QGLWidget // класс Scene3D наследует встроенный класс QGLWidget
{
  private:
    int nx;
    int ny;
    double a;
    double b;
    const char *f_name;
    GLfloat xRot; // переменная хранит угол поворота вокруг оси X
    GLfloat yRot; // переменная хранит угол поворота вокруг оси Y
    GLfloat zRot; // переменная хранит угол поворота вокруг оси Z
    GLfloat zTra; // переменная хранит величину трансляции оси Z
    GLfloat nSca; // переменная отвечает за масштабирование обьекта
    int func_id;
    int q;
    int s;
    int pp;
    QPoint ptrMousePosition; // переменная хранит координату указателя мыши в
                             // момент нажатия

    void scale_plus(); // приблизить сцену
    void scale_minus(); // удалиться от сцены
    void rotate_up(); // повернуть сцену вверх
    void rotate_down(); // повернуть сцену вниз
    void rotate_left(); // повернуть сцену влево
    void rotate_right(); // повернуть сцену вправо
    void translate_down(); // транслировать сцену вниз
    void translate_up(); // транслировать сцену вверх
    void defaultScene(); // наблюдение сцены по умолчанию

    void drawAxis(); // построить оси координат
    void graph(); // построить график функции

  protected:
    /*virtual*/ void
    initializeGL(); // метод для проведения инициализаций, связанных с OpenGL
    /*virtual*/ void resizeGL(
        int nWidth,
        int nHeight); // метод вызывается при изменении размеров окна виджета
    /*virtual*/ void
    paintGL(); // метод, чтобы заново перерисовать содержимое виджета

    /*virtual*/ void mousePressEvent(
        QMouseEvent
            *pe); // методы обработки события мыши при нажатии клавиши мыши
    /*virtual*/ void mouseMoveEvent(
        QMouseEvent *pe); // методы обработки события мыши при перемещении мыши
    /*virtual*/ void mouseReleaseEvent(
        ); // методы обработки событий мыши при отжатии клавиши мыши
    /*virtual*/ void
    wheelEvent(QWheelEvent *pe); // метод обработки событий колесика мыши
    /*virtual*/ void keyPressEvent(
        QKeyEvent
            *pe); // методы обработки события при нажатии определенной клавиши

  public:
    int p = 1;
    double (*f) (double,double);
    double (*f_dx) (double,double);
    double (*f_dy) (double,double);
    double valuex (double t, double* x, int nx, double* c,int j0);
    double valuey (double t, double* y, int ny, double* c,int i0);
    void m_15x(int nx, double* x, double* f, double* cx,double y0,int j0);
    void m_15y(int ny, double* y, double* f, double* cy,double x0,int i0);
    void c_15x(double* f, double* x, double* dx, double* cx,int j0);
    void c_15y(double* f, double* y, double* dy, double* cy,int i0);
    Scene3D(QWidget *parent = 0); // конструктор класса

//public slots:
//  void q1 ();

};
#endif
