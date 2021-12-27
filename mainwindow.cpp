#include <QLabel>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QIcon"
#include "QVBoxLayout"
#include "QSplitter"
#include "QSizePolicy"
#include "QAction"
#include "qcoreapplication.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setObjectName("MainWindow");
    resize(600,800);
    centralWidget = new QWidget(this);
    centralWidget->setFixedWidth(600);
    setCentralWidget(centralWidget);

    setWindowIcon(QIcon(R"(D:\respository\MRViewer\ui_source\win_title_icon.png)"));
    setWindowTitle("Registration Viewer");

    menuBar = new QMenuBar(this);
    menu = new QMenu(menuBar);
    menuBar->setGeometry(0,0,this->width(),30);
    setMenuBar(menuBar);

    actionOpenFileOne = new QAction(this);
    connect(actionOpenFileOne, &QAction::triggered, this,
            [&](){
//        auto dirPath = QFileDialog::getExistingDirectory(this, "选择series","");
        auto path = QFileDialog::getOpenFileName(this, "", "*");
        imageShownController->showFirstImage(path.toStdString());
    });
    actionOpenFileTwo = new QAction(this);
    connect(actionOpenFileTwo, &QAction::triggered, this,
            [&](){
//                auto dirPath = QFileDialog::getExistingDirectory(this, "选择series","");
                auto path = QFileDialog::getOpenFileName(this, "", "*");
                imageShownController->showSecondImage(path.toStdString());
    });
    menu->addAction(actionOpenFileOne);
    menu->addAction(actionOpenFileTwo);
    menuBar->addAction(menu->menuAction());

    // 设置状态栏 只能有一个
    auto stBar= new QStatusBar;
    setStatusBar(stBar);
    // 放标签控件
    auto label = new QLabel("状态栏", this);
    stBar->addWidget(label);

    auto* splitter = new QSplitter(centralWidget);
    splitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    imageShownController = new ImageShownController(this->centralWidget);
    processNodesContainer = new ProcessNodesContainer(splitter);

    splitter->addWidget(processNodesContainer);
    splitter->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    auto* mainWinLayout = new QVBoxLayout();
    mainWinLayout->setContentsMargins(0,0,0,0);
    mainWinLayout->setSpacing(0);
    mainWinLayout->addWidget(splitter);
    centralWidget->setLayout(mainWinLayout);

    retranslateUI();
    show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::retranslateUI() {
    menu->setTitle(qApp->translate("MainWindow","文件"));
    actionOpenFileOne->setText(qApp->translate("MainWindow","打开待匹配文件"));
    actionOpenFileTwo->setText(qApp->translate("MainWindow","打开匹配目标"));
}



