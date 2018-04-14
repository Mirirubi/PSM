#include "Clasificador.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	CClasificador w;
	w.show();
	return a.exec();
}
