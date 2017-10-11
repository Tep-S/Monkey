#include "rules.h"


Rules::Rules()
{

}

MapRules::MapRules(){
    obj.setX(3);
    obj.setX(10);
    objCourse = 15;// 0..360
}

void MapRules::Test(){
    const int n = 10;
    float c = 10;
    QPointF road[n];
    for(int i = 0 ; i < n; i++){
        float noise  = ((float)(rand() % 300)) / 100;
        float noise2 = ((float)(rand() % 300)) / 100;
        road[i].x() = c*i + noise;
        road[i].y() = c*i + noise2;
    }
    for(int i = 0; i < 10; i++);
        GoDot(road[0]);
}

void MapRules::AddRoad(){
    int clicked = 0;
    if(clicked){
        //get Mouse pos
        //add dot on image
        //save dot to file
    }
}

int MapRules::LoadRoad(){
    //not finished
    QSettings settings( "road.conf", QSettings::IniFormat );
    settings.beginGroup( "WINDOW_COORD" );
    int x1 = settings.value( "x",           -1 ).toInt();

}
float MapRules::DotDist(QPoinFt in1, QPointF in2){
    return sqrt(pow( (in1.x() - in2.x()) , 2) + pow( (in1.y() - in2.y()), 2));
}
int MapRules::FindRoad(){
    //get road
    QPointF road[10];
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

void MapRules::Move(){
    float gap = 1;
    float radCourse = objCourse*3.14/180;
    obj.setX(obj.x() + gap*sin(radCourse) );
    obj.setX(obj.y() + gap*cos(radCourse) );
}

int MapRules::GoDot(QPointF dot){
    //push buttons forward

    //control direction
    float dCourse = 3;
    float dx = obj.x() - dot.x();
    float dy = obj.y() - dot.y();
    float goodCourse = atan2(dx, dy);
    float diffCourse = goodCourse - objCourse;
    if ( fabs(diffCourse) > dCourse)
        objCourse += diffCourse / 2;

    Move();
    //check distance
    float dist = DotDist(obj, dot);
    if ( distPrev - dist < 0){
        //fine
    }
    int delta = 5;
    if ( dist < delta){
        //get to the point
        return 1;
    }
    distPrev = dist;
}
