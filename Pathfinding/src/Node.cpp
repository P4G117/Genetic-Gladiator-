#include "Node.h"

Node::Node(const Location &loc, int g, int f) {
    rPos = loc.row; cPos = loc.col; GValue = g; FValue = f;
}

Location Node::getLocation() const {
    return Location(rPos,cPos);
}

int Node::getGValue() const {
    return GValue;
}

int Node::getFValue() const {
    return FValue;
}

void Node::calculateFValue(const Location &locDest) {
    FValue = GValue + getHValue(locDest) * 10;
}

void Node::updateGValue(const int &i) {
    GValue += (NDIR == 8 ? (i % 2 == 0 ? 10 : 14) : 10);
}

const int& Node::getHValue(const Location &locDest) const {
    static int rd, cd, d;
    rd = locDest.row - rPos;
    cd = locDest.col - cPos;

    // Euclidian Distance
    // d = static_cast<int>(sqrt((double)(rd*rd+cd*cd)));

    // Manhattan distance
    d = abs(rd) + abs(cd);

    // Chebyshev distance
    //d = max(abs(rd), abs(cd));

    return(d);
}
