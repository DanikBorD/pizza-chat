#include <QCoreApplication>
#include "chatserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ChatServer s;
    s.listen(QHostAddress::Any, 9000);

    return a.exec();
}
