#ifndef NOTEPADFORM_H
#define NOTEPADFORM_H

#include <QPlainTextEdit>

class NotepadForm : public QWidget
{
    Q_OBJECT

public:
    NotepadForm(QWidget* p=Q_NULLPTR, Qt::WindowFlags f=Q_NULLPTR);
    virtual ~NotepadForm();

public:
    bool init();

private slots:
    void jumptab();

private:
    void setupUi();
    void uninit();

private:
    QPlainTextEdit* m_board;
};

#endif // __NOTEPADFORM_H__




