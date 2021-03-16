#pragma once

#include <QWidget>
#include "ui_ctrlwidget.h"
#include "ctrlwidget.h"

class CtrlWidget : public QWidget
{
	Q_OBJECT

public:
	CtrlWidget(QWidget *parent = Q_NULLPTR);
	~CtrlWidget();

private:
	Ui::CtrlWidget ui;
};
