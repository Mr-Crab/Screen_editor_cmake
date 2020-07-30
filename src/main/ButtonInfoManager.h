#pragma once

#include "config.h"
#include <QVector>
#include <QDomElement>

class ButtonInfoManager
{

public:
	ButtonInfoManager();
	~ButtonInfoManager();

public:
	void clearContent();
	bool createButtonInfo(ButtonInfo* info);
	bool changeButtonInfo(const QString& oldName, ButtonInfo* info);
	bool deleteButtonInfo(const QString& buttonName);

	ButtonInfo* getButtonInfoByButtonName(const QString &buttonName);

	int getNumButtonInfos();
	ButtonInfo* getButtonInfo(int index);

	QVector<ButtonInfo*> getButtonInfos();

	void addButtonInfosByDocNode(const QDomElement& buttonsNode);
	void printManagerInfo();

private:
	QVector<ButtonInfo*> m_buttonInfos;

};
