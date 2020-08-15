#ifndef QWORDDEMO_H
#define QWORDDEMO_H

#include <QMainWindow>
typedef struct
{
	//����Ԫ��
	std::string domid;
	std::string devcode;
	std::string devname;
	int _detectType;          //�������
	std::string _typeDesc;         //�豸�������
	std::string _installspot;           //��װ�ص�
	std::string _maintainer;       //��������
	std::string _model;            //�豸�ͺ�
	double electricVal;          //�����
	std::string _productSeq;       //�������к�
	std::string _productTime;      //��������
	std::string result;
	int alarm_level;
	std::string alarmTime;
	int envwindspeed;         //��������
	int envtemp;              //�����¶�
	int envhumidity;          //����ʪ��
	

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
