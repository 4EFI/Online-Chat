#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include <windows.h>

int main()
{
    sf::TcpSocket socket;
    sf::IpAddress ip = sf::IpAddress::getLocalAddress();

    char type;

    std::cout << "Enter type connecting: [c] - client, [s] - server\n";
    std::cin  >> type;

    if(type == 's')
    {
        sf::TcpListener listener;
        listener.listen(2000);

        if(listener.accept(socket) != sf::Socket::Done)
        {
            std::cout << "Error!\n";
        }
    }
    else if(type == 'c')
    {
        if(socket.connect(ip, 2000) != sf::Socket::Done)
        {
            std::cout << "Error!\n";
        }
    }

    std::string name;
    std::cout << "Enter your name:\n";
    std::cin  >> name;

    socket.setBlocking(false);

    std::string message = "";
    sf::Packet  packet;

    while(true)
    {
        if(GetAsyncKeyState(VK_ESCAPE))
        {
            std::cin >> message;
        }

        if(message != "")
        {
            packet.clear();
            packet << name << message;

            socket.send(packet);

            message = "";
        }

        if(socket.receive(packet) == sf::Socket::Done)
        {
            std::string nameRec;
            std::string messageRec;

            packet    >> nameRec >> messageRec;
            std::cout << nameRec << ": " << messageRec << '\n';
        }
    }
}
