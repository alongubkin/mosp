#ifndef _H_EVENT_HANDLER
#define _H_EVENT_HANDLER

#include "client.h"
#include "proto/messages.pb.h"

class Server;

// TODO: this class should contain also the invoke 
// for the ExtesnionManager (C++ plugins) and PluginManager 
// (Javascript plugins)

class EventHandler
{
friend class Ticker;

public:
	EventHandler();
	~EventHandler();

private:
	void OnConnectRequest(Server* server, Client* sender, const mosp::ConnectRequestMessage& message);
	void OnPlayerDisconnect(Server* server, Client* sender, const mosp::PlayerDisconnectMessage& message);
	void OnPlayerMoved(Server* server, Client* sender, const mosp::PlayerMovedMessage& message);
};

#endif