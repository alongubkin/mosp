#include "client.h"

Client::~Client() 
{
	delete peer;
}