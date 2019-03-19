#include "Udpclient.hpp"
#include <QPlainTextEdit>
#include <QWidget>
#include <StreamHandler.hpp>
#include <QThread>

UDPClient::UDPClient(QObject *parent, QHostAddress addr, quint16 port) :
    QObject(parent),
    destAddr(addr),
    destPort(port)
{
    socket = new QUdpSocket(this);
    socket->bind(QHostAddress::LocalHost);
}

UDPClient::~UDPClient()
{
    delete socket;
}

void UDPClient::Send(QByteArray &data)
{
  socket->writeDatagram(data, destAddr, destPort);
}

bool UDPClient::HasRxData()
{
    return socket->hasPendingDatagrams();
}

QByteArray UDPClient::Receive()
{
    // when data comes in
    QByteArray buffer;
    buffer.resize(static_cast<int>(socket->pendingDatagramSize()));

    QHostAddress sender;
    quint16 senderPort;

    socket->readDatagram(buffer.data(), buffer.size(),
                         &sender, &senderPort);
    return (buffer);
}

