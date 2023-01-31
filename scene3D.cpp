#include <QtGui> // подключаем модуль QtGui
//#include <QtCore>     // подключаем модуль QtCore
//#include <QtOpenGL>   // подключаем модуль QtOpenGL
#include "scene3D.h" // подключаем заголовочный файл scene3D.h
#include <math.h> // подключаем математическую библиотеку
#include <QAction>
#define NX 20
#define NY 20
#define A -1
#define B 1
//const static float pi = 3.141593; // глобальная переменная

static double f_0(double x, double y)
{
    return pow(x, 0) * pow(y, 0);
}
static double f_0_dx(double x, double y)
{
    return 0 * x * y;
}
static double f_0_dy(double x, double y)
{
    return 0 * x * y;
}

static double f_1(double x, double y)
{
    return x * pow(y, 0);
}
static double f_1_dx(double x, double y)
{
    return pow(x, 0) * pow(y, 0);
}
static double f_1_dy(double x, double y)
{
    return 0 * x * y;
}

static double f_2(double x, double y)
{
    return y * pow(x, 0);
}
static double f_2_dx(double x, double y)
{
    return 0 * x * y;
}
static double f_2_dy(double x, double y)
{
    return pow(x, 0) * pow(y, 0);
}

static double f_3(double x, double y)
{
    return x + y;
}
static double f_3_dx(double x, double y)
{
    return pow(x, 0) * pow(y, 0);
}
static double f_3_dy(double x, double y)
{
    return pow(x, 0) * pow(y, 0);
}

static double f_4(double x, double y)
{
    return sqrt(1+x * x + y * y);
}
static double f_4_dx(double x, double y)
{
    return (x) / (sqrt(1+x * x + y * y));
}
static double f_4_dy(double x, double y)
{
    return (y) / (sqrt(1+x * x + y * y));
}

static double f_5(double x, double y)
{
    return x * x + y * y;
}
static double f_5_dx(double x, double y)
{
    return 2 * x * pow(y, 0);
}
static double f_5_dy(double x, double y)
{
    return 2 * y * pow(x, 0);
}

static double f_6(double x, double y)
{
    return exp(x * x - y * y);
}
static double f_6_dx(double x, double y)
{
    return 2 * x * exp(x * x - y * y);
}
static double f_6_dy(double x, double y)
{
    return -2 * y * exp(x * x - y * y);
}

static double f_7(double x, double y)
{
    return 1 / (25 * (x * x + y * y) + 1);
}
static double f_7_dx(double x, double y)
{
    return -50 * x / ((25 * (x * x + y * y) + 1) * (25 * (x * x + y * y) + 1));
}
static double f_7_dy(double x, double y)
{
    return -50 * y / ((25 * (x * x + y * y) + 1) * (25 * (x * x + y * y) + 1));
}

Scene3D::Scene3D(QWidget* parent /*= 0*/)
    : QGLWidget(parent)
    , xRot(-90)
    , yRot(0)
    , zRot(0)
    , zTra(0)
    , nSca(1) // конструктор класса Scene3D
{
    // setFormat(QGLFormat(QGL::DepthBuffer)); // использовать буфер глубины
    // установлено по умолчанию в контексте

    // передает дальше указатель на объект pwgt
}

/*virtual*/ void Scene3D::initializeGL() // инициализация
{
    //initializeOpenGLFunctions();
    qglClearColor(Qt::white); // цвет для очистки буфера изображения - здесь
    // просто фон окна
    glEnable(GL_DEPTH_TEST); // устанавливает режим проверки глубины пикселей
    glShadeModel(GL_FLAT); // отключает режим сглаживания цветов
    glEnable(GL_CULL_FACE); // устанавливается режим, когда строятся только
    // внешние поверхности

    glEnableClientState(GL_VERTEX_ARRAY); // активизация массива вершин
    glEnableClientState(GL_COLOR_ARRAY); // активизация массива цветов вершин
}

/*virtual*/ void Scene3D::resizeGL(int nWidth, int nHeight) // окно виджета
{
    glMatrixMode(GL_PROJECTION); // устанавливает текущей проекционную матрицу
    glLoadIdentity(); // присваивает проекционной матрице единичную матрицу

    GLfloat ratio = (GLfloat)nHeight / (GLfloat)nWidth; // отношение высоты окна виджета к его ширине

    // мировое окно
    if (nWidth >= nHeight)
        glOrtho(-1.0 / ratio, 1.0 / ratio, -1.0, 1.0, -10.0,
            1.0); // параметры видимости ортогональной проекции
    else
        glOrtho(-1.0, 1.0, -1.0 * ratio, 1.0 * ratio, -10.0,
            1.0); // параметры видимости ортогональной проекции
    // плоскости отсечения (левая, правая, верхняя, нижняя, передняя, задняя)

    // glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 10.0); // параметры видимости
    // перспективной проекции плоскости отсечения (левая, правая, верхняя,
    // нижняя, ближняя, дальняя)

    // поле просмотра
    glViewport(0, 0, (GLint)nWidth, (GLint)nHeight);
}

/*virtual*/ void Scene3D::paintGL() // рисование
{
    // glClear(GL_COLOR_BUFFER_BIT); // окно виджета очищается текущим цветом
    // очистки
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // очистка буфера изображения и глубины

    glMatrixMode(GL_MODELVIEW); // устанавливает положение и ориентацию матрице
    // моделирования
    glLoadIdentity(); // загружает единичную матрицу моделирования

    // последовательные преобразования
    glScalef(nSca, nSca, nSca); // масштабирование
    glTranslatef(0.0f, zTra, 0.0f); // трансляция
    glRotatef(xRot, 1.0f, 0.0f, 0.0f); // поворот вокруг оси X
    glRotatef(yRot, 0.0f, 1.0f, 0.0f); // поворот вокруг оси Y
    glRotatef(zRot, 0.0f, 0.0f, 1.0f); // поворот вокруг оси Z

    //drawAxis(); // рисование осей координат
    //drawFigure(); // нарисовать фигуру
    graph();
    //drawAxis(); // рисование осей координат
    //renderText(0, 20, "TEXT111");
}


/*virtual*/ void
Scene3D::mousePressEvent(QMouseEvent* pe) // нажатие клавиши мыши
{
    // при нажатии пользователем кнопки мыши переменной ptrMousePosition будет
    // присвоена координата указателя мыши
    ptrMousePosition = pe->pos();

    // ptrMousePosition = (*pe).pos(); // можно и так написать
}

//Scene3D::mouseReleaseEvent(QMouseEvent *pe) // отжатие клавиши мыши
//{
//    // некоторые функции, которые должны выполняться при отжатии клавиши мыши
//}
/*virtual*/ void
Scene3D::mouseReleaseEvent() // отжатие клавиши мыши
{
    // некоторые функции, которые должны выполняться при отжатии клавиши мыши
}

/*virtual*/ void
Scene3D::mouseMoveEvent(QMouseEvent* pe) // изменение положения стрелки мыши
{
    xRot += 180 / nSca * (GLfloat)(pe->y() - ptrMousePosition.y()) / height(); // вычисление углов поворота
    zRot += 180 / nSca * (GLfloat)(pe->x() - ptrMousePosition.x()) / width();

    ptrMousePosition = pe->pos();

    updateGL(); // обновление изображения
}

/*virtual*/ void Scene3D::wheelEvent(QWheelEvent* pe) // вращение колёсика мыши
{
    if ((pe->delta()) > 0)
        scale_plus();
    else if ((pe->delta()) < 0)
        scale_minus();

    updateGL(); // обновление изображения
}

/*virtual*/ void
Scene3D::keyPressEvent(QKeyEvent* pe) // нажатие определенной клавиши
{
    switch (pe->key()) {
    case Qt::Key_Plus:
        scale_plus(); // приблизить сцену
        break;

    case Qt::Key_Equal:
        scale_plus(); // приблизить сцену
        break;

    case Qt::Key_Minus:
        scale_minus(); // удалиться от сцены
        break;

    case Qt::Key_Up:
        rotate_up(); // повернуть сцену вверх
        break;

    case Qt::Key_Down:
        rotate_down(); // повернуть сцену вниз
        break;

    case Qt::Key_9:
        rotate_left(); // повернуть сцену влево
        break;

    case Qt::Key_8:
        rotate_right(); // повернуть сцену вправо
        break;

    case Qt::Key_Z:
        translate_down(); // транслировать сцену вниз
        break;

    case Qt::Key_X:
        translate_up(); // транслировать сцену вверх
        break;

    case Qt::Key_Space: // клавиша пробела
        defaultScene(); // возвращение значений по умолчанию
        break;

    case Qt::Key_Escape: // клавиша "эскейп"
        this->close(); // завершает приложение
        break;

    case Qt::Key_1:
        p = p + 1;
        q = (q + 1) % 3;
        break;
    case Qt::Key_2:
        p = p + 1;
        s = s + 1;
        a = a / 2;
        b = b / 2;
        break;
    case Qt::Key_3:
        p = p + 1;
        s = s - 1;
        a = a * 2;
        b = b * 2;
        break;
    case Qt::Key_4:
        p = p + 1;
        nx = nx * 2;
        ny = ny * 2;
        break;
    case Qt::Key_5:
        p = p + 1;
        nx = nx / 2;
        ny = ny / 2;
        break;
    case Qt::Key_6:
        p = p + 1;
        pp++;
        break;
    case Qt::Key_7:
        p = p + 1;
        pp--;
        break;

    case Qt::Key_0: //смена функции
        p = p + 1;
        func_id = (func_id + 1) % 8;
        switch (func_id) {
        case 0:
            f = f_0;
            f_dx = f_0_dx;
            f_dy = f_0_dy;
            f_name = "f (x,y) = 1";
            break;
        case 1:
            f = f_1;
            f_dx = f_1_dx;
            f_dy = f_1_dy;
            f_name = "f (x,y) = x";
            break;
        case 2:
            f = f_2;
            f_dx = f_2_dx;
            f_dy = f_2_dy;
            f_name = "f (x,y) = y";
            break;
        case 3:
            f = f_3;
            f_dx = f_3_dx;
            f_dy = f_3_dy;
            f_name = "f (x,y) = x+y";
            break;
        case 4:
            f = f_4;
            f_dx = f_4_dx;
            f_dy = f_4_dy;
            f_name = "f (x,y) = (1+x^2+y^2)^(1/2)";
            break;
        case 5:
            f = f_5;
            f_dx = f_5_dx;
            f_dy = f_5_dy;
            f_name = "f (x,y) = x^2+y^2";
            break;
        case 6:
            f = f_6;
            f_dx = f_6_dx;
            f_dy = f_6_dy;
            f_name = "f (x,y) = e^(x^2-y^2)";
            break;
        case 7:
            f = f_7;
            f_dx = f_7_dx;
            f_dy = f_7_dy;
            f_name = "f (x,y) = 1/(25(x^2+y^2)+1)";
            break;
        }
        break;
    }

    updateGL(); // обновление изображения
}

void Scene3D::scale_plus() // приблизить сцену
{
    nSca = nSca * 1.1;
}

void Scene3D::scale_minus() // удалиться от сцены
{
    nSca = nSca / 1.1;
}

void Scene3D::rotate_up() // повернуть сцену вверх
{
    xRot += 1.0;
}

void Scene3D::rotate_down() // повернуть сцену вниз
{
    xRot -= 1.0;
}

void Scene3D::rotate_left() // повернуть сцену влево
{
    zRot += 15;
}

void Scene3D::rotate_right() // повернуть сцену вправо
{
    zRot -= 15;
}

void Scene3D::translate_down() // транслировать сцену вниз
{
    zTra -= 0.05;
}

void Scene3D::translate_up() // транслировать сцену вверх
{
    zTra += 0.05;
}

void Scene3D::defaultScene() // наблюдение сцены по умолчанию
{
    xRot = -90;
    yRot = 0;
    zRot = 0;
    zTra = 0;
    nSca = 1;
}

void Scene3D::drawAxis() // построить оси координат
{
    glLineWidth(3.0f); // устанавливаю ширину линии приближённо в пикселях
    // до вызова команды ширина равна 1 пикселю по умолчанию

    glColor4f(1.00f, 0.00f, 0.00f,
        1.0f); // устанавливается цвет последующих примитивов
    // ось x красного цвета
    glBegin(GL_LINES); // построение линии
    glVertex3f(1.0f, 0.0f, 0.0f); // первая точка
    glVertex3f(-1.0f, 0.0f, 0.0f); // вторая точка
    glEnd();

    QColor halfGreen(0, 128, 0, 255);
    qglColor(halfGreen);
    glBegin(GL_LINES);
    // ось y зеленого цвета
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, -1.0f, 0.0f);

    glColor4f(0.00f, 0.00f, 1.00f, 1.0f);
    // ось z синего цвета
    glVertex3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -1.0f);
    glEnd();
}

double raznx(double* f, double* x, int i, int j, int j0, int ny)
{
    if (j < i)
        std::swap(j, i);
    return (f[j * ny + j0] - f[i * ny + j0]) / (x[j] - x[i]);
}
double razny(double* f, double* y, int i, int j, int i0, int ny)
{
    if (j < i)
        std::swap(j, i);
    return (f[i0 * ny + j] - f[i0 * ny + i]) / (y[j] - y[i]);
}

void Scene3D::c_15x(double* f, double* x, double* dx, double* cx, int j0)
{
    for (int i = 0; i < nx; i++) {
        cx[j0 * nx * 4 + 4 * i] = f[i * nx + j0];
        cx[j0 * nx * 4 + 4 * i + 1] = dx[nx * j0 + i];
        cx[j0 * nx * 4 + 4 * i + 2] = (3 * raznx(f, x, i, i + 1, j0, nx) - 2 * dx[nx * j0 + i] - dx[nx * j0 + i + 1]) / (x[i + 1] - x[i]);
        cx[j0 * nx * 4 + 4 * i + 3] = (dx[nx * j0 + i] + dx[nx * j0 + i + 1] - 2 * raznx(f, x, i, i + 1, j0, nx)) / ((x[i + 1] - x[i]) * (x[i + 1] - x[i]));
    }
}

void Scene3D::c_15y(double* f, double* y, double* dy, double* cy, int i0)
{
    for (int i = 0; i < ny; i++) {
        cy[i0 * ny * 4 + 4 * i] = f[i0 * ny + i];
        cy[i0 * ny * 4 + 4 * i + 1] = dy[ny * i0 + i];
        cy[i0 * ny * 4 + 4 * i + 2] = (3 * razny(f, y, i, i + 1, i0, ny) - 2 * dy[ny * i0 + i] - dy[ny * i0 + i + 1]) / (y[i + 1] - y[i]);
        cy[i0 * ny * 4 + 4 * i + 3] = (dy[ny * i0 + i] + dy[ny * i0 + i + 1] - 2 * razny(f, y, i, i + 1, i0, ny)) / ((y[i + 1] - y[i]) * (y[i + 1] - y[i]));
    }
}

//интерполяция кубическими многочленами Эрмита x

void Scene3D::m_15x(int nx, double* x, double* f, double* cx, double y0, int j0)
{
    double* dx = new double[(nx + 1) * ny];
    for (int i = 0; i < nx; i++) {
        dx[nx * j0 + i] = f_dx(x[i], y0);
    }
    c_15x(f, x, dx, cx, j0);

    delete[] dx;
}

//интерполяция кубическими многочленами Эрмита y
void Scene3D::m_15y(int ny, double* y, double* f, double* cy, double x0, int i0)
{
    double* dy = new double[(nx + 1) * ny];
    for (int i = 0; i < ny; i++) {
        dy[ny * i0 + i] = f_dy(x0, y[i]);
    }
    c_15y(f, y, dy, cy, i0);

    delete[] dy;
}

double Scene3D::valuex(double t, double* x, int nx, double* c, int j0)
{

    int i;
    for (i = 0; i < nx - 1; i++) {
        if (fabs(t - x[i]) < 1e-10 || fabs(t - x[i + 1]) < 1e-10)
            break;
        else if (t > x[i] && t < x[i + 1])
            break;
    }
    return c[j0 * nx * 4 + 4 * i] + c[j0 * nx * 4 + 4 * i + 1] * (t - x[i]) + c[j0 * nx * 4 + 4 * i + 2] * (t - x[i]) * (t - x[i]) + c[j0 * nx * 4 + 4 * i + 3] * (t - x[i]) * (t - x[i]) * (t - x[i]);
}
double Scene3D::valuey(double t, double* y, int ny, double* c, int i0)
{

    int i;
    for (i = 0; i < ny - 1; i++) {
        if (fabs(t - y[i]) < 1e-10 || fabs(t - y[i + 1]) < 1e-10)
            break;
        else if (t > y[i] && t < y[i + 1])
            break;
    }
    return c[i0 * ny * 4 + 4 * i] + c[i0 * ny * 4 + 4 * i + 1] * (t - y[i]) + c[i0 * ny * 4 + 4 * i + 2] * (t - y[i]) * (t - y[i]) + c[i0 * ny * 4 + 4 * i + 3] * (t - y[i]) * (t - y[i]) * (t - y[i]);
}


void Scene3D::graph() // построить график
{
    double vx = (b - a) / (nx);
    double vy = (b - a) / (ny);
    double* f_xy;
    double* x;
    double* y;
    double max = 0;
    double maxf = 0, minf = 0;
    double maxmod = 0;
    //double i, j;
    int i0, j0;
    if (p == 1) {
        nx = NX;
        ny = NY;
        a = A;
        b = B;
        q = 0;
        s = 0;
        pp = 0;
        f = f_0;
        f_dx = f_0_dx;
        f_dy = f_0_dy;
        func_id = 0;
        f_name = "f (x,y) = 1";
    }
    glColor4f(0.00f, 0.00f, 0.00f,
        1.0f);
    renderText(0, 15, (std::string("k = ") + std::to_string(func_id)).c_str());
    renderText(40, 15, f_name);
    renderText(0, 45, (std::string("s = ") + std::to_string(s)).c_str());
    renderText(0, 55, (std::string("nx = ") + std::to_string(nx)).c_str());
    renderText(50, 55, (std::string("ny = ") + std::to_string(ny)).c_str());
    renderText(0, 65, (std::string("p = ") + std::to_string(pp)).c_str());

    renderText(0, 315, std::string("0-изменить функцию ").c_str());
    renderText(0, 325, std::string("1-изменить состав графиков ").c_str());
    renderText(0, 335, std::string("2-уменьшить масштаб ").c_str());
    renderText(0, 345, std::string("3-увеличить масштаб ").c_str());
    renderText(0, 355, std::string("4-увеличить число точек ").c_str());
    renderText(0, 365, std::string("5-уменьшить число точек ").c_str());
    renderText(0, 375, std::string("6-прибавить максимум ").c_str());
    renderText(0, 385, std::string("7-вычесть максимум ").c_str());
    renderText(0, 395, std::string("8-вращать по часовой ").c_str());
    renderText(0, 405, std::string("9-вращать против часовой ").c_str());
    glColor4f(1.00f, 1.00f, 0.00f,
        1.0f);
    renderText(0, 420, std::string("Исходная функция ").c_str());
    glColor4f(0.00f, 1.00f, 1.00f,
        1.0f);
    renderText(0, 430, std::string("Аппроксимация  ").c_str());
    glColor4f(0.00f, 0.00f, 0.00f,
        1.0f);

    f_xy = new double[nx * ny * 2];
    x = new double[nx];
    y = new double[ny];
    //массив значений x
    for (i0 = 0; i0 < nx; i0 += 1) {
        x[i0] = a + (i0 * vx);
    }
    //массив значений y
    for (j0 = 0; j0 < ny; j0 += 1) {
        y[j0] = a + (j0 * vy);
    }
    //массив значений функции
    for (i0 = 0; i0 < nx; i0 += 1) {
        for (j0 = 0; j0 < ny; j0 += 1) {
            f_xy[i0 * ny + j0] = f(a + (i0 * vx), a + (j0 * vy));
            if (i0 != nx / 2 || j0 != ny / 2) {
                if (fabs(f_xy[i0 * ny + j0]) > max)
                    max = fabs(f_xy[i0 * ny + j0]);
            }
        }
    }
    f_xy[(nx / 2) * ny + (ny / 2)] = f(a + ((nx / 2) * vx), a + ((ny / 2) * vy)) + 0.1 * pp * max;
    if (fabs(f_xy[(nx / 2) * ny + (ny / 2)]) > max)
        max = fabs(f_xy[(nx / 2) * ny + (ny / 2)]);

    renderText(0, 25, (std::string("max = ") + std::to_string(max)).c_str());

    glLineWidth(3.0f);
    glColor4f(1.00f, 1.00f, 0.00f,
        1.0f);

    glBegin(GL_LINES); // построение графика функции
    if (q == 0) {
        for (i0 = 0; i0 < nx - 1; i0 += 1) {
            glVertex3f(a + (i0 * vx), a + ((ny - 1) * vy), f_xy[i0 * ny + ny - 1]);
            glVertex3f(a + ((i0 + 1) * vx), a + ((ny - 1) * vy), f_xy[(i0 + 1) * ny + ny - 1]);
        }
        for (j0 = 0; j0 < ny - 1; j0 += 1) {
            glVertex3f(a + ((nx - 1) * vx), a + (j0 * vy), f_xy[(nx - 1) * ny + j0]);
            glVertex3f(a + ((nx - 1) * vx), a + ((j0 + 1) * vy), f_xy[(nx - 1) * ny + j0 + 1]);
        }
        for (i0 = 0; i0 < nx - 1; i0 += 1) {
            for (j0 = 0; j0 < ny - 1; j0 += 1) {
                glVertex3f(a + (i0 * vx), a + (j0 * vy), f_xy[i0 * ny + j0]);
                glVertex3f(a + ((i0 + 1) * vx), a + (j0 * vy), f_xy[(i0 + 1) * ny + j0]);

                glVertex3f(a + (i0 * vx), a + (j0 * vy), f_xy[i0 * ny + j0]);
                glVertex3f(a + (i0 * vx), a + ((j0 + 1) * vy), f_xy[i0 * ny + j0 + 1]);
                if (maxf < f_xy[i0 * ny + j0])
                    maxf = f_xy[i0 * ny + j0];
                if (minf > f_xy[i0 * ny + j0])
                    minf = f_xy[i0 * ny + j0];
            }
            if (maxf < f_xy[i0 * ny + ny - 1])
                maxf = f_xy[i0 * ny + ny - 1];
            if (minf > f_xy[i0 * ny + ny - 1])
                minf = f_xy[i0 * ny + ny - 1];
        }
        if (maxf < f_xy[(nx - 1) * ny + ny - 1])
            maxf = f_xy[(nx - 1) * ny + ny - 1];
        if (minf > f_xy[(nx - 1) * ny + ny - 1])
            minf = f_xy[(nx - 1) * ny + ny - 1];
        if (fabs(maxf) > fabs(minf)) {
            maxmod = fabs(maxf);
        }
        else {
            maxmod = fabs(minf);
        }
    }
    glEnd();




    double* cx = new double[4 * nx * ny];
    for (j0 = 0; j0 < ny - 1; j0 += 1) {
        m_15x(nx, x, f_xy, cx, y[j0], j0); //считаю многочлены от x при фиксированном y
    }
    double* cy = new double[4 * nx * ny];
    for (i0 = 0; i0 < nx - 1; i0 += 1) {
        m_15y(ny, y, f_xy, cy, y[i0], i0); //считаю многочлены от x при фиксированном x
    }

    glLineWidth(3.0f);
    glColor4f(0.00f, 1.00f, 1.00f,
        1.0f);
    glBegin(GL_LINES);
    if (q == 1) {

        for (i0 = 0; i0 < nx - 1; i0 += 1) {
            glVertex3f(a + (i0 * vx), a + (0 * vy), valuey(a + (0 * vy), y, ny, cy, i0));
            glVertex3f(a + (i0 * vx), a + ((0 + 1) * vy), valuey(a + ((0 + 1) * vy), y, ny, cy, i0));

            glVertex3f(a + (i0 * vx), a + ((ny - 1) * vy), valuey(a + ((ny - 1) * vy), y, ny, cy, i0));
            glVertex3f(a + ((i0 + 1) * vx), a + ((ny - 1) * vy), f_xy[(i0 + 1) * ny + ny - 1]);
        }
        for (j0 = 0; j0 < ny - 1; j0 += 1) {
            glVertex3f(a + ((nx - 1) * vx), a + (j0 * vy), valuex(a + ((nx - 1) * vx), x, nx, cx, j0));
            glVertex3f(a + ((nx - 1) * vx), a + ((j0 + 1) * vy), f_xy[(nx - 1) * ny + j0 + 1]);
        }

        for (j0 = 0; j0 < ny - 1; j0 += 1) {
            glVertex3f(a + (0 * vx), a + (j0 * vy), valuex(a + (0 * vx), x, nx, cx, j0));
            glVertex3f(a + ((0 + 1) * vx), a + (j0 * vy), valuex(a + ((0 + 1) * vx), x, nx, cx, j0));
            for (i0 = 0; i0 < nx - 1; i0 += 1) {
                //if(i0==nx/2-1 ){fl1=0;} else {fl1=1;}
               // if(i0==nx/2){fl2=1;} else {fl2=0;}
                glVertex3f(a + (i0 * vx) + vx / 2, a + (j0 * vy), valuex(a + (i0 * vx) + vx / 2, x, nx, cx, j0));
                glVertex3f(a + ((i0 + 1) * vx) + vx / 2, a + (j0 * vy), valuex(a + ((i0 + 1) * vx) + vx / 2, x, nx, cx, j0));

                glVertex3f(a + (i0 * vx), a + (j0 * vy) + vy / 2, valuey(a + (j0 * vy) + vy / 2, y, ny, cy, i0));
                glVertex3f(a + (i0 * vx), a + ((j0 + 1) * vy) + vy / 2, valuey(a + ((j0 + 1) * vy) + vy / 2, y, ny, cy, i0));
                if (maxf < valuey(y[j0], y, ny, cy, i0))
                    maxf = valuey(y[j0], y, ny, cy, i0);
                if (minf > valuey(y[j0], y, ny, cy, i0))
                    minf = valuey(y[j0], y, ny, cy, i0);
            }
            if (maxf < valuey(y[ny - 1], y, ny, cy, i0))
                maxf = valuey(y[ny - 1], y, ny, cy, i0);
            if (minf > valuey(y[ny - 1], y, ny, cy, i0))
                minf = valuey(y[ny - 1], y, ny, cy, i0);
        }
        if (maxf < valuey(y[ny - 1], y, ny, cy, nx - 1))
            maxf = valuey(y[ny - 1], y, ny, cy, nx - 1);
        if (minf > valuey(y[ny - 1], y, ny, cy, nx - 1))
            minf = valuey(y[ny - 1], y, ny, cy, nx - 1);
        if (fabs(maxf) > fabs(minf)) {
            maxmod = fabs(maxf);
        }
        else {
            maxmod = fabs(minf);
        }
    }
    if (q == 2) {
        for (i0 = 0; i0 < nx - 1; i0 += 1) {
            glVertex3f(a + (i0 * vx), a + (0 * vy), valuey(a + (0 * vy), y, ny, cy, i0) - f(a + (i0 * vx), a + (0 * vy)));
            glVertex3f(a + (i0 * vx), a + ((0 + 1) * vy), valuey(a + ((0 + 1) * vy), y, ny, cy, i0) - f(a + (i0 * vx), a + ((0 + 1) * vy)));
        }
        for (j0 = 0; j0 < ny - 1; j0 += 1) {
            glVertex3f(a + (0 * vx), a + (j0 * vy), valuex(a + (0 * vx), x, nx, cx, j0) - f(a + (0 * vx), a + (j0 * vy)));
            glVertex3f(a + ((0 + 1) * vx), a + (j0 * vy), valuex(a + ((0 + 1) * vx), x, nx, cx, j0) - f(a + ((0 + 1) * vx), a + (j0 * vy)));
            for (i0 = 0; i0 < nx - 1; i0 += 1) {
                glVertex3f(a + (i0 * vx) + vx / 2, a + (j0 * vy), valuex(a + (i0 * vx) + vx / 2, x, nx, cx, j0) - f(a + (i0 * vx) + vx / 2, a + (j0 * vy)));
                glVertex3f(a + ((i0 + 1) * vx) + vx / 2, a + (j0 * vy), valuex(a + ((i0 + 1) * vx) + vx / 2, x, nx, cx, j0) - f(a + ((i0 + 1) * vx) + vx / 2, a + (j0 * vy)));

                glVertex3f(a + (i0 * vx), a + (j0 * vy) + vy / 2, valuey(a + (j0 * vy) + vy / 2, y, ny, cy, i0) - f(a + (i0 * vx), a + (j0 * vy) + vy / 2));
                glVertex3f(a + (i0 * vx), a + ((j0 + 1) * vy) + vy / 2, valuey(a + ((j0 + 1) * vy) + vy / 2, y, ny, cy, i0) - f(a + (i0 * vx), a + ((j0 + 1) * vy) + vy / 2));
             //   if (maxf < valuey(a + (j0 * vy) + vy / 2, y, ny, cy, i0) - f(a + (i0 * vx), a + (j0 * vy) + vy / 2))
             //       maxf = valuey(a + (j0 * vy) + vy / 2, y, ny, cy, i0) - f(a + (i0 * vx), a + (j0 * vy) + vy / 2);
             //   if (minf > valuey(a + (j0 * vy) + vy / 2, y, ny, cy, i0) - f(a + (i0 * vx), a + (j0 * vy) + vy / 2))
             //       minf = valuey(a + (j0 * vy) + vy / 2, y, ny, cy, i0) - f(a + (i0 * vx), a + (j0 * vy) + vy / 2);


           //     if (maxf < valuex(a + (i0 * vx) + vx/2, x, nx, cx, j0) - f(a + (i0 * vx) + vx/2 , a + (j0 * vy)))
           //         maxf = valuex(a + (i0 * vx) + vx/2 , x, nx, cx, j0) - f(a + (i0 * vx) + vx/2 , a + (j0 * vy));
           //     if (minf > valuex(a + (i0 * vx) + vx/2 , x, nx, cx, j0) - f(a + (i0 * vx) + vx/2 , a + (j0 * vy)))
           //         minf = valuex(a + (i0 * vx) + vx/2 , x, nx, cx, j0) - f(a + (i0 * vx) + vx/2 , a + (j0 * vy));
            }
            //if(maxf<valuey(a+(j0*vy)+vy/2,y,ny,cy,nx-1)-f(a+((nx-1)*vx),a+(j0*vy)+vy/2)) maxf=valuey(a+(j0*vy)+vy/2,y,ny,cy,nx-1)-f(a+((nx-1)*vx),a+(j0*vy)+vy/2);
            //if(minf>valuey(a+(j0*vy)+vy/2,y,ny,cy,nx-1)-f(a+((nx-1)*vx),a+(j0*vy)+vy/2)) minf=valuey(a+(j0*vy)+vy/2,y,ny,cy,nx-1)-f(a+((nx-1)*vx),a+(j0*vy)+vy/2);
        }

        for (j0 = 1; j0 < ny - 2; j0 += 1){
            for (i0 = 1; i0 < nx - 2; i0 += 1){
                if (maxf < valuex(a + (i0 * vx) + vx/2, x, nx, cx, j0) - f(a + (i0 * vx) + vx/2 , a + (j0 * vy)))
                    maxf = valuex(a + (i0 * vx) + vx/2 , x, nx, cx, j0) - f(a + (i0 * vx) + vx/2 , a + (j0 * vy));
                if (minf > valuex(a + (i0 * vx) + vx/2 , x, nx, cx, j0) - f(a + (i0 * vx) + vx/2 , a + (j0 * vy)))
                    minf = valuex(a + (i0 * vx) + vx/2 , x, nx, cx, j0) - f(a + (i0 * vx) + vx/2 , a + (j0 * vy));
            }
        }







        //if(maxf<valuey(a+((ny-1)*vy)+vy/2,y,ny,cy,nx-1)-f(a+((nx-1)*vx),a+((ny-1)*vy)+vy/2)) maxf=valuey(a+((ny-1)*vy)+vy/2,y,ny,cy,nx-1)-f(a+((nx-1)*vx),a+((ny-1)*vy)+vy/2);
        //if(minf>valuey(a+((ny-1)*vy)+vy/2,y,ny,cy,nx-1)-f(a+((nx-1)*vx),a+((ny-1)*vy)+vy/2)) minf=valuey(a+((ny-1)*vy)+vy/2,y,ny,cy,nx-1)-f(a+((nx-1)*vx),a+((ny-1)*vy)+vy/2);
        if (fabs(maxf) > fabs(minf)) {
            maxmod = fabs(maxf);
        }
        else {
            maxmod = fabs(minf);
        }
    }


    glEnd();
    glColor4f(0.00f, 0.00f, 0.00f,
        1.0f);
    char kk[256];
    sprintf(kk,"%e",maxmod);
    renderText(0, 35, (std::string("max{|Fmax|,|Fmin|} = ") + kk).c_str());

    glLineWidth(3.0f); // устанавливаю ширину линии приближённо в пикселях
    // до вызова команды ширина равна 1 пикселю по умолчанию

    glColor4f(1.00f, 0.00f, 0.00f,
        1.0f); // устанавливается цвет последующих примитивов
    // ось x красного цвета
    glBegin(GL_LINES); // построение линии
    glVertex3f(a, 0.0f, 0.0f); // первая точка
    glVertex3f(b, 0.0f, 0.0f); // вторая точка
    glEnd();

    QColor halfGreen(0, 128, 0, 255);
    qglColor(halfGreen);
    glBegin(GL_LINES);
    // ось y зеленого цвета
    glVertex3f(0.0f, a, 0.0f);
    glVertex3f(0.0f, b, 0.0f);

    glColor4f(0.00f, 0.00f, 1.00f, 1.0f);
    // ось z синего цвета
    glVertex3f(0.0f, 0.0f, maxf);
    glVertex3f(0.0f, 0.0f, minf);
    glEnd();
}
