#include "ButtonInfoManager.h"
#include "QMessageBox"
#include <QObject>
#include <QDebug>
#include <QDomNode>

ButtonInfoManager::ButtonInfoManager()
{
}

ButtonInfoManager::~ButtonInfoManager()
{
}

void ButtonInfoManager::clearContent()
{
	for (int i = 0; i < m_buttonInfos.size(); i++)
	{
		delete m_buttonInfos[i];
		m_buttonInfos[i] = nullptr;
	}
	m_buttonInfos.clear();
}

bool ButtonInfoManager::createButtonInfo(ButtonInfo* info)
{
	ButtonInfo* _tempInfo = getButtonInfoByButtonName(info->m_buttonName);
	if (_tempInfo)
		return false;

	ButtonInfo* _info = new ButtonInfo(info);
	m_buttonInfos.push_back(_info);
	return true;
}

bool ButtonInfoManager::changeButtonInfo(const QString& oldName, ButtonInfo* info)
{
	ButtonInfo* _oldInfo = getButtonInfoByButtonName(oldName);
	if (!_oldInfo)
		return false;

	_oldInfo->copeInfo(info);
	return true;
}

bool ButtonInfoManager::deleteButtonInfo(const QString& buttonName)
{
	for (int i = 0; i < m_buttonInfos.size(); i++)
	{
		if (m_buttonInfos[i]->m_buttonName == buttonName)
		{
			m_buttonInfos.remove(i);
			return true;
		}
	}
	return false;
}

ButtonInfo* ButtonInfoManager::getButtonInfoByButtonName(const QString &buttonName)
{
	for (int i = 0; i < m_buttonInfos.size(); i++)
	{
		if (m_buttonInfos[i]->m_buttonName == buttonName)
			return m_buttonInfos[i];
	}
	return nullptr;
}

int ButtonInfoManager::getNumButtonInfos()
{
	return m_buttonInfos.size();
}

ButtonInfo* ButtonInfoManager::getButtonInfo(int index)
{
	return m_buttonInfos[index];
}

QVector<ButtonInfo*> ButtonInfoManager::getButtonInfos()
{
	return m_buttonInfos;
}

void ButtonInfoManager::addButtonInfosByDocNode(const QDomElement& buttonsNode)
{
	QDomNodeList _nodeList = buttonsNode.childNodes();
	for (int i = 0; i < _nodeList.count(); i++)
	{
		QDomNode _buttonNode = _nodeList.at(i);
		if (_buttonNode.isElement())
		{
			ButtonInfo* _buttonInfo = new ButtonInfo();
			QDomElement _buttonElement = _buttonNode.toElement();
			_buttonInfo->m_buttonName = _buttonElement.attribute("name");
			_buttonInfo->m_pageName = _buttonElement.attribute("page");
			_buttonInfo->m_width = _buttonElement.attribute("width").toInt();
			_buttonInfo->m_height = _buttonElement.attribute("height").toInt();
			_buttonInfo->m_posX = _buttonElement.attribute("posX").toInt();
			_buttonInfo->m_posY = _buttonElement.attribute("posY").toInt();

			if (_buttonElement.hasAttribute("message"))
				_buttonInfo->m_message = _buttonElement.attribute("message");
			m_buttonInfos.push_back(_buttonInfo);
		}
	}
}

void ButtonInfoManager::printManagerInfo()
{
	for (int i = 0; i < m_buttonInfos.size(); i++)
	{
		qDebug() << "manager::buttonName:" << m_buttonInfos[i]->m_buttonName;
		qDebug() << "manager::pageName:" << m_buttonInfos[i]->m_pageName;
		qDebug() << "manager::message:" << m_buttonInfos[i]->m_message;
	}

	qDebug() << "=======================";
}
