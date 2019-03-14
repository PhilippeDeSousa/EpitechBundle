/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QLabel *UsernameLabel;
    QPlainTextEdit *InputUsername;
    QLabel *IPLabel;
    QPlainTextEdit *InputIP;
    QLabel *PortLabel;
    QPlainTextEdit *InputPort;
    QPushButton *ConnectButton;
    QLabel *DestUsernameLabel;
    QComboBox *ComboBoxDestUsername;
    QMenuBar *menuBar;
    QMenu *menuBonjour;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(400, 423);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        UsernameLabel = new QLabel(centralWidget);
        UsernameLabel->setObjectName(QStringLiteral("UsernameLabel"));

        verticalLayout->addWidget(UsernameLabel);

        InputUsername = new QPlainTextEdit(centralWidget);
        InputUsername->setObjectName(QStringLiteral("InputUsername"));

        verticalLayout->addWidget(InputUsername);

        IPLabel = new QLabel(centralWidget);
        IPLabel->setObjectName(QStringLiteral("IPLabel"));

        verticalLayout->addWidget(IPLabel);

        InputIP = new QPlainTextEdit(centralWidget);
        InputIP->setObjectName(QStringLiteral("InputIP"));

        verticalLayout->addWidget(InputIP);

        PortLabel = new QLabel(centralWidget);
        PortLabel->setObjectName(QStringLiteral("PortLabel"));

        verticalLayout->addWidget(PortLabel);

        InputPort = new QPlainTextEdit(centralWidget);
        InputPort->setObjectName(QStringLiteral("InputPort"));

        verticalLayout->addWidget(InputPort);

        ConnectButton = new QPushButton(centralWidget);
        ConnectButton->setObjectName(QStringLiteral("ConnectButton"));

        verticalLayout->addWidget(ConnectButton);

        DestUsernameLabel = new QLabel(centralWidget);
        DestUsernameLabel->setObjectName(QStringLiteral("DestUsernameLabel"));

        verticalLayout->addWidget(DestUsernameLabel);

        ComboBoxDestUsername = new QComboBox(centralWidget);
        ComboBoxDestUsername->addItem(QString());
        ComboBoxDestUsername->setObjectName(QStringLiteral("ComboBoxDestUsername"));

        verticalLayout->addWidget(ComboBoxDestUsername);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 31));
        menuBonjour = new QMenu(menuBar);
        menuBonjour->setObjectName(QStringLiteral("menuBonjour"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuBonjour->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        UsernameLabel->setText(QApplication::translate("MainWindow", "Username:", nullptr));
        InputUsername->setPlainText(QApplication::translate("MainWindow", "User1", nullptr));
        IPLabel->setText(QApplication::translate("MainWindow", "IP:", nullptr));
        InputIP->setPlainText(QApplication::translate("MainWindow", "127.0.0.1", nullptr));
        PortLabel->setText(QApplication::translate("MainWindow", "Port:", nullptr));
        InputPort->setPlainText(QApplication::translate("MainWindow", "1234", nullptr));
        ConnectButton->setText(QApplication::translate("MainWindow", "Connect", nullptr));
        DestUsernameLabel->setText(QApplication::translate("MainWindow", "Dest Username:", nullptr));
        ComboBoxDestUsername->setItemText(0, QApplication::translate("MainWindow", "Choose a Username from this list", nullptr));

        menuBonjour->setTitle(QApplication::translate("MainWindow", "Babe&l Client", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
