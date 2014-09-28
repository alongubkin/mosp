#include "server.h"
#include "logger.h"
#include "password_utils.h"

Server::Server(int port)
{
	ENetAddress address;
	address.host = ENET_HOST_ANY;
	address.port = port;

	server = enet_host_create(&address, // the address to bind the server host to
		2000,	  // allow up to 2000 clients
		2,		  // allow up to 2 channels to be used, 0 and 1
		0,		  // assume any amount of incoming bandwidth
		0);		  // assume any amount of outgoing bandwidth

	if (server == NULL)
		Logger::Error("Enet failed to create a host.");
	
	ticker = new Ticker(this);

	mongo::client::initialize();
}

Server::~Server()
{ 
	delete ticker;
	enet_host_destroy(server);
}

void Server::Run()
{
	try
	{
		db = new mongo::DBClientConnection();
		db->connect("localhost");

		Logger::Info("Database Connection OK");
		CreateFakeUsers();
	}
	catch (const mongo::DBException &e)
	{
		std::cout << "Database connection failed: " << e.what() << std::endl << "exiting...";

		getchar();
		return;
	}

	isRunning = true;
	tickerThread = std::thread(&Ticker::Run, ticker);

	Listen();

	tickerThread.join();
}

void Server::Listen()
{
	Logger::Info("Server is now online and listening to incoming traffic");

	ENetEvent event;

	while (isRunning)
	{
		while (enet_host_service(server, &event, 16) > 0)
		{
			switch (event.type)
			{
			case ENET_EVENT_TYPE_CONNECT:
				OnConnect(event);
				break;

			case ENET_EVENT_TYPE_RECEIVE:
				OnReceive(event);
				break;

			case ENET_EVENT_TYPE_DISCONNECT:
				OnDisconnect(event);
				break;
			}
		}
	}
}

void Server::OnConnect(const ENetEvent &evt)
{
	// Create a new client and push it to the client list
	Client* client = new Client(evt.peer, nextAvailableId);
	clients.push_back(client);

	// Assign the client object to the peer
	evt.peer->data = client;
	nextAvailableId++;

	Logger::Info("A new client connected from %x:%u assigned with id %d", evt.peer->address.host, evt.peer->address.port, nextAvailableId);
}

void Server::OnReceive(const ENetEvent &evt)
{
	Client* client = static_cast<Client*>(evt.peer->data);
	evt.packet->userData = client;
	client->QueuePacket(evt.packet);
}

void Server::OnDisconnect(const ENetEvent &evt)
{
	// Find the client using the peer object
	Client *client = static_cast<Client*>(evt.peer->data);

	// Remove the client from the clients vector
	clients.erase(std::remove(clients.begin(), clients.end(), client), clients.end());

	Logger::Info("Client %d has disconnected", client->GetId());

	delete client;
	evt.peer->data = nullptr;
}

void Server::CreateFakeUsers()
{
	if (db->count("mosp.users") > 0)
		return;

	std::cout << "It looks like there are no users in the database." << std::endl
			  << "Would you like to add one [Y/n]? ";

	char input;
	std::cin >> input;

	if (input != 'Y' && input != 'y')
		return;

	std::string username;
	std::cout << "Username: ";
	std::cin >> username;

	std::string password;
	std::cout << "Password: ";
	std::cin >> password;

	std::string salt = mosp::GenerateSalt();

	mongo::BSONObjBuilder builder;
	builder.append("username", username);
	builder.append("password", mosp::HashPassword(password, salt));
	builder.append("salt", salt);

	db->insert("mosp.users", builder.obj());

	std::cout << "User " << username << " added successfully." << std::endl;
}