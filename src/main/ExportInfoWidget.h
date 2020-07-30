#pragma once

#include <QDialog>
#include "ui_ExportInfoWidget.h"

class ExportInfoWidget : public QDialog
{
	Q_OBJECT

public:
	ExportInfoWidget(QWidget *parent = Q_NULLPTR);
	~ExportInfoWidget();

	QString getEntityName();
	QString getID();
	void setID(const QString& text);

	public slots:
	void onOkButtonClicked();
	void onCancleButtonClicked();

private:
	Ui::ExportInfoWidget ui;
	QString m_id;
};
