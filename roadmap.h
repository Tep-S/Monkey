#ifndef ROADMAP_H
#define ROADMAP_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>

#include "sequence.h"

using namespace cv;

class Roadmap
{
public:
    Roadmap(Sequence* seqIn);
private:
    Sequence* seq;
    Mat drawedMap;
    std::vector<Point> corner;
    std::vector<Point> roadDot;
    void Color2Vertex();
    void Color2Road();
    void Vertex2Road();
    bool InLOS(Point a, Point b);
};



#endif // ROADMAP_H
