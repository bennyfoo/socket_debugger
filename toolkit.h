#ifndef SOKIT_TOOLKIT_H
#define SOKIT_TOOLKIT_H

#include <QAbstractSocket>
#include <QString>
#include <QVector>
#include <QByteArray>
#include <QHostAddress>
#include <QComboBox>
#include <QToolButton>

typedef struct _IPAddr
{
	QHostAddress ip;
	quint16 port;
} IPAddr;

class TK
{
public:
	typedef enum { OUT=0, OUT2IN, IN, ERR } PARSE_STA;

	static const char* hextab;
	static QString ascii2hex(const QString& src, QVector<uint>& posmap, uint& count);
	static QString bin2hex(const char* buf, uint len);
	static QString bin2ascii(const char* buf, uint len);
	static bool ascii2bin(const QString& src, QByteArray& dst, QString& err);

	static char* createBuffer(qint64& cap, qint64 limit);
	static void  releaseBuffer(char*& buf);

	static const char* socketTypeName(bool tcp);
	static const char* socketTypeName(QAbstractSocket* skt);
	static void initNetworkInterfaces(QComboBox* box, bool testDef = false);

	static QString ipstr(const QHostAddress& addr, quint16 port);
	static QString ipstr(const QHostAddress& addr, quint16 port, bool tcp);
	static bool popIPAddr(QComboBox* ip, QComboBox* port, IPAddr& addr);
	static void pushIPAddr(QComboBox* ip, QComboBox* port);

	static void pushComboBox(QComboBox* box, const QString& item);
	static void resetPushBox(QToolButton* btn);
};

#endif // __TOOLKIT_H__

