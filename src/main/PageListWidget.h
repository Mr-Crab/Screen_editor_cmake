#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include "Observer.h"
#include <QDomElement>

class PageItem;
class QKeyEvent;

class PageListWidget : public QWidget, public Observer
{
	Q_OBJECT

public:
	PageListWidget(QWidget *parent);
	~PageListWidget();

	void clearContetn();
	void addPagesByDocNode(QDomElement& pagesNode);

	void addPageItem(const QString& imagePath);
	PageItem* getSelectPageItem();
	void printPageInfo();
	QVector<PageItem*> getPageItems();

	int getNumPageItems();

	public slots:
	void pageItemDClicked(PageItem* item);
	void onAddPageItem();

protected:
	virtual void keyReleaseEvent(QKeyEvent *event);

	virtual void onCreateButton(ButtonInfo* info);
	virtual void onButtonChanged(const QString& oldName, ButtonInfo* info);
	virtual void onDeleteButton(const QString& buttonName);
	virtual void onPageDelete(const QString& pageName);


private:
	QVector<PageItem*> m_pageItems;
	QVBoxLayout* m_mainVLayout;
	QVBoxLayout* m_contentLayout;
};
