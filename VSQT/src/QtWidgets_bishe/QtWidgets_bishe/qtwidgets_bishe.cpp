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
	ctrl = new CtrlWidget;  //��.h�ļ��½���ctrlָ�룬��������ǿ��ƴ��ڣ�newһ������
	ctrl->show();
	cout << "�Ѵ򿪿��ƴ���" << endl;
}