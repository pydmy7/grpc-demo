#pragma once

#include "rpcmessage.grpc.pb.h"
#include "widget.h"

#include <grpcpp/grpcpp.h>

#include <memory>

class Widget;

class RpcServiceImpl final : public rpcmessage::RpcService::Service {
public:
    explicit RpcServiceImpl(std::shared_ptr<Widget> widget) : widget_(widget) {}

    grpc::Status SingleResponse(grpc::ServerContext* /*context*/, const rpcmessage::GuiMessage* request, rpcmessage::GuiMessage* response) override {
        if (request->has_cutposition()) {
            auto pos = request->cutposition().pos();
            widget_->setCutPosition(pos);
            response->mutable_cutposition()->set_pos(pos);
        }

        return grpc::Status::OK;
    }


private:
    std::shared_ptr<Widget> widget_;
};
