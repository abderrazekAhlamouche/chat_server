#include "server.hpp"

void Server::setupServer()
{
    std::cout << "setting up server \n";
    std::cout << "port : ";
    getline(std::cin, m_port);
}

void Server::initialiseSocket()
{
    setupServer();
    mSocket = std::make_unique<MSocket>(m_hostname, m_port);
    try
    {
        mSocket->init();
        mSocket->bindTo();
        mSocket->listenTo(MAX_CLIENTS);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

void Server::start()
{
    initialiseSocket();
    stopFlag = false;
    while (true)
    {
        int clientfd = 0;
        try
        {
             mSocket->acceptConnections(clientfd);
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
            break;
        }

       threads.emplace_back(std::thread([this, clientfd]() { client_handler(clientfd); }));
       
    }
    stopFlag = true;

    // join all threads before exiting
     for (auto& thread : threads) {
        thread.join();
    }
    threads.clear(); 

}

void Server::client_handler(int clientFd)
{
    auto client = std::make_shared<Client>(clientFd);
    addClient(client);
    showNbConnectedClients();
    while (!stopFlag)
    {
        Message msg;
        if (!mSocket->recvMSocket(msg, clientFd))
        {
           // std::string clientName = client->getClientName()=!""? client->getClientName():"a client has ";
            std::cout << getClientByFd(clientFd)->getClientName()+ " disconnected \n";
            removeClient(client);
            showNbConnectedClients();
            break; 
        }
        client->setMsg(msg);

        // notify the rest of the clients
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            std::for_each(clients.begin(), clients.end(), [&](std::shared_ptr<Client> client)
                          {
        if(client->getClientFd() != clientFd)
            {
                mSocket->sendMSocket(msg,client->getClientFd());
            }
             });
        }
    }
    	close(clientFd);
}

void Server::showNbConnectedClients() 
{
    std::lock_guard<std::mutex> lock(m_mutex);
    std::cout << "number of connected clients : " << clients.size() << "\n";
}

void Server::addClient(std::shared_ptr<Client> client)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    clients.push_back(client);
}

void Server::removeClient(std::shared_ptr<Client> client)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    clients.erase(std::remove(clients.begin(), clients.end(), client), clients.end());
}

std::shared_ptr<Client> Server::getClientByFd(int clientFd)const
{
    auto it =  std::find_if(clients.begin(),clients.end(),[=](std::shared_ptr<Client> client){
        return clientFd==client->getClientFd();
    });
    if(it != clients.end())
    return *it;
    return nullptr;
}