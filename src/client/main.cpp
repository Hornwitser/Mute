#include <SFML/Network.hpp>

#include <cstdint>

#include <iostream>

int main()
{
    sf::TcpSocket socket;
    sf::Socket::Status status = socket.connect("localhost", 18464);
    if (status != sf::Socket::Done)
    {
        std::cerr << "Error connectiong to server" << std::endl;
        return 1;
    }


    for (;;) {
        
    }
}
