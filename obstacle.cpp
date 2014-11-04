#include "obstacle.h"

Obstacle::~Obstacle()
{
    delete obj;
}

Obstacle::Obstacle(QGraphicsRectItem* item)
{
    obj = item;
}

void Obstacle::CalculateCollision(GameBall* ball)
{
    /* todo (Lisää original koordinaatit jokaiseen objektiin. Tai sitten geneerinen ball collision systeemi
    QPointF positionBall = ball->ball->mapFromItem(ball->ball,ball->GetCurrentPos());
    QPointF positionObstacle =  obj->mapFromScene(0,0);
    obj->S
    qreal x = positionObstacle.rx();
    qreal y = positionObstacle.ry();*/
}
