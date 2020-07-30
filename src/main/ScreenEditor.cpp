#include "ScreenEditor.h"
#include <QIcon>
#include <QDockWidget>
#include <QMessageBox>
#include "AppManager.h"
#include "ToolTipWidget.h"
#include "ButtonController.h"
#include "ExportManager.h"
#include <QFileDialog>
#include <QScrollBar>
#include "ExportInfoWidget.h"
#include "ZipArchive.h"
#include <QTime>
#include <QDateTime>
#include "PageItem.h"

ScreenEditor::ScreenEditor(QWidget *parent)
	: QMainWindow(parent)
	, m_pictureBtn(nullptr)
	,m_btnBtn(nullptr)
	, m_importBtn(nullptr)
	, m_exportBtn(nullptr)
	,m_statuInfo(nullptr)
{
	m_exportManager = new ExportManager();

	ui.setupUi(this);
	AppManager::getInstance()->m_mainWindow = this;
	AppManager::getInstance()->m_listWidget = ui.listPage;
	m_toolTipWidget = new ToolTipWidget();
	m_toolTipWidget->setWindowFlag(Qt::FramelessWindowHint);
	AppManager::getInstance()->m_toolTipWidget = m_toolTipWidget;
	AppManager::getInstance()->m_pageWidget = ui.page;
	AppManager::getInstance()->m_buttonController->bindObserver(ui.listPage);
	AppManager::getInstance()->m_buttonController->bindObserver(ui.page);

	m_exportInfoWidget = new ExportInfoWidget(this);
	initToolBar();
}

void ScreenEditor::setStateInfo(const QString& info)
{
	m_statuInfo->setText(info);
}

void ScreenEditor::setPageName(const QString& info)
{
	m_pageNameInfo->setText(info);
}

bool ScreenEditor::isButtonChecked()
{
	return m_btnBtn->isChecked();
}

bool ScreenEditor::isToolTipChecked()
{
	return m_tooltipBtn->isChecked();
}

void ScreenEditor::changeScrollValue(int width, int height)
{
	int _width = ui.scrollArea->horizontalScrollBar()->value();
	int _height = ui.scrollArea->verticalScrollBar()->value();
	ui.scrollArea->horizontalScrollBar()->setValue(_width - width);
	ui.scrollArea->verticalScrollBar()->setValue(_height - height);
}

void ScreenEditor::keyReleaseEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_1)
	{
		ui.listPage->printPageInfo();
		ui.page->printPageWidgetInfo();
		AppManager::getInstance()->m_buttonController->printManagerInfo();
	}
	else if (event->key() == Qt::Key_2)
	{
		AppManager::getInstance()->m_buttonController->printManagerInfo();
	}
	else if (event->key() == Qt::Key_3)
	{
		ui.page->printPageWidgetInfo();
	}
	else if (event->key() == Qt::Key_4)
	{
		ui.listPage->printPageInfo();
	}
}

void ScreenEditor::initToolBar()
{
	m_pictureBtn = new QToolButton();
	m_pictureBtn->setText(tr("添加页"));
	m_pictureBtn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
	m_pictureBtn->setIcon(QIcon(":/Resources/picture.png"));
	ui.toolBar->addWidget(m_pictureBtn);


	m_btnBtn = new QToolButton();
	m_btnBtn->setText(tr("按钮"));
	m_btnBtn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
	m_btnBtn->setIcon(QIcon(":/toobar/Resources/button.png"));
	m_btnBtn->setCheckable(1);
	m_btnBtn->setChecked(1);
	ui.toolBar->addWidget(m_btnBtn);

	m_tooltipBtn = new QToolButton();
	m_tooltipBtn->setText(tr("提示"));
	m_tooltipBtn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
	m_tooltipBtn->setIcon(QIcon(":/toobar/Resources/tooltip.png"));
	m_tooltipBtn->setCheckable(1);
	ui.toolBar->addWidget(m_tooltipBtn);

	m_pageBtn = new QToolButton();
	m_pageBtn->setText(tr("页"));
	m_pageBtn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
	m_pageBtn->setIcon(QIcon(":/toobar/Resources/page.png"));
	ui.toolBar->addWidget(m_pageBtn);

	m_clearBtn = new QToolButton();
	m_clearBtn->setText(tr("清空"));
	m_clearBtn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
	m_clearBtn->setIcon(QIcon(":/toobar/Resources/clear.png"));
	ui.toolBar->addWidget(m_clearBtn);

	m_deleteBtn = new QToolButton();
	m_deleteBtn->setText(tr("清除资源"));
	m_deleteBtn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
	m_deleteBtn->setIcon(QIcon(":/toobar/Resources/clear.png"));
	ui.toolBar->addWidget(m_deleteBtn);

	ui.toolBar->addSeparator();
	m_importBtn = new QToolButton();
	m_importBtn->setText(tr("导入"));
	m_importBtn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
	m_importBtn->setIcon(QIcon(":/toobar/Resources/import.png"));
	ui.toolBar->addWidget(m_importBtn);

	m_saveBtn = new QToolButton();
	m_saveBtn->setText(tr("保存"));
	m_saveBtn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
	m_saveBtn->setIcon(QIcon(":/toobar/Resources/save.png"));
	ui.toolBar->addWidget(m_saveBtn);

	m_exportBtn = new QToolButton();
	m_exportBtn->setText(tr("导出"));
	m_exportBtn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
	m_exportBtn->setIcon(QIcon(":/toobar/Resources/export.png"));
	ui.toolBar->addWidget(m_exportBtn);

	m_statuInfo = new QLabel();
	this->statusBar()->addWidget(m_statuInfo);

	m_pageNameInfo = new QLabel();
	this->statusBar()->addPermanentWidget(m_pageNameInfo);

	connect(m_pictureBtn, &QToolButton::clicked, ui.listPage, &PageListWidget::onAddPageItem);
	connect(m_pageBtn, &QToolButton::clicked, this, &ScreenEditor::onResetDockWidget);
	connect(m_importBtn, &QToolButton::clicked, this, &ScreenEditor::onimportXml);
	connect(m_saveBtn, &QToolButton::clicked, this, &ScreenEditor::onExportXml);
	connect(m_clearBtn, &QToolButton::clicked, this, &ScreenEditor::onClear);
	connect(m_deleteBtn, &QToolButton::clicked, this, &ScreenEditor::onDelete);
	connect(m_exportBtn, &QToolButton::clicked, this, &ScreenEditor::onCreateSourceFile);
}

void ScreenEditor::onResetDockWidget()
{
	if (ui.dockPage->isHidden())
		ui.dockPage->show();
}

void ScreenEditor::onExportXml()
{
	bool _result = m_exportManager->exportXml(ui.listPage->getPageItems(), AppManager::getInstance()->m_buttonController->getButtonInfos());
	if (_result)
		QMessageBox::information(this, tr("提示"), tr("保存成功！"),QMessageBox::NoButton);
	else
		QMessageBox::information(this, tr("提示"), tr("保存失败！"), QMessageBox::NoButton);
}

void ScreenEditor::onimportXml()
{
	if (AppManager::getInstance()->m_outPutPath == "")
		AppManager::getInstance()->m_outPutPath = QApplication::applicationDirPath();

	QString _dir = QFileDialog::getExistingDirectory(this, tr("请选择要打开的xml所在路径"), AppManager::getInstance()->m_outPutPath);
	if (_dir == "")
		return;

	AppManager::getInstance()->m_outPutPath = _dir;
	AppManager::getInstance()->m_buttonController->clearContent();
	ui.listPage->clearContetn();
	ui.page->clearContent();

	QDomElement _pagesNode;
	QDomElement _buttonsNode;
	m_exportManager->openXml(_dir,_pagesNode,_buttonsNode);

	ui.listPage->addPagesByDocNode(_pagesNode);
	AppManager::getInstance()->m_buttonController->addButtonInfosByDocNode(_buttonsNode);
}

void ScreenEditor::onCreateSourceFile()
{
	int _iTime = QDateTime::currentSecsSinceEpoch();
	qsrand(QTime(0, 0, 0).msecsTo(QTime::currentTime()));
	int id = qrand();
	m_exportInfoWidget->setID(QString::number(_iTime) + QString::number(id));

	if (m_exportInfoWidget->exec() != QDialog::Accepted)
		return;

	bool _result = m_exportManager->createSourceFile(m_exportInfoWidget->getEntityName(), m_exportInfoWidget->getID());
	if (!_result)
	{
		QMessageBox::information(this, tr("提示"), tr("创建资源文件出错！"));
		return;
	}

	bool _bZip = ZipArchive::CreateFromFolder(AppManager::getInstance()->m_outPutPath, m_exportInfoWidget->getEntityName());
	if (!_bZip)
	{
		QMessageBox::information(this, tr("提示"), tr("压缩文件失败！"));
		return;
	}

	QMessageBox::information(this, tr("提示"), tr("导出压缩文件成功！"));
}

void ScreenEditor::onClear()
{
	if (ui.listPage->getNumPageItems() == 0)
		return;

	AppManager::getInstance()->m_buttonController->clearContent();
	ui.listPage->clearContetn();
	ui.page->clearContent();
}

void ScreenEditor::onDelete()
{
	if (ui.listPage->getNumPageItems() == 0)
		return;

	ZipArchive::ClearUnUsedFile(AppManager::getInstance()->m_outPutPath);
	AppManager::getInstance()->m_buttonController->clearContent();
	ui.listPage->clearContetn();
	ui.page->clearContent();
}
