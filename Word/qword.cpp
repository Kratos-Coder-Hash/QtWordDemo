#include "qword.h"
#include <QDateTime>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <ActiveQt/QAxObject>
#include <ActiveQt/QAxWidget>
#include<QTextStream>
#include <ActiveQt/QAxBase>
#include <QTextFormat>

QWord::QWord(QObject *parent)
{		
	CoInitializeEx(NULL,COINIT_MULTITHREADED);//��������߳��޷�����word����
	m_word = new QAxObject(parent); 			
	m_documents = NULL;
	m_document = NULL;	
	m_bOpened=false;
	
}

QWord::~QWord()
{
	close();
}

bool QWord::createWord(QString reportname)		//����һ���µ�word
{
    QString ReportName= reportname;
	QString defaultFileName = QString("%1").arg(ReportName);
	m_saveName=QFileDialog::getSaveFileName(0,tr("Report Information"),defaultFileName,tr("*.doc"));
	//CGlobalAppData *pAppData = CAppDataSingleton::instance();
	QString SavePath = /*pAppData->m_strAppDirPath + */"/ReportWord"+m_saveName;
	QFile file(m_saveName);
	if(file.exists())
	{
		m_strError = tr("abnormal:the file already exists!");
		//m_strError = QString::fromLocal8Bit("����Ŀ���ļ��Ѵ���!");			
		return false;
	}
	if(!m_saveName.isEmpty())
	{		
		if(!m_word->setControl("Word.Application"))
		{
			m_strError = tr("abnormal:failed to get the word component,please make sure the word is installed!");
			//m_strError = QString::fromLocal8Bit("���󣺻�ȡword���ʧ�ܣ���ȷ���Ƿ�װ��word!");	
			return false;
		}
		m_word->setProperty("Visible",false);
		m_word->setProperty("DisplayAlerts", false);//����ʾ�κξ�����Ϣ�����Ϊtrue��ô�ڹر��ǻ�������ơ��ļ����޸ģ��Ƿ񱣴桱����ʾ
		m_documents = m_word->querySubObject("Documents");
		m_documents->dynamicCall("Add (void)");
		m_document = m_word->querySubObject("ActiveDocument");//��ȡ��ǰ������ĵ� 	
		return true;
	}else
	{
		m_strError = tr("abnormal:the file name is empty!");
		//m_strError = QString::fromLocal8Bit("�����ļ���Ϊ��");		
		return false;
	}
}
bool QWord::createNewWord(const QString& filePath )
{	
	m_saveName = filePath;
	QFile file(m_saveName);
	if(file.exists())
	{
		file.remove(m_saveName);
		//m_strError = tr("error:the file already exists!");
		//m_strError = QString::fromLocal8Bit("����Ŀ���ļ��Ѵ���!");			
		//return false;
	}
	if(!m_saveName.isEmpty())
	{		
		if(!m_word->setControl("Word.Application"))
		{
			m_strError = tr("abnormal:failed to get the word component,please make sure the word is installed!");
			//m_strError = QString::fromLocal8Bit("���󣺻�ȡword���ʧ�ܣ���ȷ���Ƿ�װ��word!\n");
			return false;
		}
		m_word->setProperty("Visible",false);
		m_word->setProperty("DisplayAlerts", false);//����ʾ�κξ�����Ϣ�����Ϊtrue��ô�ڹر��ǻ�������ơ��ļ����޸ģ��Ƿ񱣴桱����ʾ
		m_documents = m_word->querySubObject("Documents");
		if(!m_documents)
		{
			m_strError = tr("abnormal:failed to get the documents!");
			//m_strError = QString::fromLocal8Bit("��ȡ�ĵ�ʧ�ܣ�\n");
			return false;
		}
		m_documents->dynamicCall("Add (void)");
		m_document = m_word->querySubObject("ActiveDocument");//��ȡ��ǰ������ĵ� 	
		return true;
	}else
	{
		m_strError = tr("abnormal:the file name is empty!");
		//m_strError = QString::fromLocal8Bit("�����ļ���Ϊ��");		
		return false;
	}
}
bool QWord::openword(bool bVisable)
{
	m_word = new QAxObject();
	bool bFlag = m_word->setControl("word.Application");
	if(!bFlag)
	{
		bFlag = m_word->setControl("kwps.Application");
	}
	if(!bFlag)
	{
		return false;
	}
	m_word->setProperty("Visible",bVisable);
	QAxObject* documents =m_word->querySubObject("Documents");
	if(!documents)
	{
		return false;
	}
	documents->dynamicCall("Add(QString)",m_strFilePath);
	m_bOpened = true;
	return m_bOpened;
}

bool QWord::open(const QString& strFilePath,bool bVisable)
{
	m_strFilePath = strFilePath;
	//close();
	return openword(bVisable);
}
bool QWord::isOpen()
{
	return m_bOpened;
}
void QWord::save()	
{
	if(m_document)
		m_document->dynamicCall("Save()");
	else
		return;
}
void QWord::close()				//�ر� �˳� ����ʱ��Ҳ���Զ�����һ��
{
	if(!m_saveName.isEmpty())		//�����Ϊ��  ��Ϊ�½�   
	{
		saveAs();
		m_saveName = "";
	}
	//if(m_document)
	//	m_document->dynamicCall("Close (boolean)",false);
	//if(m_word)	
	//	m_word->dynamicCall("Quit (void)");	
	if(m_documents)
		delete m_documents;	
	if(m_word)
		delete m_word;	
	m_document = NULL;
	m_documents = NULL;
	m_word = NULL;
}
void QWord::saveAs()				
{
	if(m_document)
		m_document->dynamicCall("SaveAs(const QString&)",QDir::toNativeSeparators(m_saveName));	
	else
		return;
}

void QWord::setPageOrientation(int flag)	//����ҳ��1 ����   ���� 0����
{	
	QAxObject* selection = m_word->querySubObject("Selection");	
	if(nullptr== selection)
	{
		return;
	}
	QString page;
	switch (flag)
	{
	case 0:
		page = "wdOrientPortrait";
		break;
	case 1:
		page = "wdOrientLandscape";
		break;
	}
	selection->querySubObject("PageSetUp")->setProperty("Orientation",page);
}
void QWord::setWordPageView(int flag)		
{
	QAxObject* viewPage = m_word->querySubObject("ActiveWindow");
	if(nullptr== viewPage)
	{
		return;
	}
	QString view;
	switch (flag)
	{
	case 1:
		view = "wdNormalView";
		break;
	case 2:
		view = "wdOutlineView";
		break;
	case 3:
		view = "wdPrintView";
		break;
	case 4:
		view = "wdPrintPreview";
		break;
	case 5:
		view = "wdMasterView";
		break;
	case 6:
		view = "wdWebView";
		break;
	case 7:
		view = "wdReadingView";
		break;
	case 8:
		view = "wdConflictView";
		break;
	}	
	viewPage->querySubObject("View")->setProperty("Type",view);
}
void QWord::insertMoveDown()				//����س�
{
	QAxObject* selection  = m_word->querySubObject("Selection");
	if(nullptr== selection)
	{
		return;
	}
	selection->dynamicCall("TypeParagraph(void)");	
}
void QWord::insertText(const QString& text)
{
	QAxObject* selection  = m_word->querySubObject("Selection");
	if(nullptr== selection)
	{
		return;
	}
	selection->dynamicCall("TypeText(const QString&)",text);		
}

QString QWord::GetText()
{
	QAxObject* selection = m_word->querySubObject("Selection");	
	QString str;
	if(nullptr!= selection)
	{
	  str = selection->dynamicCall("GetText(void)").toString();
	}
		
	return str;
}
 //����ѡ��λ�����־��� 0 ,���� 1,���� 2
void QWord::setParagraphAlignment(int flag)
{
	QAxObject* selection = m_word->querySubObject("Selection");	
	if(nullptr== selection)
	{
		return;
	}
	if(flag == 0)
	{
		selection->querySubObject("ParagraphFormat")->setProperty("Alignment","wdAlignParagraphCenter");
	}else if(flag == 1)
	{
		selection->querySubObject("ParagraphFormat")->setProperty("Alignment","wdAlignParagraphJustify");
	}else if(flag == 2)
	{
		selection->querySubObject("ParagraphFormat")->setProperty("Alignment","wdAlignParagraphRight");
	}
}

void QWord::setRowAlignment(int tableIndex,int row,int flag)
{   
	QAxObject* tables = m_document->querySubObject("Tables");	
	if(nullptr== tables)
	{
		return;
	}
	QAxObject* table = tables->querySubObject("Item(int)",tableIndex);
	if(nullptr== table )
	{
		return;
	}
	QAxObject* Row= table->querySubObject("Rows(int)",row);
	if(nullptr== Row)
	{
		return;
	}
	QAxObject* range = Row->querySubObject("Range");
	if(nullptr== range)
	{
		return;
	}
	Row->querySubObject("Alignment(int)",flag);
	if(flag == 0)
	{
		range->querySubObject("ParagraphFormat")->setProperty("Alignment","wdAlignParagraphCenter");
	}else if(flag == 1)
	{
		range->querySubObject("ParagraphFormat")->setProperty("Alignment","wdAlignParagraphJustify");
	}else if(flag == 2)
	{
		range->querySubObject("ParagraphFormat")->setProperty("Alignment","wdAlignParagraphRight");
	}else if(flag ==3)
	{
		range->querySubObject("ParagraphFormat")->setProperty("Alignment","wdAlignParagraphLeft");
	}
}
void QWord::setFontSize(int fontsize)		//���������С
{
	QAxObject* selection = m_word->querySubObject("Selection");	
	if(nullptr== selection)
	{
		return;
	}
	selection->querySubObject("Font")->setProperty("Size",fontsize);
}
void QWord::setFontBold(bool flag)
{
	QAxObject* selection = m_word->querySubObject("Selection");	
	if(nullptr== selection)
	{
		return;
	}
	selection->querySubObject("Font")->setProperty("Bold",flag);
}
void QWord::setFontName(QString& fontName)
{
	QAxObject* selection = m_word->querySubObject("Selection");	
	if(nullptr== selection)
	{
		return;
	}
	selection->querySubObject("Font")->setProperty("Name",fontName);
}
void QWord::setSelectionRange(int start,int end)
{
	QAxObject* selection = m_word->querySubObject("Selection");
	if(nullptr== selection)
	{
		return;
	}
	selection->dynamicCall("SetRange(int, int)", start,end);	//��1���ַ���ʼ������9���ַ�������Χ
}
void QWord::getUsedRange(int *topLeftRow, int *topLeftColumn, int *bottomRightRow, int *bottomRightColumn)
{
	QAxObject* range = m_document->querySubObject("Range");
	if(nullptr== range)
	{
		return;
	}
	*topLeftRow = range->property("Row").toInt();
	if(nullptr== topLeftRow)
	{
		return;
	}
	*topLeftColumn = range->property("Column").toInt();
	if(nullptr== topLeftColumn)
	{
		return;
	}
	QAxObject *rows = range->querySubObject("Rows");
	if(nullptr== rows)
	{
		return;
	}
	*bottomRightRow = *topLeftRow + rows->property("Count").toInt() - 1;
	if(nullptr== bottomRightRow)
	{
		return;
	}
	QAxObject *columns = range->querySubObject("Columns");
	if(nullptr== columns)
	{
		return;
	}
	*bottomRightColumn = *topLeftColumn + columns->property("Count").toInt() - 1;
	if(nullptr== bottomRightColumn)
	{
		return;
	}
}

void QWord::intsertTable(int row,int column)
{	
	QAxObject* tables = m_document->querySubObject("Tables");	
	if(nullptr== tables)
	{
		return;
	}
	QAxObject* selection = m_word->querySubObject("Selection");
	if(nullptr== selection)
	{
		return;
	}
	QAxObject* range = selection->querySubObject("Range");
	if(nullptr== range)
	{
		return;
	}
	QVariantList params;
	params.append(range->asVariant());		
	params.append(row);
	params.append(column);	
	tables->querySubObject("Add(QAxObject*, int, int, QVariant&, QVariant&)", params);
	QAxObject* table = selection->querySubObject("Tables(int)",1);
	if(nullptr== table)
	{
		return;
	}
	table->setProperty("Style","������"); 
	QAxObject* Borders = table->querySubObject("Borders");
	if(nullptr== Borders)
	{
		return;
	}
	Borders->setProperty("InsideLineStyle",1);
	Borders->setProperty("OutsideLineStyle",1);
	/*QString doc = Borders->generateDocumentation();
	QFile outFile("D:\\360Downloads\\Picutres\\Borders.html");
	outFile.open(QIODevice::WriteOnly|QIODevice::Append);
	QTextStream ts(&outFile);
	ts<<doc<<endl;*/
}
void QWord::intsertTable(int tableIndex, int row,int column)
{	
	QAxObject* tables = m_document->querySubObject("Tables");	
	if(nullptr== tables)
	{
		return;
	}
	QAxObject* selection = m_word->querySubObject("Selection");
	if(nullptr== selection)
	{
		return;
	}
	QAxObject* range = selection->querySubObject("Range");
	if(nullptr== range)
	{
		return;
	}
	QVariantList params;
	params.append(range->asVariant());		
	params.append(row);
	params.append(column);	
	tables->querySubObject("Add(QAxObject*, int, int, QVariant&, QVariant&)", params);
	QAxObject* table = selection->querySubObject("Tables(int)",tableIndex);
	if(nullptr== table)
	{
		return;
	}
	table->setProperty("Style","������"); 
	QAxObject* Borders = table->querySubObject("Borders");
	if(nullptr== Borders)
	{
		return;
	}
	Borders->setProperty("InsideLineStyle",1);
	Borders->setProperty("OutsideLineStyle",1);
	/*QString doc = Borders->generateDocumentation();
	QFile outFile("D:\\360Downloads\\Picutres\\Borders.html");
	outFile.open(QIODevice::WriteOnly|QIODevice::Append);
	QTextStream ts(&outFile);
	ts<<doc<<endl;*/
}

void QWord::setColumnWidth(int column, int width)		//�����п�
{
	QAxObject* selection = m_word->querySubObject("Selection");	
	if(nullptr== selection)
	{
		return;
	}
	QAxObject* table = selection->querySubObject("Tables(1)");
	if(nullptr== table)
	{
		return;
	}
	table->querySubObject("Columns(int)",column)->setProperty("Width",width);

}
void QWord::setCellString(int nTable,int row,int column,const QString& text)
{
 	QAxObject* pTables =m_document->querySubObject("Tables");
	if(nullptr==pTables)
	{
		return;
	}
	QAxObject* table=pTables->querySubObject("Item(int)",nTable);
	if(table)
	{
		table->querySubObject("Cell(int,int)",row,column)->querySubObject("Range")
		                    ->dynamicCall("SetText(QString)",text);
	}
}
void QWord::MergeCells(int tableIndex, int nStartRow,int nStartCol,int nEndRow,int nEndCol)//�ϲ���Ԫ��
{
	QAxObject* tables = m_document->querySubObject("Tables");
	if(nullptr==tables)
	{
		return;
	}
	QAxObject* table = tables->querySubObject("Item(int)",tableIndex);
	if(nullptr== table)
	{
		return;
	}
	if(table)
	{
		QAxObject* StartCell =table->querySubObject("Cell(int, int)",nStartRow,nStartCol);
		QAxObject* EndCell = table->querySubObject("Cell(int, int)",nEndRow,nEndCol);
		if(nullptr==StartCell)
		{
			return;
		}
		if(nullptr== EndCell)
		{
			return;
		}
		StartCell->querySubObject("Merge(QAxObject *)",EndCell->asVariant());
	}
	
}
//�ڶ��ַ�������
// void QWord::MergeCells(int tableIndex, int nStartRow,int nStartCol,int nEndRow,int nEndCol)//�ϲ���Ԫ��
// {
// 	QAxObject* tables = m_document->querySubObject("Tables");	
// 	QAxObject* table = tables->querySubObject("Item(int)",tableIndex);
// 	QAxObject* StartCell =table->querySubObject("Cell(int, int)",nStartRow,nStartCol);
// 	QAxObject* EndCell = table->querySubObject("Cell(int, int)",nEndRow,nEndCol);
// 	StartCell->dynamicCall("Merge(LPDISPATCH)",EndCell->asVariant());
// }

void QWord::setColumnHeight(int nTable,int column, int height)
{
	QAxObject* pTables =m_document->querySubObject("Tables");
	if(nullptr==pTables)
	{
		return;
	}
	QAxObject* table=pTables->querySubObject("Item(int)",nTable);
	if(table)
	{
		table->querySubObject("Columns(int)",column)->setProperty("Hight",height);
	}
}
void QWord::setRowHeight(int nTable,int Row, int height)
{
	QAxObject* pTables =m_document->querySubObject("Tables");
	if(nullptr==pTables)
	{
		return;
	}
	QAxObject* table=pTables->querySubObject("Item(int)",nTable);

	if(table)
	{
		table->querySubObject("Rows(int)",Row)->setProperty("Hight",height);
	}
}

void QWord::setColumnHeight(int column, int height)		//�����и�
{
	QAxObject* selection = m_word->querySubObject("Selection");	
	if(nullptr== selection)
	{
		return;
	}
	QAxObject* table = selection->querySubObject("Tables(1)");
	if(table)
	{
		table->querySubObject("Columns(int)",column)->setProperty("Hight",height);
	}
	
}


void QWord::setCellString(int row, int column, const QString& text)
{
	QAxObject* selection = m_word->querySubObject("Selection");	
	if(nullptr== selection)
	{
		return;
	}
	QAxObject* table = selection->querySubObject("Tables(1)");	
	if(nullptr== table)
	{
		return;
	}
	QAxObject* rows =table->querySubObject("Rows");
	if(rows)
	{
		return;
	}	
	int Count =rows->dynamicCall("Count").toInt();
	table->querySubObject("Cell(int, int)",row,column)->querySubObject("Range")->dynamicCall("SetText(QString)", text);	
}

void QWord::setCellFontBold(int row, int column, bool isBold)	//�������ݴ���  isBold�����Ƿ����
{
	QAxObject* selection = m_word->querySubObject("Selection");	
	if(nullptr== selection)
	{
		return;
	}
	QAxObject* table = selection->querySubObject("Tables(1)");
	if(nullptr== table)
	{
		return;
	}
	table->querySubObject("Cell(int, int)",row,column)->querySubObject("Range")->dynamicCall("SetBold(int)", isBold);
}
void QWord::setCellFontSize(int row, int column, int size)		//�������ִ�С
{
	QAxObject* selection = m_word->querySubObject("Selection");	
	if(nullptr== selection)
	{
		return;
	}
	QAxObject* table = selection->querySubObject("Tables(1)");
	if(nullptr== table)
	{
		return;
	}
	table->querySubObject("Cell(int, int)",row,column)->querySubObject("Range")->querySubObject("Font")->setProperty("Size", size);	
}
QVariant QWord::getCellValue(int row, int column)					//��ȡ��Ԫ������ �˴�����Excel��˵�к��д�1��ʼ����
{
	QAxObject* selection = m_word->querySubObject("Selection");	
	QAxObject* table = selection->querySubObject("Tables(1)");
	if(nullptr!=selection&&nullptr!=table)
	return table->querySubObject("Cell(int, int)",row,column)->querySubObject("Range")->property("Text");	
}
int QWord::getTableCount()
{
	QAxObject* tables = m_document->querySubObject("Tables");
	int val;
	if(nullptr!= tables)
	{
      val = tables->property("Count").toInt();
	}	
	return val;
}
void QWord::moveForEnd()
{
	QAxObject* selection = m_word->querySubObject("Selection");	
	if(nullptr== selection)
	{
		return;
	}
	QVariantList params;
	params.append(6);		
	params.append(0);		
	selection->dynamicCall("EndOf(QVariant&, QVariant&)", params).toInt();
}
void QWord::insertCellPic(int row,int column,const QString& picPath)
{
	QAxObject* selection = m_word->querySubObject("Selection");	
	if(nullptr== selection)
	{
		return;
	}
	QAxObject* table = selection->querySubObject("Tables(1)");
	if(nullptr== table)
	{
		return;
	}
	QAxObject* range = table->querySubObject("Cell(int, int)",row,column)->querySubObject("Range");
	if(nullptr== range)
	{
		return;
	}
	range->querySubObject("InlineShapes")->dynamicCall("AddPicture(const QString&)",picPath);
}
void QWord::setTableAutoFitBehavior(int flag)
{
	QAxObject* selection = m_word->querySubObject("Selection");	
	if(nullptr== selection)
	{
		return;
	}
	QAxObject* table = selection->querySubObject("Tables(1)");
	if(nullptr== table)
	{
		return;
	}
    if(0 <= flag &&flag <= 2 )
		table->dynamicCall("AutoFitBehavior(WdAutoFitBehavior)", flag);
}
void QWord::deleteSelectColumn(int column)
{
	QAxObject* selection = m_word->querySubObject("Selection");
	if(nullptr== selection)
	{
		return;
	}
	QAxObject* table = selection->querySubObject("Tables(1)");
	if(nullptr== table)
	{
		return;
	}
	QAxObject* columns = table->querySubObject("Columns(int)",column);
	if(nullptr== columns)
	{
		return;
	}
	columns->dynamicCall("Delete()");
}

void QWord::setOptionCheckSpell(bool flags)
{
	QAxObject* opetions = m_word->querySubObject("Options");	
	if(!opetions)
		return;
	opetions->setProperty("CheckGrammarAsYouType",flags);
	opetions->setProperty("CheckGrammarWithSpelling",flags);
	opetions->setProperty("ContextualSpeller",flags);
	opetions->setProperty("CheckSpellingAsYouType",flags);
}

void QWord::addTableRow(int tableIndex ,int nRow,int rowCount)
{
	QAxObject* tables=m_document->querySubObject("Tables");
	if(nullptr== tables)
	{
		return;
	}
	QAxObject* table = tables->querySubObject("Item(int)",tableIndex);
	if(nullptr== table)
	{
		return;
	}
	QAxObject* rows =table->querySubObject("Rows");
	if(nullptr== rows)
	{
		return;
	}
	int Count =rows->dynamicCall("Count").toInt();
	if(0<nRow && nRow <= Count )
	{   
		for(int i =0; i<rowCount; ++i)
		{
			QString sPos = QString("Item(%1)").arg(nRow+i);
			QAxObject* row= rows->querySubObject(sPos.toStdString().c_str());
			QAxObject* row1= rows->querySubObject("Last");
			QAxObject* row2= rows->querySubObject("Row(int)", nRow+i);
			QAxObject* row3= rows->querySubObject("Item(int)",nRow+i);
			if (nullptr != row)
			{
				QVariant param =row ->asVariant();
				/*rows->dynamicCall("Add(Variant)",param);*/
				QAxObject* NewRow = rows->querySubObject("Add(Variant)",param);
			}
			
		}			
	}	
}
////�������
void QWord::insertTable(int tableIndex,int row,int column)
{
	
	QAxObject* tables=m_document->querySubObject("Tables");
	if(nullptr==tables)
	{
		return;
	}
	QAxObject* table = tables->querySubObject("Item(int)",tableIndex);
	if(nullptr==table)
	{
		return;
	}
	//QAxObject* rows =table->querySubObject("Rows");
	QAxObject* selection = m_word->querySubObject("Selection");
	if(nullptr==selection)
	{
		return;
	}
	QAxObject* range = selection->querySubObject("Range");
	if(nullptr==range)
	{
		return;
	}
	QVariantList params;
	params.append(range->asVariant());		
	params.append(row);
	params.append(column);	
	tables->querySubObject("Add(QAxObject*, int, int, QVariant&, QVariant&)", params);
	table = selection->querySubObject("Tables(int)",1);
	table->setProperty("Style","������"); 

	QAxObject* Borders = table->querySubObject("Borders");
	if(nullptr==Borders)
	{
		return;
	}
	Borders->setProperty("InsideLineStyle",1);
	Borders->setProperty("OutsideLineStyle",1);
}
////���ñ���п�
void QWord::setColumnWidth(int nTable,int column,int width)
{
	QAxObject* pTables =m_document->querySubObject("Tables");
	if(nullptr== pTables)
	{
		return;
	}
	QAxObject* table=pTables->querySubObject("Item(int)",nTable);
	if(table)
	{
      table->querySubObject("Columns(int)",column)->setProperty("width",width);
	}
	
}


//�ڱ���в���ͼƬ
void QWord::insertCellPic(int nTable,int row,int column,const QString& picPath)
{
	QAxObject* pTables=m_document->querySubObject("Tables");
 	if(nullptr== pTables)
 	{
 		return;
 	}
	QAxObject* table=pTables->querySubObject("Item(int)",nTable);
	if(nullptr== table)
	{
		return;
	}
	QAxObject* range=table->querySubObject("Cell(int,int )",row,column)->querySubObject("Range");                      
	if(nullptr== range)
	{
		return;
	}
	range->querySubObject("InlineShapes")->dynamicCall("AddPicture(const QString&)",picPath);
}

//�������ݴ���
void QWord::setCellFontBold(int nTable,int row,int column,bool isBold)
{
	QAxObject* pTables = m_document->querySubObject("Tables");
	if(nullptr== pTables)
	{
		return;
	}
	QAxObject* table =pTables->querySubObject("Item(int)",nTable);
	if(nullptr== table)
	{
		return;
	}
	table->querySubObject("Cell(int,int )",row,column)->querySubObject("Range")->dynamicCall("SetBold(int)",isBold);
	                          
							   
}
//�������ִ�С
void QWord:: setCellFontSize(int nTable,int row,int column,int size)
{
	QAxObject* pTables=m_document->querySubObject("Tables");
	if(nullptr== pTables)
	{
		return;
	}
	QAxObject* table =pTables->querySubObject("Item(int)",nTable);
	if(nullptr== table)
	{
		return;
	}
	table->querySubObject("Cell(int,int)",row,column)->querySubObject("Range")->querySubObject("Font")->setProperty("Size",size);
	                         
}

void QWord::setVisible(bool isVisible)
{
	if(m_word != nullptr)
	{
		m_word->setProperty("Visible",isVisible);
	}
}
