#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <string>

namespace model
{
namespace chatserver
{
namespace connection
{

class ClientSocket
{
public:
    ClientSocket(const std::string& host, int port);
    virtual ~ClientSocket();

    virtual bool makeConnection(const std::string& message);
    virtual void closeConnection();

    const std::string& getHost() const;
    int getPort() const;

protected:
    int getSock() const;

private:
    std::string host;
    int port;

    int sock;
};

}
}
}

#endif // CLIENTSOCKET_H
