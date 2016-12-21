#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "loginform.h"
#include <QStringListModel>
#include <QStringList>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    LoginForm win;
    win.exec();
    m_login = win.getLogin();
    m_pass = win.getPass();
    m_client = new ChatClient(m_login, m_pass, this);
    connect(m_client, SIGNAL(incomingMessage(QString,QString)),this,
            SLOT(onIncomingMessage(QString,QString)));

    ui->contacts->setModel(&m_contactsModel);

    connect(m_client, SIGNAL(contactsChanged(QStringList)),this,
            SLOT(onContactsChanged(QStringList)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_send_clicked()
{
    QString text;
    text = ui->message->text();
    m_client->sendMessage(text);
    ui->message->clear();
}

void MainWindow::onIncomingMessage(QString login, QString message)
{
     ui->history->append("<b>"+login+": "+"</b>"+message);
}

void MainWindow::on_message_returnPressed()
{
    on_send_clicked();
}

void MainWindow::onContactsChanged(QStringList contacts)
{
    m_contactsModel.removeRows(0, m_contactsModel.rowCount());
    m_contactsModel.setStringList(contacts);
}
