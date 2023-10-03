#include "Server.hpp"

static void privmsg_toUser(Client *client, String &entry, vector<Client *> clientList)
{
    String  msg;
    String  destNickname = entry.getWord(1);
    int     destFd       = Utils::findClientFd(destNickname, clientList);

    if (destFd == -1)//le destinataire n'existe pas
    {
        sendMsg(CODE_401(client->getNickname().c_str()), client->getFd());
        return ;
    }

    if (entry.wordCount() == 2)
        msg = entry.getWord(2);
    else
        for (int i = 2; i < entry.wordCount(); i++)
            msg += entry.getWord(i) + " ";
    
    msg += "\r\n";

    sendMsg(PRIVMSG(client->getNickname().c_str(), destNickname.c_str(), msg.c_str()), destFd);//envoi du msg
    sendMsg(CODE_302(client->getNickname().c_str(), destNickname.c_str()), client->getFd());//confirmaion envoi
}

static void privmsg_toChannel(Client *client, String &entry, vector<Channel *> channelList)
{
    String  msg;
    String  destChannel = entry.getWord(1);
    int     channelIdx = Utils::findChannelIndex(destChannel, channelList);

    if (channelIdx == -1)//channel existe pas
    {
        sendMsg(CODE_401(client->getNickname().c_str()), client->getFd());
        return ;
    }

    if (entry.wordCount() == 2)
        msg = entry.getWord(2);
    else
        for (int i = 2; i < entry.wordCount(); i++)
            msg += entry.getWord(i) + " ";
    
    msg += "\r\n";

    channelList[channelIdx]->diffuseMsg(PRIVMSG(client->getNickname().c_str(), destChannel.c_str(), msg.c_str()));
    sendMsg(CODE_302(client->getNickname().c_str(), destChannel.c_str()), client->getFd());//confirmaion envoi
}

static int  privmsg_checkFormat(String &entry)
{
    int     type = 0;
    int     nbWords = entry.wordCount();
    int     i;

    for (i = 0; entry[i] == ' '; i++) ;

    if (entry[i] == '#')
        type = 1;
    else
        type = 2;
    
    if (nbWords <= 1)
        return (0);

    if (nbWords == 2)
        return (type);

    if (entry.getWord(2) != ":")
        return (0);

    return (type);
}

void    Server::privMsg(Client *client, String &entry)
{
    entry.rmWord(1);

    if (privmsg_checkFormat(entry) == 1)
        privmsg_toChannel(client, entry, channelList);
    else if (privmsg_checkFormat(entry) == 2)
        privmsg_toUser(client, entry, clientList);
    else
        sendMsg("privmsg: bad input", client->getFd());    
}