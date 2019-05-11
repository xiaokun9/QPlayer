#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTextCodec>
#include <QFile>
#include <QTextStream>
#include <QRegExp>
#include <QStringListModel>
#include <QStandardItemModel>
#include <QTreeWidgetItem>
#include <QMouseEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QMediaPlaylist *playlist;
    QMediaPlayer *player;
    QNetworkAccessManager *m_accessManager;
    QStandardItemModel* model;

private slots:
    void on_pushButton_clicked();
    void finishedSlot(QNetworkReply *reply);

    void on_pushButton_2_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
