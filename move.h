#ifndef MOVE_H
#define MOVE_H

#include "QPoint"

#include "helper.h"

class Move
{
protected:
    AttackType attack;
    Direction direction;
public:
    Move(AttackType a = WAIT,Direction = NONE);
    void SetAttackType(AttackType);
    void SetDirection(Direction);
    Direction GetDirection();
    AttackType GetAttack();
};

#endif // MOVE_H
