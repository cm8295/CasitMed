/********************************************************************************
** Form generated from reading UI file 'casitmedclient.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CASITMEDCLIENT_H
#define UI_CASITMEDCLIENT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListView>
#include <QtGui/QMainWindow>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CasitMedClientClass
{
public:
    QWidget *centralWidget;
    QPushButton *downLoadButton;
    QLineEdit *leDownLoad;
    QLabel *lb1_1;
    QLabel *lb1_2;
    QLabel *lb1_3;
    QLabel *lb1_4;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QProgressBar *clientProgressBar;
    QTabWidget *tabWidget;
    QWidget *menu1;
    QListView *lvShowView;
    QWidget *menu2;
    QListView *lvShowOk;
    QLabel *lbtransfer;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pbSure;
    QPushButton *pbWatchPath;
    QLineEdit *leWatchPath;
    QLabel *lbspeed;
    QPushButton *pbClose;
    QPushButton *pbMin;
    QPushButton *pbSet;

    void setupUi(QMainWindow *CasitMedClientClass)
    {
        if (CasitMedClientClass->objectName().isEmpty())
            CasitMedClientClass->setObjectName(QString::fromUtf8("CasitMedClientClass"));
        CasitMedClientClass->resize(590, 422);
        CasitMedClientClass->setLayoutDirection(Qt::RightToLeft);
        centralWidget = new QWidget(CasitMedClientClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        downLoadButton = new QPushButton(centralWidget);
        downLoadButton->setObjectName(QString::fromUtf8("downLoadButton"));
        downLoadButton->setGeometry(QRect(814, 440, 61, 23));
        leDownLoad = new QLineEdit(centralWidget);
        leDownLoad->setObjectName(QString::fromUtf8("leDownLoad"));
        leDownLoad->setGeometry(QRect(810, 410, 61, 20));
        lb1_1 = new QLabel(centralWidget);
        lb1_1->setObjectName(QString::fromUtf8("lb1_1"));
        lb1_1->setGeometry(QRect(226, 390, 51, 16));
        lb1_2 = new QLabel(centralWidget);
        lb1_2->setObjectName(QString::fromUtf8("lb1_2"));
        lb1_2->setGeometry(QRect(283, 393, 54, 12));
        lb1_3 = new QLabel(centralWidget);
        lb1_3->setObjectName(QString::fromUtf8("lb1_3"));
        lb1_3->setGeometry(QRect(364, 390, 61, 16));
        lb1_4 = new QLabel(centralWidget);
        lb1_4->setObjectName(QString::fromUtf8("lb1_4"));
        lb1_4->setGeometry(QRect(431, 391, 61, 16));
        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 58, 561, 321));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        clientProgressBar = new QProgressBar(gridLayoutWidget);
        clientProgressBar->setObjectName(QString::fromUtf8("clientProgressBar"));
        clientProgressBar->setLayoutDirection(Qt::LeftToRight);
        clientProgressBar->setValue(0);

        gridLayout->addWidget(clientProgressBar, 0, 0, 1, 1);

        tabWidget = new QTabWidget(gridLayoutWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setLayoutDirection(Qt::LeftToRight);
        tabWidget->setAutoFillBackground(false);
        tabWidget->setIconSize(QSize(16, 16));
        menu1 = new QWidget();
        menu1->setObjectName(QString::fromUtf8("menu1"));
        lvShowView = new QListView(menu1);
        lvShowView->setObjectName(QString::fromUtf8("lvShowView"));
        lvShowView->setGeometry(QRect(-1, -1, 561, 271));
        lvShowView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tabWidget->addTab(menu1, QString());
        menu2 = new QWidget();
        menu2->setObjectName(QString::fromUtf8("menu2"));
        lvShowOk = new QListView(menu2);
        lvShowOk->setObjectName(QString::fromUtf8("lvShowOk"));
        lvShowOk->setGeometry(QRect(-1, -5, 561, 281));
        lvShowOk->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tabWidget->addTab(menu2, QString());

        gridLayout->addWidget(tabWidget, 2, 0, 1, 1);

        lbtransfer = new QLabel(centralWidget);
        lbtransfer->setObjectName(QString::fromUtf8("lbtransfer"));
        lbtransfer->setGeometry(QRect(20, 388, 191, 21));
        horizontalLayoutWidget_2 = new QWidget(centralWidget);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(190, 23, 381, 31));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        pbSure = new QPushButton(horizontalLayoutWidget_2);
        pbSure->setObjectName(QString::fromUtf8("pbSure"));

        horizontalLayout_2->addWidget(pbSure);

        pbWatchPath = new QPushButton(horizontalLayoutWidget_2);
        pbWatchPath->setObjectName(QString::fromUtf8("pbWatchPath"));

        horizontalLayout_2->addWidget(pbWatchPath);

        leWatchPath = new QLineEdit(horizontalLayoutWidget_2);
        leWatchPath->setObjectName(QString::fromUtf8("leWatchPath"));

        horizontalLayout_2->addWidget(leWatchPath);

        lbspeed = new QLabel(centralWidget);
        lbspeed->setObjectName(QString::fromUtf8("lbspeed"));
        lbspeed->setGeometry(QRect(498, 389, 71, 20));
        pbClose = new QPushButton(centralWidget);
        pbClose->setObjectName(QString::fromUtf8("pbClose"));
        pbClose->setGeometry(QRect(531, 0, 41, 23));
        pbClose->setFocusPolicy(Qt::NoFocus);
        pbClose->setIconSize(QSize(0, 0));
        pbMin = new QPushButton(centralWidget);
        pbMin->setObjectName(QString::fromUtf8("pbMin"));
        pbMin->setGeometry(QRect(480, 0, 51, 23));
        pbSet = new QPushButton(centralWidget);
        pbSet->setObjectName(QString::fromUtf8("pbSet"));
        pbSet->setGeometry(QRect(379, 0, 101, 23));
        CasitMedClientClass->setCentralWidget(centralWidget);

        retranslateUi(CasitMedClientClass);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(CasitMedClientClass);
    } // setupUi

    void retranslateUi(QMainWindow *CasitMedClientClass)
    {
        CasitMedClientClass->setWindowTitle(QApplication::translate("CasitMedClientClass", "CasitMedClient", 0, QApplication::UnicodeUTF8));
        downLoadButton->setText(QApplication::translate("CasitMedClientClass", "DownLoad", 0, QApplication::UnicodeUTF8));
        leDownLoad->setText(QApplication::translate("CasitMedClientClass", "b.pdf", 0, QApplication::UnicodeUTF8));
        lb1_1->setText(QApplication::translate("CasitMedClientClass", "\346\200\273\346\226\207\344\273\266\357\274\232", 0, QApplication::UnicodeUTF8));
        lb1_2->setText(QApplication::translate("CasitMedClientClass", "0", 0, QApplication::UnicodeUTF8));
        lb1_3->setText(QApplication::translate("CasitMedClientClass", "\345\211\251\344\275\231\344\274\240\350\276\223\357\274\232", 0, QApplication::UnicodeUTF8));
        lb1_4->setText(QApplication::translate("CasitMedClientClass", "0", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(menu1), QApplication::translate("CasitMedClientClass", "\346\255\243\345\234\250\344\274\240\350\276\223", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(menu2), QApplication::translate("CasitMedClientClass", "\344\274\240\350\276\223\345\256\214\346\210\220", 0, QApplication::UnicodeUTF8));
        lbtransfer->setText(QApplication::translate("CasitMedClientClass", "\346\240\207\350\257\206", 0, QApplication::UnicodeUTF8));
        pbSure->setText(QApplication::translate("CasitMedClientClass", "\347\241\256 \345\256\232", 0, QApplication::UnicodeUTF8));
        pbWatchPath->setText(QApplication::translate("CasitMedClientClass", "\346\265\217\350\247\210...", 0, QApplication::UnicodeUTF8));
        lbspeed->setText(QString());
        pbClose->setText(QApplication::translate("CasitMedClientClass", "\351\200\200\345\207\272", 0, QApplication::UnicodeUTF8));
        pbMin->setText(QApplication::translate("CasitMedClientClass", "\346\234\200\345\260\217\345\214\226", 0, QApplication::UnicodeUTF8));
        pbSet->setText(QApplication::translate("CasitMedClientClass", "\350\256\276\347\275\256\347\233\221\350\247\206\350\267\257\345\276\204", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CasitMedClientClass: public Ui_CasitMedClientClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CASITMEDCLIENT_H
