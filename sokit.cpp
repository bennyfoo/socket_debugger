#include "sokit.h"
#include "ui_sokit.h"

#include "toolkit.h"
#include "setting.h"
#include "clientform.h"
#include "serverform.h"
#include "transferform.h"
#include "notepadform.h"
#include "helpform.h"

#include <QVBoxLayout>
#include <QTabWidget>
#include <QShortcut>

#define SET_KEY_FTNM "/font/name"
#define SET_KEY_FTSZ "/font/size"

#define SET_KEY_LANG "/lang"
#define SET_VAL_LANG "sokit"
#define SET_VAL_LANX ".lan"

sokit::sokit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sokit)
{
    ui->setupUi(this);
    initUI();

    setWindowTitle(QCoreApplication::translate("sokit", "Socket Debuger V1.1"));
    setWindowIcon(QIcon(":/res/App.ico"));
}

sokit::~sokit()
{
    delete ui;
}

void sokit::initDefaultActionsName()
{
    QCoreApplication::translate("QLineEdit", "&Undo");
    QCoreApplication::translate("QLineEdit", "&Redo");
    QCoreApplication::translate("QLineEdit", "Cu&t");
    QCoreApplication::translate("QLineEdit", "&Copy");
    QCoreApplication::translate("QLineEdit", "&Paste");
    QCoreApplication::translate("QLineEdit", "Delete");
    QCoreApplication::translate("QLineEdit", "Select All");

    QCoreApplication::translate("QTextControl", "&Undo");
    QCoreApplication::translate("QTextControl", "&Redo");
    QCoreApplication::translate("QTextControl", "Cu&t");
    QCoreApplication::translate("QTextControl", "&Copy");
    QCoreApplication::translate("QTextControl", "&Paste");
    QCoreApplication::translate("QTextControl", "Delete");
    QCoreApplication::translate("QTextControl", "Select All");
}

bool sokit::initTranslator()
{
    QString file = Setting::get(SET_SEC_CFG, SET_KEY_LANG, SET_VAL_LANG);

    QStringList paths;
    paths << "."
        << "../share/" SET_APP_NAME
        << "../share/apps/" SET_APP_NAME
        << Setting::path();

    foreach(QString p, paths)
    {
       // if (m_trans.load(file, p, "", SET_VAL_LANX))
        if (m_trans.load("sokit.qm"))
        {
            QCoreApplication::installTranslator(&m_trans);
            Setting::set(SET_SEC_CFG, SET_KEY_LANG, file);
            break;
        }
    }

    return true;
}

void sokit::initFont()
{
    QFontDatabase db;
    QStringList fs = db.families();

    QFont font;

    int match = 0;

    QString family = Setting::get(SET_SEC_CFG, SET_KEY_FTNM, "").trimmed();
    QString size = Setting::get(SET_SEC_CFG, SET_KEY_FTSZ, "").trimmed();

    if (family.isEmpty() || fs.filter(family).isEmpty())
    {
        QStringList defs = QCoreApplication::translate("sokit", "font").split(";", QString::SkipEmptyParts);
        foreach(QString d, defs)
        {
            family = d.section(',', 0, 0).trimmed();
            size = d.section(',', 1, 1).trimmed();

            if (!family.isEmpty() && !fs.filter(family).isEmpty())
            {
                match = 2;
                break;
            }
        }
    }
    else
    {
        match = 1;
    }

    if (match > 0)
    {
        font.setFamily(family);

        if (db.isSmoothlyScalable(family))
            font.setStyleStrategy((QFont::StyleStrategy)(QFont::PreferAntialias | QFont::PreferOutline | QFont::PreferQuality));

        int nsize = size.toInt();
        if (nsize > 0 && nsize < 20)
            font.setPointSize(nsize);

        setFont(font);

        if (match > 1)
        {
            Setting::set(SET_SEC_CFG, SET_KEY_FTNM, family);
            Setting::set(SET_SEC_CFG, SET_KEY_FTSZ, size);
        }
    }
}

bool sokit::initUI()
{
    initTranslator();
    initFont();

    HelpForm* h = new HelpForm(this, Qt::WindowCloseButtonHint);

    QShortcut* k = new QShortcut(QKeySequence(Qt::Key_F1), this);
    QShortcut* t = new QShortcut(QKeySequence(Qt::Key_F10), this);
    connect(k, SIGNAL(activated()), h, SLOT(exec()));
    connect(t, SIGNAL(activated()), this, SLOT(ontop()));



    BaseForm* server = new ServerForm();
    BaseForm* transf = new TransferForm();
    BaseForm* client = new ClientForm();
    NotepadForm* npd = new NotepadForm();

    QTabWidget* tab = new QTabWidget(this);
    tab->addTab(client, client->windowTitle());
    tab->addTab(server, server->windowTitle());
    //tab->addTab(transf, transf->windowTitle());
    tab->addTab(npd, npd->windowTitle());
    tab->setCurrentIndex(0);

    QLayout* lay = new QVBoxLayout(this);
    lay->setSpacing(5);
    lay->setContentsMargins(5, 5, 5, 5);
    lay->addWidget(tab);

    return server->init() && transf->init() &&
        client->init() && npd->init();
}

void sokit::ontop()
{
    Qt::WindowFlags f = windowFlags();
    if (f & Qt::WindowStaysOnTopHint)
        f &= ~Qt::WindowStaysOnTopHint;
    else
        f |= Qt::WindowStaysOnTopHint;

    setWindowFlags(f);
    show();
}
