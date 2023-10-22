#include "Tutorial_webrtcBEGIN.h"
#include "modules/video_capture/video_capture_factory.h"

#include <qpixmap.h>
Tutorial_webrtcBEGIN::Tutorial_webrtcBEGIN(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    getDeviceList();

    //QPixmap pic("D:/STORAGE/img_webRTC/translated_image_vi.png");
    //ui.label->setPixmap(pic);
}

Tutorial_webrtcBEGIN::~Tutorial_webrtcBEGIN()
{}


void Tutorial_webrtcBEGIN::on_pushButton_clicked()
{
    QObject::connect(&m_captureObserver, &CaptureObserver::signal_LastImage, this, &Tutorial_webrtcBEGIN::slot_LastImage);


    static bool flag = true;
    if (flag) {
        webrtc::VideoCaptureModule::DeviceInfo* device_info = webrtc::VideoCaptureFactory::CreateDeviceInfo();

        char device_name[256];
        char unique_name[256];

        if (device_info->GetDeviceName(ui.comboBox->currentIndex(), device_name, 256, unique_name, 256) != 0) {
            qDebug() << "device_info->GetDeviceName ERROR";
            return;
        }
        m_module = webrtc::VideoCaptureFactory::Create(unique_name);
        if (m_module.get() == NULL) {
            qDebug() << "webrtc::VideoCaptureFactory::Create ERROR";
            return;
        }
        m_module->RegisterCaptureDataCallback(&m_captureObserver);
        device_info->GetCapability(m_module->CurrentDeviceName(), 0, m_capability);

        //Start capturing
        if (m_module->StartCapture(m_capability) != 0) {
            qDebug() << "m_module->StartCapture FAILED";
            return;
        }
        if (m_module->CaptureStarted()) {
            qDebug() << "Capture is running";
        }


        //m_captureObserver.getLastImage();
        //pic = m_captureObserver.getLastImage();
        //qDebug() << "accessLastImage:: " << pic;

        m_timer.start(40);
        ui.pushButton->setText(tr("close"));
    }
    else {
        ui.pushButton->setText(tr("open"));
        m_timer.stop();

        m_module->StopCapture();
        if (!m_module->CaptureStarted()) {
            qDebug() << "Capture is stoped";
        }
        ui.label->clear();
    }
    flag = !flag;
}

void Tutorial_webrtcBEGIN::getDeviceList()
{
    webrtc::VideoCaptureModule::DeviceInfo *info = webrtc::VideoCaptureFactory::CreateDeviceInfo();
    int deviceNum = info->NumberOfDevices();

    for (int i = 0; i < deviceNum; ++i) {
        const uint32_t kSize = 256;
        char name[kSize] = { 0 };
        char id[kSize] = { 0 };
        if (info->GetDeviceName(i, name, kSize, id, kSize) != -1) {
            ui.comboBox->addItem(QString(name));
        }
    }
    if (deviceNum == 0) {
        ui.pushButton->setEnabled(false);
    }
}




