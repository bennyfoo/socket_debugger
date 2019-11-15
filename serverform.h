#ifndef SERVERFORM_H
#define SERVERFORM_H

#include "baseform.h"
#include "serverskt.h"
#include "ui_serverform.h"

class ServerForm : public BaseForm
{
    Q_OBJECT

public:
    ServerForm(QWidget* p=Q_NULLPTR, Qt::WindowFlags f=Q_NULLPTR);
    virtual ~ServerForm();

protected:
    virtual bool initForm();
    virtual bool initHotkeys();
    virtual void initConfig();
    virtual void saveConfig();
    virtual void send(const QString& data, const QString& dir);
    virtual void kill(QStringList& list);

private slots:
    void trigger(bool start);

private:
    ServerSktTcp m_tcp;
    ServerSktUdp m_udp;
    Ui::ServerForm m_ui;
};

#endif // __SERVERFORM_H__



