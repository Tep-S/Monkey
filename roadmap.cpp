#include "roadmap.h"


Roadmap::Roadmap(Sequence *seqIn)
{
    seq = seqIn;
    drawedMap = imread("smth.jpg");
}

struct RoadInfo{
    int vertexNum;
    double dist;
};

struct VertexInfo{
    int num;
    Point xy;
    std::vector<RoadInfo> road;
};

void Roadmap::Color2Vertex(){
    Scalar lowGreen, highGreen;
    Mat out;
    out = seq->ColorMask(drawedMap, lowGreen, highGreen);
    for(int i = 0; i < out.rows; i+=3){
        for(int j = 0; j < out.cols; j+=3){
            if (out.at<int>(i,j,0) > 0){//need to check how to call element
                corner.push_back(Point(i,j));
            }
        }
    }
}

bool Roadmap::InLOS(Point a, Point b){
    std::vector<Point> local;
    double l = norm(a-b);
    double dxy[2] = {std::abs(a.x - b.x) / l, std::abs(a.y - b.y) / l};
    int board = (dxy[0] > dxy[1]) ? 0:1;
    double xyD[2] = {(double)a.x, (double)a.y};
    int    xyI[2] = {a.x, a.y};
    for(double dl = 0.0; dl < l; l+=1.0){
        int addDot = 0;
        for(int i = 0; i < 2; i++)
            xyD[i] += dxy[i];
        for(int i = 0; i < 2; i++){
            if (std::round(xyD[i]) != xyI[2]){
                xyI[i] = std::round(xyD[i]);
                addDot++;
            }
        }
        if (addDot)
            local.push_back(Point(xyI[0], xyI[1]));
    }
    return 1;
}

void Roadmap::Vertex2Road(){
    VertexInfo myVertex;
    std::vector<VertexInfo> testVertex;
    for(int i = 0; i < testVertex.size(); i++){
        bool theSame = (myVertex.num == testVertex[i].num);
        bool visible = InLOS(myVertex.xy, testVertex[i].xy);
        if( !theSame && visible){
            //double dist = sqrt( pow(myVertex.xy.x - testVertex[i].xy.x, 2.0) + pow(myVertex.xy.y - testVertex[i].xy.y, 2.0));
            double dist = norm(myVertex.xy - testVertex[i].xy);
            RoadInfo localRoad;
            localRoad.vertexNum = i;
            localRoad.dist = dist;
            myVertex.road.push_back(localRoad);
        }
    }

}
