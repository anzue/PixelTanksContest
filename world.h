#ifndef WORLD_H
#define WORLD_H

#include <vector>
using std::pair;
using std::vector;

#include <QString>

#include "object.h"

#include "neuralnetwork.h"
#include "tank.h"
#include "bullet.h"

class World
{
protected:
    vector<vector<Object*> > map;
    vector<Tank*> tanks;
    vector<Bullet*> bullets;
    vector<NeuralNetwork*> neuroNets;
    int timer;
    int simpleBotsCount;
    int neuroBotsCount;
public:
    World(int heigth = worldHeight,int width = worldWidth,int bots = botsCount,bool player = false);
    ~World();
    void RefreshWorld();
    void ProccesBullets();
    void ProccesTanks();
    void Selection();

    ObjectType GetObjectType(int x,int y){return map[x][y]->GetObjectType();}

    QString GetLeadersTable();

    QPoint FindEmptyCell();

    Strategy* newRandomStrategy();
    Strategy* newNeuroStrategy();
    Strategy* newDefaultStrategy();

    Strategy* newPlayerStrategy(QString file,QString w);
    //Strategy* newPlayerStrategy();

    void AddSimpleBots(int);
    void AddNeuroBots(int);
    void AddPlayer(QString);

    vector<vector< QString > > GetBitMap();
    vector<Tank*> GetTanks(){return tanks;}
    vector<Bullet*> GetBullets(){return bullets;}
    QStringList GetBulletsList();
    QString GetTextForm();
};

#endif // WORLD_H
