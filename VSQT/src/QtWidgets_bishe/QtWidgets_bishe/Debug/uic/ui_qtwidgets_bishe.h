/********************************************************************************
** Form generated from reading UI file 'qtwidgets_bishe.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTWIDGETS_BISHE_H
#define UI_QTWIDGETS_BISHE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtWidgets_bisheClass
{
public:
    QPushButton *ctrlwidgetButton;

    void setupUi(QWidget *QtWidgets_bisheClass)
    {
        if (QtWidgets_bisheClass->objectName().isEmpty())
            QtWidgets_bisheClass->setObjectName(QStringLiteral("QtWidgets_bisheClass"));
        QtWidgets_bisheClass->resize(949, 546);
        ctrlwidgetButton = new QPushButton(QtWidgets_bisheClass);
        ctrlwidgetButton->setObjectName(QStringLiteral("ctrlwidgetButton"));
        ctrlwidgetButton->setGeometry(QRect(20, 10, 93, 28));

        retranslateUi(QtWidgets_bisheClass);

        QMetaObject::connectSlotsByName(QtWidgets_bisheClass);
    } // setupUi

    void retranslateUi(QWidget *QtWidgets_bisheClass)
    {
        QtWidgets_bisheClass->setWindowTitle(QApplication::translate("QtWidgets_bisheClass", "QtWidgets_bishe", Q_NULLPTR));
        ctrlwidgetButton->setText(QApplication::translate("QtWidgets_bisheClass", "\346\216\247\345\210\266\347\263\273\347\273\237", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QtWidgets_bisheClass: public Ui_QtWidgets_bisheClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTWIDGETS_BISHE_H
