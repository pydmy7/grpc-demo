#include "widget.h"
#include "./ui_widget.h"

#include "myclient.hpp"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    myclient_ = std::make_unique<MyClient>(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));

    connect(ui->horizontalSlider, &QSlider::valueChanged, this, [this](int value) {
        myclient_->cutPositionChanged(value);
    });
}

Widget::~Widget()
{
    delete ui;
}
