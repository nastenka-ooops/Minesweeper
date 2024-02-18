#include "gamemodel.h"
void MainGame::setEasyLevel()
{
    level = LEVEL_EASY;
    tableRows = GameEasyLevel::ROWS;
    tableCols = GameEasyLevel::COLS;
    mineInitCount = GameEasyLevel::MINE_INIT_COUNT;
}

void MainGame::setMediumLevel()
{
    level = LEVEL_MEDIUM;
    tableRows = GameMediumLevel::ROWS;
    tableCols = GameMediumLevel::COLS;
    mineInitCount = GameMediumLevel::MINE_INIT_COUNT;
}

void MainGame::setHardLevel()
{
    level = LEVEL_HARD;
    tableRows = GameHardLevel::ROWS;
    tableCols = GameHardLevel::COLS;
    mineInitCount = GameHardLevel::MINE_INIT_COUNT;
}


void MainGame::setCustomLevel(int rows, int cols, int mineCount)
{
    level = LEVEL_CUSTOM;
    tableRows = rows;
    tableCols = cols;
    mineInitCount = mineCount;
}

int MainGame::getTableCols()
{
    return tableCols;
}

int MainGame::getTableRows()
{
    return tableRows;
}

void MainGame::setPause()
{
    if (status == STATUS_MAINLOOP)
    {
        status = STATUS_PAUSE;
    }
}

void MainGame::setResume()
{
    if (status == STATUS_PAUSE)
    {
        status = STATUS_MAINLOOP;
    }
}

void MainGame::restart()
{
    for (int i = 0; i < tableRows; ++i)
    {
        for (int j = 0; j < tableCols; ++j)
        {
            gameMap[i][j].type = BLOCK_EMPTY;
            gameMap[i][j].number = 0;
            gameMap[i][j].isCovered = true;
            gameMap[i][j].isMarked = false;
            gameMap[i][j].isTouched = false;
            gameMap[i][j].isError = false;
        }
    }
    status = STATUS_MAINLOOP;
    remainFlagCount = mineInitCount;
}

void MainGame::addMines()
{
    mineList.clear();
    numberList.clear();

    for (int i = 0; i < tableCols * tableRows; ++i)
    {
        numberList.append(i);
    }
    for (int i = 0; i < tableCols * tableRows; ++i)
    {
        qSwap(numberList[i], numberList[rand() % (tableRows * tableCols)]);
    }
    for (int i = 0; i < mineInitCount; ++i)
    {
        int x = numberList[i] % tableRows;
        int y = numberList[i] / tableRows;

        gameMap[x][y].type = BLOCK_MINE;
        mineList.append(QPoint(x, y));
    }
}

void MainGame::addNumbers()
{
    for (int i = 0; i < mineInitCount; ++i)
    {
        for (int sideX = -1; sideX <= 1; ++sideX)
        {
            for (int sideY = -1; sideY <= 1; ++sideY)
            {
                int x = mineList[i].x() + sideX;
                int y = mineList[i].y() + sideY;

                if (x >= 0 && x < tableRows && y >= 0 && y < tableCols && gameMap[x][y].type != BLOCK_MINE)
                {
                    gameMap[x][y].type = BLOCK_NUMBER;
                    gameMap[x][y].number += 1;
                }
            }
        }
    }
}

void MainGame::autoUncoverBlocks()
{
    for (int i = 0; i < tableRows; ++i)
    {
        for (int y = 0; y < tableCols; ++y)
        {
            if (gameMap[i][y].type == BLOCK_EMPTY && gameMap[i][y].isCovered)
            {
                emptyList.append(QPoint(i, y));
            }
        }
    }

    for (int i = 0; i < emptyList.size(); ++i)
    {
        for (int sideX = -1; sideX <= 1; ++sideX)
        {
            for (int sideY = -1; sideY <= 1; ++sideY)
            {
                int x = emptyList[i].x() + sideX;
                int y = emptyList[i].y() + sideY;

                if (x >= 0 && x < tableRows && y >= 0 && y < tableCols && !gameMap[x][y].isMarked)
                {
                    gameMap[x][y].isCovered = false;
                }
            }
        }
    }
    emptyList.clear();
}

GameBlock MainGame::getBlock(int x, int y)
{
    return gameMap[x][y];
}

GameLevel MainGame::getLevel()
{
    return level;
}

GameStatus MainGame::getStatus()
{
    return status;
}

bool MainGame::isLeftButtonClicked(int x, int y)
{
    if (gameMap[x][y].isCovered && !gameMap[x][y].isMarked){
        gameMap[x][y].isCovered = false;
        return true;
    }
    return false;
}

bool MainGame::isRightButtonClicked(int x, int y)
{
    if (gameMap[x][y].isCovered){
        if (!gameMap[x][y].isMarked){
            gameMap[x][y].isMarked= true;
            remainFlagCount -=1;
        }
        else if (gameMap[x][y].isMarked){
            gameMap[x][y].isMarked = false;
            remainFlagCount +=1;
        }
        return true;
    }
    return false;
}

int MainGame::getRemainFlagCount()
{
    return remainFlagCount;
}

bool MainGame::isSuccess()
{
    for (int i = 0; i < tableRows; ++i)
    {
        for (int j = 0; j < tableCols; ++j)
        {
            if (gameMap[i][j].type != BLOCK_MINE && gameMap[i][j].isCovered){
                return false;
            }
        }
    }
    status = STATUS_SUCCESS;
    return true;
}

bool MainGame::isFailure(int x, int y)
{
    if (gameMap[x][y].type!=BLOCK_MINE){
        return false;
    }
    gameMap[x][y].isTouched= true;

    for (int i = 0; i < tableRows; ++i)
    {
        for (int j = 0; j < tableCols; ++j)
        {
            if (gameMap[i][j].type == BLOCK_MINE && !gameMap[i][j].isMarked){
                gameMap[i][j].isCovered= false;
            } else if(gameMap[i][j].type!=BLOCK_MINE && gameMap[i][j].isMarked){
                gameMap[i][j].isError = true;
            }
        }
    }
    status =STATUS_FAILURE;
    return true;
}
