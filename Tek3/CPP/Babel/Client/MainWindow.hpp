#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include "Udpclient.hpp"

namespace Ui {
class MainWindow;
}

/// This is the GUI where everything happens
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    /// When the user clicks on the connect button, it creates a udp socket and launches the main loop in a Qthread
    void on_ConnectButton_clicked();

private:
    /// This is where the buttons are
    Ui::MainWindow *ui;
    /// This is launched in a QThread and it sends the data read from the microphone to the server
    /// It also receives the audio datagram from the socket and plays it
    [[noreturn]] void MainLoop(UDPClient &udpCLient, QString username, Ui::MainWindow *ui) const;
    /// This is what gets the sound from portaudio, encodes it with Opus, and sends it over UDP
    void TxData(UDPClient &udpClient, QString username, Babel::StreamHandler *sh, Babel::OpusHandler *om) const;
    /// This is what gets the audio datagram from UDP, decodes it with Opus and plays it with PortAudio
    void RXDataEvent(UDPClient &udpClient, QString destUsername, Babel::StreamHandler *sh, Babel::OpusHandler *om) const;
};

#endif // MAINWINDOW_HPP
