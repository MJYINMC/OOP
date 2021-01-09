#ifndef COUNTER_H
#define COUNTER_H

#include <QtWidgets>

class counter : public QWidget
{
    Q_OBJECT

public:
    counter(QWidget *parent = nullptr, int index = 0);
    ~counter();

private:
    int index, count;
    QPushButton *p;

signals:
    void ten_times(int index, int count);

private slots:
    void internalSlot();
};

#endif // COUNTER_H
