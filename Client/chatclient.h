#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QStringList>

class ChatClient : public QObject
{
    Q_OBJECT

private:
    QTcpSocket *m_socket;
    QString m_login;
    QString m_pass;

public:
    explicit ChatClient(QObject *parent = 0);
    void sendMessage(QString message);
    void auth(QString login, QString pass);

signals:
    void incomingMessage(QString login, QString message);
    void contactsChanged(QStringList contacts);



public slots:
    void onReadyRead();

};

#endif // CHATCLIENT_H
