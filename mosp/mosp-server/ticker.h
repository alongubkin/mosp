#ifndef _TICKER_H
#define _TICKER_H

class Server;

class Ticker
{
public:
	Ticker(const Server* server) : server(server) {}
	~Ticker() {};
	
	void Initialize();
	void Run();
	void HandleMesssage();

private:
	const Server* server;
};

#endif