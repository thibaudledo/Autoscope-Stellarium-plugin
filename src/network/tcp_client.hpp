#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QTcpSocket>
#include <QHostAddress>
#include <QByteArray>

/*!
 * \file tcp_client.hpp
 * \brief Header file including TCP client definition
 * \author clement-ailloud
 */

/*!
 * \class TcpClient
 * \brief The TcpClient class allow to make usage of QTcpSocket more suitable for development
 */
class TcpClient : public QTcpSocket {
    /*<! Need for QObject signal/slot connection */
    Q_OBJECT
public:

    /*!
     * \brief Builder of the TcpClient class
     * \param parent The parent of the TcpClient
     */
    TcpClient(QTcpSocket *parent = 0);

    /*!
     * \brief Builder of the TcpClient class
     * \param host_address The address of the server
     * \param port The port of the server
     */
    TcpClient(QHostAddress host_address, quint16 port);

    /*!
     * \brief Destroyer of the TcpClient class
     */
    ~TcpClient();

public slots:

    /*!
     * \brief Handle host found
     */
    void host_found_handler(void);

    /*!
     * \brief Handle connection to host
     */
    void connected_handler(void);

private:

    quint16 m_port; /*!< server port */
    QHostAddress m_host_address;    /*!< server host address */
};

#endif // TCPCLIENT_H
