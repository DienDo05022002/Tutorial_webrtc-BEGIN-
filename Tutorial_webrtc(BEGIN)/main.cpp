#include "Tutorial_webrtcBEGIN.h"
#include <QtWidgets/QApplication>
#include <qdebug.h>

#include "modules/video_capture/video_capture_factory.h"
#include "test/vcm_capturer.h"
#include "modules/video_capture/video_capture.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//######################################################################
//        Dùng "GetDeviceName()" để in ra tên camera
//######################################################################
    int deviceNum = 1;
    std::unique_ptr<webrtc::VideoCaptureModule::DeviceInfo> info(webrtc::VideoCaptureFactory::CreateDeviceInfo());
    for (int i = 0; i < deviceNum; i++) {
        const uint32_t kSize = 256;
        char name[kSize] = { 0 };
        char id[kSize] = { 0 };
        if (info->GetDeviceName(i, name, kSize, id, kSize) != -1) {
            qDebug() << "ID::: " << QString(id);
            qDebug() << "Your camera name:::" << QString(name);
        }
    }
    //###########################   *** END *** ############################
    //######################################################################

    Tutorial_webrtcBEGIN w;
    w.show();
    return a.exec();
}

