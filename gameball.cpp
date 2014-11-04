#include <QtCore>
#include <QDebug>
#include "gameball.h"
#include <QGraphicsItem>

#define BALL_DEFAULT_SPEED          2
#define PI 3.14159265

GameBall::GameBall(QGraphicsEllipseItem *object)
{
    ball = object;
    /* Use angle for direction of ball movement 0 left 90 up 180 right ... */
    angle = 0;
    speed = BALL_DEFAULT_SPEED;
}

GameBall::~GameBall()
{
    /* Ball object is owned by scene. No cleaning needed for it */
}

void GameBall::Move()
{
    /* Calculate X and Y Movement based of Speed and angle */
    qreal x,y;
    y = sin(angle*PI/180)*speed*-1;
    x = cos(angle*PI/180)*speed*-1;
    ball->moveBy(x,y);
}

QPointF GameBall::GetCurrentPos()
{
    QPointF pos = ball->pos();
    return pos;
}

bool GameBall::DirectionLeft()
{
    bool going_to_left = false;
    if (angle <= 90)
    {
        going_to_left = true;
    }
    else if (angle > 270 && angle <= 360)
    {
        going_to_left = true;
    }
    return going_to_left;
}

bool GameBall::DirectionUp()
{
    bool going_to_up = false;
    if (angle <= 180)
    {
        going_to_up = true;
    }
    return going_to_up;
}


void GameBall::ChangeAngle(int value)
{
    angle += value;
    /* Give small random effect */
    angle += (rand()-(RAND_MAX/2))%3;
    if (angle < 0)
    {
        angle = 360+angle;
    }
    angle %= 360;
}

void GameBall::SetAngle(int value)
{
    angle = value;
}

int GameBall::GetAngle()
{
    return angle;
}

void GameBall::IncreaseSpeed(float ratio)
{
    speed *=ratio;
}

void GameBall::SetSpeed(int value)
{
    speed = value;
}

void GameBall::CalculateCollision()
{
    if (DirectionLeft())
    {
        if (DirectionUp())
        {
            if (GetAngle() == 0)
            {
                ChangeAngle(180);
            }
            else
            {
                SetAngle(90+(90-GetAngle()));
            }
        }
        else
        {
            SetAngle(270-(GetAngle()-270));
        }
    }
    else
    {
        if (GetAngle() == 180)
        {
            ChangeAngle(180);
        }
        else
        {
            if (DirectionUp())
            {
                SetAngle(180-GetAngle());
            }
            else
            {
                SetAngle(270+(270-GetAngle()));
            }
        }
    }
}


