#include "move.h"

Move::Move(AttackType a,Direction d):
    attack(a),direction(d){}

void Move::SetAttackType(AttackType a){
    attack = a;
}

void Move::SetDirection(Direction d){
    direction = d;
}

AttackType Move::GetAttack(){return attack;}

Direction Move::GetDirection(){return direction;}
