#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "painter.h"

extern const int canvas_width;
extern const int canvas_height;
extern const int btn_size;

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    PaintWidget *painter;
    QMenuBar *menubar;//菜单栏
    QStatusBar *statusbar;//状态栏
    //QToolBar *maintoolbar;//

    QDockWidget *canvasDock;//画布停靠窗
    QDockWidget *toolboxDock;//工具箱停靠窗
    QToolBar *penArgDock;//笔尖参数停靠窗
    QButtonGroup *designLib;//工具箱中的设计库
    QButtonGroup *penSizeChg;//修改笔尖尺寸

    QString path_of_curr_file;
    //Statues
    QLabel *tempStatus;
    QLabel *permStatus;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    /* 四个slot分别对应菜单上的四个动作 */
    void _NewFile();
    void _OpenFile();
    void _SaveFile();
    void _SaveAsFile();
    void _ConnectUs();
    void designLibSelect(int id);
    void add_pen_width();
    void minus_pen_width();
    void chg_pen_size(int sign);
    void set_red();
    void set_blue();
    void set_black();
};

#endif // MAINWINDOW_H
