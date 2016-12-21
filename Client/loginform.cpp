#include "loginform.h"
#include "ui_loginform.h"
#include "mainwindow.h"
#include <QDebug>


LoginForm::LoginForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginForm)
{   connect(m_client, SIGNAL(loginResult()),this, SLOT(on_login_result()));
    ui->setupUi(this);
}

LoginForm::~LoginForm()
{
    delete ui;
}

QString LoginForm::getLogin()
{
    return m_login;
}

QString LoginForm::getPass()
{
    return m_pass;
}

void LoginForm::on_chatButton_clicked()
{
    m_text = ui->login->text().split(" ");
    m_login = m_text[0];
    m_pass = m_text[1];
    m_socket->write(QString("connect " + m_login + " " + m_pass).toUtf8());
}

void LoginForm::on_login_result()
{
    qDebug() << "on_login_result";
    close();
}
