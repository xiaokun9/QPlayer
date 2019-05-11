#include "mytableview.h"

MyTableView::MyTableView(QWidget *parent):QTableView(parent)
{
     player = new QMediaPlayer;
     qDebug()<<player->volume();
     player->setVolume(30);
}


void MyTableView::mousePressEvent(QMouseEvent *event)
{
   if(event->button()==Qt::LeftButton)
   {
       setCurrentIndex(QModelIndex());
       QTableView::mousePressEvent(event);
       QModelIndex index=currentIndex();
       if(index.row()<0&&index.column()<0)
           return;
       //emit leftClicked(index);
      // qDebug()<<"左击一下";
   }
}
void MyTableView::mouseDoubleClickEvent(QMouseEvent *event)
{
    //"http://p.hanmaidj.com:700/770551120/hanmaidj_com/女麦/MC小月 一声兄弟 一生兄弟.mp3"
    if(event->button()==Qt::LeftButton)
    {
        qDebug()<<this->currentIndex().data().toString();
        QString temp="http://p.hanmaidj.com:700/770551120/hanmaidj_com/女麦/"\
                +this->currentIndex().data().toString()+".mp3";
        player->setMedia(QMediaContent(QUrl::fromLocalFile(temp)));
        player->play();
        qDebug()<<"左击两下";
        qDebug()<<this->columnWidth(0);
        //emit leftdoubleClicked();
    }
}
