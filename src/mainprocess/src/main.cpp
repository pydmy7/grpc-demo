#include "widget.h"

#include <QApplication>

#include "rpcserviceimpl.hpp"

#include <memory>
#include <thread>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    std::shared_ptr<Widget> widget = std::make_shared<Widget>();
    widget->show();

    std::thread([widget]() {
        auto selected_port {0};
        RpcServiceImpl rpcServiceImpl(widget);
        grpc::ServerBuilder builder;
        builder.AddListeningPort("localhost:50051", grpc::InsecureServerCredentials(), &selected_port);
        builder.RegisterService(&rpcServiceImpl);

        std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
        server->Wait();
    }).detach();

    return app.exec();
}
