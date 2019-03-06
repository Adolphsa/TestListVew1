#ifndef MYITEMDELEGATE_H
#define MYITEMDELEGATE_H

#include <QStyledItemDelegate>

class MyItemDelegate : public QStyledItemDelegate
{

public:
    MyItemDelegate(QObject *parent = nullptr);

    // painting
    void paint(QPainter *painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const Q_DECL_OVERRIDE;

    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const Q_DECL_OVERRIDE;


};

#endif // MYITEMDELEGATE_H
