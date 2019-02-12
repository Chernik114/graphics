#ifndef SERIALIZEDGAMEVIEW_H
#define SERIALIZEDGAMEVIEW_H

#include "gameview.h"

QDataStream& operator<<(QDataStream& s, GameView& view);
QDataStream& operator>>(QDataStream& s, GameView& view);

#endif // SERIALIZEDGAMEVIEW_H
