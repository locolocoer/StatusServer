#include "StatusServiceImpl.h"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "ConfigMgr.h"
std::string generate_unique_string() {
    auto uid = boost::uuids::random_generator()();
    std::string unique_s = to_string(uid);
    return unique_s;
}


StatusServiceImpl::StatusServiceImpl() :_index_server(0)
{
    auto& inst = ConfigMgr::Inst();
    ChatServer server;
    server.host = inst["ChatServer1"]["Host"];
    server.port = inst["ChatServer1"]["Port"];
    _server.push_back(server);
    server.host = inst["ChatServer2"]["Host"];
    server.port = inst["ChatServer2"]["Port"];
    _server.push_back(server);
}

::grpc::Status StatusServiceImpl::GetChatServer(::grpc::ServerContext* context, const::message::GetChatReq* request, ::message::GetChatRsp* response)
{
    _index_server = (_index_server++) % (_server.size());
    auto& chatserver = _server[_index_server];
    response->set_host(chatserver.host);
    response->set_port(chatserver.port);
    response->set_token(generate_unique_string());
    response->set_error(0);
    return grpc::Status::OK;
}
