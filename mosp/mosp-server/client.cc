#include "client.h"

Client::~Client() 
{
	delete peer;
}

template <typename T>
void Client::Send(const T& message)
{
	unsigned char* data = new unsigned char[message.ByteSize()];
	message.SerializeToArray(data, message.ByteSize());

	ENetPacket* packet = enet_packet_create(data, message.ByteSize(), ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet); //Handles the deallocation of the packet as well so we won't need to call enet_packet_destroy()

	delete data;
}

void Client::HandleJoinRequestMessage(const mosp::JoinRequestMessage& message)
{
	printf("Name: %s\n", message.name().c_str());

	mosp::Vector3* position = new mosp::Vector3();
	position->set_x(0);
	position->set_y(0);
	position->set_z(0);

	mosp::JoinResponseMessage response;
	response.set_success(true);
	response.set_client_id(this->GetId());
	response.set_allocated_position(position);

	Send(response);
}
