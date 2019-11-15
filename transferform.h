#ifndef TRANSFERFORM_H
#define TRANSFERFORM_H

#include "ui_transferform.h"
#include "baseform.h"

class TransferSkt;
class TransferForm : public BaseForm
{
	Q_OBJECT

public:
    TransferForm(QWidget* p=Q_NULLPTR, Qt::WindowFlags f=Q_NULLPTR);
	~TransferForm();

protected:
	virtual bool initForm();
	virtual bool initHotkeys();
	virtual void initConfig();
	virtual void saveConfig();
	virtual void send(const QString& data, const QString& dir);
	virtual void kill(QStringList& list);

private slots:
	void trigger(bool start);
	void stop();

private:
	TransferSkt* m_server;
	Ui::TransferForm m_ui;
};

#endif // __TRANSFERFORM_H__



