#pragma once

#include <stdio.h>

typedef enum Direction{
	DirectionLeft,
	DirectionTop,
	DirectionRight,
	DirectionBottom
}Direction;

Direction DirectionReverse(Direction d);
