#include <qdebug.h>

#include "CaptureObserver.h"
#include "third_party/libyuv/include/libyuv/convert_argb.h"

void CaptureObserver::OnFrame(const webrtc::VideoFrame& videoFrame)
{
    /*for (int i = 0; i < 10; ++i)
    {
        mySignal(i);
    }*/

    QMutexLocker lock(&m_mutex_lock);
    int height = videoFrame.height();
    int width = videoFrame.width();

    static int incoming_frames_ = 0;
    incoming_frames_++;
    qDebug() << "width" << width << "height" << height << "incoming_frames_" << incoming_frames_;

    //Convert received data frame to //Chuyển đổi khung dữ liệu nhận được sang định dạng
    rtc::scoped_refptr<webrtc::I420BufferInterface> buffer(
        videoFrame.video_frame_buffer()->ToI420());

    //Open up a space to store BGR data//Mở một không gian để lưu trữ dữ liệu BGR
    const int length = buffer->width() * buffer->height() * 4;
    qDebug() << "width::" << buffer->width() << ", height::" << buffer->height();
    uchar* imageBuffer = new uchar[length];

    //Use libyuvy library to convert one frame of data to BGR//Sử dụng thư viện libyuvy để chuyển đổi một khung dữ liệu sang BGR
    libyuv::I420ToARGB(buffer->DataY(), buffer->StrideY(), buffer->DataU(),
        buffer->StrideU(), buffer->DataV(), buffer->StrideV(),
        imageBuffer,
        buffer->width() * 3,
        buffer->width(), buffer->height());

    QImage image(imageBuffer, buffer->width(), buffer->height(), QImage::Format_RGBA8888);
    qDebug() << image;//image.save("local.png");return;
    //m_lastImage = image.copy();
    emit signal_LastImage(image.copy());

    
    delete imageBuffer;
}


