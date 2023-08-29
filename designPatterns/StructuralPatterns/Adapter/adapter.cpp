#include <iostream>
#include <string>

// 旧的串口设备类
class SerialDevice {
public:
    void connectToCOMPort(int portNumber) {
        // 连接到串口设备的逻辑
    }

    void sendData(std::string data) {
        // 发送数据到串口的逻辑
    }
};

// 新的USB接口标准
class USBInterface {
public:
    virtual void connectToUSBPort() = 0;
    virtual void sendDataOverUSB(std::string data) = 0;
};

// USB到串口适配器类
class USBToSerialAdapter : public USBInterface {
private:
    SerialDevice* serialDevice;

public:
    USBToSerialAdapter(SerialDevice* device) {
        this->serialDevice = device;
    }

    void connectToUSBPort() override {
        // 适配USB连接到串口设备的逻辑
        serialDevice->connectToCOMPort(1); // 假设连接到COM1口
    }

    void sendDataOverUSB(std::string data) override {
        // 适配数据发送到串口的逻辑
        serialDevice->sendData(data);
    }
};

int main() {
    SerialDevice* oldDevice = new SerialDevice();
    USBInterface* adapter = new USBToSerialAdapter(oldDevice);

    adapter->connectToUSBPort();
    adapter->sendDataOverUSB("Hello, world!");

    delete adapter;
    delete oldDevice;

    return 0;
}
