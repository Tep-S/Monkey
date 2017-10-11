#ifndef RULES_H
#define RULES_H

#include <math.h>
#include "QPoint"
#include "QPointF"

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
    void Move();
    void Test();
    QPointF obj;
    float objCourse;
    void AddRoad();
    int LoadRoad();
    int FindRoad();
    //
    int GoDot(QPointF dot);
    float distPrev;
    float DotDist(QPointF in1, QPointF in2);
};

#endif // RULES_H
