#include <QtWidgets>
#include "mainwindow.h"
#include "painter.h"

const int canvas_width = 1100;
const int canvas_height = 600;
const int btn_size = 50;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("逻辑电路设计");
    setWindowIcon(QIcon(":/window.png"));
    resize(1280, 720);//设置窗口大小为1280*720


//    //About Menu
//    aboutMenu = menuBar()->addMenu(tr("关于"));

    /* 建立并链接菜单 */
        /* 建立菜单栏 */
    menubar = new QMenuBar(this);//建立一个以主窗口为parent的menubar
    this->setMenuBar(menubar);//设置窗口的菜单栏为刚创建的menubar
    QMenu *menu_file = menuBar()->addMenu("文件");//在菜单栏上添加“文件”菜单
        /* 建立动作 */
    QAction *new_file = new QAction(QIcon(":/new_file.png"), "新建", this);
    QAction *open_file = new QAction(QIcon(":/open_file.png"), "打开", this);
    QAction *save_file = new QAction(QIcon(":/save.png"), "保存", this);
    QAction *save_as_file = new QAction(QIcon(":/save_as.png"), "另存为", this);
        /* 设置动作快捷键 */
    new_file->setShortcuts(QKeySequence::New);
    open_file->setShortcuts(QKeySequence::Open);
    save_file->setShortcuts(QKeySequence::Save);
    save_as_file->setShortcuts(QKeySequence::SaveAs);//另存为的快捷键ctrl+shift+s没有实装？
        /* 将动作添加到“文件”菜单中 */
    menu_file->addAction(new_file);
    menu_file->addAction(open_file);
    menu_file->addAction(save_file);
    menu_file->addAction(save_as_file);
        /* 将动作与槽链接 */
    connect(new_file, SIGNAL(triggered()), this, SLOT(_NewFile()));
    connect(open_file, SIGNAL(triggered()), this, SLOT(_OpenFile()));
    connect(save_file, SIGNAL(triggered()), this, SLOT(_SaveFile()));
    connect(save_as_file, SIGNAL(triggered()), this, SLOT(_SaveAsFile()));
        /* 设置状态栏提示信息 */
    new_file->setStatusTip("新建电路原理图");
    open_file->setStatusTip("打开电路原理图");
    save_file->setStatusTip("保存电路原理图");
    save_as_file->setStatusTip("另存为电路原理图");

    QMenu *menu_about = menuBar()->addMenu("帮助");//在菜单栏上添加“关于”菜单
    QAction *connect_us = new QAction("联系我们",this);
    menu_about->addAction(connect_us);
    connect(connect_us, SIGNAL(triggered()), this, SLOT(_ConnectUs()));

    /* 建立并链接状态栏 */
    statusbar = new QStatusBar(this);//建立一个以主窗口为parent的statusbar
    this->setStatusBar(statusbar);//设置窗口的状态栏为刚创建的statusbar



    /* 创建并配置画布停靠窗 */
        /* 创建并设置画布停靠窗 */
    canvasDock = new QDockWidget("设计原理图", this);
    canvasDock->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
    canvasDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    canvasDock->setMinimumSize(canvas_width, canvas_height);
    setCentralWidget(canvasDock);
        /* 在停靠窗中创建画布 */
    painter = new PaintWidget(canvasDock);//画布的parent是停靠窗
    painter->setScaledContents(true);//允许自动缩放
        /* 初始化画布 */
    QImage img;
    painter->setImage(img);
    painter->setPenWidth(2);
    painter->setPenColor(Qt::darkBlue);
    painter->setPixmap(QPixmap::fromImage(img));//??有用，但还不知道具体什么用
    painter->setShape(0);
    painter->resize(canvas_width*2, canvas_height*2);//设置画布大小
        /* 为画布添加滚动条效果 */
    QScrollArea *scroller = new QScrollArea(this);//为什么不是以painter或canvasDock为parent?
    scroller->setBackgroundRole(QPalette::Dark);//?
    scroller->setAlignment(Qt::AlignCenter);//设置中间对齐
    scroller->setWidget(painter);//设置滚动范围为哪个组件
    canvasDock->setWidget(scroller);

    /* 创建并设置toolbox */
        /* 创建并设置toolbox停靠窗 */
    toolboxDock = new QDockWidget("元件库", this);
    addDockWidget(Qt::LeftDockWidgetArea, toolboxDock);//停靠窗配置在左侧
    splitDockWidget(toolboxDock, canvasDock, Qt::Horizontal);//?
        /* 创建按钮 */
    QPushButton *and2_btn = new QPushButton(QIcon(":/and2.png"), "", this);//为什么parent是mainwindow?
    QPushButton *or2_btn = new QPushButton(QIcon(":/or2.png"), "", this);
    QPushButton *and3_btn = new QPushButton(QIcon(":/and3.png"), "", this);
    QPushButton *or3_btn = new QPushButton(QIcon(":/or3.png"), "", this);
    QPushButton *and4_btn = new QPushButton(QIcon(":/and4.png"), "", this);
    QPushButton *or4_btn = new QPushButton(QIcon(":/or4.png"), "", this);
    QPushButton *xor_btn = new QPushButton(QIcon(":/xor.png"), "", this);
    QPushButton *inv_btn = new QPushButton(QIcon(":/inv.png"), "", this);
    QPushButton *h_line_btn = new QPushButton(QIcon(":/h_line.png"), "", this);
    QPushButton *v_line_btn = new QPushButton(QIcon(":/v_line.png"), "", this);
    QPushButton *free_line_btn = new QPushButton(QIcon(":/free_line.png"), "", this);
    QPushButton *dot_btn = new QPushButton(QIcon(":/dot.png"), "", this);
    QPushButton *erase_btn = new QPushButton(QIcon(":/eraser.png"), "", this);
    QPushButton *delete_btn = new QPushButton(QIcon(":/delete.png"), "", this);
    and2_btn->setFixedSize(btn_size, btn_size);
    or2_btn->setFixedSize(btn_size, btn_size);
    and3_btn->setFixedSize(btn_size, btn_size);
    or3_btn->setFixedSize(btn_size, btn_size);
    and4_btn->setFixedSize(btn_size, btn_size);
    or4_btn->setFixedSize(btn_size, btn_size);
    xor_btn->setFixedSize(btn_size, btn_size);
    inv_btn->setFixedSize(btn_size, btn_size);
    h_line_btn->setFixedSize(btn_size, btn_size);
    v_line_btn->setFixedSize(btn_size, btn_size);
    free_line_btn->setFixedSize(btn_size, btn_size);
    dot_btn->setFixedSize(btn_size, btn_size);
    erase_btn->setFixedSize(btn_size, btn_size);
    delete_btn->setFixedSize(btn_size, btn_size);
    and2_btn->setToolTip("二输入与门");
    or2_btn->setToolTip("二输入或门");
    and3_btn->setToolTip("三输入与门");
    or3_btn->setToolTip("三输入或门");
    and4_btn->setToolTip("四输入与门");
    or4_btn->setToolTip("四输入或门");
    xor_btn->setToolTip("异或门");
    inv_btn->setToolTip("非门");
    h_line_btn->setToolTip("水平连接线");
    v_line_btn->setToolTip("垂直连接线");
    free_line_btn->setToolTip("自由连接线");
    dot_btn->setToolTip("电路连接点");
    erase_btn->setToolTip("区域清除");
    and2_btn->setStatusTip("绘制二输入与门");
    or2_btn->setStatusTip("绘制二输入或门");
    and3_btn->setStatusTip("绘制三输入与门");
    or3_btn->setStatusTip("绘制三输入或门");
    and4_btn->setStatusTip("绘制四输入与门");
    or4_btn->setStatusTip("绘制四输入或门");
    xor_btn->setStatusTip("绘制异或门");
    inv_btn->setStatusTip("绘制非门");
    h_line_btn->setStatusTip("绘制水平连接线");
    v_line_btn->setStatusTip("绘制垂直连接线");
    free_line_btn->setStatusTip("绘制自由连接线");
    dot_btn->setStatusTip("绘制电路连接点");
    erase_btn->setStatusTip("清除指定区域");
    delete_btn->setStatusTip("清除整张画布");
    //and2_btn->setObjectName("custombutton");???
        /* 将按钮排列在停靠窗中 */
    QGridLayout *toolbox_layout = new QGridLayout();
    toolbox_layout->setAlignment(Qt::AlignTop);
    toolbox_layout->addWidget(and2_btn, 0, 0);
    toolbox_layout->addWidget(or2_btn, 0, 1);
    toolbox_layout->addWidget(and3_btn, 1, 0);
    toolbox_layout->addWidget(or3_btn, 1, 1);
    toolbox_layout->addWidget(and4_btn, 2, 0);
    toolbox_layout->addWidget(or4_btn, 2, 1);
    toolbox_layout->addWidget(xor_btn, 3, 0);
    toolbox_layout->addWidget(inv_btn, 3, 1);
    toolbox_layout->addWidget(h_line_btn, 4, 0);
    toolbox_layout->addWidget(v_line_btn, 4, 1);
    toolbox_layout->addWidget(free_line_btn, 5, 0);
    toolbox_layout->addWidget(dot_btn, 5, 1);
    toolbox_layout->addWidget(erase_btn, 6, 0);
    toolbox_layout->addWidget(delete_btn, 6, 1);
    QWidget *toolWidget = new QWidget(toolboxDock);
    toolWidget->setLayout(toolbox_layout);
    toolboxDock->setWidget(toolWidget);
        /* 链接按钮 */
    designLib = new QButtonGroup();
    designLib->addButton(and2_btn, 1);
    designLib->addButton(or2_btn, 2);
    designLib->addButton(and3_btn, 3);
    designLib->addButton(or3_btn, 4);
    designLib->addButton(and4_btn, 5);
    designLib->addButton(or4_btn, 6);
    designLib->addButton(xor_btn, 7);
    designLib->addButton(inv_btn, 8);
    designLib->addButton(h_line_btn, 9);
    designLib->addButton(v_line_btn, 10);
    designLib->addButton(free_line_btn, 11);
    designLib->addButton(dot_btn, 12);
    designLib->addButton(erase_btn, 13);
    designLib->addButton(delete_btn, 14);
    connect(designLib, SIGNAL(buttonClicked(int)), this, SLOT(designLibSelect(int)));

    /* 创建并配置参数停靠窗 */
    penArgDock = new QToolBar();
    penArgDock = addToolBar("笔尖参数设置");//???
    penArgDock->setMovable(true);
    QPushButton *add_width_btn = new QPushButton(QIcon(":/add_width.png"), "", this);
    QPushButton *minus_width_btn = new QPushButton(QIcon(":/minus_width.png"), "", this);
    QPushButton *red_btn = new QPushButton(QIcon(":/red.png"), "", this);
    QPushButton *blue_btn = new QPushButton(QIcon(":/blue.png"), "", this);
    QPushButton *black_btn = new QPushButton(QIcon(":/black.png"), "", this);

    add_width_btn->resize(btn_size, btn_size);
    minus_width_btn->resize(btn_size, btn_size);
    red_btn->resize(btn_size, btn_size);
    blue_btn->resize(btn_size, btn_size);
    black_btn->resize(btn_size, btn_size);
    connect(add_width_btn, SIGNAL(clicked()), this, SLOT(add_pen_width()));
    connect(minus_width_btn, SIGNAL(clicked()), this, SLOT(minus_pen_width()));
    connect(red_btn, SIGNAL(clicked()), this, SLOT(set_red()));
    connect(blue_btn, SIGNAL(clicked()), this, SLOT(set_blue()));
    connect(black_btn, SIGNAL(clicked()), this, SLOT(set_black()));
    QHBoxLayout *penArgLayout = new QHBoxLayout();
    penArgLayout->setAlignment(Qt::AlignLeft);
    penArgLayout->addWidget(add_width_btn);
    penArgLayout->addWidget(minus_width_btn);
    penArgLayout->addWidget(red_btn);
    penArgLayout->addWidget(blue_btn);
    penArgLayout->addWidget(black_btn);
    QWidget *penArgWidget = new QWidget();
    penArgWidget->setLayout(penArgLayout);
    penArgDock->addWidget(penArgWidget);




    /*
    QImage img(nullptr);
    painter->setImage(img);
    painter->resize(1000, 1000);
    painter->setShape(PaintWidget::Pen);
    painter->setPenWidth(2);
    */
}

MainWindow::~MainWindow()
{

}
