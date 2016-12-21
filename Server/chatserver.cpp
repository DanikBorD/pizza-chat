#include "chatserver.h"
#include <QDebug>
#include <QFile>
#include <QStringList>
#include <QTcpSocket>
#include <QMessageBox>

void ChatServer::incomingConnection(int handle)
{
    qDebug() << "new connection";
    QTcpSocket *socket = new QTcpSocket(this);
    socket->setSocketDescriptor(handle);
    m_waitingConnections.append(socket);
    connect(socket, SIGNAL(readyRead()),this, SLOT(onReadyRead()));
}

bool ChatServer::auth(QString login, QString pass)
{
    bool res = true;
    QString chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklnmopqrstuvwxyz0123456789_";
    for (int i = 0; i < chars.length(); i++)
    {
        if (!login.contains(chars[i]))
        {
            res = false;
            break;
        }
    }
    if(res == false)
    {
        emit loginFail();
        //QMessageBox::information(this, "Error", "Login error", QMessageBox::Ok);
        return;
    }

    if(m_users.keys().contains(login))
    {
        if ((m_users[login] == pass) && (res == true))
        {
            emit loginResult();
            return true;
        }
    }
    emit loginLal();
    //QMessageBox::information(this, "Lalniy error", "LAAAAAAAAL", QMessageBox::Ok);
    return false;

}

ChatServer::ChatServer(QObject *parent) :
    QTcpServer(parent)
{
    QFile file("file.txt");
    if (!file.open(QFile::ReadOnly))
    {
        qDebug() << "file is not open!";
        return;
    }
    QTextStream fstream(&file);
    while (!fstream.atEnd())
    {
        QStringList ls = fstream.readLine().split(" ");

        m_users[ls[0]] = ls[1];
    }
}

void ChatServer::sendText(QTcpSocket *socket, QString text)
{
    socket->write(text.toUtf8());
}

void ChatServer::sendContacts(QTcpSocket * socket)
{
    sendText(socket,"contacts\r\n");
    foreach (QString user, m_connections.keys())
        sendText(socket,user + "\r\n");
    socket->flush();
}

void ChatServer::onReadyRead()
{

    QTcpSocket *socket = (QTcpSocket *)(QObject::sender());
    QString text = QString::fromUtf8(socket->readAll());
    qDebug() << text;
    int pos = text.indexOf(" ");
    if (pos == -1)
        return;
    QString command = text.mid(0,pos);
    sendContacts(socket);
    if (command == "connect")
    {
//      QString user = text.mid(pos+1);
        QStringList ls = text.split(" ");
        QString login = ls[1];
        QString pass = ls[2];
        if (auth(login, pass));
        {
            m_waitingConnections.remove(m_waitingConnections.indexOf(socket));
            m_connections[login] = socket;
            sendContacts(socket);
        }
    }
    if (command == "message")
    {
        QString message = text.mid((pos+1));
        foreach (QTcpSocket *socket, m_connections)
        {
            socket->write(text.toUtf8());
            socket->write("\r\n");
            socket->flush();
        }
    }

}

