#ifndef QWORDDEMO_H
#define QWORDDEMO_H

#include <QMainWindow>
typedef struct
{
	//公共元素
	std::string domid;
	std::string devcode;
	std::string devname;
	int _detectType;          //分析类别
	std::string _typeDesc;         //设备类别描述
	std::string _installspot;           //安装地点
	std::string _maintainer;       //生产厂家
	std::string _model;            //设备型号
	double electricVal;          //额定电流
	std::string _productSeq;       //生产序列号
	std::string _productTime;      //出厂日期
	std::string result;
	int alarm_level;
	std::string alarmTime;
	int envwindspeed;         //环境风速
	int envtemp;              //环境温度
	int envhumidity;          //环境湿度
	

}ReportableInfo;

typedef enum 
{
	ALARM_CURRENT_HEAT,
	ALARM_VOLTAGE_HEAT,
}ALARM_HEAT_TYPE;

typedef enum 
{
	NORMAL_ALARM,
	GENERAL_ALARM,
	CRITICAL_ALARM,
	URGENT_ALARM,
	_ALARM_NUM,
}ALARM_LEVEL;

namespace Ui {
class QWordDemo;
}

class QWordDemo : public QMainWindow
{
    Q_OBJECT

public:
    explicit QWordDemo(QWidget *parent = 0);
    ~QWordDemo();
	QString getDetectType(int detectType);
	QString getAlarmLevel(int level);

private:
    Ui::QWordDemo *ui;
	ReportableInfo repItem;
private slots:
		void on_exportPushBtn_clicked();
};

#endif // QWORDDEMO_H
