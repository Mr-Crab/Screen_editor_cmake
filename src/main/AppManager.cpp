#include "AppManager.h"
#include "ToolTipWidget.h"
#include "ButtonController.h"
#include <QDebug>

AppManager* AppManager::getInstance()
{
	static AppManager instance;
	return &instance;
}

AppManager::AppManager()
	:m_mainWindow(nullptr)
	, m_listWidget(nullptr)
	, m_toolTipWidget(nullptr)
	, m_pageWidget(nullptr)
	, m_outPutPath("")
{
	m_buttonController = new ButtonController();
}

AppManager::~AppManager()
{
}
