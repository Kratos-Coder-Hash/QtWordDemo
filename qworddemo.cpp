#include "qworddemo.h"
#include "ui_qworddemo.h"
#include "Word/qword.h"
#include <QDateTime>
#include<QDir>
QWordDemo::QWordDemo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QWordDemo)
{
    ui->setupUi(this);
}

QWordDemo::~QWordDemo()
{
    delete ui;
}

QString QWordDemo::getDetectType(int detectType)
{
	QString strDetectType;
	switch(detectType)
	{
	case ALARM_CURRENT_HEAT:
		{
			strDetectType = tr("Current Heat");
		}
		break;

	case ALARM_VOLTAGE_HEAT:
		{
			strDetectType = tr("Voltage Heat");
		}
		break;
	default:
		break;
	}

	return strDetectType;
}
QString QWordDemo::getAlarmLevel(int level)
{
	QString strLevel;
	switch(level)
	{
	case NORMAL_ALARM:
		{
			strLevel = tr("Normal");
		}
		break;

	case GENERAL_ALARM:
		{
			strLevel = tr("Deferred Alarm "); //一般告警
		}
		break;

	case CRITICAL_ALARM:
		{
			strLevel = tr("Critical Alarm ");//严重告警
		}
		break;

	case URGENT_ALARM:
		{
			strLevel = tr("Urgent Alarm");//紧急告警
		}
		break;

	default:
		break;
	}

	return strLevel;
}

void QWordDemo::on_exportPushBtn_clicked()
{
	repItem.domid				= "";
	repItem.devcode				= "";
	repItem.devname				= "device1";
	repItem._detectType			= 2;
	repItem._typeDesc           = "Pressured oil driverpipe";
	repItem.electricVal         = 1.2;
	repItem.result              = "comp_A_B_C_phase Over the upper limit,possible cause:no oil;";
	repItem._installspot        = "hang zhou";
	repItem.alarm_level         = 3;
	repItem.alarmTime           = "2017-09-04 04:40:39";
	repItem._maintainer         = "HK";
	repItem._model              = "HK005";
	repItem._productSeq         = "1234569";
	repItem._productTime        = "2015-09-04 04:40:39";
	repItem.envtemp             = 12;
	repItem.envhumidity         = 25;
	repItem.envwindspeed        = 13;
    
	QString strDevName = QString::fromStdString(repItem.devname);
	QString strResult=QString::fromStdString(repItem.result);
	QString strOrgName = QString::fromStdString(repItem._installspot);
	QString strAlarmLevel =QString("%1").arg(repItem.alarm_level);
	QString strAlarmTime = QString::fromStdString(repItem.alarmTime);

	QString strDevCode = QString::fromStdString(repItem.devcode);
	QString strDetectType =getDetectType(repItem._detectType);
	QString strDevType = QString::fromStdString(repItem._typeDesc);
	QString strInstallPlace = QString::fromStdString(repItem._installspot);
	QString  strManufacture = QString::fromStdString(repItem._maintainer);
	QString strDevModel=QString::fromStdString(repItem._model); 
	QString strRateCurrent =QString("%1").arg(repItem.electricVal);
	QString strDevProSeq =QString::fromStdString(repItem._productSeq);
	QString strDevProTime =QString::fromStdString(repItem._productTime); 


	QString current_Date_Time = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
	QString fileName = tr("Infrared diagnosis report")+"_"+ strDevName + "_" + current_Date_Time;
	fileName.replace("-", "");
	fileName.replace(":", "");
	fileName.replace(" ", "");
	QString filePath = "";
	QDate Cur_Date= QDate::currentDate();
	QString strCurDate = Cur_Date.toString("yyyy-MM-dd");
	filePath = "E:/demo/QWordDemo/ReportWord/"+strCurDate+"/";
	
	QDir dirReportPath(filePath);
	if (!dirReportPath.exists())
	{
		if (dirReportPath.mkpath(filePath))
		{
			filePath += fileName + tr(".doc");
		}	
	}
	else
	{
		filePath += fileName + tr(".doc");
	}
	QWord word;
	if( !word.createNewWord(filePath) )
	{
		QString error = tr("Failed to export report,") + word.getStrErrorInfo();
		return;
	}


	word.setPageOrientation(0);			//页面方向
	word.setWordPageView(3);			//页面视图
	word.setFontName(QString::fromLocal8Bit("宋体"));
	word.setParagraphAlignment(0);		//下面文字位置
	word.setFontSize(20);				//字体大小
	word.setFontBold(true);				//字体加粗
	word.insertText(tr("Electrical Equipment Infrared Diagnosis Report "));
	word.setFontBold(false);			
	word.insertMoveDown();
	word.setFontSize(10);	
	word.setParagraphAlignment(1);
	QString current_Time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
	word.insertText(tr("Report Generation Date:"));
	word.insertText(current_Time);
	word.insertMoveDown();
	//first table
	word.intsertTable(4,6);
	word.setCellFontBold(1,1,1,true);
	word.setCellFontBold(1,1,3,true);
	word.setCellFontBold(1,1,5,true);
	word.setCellFontBold(1,2,1,true);
	word.setCellFontBold(1,2,3,true);
	word.setCellFontBold(1,2,5,true);
	word.setCellFontBold(1,3,1,true);
	word.setCellFontBold(1,3,3,true);
	word.setCellFontBold(1,3,5,true);
	word.setCellFontBold(1,4,1,true);
	word.setCellFontBold(1,4,3,true);
	word.setCellFontBold(1,4,5,true);
	word.setTableAutoFitBehavior(0);
	word.setFontSize(10);
	word.setColumnWidth(1,1,120);
	word.setColumnWidth(1,2,120);
	word.setColumnWidth(1,3,120);
	word.setColumnWidth(1,4,120);
	word.setColumnWidth(1,5,120);

	word.setRowAlignment(1,1,0);	
	word.setCellString(1,1,1,tr("Device Name"));
	word.setCellString(1,1,2,strDevName);
	word.setCellString(1,1,3,tr("Analysis Type"));
	word.setCellString(1,1,4,strDetectType);
	word.setCellString(1,1,5,tr("Device Type"));
	word.setCellString(1,1,6,strDevType);

	word.setRowAlignment(1,2,0);
	word.setCellString(1, 2,1,tr("Install place"));
	word.setCellString(1,2,2,strInstallPlace);
	word.setCellString(1,2,3,tr("Manufacture"));
	word.setCellString(1,2,4,strManufacture);
	word.setCellString(1,2,5,tr("Device Model"));
	word.setCellString(1,2,6,strDevModel);

	word.setRowAlignment(1,3,0);
	word.setCellString(1,3,1,tr("Rated Current"));
	word.setCellString(1,3,2,strRateCurrent);
	word.setCellString(1,3,3,tr("Produce sequence Number "));
	word.setCellString(1,3,4,strDevProSeq);
	word.setCellString(1,3,5,tr("Factory Time"));
	word.setCellString(1,3,6,strDevProTime);

	word.setRowAlignment(1,4,0);
	word.setCellString(1,4,1,tr("Temperature"));
	if(repItem.envtemp==255)
	{
		word.setCellString(1,4,2,tr("Unknown Value "));
	}
	else
	{
		word.setCellString(1,4,2,QString("%1").arg(repItem.envtemp)+ QString::fromLocal8Bit("℃  "));
	}

	word.setCellString(1,4,3,tr("Humidity"));
	if(repItem.envhumidity==-1)
	{
		word.setCellString(1,4,4,tr("Unknown Value "));
	}
	else
	{
		word.setCellString(1,4,4,QString("%1").arg(repItem.envhumidity)+ QString::fromLocal8Bit("%  "));
	}

	word.setCellString(1,4,5,tr("Wind speed"));
	if(repItem.envwindspeed==-1)
	{
		word.setCellString(1,4,6,tr(" Unknown Value "));
	}
	else
	{
		word.setCellString(1,4,6,QString("%1").arg(repItem.envwindspeed)+ tr("Class  "));
	}
	word.moveForEnd();
	word.insertMoveDown();


	//second table
	word.intsertTable(2,2);
	word.setCellString(2,1,1,tr("Infrared alarm heat map"));
	word.setCellString(2,1,2,tr("Visible light picture"));
	word.setCellString(2,2,1,tr(""));
	word.setCellString(2,2,2,tr(""));
	word.setTableAutoFitBehavior(0);
	word.moveForEnd();
	word.insertMoveDown();

	//third table
	word.intsertTable(1,5);
	word.setRowAlignment(3,1,0);
	word.setColumnWidth(1,100);
	word.setColumnWidth(2,60);
	word.setColumnWidth(3,60);
	word.setColumnWidth(4,60);
	word.setColumnWidth(5,135);
	word.setCellString(3,1,1,tr("Picture"));
	word.setCellString(3,1,2,tr("Record") );
	word.setCellString(3,1,3,tr("Map") );
	word.setCellString(3,1,4,tr("DownLoad") );
	word.setCellString(3,1,5,tr("Count") );
	word.moveForEnd();
	word.insertMoveDown();
	
	word.setParagraphAlignment(1);
	word.setFontBold(true);
	word.insertText(tr("Diagnosis Analysis:"));

	word.intsertTable(1,1);
	word.setParagraphAlignment(1);
	word.setCellFontBold(4,1,1,false);
	word.setTableAutoFitBehavior(0);

	QString strRet=tr("Refer to the equipment reason for the diagnosis and treatment of the equipment,according to the standard of infrared diagnosis of electrical equipment .")+QString::fromLocal8Bit("\r\n");

	strRet += tr("According to the actual measured temperature,reduced temperature and temperature difference racquetball,General analysis,and diagnosis conclusion as follows:")+QString::fromLocal8Bit("\r\n");
	int AlmLevel = NORMAL_ALARM;
	QString tempAlaLevel =getAlarmLevel(AlmLevel);
	strRet +=  tr("Fault Level:");
	strRet +=  tempAlaLevel;
	strRet += QString::fromLocal8Bit("\r\n");
	strRet += strResult;
	strRet += QString::fromLocal8Bit("\r\n");
	strRet += QString::fromLocal8Bit("\r\n");
	word.insertText(strRet);
	word.moveForEnd();


	word.setParagraphAlignment(1);
	word.setFontBold(true);
	word.insertText(tr("Conclusion and suggestions:"));
	word.intsertTable(1,1);
	word.setParagraphAlignment(1);
	QString strAdvice;
	switch(AlmLevel)
	{
	case NORMAL_ALARM:
		{
			strAdvice = tr("Normal");
		}
		break;

	case GENERAL_ALARM:
		{

			strAdvice = tr("Current device alarm,and the system will automatically track inspect,proposing arrangment for the analysis and detection of professional personnel.");
		}
		break;

	case CRITICAL_ALARM:
		{

			strAdvice =tr("Current device alarm,it's suggested that the diagnosis and analysis of the actual diagnosis and analysis,in order to further identify the fault and arrange the professional personnelto solve it.");
		}
		break;

	case URGENT_ALARM:
		{

			strAdvice =tr("Current device alarm,it's suggested that the diagnosis and analysis of the actual diagnosis and analysis.if necessary,as soon as possible to carry out power outage.");
		}
		break;
	default:
		break;
	}
	word.setCellFontBold(1,1,false);
	word.insertText(strAdvice);
	word.insertMoveDown();
	word.moveForEnd();

	word.setParagraphAlignment(1);
	word.insertText(tr("Comments: "));//备注
	word.intsertTable(1,1);
	word.setParagraphAlignment(1);
	word.insertMoveDown();
	word.insertMoveDown();
	word.insertMoveDown();
	word.insertMoveDown();
	word.moveForEnd();

	word.setVisible(true);
	word.saveAs();
}
