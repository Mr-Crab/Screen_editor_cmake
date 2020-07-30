#pragma once

#include <QWidget>
#include <QGridLayout>
#include <QVector>

class ButtonListWidget : public QWidget
{
	Q_OBJECT

public:
	ButtonListWidget(QWidget *parent);
	~ButtonListWidget();

	void addButtonItem(const QString& buttonName, const QString& pageName, const QString& message, int posx, int posy, int width, int height);

private:
	QGridLayout* m_grideLayout;
};
