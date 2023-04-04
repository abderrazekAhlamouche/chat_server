#pragma once
#include<string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/socket.h>
#include <iostream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include "message.hpp"

#define buffer_size  1024
//class role 
//intitialise socket 
//recv and send data 

//class design 
//ctor takes the host name and port
//ctor initialises the connection 
//send/recv data  methods
//dtor closes initial socket , closes accept socket , freeaddrinfo 

class MSocket{
std::string hostname="";
std::string port="";
struct addrinfo hints,*host;
int sockFd; 
struct sockaddr client_address;
char buffer[buffer_size];

public:
MSocket(std::string  host, std::string port );
MSocket() = default ; 
void init();
void bindTo();
void listenTo(int max_clients);
void acceptConnections(int& clientFd);
bool sendMSocket(IMessage& msg ,int l_clientFd);
bool recvMSocket(IMessage& msg ,int l_clientFd);
/* inline int getClientFd()const
{
    return clientFd ; 
} */
virtual ~MSocket();
};
