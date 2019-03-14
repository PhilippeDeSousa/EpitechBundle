#ifndef UDPCLIENT_HPP
#define UDPCLIENT_HPP

#include <QObject>
#include <QUdpSocket>
#include <StreamHandler.hpp>
#include "OpusHandler.hpp"

class UDPClient : public QObject
{
    Q_OBJECT
public:
    /// Creates a UDP Client
    /// with the address and port used for the sending
    /// please initialise the parent because the QUdpSocket
    /// crashes when the window closes if parent == nullptr
    explicit UDPClient(QObject *parent, QHostAddress addr, quint16 port);
    /// Sends the datagram to the destAddr at destPort
    void Send(QByteArray &data);
    /// Returns a datagram read from the Socket
    QByteArray Receive();
    /// Since connect SIGNAL/SLOT is broken with multithreading
    /// it returns true if it has packets to read
    bool HasRxData();
    ~UDPClient();

signals:

public slots:

private:
    /// This is what links this program to the server
    /// We chose UDP because audio streaming
    /// doesn't need ACK packets to provide a good user experience
    QUdpSocket *socket = nullptr;
    /// Address of the Server
    QHostAddress destAddr;
    /// Port of the Server
    quint16 destPort;
};

#endif // UDPCLIENT_HPP
