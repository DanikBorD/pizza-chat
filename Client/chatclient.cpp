#include "chatclient.h"
#include <QDebug>

ChatClient::ChatClient(QObject *parent) :
    QObject(parent)
{
    m_socket = new QTcpSocket(this);
    m_socket->connectToHost("10.0.0.48", 9000);
    m_socket->waitForConnected();
    m_socket->write(QString("connect " + m_login + " " + m_pass).toUtf8());
    connect(m_socket, SIGNAL(readyRead()),this, SLOT(onReadyRead()));
    m_socket->flush();
}

void ChatClient::sendMessage(QString message)
{
    m_socket->write(QString("message " + m_login + " " + message).toUtf8());
}

void ChatClient::auth(QString login, QString pass)
{

}

void ChatClient::onReadyRead()
{
    QTcpSocket *socket = (QTcpSocket *)(QObject::sender());
    QString text = QString::fromUtf8(socket->readAll());
    qDebug() << text;
    int pos = text.indexOf(" ");
    if (pos == -1)
        return;
    QString command = text.mid(0,pos);
    if (command == "message")
    {
        QString message = text.mid((pos+1));
        pos = message.indexOf(" ");
        if (pos < 0)
            return;
        QString user = message.mid(0,pos);
        QString messageText = message.mid(pos + 1);
        emit incomingMessage(user,messageText);
    }
    if (command == "contacts"){
        QString contacts = text.mid(pos + 1).trimmed();
        QStringList contactList = contacts.split(" ");
        emit contactsChanged(contactList);
    }

}
