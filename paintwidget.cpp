#include <QStringRef>
#include "paintwidget.h"

using std::swap;

PaintWidget::PaintWidget(
        QWidget *parent,
        int _heigth,
        int _width,
        int _bots,
        bool player) : QWidget(parent)
{
    heigth = _heigth;
    width = _width;

    world = new World(_heigth,_width,_bots,player);
    resize((_heigth+9)*cellSize,(_width+2)*cellSize);
    move(0,0);

}

PaintWidget::~PaintWidget(){
    delete world;
}

void PaintWidget::paintEvent(QPaintEvent *event){



   // qDebug("updateing paintwidget");

    QPainter *painter = new QPainter(this);
    world->RefreshWorld();

  //  qDebug(std::to_string(heigth).c_str());
 //   qDebug(std::to_string(width).c_str());
    auto bitMap = world->GetBitMap();

    for(int i=0;i<bitMap.size();++i)
        for(int j=0;j<bitMap[i].size();++j){
            QString s = bitMap[i][j];
            QPoint position = QPoint(i,j);
            if(s[0] == 'T'){
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

                switch (s[1].toLatin1()) {

                case 'L':
                    break;
                case 'R':
                    for(int i=0;i<paintSize/2;++i)
                        for(int j=0;j<paintSize;++j)
                            swap(a[i][j],a[paintSize-i-1][j]);
                    break;
                case 'U':
                    for(int i=0;i<paintSize;++i)
                        for(int j=0;j<i;++j)
                            swap(a[i][j],a[j][i]);
                    break;
                case 'D':
                    for(int i=0;i<paintSize;++i)
                        for(int j=0;j<paintSize-i;++j)
                            swap(a[i][j],a[paintSize-j-1][paintSize-i-1]);
                    break;
                default:
                    break;
                }


                QPoint pPosition = QPoint(i,j);
                pPosition*=cellSize;
                QBrush brush;
                QColor color = QColor(QString::fromStdString(s.toStdString().substr(2,s.length()-2)));
                brush.setColor(color);
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

            }
            if(s[0] == 'W'){
                QBrush brush;
                brush.setColor(wallColor);
                painter->setBrush(brush);

                QPoint p = position*cellSize;
                QPainterPath path;
                QPointF a[4]= {
                    QPointF(p.x(),p.y()),
                    QPointF(p.x()+cellSize,p.y()),
                    QPointF(p.x()+cellSize,p.y()+cellSize),
                    QPointF(p.x(),p.y()+cellSize)
                };
                path.moveTo(a[3]);
                for(int i=0;i<4;++i)
                    path.lineTo(a[i]);
                painter->fillPath(path,QBrush(wallColor));
            }
            if(s[0]=='E'){
                QBrush brush;
                brush.setColor(wallColor);
                painter->setBrush(brush);

                QPoint p = position*cellSize;
                QPainterPath path;
                QPointF a[4]= {
                    QPointF(p.x(),p.y()),
                    QPointF(p.x()+cellSize,p.y()),
                    QPointF(p.x()+cellSize,p.y()+cellSize),
                    QPointF(p.x(),p.y()+cellSize)
                };
                path.moveTo(a[3]);
                for(int i=0;i<4;++i)
                    path.lineTo(a[i]);
                painter->fillPath(path,QBrush(backgroundColor));

            }
        }

    QString leaders = world->GetLeadersTable();
    auto le = leaders.split('\n');
    QPen pen = QPen(Qt::black);
    painter->setPen(pen);
    for(int i=0;i<le.size();++i)
        painter->drawText((heigth+2)*cellSize+ 10,width+10+cellSize*i,le[i]);


    auto bullets = world->GetBullets();
    for(auto bullet:bullets){

        QPen pen(bulletColor);
        QPoint position = bullet->GetPosition();
        QBrush brush(bulletColor);

        painter->setPen(pen);
        painter->setBrush(brush);
        int r = 3;
        QRectF rectangle(position.x()-r, position.y()-r, 2*r,2*r);
        painter->drawEllipse(rectangle);
    }


    delete painter;
}

void PaintWidget::ActivateWindow(){
    activateWindow();
}

void PaintWidget::InitMap(int _heigth,int _width,int _bots,bool player){
    if(world!=NULL)
        delete world;

    heigth = _heigth;
    width = _width;

    world = new World(_heigth,_width,_bots,player);
    resize((_heigth+9)*cellSize,(_width+2)*cellSize);
    move(0,0);

}


void PaintWidget::AddSimpleBots(int c){
    world->AddSimpleBots(c);
}

void PaintWidget::AddNeuroBots(int c){
    world->AddNeuroBots(c);
}

void PaintWidget::AddPlayer(QString s){
    qDebug("staring player on paintwidget");
    world->AddPlayer(s);
    qDebug("finishing player on paintwidget");
}
