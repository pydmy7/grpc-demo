#include "widget.h"
#include "./ui_widget.h"

#include "myclient.hpp"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    myClient_ = std::make_unique<MyClient>(grpc::CreateChannel("localhost:50052", grpc::InsecureChannelCredentials()));

    connect(ui->horizontalSlider, &QSlider::valueChanged, this, [this](int value) {
        myClient_->cutPositionChanged(value);
    });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::setCutPosition(int pos)
{
    ui->horizontalSlider->setValue(pos);
}
