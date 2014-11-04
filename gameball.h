/*
** Copyright (c) 2014 Jarmo Hautakoski
**
** ArcanoidUbuntu project
**  */

#ifndef BALL_H
#define BALL_H

#include <QtCore>
#include <QGraphicsItem>
#include <QGraphicsScene>

class GameBall : public QObject
{
    Q_OBJECT
public:
    GameBall(QGraphicsEllipseItem* object);
    ~GameBall();
    void Move();
    QPointF GetCurrentPos();
    bool DirectionLeft();
    bool DirectionUp();
    void ChangeAngle(int value);
    void SetAngle(int value);
    int GetAngle();
    void IncreaseSpeed(float ratio);
    void CalculateCollision();
    void SetSpeed(int value);
    QGraphicsEllipseItem* ball;
    int speed;
private:
    int angle;
};

#endif // BALL_H
