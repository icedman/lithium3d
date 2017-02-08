
#include "gameapp.h"

#include <QApplication>

int main(int argc, char** argv)
{
	QApplication a(argc, argv);

	GameApp app(0);
	app.show();

	app.GameInit();

	// fprintf(stdout, "run!\n");
    return a.exec();
}

