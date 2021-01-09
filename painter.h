#ifndef PAINTER_H
#define PAINTER_H

#include <QMainWindow>
#include <QtWidgets>

class PaintWidget : public QLabel
{
    Q_OBJECT
public:
    explicit PaintWidget(QWidget *parent = nullptr);
    void paint(QImage &CurrImg);
    void setImage(QImage img);
    QImage getImage();
    void setPenColor(QColor color);
    void setPenWidth(int width);
    void setShape(int type);
    QColor getPenColor() const;
    int getPenWidth() const;
    QImage image;
private:
    int penWidth;
    int drawtype;
    QColor penColor;
    QImage tmpImg;
    QPoint endPoint;
    QPoint startPoint;
    bool drawing;
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
};

#endif // PAINTER_H
