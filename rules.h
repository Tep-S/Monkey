#ifndef RULES_H
#define RULES_H

#include <math.h>
#include "QPoint"

class Rules
{
public:
    Rules();
};

class MapRules
{
public:
    MapRules();
private:
    QPoint obj;
    float objCourse;
    int LoadRoad();
    int FindRoad();
    //
    int GoDot(QPoint dot);
    float distPrev;
    float DotDist(QPoint in1, QPoint in2);
};

#endif // RULES_H
