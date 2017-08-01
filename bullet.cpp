#include "bullet.h"

/*
Bullet::Bullet()
{

}*/

Bullet::Bullet(Tank* t,Attack a, QPoint p, Direction d)
    :
      Object(p),
      attack(a),
      owner(t)
{
    switch (d) {
    case UP:
        moveVector = QPoint(0,-1);
        break;
    case DOWN:
        moveVector = QPoint(0,1);
        break;
    case LEFT:
        moveVector = QPoint(-1,0);
        break;
    case RIGHT:
        moveVector = QPoint(1,0);
        break;
    case NONE:
        break;
    }
    moveVector*=attack.GetSpeed();
    way = 0;
}

Bullet::~Bullet(){

}


bool Bullet::Shift(){
    position+=moveVector;
    way+=abs(moveVector.x()+moveVector.y());
    if(way>=attack.GetLength())
        return false;
    return true;
}

void Bullet::Display(QPainter *p){
    QPen pen(bulletColor);


    QBrush brush(
                (attack.GetType() == SIMPLE)?
                    bulletColor:
                    ((attack.GetType() == FREEZING)?
                         Qt::blue:
                         Qt::gray));

    p->setPen(pen);
    p->setBrush(brush);
    int r = 3;
    QRectF rectangle(position.x()-r, position.y()-r, 2*r,2*r);
    p->drawEllipse(rectangle);
}

int Bullet::TimeToNext(){
    if(moveVector == QPoint(0,0))
        return 10000000;

    QPoint p = position/cellSize;
    QPoint q = p;
    QPoint pos =position;
    int t=0;
    while(q==p){
        pos+=moveVector;
        q = pos/cellSize;
        ++t;
    }
    return t;

}
