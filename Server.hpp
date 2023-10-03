#pragma once

#include <iostream>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <vector>
#include <fcntl.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>

#include "libX.hpp"
#include "Client.hpp"
#include "Utils.hpp"
#include "Channel.hpp"

#define vector          std::vector
#define BUFFER_SIZE     100

class Client;
class Channel;

class Server
{
        public:
                Server();
                Server(char **argv);
                ~Server();

                void    servEmpty();
                void    servCheckSockets(fd_set &sockets);
                void    servNewConnection();
                void    servTreatClient(Client *client);
                void    servReceive(Client *client);

                void    pass(Client *client, String &entry);
                void    nick(Client *client, String &entry);
                void    user(Client *client, String &entry);
                void    kick(Client *client, String &cmd, String &entry);
                //void    privMsg(Client *client, String &entry);

                vector<Channel *>       channelList;
                bool    CheckChannelName(String name);
                bool    IfChannelExist(String name);
                void    join(Client *client, String cmd, String entry);
               // void    privMsg(Client *client, String cmd, String entry);
                //void    ping();
                //void    invite();

                int     getFdMax();
                int     getEntrySocket();
                
                vector<Client *>        clientList;
                //vector<Channel *>       channelList;

        private:
                int             EntrySocket;
                String          Hostname;
                String          password;
};

void    sendMsg(const char *msg, int fd);