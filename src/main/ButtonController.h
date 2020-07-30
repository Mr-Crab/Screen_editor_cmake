#pragma once
#include "Controller.h"
#include "ButtonInfoManager.h"
#include "config.h"
#include <QDomElement>

class ButtonInfo;
class ButtonController : public Controller
{
public:
	ButtonController();
	~ButtonController();

	void clearContent();
	void creatButton(ButtonInfo* info);
	void changeButton(const QString& oldName, ButtonInfo* info);
	void deleteButton(const QString& buttonName);

	void deletePage(const QString& pageName);

	ButtonInfo* getButtonInfoByButtonName(const QString& buttonName);
	int getNumButtonInfos();
	ButtonInfo* getButtonInfo(int index);

	void addButtonInfosByDocNode(const QDomElement& buttonsNode);
	void printManagerInfo();

	QVector<ButtonInfo*> getButtonInfos();

private:
	ButtonInfoManager* m_buttonInfoManager;
};
