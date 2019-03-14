//                                                                                                 
// EPITECH PROJECT, 2018                                                                           
// cpp                                                                                             
// File description:                                                                               
// cpp                                                                                             
// 

#include <iostream>
#include "Server.hpp"

int main(int argc, char **argv)
{
  try {
    auto port = (argc == 2) ? static_cast<unsigned short>(std::stoul(argv[1])) : 1234;
    std::cout << "Using Port: " << port << std::endl;

    UDPServer server(port);
    server.Run();
  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}
