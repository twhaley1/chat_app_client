#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <string>
#include <vector>
#include <thread>

#include "connection/clientsocket.h"

namespace model
{
namespace chatserver
{

class ChatServer
{
public:
    ChatServer(connection::ClientSocket* messageListeningSocket, connection::ClientSocket* stateListeningSocket);
    ~ChatServer();

    bool sendMessage(const std::string& alias, const std::string& message, connection::ClientSocket& socket);
    void startListeningThread(const std::string& alias);

private:
    connection::ClientSocket* messageListeningSocket;
    std::thread* messageListeningThread;

    connection::ClientSocket* stateListeningSocket;
    std::thread* stateListeningThread;
};

}
}

#endif // CHATSERVER_H
