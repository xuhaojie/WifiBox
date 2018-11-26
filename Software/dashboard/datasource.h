#ifndef DATASOURCE_H
#define DATASOURCE_H

#include <QThread>
#include <QtNetwork/QTcpSocket>

class DataSource : public QThread
{
    Q_OBJECT
public:
    explicit DataSource(QObject *parent = 0);
    ~DataSource();
    int init();
    void run();

signals:
    void dataChanged(const QString& key, const QString& value);

public slots:

    void stop();
    void send(const QString& data);

private slots:
    void abortedSlot();

    void connectedSlot();

    void disconnectedSlot();

    void readyReadSlot();

    void errorSlot(QAbstractSocket::SocketError);

protected:
    void connectServer();

private:
    QTcpSocket *m_pSocket;

    bool m_isConnected;
    bool m_quit;
    bool m_done;


};

#endif // DATASOURCE_H
