#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <QVector>
#include <QPoint>

using BlockPointList = QVector<QPoint>;
using NumberList = QVector<int>;

enum GameStatus
{
    STATUS_MAINLOOP,
    STATUS_PAUSE,
    STATUS_FAILURE,
    STATUS_SUCCESS
};

enum GameLevel
{
    LEVEL_EASY,
    LEVEL_MEDIUM,
    LEVEL_HARD,
    LEVEL_CUSTOM
};
enum GameBlockType
{
    BLOCK_EMPTY,
    BLOCK_NUMBER,
    BLOCK_MINE
};

class GameBlock
{
public:
    static const int SIZE = 32;
public:
    GameBlockType type;
public:
    int number;
    bool isCovered;
    bool isMarked;
    bool isError;
    bool isTouched;
};

class GameMediumLevel
{
public:
    static const int ROWS = 15;
    static const int COLS = 15;
    static const int MINE_INIT_COUNT = 30;
};

class GameHardLevel
{
public:
    static const int ROWS = 30;
    static const int COLS = 20;
    static const int MINE_INIT_COUNT = 100;
};

class GameEasyLevel
{
public:
    static const int ROWS = 10;
    static const int COLS = 10;
    static const int MINE_INIT_COUNT = 10;
};

class MainGame
{
private:
    static const int ROWS_MAX = 40;
    static const int COLS_MAX = 25;

private:
    GameBlock gameMap[ROWS_MAX][COLS_MAX];
    BlockPointList mineList;
    BlockPointList emptyList;
    NumberList numberList;
    GameStatus status;
    GameLevel level;

private:
    int tableRows;
    int tableCols;
    int mineInitCount;
    int remainFlagCount;

public:
    void setEasyLevel();

    void setMediumLevel();

    void setHardLevel();

    void setCustomLevel(int rows, int cols, int mineCount);

public:
    int getTableCols();

    int getTableRows();

    GameBlock getBlock(int x, int y);

    GameLevel getLevel();

    GameStatus getStatus();

    int getRemainFlagCount();

public:
    void setPause();

    void setResume();

public:
    void restart();

    void addMines();

    void addNumbers();

    void autoUncoverBlocks();

public:
    bool isLeftButtonClicked(int x, int y);
    bool isRightButtonClicked(int x, int y);

public:
    bool isSuccess();
    bool isFailure(int x, int y);
};

#endif // GAMEMODEL_H
