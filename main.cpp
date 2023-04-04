#include <iostream>
#include "MSocket.hpp"
#include "message.hpp"
#include <algorithm>
#include <thread>
#include<vector>
#include "server.hpp"

using namespace std ; 

// void client_handler(int clientFd )
// {
//     while (1)
// {
//     /* code */
//     Message msg ;  
//   // m_socket.recvMSocket(msg);
//     int reception_size; 
//     char buffer[buffer_size] ; 
//     reception_size = recv(clientFd,buffer,buffer_size,0);
//     /* deserialization */
//     if (reception_size == 0)
//     {
//         cout << "client disconnected \n" ;
//         break ; 
//     }
//     std::string serialized_object(buffer, reception_size);
//     msg.ideSerialize(serialized_object);
//    //Message* l_msg = dynamic_cast<Message*>(msg);
//    cout << "message received : \n";
//    cout << "sender : "<< msg.getSender() << "\n";
//    cout << "message : "<< msg.getContent()<< "\n";
//    cout << "sending reversed content ...\n";
//    string content = msg.getContent();
//     msg.setContent(content);
//    // m_socket.sendMSocket(msg);
//     std::string serializedMsg = msg.iserialize();  
//     if(send(clientFd,serializedMsg.c_str(),serializedMsg.length(),0)==-1)
//     {
//      std::cout << "message could not be sent !\n" ;
//     }
// }
// }

int main()
{
   /*  //declaring a socket 
    string  hostname = "127.0.0.1";
    string  port = "12000";
    vector<thread> threads ; 
    MSocket m_socket(hostname,port);
   if( !m_socket.init(max_client))
   {
    cout << "socket initialization failed \n aborting program ... " ; 
    return 0;
   }
   while(1)
   {
    m_socket.acceptM();
    threads.emplace_back(thread(client_handler,m_socket.getClientFd())); 
   }
    
//   string message = "";
    // Limit the number of threads to MAX_CLIENTS
        //if (threads.size() == max_client) {
            for (auto& thread : threads) {
                thread.join();
            }
            threads.clear();
       // }

   
/*  */ 
Server m_server ; 
m_server.start();
    
}