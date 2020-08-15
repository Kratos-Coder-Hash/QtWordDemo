/********************************************************************************
** Form generated from reading UI file 'qworddemo.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QWORDDEMO_H
#define UI_QWORDDEMO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QWordDemo
{
public:
    QWidget *centralWidget;
    QPushButton *exportPushBtn;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QWordDemo)
    {
        if (QWordDemo->objectName().isEmpty())
            QWordDemo->setObjectName(QStringLiteral("QWordDemo"));
        QWordDemo->resize(400, 300);
        centralWidget = new QWidget(QWordDemo);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        exportPushBtn = new QPushButton(centralWidget);
        exportPushBtn->setObjectName(QStringLiteral("exportPushBtn"));
        exportPushBtn->setGeometry(QRect(140, 100, 93, 28));
        QWordDemo->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QWordDemo);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 26));
        QWordDemo->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QWordDemo);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QWordDemo->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QWordDemo);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QWordDemo->setStatusBar(statusBar);

        retranslateUi(QWordDemo);

        QMetaObject::connectSlotsByName(QWordDemo);
    } // setupUi

    void retranslateUi(QMainWindow *QWordDemo)
    {
        QWordDemo->setWindowTitle(QApplication::translate("QWordDemo", "QWordDemo", 0));
        exportPushBtn->setText(QApplication::translate("QWordDemo", "Export", 0));
    } // retranslateUi

};

namespace Ui {
    class QWordDemo: public Ui_QWordDemo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QWORDDEMO_H
