#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QTcpSocket>
#include <QHostAddress>
#include <QByteArray>

//!
//! \class TcpClient
//!
//! \brief The TcpClient class allow to make usage of QTcpSocket more suitable for development
//!

class TcpClient : public QTcpSocket {
    /*<! Need for QObject signal/slot connection */
    Q_OBJECT
public:
    TcpClient(QTcpSocket *parent = 0);
    TcpClient(QHostAddress host_address, quint16 port, QTcpSocket *parent = 0);
    ~TcpClient();

public slots:
    void host_found_handler(void);
    void connected_handler(void);

private:
    /*!< server port */
    quint16 m_port;

    /*!< server host address */
    QHostAddress m_host_address;
};

#endif // TCPCLIENT_H
