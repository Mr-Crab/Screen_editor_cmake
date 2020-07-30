#pragma once

#include <QString>

class ButtonInfo;
class Observer
{
public:
	Observer();
	~Observer();

public:
	virtual void onCreateButton(ButtonInfo* info) = 0;
	virtual void onButtonChanged(const QString& oldName, ButtonInfo* info) = 0;
	virtual void onDeleteButton(const QString& buttonName) = 0;

	virtual void onPageDelete(const QString& pageName) = 0;
};
