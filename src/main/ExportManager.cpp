#include "ExportManager.h"
#include <QDomDocument>
#include <QApplication>
#include <QTextStream>
#include "PageItem.h"
#include "config.h"
#include "AppManager.h"

ExportManager::ExportManager()
	:m_file(nullptr)
{
}

ExportManager::~ExportManager()
{
}

bool ExportManager::exportXml(const QVector<PageItem*>& pageItems, const QVector<ButtonInfo*>& buttonInfos)
{
	QString _filePath = AppManager::getInstance()->m_outPutPath + "/screen_info.xml";
	m_file = new QFile(_filePath);

	if (!m_file->open(QFile::WriteOnly | QFile::Truncate))
	{
		delete m_file;
		m_file = nullptr;
		return false;
	}

	QDomDocument doc;

	QDomProcessingInstruction instruction = doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
	doc.appendChild(instruction);

	//root
	QDomElement _rootNode = doc.createElement("screen");
	doc.appendChild(_rootNode);

	//pages
	QDomElement _pagesNode = doc.createElement("pages");
	_rootNode.appendChild(_pagesNode);

	for (int i = 0; i < pageItems.size(); i++)
	{
		PageItem* _tempPage = pageItems[i];
		QDomElement pageNode;
		createNodeByPageItem(doc, _tempPage, pageNode);

		_pagesNode.appendChild(pageNode);
	}

	//buttons
	QDomElement _buttonsNode = doc.createElement("buttons");
	_rootNode.appendChild(_buttonsNode);

	for (int j = 0; j < buttonInfos.size(); j++)
	{
		ButtonInfo* _tempInfo = buttonInfos[j];
		QDomElement buttonNode;
		createNodeByButtonInfo(doc, _tempInfo, buttonNode);

		_buttonsNode.appendChild(buttonNode);
	}

	QTextStream out_stream(m_file);
	doc.save(out_stream, 4); //缩进4格
	m_file->close();
	delete m_file;
	m_file = nullptr;

	return true;
}

void ExportManager::createNodeByPageItem(QDomDocument& doc, PageItem* item, QDomElement& pageNode)
{
	pageNode = doc.createElement("page");
	QString _pageName = item->getPageName();
	pageNode.setAttribute("name", _pageName);

	for (int i = 0; i < item->getNumButtonNames(); i++)
	{
		QString _buttonName = item->getButtonName(i);
		QDomElement _itemNode = doc.createElement("item");
		_itemNode.setAttribute("button", _buttonName);
		pageNode.appendChild(_itemNode);
	}
}

void ExportManager::createNodeByButtonInfo(QDomDocument& doc, ButtonInfo* info, QDomElement& buttonNode)
{
	buttonNode = doc.createElement("button");
	buttonNode.setAttribute("name", info->m_buttonName);
	buttonNode.setAttribute("page", info->m_pageName);
	buttonNode.setAttribute("posX", QString::number(info->m_posX));
	buttonNode.setAttribute("posY", QString::number(info->m_posY));
	buttonNode.setAttribute("width", QString::number(info->m_width));
	buttonNode.setAttribute("height", QString::number(info->m_height));

	if(info->m_message != "")
		buttonNode.setAttribute("message", info->m_message);
}

void ExportManager::openXml(const QString& xmlDirPath, QDomElement &pagesNode, QDomElement& buttonsNode)
{
	QFile file(xmlDirPath + "/screen_info.xml");
	if (!file.open(QFile::ReadOnly))
		return;

	QDomDocument doc;
	if (!doc.setContent(&file))
	{
		file.close();
		return;
	}

	file.close();

	QDomElement _rootNode = doc.documentElement();
	pagesNode = _rootNode.firstChildElement("pages");
	buttonsNode = _rootNode.firstChildElement("buttons");
}

bool ExportManager::createSourceFile(const QString& fileName, const QString& id)
{
	bool _bEntity = createSourceByType(fileName, id, ENTITY);
	if (!_bEntity)
		return false;

	bool _bNode = createSourceByType(fileName, id, NODE);
	if (!_bNode)
		return false;

	bool _bTitleH = createSourceByType(fileName, id, TITLE_H);
	if (!_bTitleH)
		return false;

	bool _bPro = createSourceByType(fileName, id, PROP);
	if (!_bPro)
		return false;

	return true;
}

bool ExportManager::createSourceByType(const QString& fileName, const QString& id, sourceType type)
{
	QString _suffix = "";
	switch (type)
	{
	case ENTITY:
		_suffix = ".entity";
		break;
	case NODE:
		_suffix = ".node";
		break;
	case TITLE_H:
		_suffix = ".h";
		break;
	case PROP:
		_suffix = ".prop";
		break;
	default:
		break;
	}
	QString _typePath = ":/source/Resources/template" + _suffix;
	QString _saveEntityPath = AppManager::getInstance()->m_outPutPath + "/" + fileName + _suffix;
	QFile _file(_typePath);

	if (!_file.open(QIODevice::ReadOnly))
		return false;

	QString _entityText = _file.readAll();
	_entityText = _entityText.replace("%ENTITYNAME%", fileName);
	if (type == NODE)
		_entityText = _entityText.replace("%ID%", id);

	_file.close();

	QFile _saveFile(_saveEntityPath);
	if (!_saveFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
		return false;

	_saveFile.write(_entityText.toLocal8Bit());
	_saveFile.close();
	return true;
}

