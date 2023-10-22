#pragma once
#include "modules/video_capture/video_capture.h"
#include "test/test_video_capturer.h"

#include <qmutex.h>
#include <QTimer>
#include <QImage>
#include <qpixmap.h>
#include <qdebug.h>

class CaptureObserver : public QObject, public rtc::VideoSinkInterface<webrtc::VideoFrame>
{
    Q_OBJECT
public:
    void OnFrame(const webrtc::VideoFrame& videoFrame) override;

    //QImage getLastImage() {
    //    return m_lastImage;
    //}

signals:
    void signal_LastImage(const QImage m_lastImage);

    void mySignal(int value);
//public slots:
//    void mySlot(int value)
//    {
//        qDebug() << "Received value: " << value;
//    }


private:
    //QImage m_lastImage;
    QMutex m_mutex_lock;
};
