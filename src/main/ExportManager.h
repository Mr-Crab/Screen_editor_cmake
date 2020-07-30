#pragma once

#include <QString>
#include <QVector>
#include <QFile>
#include <QDomElement>
#include "config.h"

class ButtonInfo;
class PageItem;
class ExportManager
{
public:
	ExportManager();
	~ExportManager();

	bool exportXml(const QVector<PageItem*>& pageItems, const QVector<ButtonInfo*>& buttonInfos);
	void createNodeByPageItem(QDomDocument& doc, PageItem* item, QDomElement& pageNode);
	void createNodeByButtonInfo(QDomDocument& doc, ButtonInfo* info, QDomElement& buttonNode);

	void openXml(const QString& xmlDirPath,QDomElement &pagesNode,QDomElement& buttonsNode);


	//生成文件
	bool createSourceFile(const QString& fileName, const QString& id);

private:
	bool createSourceByType(const QString& fileName, const QString& id, sourceType type);

private:
	QFile* m_file;
};
