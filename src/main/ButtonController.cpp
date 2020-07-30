#include "ButtonController.h"
#include "Observer.h"

ButtonController::ButtonController()
{
	m_buttonInfoManager = new ButtonInfoManager();
}

ButtonController::~ButtonController()
{
}

void ButtonController::clearContent()
{
	m_buttonInfoManager->clearContent();
}

void ButtonController::creatButton(ButtonInfo* info)
{
	if (!m_buttonInfoManager->createButtonInfo(info))
		return;

	for (int i = 0; i < getNumObservers() ; i++)
	{
		Observer* _observer = getObserver(i);
		_observer->onCreateButton(info);
	}
}

void ButtonController::changeButton(const QString& oldName, ButtonInfo* info)
{
	if (!m_buttonInfoManager->changeButtonInfo(oldName, info))
		return;

	for (int i = 0; i < getNumObservers(); i++)
	{
		Observer* _observer = getObserver(i);
		_observer->onButtonChanged(oldName, info);
	}
}

void ButtonController::deleteButton(const QString& buttonName)
{
	if (!m_buttonInfoManager->deleteButtonInfo(buttonName))
		return;

	for (int i = 0; i < getNumObservers(); i++)
	{
		Observer* _observer = getObserver(i);
		_observer->onDeleteButton(buttonName);
	}
}

void ButtonController::deletePage(const QString& pageName)
{
	for (int i = 0; i < getNumObservers(); i++)
	{
		Observer* _observer = getObserver(i);
		_observer->onPageDelete(pageName);
	}
}

ButtonInfo* ButtonController::getButtonInfoByButtonName(const QString& buttonName)
{
	return m_buttonInfoManager->getButtonInfoByButtonName(buttonName);
}

int ButtonController::getNumButtonInfos()
{
	return m_buttonInfoManager->getNumButtonInfos();
}

ButtonInfo* ButtonController::getButtonInfo(int index)
{
	return m_buttonInfoManager->getButtonInfo(index);
}

void ButtonController::addButtonInfosByDocNode(const QDomElement& buttonsNode)
{
	m_buttonInfoManager->addButtonInfosByDocNode(buttonsNode);
}

void ButtonController::printManagerInfo()
{
	m_buttonInfoManager->printManagerInfo();
}

QVector<ButtonInfo*> ButtonController::getButtonInfos()
{
	return m_buttonInfoManager->getButtonInfos();
}
