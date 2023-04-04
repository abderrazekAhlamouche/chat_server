#pragma once 
#include "message.hpp"
#include <memory>
class Client
{
    int m_clientFd;
    std::unique_ptr<Message> m_msg ;
    public:
    Client(int clientFd , std::unique_ptr<Message> msg =nullptr):
    m_clientFd{clientFd},
    m_msg{std::move(msg)}{}
    virtual ~Client()=default ; 
    int getClientFd()
    {
        return m_clientFd ;
    }
    std::string getClientName()
    {
        return m_msg->getSender() ;
    }
    std::string getMsgContent()const
    {
        return m_msg->getContent();
    }
    void setMsg(Message const& msg)
    {
        m_msg = std::make_unique<Message>(msg);
    }
    void generateId();
    void update();

};
