#ifndef HELPFORM_H
#define HELPFORM_H

#include "ui_helpform.h"

class HelpForm : public QDialog
{
	Q_OBJECT

public:
    HelpForm(QWidget* p=Q_NULLPTR, Qt::WindowFlags f=Q_NULLPTR);
	virtual ~HelpForm();

private:
	void init();

private:
	Ui::HelpForm m_ui;
};

#endif // __HELPFORM_H__




