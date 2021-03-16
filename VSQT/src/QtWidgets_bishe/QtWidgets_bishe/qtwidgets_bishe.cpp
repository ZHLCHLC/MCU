#include "qtwidgets_bishe.h"
#include<iostream>

using namespace std;

QtWidgets_bishe::QtWidgets_bishe(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
	connect(ui.ctrlwidgetButton, SIGNAL(clicked()), this, SLOT(ctrlButton_clicked()));
}


void QtWidgets_bishe::ctrlButton_clicked() {
	ctrl = new CtrlWidget;  //在.h文件新建的ctrl指针，在这里就是控制窗口，new一个出来
	ctrl->show();
	cout << "已打开控制窗口" << endl;
}