#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSoundEffect>
#include <QTimer>

#include "gamemodel.h"
#include "aboutdialog.h"
#include "customdialog.h"
#include "successdialog.h"
#include "recorddialog.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class GameTimers{
public:
    static const int GAME_FPS = 10;
    static const int CLOCK_INTERVAL = 1000;

public:
    QTimer interval;
    QTimer clock;
};

class GameAudio{
public:
    QSoundEffect click;
    QSoundEffect failure;
    QSoundEffect success;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    static const int MARGIN_X = 12;
    static const int MARGIN_Y = 78;

private:
    int screenWidth;
    int screenHeight;
    int elapseTime;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    MainGame * pGame;
    AboutDialog *pAboutDialog;
    CustomDialog *pCustomDialog;
    RecordDialog *pRecordDialog;
    SuccessDialog *pSuccessDialog;

private:
    GameTimers timers;
    GameAudio audio;

private:
    void setGameEasyLevel();
    void setGameMediumLevel();
    void setGameHardLevel();
    void setGameCustomLevel();
    void resizeWindow();

private:
    void loadAudio();
    void mainInterval();
    void clockCallback();
    void setInterval();
    void connectTimer();
    void connectAction();
    void startTimer();

private:
    void gameRestart();
    void gamePause();
    void gameoverSuccess();
    void gameAutoPause();
    void gameAutoUncoverBlocks();
    void updateGameInfo();

private:
    void mousePressEvent(QMouseEvent *pMouseevent);
    void keyPressEvent(QKeyEvent *pKeyevent);


public:
    void setGame(MainGame * pGame);
    void initialize();
};
#endif // MAINWINDOW_H
