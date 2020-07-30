#pragma once

#include <QWidget>
#include <QMouseEvent>
#include <QPoint>
#include <QVector>
#include "Observer.h"

class PageItem;
class ButtonItem;
class ButtonInfo;
class PageWidget : public QWidget, public Observer
{
	Q_OBJECT

public:
	PageWidget(QWidget *parent = nullptr);
	~PageWidget();

	void clearContent();
	void updateByPageItem(PageItem* pageItem);
	void addButtonItem(const ButtonInfo* buttonInfo);

	ButtonItem* getButtonItemByName(const QString& buttonName);
	void deleteTempItem();
	void printPageWidgetInfo();

protected:
	virtual void paintEvent(QPaintEvent *event);
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);

	virtual void onCreateButton(ButtonInfo* info);
	virtual void onButtonChanged(const QString& oldName, ButtonInfo* info);
	virtual void onDeleteButton(const QString& buttonName);

	virtual void onPageDelete(const QString& pageName);

private:
	void changeButtonSelectState(ButtonItem* item);
	void deleteItem(ButtonItem* item);


private:
	QString m_pageName;
	QPoint m_startPoint;
	ButtonItem* m_tempButtonItem;
	ButtonItem* m_currentItem;
	QVector<ButtonItem*> m_buttonItems;

	public slots:
	void onItemClicked(ButtonItem* item);

};
