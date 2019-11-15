#ifndef SOKIT_H
#define SOKIT_H

#include <QWidget>
#include <QTranslator>

namespace Ui {
class sokit;
}

class sokit : public QWidget
{
    Q_OBJECT

public:
    explicit sokit(QWidget *parent = nullptr);
    ~sokit();

    bool initTranslator();
    bool initUI();

private slots:
    void ontop();

private:
    void initFont();
    void initDefaultActionsName();

private:
    QTranslator m_trans;
    Ui::sokit *ui;
};

#endif // SOKIT_H
