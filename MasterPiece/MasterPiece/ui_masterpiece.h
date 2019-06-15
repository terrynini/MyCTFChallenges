/********************************************************************************
** Form generated from reading UI file 'masterpiece.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MASTERPIECE_H
#define UI_MASTERPIECE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "board.h"

QT_BEGIN_NAMESPACE

class Ui_MasterPiece
{
public:
    QWidget *centralWidget;
    Board *widget;
    QLabel *label;
    QPushButton *pushButton;
    QLabel *label_2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MasterPiece)
    {
        if (MasterPiece->objectName().isEmpty())
            MasterPiece->setObjectName(QStringLiteral("MasterPiece"));
        MasterPiece->resize(1047, 619);
        centralWidget = new QWidget(MasterPiece);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        widget = new Board(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(340, 40, 650, 410));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setEnabled(true);
        label->setGeometry(QRect(0, 30, 521, 651));
        label->setPixmap(QPixmap(QString::fromUtf8(":/bob-ross.png")));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(510, 520, 321, 41));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(520, 460, 302, 57));
        QFont font;
        font.setPointSize(48);
        label_2->setFont(font);
        label_2->setScaledContents(false);
        MasterPiece->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MasterPiece);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1047, 22));
        MasterPiece->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MasterPiece);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MasterPiece->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MasterPiece);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MasterPiece->setStatusBar(statusBar);

        retranslateUi(MasterPiece);

        QMetaObject::connectSlotsByName(MasterPiece);
    } // setupUi

    void retranslateUi(QMainWindow *MasterPiece)
    {
        MasterPiece->setWindowTitle(QApplication::translate("MasterPiece", "MasterPiece", 0));
        label->setText(QString());
        pushButton->setText(QApplication::translate("MasterPiece", "Is this flag?", 0));
        label_2->setText(QApplication::translate("MasterPiece", "Draw me a flag", 0));
    } // retranslateUi

};

namespace Ui {
    class MasterPiece: public Ui_MasterPiece {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MASTERPIECE_H
