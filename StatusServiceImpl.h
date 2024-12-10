#pragma once
#include <grpcpp/grpcpp.h>
#include "msg.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using message::GetChatReq;
using message::GetChatRsp;
using message::StatusService;
struct ChatServer {
	std::string host;
	std::string port;
};
class StatusServiceImpl final : public StatusService::Service
{
public:
	StatusServiceImpl();
	::grpc::Status GetChatServer(::grpc::ServerContext* context, const ::message::GetChatReq* request, ::message::GetChatRsp* response) override;
	std::vector<ChatServer> _server;
	int _index_server;
};

