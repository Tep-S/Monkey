#include "rules.h"


Rules::Rules()
{

}

MapRules::MapRules(){
    obj.setX(3);
    obj.setX(10);
    objCourse = 15;// 0..360
}

int MapRules::LoadRoad(){

}
float MapRules::DotDist(QPoint in1, QPoint in2){
    return sqrt(pow( (in1.x() - in2.x()) , 2) + pow( (in1.y() - in2.y()), 2));
}
int MapRules::FindRoad(){
    //get road
    QPoint road[10];
    int n = 10;
    float max = 1e10;
    int dot = 0;
    for(int i = 0; i < n; i++){
        int dist = DotDist(obj, road[i]);
        if ( dist < max ){
            max = dist;
            dot = i;
        }
    }
    return dot;
}
int MapRules::GoDot(QPoint dot){
    //push buttons forward

    //control direction
    float dCourse = 3;
    float dx = obj.x() - dot.x();
    float dy = obj.y() - dot.y();
    float goodCourse = atan2(dx, dy);
    if ( fabs(goodCourse - objCourse) < dCourse){
        //fine
    }else{
        //correct
    }

    //check distance
    float dist = DotDist(obj, dot);
    if ( distPrev - dist < 0){
        //fine
    }
    int delta = 10;
    if ( dist < delta){
        //get to the point
        return 1;
    }
    distPrev = dist;
}
