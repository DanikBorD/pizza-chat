#ifndef LOGINFORM_H
#define LOGINFORM_H
#include <chatclient.h>

#include <QDialog>
#include <QTcpSocket>

namespace Ui {
class LoginForm;
}

class LoginForm : public QDialog
{
    Q_OBJECT

public:
    explicit LoginForm(QWidget *parent = 0);
    ~LoginForm();
    QString getLogin();
    QString getPass();

private slots:
    void on_chatButton_clicked();
    void on_login_result();

private:
    QTcpSocket m_socket;
    ChatClient * m_client;
    Ui::LoginForm *ui;
    QString m_login;
    QString m_pass;
    QStringList m_text;
};

#endif // LOGINFORM_H
