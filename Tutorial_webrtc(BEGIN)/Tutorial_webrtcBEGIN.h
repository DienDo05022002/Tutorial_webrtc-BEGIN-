#pragma once

#include <QtWidgets/QMainWindow>
#include <qtimer.h>
#include <qdebug.h>
#include <map>
#include <memory>
#include <string>

//#include "rtc_base/third_party/sigslot/sigslot.h"
#include "ui_Tutorial_webrtcBEGIN.h"
#include "CaptureObserver.h"


class Tutorial_webrtcBEGIN : public QMainWindow
{
    Q_OBJECT

public:
    Tutorial_webrtcBEGIN(QWidget *parent = nullptr);
    ~Tutorial_webrtcBEGIN();

public slots:
    void on_pushButton_clicked();

    void slot_LastImage(const QImage m_lastImage)
    {
        qDebug() << "Received value: " << m_lastImage;
        QPixmap pixmap = QPixmap::fromImage(m_lastImage);  // Tạo một QPixmap từ QImage
        //label->setPixmap(pixmap);
        ui.label->setPixmap(pixmap);
    }

private:
    //Lay ds thiet bi
    void getDeviceList();

    rtc::scoped_refptr<webrtc::VideoCaptureModule> m_module;
    webrtc::VideoCaptureCapability m_capability;
    CaptureObserver m_captureObserver;
    Ui::Tutorial_webrtcBEGINClass ui;
    QTimer m_timer;

    QImage pic;
};


