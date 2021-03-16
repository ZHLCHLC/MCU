#pragma once

#include <QtWidgets/QWidget>
#include "ui_qtwidgets_bishe.h"
#include "ctrlwidget.h"
class QtWidgets_bishe : public QWidget
{
    Q_OBJECT

public:
    QtWidgets_bishe(QWidget *parent = Q_NULLPTR);
	
	CtrlWidget *ctrl;
private:
    Ui::QtWidgets_bisheClass ui;
	
public slots:
	void ctrlButton_clicked();

};
