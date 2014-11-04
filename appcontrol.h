#ifndef APPCONTROLL_H
#define APPCONTROLL_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QtCore>
#include "apptimer.h"
#include "player.h"
#include "gameball.h"
#include "obstacle.h"



enum GameDifficulty {
    easy = 1,
    medium = 2,
    hard = 3
};

class AppControl : public QObject
{
    Q_OBJECT
public:
    AppControl(QGraphicsView* view);
    ~AppControl();
    void Timeout(AppTimer* timer);
    void KeyEvent(Qt::Key key);
    void SettingsUpdated();
    void InitializeGame(int WidthOfArena,int HeighOfArena);
    void ReInitializeGame();
    void CollisionControl();
    void CheckGoal();
    void CreateRandomObjects(int current_timer_count);
    void SetGameLevel(GameDifficulty value);
private:
    QGraphicsView* viewP;
    QGraphicsScene* scene;
    qreal height,width;
    Player* leftPlayer;
    Player* rightPlayer;
    QGraphicsRectItem* upperWall;
    QGraphicsRectItem* lowerWall;
    GameBall* ball;
    QGraphicsItem* previous_collision_ball;
    QGraphicsItem* previous_collision_brick;
    QList <Obstacle*> listOfObstagle;
    int game_start_time;
    GameDifficulty GameDifficultyValue;
    int ballSize;
    int ballSpeedIncreaseTimeout;
    int ballDefaultSpeed;
    int randomObjectCreationSpeed;
    int PlayerBrickHeight;


};

#endif // APPCONTROLL_H
