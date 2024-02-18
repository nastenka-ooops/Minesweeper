#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStyle>
#include <QScreen>
#include <QMouseEvent>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pAboutDialog = new AboutDialog(this);
    pCustomDialog = new CustomDialog(this);
    pSuccessDialog = new SuccessDialog(this);
    pRecordDialog = new RecordDialog(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete pAboutDialog;
    delete pCustomDialog;
    delete pSuccessDialog;
    delete pRecordDialog;
}
void MainWindow::setGame(MainGame * pGame)
{
    this->pGame = pGame;
    ui->pGraphics->setGame(pGame);
}

void MainWindow::initialize()
{
    loadAudio();
    setInterval();
    connectTimer();
    connectAction();
    startTimer();
    setGameEasyLevel();
    gameRestart();
}

void MainWindow::startTimer(){
    timers.interval.start();
    timers.clock.start();
}
void MainWindow::loadAudio()
{    
    audio.click.setSource(QUrl("qrc:/Audio/click.wav"));
    audio.failure.setSource(QUrl("qrc:/Audio/failure.wav"));
    audio.success.setSource(QUrl("qrc:/Audio/success.wav"));
}

void MainWindow::setInterval(){
    timers.interval.setInterval(1000/GameTimers::GAME_FPS);
    timers.clock.setInterval(GameTimers::CLOCK_INTERVAL);
};

void MainWindow::connectTimer(){
    connect(&timers.interval, &QTimer::timeout, this, &MainWindow::mainInterval);
    connect(&timers.clock, &QTimer::timeout, this, &MainWindow::clockCallback);
};
void MainWindow::clockCallback(){
    if(pGame->getStatus()==STATUS_MAINLOOP){
        elapseTime +=1;
    }
}
void MainWindow::connectAction(){
    connect(ui->pActionEasyLevel, &QAction::triggered, this, &MainWindow::setGameEasyLevel);
    connect(ui->pActionMediumLevel, &QAction::triggered, this, &MainWindow::setGameMediumLevel);
    connect(ui->pActionHardLevel, &QAction::triggered, this, &MainWindow::setGameHardLevel);
    connect(ui->pActionCustomLevel, &QAction::triggered, this, &MainWindow::setGameCustomLevel);
    connect(ui->pActionPause, &QAction::triggered, this, &MainWindow::gamePause);
    connect(ui->pActionRestart, &QAction::triggered, this, &MainWindow::gameRestart);
    connect(ui->pActionAbout, &QAction::triggered, pAboutDialog, &AboutDialog::exec);
    connect(ui->pActionRecord, &QAction::triggered, pRecordDialog, &RecordDialog::showDialog);
};

void MainWindow::setGameEasyLevel()
{
  pGame->setEasyLevel();
  resizeWindow();
  gameRestart();
}

void MainWindow::setGameMediumLevel()
{
  pGame->setMediumLevel();
  resizeWindow();
  gameRestart();
}

void MainWindow::setGameHardLevel()
{
  pGame->setHardLevel();
  resizeWindow();
  gameRestart();
}
void MainWindow::setGameCustomLevel()
{
    pCustomDialog->showDialog();

    if(pCustomDialog->getIsNeedSet()){
        int tableRows = pCustomDialog->getInputRows();
        int tableCols = pCustomDialog->getInputCols();
        int mineInitCount = pCustomDialog->getInputMineCount();
    pGame->setCustomLevel(tableRows, tableCols, mineInitCount);
    resizeWindow();
    gameRestart();
 }
}
void MainWindow::gameRestart()
{
    audio.click.stop();
    audio.click.play();

    pGame->restart();
    pGame->addMines();
    pGame->addNumbers();
    elapseTime=0;
}
void MainWindow::resizeWindow()
{
  screenWidth = pGame->getTableRows() * GameBlock::SIZE + MARGIN_X + MARGIN_X;
  screenHeight = pGame->getTableCols() * GameBlock::SIZE + MARGIN_X + MARGIN_Y;

  setFixedSize(screenWidth, screenHeight);
  setGeometry(
        QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, size(),
                            QGuiApplication::primaryScreen()->geometry()));

}

void MainWindow::mainInterval(){
    updateGameInfo();

  if (pGame->getStatus()==STATUS_MAINLOOP){
       gameAutoPause();
       gameoverSuccess();
       gameAutoUncoverBlocks();
  }
  ui->pGraphics->update();
}

void MainWindow::updateGameInfo()
{
    QString timeInfo=QString("TIME: %1").arg(elapseTime);
    QString mineInfo = QString("MINE: %1").arg(pGame->getRemainFlagCount());

    if(pGame->getStatus()==STATUS_PAUSE){
        timeInfo.append("(PAUSE)");
    }
    if(pGame->getStatus()==STATUS_FAILURE){
        mineInfo.append(" BOOM!");
    }
    if(pGame->getStatus()==STATUS_SUCCESS){
        mineInfo.append(" SUCCESS!");
    }
    ui->pTimeLabel->setText(timeInfo);
    ui->pMineLabel->setText(mineInfo);
}
void MainWindow::gamePause(){
    pGame->setPause();
}
void MainWindow::gameAutoPause(){
    if(isMinimized()){
        pGame->setPause();
    }
}
void MainWindow::gameAutoUncoverBlocks(){
    pGame->autoUncoverBlocks();
}
void MainWindow::gameoverSuccess(){
    if(pGame->isSuccess()){
        audio.success.stop();
        audio.success.play();
        if(pGame->getLevel()!=LEVEL_CUSTOM){
            pSuccessDialog->showDialog();
            if(pSuccessDialog->getIsNeedSave()){
                pRecordDialog->addRecord(pSuccessDialog->getInputName(), elapseTime, pGame->getLevel());
            }
        }
    }
}
void MainWindow::mousePressEvent(QMouseEvent *pMouseEvent){
    if(pMouseEvent->button() ){
        if(pGame->getStatus()==STATUS_MAINLOOP){
            QPoint mouse = pMouseEvent->pos();

            int x = ((mouse.x()-MARGIN_X)/GameBlock::SIZE);
            int y = ((mouse.y()-MARGIN_Y)/GameBlock::SIZE);

            if(pMouseEvent->button()==Qt::LeftButton && pGame->isLeftButtonClicked(x,y)){
                if(pGame->isFailure(x,y)){
                    audio.failure.stop();
                    audio.failure.play();
                }else{
                    audio.click.stop();
                    audio.click.play();
                }
            } else if(pMouseEvent->button()==Qt::RightButton && pGame->isRightButtonClicked(x,y)){
                audio.click.stop();
                audio.click.play();
            }
        } else if (pGame->getStatus()==STATUS_PAUSE){
            audio.click.stop();
            audio.click.play();
            pGame->setResume();
        }else{
            gameRestart();
        }
    }
}
void MainWindow::keyPressEvent(QKeyEvent *pKeyEvent){
    if (pKeyEvent->key()==Qt::Key_R){
        gameRestart();
    }
    if (pKeyEvent->key()==Qt::Key_P){
        gamePause();
    }
}

