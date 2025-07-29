#pragma once

#include "rpcmessage.grpc.pb.h"

#include <grpcpp/grpcpp.h>

class MyClient {
public:
    explicit MyClient(std::shared_ptr<grpc::Channel> channel)
        : stub_(rpcmessage::RpcService::NewStub(channel)) {}

    void cutPositionChanged(int value) {
        grpc::ClientContext context;

        rpcmessage::GuiMessage request;
        request.mutable_cutposition()->set_pos(value);

        rpcmessage::GuiMessage response;
        grpc::Status status = stub_->SingleResponse(&context, request, &response);

        if (status.ok()) {
            std::cout << "Response: " << response.mutable_cutposition()->pos() << std::endl;
        } else {
            std::cerr << "RPC failed" << std::endl;
        }
    }

private:
    std::unique_ptr<rpcmessage::RpcService::Stub> stub_;
};
