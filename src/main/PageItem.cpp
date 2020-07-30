#include "PageItem.h"
#include <QIcon>
#include <QFileInfo>
#include <QCursor>
#include <QDrag>
#include <QPoint>
#include <QMimeData>
#include <qapplication.h>
#include <QPixmap>
#include <QPainter>
#include <QImage>
#include <QRect>
#include <QDragEnterEvent>
#include <QDropEvent>
#include "ToolTipWidget.h"
#include "AppManager.h"
#include "ScreenEditor.h"
#include "ToolTipWidget.h"

PageItem::PageItem(QWidget* parent)
	:QToolButton(parent)
	, m_imagePath("")
	,m_pageName("")
{
	this->setFixedHeight(128);
	this->setCheckable(1);
	this->setAcceptDrops(true);
	this->setIconSize(QSize(192, 108));
	this->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	this->setObjectName("page_item");
	this->setStyleSheet(
		"#page_item::checked{ border:2px solid rgb(255,0,0);}"
	);
}

PageItem::~PageItem()
{
	m_buttonNames.clear();
}

void PageItem::setPageImage(const QString& imagePath)
{
	m_imagePath = imagePath;
	this->setIcon(QIcon(imagePath));
}

QString PageItem::getPageImage()
{
	return m_imagePath;
}

void PageItem::setPageName(const QString& pageName)
{
	m_pageName = pageName;
	this->setText(pageName);
}

QString PageItem::getPageName()
{
	return m_pageName;
}

void PageItem::clearButtonNames()
{
	m_buttonNames.clear();
}

bool PageItem::isExsitName(const QString& name)
{
	for (int i = 0; i < m_buttonNames.size(); i++)
	{
		if (m_buttonNames[i] == name)
			return true;
	}

	return false;
}

void PageItem::addButtonName(const QString& buttonName)
{
	if (isExsitName(buttonName))
		return;

	m_buttonNames.push_back(buttonName);
}

void PageItem::removeButtonName(const QString& buttonName)
{
	for (int i = 0; i < m_buttonNames.size(); i++)
	{
		if (m_buttonNames[i] == buttonName)
		{
			m_buttonNames.remove(i);
			return;
		}
	}
}

void PageItem::changeButtonName(const QString& oldButtonName, const QString& newButtonName)
{
	for (int i = 0; i < m_buttonNames.size(); i++)
	{
		if (m_buttonNames[i] == oldButtonName)
		{
			m_buttonNames[i] = newButtonName;
			return;
		}
	}
}

int PageItem::getNumButtonNames()
{
	return m_buttonNames.size();
}

QString PageItem::getButtonName(int index)
{
	return m_buttonNames[index];
}

void PageItem::enterEvent(QEvent *event)
{
	if(AppManager::getInstance()->m_toolTipWidget->isHidden() && AppManager::getInstance()->m_mainWindow->isToolTipChecked())
	{
		QPoint _point = QCursor::pos();
		AppManager::getInstance()->m_toolTipWidget->setToolTipImage(m_imagePath);
		AppManager::getInstance()->m_toolTipWidget->setImageName(m_pageName);
		AppManager::getInstance()->m_toolTipWidget->setGeometry(_point.x(), _point.y(), 768, 450);
		AppManager::getInstance()->m_toolTipWidget->show();
	}
}

void PageItem::leaveEvent(QEvent *event)
{
	if (!AppManager::getInstance()->m_toolTipWidget->isHidden())
		AppManager::getInstance()->m_toolTipWidget->close();
}

void PageItem::mousePressEvent(QMouseEvent *e)
{
	if (e->button() == Qt::LeftButton)
	{
		m_startPoint = e->pos();
	}
	QToolButton::mousePressEvent(e);
}

void PageItem::mouseMoveEvent(QMouseEvent *e)
{
	if (e->buttons()& Qt::LeftButton)
	{
		if ((e->pos() - m_startPoint).manhattanLength() < QApplication::startDragDistance())
			return;

		QDrag* drag = new QDrag(this);
		QMimeData* _miniData = new QMimeData();
		_miniData->setText(m_pageName);
		drag->setMimeData(_miniData);

		QPixmap _dragimage(96, 54);
		QPainter _painter(&_dragimage);
		_painter.drawImage(QRect(0, 0, 96, 54), QImage(m_imagePath));
		drag->setPixmap(_dragimage);

		drag->exec();
	}
	QToolButton::mouseMoveEvent(e);
}

void PageItem::mouseReleaseEvent(QMouseEvent* event)
{

}

void PageItem::mouseDoubleClickEvent(QMouseEvent *event)
{
	Q_UNUSED(event);

	emit sigItemDClicked(this);
}

void PageItem::dragEnterEvent(QDragEnterEvent *event)
{
	if (event->mimeData()->hasFormat("btn"))
	{
		event->acceptProposedAction();
		return;
	}

	event->ignore();
}

void PageItem::dropEvent(QDropEvent *event)
{
	if (event->mimeData()->hasFormat("btn"))
	{
		QString _buttonName = event->mimeData()->text();
		addButtonName(_buttonName);
	}
}

