/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionPrimary;
    QAction *actionMiddle;
    QAction *actionSenior;
    QAction *actionUser_defined;
    QAction *actionQuit;
    QAction *actionHelp;
    QAction *actionAbout;
    QAction *actionHow_to_play;
    QAction *action2p;
    QWidget *centralWidget;
    QWidget *widget;
    QLabel *label;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QMenuBar *menuBar;
    QMenu *menuGame;
    QMenu *menuAbout;
    QMenu *menu2p;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(372, 374);
        actionPrimary = new QAction(MainWindow);
        actionPrimary->setObjectName(QStringLiteral("actionPrimary"));
        actionMiddle = new QAction(MainWindow);
        actionMiddle->setObjectName(QStringLiteral("actionMiddle"));
        actionSenior = new QAction(MainWindow);
        actionSenior->setObjectName(QStringLiteral("actionSenior"));
        actionUser_defined = new QAction(MainWindow);
        actionUser_defined->setObjectName(QStringLiteral("actionUser_defined"));
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        actionHelp = new QAction(MainWindow);
        actionHelp->setObjectName(QStringLiteral("actionHelp"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionHow_to_play = new QAction(MainWindow);
        actionHow_to_play->setObjectName(QStringLiteral("actionHow_to_play"));
        action2p = new QAction(MainWindow);
        action2p->setObjectName(QStringLiteral("action2p"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 0, 190, 255));
        widget->setAutoFillBackground(true);
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(0, 0, 190, 255));
        label->setAutoFillBackground(true);
        label->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/IMAGE/background.png")));
        label->setScaledContents(true);
        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(10, 150, 91, 111));
        pushButton->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/IMAGE/start.png);"));
        pushButton_2 = new QPushButton(widget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(100, 150, 91, 111));
        pushButton_2->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/IMAGE/quit.png);"));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 372, 23));
        menuGame = new QMenu(menuBar);
        menuGame->setObjectName(QStringLiteral("menuGame"));
        menuAbout = new QMenu(menuBar);
        menuAbout->setObjectName(QStringLiteral("menuAbout"));
        menu2p = new QMenu(menuBar);
        menu2p->setObjectName(QStringLiteral("menu2p"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuGame->menuAction());
        menuBar->addAction(menuAbout->menuAction());
        menuBar->addAction(menu2p->menuAction());
        menuGame->addAction(actionPrimary);
        menuGame->addAction(actionMiddle);
        menuGame->addAction(actionSenior);
        menuGame->addAction(actionUser_defined);
        menuGame->addAction(actionQuit);
        menuAbout->addAction(actionHelp);
        menuAbout->addAction(actionHow_to_play);
        menuAbout->addAction(actionAbout);
        menu2p->addAction(action2p);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        actionPrimary->setText(QApplication::translate("MainWindow", "Primary", Q_NULLPTR));
        actionMiddle->setText(QApplication::translate("MainWindow", "Middle", Q_NULLPTR));
        actionSenior->setText(QApplication::translate("MainWindow", "Senior", Q_NULLPTR));
        actionUser_defined->setText(QApplication::translate("MainWindow", "User-defined", Q_NULLPTR));
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", Q_NULLPTR));
        actionHelp->setText(QApplication::translate("MainWindow", "Help", Q_NULLPTR));
        actionAbout->setText(QApplication::translate("MainWindow", "About  author", Q_NULLPTR));
        actionHow_to_play->setText(QApplication::translate("MainWindow", "How to play", Q_NULLPTR));
        action2p->setText(QApplication::translate("MainWindow", "\345\217\214\344\272\272\346\250\241\345\274\217", Q_NULLPTR));
        label->setText(QString());
        pushButton->setText(QString());
        pushButton_2->setText(QString());
        menuGame->setTitle(QApplication::translate("MainWindow", "game", Q_NULLPTR));
        menuAbout->setTitle(QApplication::translate("MainWindow", "about", Q_NULLPTR));
        menu2p->setTitle(QApplication::translate("MainWindow", "\346\233\264\345\244\232\346\250\241\345\274\217", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
