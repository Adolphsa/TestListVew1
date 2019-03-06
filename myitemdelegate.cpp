#include "myitemdelegate.h"
#include "mylistitemdata.h"
#include <QPainter>
#include <QDebug>

MyItemDelegate::MyItemDelegate(QObject *parent) : QStyledItemDelegate(parent)
{

}

void MyItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.isValid())
    {
        painter->save();
        QVariant var = index.data(Qt::UserRole+1);
        MyListItemData itemData = var.value<MyListItemData>();

        // 矩形区域
        QRectF rect;
        rect.setX(option.rect.x());
        rect.setY(option.rect.y());
        rect.setWidth(option.rect.width()-1);
        rect.setHeight(option.rect.height()-1);


        QPainterPath path;
        path.moveTo(rect.topRight());
        path.lineTo(rect.topLeft());
        path.lineTo(rect.bottomLeft());
        path.lineTo(rect.bottomRight());
        path.lineTo(rect.topRight());


        // 鼠标悬停或者选中时改变背景色
        if (option.state.testFlag(QStyle::State_MouseOver)) {
            painter->setPen(QPen(QColor("#ebeced")));
            painter->setBrush(QColor("#ebeced"));
            painter->drawPath(path);
        }
        if (option.state.testFlag(QStyle::State_Selected)) {
            painter->setPen(QPen(QColor("#e3e3e5")));
            painter->setBrush(QColor("#e3e3e5"));
            painter->drawPath(path);
        }

        // 绘制图片，姓名，信息位置区域
        QRectF iconRect = QRect(rect.left()+5, rect.top()+5, 80, 80);
        QRectF nameTextRect = QRect(iconRect.right()+20, iconRect.top(), rect.width()-10-iconRect.width(), 30);
        QRectF infoTextRect = QRect(nameTextRect.left(), nameTextRect.bottom()+10, rect.width()-10-iconRect.width(), 30);

        painter->drawImage(iconRect, QImage(itemData.imgPath));
        painter->setPen(QPen(Qt::black));
        painter->setFont(QFont("黑体", 20));
        painter->drawText(nameTextRect, itemData.nameText);

        painter->setPen(QPen(Qt::gray));
        painter->setFont(QFont("Microsoft Yahei", 10));
        painter->drawText(infoTextRect, itemData.infoText);

        painter->restore();

    }
}

QSize MyItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index)
    return QSize(option.rect.width(), 100);
}
