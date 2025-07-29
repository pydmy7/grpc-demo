#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class MyClient;

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

    void setCutPosition(int pos);

private:
    Ui::Widget *ui;

    std::unique_ptr<MyClient> myClient_;
};
#endif // WIDGET_H
