#pragma once

#include <QWidget>
#include <QLabel>

class ToolTipWidget : public QWidget
{
	Q_OBJECT

public:
	ToolTipWidget(QWidget *parent = nullptr);
	~ToolTipWidget();

	void setToolTipImage(QString imagePath);
	void setImageName(QString iamgeName);

private:
	QWidget* m_widget;
	QLabel* m_label;
};
