#ifndef VIEWMODEL_H
#define VIEWMODEL_H

#include <QObject>

#include <string>
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

public:
    void join(const std::string& alias);
    bool sendMessage(const std::string& message);

    const std::string getLog() const;

signals:
    void logChanged();

private:
    ViewModel();
    ~ViewModel();

    model::chatserver::ChatServer* server;
    model::chatserver::connection::ListeningClientSocket* listeningSocket;

    std::string alias;
    std::stringstream log;

    void addToLog(const std::string& message);
};

}

#endif // VIEWMODEL_H
