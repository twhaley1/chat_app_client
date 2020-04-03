#include <qt5/QtConcurrent/QtConcurrent>

#include <chrono>
#include <thread>
#include <sstream>

#include "chatserver.h"

namespace model
{
namespace chatserver
{

ChatServer::ChatServer(connection::ClientSocket* messageListeningSocket, connection::ClientSocket* stateListeningSocket)
{
    this->messageListeningSocket = messageListeningSocket;
    this->messageListeningThread = nullptr;
    this->stateListeningSocket = stateListeningSocket;
    this->stateListeningThread = nullptr;
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
    this->messageListeningThread = new std::thread(&connection::ClientSocket::makeConnection, this->messageListeningSocket, message.str());
    this->stateListeningThread = new std::thread(&connection::ClientSocket::makeConnection, this->stateListeningSocket, message.str());
}

ChatServer::~ChatServer()
{
    this->messageListeningSocket->closeConnection();
    this->messageListeningThread->join();
    this->stateListeningSocket->closeConnection();
    this->stateListeningThread->join();
    delete this->messageListeningThread;
    delete this->stateListeningThread;
}

}
}
