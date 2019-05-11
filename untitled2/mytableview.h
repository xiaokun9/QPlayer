#ifndef MYTABLEVIEW_H
#define MYTABLEVIEW_H
#include <QTableView>
#include <QMouseEvent>
#include <qdebug.h>
#include <QMediaPlayer>

class MyTableView : public QTableView
{
//    Q_OBJECT
public:
    MyTableView(QWidget *parent = 0);
    QMediaPlayer *player;

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

signals:
//    void leftClicked(const QModelIndex &index);
//    void leftdoubleClicked();

};

#endif // MYTABLEVIEW_H
