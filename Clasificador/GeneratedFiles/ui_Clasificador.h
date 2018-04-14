/********************************************************************************
** Form generated from reading UI file 'Clasificador.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLASIFICADOR_H
#define UI_CLASIFICADOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "qtimagemanager.h"

QT_BEGIN_NAMESPACE

class Ui_CClasificadorClass
{
public:
    QWidget *centralWidget;
    QPushButton *ssButton;
    QLineEdit *lineEdit;
    CQtImageManager *cuadro;
    QPushButton *ssButton_2;
    CQtImageManager *video;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CClasificadorClass)
    {
        if (CClasificadorClass->objectName().isEmpty())
            CClasificadorClass->setObjectName(QStringLiteral("CClasificadorClass"));
        CClasificadorClass->resize(1448, 826);
        centralWidget = new QWidget(CClasificadorClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        ssButton = new QPushButton(centralWidget);
        ssButton->setObjectName(QStringLiteral("ssButton"));
        ssButton->setGeometry(QRect(30, 540, 771, 87));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(30, 640, 771, 68));
        cuadro = new CQtImageManager(centralWidget);
        cuadro->setObjectName(QStringLiteral("cuadro"));
        cuadro->setGeometry(QRect(830, 230, 250, 298));
        ssButton_2 = new QPushButton(centralWidget);
        ssButton_2->setObjectName(QStringLiteral("ssButton_2"));
        ssButton_2->setGeometry(QRect(840, 540, 231, 31));
        video = new CQtImageManager(centralWidget);
        video->setObjectName(QStringLiteral("video"));
        video->setGeometry(QRect(30, 57, 771, 471));
        CClasificadorClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(CClasificadorClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1448, 26));
        CClasificadorClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(CClasificadorClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        CClasificadorClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(CClasificadorClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        CClasificadorClass->setStatusBar(statusBar);

        retranslateUi(CClasificadorClass);

        QMetaObject::connectSlotsByName(CClasificadorClass);
    } // setupUi

    void retranslateUi(QMainWindow *CClasificadorClass)
    {
        CClasificadorClass->setWindowTitle(QApplication::translate("CClasificadorClass", "CClasificador", nullptr));
        ssButton->setText(QApplication::translate("CClasificadorClass", "Start/Stop", nullptr));
        ssButton_2->setText(QApplication::translate("CClasificadorClass", "Ver leyenda", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CClasificadorClass: public Ui_CClasificadorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLASIFICADOR_H
