#include "osvec.hpp"
#include "node.hpp"

#include <SFML/Network.hpp>


using namespace mute;

int main()
{
    NodeGraph graph;

    graph.insert(Node{}, NodeId(1));
    graph.insert(Node{}, NodeId(2));
    graph.insert(Node{}, NodeId(3));
    graph.insert(Link{NodeId(1), NodeId(2)});
    graph.insert(Link{NodeId(2), NodeId(3)});

    MUTE_LOG << graph[NodeId(2)].links() << endl;
    MUTE_LOG << graph[NodeId(2)].neighbors() << endl;
/*
    sf::TcpListener listener;

    if (listener.listen(18464) != sf::Socket::Done) {
        std::cerr << "Error binding to socket" << std::endl;
        return 1;
    }

    sf::TcpSocket client;
    if (listener.accept(client) != sf::Socket::Done)
    {
        std::cerr << "Error accepting client connection" << std::endl;
        return 1;
    }*/
}
