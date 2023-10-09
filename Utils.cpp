#include "Utils.hpp"

Utils::Utils()
{}

String  Utils::getCmd(String entry)
{
    String cmd;

    cmd = entry.substr(0, entry.find(' '));
    return (cmd);
}

int     Utils::findClientFd(String nickname, vector<Client *> &clientList)
{
    size_t i = 0;
    
    while(i != clientList.size())
    {
        if (clientList[i]->getNickname() == nickname)
            return (clientList[i]->getFd());
        i++;
    }
    return (-1);
}

String  Utils::findClientNick(int fd, vector<Client *> &clientList)
{
    String  notFound;

    for (int i = 0; i < (int)clientList.size(); i++)
    {
        if (clientList[i]->getFd() == fd)
            return (clientList[i]->getNickname());
    }
    return (notFound);
}

int     Utils::findClientIndex(int fd, vector<Client *> &clientList)
{
    for (int i = 0; i < (int)clientList.size(); i++)
    {
        if (clientList[i]->getFd() == fd)
            return (i);
    }
    return (-1);
}

int     Utils::findChannelIndex(String name, vector<Channel *> &channelList)
{
    size_t i = 0;
    
    while(i != channelList.size())
    {
        if (channelList[i]->getName() == name)
            return (i);
        i++;
    }
    return (-1);
}

bool    Utils::nicknameAvailable(String &nickname, vector<Client *> &clientList)
{
    for (int i = 0; i < (int)clientList.size(); i++)
        if (clientList[i]->getNickname() == nickname)
            return (false);
    return (true);
}

bool    Utils::usernameAvailable(String &username, vector<Client *> &clientList)
{
    for (int i = 0; i < (int)clientList.size(); i++)
        if (clientList[i]->getUsername() == username)
            return (false);
    return (true);
}

int Utils::passSpace(String str) {

    int i = 0;
    while (str[i] && str[i] == ' ')
        i++;
    return (i);
}

bool    Utils::modValidChar(char ch)
{
    if (ch != '+' && ch != '-' && ch != 'i' && ch != 't' && ch != 'k' && ch != 'l' && ch != 'o')
        return (false);
    return (true);
}

void    Utils::bye(Server *serv)
{
    for (int i = 0; i < (int)serv->channelList.size(); i++)
        delete serv->channelList[i];
    
    for (int i = 0; i < (int)serv->clientList.size(); i++)
    {
        close (serv->clientList[i]->getFd());
        delete serv->clientList[i];
    }

    close (serv->getEntrySocket());
}

/*void    Utils::rmFromServer(int fdTarget, vector<Client *> &clientList, vector<Channel *> &channelList)
{
    Client *tmp;

    for (int i = 0; i < channelList.size(); i++) //checker les channel ou il etait
    {
        vector<int> users = channelList[i]->getUsers();
        vector<int> admins = channelList[i]->getAdmins();
        int         owner = channelList[i]->getOwner();

        for (int u = 0; u < users.size(); u++)//list des users
        {
            if (users[i] == fdTarget)
            {
                users.erase(users.begin() + i);           
                break;
            }
        }

        for (int a = 0; a < admins.size(); a++)//admin
        {
            if (admins[i] == fdTarget)
            {
                admins.erase(admins.begin() + i);
                break;
            }
        }

        if (owner == fdTarget)//transfert droit d'owner 
        {
            if (admins.size() != 0)
                channelList[i]->setOwner() = admins[0];
            else if (users.size() != 0)
                channelList[i]->setOwner() = users[0];
            else
            {
                channelList.erase(channelList.begin() + i);
                i--;
            }
        }
    }


    for (int i = 0; i < clientList.size(); i++)
    {
        if (fdTarget == clientList[i]->getFd())
        {
            tmp = clientList[i];
            clientList.erase(clientList.begin() + i);
            close (fdTarget);
            delete tmp;
        }
    }    
}*/
