#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QSerialPort>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    QSerialPort *serial_port_;

private slots:
    void on_OpenButton_clicked();

    void on_CloseButton_clicked();

    void on_SendButton_clicked();

    void on_ClearButton_clicked();

    void SerialPortReadyReadSlot();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
