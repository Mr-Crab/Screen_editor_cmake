#include "PageWidget.h"
#include "PageItem.h"
#include "AppManager.h"
#include "ScreenEditor.h"
#include <QPoint>
#include <QPainter>
#include <QRect>
#include <QMessageBox>
#include <QStyleOption>
#include "ButtonInfoManager.h"
#include "ButtonPropertyDialog.h"
#include "config.h"
#include "ButtonItem.h"
#include "ButtonController.h"
#include <QDebug>

PageWidget::PageWidget(QWidget *parent)
	: QWidget(parent)
	, m_pageName("")
	, m_tempButtonItem(nullptr)
	, m_currentItem(nullptr)
{
	this->setMouseTracking(true);
}

PageWidget::~PageWidget()
{
}

void PageWidget::clearContent()
{
	for (int i = 0; i < m_buttonItems.size(); i++)
	{
		delete m_buttonItems[i];
		m_buttonItems[i] = nullptr;
	}
	m_buttonItems.clear();
	this->setStyleSheet("background-image: url();");

	deleteTempItem();
}

void PageWidget::updateByPageItem(PageItem* pageItem)
{
	clearContent();

	QString _imagePath = pageItem->getPageImage();
	this->setStyleSheet("background-image: url(" + _imagePath + ");");
	m_pageName = pageItem->getPageName();

	for (int i = 0; i < pageItem->getNumButtonNames(); i++)
	{
		QString _buttonName = pageItem->getButtonName(i);
		ButtonInfo* _info = AppManager::getInstance()->m_buttonController->getButtonInfoByButtonName(_buttonName);
		if (!_info)
			continue;

		addButtonItem(_info);
	}
}

void PageWidget::addButtonItem(const ButtonInfo* buttonInfo)
{
	ButtonItem* _item = new ButtonItem(this);
	_item->setGeometry(buttonInfo->m_posX, buttonInfo->m_posY, buttonInfo->m_width, buttonInfo->m_height);
	_item->setButtonName(buttonInfo->m_buttonName);
	_item->setPageName(buttonInfo->m_pageName);
	_item->setMessageName(buttonInfo->m_message);
	_item->show();
	connect(_item, &ButtonItem::sigItemDClicked, this, &PageWidget::onItemClicked);
	m_buttonItems.push_back(_item);
}

ButtonItem* PageWidget::getButtonItemByName(const QString& buttonName)
{
	for (int i = 0; i < m_buttonItems.size(); i++)
	{
		if (m_buttonItems[i]->getButtonName() == buttonName)
			return m_buttonItems[i];
	}

	return nullptr;
}

void PageWidget::deleteTempItem()
{
	if (m_tempButtonItem != nullptr)
	{
		m_tempButtonItem->deleteLater();
		m_tempButtonItem = nullptr;
	}
}

void PageWidget::changeButtonSelectState(ButtonItem* item)
{
	for (int i = 0; i < m_buttonItems.size(); i++)
	{
		if (item != m_buttonItems[i])
			m_buttonItems[i]->setChecked(0);
		else
			item->setChecked(1);
	}
}

void PageWidget::deleteItem(ButtonItem* item)
{
	for (int i = 0; i < m_buttonItems.size(); i++)
	{
		if (item == m_buttonItems[i])
		{
			delete m_buttonItems[i];
			m_buttonItems[i] = nullptr;
			m_buttonItems.remove(i);
			return;
		}
	}
}

void PageWidget::printPageWidgetInfo()
{
	for (int i = 0; i < m_buttonItems.size(); i++)
	{
		qDebug() << "PageWidget:buttonName:" << m_buttonItems[i]->getButtonName();
		qDebug() << "PageWidget:pageName:" << m_buttonItems[i]->getPageName();
		qDebug() << "PageWidget:message:" << m_buttonItems[i]->getMessageName();
	}
}

void PageWidget::onItemClicked(ButtonItem* item)
{
	m_currentItem = item;
	changeButtonSelectState(item);

	ButtonPropertyDialog::getInstance()->setButtonType(CHANGE);
	ButtonPropertyDialog::getInstance()->setPropertyValue(item->getButtonName(), item->getPageName(), item->getMessageName(), item->pos().x(), item->pos().y(), item->width(), item->height());
	ButtonPropertyDialog::getInstance()->show();
}

void PageWidget::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event);

	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void PageWidget::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton || event->button() == Qt::MidButton)
	{
		m_startPoint = event->pos();
	}
}

void PageWidget::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		if (!AppManager::getInstance()->m_mainWindow->isButtonChecked())
			return;

		if (!m_tempButtonItem)
			return;

		ButtonPropertyDialog::getInstance()->setButtonType(CREATE);
		ButtonPropertyDialog::getInstance()->setPropertyValue(m_tempButtonItem->getButtonName(), m_tempButtonItem->getPageName(), m_tempButtonItem->getMessageName(), m_tempButtonItem->pos().x(), m_tempButtonItem->pos().y(), m_tempButtonItem->width(), m_tempButtonItem->height());
		ButtonPropertyDialog::getInstance()->show();
	}
}

void PageWidget::mouseMoveEvent(QMouseEvent *event)
{
	int x = event->pos().x();
	int y = event->pos().y();
	AppManager::getInstance()->m_mainWindow->setStateInfo("X:" + QString::number(x) + " - Y:" + QString::number(y));

	if (event->buttons()&Qt::LeftButton)
	{
		if (!AppManager::getInstance()->m_mainWindow->isButtonChecked())
			return;

		if (m_tempButtonItem != nullptr)
		{
			m_tempButtonItem->deleteLater();
			m_tempButtonItem = nullptr;
		}
		QPoint _tempPos = event->pos();
		m_tempButtonItem = new ButtonItem(this);
		int _width = _tempPos.x() - m_startPoint.x();
		int _height = _tempPos.y() - m_startPoint.y();
		if (_width < 2 || _height < 2)
			return;

		m_tempButtonItem = new ButtonItem(this);
		int _count = AppManager::getInstance()->m_buttonController->getNumButtonInfos();
		m_tempButtonItem->setButtonName(m_pageName + "#" + QString::number(_count));
		m_tempButtonItem->setGeometry(m_startPoint.x(), m_startPoint.y(), _width, _height);
		m_tempButtonItem->show();
	}
	else if (event->buttons() & Qt::MidButton)
	{
		QPoint _temPos = event->pos();
		int _width = _temPos.x() - m_startPoint.x();
		int _height = _temPos.y() - m_startPoint.y();

		if (abs(_width) < 10 && abs(_height) < 10)
			return;

		AppManager::getInstance()->m_mainWindow->changeScrollValue(_width, _height);
		m_startPoint = event->pos();
		this->repaint();
	}
}

void PageWidget::onCreateButton(ButtonInfo* info)
{
	addButtonItem(info);
}

void PageWidget::onButtonChanged(const QString& oldName, ButtonInfo* info)
{
	ButtonItem* _tempItem = getButtonItemByName(oldName);
	if (!_tempItem)
	{
		QMessageBox::information(this, tr("提示"), tr("按钮属性设置失败"));
		return;
	}

	_tempItem->updateByButtonInfo(info);
}

void PageWidget::onDeleteButton(const QString& buttonName)
{
	ButtonItem* _tempItem = getButtonItemByName(buttonName);
	if (!_tempItem)
	{
		QMessageBox::information(this, tr("提示"), tr("onDeleteButton 出错"));
		return;
	}

	deleteItem(_tempItem);
}

void PageWidget::onPageDelete(const QString& pageName)
{
	clearContent();
	m_pageName = "";
}
