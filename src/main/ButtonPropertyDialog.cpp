#include "ButtonPropertyDialog.h"
#include <QIntValidator>
#include <QMessageBox>
#include <QCloseEvent>
#include <QDropEvent>
#include <QDragEnterEvent>
#include <QMimeData>
#include "ButtonInfoManager.h"
#include "AppManager.h"
#include "ButtonController.h"
#include "PageWidget.h"
#include "ScreenEditor.h"

ButtonPropertyDialog* ButtonPropertyDialog::getInstance()
{
	static ButtonPropertyDialog instance;
	return &instance;
}

ButtonPropertyDialog::ButtonPropertyDialog(QWidget *parent)
	: QDialog(parent)
	,m_oldButtonInfo(nullptr)
	,m_newButtonInfo(nullptr)
	,m_buttonType(CREATE)
{
	ui.setupUi(this);
	this->setWindowFlags(Qt::WindowStaysOnTopHint);

	QIntValidator* _validatorX = new QIntValidator(0, 1920);
	QIntValidator* _validatorY = new QIntValidator(0, 1080);
	ui.lineEdit_posX->setValidator(_validatorX);
	ui.lineEdit_width->setValidator(_validatorX);
	ui.lineEdit_posY->setValidator(_validatorY);
	ui.lineEdit_height->setValidator(_validatorY);

	m_oldButtonInfo = new ButtonInfo();
	m_newButtonInfo = new ButtonInfo();
	connect(ui.pushButton, &QPushButton::clicked, this, &ButtonPropertyDialog::onOKButtonClicked);
	connect(ui.pushButton_delete, &QPushButton::clicked, this, &ButtonPropertyDialog::onDeleteButtonClicked);

	this->setAcceptDrops(true);
	ui.lineEdit_buttonName->setAcceptDrops(false);
	ui.lineEdit_messsage->setAcceptDrops(false);
	ui.lineEdit_page->setAcceptDrops(false);
	ui.lineEdit_posX->setAcceptDrops(false);
	ui.lineEdit_posY->setAcceptDrops(false);
	ui.lineEdit_width->setAcceptDrops(false);
	ui.lineEdit_height->setAcceptDrops(false);
}

ButtonPropertyDialog::~ButtonPropertyDialog()
{
	if (m_oldButtonInfo)
	{
		delete m_oldButtonInfo;
		m_oldButtonInfo = nullptr;
	}
	if (m_newButtonInfo)
	{
		delete m_newButtonInfo;
		m_newButtonInfo = nullptr;
	}
}

void ButtonPropertyDialog::setPropertyValue(const QString& buttonName, const QString& pageName, const QString& message, int posX, int posY, int width, int height)
{
	ui.lineEdit_buttonName->setText(buttonName);
	ui.lineEdit_page->setText(pageName);
	ui.lineEdit_messsage->setText(message);
	ui.lineEdit_width->setText(QString::number(width));
	ui.lineEdit_height->setText(QString::number(height));
	ui.lineEdit_posX->setText(QString::number(posX));
	ui.lineEdit_posY->setText(QString::number(posY));

	m_oldButtonInfo->m_buttonName = buttonName;
	m_oldButtonInfo->m_pageName = pageName;
	m_oldButtonInfo->m_pageName = message;
	m_oldButtonInfo->m_posX = posX;
	m_oldButtonInfo->m_posY = posY;
	m_oldButtonInfo->m_width = width;
	m_oldButtonInfo->m_height = height;
}

void ButtonPropertyDialog::setButtonType(ButtonType type)
{
	m_buttonType = type;
}

ButtonType ButtonPropertyDialog::getButtonType()
{
	return m_buttonType;
}

void ButtonPropertyDialog::closeEvent(QCloseEvent *e)
{
	if (m_buttonType == CREATE)
		AppManager::getInstance()->m_pageWidget->deleteTempItem();
}

void ButtonPropertyDialog::dragEnterEvent(QDragEnterEvent *event)
{
	event->acceptProposedAction();
}

void ButtonPropertyDialog::dropEvent(QDropEvent *event)
{
	ui.lineEdit_page->setText(event->mimeData()->text());
	event->acceptProposedAction();
}

void ButtonPropertyDialog::onOKButtonClicked()
{
	QString _buttonName = ui.lineEdit_buttonName->text();
	QString _pageName = ui.lineEdit_page->text();

	if (_buttonName == "")
	{
		QMessageBox::warning(this,tr("提示"),tr("按钮名称不能为空"));
		return;
	}
	if (_pageName == "")
	{
		QMessageBox::warning(this, tr("提示"), tr("跳转页不能为空"));
		return;
	}
	if (m_buttonType == CREATE && AppManager::getInstance()->m_buttonController->getButtonInfoByButtonName(_buttonName) != nullptr)
	{
		QMessageBox::warning(this, tr("提示"), tr("按钮名称已存在"));
		return;
	}

	m_newButtonInfo->m_buttonName = ui.lineEdit_buttonName->text();
	m_newButtonInfo->m_pageName = ui.lineEdit_page->text();
	m_newButtonInfo->m_message = ui.lineEdit_messsage->text();
	m_newButtonInfo->m_posX = ui.lineEdit_posX->text().toInt();
	m_newButtonInfo->m_posY = ui.lineEdit_posY->text().toInt();
	m_newButtonInfo->m_width = ui.lineEdit_width->text().toInt();
	m_newButtonInfo->m_height = ui.lineEdit_height->text().toInt();

	if (m_buttonType == CREATE)
	{
		AppManager::getInstance()->m_buttonController->creatButton(m_newButtonInfo);
	}
	else
	{
		AppManager::getInstance()->m_buttonController->changeButton(m_oldButtonInfo->m_buttonName, m_newButtonInfo);
	}

	close();
}

void ButtonPropertyDialog::onDeleteButtonClicked()
{
	if (m_buttonType == CREATE)
	{
		AppManager::getInstance()->m_pageWidget->deleteTempItem();
	}
	else
	{
		AppManager::getInstance()->m_buttonController->deleteButton(m_oldButtonInfo->m_buttonName);
	}
	close();
}

