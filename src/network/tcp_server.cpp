#include "tcp_server.hpp"

TcpServer::TcpServer(){

}

TcpServer::TcpServer(bool autostart){
    m_host_address = "127.0.0.1";
    m_port = 4444;

    if (autostart){
        start();
    }
}

TcpServer::TcpServer(QString &host_address, quint16 port, bool autostart){
    m_host_address = host_address;
    m_port = port;

    if (autostart){
        start();
    }
}

TcpServer::~TcpServer(){

}

void TcpServer::create_socket(){
    m_tcp_client = nextPendingConnection();

    if (!m_tcp_client->isValid()){
        qDebug() << "TCP socket error: socket state: " << m_tcp_client->state();
    }

    //connect(m_tcp_client, SIGNAL(readyRead()), this, SLOT());

    qDebug() << "Connection opened";
}

void TcpServer::start(){
    bool ret = false;

    qDebug() << "Starting TCP server...";

    connect(this, SIGNAL(newConnection()), this, SLOT(create_socket()));

    // Get host address automatically whether possible
    ret = listen(QHostAddress(QString(m_host_address)), m_port);

    if (ret == false){
        qDebug() << "Starting TCP server... failed";
    }

    // Wait until isListening() with timeout

    qDebug() << "Starting TCP server... done";
}

void TcpServer::set_port(quint16 port){
    m_port = port;
}

void TcpServer::set_address(const char *address){
    m_host_address = QString(address);
}

QTcpSocket *TcpServer::get_client(void){
    return m_tcp_client;
}

