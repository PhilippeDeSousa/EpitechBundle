#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include <QThread>
#include "StreamHandler.hpp"
#include "OpusHandler.hpp"
#include "PacketManager.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ConnectButton_clicked()
{
    QString ip = ui->InputIP->toPlainText();
    QHostAddress addr(ip);

    QString portStr = ui->InputPort->toPlainText();
    quint16 port = portStr.toUShort();

    QString username = ui->InputUsername->toPlainText();

    auto func = [&, addr, port, username]{
        UDPClient udpClient(this, addr, port);
        MainLoop(udpClient, username, ui);
    };
    QThread *thread = QThread::create(func);
    thread->start();
}

[[noreturn]] void MainWindow::MainLoop(UDPClient &udpClient, QString username, Ui::MainWindow *ui) const
{
    auto sh = new Babel::StreamHandler;
    auto om = new Babel::OpusHandler;

    while (true) {
        TxData(udpClient, username, sh, om);
        if (udpClient.HasRxData()) {
            QString destUsername = ui ? ui->ComboBoxDestUsername->currentText() : QString("");
            RXDataEvent(udpClient, destUsername, sh, om);
        }
    }
}

void MainWindow::TxData(UDPClient &udpClient, QString username, Babel::StreamHandler *sh, Babel::OpusHandler *om) const
{
    std::vector<float> *raw = sh->getInputFromList();
    if (raw != nullptr) {
        auto encoded = om->encode(*raw);
        if (encoded) {
            QByteArray usernamePacket = PacketManager::CreateUsernamePacket(username);
            udpClient.Send(usernamePacket);
            QByteArray packet = PacketManager::CreateSoundPacket(username, *encoded);
            udpClient.Send(packet);
        }
    }
}

void MainWindow::RXDataEvent(UDPClient &udpClient, QString destUsername, Babel::StreamHandler *sh, Babel::OpusHandler *om) const
{
    QByteArray packet = udpClient.Receive();
    if (PacketManager::IsSoundPacketForMe(packet, destUsername)) {
        qDebug() << "Received sound from: " << destUsername;
        std::vector<unsigned char> *raw = PacketManager::getSoundFromPacket(packet);
        if (raw) {
            auto decoded = om->decode(*raw);
            sh->addOutputToList(decoded);
        }
    } else if (PacketManager::getPacketType(packet) == PacketManager::PacketType::Username) {
        QString newUsername = PacketManager::getUsernameFromUsernamePacket(packet);
        if (ui->ComboBoxDestUsername->findText(newUsername) == -1)
            ui->ComboBoxDestUsername->addItem(newUsername);
    }
}

