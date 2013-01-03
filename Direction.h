#pragma once

#include <stdio.h>

typedef enum Direction{
	DirectionLeft,
	DirectionTop,
	DirectionRight,
	DirectionBottom
}Direction;

Direction DirectionReverse(Direction d);

//dをr方向に向けたらどっち向きか(Topを前、Bottomを後ろとみなす)
Direction DirectionRotate(Direction d,Direction r);
