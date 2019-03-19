#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <vector>

class UDPServer
{
public:
  /// Creates a UDP socket and runs it on the specified port
  /// port is in normal endianness (no ntohs)
  UDPServer(unsigned short port);
  /// Runs the Server
  void Run();

private:
  void HandleReceiveFrom(const boost::system::error_code &error, size_t bytesReceived);
  void HandleSendTo([[maybe_unused]] const boost::system::error_code &error,
                    [[maybe_unused]] size_t bytesSent);

  boost::asio::io_service io_service_;
  boost::asio::ip::udp::socket socket_;
  boost::asio::ip::udp::endpoint sender_endpoint_;
  static constexpr int maxLength = 1024;
  char data_[maxLength];
  /// This is the list of every clients that sent something
  /// to the server at one point in time (UDP has no handshake)
  std::vector<boost::asio::ip::udp::endpoint> clients;
};
