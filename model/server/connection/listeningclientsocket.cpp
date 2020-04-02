#include <unistd.h>

#include "listeningclientsocket.h"

namespace model
{
namespace chatserver
{
namespace connection
{

ListeningClientSocket::ListeningClientSocket(const std::string& host, int port) : ClientSocket (host, port)
{
    this->running = true;
    this->giveToMessageHandler = nullptr;
}

void ListeningClientSocket::setMessageHandler(void(*messageHandler)(const std::string&))
{
    this->giveToMessageHandler = messageHandler;
}

bool ListeningClientSocket::makeConnection(const std::string& message)
{
    bool isSendSuccessful = ClientSocket::makeConnection(message);
    if (isSendSuccessful)
    {
        ssize_t numberOfReadBytes = 0;
        char byteBuffer[1024] = {0};
        while (numberOfReadBytes >= 0 && this->running)
        {
            numberOfReadBytes = read(this->getSock(), byteBuffer, 1024);
            if (numberOfReadBytes > 0)
            {
                std::string receivedMessage(byteBuffer);
                if (this->giveToMessageHandler != nullptr)
                {
                    this->giveToMessageHandler(receivedMessage);
                }
                for (int i = 0; i < 1024; i++)
                {
                    byteBuffer[i] = 0;
                }
                numberOfReadBytes = 0;
            }
        }
    }
    return true;
}

void ListeningClientSocket::closeConnection()
{
    ClientSocket::closeConnection();
    this->running = false;
}

}
}
}
