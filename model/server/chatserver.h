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
    ChatServer(connection::ClientSocket* listeningSocket);
    ~ChatServer();

    bool sendMessage(const std::string& alias, const std::string& message, connection::ClientSocket& socket);
    void startListeningThread(const std::string& alias);

private:
    connection::ClientSocket* listeningSocket;
    std::thread* listeningThread;
};

}
}

#endif // CHATSERVER_H
