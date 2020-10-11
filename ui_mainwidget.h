/********************************************************************************
** Form generated from reading UI file 'mainwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWIDGET_H
#define UI_MAINWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mainwidget
{
public:
    QPushButton *pushButton;

    void setupUi(QWidget *mainwidget)
    {
        if (mainwidget->objectName().isEmpty())
            mainwidget->setObjectName(QStringLiteral("mainwidget"));
        mainwidget->resize(463, 346);
        pushButton = new QPushButton(mainwidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(170, 150, 75, 23));

        retranslateUi(mainwidget);

        QMetaObject::connectSlotsByName(mainwidget);
    } // setupUi

    void retranslateUi(QWidget *mainwidget)
    {
        mainwidget->setWindowTitle(QApplication::translate("mainwidget", "Form", Q_NULLPTR));
        pushButton->setText(QApplication::translate("mainwidget", "\345\215\225\344\272\272\346\250\241\345\274\217", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class mainwidget: public Ui_mainwidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWIDGET_H
