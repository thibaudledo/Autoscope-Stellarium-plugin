#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QDebug>

#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>

#include <QString>

//!
//! \class TcpServer
//!
//! \brief The TcpServer class allow to make usage of QTcpServer more suitable for development
//!

class TcpServer : public QTcpServer {
    Q_OBJECT

public:
    explicit TcpServer();
    TcpServer(bool autostart = 0);
    TcpServer(QString &host_address, quint16 port = 4444, bool autostart = 0);
    ~TcpServer();

    //!
    //! \fn    void start(void)
    //!
    //! \brief start
    //!

    void start(void);

    //!
    //! \fn    void set_port(quint16 port)
    //!
    //! \brief set_port
    //!
    //! \param port
    //!

    void set_port(quint16 port);

    //!
    //! \fn    void set_address(const char *address)
    //!
    //! \brief set_address
    //!
    //! \param address
    //!

    void set_address(const char *address);

    //!
    //! \fn    QTcpSocket *get_client(void)
    //!
    //! \brief get_client
    //!
    //! \return client address for interacting with the client connected to the server
    //!

    QTcpSocket *get_client(void);

public slots:
    //!
    //! \fn    void create_socket(void)
    //!
    //! \brief create_socket
    //!

    void create_socket(void);

private:
    /*!< Server port */
    quint16 m_port;

    /*!< Server address */
    QString m_host_address;

    /*!< Client object used to communicate with the client connected to the server */
    QTcpSocket *m_tcp_client;

};

#endif // WIDGET_H
