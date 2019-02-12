#include "serializedgameview.h"

QDataStream &operator<<(QDataStream &s, GameView &view)
{
    qDebug() << "Save";
}

QDataStream &operator>>(QDataStream &s, GameView &view)
{
    qDebug() << "Load";
}
