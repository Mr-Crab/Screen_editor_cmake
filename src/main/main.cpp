#include "ScreenEditor.h"
#include <QtWidgets/QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{

	QApplication a(argc, argv);

	ScreenEditor w;
	w.show();
	return a.exec();
}
