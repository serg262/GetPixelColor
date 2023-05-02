#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <windows.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

void mouse_hook_event();


private:
    Ui::MainWindow *ui;
    HCURSOR def_arrow_cur;

    HCURSOR Ic_old_edit, Ic_new_edit;
};
#endif // MAINWINDOW_H
