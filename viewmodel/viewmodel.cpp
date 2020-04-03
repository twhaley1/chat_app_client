#include <sstream>

#include "viewmodel.h"
#include "utils/utils.h"

namespace vm
{

ViewModel* ViewModel::vmodel = nullptr;

ViewModel* ViewModel::get()
{
    if (ViewModel::vmodel == nullptr)
    {
        ViewModel::vmodel = new ViewModel();
    }
    return ViewModel::vmodel;
}

ViewModel::ViewModel()
{
    this->messageListeningSocket = new model::chatserver::connection::ListeningClientSocket("127.0.0.1", 4555);
    this->messageListeningSocket->setMessageHandler(ViewModel::updateLog);
    this->stateListeningSocket = new model::chatserver::connection::ListeningClientSocket("127.0.0.1", 4650);
    this->stateListeningSocket->setMessageHandler(ViewModel::updateUsers);
    this->server = new model::chatserver::ChatServer(this->messageListeningSocket, this->stateListeningSocket);
}

void ViewModel::updateLog(const std::string& message)
{
    ViewModel::get()->addToLog(message);
}

void ViewModel::addToLog(const std::string& message)
{
    this->log << message;
    emit this->logChanged();
}

void ViewModel::updateUsers(const std::string &message)
{
    std::vector<std::string> tokens = utils::split(message, ":");
    ViewModel::get()->setUsers(tokens);
}

void ViewModel::setUsers(const std::vector<std::string> users)
{
    this->chatroomUsers.clear();
    this->chatroomUsers.insert(this->chatroomUsers.end(), users.begin(), users.end());
    emit this->usersChanged();
}

void ViewModel::join(const std::string& alias)
{
    this->alias = alias;
    this->server->startListeningThread(this->alias);
}

bool ViewModel::sendMessage(const std::string& message)
{
    model::chatserver::connection::ClientSocket messageSocket("127.0.0.1", 4500);
    return this->server->sendMessage(this->alias, message, messageSocket);
}

void ViewModel::leave()
{
    model::chatserver::connection::ClientSocket leaveMessageSocket("127.0.0.1", 4555);
    model::chatserver::connection::ClientSocket leaveStateSocket("127.0.0.1", 4650);

    std::stringstream message;
    message << "leave " << this->alias << std::endl;
    leaveMessageSocket.makeConnection(message.str());
    leaveStateSocket.makeConnection(message.str());

    leaveMessageSocket.closeConnection();
    leaveStateSocket.closeConnection();
}

const std::string ViewModel::getLog() const
{
    return this->log.str();
}

const std::vector<std::string>& ViewModel::getUsers() const
{
    return this->chatroomUsers;
}

const std::string& ViewModel::getAlias() const
{
    return this->alias;
}

ViewModel::~ViewModel()
{
    delete this->server;
    delete this->messageListeningSocket;
    delete this->stateListeningSocket;
}

}
