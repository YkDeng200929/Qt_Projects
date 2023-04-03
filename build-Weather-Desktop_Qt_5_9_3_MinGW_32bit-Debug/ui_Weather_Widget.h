/********************************************************************************
** Form generated from reading UI file 'Weather_Widget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WEATHER_WIDGET_H
#define UI_WEATHER_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Weather_Widget
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label_data;
    QLabel *label_icon;
    QHBoxLayout *horizontalLayout;
    QLabel *label_low_temp;
    QLabel *label_high_temp;
    QLabel *label_text_info;

    void setupUi(QDialog *Weather_Widget)
    {
        if (Weather_Widget->objectName().isEmpty())
            Weather_Widget->setObjectName(QStringLiteral("Weather_Widget"));
        Weather_Widget->resize(146, 315);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Weather_Widget->sizePolicy().hasHeightForWidth());
        Weather_Widget->setSizePolicy(sizePolicy);
        Weather_Widget->setMaximumSize(QSize(146, 16777215));
        verticalLayout = new QVBoxLayout(Weather_Widget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_data = new QLabel(Weather_Widget);
        label_data->setObjectName(QStringLiteral("label_data"));
        label_data->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_data);

        label_icon = new QLabel(Weather_Widget);
        label_icon->setObjectName(QStringLiteral("label_icon"));
        label_icon->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_icon);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_low_temp = new QLabel(Weather_Widget);
        label_low_temp->setObjectName(QStringLiteral("label_low_temp"));
        label_low_temp->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label_low_temp);

        label_high_temp = new QLabel(Weather_Widget);
        label_high_temp->setObjectName(QStringLiteral("label_high_temp"));
        label_high_temp->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label_high_temp);


        verticalLayout->addLayout(horizontalLayout);

        label_text_info = new QLabel(Weather_Widget);
        label_text_info->setObjectName(QStringLiteral("label_text_info"));
        label_text_info->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_text_info);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 3);
        verticalLayout->setStretch(2, 1);
        verticalLayout->setStretch(3, 1);

        retranslateUi(Weather_Widget);

        QMetaObject::connectSlotsByName(Weather_Widget);
    } // setupUi

    void retranslateUi(QDialog *Weather_Widget)
    {
        Weather_Widget->setWindowTitle(QApplication::translate("Weather_Widget", "Dialog", Q_NULLPTR));
        label_data->setText(QApplication::translate("Weather_Widget", "data", Q_NULLPTR));
        label_icon->setText(QApplication::translate("Weather_Widget", "pic", Q_NULLPTR));
        label_low_temp->setText(QApplication::translate("Weather_Widget", "low", Q_NULLPTR));
        label_high_temp->setText(QApplication::translate("Weather_Widget", "high", Q_NULLPTR));
        label_text_info->setText(QApplication::translate("Weather_Widget", "info", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Weather_Widget: public Ui_Weather_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WEATHER_WIDGET_H
