#include "datasource.h"

DataSource::DataSource(QObject *parent) : QThread(parent)
  ,m_pSocket(0)
  ,m_isConnected(false)
  ,m_quit(false)
  ,m_done(false)
{


}

DataSource::~DataSource()
{
   if(m_pSocket)
   {
        stop();
        delete m_pSocket;
        m_pSocket = NULL;
   }
}

int DataSource::init()
{
    if(0 == m_pSocket)
    {
        m_pSocket = new QTcpSocket(this);
        if(m_pSocket)
        {
            //connect(m_pSocket, SIGNAL(aborted()), this, SLOT(abortedSlot()));

            connect(m_pSocket, SIGNAL(connected()), this, SLOT(connectedSlot()));

            connect(m_pSocket, SIGNAL(disconnected()), this, SLOT(disconnectedSlot()));
            return 0;
        }
    }
    return -1;
}

void DataSource::stop()
{
    if(0 == m_pSocket)
    {
        return;
    }
    m_quit = true;
    while(!m_done)
    {
        usleep(50*1000);
    }
    m_pSocket->abort();
    m_pSocket->disconnect();
    m_isConnected = false;
}

void DataSource::send(const QString &data)
{
    if(m_pSocket && m_isConnected)
    {
        m_pSocket->write(data.toLocal8Bit(),data.length());
        m_pSocket->flush();

        return;
    }
}

void DataSource::abortedSlot()
{

}

void DataSource::connectServer()
{
    if(0 == m_pSocket)
    {
        return;
    }

    m_pSocket->connectToHost("10.10.10.1", 1688);
    m_pSocket->waitForConnected(1000);
}

void DataSource::run()
{
    char recvBuf[1025];
    int Count = 0;
    char NameBuffer[256];
    char ValueBuffer[256];
    char* pName = NameBuffer;
    char* pValue = ValueBuffer;

    memset(recvBuf,0,sizeof(recvBuf));
    enum PARSE_STATE
    {
        PS_NAME = 0,
        PS_VALE = 1,
    };
    PARSE_STATE State = PS_NAME;
    int PakageSize = 0;
    if(init()<0)
    {
        return;
    }
    while(!m_quit)
    {
        if(!m_isConnected)
        {
            connectServer();
            usleep(100*1000);
        }
        else if(m_pSocket->waitForReadyRead(500))
        {

            Count = 0;
            memset(recvBuf,0,sizeof(recvBuf));

            int RecvLength = m_pSocket->read(recvBuf,1024);
            if(RecvLength >0 )
            {
                char* pData = recvBuf;

                Count = RecvLength;
                while(Count --)
                {
                    switch(*pData)
                    {
                    case '=':
                        *pName = '\0';
                        State = PS_VALE;
                        break;
                    case '\r':
                        break;
                    case '\n':
                        *pValue = '\0';
                        if(pName > NameBuffer && pValue >= ValueBuffer)
                        {
                            emit dataChanged(NameBuffer,ValueBuffer);

                        }
                        else
                        {
                            PakageSize = 0;
                        }
                        State = PS_NAME;
                        pName = NameBuffer;
                        pValue = ValueBuffer;
                        break;
                    default:
                        if(PS_NAME == State)
                        {
                            *pName++ = *pData;
                        }
                        else if(PS_VALE == State)
                        {
                            *pValue++ = *pData;
                        }
                        break;
                    }
                    pData++;

                }
            }
        }
    }
    m_done = true;
}

void DataSource::connectedSlot()
{

    m_isConnected = true;

}

void DataSource::disconnectedSlot()

{
    m_isConnected = false;
}

void DataSource::readyReadSlot()

{

    QByteArray message = m_pSocket->readAll();

    //ui->recvEdit->append(message);

}

void DataSource::errorSlot(QAbstractSocket::SocketError)

{

    //QMessageBox::information(this, "show", socket_->errorString());
    //disconnectedSlot();

}


