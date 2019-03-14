#include "Server.hpp"

UDPServer::UDPServer(unsigned short port)
  : socket_(io_service_,
            boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port))
{
  socket_.async_receive_from(
                             boost::asio::buffer(data_, maxLength), sender_endpoint_,
                             boost::bind(&UDPServer::HandleReceiveFrom, this,
                                         boost::asio::placeholders::error,
                                         boost::asio::placeholders::bytes_transferred));
}

void UDPServer::Run()
{
  io_service_.run();
}

void UDPServer::HandleReceiveFrom(const boost::system::error_code &error,
                                  size_t bytesReceived)
{
  if (!error && bytesReceived > 0) {
    if (std::find(clients.begin(), clients.end(), sender_endpoint_) == clients.end())
      clients.push_back(sender_endpoint_);
    for (auto client_endpoint : clients)
      socket_.async_send_to(
                            boost::asio::buffer(data_, bytesReceived), client_endpoint,
                            boost::bind(&UDPServer::HandleSendTo, this,
                                        boost::asio::placeholders::error,
                                        boost::asio::placeholders::bytes_transferred));
  } else {
    socket_.async_receive_from(
                               boost::asio::buffer(data_, maxLength), sender_endpoint_,
                               boost::bind(&UDPServer::HandleReceiveFrom, this,
                                           boost::asio::placeholders::error,
                                           boost::asio::placeholders::bytes_transferred));
  }
}

void UDPServer::HandleSendTo([[maybe_unused]] const boost::system::error_code &error,
                             [[maybe_unused]] size_t bytesSent)
{
  socket_.async_receive_from(
                             boost::asio::buffer(data_, maxLength), sender_endpoint_,
                             boost::bind(&UDPServer::HandleReceiveFrom, this,
                                         boost::asio::placeholders::error,
                                         boost::asio::placeholders::bytes_transferred));
}
