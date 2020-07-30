#include "ButtonItem.h"
#include "config.h"
#include <QDrag>
#include <QMimeData>
#include <QApplication>

ButtonItem::ButtonItem(QWidget *parent)
	: QPushButton(parent)
	,m_message("")
	,m_pageName("")
	,m_buttonName("")
{
	this->setCheckable(1);
	this->setObjectName("button_item");
	this->setStyleSheet(
		"#button_item{ border:2px solid rgb(0,255,0);background:#30000000}"
		"#button_item::hover{ border:2px solid rgb(255,255,0);}"
		"#button_item::pressed{ border:2px solid rgb(255,0,0);}"
	);
}

ButtonItem::~ButtonItem()
{
}

void ButtonItem::setButtonName(const QString& buttonName)
{
	m_buttonName = buttonName;
	this->setToolTip(buttonName);
}

QString ButtonItem::getButtonName()
{
	return m_buttonName;
}

void ButtonItem::setPageName(const QString& pageName)
{
	m_pageName = pageName;
}

QString ButtonItem::getPageName()
{
	return m_pageName;
}

void ButtonItem::setMessageName(const QString& messageName)
{
	m_message = messageName;
}

QString ButtonItem::getMessageName()
{
	return m_message;
}

void ButtonItem::updateByButtonInfo(const ButtonInfo* info)
{
	m_buttonName = info->m_buttonName;
	m_pageName = info->m_pageName;
	m_message = info->m_message;
	this->setGeometry(info->m_posX, info->m_posY, info->m_width, info->m_height);
}

void ButtonItem::mousePressEvent(QMouseEvent *e)
{
	if (e->button() == Qt::LeftButton)
	{
		m_startPoint = e->pos();
	}
}

void ButtonItem::mouseMoveEvent(QMouseEvent* e)
{
	if (e->buttons() & Qt::LeftButton)
	{
		if ((e->pos() - m_startPoint).manhattanLength() < QApplication::startDragDistance())
			return;

		QDrag* _darg = new QDrag(this);
		QMimeData* _mimeData = new QMimeData();
		_mimeData->setData("btn", "");
		_mimeData->setText(m_buttonName);
		_darg->setMimeData(_mimeData);
		_darg->exec();
	}
}

void ButtonItem::mouseDoubleClickEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		emit sigItemDClicked(this);
	}
}
