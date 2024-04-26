#include "Brick.h"

int Brick::getResistance() const { return _resistance; }

int Brick::getContainsBall() const { return _containsBall; }

void Brick::setResistance(int resistance) { _resistance = resistance; }

void Brick::setContainsBall(int containsBall) { _containsBall = containsBall; }
