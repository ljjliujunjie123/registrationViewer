//
// Created by 19956875375 on 2021/12/22.
//

#ifndef REGISTRATIONVIEWER_NPUSHBUTTONEXTEND_H
#define REGISTRATIONVIEWER_NPUSHBUTTONEXTEND_H
///  @file NPushButtonExtend.h
///  @brief QPushButton扩展
///  @author project4gogo@163.com
///  @date 2018


#include <QObject>
#include <QPushButton>
#include <QAction>
#include <QList>
using namespace std;
///
/// \brief The NPushButtonExtend class
/// 在原有基础上增加了菜单功能，通过左键点击指定区域，弹出菜单选项。
/// 菜单可固定，也可动态生成
///
///
class NPushButtonExtend : public QPushButton
{
public:
    enum
    {
        MENU_STATIC = 0,
        MENU_DYNAMIC,
    };

    enum
    {
        MENU_BUTTON_LEFT = 0,
        MENU_BUTTON_RIGHT,
    };
    Q_OBJECT
public:
    NPushButtonExtend(QWidget *parent);
    ~NPushButtonExtend();

    ///菜单动态生成，通过发送信号signalRequestMenuy请求菜单
    void SetDynamicMenu();

    ///菜单固定
    void SetStaticMenu();

    ///点击弹出菜单的区域大小
    void SetExtendSize(QRect rc);

    ///设置弹出菜单使用的按键
    /// @param leftOrRight 按键标识 0:左键 1:右键
    void SetMenuButton(int leftOrRight);

    ///增加菜单项
    /// @param icon 图标
    /// @param text 菜单项名称
    /// @param checked 初始状态是否为选中，当checkable=true时有效
    /// @param checkable 菜单项是否为checkable模式
    /// @return 返回值为菜单项的索引
    int AddMenuItem(QIcon &icon, QString text, bool checked = false, bool checkable = false);
    int AddMenuItem(QString text, bool checked = false, bool checkable = false);
    void AddSeparator();

    ///设置菜单项显示的文字
    void SetMenuItemText(int index, QString text);

    QAction *GetMenuItem(int index);
    QAction *GetMenuItem(QString text);


    signals:
            ///需要弹出菜单时，发出的请求设置菜单信息
            void signalRequestMenu();

            ///选中了菜单项时发出
            /// @param index 选中的菜单项索引，按加入顺序排列
            /// @param text  菜单项显示的文字
            void signalMenuClicked(QString text);

protected slots:
            void OnMenuClicked(bool checked);

    void OnShowMenu();
protected:
    void ReleaseMenuItem();

    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent *e) override;

private:
    QList<QAction*> m_menuItemList;
    QRect m_menuPopRc;

    bool m_bUsingSataicMenu = MENU_STATIC;
    int m_menuButton = MENU_BUTTON_RIGHT;


};

#endif //REGISTRATIONVIEWER_NPUSHBUTTONEXTEND_H
