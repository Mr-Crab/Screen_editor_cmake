#pragma once

#include <QtWidgets/QMainWindow>
#include <QToolButton>
#include "ui_ScreenEditor.h"
#include <QLabel>
#include <QKeyEvent>

# pragma execution_character_set("utf-8") 

class ExportManager;
class ToolTipWidget;
class ExportInfoWidget;
class ScreenEditor : public QMainWindow
{
	Q_OBJECT

public:
	ScreenEditor(QWidget *parent = Q_NULLPTR);

	void setStateInfo(const QString& info);
	void setPageName(const QString& info);
	bool isButtonChecked();
	bool isToolTipChecked();

	void changeScrollValue(int width, int height);

protected:
	virtual void keyReleaseEvent(QKeyEvent *event);

private:
	void initToolBar();

private:
	Ui::ScreenEditorClass ui;
	QToolButton* m_pictureBtn;
	QToolButton* m_btnBtn;
	QToolButton* m_tooltipBtn;
	QToolButton* m_clearBtn;
	QToolButton* m_deleteBtn;
	QToolButton* m_saveBtn;
	QToolButton* m_exportBtn;
	QToolButton* m_importBtn;
	QToolButton* m_pageBtn;
	ToolTipWidget* m_toolTipWidget;
	QLabel* m_statuInfo;
	QLabel* m_pageNameInfo;

	ExportInfoWidget* m_exportInfoWidget;
	ExportManager* m_exportManager;

	public slots:
	void onResetDockWidget();
	void onExportXml();
	void onimportXml();
	void onCreateSourceFile();
	void onClear();
	void onDelete();
};
