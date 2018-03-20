#include "settings.h"

Settings::Settings()
{

}

struct Rectangle{
    int xy[2];
    int xySize[2];
};

struct Aim{
    int goals;
    int ready;
};

struct Goal{
    int xy[2];
    int move;
    int visible;
};

void Settings::Load(){
    QSettings settings( "coord.conf", QSettings::IniFormat );
    settings.beginGroup( "WINDOW_COORD" );
#if 0
    int x1 = settings.value( "x",           -1 ).toInt();
    int y1 = settings.value( "y",           -1 ).toInt();
    int xSize1 = settings.value( "xSize",   -1 ).toInt();
    int ySize1 = settings.value( "ySize",   -1 ).toInt();

    settings.beginGroup( "MAP_COORD" );
    int x = settings.value( "x",            -1 ).toInt();
    int y = settings.value( "y",            -1 ).toInt();
    int xSize = settings.value( "xSize",    -1 ).toInt();
    int ySize = settings.value( "ySize",    -1 ).toInt();

    settings.beginGroup( "TIMINGS" );
    int startSkeep = settings.value( "startSkeep",      -1 ).toInt();
    float recharge = settings.value( "recharge",        -1 ).toFloat();
    float aimReady = settings.value( "aimReady",        -1 ).toFloat();
    float changeGoal = settings.value( "changeGoal",    -1 ).toFloat();
#endif
    //settings.beginGroup( "PATTERN_IMAGES" );
    //color and images

}

void Settings::LoadLogic(){

}
