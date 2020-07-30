#pragma once

#include <QDialog>
#include "config.h"
#include "ui_ButtonPropertyDialog.h"

# pragma execution_character_set("utf-8") 
class ButtonInfo;
class QCloseEvent;
class QDropEvent;
class QDragEnterEvent;
class ButtonPropertyDialog : public QDialog
{
	Q_OBJECT

public:
	static ButtonPropertyDialog* getInstance();
	~ButtonPropertyDialog();
private:
	ButtonPropertyDialog(QWidget *parent = Q_NULLPTR);

public:
	void setPropertyValue(const QString& buttonName, const QString& pageName, const QString& message, int posX, int posY, int width, int height);
	void setButtonType(ButtonType type);
	ButtonType getButtonType();

protected:
	virtual void closeEvent(QCloseEvent *e);
	virtual void dragEnterEvent(QDragEnterEvent *event);
	virtual void dropEvent(QDropEvent *event);

private:
	Ui::ButtonPropertyDialog ui;
	ButtonInfo* m_oldButtonInfo;
	ButtonInfo* m_newButtonInfo;
	ButtonType m_buttonType;

	public slots:
	void onOKButtonClicked();
	void onDeleteButtonClicked();
};
