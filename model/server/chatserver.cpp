#include <qt5/QtConcurrent/QtConcurrent>

#include <chrono>
#include <thread>
#include <sstream>

#include "chatserver.h"

namespace model
{
namespace chatserver
{

ChatServer::ChatServer(connection::ClientSocket* listeningSocket)
{
    this->listeningSocket = listeningSocket;
    this->listeningThread = nullptr;
}

bool ChatServer::sendMessage(const std::string& alias, const std::string& message, connection::ClientSocket& socket)
{
    char groupSeparator = char(29);
    std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now().time_since_epoch());
    long time = ms.count();
    std::string formattedMessage = alias + groupSeparator + message + groupSeparator + std::to_string(time);

    bool isSent = socket.makeConnection(formattedMessage);
    socket.closeConnection();
    return isSent;
}

void ChatServer::startListeningThread(const std::string& alias)
{
    std::stringstream message;
    message << "enter " << alias << std::endl;
    this->listeningThread = new std::thread(&connection::ClientSocket::makeConnection, this->listeningSocket, message.str());
}

ChatServer::~ChatServer()
{
    this->listeningSocket->closeConnection();
    this->listeningThread->join();
    delete this->listeningThread;
}

}
}
