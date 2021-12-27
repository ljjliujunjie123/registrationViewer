#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include "UI/ImageShownContainer.h"
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

    ImageShownContainer *imageShownContainer;
    ProcessNodesContainer *processNodesContainer;

    void retranslateUI();
};
#endif // MAINWINDOW_H
