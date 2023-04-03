/********************************************************************************
** Form generated from reading UI file 'Weather_Info.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WEATHER_INFO_H
#define UI_WEATHER_INFO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Weather_Info
{
public:
    QVBoxLayout *verticalLayout;

    void setupUi(QWidget *Weather_Info)
    {
        if (Weather_Info->objectName().isEmpty())
            Weather_Info->setObjectName(QStringLiteral("Weather_Info"));
        Weather_Info->resize(809, 503);
        verticalLayout = new QVBoxLayout(Weather_Info);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));

        retranslateUi(Weather_Info);

        QMetaObject::connectSlotsByName(Weather_Info);
    } // setupUi

    void retranslateUi(QWidget *Weather_Info)
    {
        Weather_Info->setWindowTitle(QApplication::translate("Weather_Info", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Weather_Info: public Ui_Weather_Info {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WEATHER_INFO_H
