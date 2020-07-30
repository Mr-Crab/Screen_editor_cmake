#include "ToolTipWidget.h"
#include <QVBoxLayout>

ToolTipWidget::ToolTipWidget(QWidget *parent)
	: QWidget(parent)
	,m_label(nullptr)
	,m_widget(nullptr)
{
	QVBoxLayout* _mainVLayout = new QVBoxLayout(this);
	m_widget = new QWidget();
	m_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	_mainVLayout->addWidget(m_widget);
	m_label = new QLabel();
	m_label->setAlignment(Qt::AlignCenter);
	m_label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	_mainVLayout->addWidget(m_label);
}

ToolTipWidget::~ToolTipWidget()
{
}

void ToolTipWidget::setToolTipImage(QString imagePath)
{
	m_widget->setStyleSheet("border-image:url(" + imagePath + ");");
}

void ToolTipWidget::setImageName(QString iamgeName)
{
	m_label->setText(iamgeName);
}
