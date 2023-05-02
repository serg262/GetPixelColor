#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "hook.h"

#include <QPixmap>
#include <QScreen>
#include <QDesktopWidget>
#include <QMessageBox>
#include <QDebug>

#define OCR_NORMAL          32512


wchar_t *convertCharArrayToLPCWSTR(const char* charArray)
{
    wchar_t* wString=new wchar_t[4096];
    MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
    return wString;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    def_arrow_cur = CopyCursor(LoadCursor(nullptr, IDC_ARROW));

    QString str(QString(PRO_FILE_PWD) + "/image/cursor.cur");


        QByteArray ba = str.toLocal8Bit();
        const char *c_str = ba.data();



    HCURSOR my_cur = LoadCursorFromFile(convertCharArrayToLPCWSTR(c_str));
    if(!my_cur)
    {
        QMessageBox::warning(this,"Warning", "Ошибка загрузки файла!!!");
        return;
    }

  //  SetCursor(my_cur);
   // DestroyCursor(my_cur);

    HANDLE load = (HCURSOR)LoadImage(0, MAKEINTRESOURCE(32513), IMAGE_CURSOR, 0, 0, LR_SHARED);
    Ic_old_edit = (HCURSOR)CopyImage(load, IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR);
    Ic_new_edit = LoadCursorFromFile(convertCharArrayToLPCWSTR(c_str));
    SetSystemCursor(Ic_new_edit, 32513);

    this->setWindowFlags(Qt::WindowStaysOnTopHint);

    Hook* hook = new Hook(this);
    connect(hook, &Hook::hookEvent, this, &MainWindow::mouse_hook_event);

}

MainWindow::~MainWindow()
{
    SetSystemCursor(Ic_old_edit, 32513);

    DestroyCursor(Ic_old_edit);
    DestroyCursor(Ic_new_edit);
    delete ui;
}

void MainWindow::mouse_hook_event()
{
    QPoint mousePos = QCursor::pos();

    qDebug()<<mousePos.x();
    qDebug()<<this->pos().x();

    if(mousePos.x() >= this->pos().x())
        return;

    QScreen *screen = QApplication::primaryScreen();

    QPixmap pix = screen->grabWindow(QApplication::desktop()->winId());

    QImage img = pix.toImage();

    QRgb rgb = img.pixel(mousePos.x(), mousePos.y());
    QColor *color = new QColor;
    color->setRgb(rgb);

    ui->lineEdit_R->setText(QString::number(color->red()));
    ui->lineEdit_G->setText(QString::number(color->green()));
    ui->lineEdit_B->setText(QString::number(color->blue()));
    ui->lineEdit_HTML->setText(color->name());

    ui->lineEdit_X->setText(QString::number(mousePos.x()));
    ui->lineEdit_Y->setText(QString::number(mousePos.y()));

    ui->label_color->setStyleSheet(QString("background-color: %0; border: 1px solid black;").arg(color->name()));
}


