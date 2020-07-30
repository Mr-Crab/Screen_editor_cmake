#include "ExportInfoWidget.h"
#include <QTime>

ExportInfoWidget::ExportInfoWidget(QWidget *parent)
	: QDialog(parent)
	, m_id("")
{
	ui.setupUi(this);

	connect(ui.pushButton_OK, &QPushButton::clicked, this, &ExportInfoWidget::onOkButtonClicked);
	connect(ui.pushButton_Cancel, &QPushButton::clicked, this, &ExportInfoWidget::onCancleButtonClicked);
}

ExportInfoWidget::~ExportInfoWidget()
{
}

QString ExportInfoWidget::getEntityName()
{
	return ui.lineEdit_entityName->text();
}

QString ExportInfoWidget::getID()
{
	return m_id;
}

void ExportInfoWidget::setID(const QString& text)
{
	m_id = text;
}

void ExportInfoWidget::onOkButtonClicked()
{
	if (getEntityName() == "" || getID() == "")
		return;

	this->accept();
	this->close();
}

void ExportInfoWidget::onCancleButtonClicked()
{
	this->reject();
	this->close();
}
