/*
** Copyright (c) 2014 Jarmo Hautakoski
**
** ArcanoidUbuntu project
**  */

#include "appcontrol.h"
#include <QGraphicsItem>
#include <QList>
#include "player.h"
#include "gameball.h"
#include <QDir>

#define WALL_TICKHNESS 10
#define BALL_SIZE_EASY 30
#define PLAYER_HEIGHT_EASY 50
#define PLAYER_WIDTH 10
#define BALL_SPPED_INCREASE_TIMEOUT_EASY 800
#define BALL_SPEED_INCREASE_RATIO 1.5
#define BALL_DEFAULT_SPEED_EASY 4
#define RANDOM_OBJECT_CREATION_TIMEOUT_EASY 500
#define RANDOM_OBJECT_HEIGHT 25
#define RANDOM_OBJECT_WIDTH PLAYER_WIDTH

AppControl::AppControl(QGraphicsView* view)
{
    viewP = view;
    scene = new QGraphicsScene();

   // Sound = new GameSound("C:\Qt\Tools\QtCreator\bin\Arcanoid\C64Music Druid.wav");
    viewP->setScene(scene);
    game_start_time = 0;
    previous_collision_brick = NULL;
    previous_collision_ball = NULL;

    SetGameLevel(easy);
    /*QDir* dir = new QDir();
    //QString fullPath = dir->absoluteFilePath("01 Daybreak.mp3");
    QSound* player = new QSound("01 Daybreak.mp3",this);
    player->setLoops(3);
    player->play();*/
}

AppControl::~AppControl()
{
    Obstacle* obstacle = NULL;

    /* Remove all obstacle objects */
    while (!listOfObstagle.isEmpty())
    {
        obstacle =  listOfObstagle.takeFirst();
        /* Remove object from Scene */
        scene->removeItem(obstacle->obj);
        delete obstacle;
    }
    delete leftPlayer;
    delete rightPlayer;
    delete ball;
    /* Scene cleans all graphic elements which are tight to it */
    delete scene;
}

void AppControl::Timeout(AppTimer* timer)
{
    int timer_count = timer->TimeOutCount();
    if (game_start_time == 0)
    {
        game_start_time = timer_count;
    }
    else
    {
        /* Increase ball speed every minute */
        if (!((timer_count - game_start_time)%ballSpeedIncreaseTimeout))
        {
            ball->IncreaseSpeed(BALL_SPEED_INCREASE_RATIO);
        }
    }
    /* Move Ball */
    if(ball)
    {
        ball->Move();
    }
    /* Check do we need to increase Left Player Brick Speed */
    leftPlayer->TimerTrigger(timer_count);

    /* Check do we need to increase Right Player Brick Speed */
    rightPlayer->TimerTrigger(timer_count);

    /* Generate Random objects */
    CreateRandomObjects(timer_count);

    /* Check Collision */
    CollisionControl();

    /* Check do we have goal */
    CheckGoal();
}

void AppControl::KeyEvent(Qt::Key key)
{
    if (key == Qt::Key_A)
    {
        leftPlayer->MoveBrickUp();

    }
    if (key == Qt::Key_Z)
    {
        leftPlayer->MoveBrickDown();
    }
    if (key == Qt::Key_K)
    {
        rightPlayer->MoveBrickUp();
    }
    if (key == Qt::Key_M)
    {
        rightPlayer->MoveBrickDown();
    }
}

void AppControl::SettingsUpdated()
{

}

void AppControl::InitializeGame(int WidthOfArena,int HeighOfArena)
{
    /* Read view size information */
    height = HeighOfArena;
    width = WidthOfArena;
    QPointF point;

    QPen blackPen = QPen(Qt::black);
    blackPen.setWidth(2);
    QBrush Brush = QBrush(Qt::blue);
    /* Create left player */
    QGraphicsTextItem * PlayerGoals = new QGraphicsTextItem();
    PlayerGoals->setPlainText("Goals: ");
    PlayerGoals->setPos(20,20);
    scene->addItem(PlayerGoals);
    QGraphicsRectItem* player = scene->addRect(0,((height/2)-(PlayerBrickHeight/2)),PLAYER_WIDTH,PlayerBrickHeight,blackPen,Brush);
    leftPlayer = new Player(player,PlayerGoals);

    /* Create right player */
    Brush = QBrush(Qt::green);
    PlayerGoals = new QGraphicsTextItem();
    PlayerGoals->setPlainText("Goals: ");
    PlayerGoals->setPos(width-80,20);
    scene->addItem(PlayerGoals);
    player = scene->addRect((width-PLAYER_WIDTH),((height/2)-(PlayerBrickHeight/2)),PLAYER_WIDTH,PlayerBrickHeight,blackPen,Brush);
    rightPlayer = new Player(player,PlayerGoals);

    /* Create walls */
    Brush = QBrush(Qt::gray);
    upperWall = scene->addRect(0,0,width,WALL_TICKHNESS,blackPen,Brush);
    lowerWall = scene->addRect(0,(height-WALL_TICKHNESS),width,WALL_TICKHNESS,blackPen,Brush);
    /* Create ball */
    Brush = QBrush(Qt::red);
    QGraphicsEllipseItem* ball_object = scene->addEllipse((width/2),height/2,ballSize,ballSize,blackPen,Brush);
    ball = new GameBall(ball_object);
    ball->SetSpeed(ballDefaultSpeed);



}

void AppControl::ReInitializeGame()
{
    Obstacle* obstacle = NULL;
    game_start_time = 0;

    /* Remove old ball */
    scene->removeItem(ball->ball);
    delete ball->ball;
    delete ball;

    /* Create ball */
    QPen blackPen = QPen(Qt::black);
    blackPen.setWidth(2);
    QBrush Brush = QBrush(Qt::red);
    QGraphicsEllipseItem* ball_object = scene->addEllipse((width/2),height/2,ballSize,ballSize,blackPen,Brush);
    ball = new GameBall(ball_object);

    previous_collision_ball = NULL;
    previous_collision_brick = NULL;


    /* Remove all obstacle objects */
    while (!listOfObstagle.isEmpty())
    {
        obstacle =  listOfObstagle.takeFirst();
        /* Remove object from Scene */
        scene->removeItem(obstacle->obj);
        delete obstacle;
    }
}

void AppControl::CollisionControl()
{
    QList<QGraphicsItem *> items = scene->collidingItems((QGraphicsItem *)ball->ball);
    QGraphicsItem* tmp_item;
    Player* colliding_player;
    int collision_move_amount   = 0;
    if (!items.isEmpty())
    {
        tmp_item = items.first();
        if (tmp_item != previous_collision_ball)
        {
            if ((tmp_item == rightPlayer->player_obj) || (leftPlayer->player_obj == tmp_item))
            {
                int brick_impact = 10;
                /* Calculate collision impact to ball movement */
                ball->CalculateCollision();
                /* Calculate brick movement impact to ball */

                if (tmp_item == rightPlayer->player_obj)
                {
                    colliding_player = rightPlayer;
                }
                else
                {
                    colliding_player = leftPlayer;
                }

                if (ball->DirectionUp() && colliding_player->BrickMoveUp())
                {
                    brick_impact *=-1;
                }
                else if (!ball->DirectionUp() && !colliding_player->BrickMoveUp())
                {
                    brick_impact *=-1;
                }
                ball->ChangeAngle(brick_impact);

            }
            else if (upperWall == tmp_item)
            {
                if (ball->DirectionLeft())
                {
                ball->SetAngle(360-ball->GetAngle());
                }
                else
                {
                ball->SetAngle(180+(180-ball->GetAngle()));
                }
            }
            else if (lowerWall == tmp_item)
            {
                if (ball->DirectionLeft())
                {
                ball->SetAngle(90-(ball->GetAngle()-270));
                }
                else
                {
                 ball->SetAngle(180-(ball->GetAngle()-180));
                }
            }
            else /* Check is this collision with obstacle objects */
            {
                Obstacle* obstacle = NULL;
                /* Check is collision happening with random objects */
                for (int i = 0; i < listOfObstagle.size(); ++i)
                {
                    if (listOfObstagle.at(i)->obj == tmp_item)
                    {
                        obstacle =  listOfObstagle.at(i);
                        /* Remove object from Scene */
                        scene->removeItem(tmp_item);
                        tmp_item = NULL;
                        listOfObstagle.removeOne(obstacle);
                        break;
                    }

                }
                if (obstacle)
                {
                    /* New ball direction */
                    ball->CalculateCollision();
                    delete obstacle;
                }
            }
            previous_collision_ball = tmp_item;
        }

    }
    /* Check is right player out of game arena */
    items.clear();
    tmp_item = NULL;
    items = scene->collidingItems((QGraphicsItem *)rightPlayer->player_obj);
    if (!items.isEmpty() && items.first() != ball->ball)
    {
        /* Stop brick */
        rightPlayer->StopBrick();

        colliding_player = rightPlayer;
        tmp_item = items.first();

    }
    /* Check is left player out of game arena */
    items.clear();
    items = scene->collidingItems((QGraphicsItem *)leftPlayer->player_obj);
    if (!items.isEmpty() && items.first() != ball->ball)
    {
        /* Stop brick */
        leftPlayer->StopBrick();
        /* Move it back inside game arena */
        colliding_player = leftPlayer;
        tmp_item = items.first();
    }

    /* Check is this second collision in row -> Increase movement */
    if (previous_collision_brick == tmp_item)
    {
        collision_move_amount = 10;
    }
    else
    {
        collision_move_amount = 2;
    }

    /* Move brick back inside game arena */
    if (upperWall == tmp_item)
    {
        colliding_player->MoveBrickDown(collision_move_amount);
        previous_collision_brick = tmp_item;
    }
    else if (lowerWall == tmp_item)
    {
        colliding_player->MoveBrickUp(collision_move_amount);
        previous_collision_brick = tmp_item;
    }
    items.clear();
}

void AppControl::CheckGoal()
{
    QPointF ball_pos    = ball->GetCurrentPos();
    QString tmp_str;

    if (ball_pos.x() < -(width/2+PLAYER_WIDTH))
    {
        rightPlayer->AddGoal();
        /* Move ball back to center */
        ReInitializeGame();
    }
    else if (ball_pos.x() > (width/2+PLAYER_WIDTH))
    {
        leftPlayer->AddGoal();
        /* Move ball back to center */
        ReInitializeGame();
    }
    /* Update player score data */


}

void AppControl::CreateRandomObjects(int timer_count)
{
    int game_time = timer_count - game_start_time;
    qreal random_x = rand()%(int)(width-(PLAYER_WIDTH*2)-RANDOM_OBJECT_WIDTH);
    qreal random_y = rand()%(int)(height-(WALL_TICKHNESS*2)-RANDOM_OBJECT_HEIGHT);
    if (!(game_time % randomObjectCreationSpeed) && (game_time > 0))
    {
        QPen blackPen = QPen(Qt::black);
        blackPen.setWidth(2);
        QBrush Brush = QBrush(Qt::yellow);
        /* Create object */

        QGraphicsRectItem* object = scene->addRect(random_x+PLAYER_WIDTH,random_y+WALL_TICKHNESS,RANDOM_OBJECT_WIDTH,RANDOM_OBJECT_HEIGHT,blackPen,Brush);
        while (!scene->collidingItems(object).isEmpty())
        {
            scene->removeItem(object);
            delete object;
            random_x = rand()%(int)(width-(PLAYER_WIDTH*2));
            random_y = rand()%(int)(height-(WALL_TICKHNESS*2));
            object = scene->addRect(random_x+PLAYER_WIDTH,random_y+WALL_TICKHNESS,RANDOM_OBJECT_WIDTH,RANDOM_OBJECT_HEIGHT,blackPen,Brush);
        }
        listOfObstagle.append(new Obstacle(object));
    }

}

void AppControl::SetGameLevel(GameDifficulty value)
{
    switch (value)
    {
    case medium:
        ballSize                    = BALL_SIZE_EASY/2;
        ballSpeedIncreaseTimeout    = BALL_SPPED_INCREASE_TIMEOUT_EASY/1.5;
        randomObjectCreationSpeed   = RANDOM_OBJECT_CREATION_TIMEOUT_EASY/3;
        PlayerBrickHeight           = PLAYER_HEIGHT_EASY;
        ballDefaultSpeed            = BALL_DEFAULT_SPEED_EASY*1.5;
        break;
    case hard:
        ballSize                    = BALL_SIZE_EASY/3;
        ballSpeedIncreaseTimeout    = BALL_SPPED_INCREASE_TIMEOUT_EASY/2;
        randomObjectCreationSpeed   = RANDOM_OBJECT_CREATION_TIMEOUT_EASY/5;
        PlayerBrickHeight           = PLAYER_HEIGHT_EASY/2;
        ballDefaultSpeed            = BALL_DEFAULT_SPEED_EASY*2;
        break;
    case easy:
    default:
        /* Use easy game level as default */
        ballSize                    = BALL_SIZE_EASY;
        ballSpeedIncreaseTimeout    = BALL_SPPED_INCREASE_TIMEOUT_EASY;
        randomObjectCreationSpeed   = RANDOM_OBJECT_CREATION_TIMEOUT_EASY;
        PlayerBrickHeight           = PLAYER_HEIGHT_EASY;
        ballDefaultSpeed            = BALL_DEFAULT_SPEED_EASY;
    }
    GameDifficultyValue = value;
}
