#include <QStandardItemModel>
#include <QObject>
#include <QDebug>
#include <QTime>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mylistitemdata.h"
#include "myitemdelegate.h"

const QStringList icons = {
    ":/images/dog1.jpg", ":/images/dog2.jpg", ":/images/dog3.jpg",
    ":/images/dog4.jpg", ":/images/dog5.jpg"
};
const QStringList names = {
    "哈士奇A", "哈士奇B", "拉拉",
    "多多", "德牧",
};

const QStringList infoes = {
    "哈士奇A小时候被捧起来的样子", "哈士奇B一窝小崽子", "拉拉好饿呀，叼起盆子就来吃饭",
    "多多笑容甜美动人", "德牧，你瞅我干啥，瞅你咋地",
};

// min:随机数的最小值，max:随机数的最大值
int generateRandomInteger(int min, int max)
{
    Q_ASSERT(min < max);
    // 加入随机种子。种子是当前时间距离0点0分0秒的秒数。
    // 每次启动程序，只添加一次种子，以做到数字真正随机。
    static bool seedStatus;
    if (!seedStatus)
    {
        qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
        seedStatus = true;
    }
    int nRandom = qrand() % (max - min);
    nRandom = min + nRandom;

    return nRandom;
}

QStandardItemModel *pModel;
MyItemDelegate *pItemDelegate;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //加号icon
    ui->addButton->setStyleSheet("border-image: url(:/images/add.png);");

    connect(ui->addButton, &QPushButton::pressed, [=](){
        ui->addButton->setStyleSheet("border-image:url(:/images/add2.png)");}
    );
    connect(ui->addButton, &QPushButton::released, [=](){
        ui->addButton->setStyleSheet("border-image:url(:/images/add.png)"); }
    );

    //减号icon
    ui->subtractButton->setStyleSheet("border-image: url(:/images/subtract.png);");
    connect(ui->subtractButton, &QPushButton::pressed, [=](){
        ui->subtractButton->setStyleSheet("border-image:url(:/images/subtract2.png)");}
    );
    connect(ui->subtractButton, &QPushButton::released, [=](){
        ui->subtractButton->setStyleSheet("border-image:url(:/images/subtract.png)"); }
    );


        pModel = new QStandardItemModel();
        for (int i=0; i<2; ++i) {
            QStandardItem *pItem = new QStandardItem;
            MyListItemData itemData;
            itemData.nameText = names.at(i);
            itemData.infoText = infoes.at(i);
            itemData.imgPath = icons.at(i);
            pItem->setData(QVariant::fromValue(itemData), Qt::UserRole+1);
            pModel->appendRow(pItem);

        }

        pItemDelegate = new MyItemDelegate(this);
        ui->listView->setItemDelegate(pItemDelegate);
        ui->listView->setModel(pModel);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addButton_clicked()
{
    QString str("加号");
    qDebug() << str;

    int randNum = generateRandomInteger(0,10);
    qDebug() << randNum;

    QStandardItem *pItem = new QStandardItem;
    MyListItemData itemData;
    itemData.nameText = names.at(randNum%5);
    itemData.infoText = infoes.at(randNum%5);
    itemData.imgPath = icons.at(randNum%5);
    pItem->setData(QVariant::fromValue(itemData), Qt::UserRole+1);
    pModel->appendRow(pItem);

    qDebug() << ui->listView->model()->rowCount();

}

void MainWindow::on_subtractButton_clicked()
{
    QString str("减号");
    qDebug() << str;
    qDebug() << ui->listView->model()->rowCount();

    pModel->removeRow(ui->listView->model()->rowCount()-1);
}


