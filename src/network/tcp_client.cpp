#include "tcp_client.hpp"

TcpClient::TcpClient(QTcpSocket *parent) : QTcpSocket(parent){
    connect(this, SIGNAL(hostFound()), this, SLOT(host_found_handler()));
    connect(this, SIGNAL(connected()), this, SLOT(connected_handler()));

    m_host_address.setAddress("127.0.0.1");
    m_port = 4444;
}

TcpClient::TcpClient(QHostAddress host_address, quint16 port)
  : m_host_address(host_address), m_port(port){
    connect(this, SIGNAL(hostFound()), this, SLOT(host_found_handler()));
    connect(this, SIGNAL(connected()), this, SLOT(connected_handler()));
}

TcpClient::~TcpClient(){

}

void TcpClient::host_found_handler(){
    qDebug() << "Host found";
}

void TcpClient::connected_handler(){
    qDebug() << "Connected to" << m_host_address.toString();
}
