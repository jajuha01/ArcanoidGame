#include "player.h"

#define PLAYER_BRICK_SPEED_INCREASE_LIMIT 2
#define PLAYER_BRICK_SPEED_INCREASE_TIMELIMIT 10
#define PLAYER_BRICK_DEFAULT_SPEED 4
#define PLAYER_BRICK_MAX_SPEED 30
#define PLAYER_BRICK_SPEED_INREASE 2

Player::Player(QGraphicsRectItem* rectangle,QGraphicsTextItem* text)
{
    player_obj              = rectangle;
    scoreTag                = text->toPlainText();
    score_item              = text;
    key_count               = 0;
    key_count_start_time    = 0;
    brick_direction         = 0;
    goals                   = 0;
    brick_speed             = PLAYER_BRICK_DEFAULT_SPEED;

    /* Add zero goals to end of string */
    score_item->setPlainText(QString (scoreTag + QString::number(0)));
}

Player::~Player()
{
    /* Player_obj is owned in scene which take care of cleaning it */
}

void Player::MoveBrickUp()
{
    brick_direction = -1;
    key_count++;
}

void Player::MoveBrickDown()
{
    brick_direction = 1;
    key_count++;
}

void Player::SetBrickSpeed(int value)
{

}

void Player::TimerTrigger(int timer_count)
{
    /* React every third timout */
    if (!(timer_count%3))
    {
        if (key_count >= PLAYER_BRICK_SPEED_INCREASE_LIMIT )
        {
            if (brick_speed < PLAYER_BRICK_MAX_SPEED)
            {
                brick_speed = brick_speed*PLAYER_BRICK_SPEED_INREASE;
            }
            key_count = 0;
        }
        else if ((brick_speed > PLAYER_BRICK_DEFAULT_SPEED))
        {
            brick_speed = brick_speed/PLAYER_BRICK_SPEED_INREASE;
            if (brick_speed < PLAYER_BRICK_DEFAULT_SPEED)
            {
                 brick_speed = PLAYER_BRICK_DEFAULT_SPEED;
            }
            key_count = 0;
        }
        key_count_start_time = timer_count;
        player_obj->moveBy(0,(brick_speed*brick_direction));
    }
}

bool Player::BrickMoveUp()
{
    bool direction_up = false;
    if (brick_direction < 0)
    {
        direction_up = true;
    }
    return direction_up;
}

QPointF Player::GetCurrentPos()
{
    QPointF pos = player_obj->pos();
    return pos;
}

void Player::MoveBrickUp(int amount_of_pixels)
{
     player_obj->moveBy(0,amount_of_pixels*-1);
}

void Player::MoveBrickDown(int amount_of_pixels)
{
    player_obj->moveBy(0,amount_of_pixels);
}

void Player::StopBrick()
{
    brick_direction = 0;
}

void Player::AddGoal()
{
    QString tmp_str;
    goals++;
    tmp_str = QString::number(goals);
    /* Create new text to render based of original tag + goals */
    score_item->setPlainText(QString (scoreTag + tmp_str));
}
