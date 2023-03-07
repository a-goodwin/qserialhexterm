#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>
#include <QSystemTrayIcon>

#define CH0 QLatin1Char('0')

#define APP_VER_STR "1.16"

namespace Ui {
class MainWindow;
}

class QPushButton;
class QLineEdit;
class QHBoxLayout;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QSystemTrayIcon *ticon;
protected:
    QByteArray sender, receiver;
    QSerialPort serial;
    QList<QSerialPortInfo> ports;
    qint32 baudrate;
    QSerialPortInfo curSer;
    QTimer resendTimer, refreshTimer;
private slots:
    void on_serials_activated(int index);
    void onSerialData();
    void onSerialError(QSerialPort::SerialPortError error);
    void on_bClearTransmitter_clicked();
    void on_bClearReceiver_clicked();
    void on_bSend_clicked();
    void on_TimerUartRefresh();
    void on_bUartRefresh_clicked();
    void on_bConnect_clicked();
    void on_eBaudRate_activated(const QString &arg1);
    void on_bReSend_clicked(bool checked);
    void ticon_activated(QSystemTrayIcon::ActivationReason reason);


    void on_bAddScript_clicked(QString nm="", QString cmd="");
    void onScriptSendButton();
    void slScriptDelButtonClick(bool clicked);
    void onScriptDelButton(int defIdx);
    void on_bSaveScripts_clicked();

    void on_bClearScripts_clicked();
    void slScrTimer();
    void slRWUpdate();
private:
    void _disconn();
    void _fetchScriptsFromFile();
    void _saveScriptsToFile();

    Ui::MainWindow *ui;

    int m_curidx = -1;

    QList<QPushButton*> m_scrButs;
    QList<QHBoxLayout*> m_scrLays;
    QList<QPushButton*> m_scrDelButs;
    QList<QLineEdit*> m_scrNames;
    QList<QLineEdit*> m_scrCommands;

    QByteArray data;
    int rcount = 0;
    int wcount = 0;
    int lwcount = 0;
    QTimer *scrTimer;
};

#endif // MAINWINDOW_H
