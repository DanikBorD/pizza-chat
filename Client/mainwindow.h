#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <chatclient.h>
#include <QStringListModel>
#include <QStringList>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_send_clicked();
    void onIncomingMessage(QString login, QString message);
    void on_message_returnPressed();
    void onContactsChanged(QStringList contacts);

private:
    Ui::MainWindow *ui;
    QString m_login;
    QString m_pass;
    ChatClient * m_client;
    QStringListModel m_contactsModel;
};

#endif // MAINWINDOW_H
