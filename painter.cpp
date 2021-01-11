#include <QtGui>
#include <QtWidgets>
#include <QMainWindow>
#include "painter.h"
#include "mainwindow.h"

#define ITEM_WIDTH 100
#define ITEM_HEIGHT 50

PaintWidget::PaintWidget(QWidget *parent) : QLabel (parent)
{
    drawing = false;
}
void PaintWidget::setImage(QImage img)  //设置画布
{
    QImage img1 = QImage(canvas_width*2, canvas_height*2, QImage::Format_ARGB32);//ARGB支持透明像素
    img1.fill(qRgb(255, 255, 255));//白色
    if (img.isNull())
        img = img1;
    image = img;    //真实的画布
    tmpImg = img;   //临时画布，用于实现绘制（鼠标拖动）时的效果预览
    paint(img);
}
QImage PaintWidget::getImage()  //获得画布
{
    if (!image.isNull())
        return image;
}
void PaintWidget::setPenColor(QColor color) //设置笔的颜色
{
    penColor = color;
}
QColor PaintWidget::getPenColor() const     //获得笔的颜色，const保证数据不被修改
{
    return penColor;
}
void PaintWidget::setPenWidth(int width)    //设置笔的宽度
{
    penWidth = width;
}
int PaintWidget::getPenWidth() const        //获得笔的宽度
{
    return penWidth;
}
void PaintWidget::setShape(int type)        //获得绘制图片的类型
{
    drawtype = type;
}
void PaintWidget::paintEvent(QPaintEvent *) //画笔的绘画事件
{
    //qDebug() << "paintEvent" << endl;
    QPainter painter(this);
    if (drawing)
        painter.drawImage(0, 0, tmpImg);    //先画在临时画布上
    else
        painter.drawImage(0, 0, image);     //鼠标release时，将临时画布内容画到真实画布上
}
void PaintWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        startPoint = event->pos();                      //鼠标按下时，获得绘图起始点数据
        drawing = true;                                 //在临时画布上绘图
    }
}
void PaintWidget::mouseMoveEvent(QMouseEvent *event)
{
    //qDebug() << startPoint << endPoint << endl;
    if (event->buttons() & Qt::LeftButton){
        endPoint = event->pos();                        //鼠标拖动时，当前点为绘图终点数据
        tmpImg = image;
        paint(tmpImg);
    }
}
void PaintWidget::mouseReleaseEvent(QMouseEvent *)
{
    drawing = false;
    paint(image);                                       //鼠标release时，在真实画布上绘制

}
void PaintWidget::paint(QImage &CurrImg)
{
    QPainter qpainter(&CurrImg);                        //现在临时画布上绘图
    QPainter eraser(&image);                            //擦除时无需预览，直接在真实画布上进行
    //qpainter对象初始化
    QPen pen;
    pen.setWidth(penWidth);
    pen.setColor(penColor);
    qpainter.setPen(pen);
    qpainter.setRenderHint(QPainter::Antialiasing, true); //抗锯齿

    switch (drawtype) {
    case 1:
        //draw and2 调用drawPixmap函数，使用图片实现绘图，下同
        qpainter.drawPixmap(endPoint.x()-30,endPoint.y()-15,ITEM_WIDTH,ITEM_HEIGHT,QPixmap(":/and2.png"));
        break;
    case 2:
        //draw or2
        qpainter.drawPixmap(endPoint.x()-30,endPoint.y()-15,ITEM_WIDTH,ITEM_HEIGHT,QPixmap(":/or2.png"));
        break;
    case 3:
        //draw and3
        qpainter.drawPixmap(endPoint.x()-30,endPoint.y()-15,ITEM_WIDTH,ITEM_HEIGHT,QPixmap(":/and3.png"));
        break;
    case 4:
        //draw or3
        qpainter.drawPixmap(endPoint.x()-30,endPoint.y()-15,ITEM_WIDTH,ITEM_HEIGHT,QPixmap(":/or3.png"));
        break;
    case 5:
        //draw and4
        qpainter.drawPixmap(endPoint.x()-30,endPoint.y()-15,ITEM_WIDTH,ITEM_HEIGHT,QPixmap(":/and4.png"));
        break;
    case 6:
        //draw or4
        qpainter.drawPixmap(endPoint.x()-30,endPoint.y()-15,ITEM_WIDTH,ITEM_HEIGHT,QPixmap(":/or4.png"));
        break;
    case 7:
        //draw xor
        qpainter.drawPixmap(endPoint.x()-30,endPoint.y()-15,ITEM_WIDTH,ITEM_HEIGHT,QPixmap(":/xor.png"));
        break;
    case 8:
        //draw inv
        qpainter.drawPixmap(endPoint.x()-30,endPoint.y()-15,ITEM_WIDTH,ITEM_HEIGHT,QPixmap(":/inv.png"));
        break;
    case 9:
        //draw h_line
        qpainter.drawLine(startPoint.x(),startPoint.y(),endPoint.x(),startPoint.y());   //y坐标不变，绘制水平直线
        break;
    case 10:
        //draw v_line
        qpainter.drawLine(startPoint.x(),startPoint.y(),startPoint.x(),endPoint.y());   //x坐标不变，绘制垂直直线
        break;
    case 11:
        //draw free_line
        qpainter.drawLine(startPoint, endPoint);    //调用QPainter的drawLine函数绘制任意倾斜的直线
        break;
    case 12:
        //draw dot
        qpainter.drawPixmap(endPoint.x()-49,endPoint.y()-22,ITEM_WIDTH,ITEM_HEIGHT,QPixmap(":/node.png"));
        break;
    case 13:
        //erase
        eraser.drawPixmap(endPoint.x()-30,endPoint.y()-15,ITEM_WIDTH,ITEM_WIDTH,QPixmap(":/blank.png"));
        break;
    case 14:
        //clear all
        qpainter.drawPixmap(0,0,canvas_width*2, canvas_height*2,QPixmap(":/blank_all.png"));
        break;
    }
    update();
}
