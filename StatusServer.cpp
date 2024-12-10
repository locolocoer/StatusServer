#include "ConfigMgr.h"
#include <iostream>
#include "msg.grpc.pb.h"
#include <grpcpp/grpcpp.h>
#include "StatusServiceImpl.h"
#include <boost/asio.hpp>
void RunServer() {
	auto& inst = ConfigMgr::Inst();
	std::string server_add = inst["StatusServer"]["Host"] + ":" + inst["StatusServer"]["Port"];
	StatusServiceImpl service;
	grpc::ServerBuilder builder;
	builder.AddListeningPort(server_add, grpc::InsecureServerCredentials());
	builder.RegisterService(&service);
	std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
	std::cout << "Server listening on " << server_add << std::endl;
	boost::asio::io_context ioc;
	boost::asio::signal_set signals(ioc, SIGINT, SIGTERM);
	signals.async_wait([&](boost::system::error_code ec, int signal_number) {
		if (!ec) {
			std::cout << "server shutdown!" << std::endl;
			server->Shutdown();
		}
		});
	std::thread([&ioc]() {
		ioc.run();
		}).detach();
	server->Wait();
	ioc.stop();
}
int main() {
	try {
		RunServer();
	}
	catch (std::exception& e) {
		std::cout << "Error occured: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	return 0;
}