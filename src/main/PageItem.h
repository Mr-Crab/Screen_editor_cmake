#pragma once

#include <QToolButton>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QPoint>

class PageItem : public QToolButton
{
	Q_OBJECT

public:
	PageItem(QWidget* parent);
	~PageItem();

	void setPageImage(const QString& imagePath);
	QString getPageImage();

	void setPageName(const QString& pageName);
	QString getPageName();

	void clearButtonNames();
	bool isExsitName(const QString& name);
	void addButtonName(const QString& buttonName);
	void removeButtonName(const QString& buttonName);
	void changeButtonName(const QString& oldButtonName, const QString& newButtonName);

	int getNumButtonNames();
	QString getButtonName(int index);

protected:
	virtual void enterEvent(QEvent *event);
	virtual void leaveEvent(QEvent *event);
	virtual void mousePressEvent(QMouseEvent *e);
	virtual void mouseMoveEvent(QMouseEvent *e);
	virtual void mouseReleaseEvent(QMouseEvent* event);
	virtual void mouseDoubleClickEvent(QMouseEvent *event);

	virtual void dragEnterEvent(QDragEnterEvent *event);
	virtual void dropEvent(QDropEvent *event);

signals:
	void sigItemDClicked(PageItem*);

private:
	QPoint m_startPoint;

	QString m_imagePath;
	QString m_pageName;
	QVector<QString> m_buttonNames;
};

