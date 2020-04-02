#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "clientsocket.h"

namespace model
{
namespace chatserver
{
namespace connection
{

ClientSocket::ClientSocket(const std::string& host, int port)
{
    this->host = host;
    this->port = port;
    this->sock = 0;
}

bool ClientSocket::makeConnection(const std::string& message)
{
    struct sockaddr_in serv_addr;
    if ((this->sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        return false;
    }
    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(static_cast<uint16_t>(static_cast<unsigned int>(this->port)));
    if (inet_pton(AF_INET, this->host.c_str(), &serv_addr.sin_addr) <= 0)
    {
        return false;
    }
    if (connect(this->sock, reinterpret_cast<struct sockaddr*>(&serv_addr), sizeof(serv_addr)) < 0)
    {
        return false;
    }

    send(this->sock, message.c_str(), message.length(), 0);
    return true;
}

void ClientSocket::closeConnection()
{
    close(this->sock);
}

const std::string& ClientSocket::getHost() const
{
    return this->host;
}

int ClientSocket::getPort() const
{
   return this->port;
}

int ClientSocket::getSock() const
{
    return this->sock;
}

ClientSocket::~ClientSocket()
{
}

}
}
}
