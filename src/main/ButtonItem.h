#pragma once

#include <QPushButton>
#include <QMouseEvent>
#include <QPoint>

class ButtonPropertyDialog;
class ButtonInfo;

class ButtonItem : public QPushButton
{
	Q_OBJECT

public:
	ButtonItem(QWidget *parent);
	~ButtonItem();

	void setButtonName(const QString& buttonName);
	QString getButtonName();

	void setPageName(const QString& buttonName);
	QString getPageName();

	void setMessageName(const QString& buttonName);
	QString getMessageName();


	void updateByButtonInfo(const ButtonInfo* info);

protected:
	virtual void mousePressEvent(QMouseEvent *e);
	virtual void mouseMoveEvent(QMouseEvent* e);
	virtual void mouseDoubleClickEvent(QMouseEvent *event);

signals:
	void sigItemDClicked(ButtonItem*);

private:
	QPoint m_startPoint;
	QString m_buttonName;
	QString m_pageName;
	QString m_message;
};
