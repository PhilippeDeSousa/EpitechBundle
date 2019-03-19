#include <iostream>
#include <SFML/Network.hpp>
#include <string>



int main()
{
  sf::Uint32 x = 24;
  std::string s = "hello";
  sf::Uint32 l = 13;
  // Group the variables to send into a packet
  sf::Packet packet;
  packet << x << s << l;
  // Extract the variables contained in the packet
  sf::Uint32 x1;
  std::string s1;
  sf::Uint32 l1;
  std::cout << "Packet: " << packet << std::endl;
  if (packet >> x1 >> s1 >> l1)
    {
      std::cout << "It worked: "<< x1 << s1 << l1 << std::endl;
      return 0;
    }
  return 1;
}
