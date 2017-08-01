#include "defaultstrategy.h"

DefaultStrategy::DefaultStrategy(){}

DefaultStrategy::~DefaultStrategy(){}

Move DefaultStrategy::GetMove(){
    fuel-=waitFuel;
    if(move.GetAttack()!=WAIT)
        fuel-= shotFuel;
    if(move.GetDirection()!=NONE)
        fuel-= moveFuel;
    return move = Move(rand()%2?SIMPLE:WAIT,Direction(rand()%5));
}

Move DefaultStrategy::CalculateMove(World *, Tank *){
    return move = Move(rand()%2?SIMPLE:WAIT,Direction(rand()%5));
}
