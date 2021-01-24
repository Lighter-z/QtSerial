#include "widget.h"
#include "ui_widget.h"
#include <QSerialPortInfo>
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    QStringList serial_name_port;

    serial_port_ = new QSerialPort(this);

    connect(serial_port_, SIGNAL(readyRead()), this, SLOT(SerialPortReadyReadSlot()));

    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        serial_name_port << info.portName();
    }

    ui->SerialComboBox->addItems(serial_name_port);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_OpenButton_clicked()
{
    QSerialPort::BaudRate baud_rate = QSerialPort::Baud115200;;
    QSerialPort::DataBits data_bits = QSerialPort::Data8;
    QSerialPort::StopBits stop_bits = QSerialPort::OneStop;
    QSerialPort::Parity check_bits = QSerialPort::NoParity;

    if(ui->BaudRateComboBox->currentText() == "115200") {
        baud_rate = QSerialPort::Baud115200;
    } else if(ui->BaudRateComboBox->currentText() == "9600") {
        baud_rate = QSerialPort::Baud9600;
    } else if(ui->BaudRateComboBox->currentText() == "4800") {
        baud_rate = QSerialPort::Baud4800;
    }

    if(ui->DataBitsComboBox->currentText() == "5") {
        data_bits = QSerialPort::Data5;
    } else if(ui->DataBitsComboBox->currentText() == "6") {
        data_bits = QSerialPort::Data6;
    } else if(ui->DataBitsComboBox->currentText() == "7") {
        data_bits = QSerialPort::Data7;
    } else if(ui->DataBitsComboBox->currentText() == "8") {
        data_bits = QSerialPort::Data8;
    }

    if(ui->StopBitsComboBox->currentText() == "1") {
        stop_bits = QSerialPort::OneStop;
    } else if(ui->StopBitsComboBox->currentText() == "1.5") {
        stop_bits = QSerialPort::OneAndHalfStop;
    } else if(ui->StopBitsComboBox->currentText() == "2") {
        stop_bits = QSerialPort::TwoStop;
    }

    if(ui->CheckBitsComboBox->currentText() == "none") {
        check_bits = QSerialPort::NoParity;
    }

    serial_port_->setPortName(ui->SerialComboBox->currentText());
    serial_port_->setBaudRate(baud_rate);
    serial_port_->setDataBits(data_bits);
    serial_port_->setStopBits(stop_bits);
    serial_port_->setParity(check_bits);

    if(serial_port_->open(QIODevice::ReadWrite) == true) {
        QMessageBox::information(this, "提示", "成功");
    } else {
        QMessageBox::critical(this, "提示", "失败");
    }

}

void Widget::on_CloseButton_clicked()
{
    serial_port_->close();
}

void Widget::on_SendButton_clicked()
{
    serial_port_->write(ui->SendEdit->text().toLocal8Bit().data());
}

void Widget::on_ClearButton_clicked()
{
    ui->RecvEdit->clear();
}

void Widget::SerialPortReadyReadSlot()
{
    QString buf;
    buf = QString(serial_port_->readAll());
    ui->RecvEdit->appendPlainText(buf);
}
