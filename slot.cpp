#include "mainwindow.h"

void MainWindow::_NewFile()
{
    QImage img = QImage(canvas_width*2, canvas_height*2, QImage::Format_RGB32);//新建一个图片当画布
    img.fill(qRgb(255, 255, 255));//这个用来当画布的图片填充为白色
    path_of_curr_file = "";//不设置当前路径
    painter->setImage(img);
}
void MainWindow::_OpenFile()
{
    /* 选择一个图片路径，打开这个图片，以这时候的路径为当前路径。显示这个图片。 */
    QString path = QFileDialog::getOpenFileName(this, "选择电路原理图", ".", "schemetic(*.jpg *.png *.bmp)");
    if (!path.isEmpty()){
        QImage *open_file = new QImage();
        if (!open_file->load(path)){
            QMessageBox::information(this, "错误", "打开文件失败！");
            delete open_file;
        }
        else{
            path_of_curr_file = path;
            painter->setImage(*open_file);
        }
    }
}
void MainWindow::_SaveFile()
{
    /* 如果之前没有经过open操作，当前文件路径是空的，需要选择一个路径保存。保存的核心操作是自带的.save() */
    if (path_of_curr_file.isEmpty()){
        QString path = QFileDialog::getSaveFileName(this, "保存电路原理图", ".", "schemetic(*.jpg *.png *.bmp)");
        if (!path.isEmpty())
            path_of_curr_file = path;
    }
    QImage save_file = painter->getImage();
    save_file.save(path_of_curr_file);
}
void MainWindow::_SaveAsFile()
{
    QString path = QFileDialog::getSaveFileName(this, "另存为电路原理图", ".", "schemetic(*.jpg *.png *.bmp)");
    if (!path.isEmpty())
        path_of_curr_file = path;
    QImage save_file = painter->getImage();
    save_file.save(path_of_curr_file);
}

void MainWindow::designLibSelect(int id)
{
    switch (id) {
    case 1:
        painter->setShape(1);
        break;
    case 2:
        painter->setShape(2);
        break;
    case 3:
        painter->setShape(3);
        break;
    case 4:
        painter->setShape(4);
        break;
    case 5:
        painter->setShape(5);
        break;
    case 6:
        painter->setShape(6);
        break;
    case 7:
        painter->setShape(7);
        break;
    case 8:
        painter->setShape(8);
        break;
    case 9:
        painter->setShape(9);
        break;
    case 10:
        painter->setShape(10);
        break;
    case 11:
        painter->setShape(11);
        break;
    case 12:
        painter->setShape(12);
        break;
    case 13:
        painter->setShape(13);
        break;
    }
}
void MainWindow::add_pen_width()
{
    qDebug() << "add_pen_width, penWidth: " << painter->getPenWidth() << endl;
    if (painter->getPenWidth() < 10)
        painter->setPenWidth(painter->getPenWidth()+1);
}
void MainWindow::minus_pen_width()
{
    qDebug() << "minus_pen_width, penWidth: " << painter->getPenWidth() << endl;
    if (painter->getPenWidth() > 1)
        painter->setPenWidth(painter->getPenWidth()-1);
}
void MainWindow::chg_pen_size(int sign)
{
    switch (sign) {
    case 0:
        if (painter->getPenWidth() < 10)
            painter->setPenWidth(painter->getPenWidth()+1);
        break;
    case 1:
        if (painter->getPenWidth() > 1)
            painter->setPenWidth(painter->getPenWidth()-1);
        break;
    }
    qDebug() << "penWidth: " << painter->getPenWidth() << endl;
}
void MainWindow::set_red()
{
    painter->setPenColor(Qt::red);
}
void MainWindow::set_blue()
{
    painter->setPenColor(Qt::darkBlue);
}
void MainWindow::set_black()
{
    painter->setPenColor(Qt::black);
}
