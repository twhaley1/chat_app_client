#ifndef LISTENINGCLIENTSOCKET_H
#define LISTENINGCLIENTSOCKET_H

#include "../chatserver.h"
#include "clientsocket.h"

namespace model
{
namespace chatserver
{
namespace connection
{

class ListeningClientSocket : public ClientSocket
{
public:
    ListeningClientSocket(const std::string& host, int port);

    bool makeConnection(const std::string& message) override;
    void closeConnection() override;
    void setMessageHandler(void(*messageHandler)(const std::string&));

private:
    volatile bool running;
    void(*giveToMessageHandler)(const std::string&);
};

}
}
}

#endif // LISTENINGCLIENTSOCKET_H
