#pragma once
#include "MSocket.hpp"
#include "message.hpp"
#include "string"
#include <memory>
#include "client.hpp"
#include <vector>
#include <thread>
#include <algorithm>
#include <atomic>
#include <mutex>

#define MAX_CLIENTS 10 

class Server{
   const std::string m_hostname = "127.0.0.1" ; 
    std::string m_port ;
    std::atomic<bool> stopFlag ;
    std::unique_ptr<MSocket> mSocket ;   
    std::vector<std::shared_ptr<Client>> clients ;
    std::vector<std::thread> threads ;  
    std::mutex m_mutex;
    public:
    Server() = default ; 
    virtual ~Server() = default ; 
    void setupServer();
    void initialiseSocket();
    void start();
    void client_handler(int clientFd);
    void showNbConnectedClients();
    void addClient(std::shared_ptr<Client> client);
    void removeClient(std::shared_ptr<Client> client);
    std::shared_ptr<Client> getClientByFd(int clientFd)const;
};