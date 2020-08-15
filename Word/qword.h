#ifndef QWORD_H
#define QWORD_H

#define _WIN32_DCOM

#include <QMainWindow>
#include"qmainwindow.h"
#include <QString>
#include <QVariant>
#include <ActiveQt/QAxObject>
#include <ActiveQt/QAxWidget>
#include "objbase.h"
//#include "GlobalAppData.h"

class QWord : public QObject
{
	Q_OBJECT

public:
	QWord(QObject *parent = 0);
	~QWord();

public:
	QAxObject* getDocuments(){return m_documents;}
	QAxObject* getDocument(){return m_document;}
	QAxObject* getWordApp(){return m_word;}	
public:
	/**************************************************************************/
	/* �ļ�   ����                                                            */
	/**************************************************************************/
	void save();				//�����������	
	void close();				//�ر� �˳� ����ʱ��Ҳ���Զ�����һ��
	void saveAs();				//�½�word���Ϊ
	bool createWord(QString reportname );		//����һ���µ�word�ĵ�
	void openWord();			//��һ�����е�word�ĵ�
	bool createNewWord(const QString& filePath );		//����һ���µ�word�ĵ�

	void setTableAutoFitBehavior(int flag);//����Զ�������: 0 �̶�  1�������ݵ���  2 ���ݴ��ڵ���
	void setPageOrientation(int flag);	//����ҳ��0Ϊ����wdOrientPortrait  1Ϊ����wdOrientLandscape 
	void setWordPageView(int flag);	//����ҳ����ͼ����web��ͼwdWebView 6����ҳ����ͼwdPrintView 3 �����Ķ���ͼwdReadingView 7
	void setFontSize(int fontsize);						//���������С
	void setFontName(QString& fontName);				//��������	���� �����塱
	void setFontBold(bool flag);						//����Ӵ�
	void setParagraphAlignment(int flag);				//����ѡ��λ�����־��� 0 ������ 1 ,���� 2
	void setRowAlignment(int tableIndex,int row,int flag);
	//ͬʱ�����п���и߿��Թ̶�ͼƬ�Ĵ�С
	void setColumnWidth(int column, int width);			//�����п�
	void setColumnHeight(int column, int height);		//�����и�
	void setRowHeight(int nTable,int Row, int height);
	void setCellString(int row, int column, const QString& text);
	void setCellFontBold(int row, int column, bool isBold);			//�������ݴ���  isBold�����Ƿ����
	void setCellFontSize(int row, int column, int size);			//�������ִ�С
	void setOptionCheckSpell(bool flags);		//�������ĵ�ƴд���  true�������  false ȡ����� 

	QString GetText();												//��ȡ����
	void getUsedRange(int *topLeftRow, int *topLeftColumn, int *bottomRightRow, int *bottomRightColumn);
	void setSelectionRange(int start,int end);	//"SetRange(1, 9)"��1���ַ���ʼ������9���ַ�������Χ
	QVariant getCellValue(int row, int column);						//��ȡ��Ԫ������ 
	int getTableCount();											//��ȡword�б������	


	QString getStrErrorInfo(){return m_strError;}					//��ȡ�����г��ֵĴ�����Ϣ������QMessageBox::information��ӡ ��cpp����QMessageBox �����������߳��е���������  
	void deleteSelectColumn(int column);							//ɾ��ָ������
	void moveForEnd();												//�ƶ�ѡ�������ĵ�ĩβ
	void insertCellPic(int row,int column,const QString& picPath);	//��Ԫ�����ͼƬ
	void intsertTable(int row,int column);							//����һ�����м��б��
	void insertMoveDown();											//����س�
	void insertText(const QString& text);							//��������
	void insertTable(int tableIndex,int row,int column);
	//����Ѳ�쵥λ  Ѳ��ƻ� Ѳ��ʱ�� Ѳ �� ��  ˳�򴫲�
	//void insertTitle(const QString& str1,const QString& str2,const QString& str3,const QString& str4);
	void MergeCells(int tableIndex, int nStartRow,int nStartCol,int nEndRow,int nEndCol);//�ϲ���Ԫ��	
	bool open(const QString& strFilePath,bool bVisable);
	bool openword(bool bVisable);
	bool isOpen();


	void setColumnWidth(int nTable,int column,int width);
	void setCellString(int nTable,int row,int column,const QString& text);
	void insertCellPic(int nTable,int row,int column,const QString& picPath);
	void setCellFontBold(int nTable,int row,int column,bool isBold);
	void setCellFontSize(int nTable,int row,int column,int size);
	//void addTableRow(int nTable ,int nRow,int rowCount);
	void addTableRow(int tableIndex ,int nRow,int rowCount);
	void setColumnHeight(int nTable,int column, int height);
	void intsertTable(int tableIndex, int row,int column);

public:
	void setVisible(bool isVisible);

private:
	QAxObject* m_word;
	QAxObject* m_documents;	
	QAxObject* m_document;	
	QString  m_fileName;
	QString  m_saveName;
	QString  m_strError;
	QString  m_strFilePath;
	bool m_bOpened;

};

#endif // QWORD_H