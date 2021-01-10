#include <QtGui>
#include <QtWidgets>
#include <QMainWindow>
#include "painter.h"
#include "mainwindow.h"

PaintWidget::PaintWidget(QWidget *parent) : QLabel (parent)
{
    drawing = false;
}
void PaintWidget::setImage(QImage img)
{
    QImage img1 = QImage(canvas_width*2, canvas_height*2, QImage::Format_ARGB32);//ARGB支持透明像素
    img1.fill(qRgb(255, 255, 255));
    if (img.isNull())
        img = img1;
    image = img;
    tmpImg = img;
    paint(img);
}
QImage PaintWidget::getImage()
{
    if (!image.isNull())
        return image;
}
void PaintWidget::setPenColor(QColor color)
{
    penColor = color;
}
QColor PaintWidget::getPenColor() const
{
    return penColor;
}
void PaintWidget::setPenWidth(int width)
{
    penWidth = width;
}
int PaintWidget::getPenWidth() const
{
    return penWidth;
}
void PaintWidget::setShape(int type)
{
    drawtype = type;
}
void PaintWidget::paintEvent(QPaintEvent *)
{
    //qDebug() << "paintEvent" << endl;
    QPainter painter(this);
    if (drawing)
        painter.drawImage(0, 0, tmpImg);
    else
        painter.drawImage(0, 0, image);
}
void PaintWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        startPoint = event->pos();
        drawing = true;
    }
}
void PaintWidget::mouseMoveEvent(QMouseEvent *event)
{
    //qDebug() << startPoint << endPoint << endl;
    if (event->buttons() & Qt::LeftButton){
        endPoint = event->pos();
        tmpImg = image;
        paint(tmpImg);
    }
}
void PaintWidget::mouseReleaseEvent(QMouseEvent *)
{
    drawing = false;
    paint(image);
}
void PaintWidget::paint(QImage &CurrImg)
{
    QPainter qpainter(&CurrImg);
    QPen pen;
    pen.setWidth(penWidth);
    pen.setColor(penColor);
    qpainter.setPen(pen);
    qpainter.setRenderHint(QPainter::Antialiasing, true); //抗锯齿？

    switch (drawtype) {
    case 1:
        //draw and2
        qpainter.drawPixmap(0,0,50,30,QPixmap(":/and2.png"));
        break;
    case 2:
        //draw or2
        qpainter.drawPixmap(0,0,50,30,QPixmap(":/or2.png"));
        break;
    case 3:
        //draw and3
        qpainter.drawPixmap(0,0,50,30,QPixmap(":/and3.png"));
        break;
    case 4:
        //draw or3
        qpainter.drawPixmap(0,0,50,30,QPixmap(":/or3.png"));
        break;
    case 5:
        //draw and4
        qpainter.drawPixmap(0,0,50,30,QPixmap(":/and4.png"));
        break;
    case 6:
        //draw or4
        qpainter.drawPixmap(0,0,50,30,QPixmap(":/or4.png"));
        break;
    case 7:
        //draw xor
        qpainter.drawPixmap(0,0,50,30,QPixmap(":/xor.png"));
        break;
    case 8:
        //draw inv
        qpainter.drawPixmap(0,0,50,30,QPixmap(":/inv.png"));
        break;
    case 9:
        //draw h_line
        qpainter.drawPixmap(0,0,50,30,QPixmap(":/h_line.png"));
        break;
    case 10:
        //draw v_line
        qpainter.drawPixmap(0,0,50,30,QPixmap(":/v_line.png"));
        break;
    case 11:
        //draw free_line
        qpainter.drawLine(startPoint, endPoint);
        break;
    case 12:
        //draw dot
        qpainter.drawPixmap(0,0,50,30,QPixmap(":/dot.png"));
        break;
    case 13:
        //draw blank(to clear)
        qpainter.drawPixmap(0,0,canvas_width, canvas_height,QPixmap(":/blank.png"));
        break;
    }
    update();
}
