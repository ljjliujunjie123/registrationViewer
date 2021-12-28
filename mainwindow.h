#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include "UI/ImageShownController.h"
#include "UI/ProcessNodesContainer.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:

private:
    Ui::MainWindow *ui;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menu;
    QAction *actionOpenFileOne;
    QAction *actionOpenFileTwo;

    ImageShownController *imageShownController;
    ProcessNodesContainer *processNodesContainer;

    void retranslateUI();

    void serverListener();
};
#endif // MAINWINDOW_H
