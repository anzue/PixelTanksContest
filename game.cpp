#include "game.h"
#include "ui_game.h"

#include <QFileDialog>

#include <QPainter>
#include <QKeyEvent>

#include <vector>
using std::vector;
using std::swap;

#include <QTableView>
#include <QTableWidget>

#include <iostream>
using std::cout;

#include "helper.h"

#include "tank.h"

Game::Game(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Game)
{
    timer = NULL;
    ui->setupUi(this);
   // world = new World(worldHeight,worldWidth);
   // ui->SettingsBox->hide();

    if(widget != NULL){
   //     delete widget;
        widget = NULL;
    }

     widget = new PaintWidget(this);
     widget->hide();

    ui->HeigthBox->setMinimum(10);
    ui->HeigthBox->setMaximum(40);
    ui->HeigthBox->setValue(15);

    ui->WidthBox->setMinimum(10);
    ui->WidthBox->setMaximum(30);
    ui->WidthBox->setValue(15);

    ui->SimpleBotsCount->setMinimum(1);
    ui->SimpleBotsCount->setMaximum(14);

    //ui->NeuroBotsCount->setMinimum(1);
    //ui->NeuroBotsCount->setMaximum(14);

}

Game::~Game()
{
    delete ui;
}

void Game::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
   // if(event->isAccepted()){;}
 //   PlayerStrategy::GetInstance()->SetKeys(keys);

}

void Game::keyPressEvent(QKeyEvent* event){
/*
    std::string s;
    s = event->text().toStdString();
    if(s.size()<=0)
        return;

    keys.push_back(s[0]);
*/
    //experimental, may cause problems
    //refreshWorld();
}


void Game::initTimer(){
   // QTimer *timer = NULL;
    if(timer == NULL){
        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(refreshWorld()));
    }
    timer->start(renewInterval);
}

void Game::refreshWorld(){
   // std::cerr << "ref\n";

    //qDebug("refreshing world due the timer");

  //PlayerStrategy::GetInstance()->SetKeys(keys);
  //keys.clear();



    //lalala

 // update();
  if(!widget->isHidden())
    widget->update();

}

void Game::on_StartGame_clicked()
{

    widget->show();
    initTimer();
   // qDebug("starting game\n");
  /*
    widget->InitMap(
                ui->HeigthBox->value(),
                ui->WidthBox->value(),
                5,
                ui->EnablePlayer->isChecked()
                );
*/
  //  if(ui->EnablePlayer->isChecked())
    {
        widget->activateWindow();
        //ui->SettingsBox->hide();
    }


}

void Game::on_WidthBox_valueChanged(int a)
{
    ui->SimpleBotsCount->setMaximum(a*ui->HeigthBox->value()/16);
    //ui->NeuroBotsCount->setMaximum(a*ui->HeigthBox->value()/16);
}

void Game::on_HeigthBox_valueChanged(int a)
{
    ui->SimpleBotsCount->setMaximum(a*ui->WidthBox->value()/16);
    //ui->NeuroBotsCount->setMaximum(a*ui->WidthBox->value()/16);
}

void Game::on_AddNeuroBots_clicked()
{
    //widget->AddNeuroBots(ui->NeuroBotsCount->value());
}

void Game::on_AddSimpleBots_clicked()
{
    widget->AddSimpleBots(ui->SimpleBotsCount->value());
}

void Game::on_AddPlayer_clicked()
{


   QFileDialog dialog;

   //dialog.setDirectory("E:\\Projects");
    dialog.setDirectory("E:\\Projects\\build-TankBot-Desktop_Qt_5_8_0_MSVC2015_64bit-Debug\\debug");
    QString fileName = dialog.getOpenFileName(
            this
          //      ,
          //  tr("Save Address Book"), "",
          //  tr("Address Book (*.abk);;All Files (*)")
                );
    qDebug(fileName.toStdString().c_str());
    qDebug("attemptAdding");
    widget->AddPlayer(fileName);
    qDebug("all seems good.Maybe");

}
