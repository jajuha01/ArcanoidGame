/*
** Copyright (c) 2014 Jarmo Hautakoski
**
** ArcanoidUbuntu project
**  */

#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QGraphicsItem>
#include "gameball.h"

class Obstacle : public QObject
{
    Q_OBJECT
public:
    Obstacle();
    ~Obstacle();
    Obstacle(QGraphicsRectItem* item);
    void CalculateCollision(GameBall* ball);
    QGraphicsRectItem* obj;

};

#endif // OBSTACLE_H
