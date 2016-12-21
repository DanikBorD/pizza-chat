#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QTcpServer>
#include <QHash>
#include <QTcpSocket>
#include <QString>
#include <QVector>

class ChatServer : public QTcpServer
{ 
    Q_OBJECT
protected:
    void incomingConnection(int handle);

private:
    QHash<QString, QTcpSocket* > m_connections;
    QVector<QTcpSocket * > m_waitingConnections;
    bool auth(QString login, QString pass);
    QHash<QString, QString> m_users;

public:
    explicit ChatServer(QObject *parent = 0);
    void sendText(QTcpSocket* socket, QString text);
    void sendContacts(QTcpSocket*socket);


signals:
    void loginResult();
    void loginFail();
    void loginLal();

public slots:

private slots:
    void onReadyRead();

};

#endif // CHATSERVER_H
