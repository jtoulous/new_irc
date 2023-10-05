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
#include "Define.hpp"

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

                void    servCheckSockets(fd_set &sockets);
                void    servNewConnection();
                void    servTreatClient(Client *client);
                int     servReceive(Client *client);

                void    pass(Client *client, String &entry);
                void    nick(Client *client, String &entry);
                void    user(Client *client, String &entry);
                void    kick(Client *client, String &cmd, String &entry);
                void    privMsg(Client *client, String &entry);
                void    join(Client *client, String &entry);
                void    invite(Client *client, String &entry);

                bool    CheckChannelName(String name);
                bool    IfChannelExist(String name);
                bool    IfPasswordIsOk(String name, String password);
                void    SendMessageToClient(int client_fd, Client *client, int index_chan);
                Client* IfGuestExist(String name);
                
                void    Topic(Client *client, String entry);

                int     getFdMax();
                int     getEntrySocket();
                
                vector<Client *>        clientList;
                vector<Channel *>       channelList;

        private:
                int             EntrySocket;
                String          Hostname;
                String          password;
};

void    sendMsg(String msg, int fd, String nick);