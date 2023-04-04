#include "MSocket.hpp"

MSocket::MSocket(std::string host , std::string port  ):
hostname(host),port(port){}

void MSocket::init()
{
    int result = 0 ;
    
memset(&hints, 0, sizeof(struct addrinfo));		/* memset_s() */
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

     if(getaddrinfo( hostname.c_str(), port.c_str(), &hints, &host) != 0)
     throw std::runtime_error("failed to get address info") ; 

     /*create a socket*/
     if((sockFd = socket(host->ai_family,host->ai_socktype,host->ai_protocol)) < 0)
     throw std::runtime_error("failed to create socket"); 
}

    void MSocket::bindTo(){
        init();
     /*bind the server to a socket */
     if(bind(sockFd,host->ai_addr,host->ai_addrlen)==-1)
     throw std::runtime_error("failed to bind socket"); 
    }

    void MSocket::listenTo(int max_clients)
    {
     /*listen for incomming connection */
     if (listen(sockFd, max_clients) == -1)
        throw std::runtime_error("failed to listen for connections");
    }

void MSocket::acceptConnections(int& clientFd)
{
    /*accept a new connection */
    socklen_t client_len = sizeof(client_address);
    if ((clientFd = accept(sockFd, &client_address, &client_len)) == -1)
     throw std::runtime_error("failed to accept connection");
    std::cout << "Socket initialised successfully for address " + hostname + " Port " + port + "\n";
    std::cout << "accepting new client ... \n";
}

bool MSocket::recvMSocket(IMessage& msg ,int l_clientFd )
{
    int reception_size ; 
    reception_size = recv(l_clientFd,buffer,buffer_size,0);
     if(reception_size == 0)
    {
        std::cerr << " client disconnected "<<errno<< "\n" ; 
           return false ; 
    }else if(reception_size < 0 )
    {
         perror("Error receiving data from server");
         std::cerr << " network error :  "<<errno<< "\n";
         return false ;  
    }
    /* deserialization */
    std::string serialized_object(buffer, reception_size);
    msg.ideSerialize(serialized_object);
    return true ; 
}

bool MSocket::sendMSocket(IMessage& msg ,int l_clientFd)
{
  std::string serializedMsg = msg.iserialize();  
 if(send(l_clientFd,serializedMsg.c_str(),serializedMsg.length(),0)==-1)
 {
    std::cout << "message could not be sent !\n" ;
    return false ; 
 }
 return true ; 
}

MSocket::~MSocket()
{
    /* close-up */
	freeaddrinfo(host);
	close(sockFd);
}

