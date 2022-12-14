#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <fundamental_window.h>
#include <advanced_window.h>
#include <qcustomplot.h>
#include <com.h>
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QtDebug>
#include <QDoubleValidator>

#define dataSendFreq 200    // 数据发送频率
#define dataRecvFreq 100    // 数据接收频率

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initialPlot(QCustomPlot *plot,int low_limit,int up_limit); // 初始化图表
    void scanPort();                                                // 检索串口
    uchar* floatTo4Bytes(float floatdata);                          // 浮点数转4字节
    void curveLegendSet(QLabel *curvelegend,int curveIndex);

    void initialValidator();

public:
    QList<FloatDatas> datalist;     // 全部数据帧存储
    int showPtr;                    // 显示指针
    int dataPtr;                    // 数据指针

    // 曲线图例样式表
    const QString m_bulue_SheetStyle    = "min-width:40px; min-height:4px; max-width:40px; max-height:4px; border:1px solid black; border-radius:2px; background:rgb(74,144,226)"; // 蓝色
    const QString m_red_SheetStyle      = "min-width:40px; min-height:4px; max-width:40px; max-height:4px; border:1px solid black; border-radius:2px; background:rgb(230,0,57)";   // 红色
    const QString m_yellow_SheetStyle   = "min-width:40px; min-height:4px; max-width:40px; max-height:4px; border:1px solid black; border-radius:2px; background:rgb(255,255,36)"; // 黄色
    const QString m_green_SheetStyle    = "min-width:40px; min-height:4px; max-width:40px; max-height:4px; border:1px solid black; border-radius:2px; background:rgb(2,179,64)";   // 绿色
    const QString m_orange_SheetStyle   = "min-width:40px; min-height:4px; max-width:40px; max-height:4px; border:1px solid black; border-radius:2px; background:rgb(254,98,31)";  // 橙色
    const QString m_purple_SheetStyle   = "min-width:40px; min-height:4px; max-width:40px; max-height:4px; border:1px solid black; border-radius:2px; background:rgb(230,102,255)";// 紫色

    // 子窗口
    Fundamental_Window* Fwindow;
    Advanced_Window* Awindow;

private:
    QTimer* refreshTimer;           // 刷新计时器
    QTimer* sendTimer;              // 发送计时器
    int sendFrameCount = 1;                  // 发送计数器
    FrameToSendFormat frameToSendFormat;  // 发送数据帧

signals:
    void openSerial(QString portname);              // 打开串口 信号
    void closeSerial(QString portname);             // 关闭串口 信号
    void sendFrameData(QByteArray frameToSend);       // 向子线程发送串口数据 信号

public slots:
    void recvfloats(QList<FloatDatas> recvDatasList);   // 收到子线程解析的数据 槽函数

    void sendFrame();          // 发送帧数据
    void plotUpdate();         // 主线程曲线添加显示数据 槽函数

private slots:
    void on_pushButton_scanPort_clicked();
    void on_pushButton_openPort_clicked();
    void on_pushButton_saveData_clicked();
    void on_comboBox_chart1_1_currentIndexChanged(int index);
    void on_comboBox_chart1_2_currentIndexChanged(int index);
    void on_comboBox_chart2_1_currentIndexChanged(int index);
    void on_comboBox_chart2_2_currentIndexChanged(int index);
    void on_pushButton_fundamental_clicked();
    void on_pushButton_advanced_clicked();
    void on_checkBox_EnableSend_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
    QThread* subThread;
    Com* readwriteCom;
};
#endif // MAINWINDOW_H
