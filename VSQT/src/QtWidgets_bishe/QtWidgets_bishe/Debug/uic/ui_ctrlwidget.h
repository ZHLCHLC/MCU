/********************************************************************************
** Form generated from reading UI file 'ctrlwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CTRLWIDGET_H
#define UI_CTRLWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CtrlWidget
{
public:

    void setupUi(QWidget *CtrlWidget)
    {
        if (CtrlWidget->objectName().isEmpty())
            CtrlWidget->setObjectName(QStringLiteral("CtrlWidget"));
        CtrlWidget->resize(400, 300);

        retranslateUi(CtrlWidget);

        QMetaObject::connectSlotsByName(CtrlWidget);
    } // setupUi

    void retranslateUi(QWidget *CtrlWidget)
    {
        CtrlWidget->setWindowTitle(QApplication::translate("CtrlWidget", "CtrlWidget", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CtrlWidget: public Ui_CtrlWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CTRLWIDGET_H
