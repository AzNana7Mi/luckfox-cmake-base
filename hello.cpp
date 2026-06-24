#include <cstdio>
#include <vector>

#include "cstring"
#include "thread"
#include "CSerialPort/SerialPort.h"
#include "CSerialPort/SerialPortInfo.h"
//#define I_OS_LINUX

using itas109::CSerialPort;
using itas109::CSerialPortInfo;
using itas109::SerialPortInfo;
using itas109::BaudRate;
using itas109::Parity;
using itas109::DataBits;
using itas109::StopBits;
using itas109::FlowControl;
using std::this_thread::sleep_for;
using std::vector;
using std::chrono::milliseconds;

class MainProgram{
	private:
		CSerialPort serial_port;

	public:
	void Main_Program(){
		printf("Hello World, 123123!\n");
	}

	void Scan_Serial_Ports(){
		vector<SerialPortInfo> ports = CSerialPortInfo::availablePortInfos();
		for (size_t i = 0; i<ports.size(); i++) {
			printf("%d - %s | %s | %s\n",
			   i + 1,
			   ports[i].portName,      // 串口名称, Linux: /dev/ttyS0 或 /dev/ttyUSB0
			   ports[i].description,   // 描述信息
			   ports[i].hardwareId);   // 硬件ID
		}
	}
	/*
	 * 连接开发板, 输入luckfox-config, 配置外设开关
	 * 注意：任何一个UART端口, 都会从/dev/ttyS1开始
	 */
	void Open_UART1() {
		this->serial_port.init(
			"/dev/ttyS1",
			BaudRate::BaudRate115200,
			Parity::ParityNone,
			DataBits::DataBits8,
			StopBits::StopOne,
			FlowControl::FlowNone,
			4096);
		if (serial_port.open()) {
			printf("串口打开成功！\n");
			char msg[] = "hello uart!\n";
			while (true){
				serial_port.writeData(msg, static_cast<int>(strlen(msg)));
				sleep_for(milliseconds(1000));
			}
		}
		else {
			printf("串口打开失败！\n");
		}
	}

};

int main(){
	MainProgram prog;
	prog.Scan_Serial_Ports();
	prog.Open_UART1();
	return 0;
}
