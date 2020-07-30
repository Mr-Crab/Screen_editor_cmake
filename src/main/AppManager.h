#pragma once

#include <QObject>

class ScreenEditor;
class PageListWidget;
class ToolTipWidget;
class PageWidget;
class ButtonPropertyDialog;
class ButtonController;

class AppManager 
{
public:
	static AppManager* getInstance();
	~AppManager();

private:
	AppManager();

public:
	ScreenEditor* m_mainWindow;
	PageListWidget* m_listWidget;
	PageWidget* m_pageWidget;
	ToolTipWidget* m_toolTipWidget;
	ButtonController* m_buttonController;

	QString m_outPutPath;
};
