#ifndef MYLISTITEMDATA_H
#define MYLISTITEMDATA_H

#include <QMetaType>

typedef struct {
    QString imgPath;
    QString nameText;
    QString infoText;
} MyListItemData;

Q_DECLARE_METATYPE(MyListItemData)

#endif // MYLISTITEMDATA_H
