#include "PageListWidget.h"
#include "PageItem.h"
#include <QFileDialog>
#include <AppManager.h>
#include <ScreenEditor.h>
#include <QStringList>
#include <QSpacerItem>
#include <QMessageBox>
#include "config.h"
#include <QKeyEvent>
#include <QFileInfo>
#include <QDebug>
#include "ButtonController.h"
#include "ButtonPropertyDialog.h"

PageListWidget::PageListWidget(QWidget *parent)
	: QWidget(parent)
	, m_mainVLayout(nullptr)
	,m_contentLayout(nullptr)
{
	m_mainVLayout = new QVBoxLayout(this);
	m_contentLayout = new QVBoxLayout();
	m_contentLayout->setSpacing(9);
	m_mainVLayout->addLayout(m_contentLayout);
	m_mainVLayout->addSpacerItem(new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Expanding));
	this->setFocusPolicy(Qt::StrongFocus);
}

PageListWidget::~PageListWidget()
{
}

void PageListWidget::clearContetn()
{
	for (int i = 0; i < m_pageItems.size(); i++)
	{
		delete m_pageItems[i];
		m_pageItems[i] = nullptr;
	}
	m_pageItems.clear();
}

void PageListWidget::addPagesByDocNode(QDomElement& pagesNode)
{
	QDomNodeList _nodeList = pagesNode.childNodes();
	for (int i = 0; i < _nodeList.count() ; i++)
	{
		QDomNode _pageNode = _nodeList.at(i);
		if (_pageNode.isElement())
		{
			PageItem* _pageItem = new PageItem(this);
			QDomElement _pageElement = _pageNode.toElement();
			QString _pageName = _pageElement.attribute("name");
			_pageItem->setPageName(_pageName);
			_pageItem->setPageImage(AppManager::getInstance()->m_outPutPath + "/" + _pageName + ".png");
			m_contentLayout->addWidget(_pageItem, 0);
			connect(_pageItem, &PageItem::sigItemDClicked, this, &PageListWidget::pageItemDClicked);

			QDomNodeList _itemList = _pageElement.childNodes();
			for (int j = 0; j < _itemList.count(); j++)
			{
				QDomNode _itemNode = _itemList.at(j);
				if (!_itemNode.isElement())
					continue;

				QDomElement _itemElement = _itemNode.toElement();
				QString _buttonName = _itemElement.attribute("button");
				_pageItem->addButtonName(_buttonName);
			}
			m_pageItems.push_back(_pageItem);
		}
	}
}

void PageListWidget::addPageItem(const QString& imagePath)
{
	QFileInfo _info(imagePath);
	if (!_info.exists())
	{
		QMessageBox::information(AppManager::getInstance()->m_mainWindow, tr("提示"), imagePath + "not exist");
		return;
	}


	PageItem* _item = new PageItem(this);
	_item->setPageImage(imagePath);
	_item->setPageName(_info.baseName());
	m_contentLayout->addWidget(_item, 0);
	m_pageItems.push_back(_item);

	connect(_item, &PageItem::sigItemDClicked, this, &PageListWidget::pageItemDClicked);
}

PageItem* PageListWidget::getSelectPageItem()
{
	for (int i = 0; i < m_pageItems.size(); i++)
	{
		PageItem* _item = m_pageItems[i];
		if (_item->isChecked())
			return _item;
	}

	return nullptr;
}

void PageListWidget::pageItemDClicked(PageItem* item)
{
	QString name = item->getPageName();
	for (int i = 0; i < m_pageItems.size(); i++)
	{
		PageItem* _item = m_pageItems[i];
		if (_item != item)
			_item->setChecked(0);
		else
			item->setChecked(1);
	}

	AppManager::getInstance()->m_pageWidget->updateByPageItem(item);
	AppManager::getInstance()->m_mainWindow->setPageName(item->getPageName());

	ButtonPropertyDialog::getInstance()->close();
}

void PageListWidget::onAddPageItem()
{
	if (AppManager::getInstance()->m_outPutPath == "")
		AppManager::getInstance()->m_outPutPath = QApplication::applicationDirPath();


	QStringList _list = QFileDialog::getOpenFileNames(AppManager::getInstance()->m_mainWindow, tr("提示"), AppManager::getInstance()->m_outPutPath, "*.png");
	
	for (int i = 0; i < _list.size(); i++)
	{
		if (i == 0)
		{
			QFileInfo _info(_list[0]);
			AppManager::getInstance()->m_outPutPath = _info.absoluteDir().absolutePath();
		}

		addPageItem(_list[i]);
	}
}

void PageListWidget::keyReleaseEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Delete)
	{
		PageItem* _item = getSelectPageItem();
		if (_item)
		{
			AppManager::getInstance()->m_buttonController->deletePage(_item->getPageName());
		}
	}
}

void PageListWidget::onCreateButton(ButtonInfo* info)
{
	PageItem* _pageItem = getSelectPageItem();
	if (!_pageItem)
		return;

	_pageItem->addButtonName(info->m_buttonName);
}

void PageListWidget::onButtonChanged(const QString& oldName, ButtonInfo* info)
{
	PageItem* _pageItem = getSelectPageItem();
	if (!_pageItem)
		return;

	_pageItem->changeButtonName(oldName, info->m_buttonName);
}

void PageListWidget::onDeleteButton(const QString& buttonName)
{
	PageItem* _pageItem = getSelectPageItem();
	if (!_pageItem)
		return;

	_pageItem->removeButtonName(buttonName);
}

void PageListWidget::onPageDelete(const QString& pageName)
{
	for (int i = 0; i < m_pageItems.size(); i++)
	{
		PageItem* _pageItem = m_pageItems[i];
		if (_pageItem->getPageName() == pageName)
		{
			delete _pageItem;
			_pageItem = nullptr;
			m_pageItems.remove(i);
		}
	}
}

void PageListWidget::printPageInfo()
{
	for (int i = 0; i < m_pageItems.size(); i++)
	{
		PageItem* _pageItem = m_pageItems[i];
		qDebug()<<"PageName:" << _pageItem->getPageName();
		for (int j = 0; j < _pageItem->getNumButtonNames(); j++)
		{
			qDebug() << _pageItem->getButtonName(j);
		}
		qDebug() << "==============";
	}
}

QVector<PageItem*> PageListWidget::getPageItems()
{
	return m_pageItems;
}

int PageListWidget::getNumPageItems()
{
	return m_pageItems.size();
}
