//
// Created by 19956875375 on 2021/12/22.
//

#include "npushbuttonextend.h"

#include <QDebug>
#include <QMouseEvent>
#include <QTimer>
#include <QPoint>
#include <QMenu>

#define N_PUSH_BUTTON_EXTEND_NAME "n_push_button_extend_meu_obj_name"
NPushButtonExtend::NPushButtonExtend(QWidget *parent)
    :QPushButton(parent)
{
    setObjectName("NPushButton");
    setStyleSheet("border: none;");
    m_menuPopRc = QRect(0, 0, width(), height());
}

NPushButtonExtend::~NPushButtonExtend()
{
    ReleaseMenuItem();
}

void NPushButtonExtend::SetDynamicMenu()
{
    m_bUsingSataicMenu = MENU_DYNAMIC;
}

void NPushButtonExtend::SetStaticMenu()
{
    m_bUsingSataicMenu = MENU_STATIC;
}

int NPushButtonExtend::AddMenuItem(QIcon &icon, QString text, bool checked, bool checkable)
{
    QAction *pAction = new QAction(icon, text, this);
    connect(pAction, &QAction::triggered, this, &NPushButtonExtend::OnMenuClicked);
    m_menuItemList.push_back(pAction);

    return m_menuItemList.size()-1;
}

int NPushButtonExtend::AddMenuItem(QString text, bool checked, bool checkable)
{
    QIcon icon;
    return AddMenuItem(icon, text, checked, checkable);
}

void NPushButtonExtend::AddSeparator()
{
    m_menuItemList.push_back(nullptr);
}

void NPushButtonExtend::SetMenuItemText(int index, QString text)
{
    if(index >= 0 && index < m_menuItemList.size())
    {
        QAction *pAction = m_menuItemList[index];
        if(nullptr != pAction)
        {
            pAction->setText(text);
        }
    }
}

QAction *NPushButtonExtend::GetMenuItem(int index)
{
    QAction *p = nullptr;
    if((index >= 0) && (index < m_menuItemList.size()))
    {
        p = m_menuItemList[index];
    }
    return p;
}

QAction *NPushButtonExtend::GetMenuItem(QString text)
{
    QAction *p = nullptr;
    for(int i = 0; i < m_menuItemList.size(); i++)
    {
        if(0 == text.compare(m_menuItemList[i]->text()))
        {
            p = m_menuItemList[i];
            break;
        }
    }
    return p;
}

void NPushButtonExtend::SetExtendSize(QRect rc)
{
    m_menuPopRc = rc;
}

void NPushButtonExtend::SetMenuButton(int leftOrRight)
{
    m_menuButton = leftOrRight;
}

void NPushButtonExtend::OnMenuClicked(bool checked)
{
    QAction *p = reinterpret_cast<QAction*>(sender());
    for(int i = 0; i < m_menuItemList.size(); i++)
    {
        if(p == m_menuItemList[i])
        {
            emit signalMenuClicked(p->text());
            break;
        }
    }
}

void NPushButtonExtend::OnShowMenu()
{
    ///动态生成时，释放上一次生成的菜单
    if(MENU_DYNAMIC == m_bUsingSataicMenu)
    {
        ReleaseMenuItem();
    }

    /// 请求菜单
    emit signalRequestMenu();

    ///生成菜单
    if(m_menuItemList.size() > 0)
    {
        QMenu *menu = new QMenu(this);
        menu->setObjectName(N_PUSH_BUTTON_EXTEND_NAME);
        for(int i = 0; i < m_menuItemList.size(); i++)
        {
            if(nullptr != m_menuItemList[i])
            {
                menu->addAction(m_menuItemList[i]);
            }
            else
            {
                menu->addSeparator();
            }
        }
        menu->exec(QCursor::pos());

        delete menu;
    }
}

void NPushButtonExtend::ReleaseMenuItem()
{
    for(int i = 0; i < m_menuItemList.size(); i++)
    {
        QAction *p = m_menuItemList[i];
        if(nullptr != p)
        {
            p->deleteLater();
        }
    }
    m_menuItemList.clear();
}




void NPushButtonExtend::mousePressEvent(QMouseEvent *e)
{
    bool bUsed = false;
    do
    {
        if((MENU_BUTTON_LEFT == m_menuButton) && (Qt::LeftButton != e->button()))
        {
            break;
        }

        if((MENU_BUTTON_RIGHT == m_menuButton) && (Qt::RightButton != e->button()))
        {
            break;
        }

        if(m_menuPopRc.contains(e->pos().x(), e->pos().y()))
        {
            QTimer::singleShot(1, this, SLOT(OnShowMenu()));
            bUsed = true;
        }

    }while(false);

    if(false == bUsed)
    {
        QPushButton::mousePressEvent(e);
    }
}
