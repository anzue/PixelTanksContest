#include<iostream>
#include<string>

using std::to_string;
using std::swap;

#include "tank.h"
#include "playerstrategy.h"

#define max(a,b) ((a>b)?(a):(b))


Tank::Tank(
        QPoint p,
        Strategy *s,
        Direction d,
        QColor c,
        int h,
        QString na)
    : Object(p),
      strategy(s),
      direction(d),
      color(c),
      healthPoints(h)
{
    delay = 0;
    //alive = 1;
    points = 0;
    name = na;
    shotDelay = 0;
    for(int i=0;i<4;++i)
        attackDelay[i] = 0;
    respawnDelay = 0;
}

Tank::~Tank(){
    if(strategy!=NULL)
        delete strategy;
}

Direction Tank::GetDirection(){return direction;}

QColor Tank::GetColor(){return color;}

ObjectType Tank::GetObjectType(){
    return TANK;
}

void Tank::Display(QPainter* painter){
    char a[paintSize][paintSize+1] = {
        ".....=.....",
        ".=...=...=.",
        ".==..=..==.",
        ".===.=.===.",
        ".=========.",
        ".=========.",
        ".=========.",
        ".===...===.",
        ".==.....==.",
        ".=.......=.",
        "..........."
    };

    switch (direction) {

    case LEFT:
        break;
    case RIGHT:
        for(int i=0;i<paintSize/2;++i)
            for(int j=0;j<paintSize;++j)
                swap(a[i][j],a[paintSize-i-1][j]);
        break;
    case UP:
        for(int i=0;i<paintSize;++i)
            for(int j=0;j<i;++j)
                swap(a[i][j],a[j][i]);
        break;
    case DOWN:
        for(int i=0;i<paintSize;++i)
            for(int j=0;j<paintSize-i;++j)
                swap(a[i][j],a[paintSize-j-1][paintSize-i-1]);
        break;
    default:
        break;
        }


    QPoint pPosition = position;
    pPosition*=cellSize;
    QBrush brush;
    brush.setColor(Qt::red);
    QPen pen;
    for(int i=0;i<cellSize;++i)
        for(int j=0;j<cellSize;++j){
            if(a[i*paintSize/cellSize][j*paintSize/cellSize]=='=')
                pen.setColor(color);
            else
                pen.setColor(backgroundColor);
            painter->setPen(pen);
            painter->drawPoint(pPosition.x()+i,pPosition.y()+j);

        }


    if(strategy == PlayerStrategy::GetInstance()){
        painter->setPen(QPen(Qt::black));
        painter->drawText(10,(worldWidth+4)*cellSize+10,QString(to_string(healthPoints).c_str()));}
}

void Tank::SetStrategy(Strategy *s){
    strategy = s;
}

void Tank::SetDirection(Direction d){
    direction = d;
}

void Tank::erase(){
    this->~Tank();
}

Move Tank::GetMove(World * world){

    if(healthPoints<defaultHealthPoints && rand()%10 == 0)
        ++healthPoints;

    if(delay>0 ){
        --delay;
        return Move();
    }

    if(color == frozenColor)
        color = oldColor;
    if(shotDelay>0)
        --shotDelay;

    for(int i=0;i<4;++i)
        if(attackDelay[i]>0)
            --attackDelay[i];

    if(strategy!=NULL){
        delay = moveDelay;
        strategy->CalculateMove(world,this);
        Move m = strategy->GetMove();
        if(shotDelay>0)
            m.SetAttackType(WAIT);
        if(m.GetAttack()!=WAIT){
            shotDelay = defaultShotDelay;
            attackDelay[(int)m.GetAttack()] = attacks[(int)m.GetAttack()].GetDelay();
        }
        return m;
    }
    return Move();
}

void Tank::SetMove(Move a){
    strategy->SetMove(a);
}

void Tank::SetDelay(int d){
    delay = max(d,delay);
}

void Tank::TakeDamage(int d){
    healthPoints-=d;
    if(healthPoints<=0){
        healthPoints = 0;
        respawnDelay = defaultRespawnDelay;
    }
}

QString Tank::GetInfo(){
    QString r = name;
    r += " "+QString(to_string(points).c_str());
    return r;
}

void Tank::SetColor(QColor c){
    if(color!= frozenColor)
        oldColor = color;
    color = c;
}

void Tank::AddPoints(int p){
     points+=p;
    if(strategy!=NULL)
        strategy->AddPoints(p);
}

bool Tank::IsAlive(){
    return (respawnDelay == 0);}

bool Tank::Respawn(){
    if(--respawnDelay == 0){
        healthPoints =  defaultHealthPoints;
        return 1;
    }
    return 0;
}
