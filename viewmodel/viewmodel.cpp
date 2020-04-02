#include "viewmodel.h"

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
    this->listeningSocket = new model::chatserver::connection::ListeningClientSocket("127.0.0.1", 4555);
    this->listeningSocket->setMessageHandler(ViewModel::updateLog);
    this->server = new model::chatserver::ChatServer(this->listeningSocket);
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

const std::string ViewModel::getLog() const
{
    return this->log.str();
}

ViewModel::~ViewModel()
{
    delete this->server;
    delete this->listeningSocket;
}

}
