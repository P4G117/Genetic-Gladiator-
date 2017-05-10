//
// Created by victork on 07/05/17.
//

#ifndef PATHFINDING_NODE_H
#define PATHFINDING_NODE_H

#include "Globales.h"


class Node {
private:
    // current position
    int rPos;
    int cPos;

    int GValue; /// total distance already travelled to reach the node
    int FValue; /// smaller FValue gets priority
public:
    Node(const Location &loc, int g, int f);//{}

    Location getLocation() const; //{
    //  return Location(rPos,cPos);
    //}

    int getGValue() const; //{
    //return GValue;
    //}
    int getFValue() const; //{
    //return FValue;
    //}

    void calculateFValue(const Location& locDest);//{
    //FValue = GValue + getHValue(locDest) * 10;
    //}

    // i: direction
    void updateGValue(const int & i);//{
    //GValue += (NDIR == 8 ? (i % 2 == 0 ? 10 : 14) : 10);
    //}

    // Estimation function for the remaining distance to the goal.
    const int & getHValue(const Location& locDest) const;//{
    /*static int rd, cd, d;
    rd = locDest.row - rPos;
    cd = locDest.col - cPos;

    // Euclidian Distance
    // d = static_cast<int>(sqrt((double)(rd*rd+cd*cd)));

    // Manhattan distance
    d = abs(rd) + abs(cd);

    // Chebyshev distance
    //d = max(abs(rd), abs(cd));

    return(d);*/
    //}

    // Determine FValue (in the priority queue)
    friend bool operator<(const Node & a, const Node & b){
    return a.getFValue() > b.getFValue();
    }

};


#endif //PATHFINDING_NODE_H
