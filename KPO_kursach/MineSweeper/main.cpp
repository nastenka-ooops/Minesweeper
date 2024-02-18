#include "mainwindow.h"

#include <QApplication>
void setRandomSeed(){
    srand(time(NULL));
}
int main(int argc, char *argv[])
{
    setRandomSeed();
    QApplication a(argc, argv);

    MainGame game;
    MainWindow window;

    window.setGame(&game);
    window.initialize();
    window.show();

    return a.exec();
}
