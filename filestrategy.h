#ifndef FILESTRATEGY_H
#define FILESTRATEGY_H
#include <QProcess>
#include "strategy.h"
#include "world.h"

class FileStrategy:public Strategy
{
    QProcess *process;

    QString MoveVectorToDir(int d){
        switch(d){
            case 0:
                return "u";
            case 1:
                return "r";
            case 2:
                return "l";
            case 3:
                return "d";
            default:
                return "d";
        }
    }

     QString MoveVectorToDir(QPoint p){
         if(p.rx() == 0)
             if(p.ry()>0)
                 return "r";
             else
                 return "l";

        if(p.rx()>0)
            return "d";
        else
            return "u";
     }

public:
    FileStrategy(){
        process = NULL;
    }

    ~FileStrategy(){
        process->close();
        delete process;
    }

    Move GetMove(){
        return move;
    }


    Move CalculateMove(World * w, Tank * t){
        auto tanks = w->GetTanks();
        int size = tanks.size();
        QString input,output;
        int self = -1;
        for(int i=0;i<tanks.size();++i){
            if(tanks[i]->GetPosition() == t->GetPosition())
                self = i+1;
        }
        input = QString::fromStdString(std::to_string(size)) +
                " "+
                QString::fromStdString(std::to_string(self))+
                "\n";

        for(int i=0;i<tanks.size();++i){
            input+=
                    QString::fromStdString(std::to_string(tanks[i]->GetPosition().rx()))+
                    " "+
                    QString::fromStdString(std::to_string(tanks[i]->GetPosition().ry()))+
                    " "+
                    MoveVectorToDir(tanks[i]->GetDirection())+"\n";


        }
        auto bullets = w->GetBullets();
        int bsize = bullets.size();
        input+=QString::fromStdString(std::to_string(bsize)) + "\n";
        for(int i=0;i<bsize;++i){
            QPoint p = bullets[i]->GetPosition()/cellSize;
            input+=
                    QString::fromStdString(std::to_string(p.rx()))+
                    " "+
                    QString::fromStdString(std::to_string(p.ry()))+
                    " "+
                    MoveVectorToDir(bullets[i]->GetMoveVector())+
                    " "+
                    QString::fromStdString(std::to_string(bullets[i]->TimeToNext()))+
                    "\n";
        }

       // input += "\r";

        qDebug("input");
        qDebug(input.toStdString().c_str());

        if(!process->isOpen() || !process->isReadable() || !process->isWritable()){
            qDebug("Huston we have problem");
            return move = Move();
        }
        qDebug("Huston OK");
        process->waitForReadyRead(100);
        process->write(input.toStdString().c_str());
        process->waitForFinished(500);

        qDebug("finished");
        if(1)
            qDebug("Ready read");
        else
            qDebug("Not ready");
      //  output = (process->read(100));
        char data[201];


        //process->readAllStandardOutput();
        process->readLine(data,100);
        output = QString(data);

        qDebug("output");
        qDebug(output.toStdString().c_str());
        qDebug(data);

        if(output.length() == 0){
           // output = "move";
            output = "wait";
            qDebug("no output");
        }

        switch(output[0].toLatin1()){
        // move
            case 'm':{
                Direction d = t->GetDirection();
                return move = Move(WAIT,d);}
        //shot
            case 's':
                return move = Move(SIMPLE,NONE);
        //turn
            case 't':{
                switch(output[5].toLatin1()){
                    case 'u':
                        return move = Move(WAIT,UP);
                    case 'd':
                        return move = Move(WAIT,DOWN);
                    case 'l':
                        return move = Move(WAIT,LEFT);
                    case 'r':
                        return move = Move(WAIT,RIGHT);
                    default:
                        return move = Move(WAIT,RIGHT);
                }

                return move = Move(WAIT,NONE);
             }
       //wait or incorrect
            default:
                return move = Move(WAIT,NONE);
        }


    }


    FileStrategy(QString filename,QString world)
    {
        qDebug("attemp to create process");
        process = new QProcess();
        process->start(filename);
        if(process->isOpen() && process->isReadable() && process->isWritable())
            qDebug("all is ok");
        else
            qDebug("something is wrong");

       // world+="\n";

        process->write(world.toStdString().c_str());

    }

};







#endif // FILESTRATEGY_H
