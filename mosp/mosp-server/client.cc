#include "client.h"

Client::~Client() 
{
	delete peer;
}

void Client::QueueMessage(const mosp::BaseMessage *message)
{
	incomingMessages.push(message);
}