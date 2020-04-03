#ifndef VIEWMODEL_H
#define VIEWMODEL_H

#include <QObject>

#include <string>
#include <vector>
#include <sstream>

#include "model/server/chatserver.h"
#include "model/server/connection/clientsocket.h"
#include "model/server/connection/listeningclientsocket.h"

namespace vm
{

class ViewModel : public QObject
{
    Q_OBJECT

public:
    static ViewModel* get();

private:
    static ViewModel* vmodel;
    static void updateLog(const std::string& message);
    static void updateUsers(const std::string& message);

public:
    void join(const std::string& alias);
    bool sendMessage(const std::string& message);
    void leave();

    const std::string getLog() const;
    const std::vector<std::string>& getUsers() const;
    const std::string& getAlias() const;

signals:
    void logChanged();
    void usersChanged();

private:
    model::chatserver::ChatServer* server;
    model::chatserver::connection::ListeningClientSocket* messageListeningSocket;
    model::chatserver::connection::ListeningClientSocket* stateListeningSocket;

    std::string alias;
    std::stringstream log;
    std::vector<std::string> chatroomUsers;

    ViewModel();
    ~ViewModel();
    void addToLog(const std::string& message);
    void setUsers(const std::vector<std::string> users);
};

}

#endif // VIEWMODEL_H
