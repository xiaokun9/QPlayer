#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    playlist = new QMediaPlaylist;
    m_accessManager = new QNetworkAccessManager(this);
    QObject::connect(m_accessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(finishedSlot(QNetworkReply*)));
    model = new QStandardItemModel();
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QNetworkRequest *request = new QNetworkRequest();
    request->setUrl(QUrl("http://www.hanmaidj.com/mc/nv/hits/1/"));
    m_accessManager->get(*request);
}
void MainWindow::finishedSlot(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
#if 0
        QByteArray bytes = reply->readAll();
        // qDebug()<<bytes;
        QString string = QString::fromUtf8(bytes);
        qDebug()<<string;
        //ui->textBrowser->setText(string.toUtf8());
        ui->textBrowser->setText(string);
#endif
        QTextCodec *codec = QTextCodec::codecForName("GBK");
        //使用utf8编码, 这样可以显示中文
        QByteArray bytes = reply->readAll();
        QString str = codec->toUnicode(bytes);
        QFile out_file("test.html");
        if(out_file.open(QIODevice::WriteOnly))
        {
            QTextStream out(&out_file);
            out<<str;
        }
        //QString pattern = "class=\"mname\" title='(.*)'>";
        //QRegularExpression dateRegex("class=\"mname\" title='(.*)'>");

        //href=/mc/nv/([0-9]+)/ class=\"mname\" title='(.*)'>
        QRegularExpression dateRegex("href=/mc/nv/([0-9]+)/ class=\"mname\" title='(.*)'>");
        QRegularExpressionMatchIterator dateItr = dateRegex.globalMatch(str);
        int mouch=0;
        //QStringList strList;

        QStringList labels = QObject::trUtf8("女麦,ID").simplified().split(",");
        model->setHorizontalHeaderLabels(labels);
        //定义item
        QStandardItem* item1;
        QStandardItem* item2;
        while (dateItr.hasNext())
        {
            QRegularExpressionMatch match = dateItr.next();
            if (match.hasMatch())
            {
                //strList.append(match.captured(1));
                item1 = new QStandardItem(QString("%1").arg(match.captured(2)));
                item2 = new QStandardItem(QString("%1").arg(match.captured(1)));
                model->setItem(mouch,0,item1);
                model->setItem(mouch,1,item2);
                mouch++;
                qDebug() << "date:" <<mouch<< match.captured(2);
            }
        }
        // QStringListModel *m_model=new QStringListModel(strList);
        //ui->tableView->setModel(m_model);
        // ui->tableView->setShowGrid(true);

        //        for(int i = 0;i < 10;i++){
        //            item = new QStandardItem(QString("%1").arg(i));
        //            model->setItem(i,0,item);
        ////            item = new QStandardItem(QString("%1").arg(i*2));
        ////            model->setItem(i,1,item);
        ////            item = new QStandardItem(QString("%1").arg(i*3));
        ////            model->setItem(i,2,item);
        //        }
        ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        ui->tableView->setModel(model);
        ui->tableView->setSelectionBehavior ( QAbstractItemView::SelectRows); //设置选择行为，以行为单位
        ui->tableView->setSelectionMode ( QAbstractItemView::SingleSelection); //设置选择模式，选择单行
        ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
       // ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked);
        ui->tableView->show();

        QRegularExpression dateRegex_p("(/mc/nv/hits/[0-9]+/)'>(.*)</option>");
        QRegularExpressionMatchIterator dateItr_p = dateRegex_p.globalMatch(str);
        while (dateItr_p.hasNext())
        {
            QRegularExpressionMatch match_P = dateItr_p.next();
            if (match_P.hasMatch())
            {
                //item = new QStandardItem(QString("%1").arg(match.captured(2)));
                qDebug()<<match_P.captured(1);
                QVariant var;
                var.setValue(match_P.captured(1));
                ui->comboBox->addItem(match_P.captured(2),var);
            }
        }
        reply->deleteLater();//最后要释放replay对象
    }
    else
    {
        qDebug()<<"handle errors here";
        QVariant statusCodeV = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
        //statusCodeV是HTTPserver的对应码，reply->error()是Qt定义的错误码，能够參考QT的文档
        qDebug( "found error ....code: %d %d\n", statusCodeV.toInt(), (int)reply->error());
        qDebug(qPrintable(reply->errorString()));
    }
    reply->deleteLater();
}


void MainWindow::on_pushButton_2_clicked()
{
    playlist->addMedia(QUrl::fromLocalFile("http://p.hanmaidj.com:700/770551120/hanmaidj_com/女麦/MC佳瑶 小苹果dj.mp3"));
    playlist->addMedia(QUrl::fromLocalFile("http://p.hanmaidj.com:700/770551120/hanmaidj_com/2014/06/201406MC佳瑶 小苹果dj.mp3"));
    playlist->addMedia(QUrl::fromLocalFile("http://p.hanmaidj.com:700/770551120/hanmaidj_com/女麦/MC小月 一声兄弟 一生兄弟.mp3"));
    playlist->setCurrentIndex(1);

    player = new QMediaPlayer;
    player->setPlaylist(playlist);
    qDebug()<<player->volume();
    player->setVolume(50);

    player->play();
}


//下拉选择框
void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    qDebug()<<arg1;
    qDebug()<<ui->comboBox->currentData().toString();
    model->removeRows(0,model->rowCount());

}


