/*
** Copyright (c) 2014 Jarmo Hautakoski
**
** ArcanoidUbuntu project
**  */

#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsItem>

class Player : public QObject
{
    Q_OBJECT
public:
    Player(QGraphicsRectItem* rectangle,QGraphicsTextItem* text);
    ~Player();
    void MoveBrickUp();
    void MoveBrickDown();
    void SetBrickSpeed(int value);
    void TimerTrigger(int timer_count);
    bool BrickMoveUp();
    QPointF GetCurrentPos();
    void MoveBrickUp(int amount_of_pixels);
    void MoveBrickDown(int amount_of_pixels);
    void StopBrick();
    void AddGoal();
    QGraphicsRectItem* player_obj;
private:
    QGraphicsTextItem* score_item;
    QString scoreTag;
    const char* default_string;
    int key_count;
    int key_count_start_time;
    int brick_speed;
    int brick_direction;
    int player_brick_height;
    int goals;
    int ScoreTextOriginalSize;
};

#endif // PLAYER_H
