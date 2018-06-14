#include "sequence.h"
//#include "opencv2/opencv_modules.hpp"
#include "opencv2/objdetect.hpp"
#include <QDir>

using namespace cv;
using namespace std;

Sequence::Sequence(){
    cmdCnt = 0;
}

void Sequence::ImgAct(int command, float* par, cv::Mat& outImg){
   // cv::Mat img;
    enum{
        Do_Gray,
        Do_Thresh,
        Do_Canny,
        Do_Contours,
        Do_Bgr2Hsv,
        Do_Blur,
        Do_Hsv2Bgr
    };
   // int lens[6] = {0, 2, 3, 0};

    switch(command){
    case Do_Gray:{
        cv::cvtColor(img, outImg, CV_BGR2GRAY);
    }
        break;
    case Do_Thresh:{
        //need gray in
        threshold( img, img, (int)par[0], (int)par[1], CV_THRESH_BINARY );//p1 20 p2 150
    }
        break;
    case Do_Canny:{
        cv::Canny( img, outImg, par[0], par[1], 3 );//check param!
    }
        break;
    case Do_Contours:{
       // vector<vector<Point> > contours;
       // vector<Vec4i> hierarchy;
        //need canny before
       // findContours( img, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
    }
        break;
    case Do_Bgr2Hsv:{
        cv::cvtColor(img, img, CV_BGR2HSV);
    }
        break;
    case Do_Blur:{
        //src gray?
   //     cv::blur( img, img, Size(3,3));
    }
        break;
    case Do_Hsv2Bgr:{
        cv::cvtColor(img, img, CV_HSV2BGR);
    }
        break;
    }

}

void Sequence::SobelDir(){
    Mat img = imread( "log/cat.jpg", IMREAD_GRAYSCALE );
    //Mat img = imread( "log/furr.png", IMREAD_GRAYSCALE );
    Mat imgBlur, imgErode, xDer, yDer, xySobel, angleDir, absX, absY;
    GaussianBlur(img, imgBlur, Size(31,31), 0, 0, BORDER_DEFAULT);

    //int erosion_size = 6;
    //Mat element = getStructuringElement( MORPH_RECT,Size( 2*erosion_size + 1, 2*erosion_size+1 ),Point( erosion_size, erosion_size ) );
    //dilate(imgBlur, imgErode, element);
    namedWindow("erode", 1);
    imshow("erode", imgBlur);
   // int morph_elem = 0;
   // int morph_size = 7;//2
   // Mat element = getStructuringElement( morph_elem, Size( 2*morph_size + 1, 2*morph_size+1 ), Point( morph_size, morph_size ) );
   //morphologyEx(img, imgBlur, CV_MOP_OPEN, element);

    Sobel(imgBlur, xDer, CV_32FC1, 1, 0);
    Sobel(imgBlur, yDer, CV_32FC1, 0, 1);
    convertScaleAbs( xDer, absX);
    convertScaleAbs( yDer, absY);
    addWeighted( absX, 0.5, absY, 0.5, 0, xySobel );
    namedWindow("grad", 1);
    imshow("grad", xySobel);
    //namedWindow("grad2", 1);
    //imshow("grad2", absY);

}

void Sequence::Haar(){
    String face_cascade_name = "log/cascade_tank2.xml";
    CascadeClassifier face_cascade;
    if( !face_cascade.load( face_cascade_name ) ){ qInfo("--(!)Error loading face cascade\n"); return; };
    QString mainPath = "C:/Users/Sam/Desktop/autoscreens2/tank/orig/tank_train/";
    QDir folder(mainPath);
    folder.setNameFilters(QStringList()<<"*.jpeg");
    QStringList fileList = folder.entryList();
    for(int i = 0; i < fileList.size(); i++){
        QString tempPath = mainPath + (QString)fileList.at(i);
        Mat frame = imread(tempPath.toStdString().c_str());
        if (frame.empty()){
            qInfo("no image");
            return;
        }
        Mat frame_gray;
        cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
        std::vector<Rect> faces;
        equalizeHist( frame_gray, frame_gray );
        face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30) );
        for ( size_t i = 0; i < faces.size(); i++ ){
            Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
            ellipse( frame, center, Size( faces[i].width/2, faces[i].height/2 ), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );
           // Mat faceROI = frame_gray( faces[i] );
        }
        namedWindow("haar");
        imshow( "haar", frame );
        char c = (char)waitKey(50);
        if( c == 27 ) { break; } // escape
    }
}

void CheckBorder(int* param, int* val, int step){
    for(int i = 0; i < 3; i++){
        int stepT = (i == 0) ? step : step*5;
        param[i] = val[i] + step;
        if(param[i] > 255)
            param[i] = 255;
        if(param[i] < 0)
            param[i] = 0;
    }
}

int BigContourIdx(std::vector<std::vector<cv::Point>> contours){
    int biggestContourIdx = -1;
    float biggestContourArea = 0;
    //Mat drawing = Mat::zeros( hsvMask.size(), CV_8UC3 );
    Scalar color = Scalar(255, 0, 0);
    for( int i = 0; i< contours.size(); i++ ){
        //drawContours( drawing, contours, i, color, 1, 8, hierarchy, 0, cv::Point() );
        float ctArea= contourArea(contours[i]);
        if(ctArea > biggestContourArea){
            biggestContourArea = ctArea;
            biggestContourIdx = i;
        }
    }
    return biggestContourIdx;
}

// comparison function object
bool compareContourAreas ( std::vector<cv::Point> contour1, std::vector<cv::Point> contour2 ) {
    double i = fabs( cv::contourArea(cv::Mat(contour1)) );
    double j = fabs( cv::contourArea(cv::Mat(contour2)) );
    return ( i < j );
}

cv::Vec3b Sequence::PixHsv(cv::Mat in, cv::Point pix){
    Mat inTemp = in(Rect(pix.x, pix.y,1,1));
    Mat hsv;
    cvtColor(inTemp, hsv, COLOR_BGR2HSV);
    Vec3b pixel = hsv.at<Vec3b>(0, 0);
    return pixel;
}

cv::Mat Sequence::ColorMask2(cv::Mat in, cv::Vec3b hsvDel, int colorWide){
    qInfo("%d %d %d", hsvDel.val[0], hsvDel.val[1], hsvDel.val[2]);
    int hsvPixel[3] = {hsvDel.val[0], hsvDel.val[1], hsvDel.val[2]};
    int low[3], high[3];
    int step = colorWide;
    CheckBorder(low, hsvPixel, -step);
    CheckBorder(high, hsvPixel, step);

    Mat hsv, hsvMask, hsvM1, hsvM2;
    cvtColor(in, hsv, COLOR_BGR2HSV);
    inRange(hsv, Scalar(low[0], low[1], low[2]), Scalar(high[0], high[1], high[2]), hsvMask);
    //inRange(hsv, Scalar(low[0], 0, 0), Scalar(high[0], 255, 255), hsvMask);
    //inRange(hsv, Scalar(0, 0, 0), Scalar(15, 255, 255), hsvM1);
    //inRange(hsv, Scalar(165, 0, 0), Scalar(180, 255, 255), hsvM2);
   // bitwise_or(hsvM1, hsvM2, hsvMask);
    imshow("inmask", hsvMask);
    //imwrite("log/point.jpg",hsvMask);
    return hsvMask;
}
/*
void DeleteColor(cv::Mat in, cv::Point pix){
    cv::Mat gray, maskInv, out;
    cv::Vec3b hsvDel = PixHsv(in, pix);
    cv::Mat mask = ColorMask2(in, hsvDel);
    cv::bitwise_not(mask, maskInv);
    cv::cvtColor(in, gray, cv::COLOR_BGR2GRAY);
    cv::bitwise_and(gray, gray, out, maskInv);
}*/

void Sequence::DrawRotRect(cv::Mat image, std::vector<cv::Point> contours){
    RotatedRect rRect = minAreaRect(contours);
    Point2f points[4];
    rRect.points(points);
    for(int i = 0; i < 4; ++i)
        line(image, points[i], points[(i+1)%4], cv::Scalar(255,255,255), 2);
}

Point Sequence::FindTarget(Mat in){
    Mat edge, inRoiGray;
   // Mat in = imread( "log/la2_2.jpg", IMREAD_GRAYSCALE);
    int croppX = in.cols/6;
    int croppY = in.rows/6;
    Point croppPoint(croppX, croppY);
    Mat inRoi = in(Rect(croppX, croppY, in.cols - croppX*2, in.rows - croppY*2));
    qInfo("roi %d %d", inRoi.cols, inRoi.rows);
    cvtColor(inRoi, inRoiGray, COLOR_BGR2GRAY);


        Canny(inRoi,edge,50, 500);
        int morph_elem = 0;
        int morph_size = 2;
        Mat element = getStructuringElement( morph_elem, Size( 2*morph_size + 1, 2*morph_size+1 ), Point( morph_size, morph_size ) );
        morphologyEx(edge, edge, CV_MOP_CLOSE, element);
        vector<vector<Point>> contours;
        std::vector<cv::Vec4i> hierarchy;
        findContours(edge,contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
        sort(contours.begin(), contours.end(), compareContourAreas);

        for(int i = 0; i < contours.size(); i++)
            DrawRotRect(edge, contours[i]);

       // for(int i  = 0; i < contours.size(); i++)
            RotatedRect rRect = minAreaRect(contours[contours.size()/2]);
            Point2f points[4];
            rRect.points(points);
            int xAvg(0), yAvg(0);
            for(int i = 0; i < 4; ++i){
                xAvg += points[i].x;
                yAvg += points[i].y;
            }
            Point retPoint = Point(xAvg/4, yAvg/4);
       // }


        circle(edge, retPoint, 30, Scalar(255, 255, 255));
        namedWindow("edge", CV_WINDOW_AUTOSIZE);
        imshow("edge",edge);
        waitKey(1000);
        qInfo("point %d %d cropp %d %d", retPoint.x, retPoint.y, croppPoint.x, croppPoint.y);
        return retPoint + croppPoint;
}

int Sequence::GetHP(Point pix){
    int debug = 1;

   // Mat in = imread( "log/statusbar.jpg");
    Mat inBig = imread( "log/la2.jpg");//613 46 763 55
    //Mat in2 = imread( "log/rainbow.png");//613 46 763 55
    Mat in = inBig(Rect(610,41, 767 - 610, 60 - 41));
    Mat inClust = ImgKmeans(in);
    namedWindow("in", CV_WINDOW_AUTOSIZE);
    imshow("in",inClust);
    Vec3b hsvDel = PixHsv(inClust, Point(29,9));
    Mat hsvMask = ColorMask2(inClust, hsvDel, 15);
    /***********
    for(int i = 0; i < 25; i++){
        Mat rgb;
        Mat hsv(1,1, CV_8UC3, Scalar(i*10,255,255));
        cvtColor(hsv, rgb, COLOR_HSV2BGR);
        circle(inBig, Point(200,200), 50, Scalar(rgb.data[0], rgb.data[1], rgb.data[2]), 20);
        namedWindow("raw");
        imshow("raw",inBig);
        waitKey(200);
    }
    return 0;*/
    //Vec3b hsvPix = PixHsv(in2, Point(1600,150));
   /* if(debug){
        for(int i = 0; i < 240; i++){
            //Mat hsvMask2 = ColorMask2(in2, hsvPix, 30);
            Mat hsv, hsvMask2;
            cvtColor(in, hsv, COLOR_HSV2BGR);
            inRange(hsv, Scalar(i*1, 0, 0), Scalar((i+10)*1, 255, 255), hsvMask2);
            qInfo("hue %d ", i*1);
            namedWindow("red", CV_WINDOW_AUTOSIZE);
            imshow("red",hsvMask2);
            waitKey(200);
        }
        return 0;

    }*/
        namedWindow("red", CV_WINDOW_AUTOSIZE);
        imshow("red",hsvMask);
        waitKey(0);
    vector<vector<Point>> contours;
        findContours(hsvMask,contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
        Mat drawing = Mat::zeros( hsvMask.size(), CV_8UC3 );
        sort(contours.begin(), contours.end(), compareContourAreas);
        DrawRotRect(drawing, contours[contours.size()-1]);

       // RotatedRect rRect = minAreaRect(contours[biggestContourIdx]);
       // cv::Point2f points[4];
        //rRect.points(points);
        int minX = 10000;
        int maxX = 0;
        /*for(int i = 0; i < 4; ++i){
            if (points[i].x > maxX)
                maxX = points[i].x;
            if (points[i].x < minX)
                minX = points[i].x;
            if(debug)
                line(drawing, points[i], points[(i+1)%4], cv::Scalar(0,0,255), 2);
        }*/
        qInfo("min %d max %d", minX, maxX);
        if(debug){
        //drawContours( drawing, contours, biggestContourIdx, color, 1, 8, hierarchy, 0, cv::Point() );
            namedWindow("contour", CV_WINDOW_KEEPRATIO);
            imshow("contour",drawing);
        }
        return (maxX - minX + 1);
}

void Sequence::GetHP_MP(){
    double recLong[3];
    recLong[0] = GetHP(Point(76,18));
    recLong[1] = GetHP(Point(76,49));
    recLong[2] = GetHP(Point(76,80));
    qInfo("%.f %.f %.f", recLong[0]/197*50, recLong[1]/197*1000, recLong[2]/197*204);

}

void Sequence::FindRect(cv::Mat input){
    Mat in = imread( "log/la2.jpg");//, IMREAD_GRAYSCALE );
    /*Mat inGray;
    cvtColor(in, inGray, COLOR_BGR2GRAY);
    Rect roi(inGray.cols/2 - 150,23,300,inGray.rows/10);
    Mat inGrayCrop = inGray(roi);
    Mat thresh, contours;
    threshold(inGrayCrop,thresh,150,255,THRESH_BINARY);
    namedWindow("thresh");
    imshow("thresh", thresh);
    //Canny(thresh,contours,100,250);
    //namedWindow("canny");
    //imshow("canny", contours);
*/
    Mat inHSV;
    cvtColor(in, inHSV, COLOR_BGR2HSV);
    Rect roi2(inHSV.cols/2 - 150,23,300,inHSV.rows/10);
    Mat inHsvCrop = inHSV(roi2);

    Mat redMask, redBGR;
    Vec3b pixel = inHSV.at<Vec3b>(161,68);
    inRange(inHSV, cv::Scalar(0,140,150), cv::Scalar(30,255,200), redMask);
    namedWindow("allout");
    imshow("allout", in);
    namedWindow("redout");
    imshow("redout", redMask);


    waitKey(0);
    //imshow("smth", inCropped);

}

cv::Mat Sequence::ColorMask(cv::Mat input, cv::Scalar low, cv::Scalar high){
    Mat imgHSV;
    Mat imgThresholded;

    //Convert the captured frame from BGR to HSV
    cvtColor(input, imgHSV, COLOR_BGR2HSV);

    //Threshold the image
    inRange(imgHSV, low, high, imgThresholded);

    //morphological opening (remove small objects from the foreground)
    erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
    dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
    return imgThresholded;
}

Mat Sequence::ImgKmeans(Mat src){
    //Mat src = imread( "log/map_tank.jpg", 1 );
    Mat samples(src.rows * src.cols, 3, CV_32F);
    for( int y = 0; y < src.rows; y++ )
      for( int x = 0; x < src.cols; x++ )
        for( int z = 0; z < 3; z++)
          samples.at<float>(y + x*src.rows, z) = src.at<Vec3b>(y,x)[z];


    int clusterCount = 2;
    Mat labels, centers;
    int attempts = 5;
    kmeans(samples, clusterCount, labels, TermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS, 10000, 0.0001), attempts, KMEANS_PP_CENTERS, centers );


    Mat new_image( src.size(), src.type() );
    for( int y = 0; y < src.rows; y++ )
      for( int x = 0; x < src.cols; x++ ){
        int cluster_idx = labels.at<int>(y + x*src.rows,0);
        for( int z = 0; z < 3; z++)
            new_image.at<Vec3b>(y,x)[z] = centers.at<float>(cluster_idx, z);
      }
    return new_image;
    //imshow( "clustered image", new_image );
    //waitKey( 0 );
}

void Sequence::KmeansTest(){
        const int MAX_CLUSTERS = 5;
        Scalar colorTab[] =
        {
            Scalar(0, 0, 255),
            Scalar(0,255,0),
            Scalar(255,100,100),
            Scalar(255,0,255),
            Scalar(0,255,255)
        };
        Mat img(500, 500, CV_8UC3);
        RNG rng(12345);
        for(;;)
        {
            int k, clusterCount = rng.uniform(2, MAX_CLUSTERS+1);
            int i, sampleCount = rng.uniform(1, 1001);
            Mat points(sampleCount, 1, CV_32FC2), labels;
            clusterCount = MIN(clusterCount, sampleCount);
            Mat centers;
            /* generate random sample from multigaussian distribution */
            for( k = 0; k < clusterCount; k++ )
            {
                Point center;
                center.x = rng.uniform(0, img.cols);
                center.y = rng.uniform(0, img.rows);
                Mat pointChunk = points.rowRange(k*sampleCount/clusterCount,
                                                 k == clusterCount - 1 ? sampleCount :
                                                 (k+1)*sampleCount/clusterCount);
                rng.fill(pointChunk, RNG::NORMAL, Scalar(center.x, center.y), Scalar(img.cols*0.05, img.rows*0.05));
            }
            randShuffle(points, 1, &rng);
            kmeans(points, clusterCount, labels,
                TermCriteria( TermCriteria::EPS+TermCriteria::COUNT, 10, 1.0),
                   3, KMEANS_PP_CENTERS, centers);
            img = Scalar::all(0);
            for( i = 0; i < sampleCount; i++ )
            {
                int clusterIdx = labels.at<int>(i);
                Point ipt = points.at<Point2f>(i);
                circle( img, ipt, 2, colorTab[clusterIdx], FILLED, LINE_AA );
            }
            imshow("clusters", img);
            char key = (char)waitKey();
            if( key == 27 || key == 'q' || key == 'Q' ) // 'ESC'
                break;
}
}

void Sequence::MotionMask(cv::Mat input, cv::Mat outputMask){
    Mat in = imread( "log/rural/rural1.jpg");
    Mat inHSV;
    cvtColor(in, inHSV, COLOR_BGR2HSV);


    Mat redMask, redBGR;
    Vec3b pixel = inHSV.at<Vec3b>(357,331);
    int hsvPixel[3] = {pixel.val[0], pixel.val[1], pixel.val[2]};
    int low[3], high[3];
    int step = 15;
    CheckBorder(low, hsvPixel, -step);
    CheckBorder(high, hsvPixel, step);

    inRange(inHSV, Scalar(low[0], low[1], low[2]), Scalar(high[0], high[1], high[2]), redMask);
    qInfo("%d %d %d", pixel[0], pixel[1], pixel[2]);
  // namedWindow("allout");
  //  imshow("allout", in);
  /*   namedWindow("redout");
    imshow("redout", redMask);
*/
    Mat inputTest[3];
    inputTest[0] = imread("log/rural/rural1.jpg", IMREAD_GRAYSCALE );
    inputTest[1] = imread("log/rural/rural2.jpg", IMREAD_GRAYSCALE );
    inputTest[2] = imread("log/rural/rural3.jpg", IMREAD_GRAYSCALE );
    int morph_elem = 0;
    int morph_size = 2;
    Mat element = getStructuringElement( morph_elem, Size( 2*morph_size + 1, 2*morph_size+1 ), Point( morph_size, morph_size ) );

    Mat diff1, diff2, diff3;
    Mat diffT1, diffT2;
    Mat threshOut;
    absdiff(inputTest[0], inputTest[1], diff1);
    absdiff(inputTest[1], inputTest[2], diff2);
    morphologyEx(diff1, diff1, CV_MOP_CLOSE, element);
    morphologyEx(diff2, diff2, CV_MOP_CLOSE, element);
    threshold(diff1,diffT1,25,255,THRESH_BINARY);
    threshold(diff2,diffT2,25,255,THRESH_BINARY);
    bitwise_xor(diffT1, diffT2, diff3, redMask);

    vector<vector<Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    findContours(diff3,contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
    sort(contours.begin(), contours.end(), compareContourAreas);

    DrawRotRect(diff3, contours[contours.size()-1]);
    DrawRotRect(diff3, contours[contours.size()-2]);

    namedWindow("contours");
    imshow("contours", diff3);

   /* Mat labels;
    Mat centers;
    Mat data;
    diff3.convertTo(data, CV_32F);
    kmeans(data, 3, labels,
                TermCriteria( TermCriteria::EPS+TermCriteria::COUNT, 10, 1.0),
                   3, KMEANS_PP_CENTERS, centers);
    qInfo("%d %d ", labels.cols, labels.rows);
    //for( i = 0; i < sample_count; i++ ) {
    //CvPoint2D32f pt = ((CvPoint2D32f*)points->data.fl)[i];
    //int cluster_idx = clusters->data.i[i];
    Scalar colorTab[] ={
            Scalar(0, 0, 0),
            Scalar(255,255,255),
            Scalar(0,0,255)
    };

    for (int i = 0; i < labels.rows; ++i){
        int clusterIdx = labels.at<int>(i);
        qInfo("%d", clusterIdx);
        Point2f c = data.at<Point2f>(i);
        //qInfo("%.f %.f", c.x, c.y);
        circle( in, c, 5, colorTab[clusterIdx], FILLED, LINE_AA );
        //circle(data, c, 3, Scalar(255,255,255));
    }
    namedWindow("motion");
    imshow("motion", data);*/

}

Point Sequence::MatchFeature(Mat input, QString templName)
{
    Mat templ = imread( templName.toStdString(), IMREAD_GRAYSCALE );
    MatchFeature(input, templ);
}

Point Sequence::MatchFeature(Mat input, Mat templateIn)
{
    using namespace cv::xfeatures2d;
    Mat img_1 = input;
    Mat img_2 = templateIn;

  if( !img_1.data || !img_2.data ){
      qInfo("read error");
    //return -1;
   }

  //-- Step 1: Detect the keypoints using SURF Detector, compute the descriptors
  int minHessian = 400;
  Ptr<SURF> detector = SURF::create();
  detector->setHessianThreshold(minHessian);
  std::vector<KeyPoint> keypoints_1, keypoints_2;
  Mat descriptors_1, descriptors_2;
  detector->detectAndCompute( img_1, Mat(), keypoints_1, descriptors_1 );
  detector->detectAndCompute( img_2, Mat(), keypoints_2, descriptors_2 );
  //-- Step 2: Matching descriptor vectors using FLANN matcher
  FlannBasedMatcher matcher;
  std::vector< DMatch > matches;
  matcher.match( descriptors_1, descriptors_2, matches );
  double max_dist = 0; double min_dist = 100;
  //-- Quick calculation of max and min distances between keypoints
  for( int i = 0; i < descriptors_1.rows; i++ ){
    double dist = matches[i].distance;
    if( dist < min_dist ) min_dist = dist;
    if( dist > max_dist ) max_dist = dist;
  }
  printf("-- Max dist : %f \n", max_dist );
  printf("-- Min dist : %f \n", min_dist );
  //-- Draw only "good" matches (i.e. whose distance is less than 2*min_dist,
  //-- or a small arbitary value ( 0.02 ) in the event that min_dist is very
  //-- small)
  //-- PS.- radiusMatch can also be used here.
  std::vector< DMatch > good_matches;
  for( int i = 0; i < descriptors_1.rows; i++ )
    if( matches[i].distance <= max(2*min_dist, 0.02) )
        good_matches.push_back( matches[i]);

 // for( int i = 0; i < (int)good_matches.size(); i++ )
 //     printf( " pnt 1: %.1f   %.1f  \n", i, keypoints_2[matches[i]].pt.x, keypoints_2[matches[i]].pt.y);


  //-- Draw only "good" matches
  Mat img_matches;
  //keypoints_1[i].pt.
  drawMatches( img_1, keypoints_1, img_2, keypoints_2,
               good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),
               std::vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );
  //-- Show detected matches
  Point2d pAvg(0.0, 0.0);
  int matchSize = (int)good_matches.size();
  for( int i = 0; i < matchSize; i++ )
      pAvg += (Point2d)keypoints_1[good_matches[i].queryIdx].pt;

  return Point(pAvg);

/*  Point roiCenter(pAvg.x / matchSize, pAvg.y / matchSize);
  circle(img_matches, roiCenter, 50, Scalar(255,0,0));
  imshow( "Good Matches", img_matches );
  waitKey(0);
  */
}

Point Sequence::MatchPixel(Mat img, QString templName, double thresh, double& maxLock){
        Mat templ = imread(templName.toStdString(), IMREAD_GRAYSCALE);
        MatchPixel(img, templ, thresh, maxLock);
}

Point Sequence::MatchPixel(Mat img, Mat templ, double thresh, double& maxLock){
    Mat result;
    int match_method = 5;

    /// Create the result matrix
    int result_cols =  img.cols - templ.cols + 1;
    int result_rows = img.rows - templ.rows + 1;

    result.create( result_rows, result_cols, CV_32FC1 );

    /// Do the Matching and Normalize
    matchTemplate( img, templ, result, match_method );
    //normalize( result, result, 0, 1, NORM_MINMAX, -1, Mat() );//need just for imshow!!!
    /// Localizing the best match with minMaxLoc
    double minVal, maxVal;
    Point minLoc, maxLoc;
    Point matchLoc(0,0);

    minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );
    qInfo("min %.2f max %.2f", minVal, maxVal);
    maxLock = maxVal;
    if (maxVal < thresh)
        return matchLoc;

    /// For SQDIFF and SQDIFF_NORMED, the best matches are lower values. For all the other methods, the higher the better
    if( match_method  == CV_TM_SQDIFF || match_method == CV_TM_SQDIFF_NORMED )
        matchLoc = minLoc;
    else
        matchLoc = maxLoc;

    return matchLoc;

    //rectangle( img_display, matchLoc, Point( matchLoc.x + templ.cols , matchLoc.y + templ.rows ), Scalar::all(0), 2, 8, 0 );
}

void Sequence::OpenImage(QString imageName){
    if (imageName.isEmpty()) // Do nothing if filename is empty
        return;
    imgClean = cv::imread(imageName.toStdString().c_str(), 1);
    if (imgClean.empty())
        return;
}
QString Sequence::SaveCommand(SaveCmd cmdIn){
    QStringList strList;
    strList.append("grayscale");
    strList.append("threshing");
    strList.append("canny");
    strList.append("contour");
    strList.append("bgr2hsv");
    strList.append("blur");
    strList.append("hsv2bgr");
    qInfo("len %d ", strList.length());

    SaveCmd cmd;
    cmd.len = 4;
    QString str;
    str.append(strList.value(cmd.cmd));
    for(int i = 0; i < cmd.len; i++){
        cmd.param[i] = i*i;
        str.append("p");
        str.append(QString::number(i));
        str.append(" ");
        str.append(QString::number(cmd.param[i]));
    }
    cmdBuff[cmdCnt] = cmdIn;
    cmdCnt++;
    return str;
//which command
//params
//add to string
}

void Sequence::Draw(){

    img = imgClean;
    /*for(int i = 0; i < cmdCnt; i++){
        ImgAct(cmdBuff[i].cmd, cmdBuff[i].param, outImg);
        outImg.copyTo(img);
    }
    cv::Mat outImg;\outImg.cop
    ImgAct(cmdBuff[0].cmd, cmdBuff[0].param, outImg);*/

    cv::Mat imgGray;
    cv::Mat thresh;
    cv::Mat out;
    cv::cvtColor(img, imgGray, CV_BGR2GRAY);
    cv::Canny( imgGray, thresh, 1, 2, 3 );//check param!
    out = cv::Scalar::all(0);
    thresh.copyTo(out);
    //src.copyTo( dst, detected_edges);
    cv::namedWindow("My Image");
    cv::imshow("My Image", out);
}

void Sequence::RemoveCommand(){
    if (cmdCnt > 0)
        cmdCnt--;
}
void Sequence::SaveSequence(QString filename){

    QSettings settings( filename, QSettings::IniFormat );
    for(int i = 0; i < cmdCnt; i++){
        settings.beginGroup( QString::number(cmdBuff[i].cmd) );
        for(int j = 0; j < cmdBuff[i].len; j++)
            settings.setValue(QString::number(j), QString::number(cmdBuff[i].param[j]));
    }
    cmdCnt = 0;
//save all rows to file
}

void Sequence::LoadSequence(QString filename){
    QSettings settings( filename, QSettings::IniFormat );
    qInfo("%s", settings.group().toStdString().c_str());
}

void Sequence::FindRoad(cv::Mat input){

    // Set-Up
    int houghVote = 200;

    // Set up windows
    bool showOriginal = 1;
    bool showCanny = 1;
    bool showHough = 1;
    bool showHoughP = 1;

    Mat image = input;
    double frameItr = 0;
    int crestCount = 0, frameSkip = 0;
    if (!image.empty()){
        qInfo("+");
        // ROI
        // optimized? -=> yes
        int top = 0;
        int left = 0;
        int width = 640;
        int height = 480;

        Rect roi(left,top,width,height);
        Mat imgROI = image(roi);
        Scalar val = Scalar(0, 0, 0);
        copyMakeBorder(imgROI, imgROI, 2, 2, 2, 2, BORDER_CONSTANT, val);

        if(showOriginal)
            imshow("Original Image",imgROI);

        // Canny algorithm
        Mat contours;
        Canny(imgROI,contours,100,200);
        Mat contoursInv;
        threshold(contours,contoursInv,128,255,THRESH_BINARY_INV);

        if(showCanny)
            imshow("Contours1",contours); // use contoursInv for white

        /*
         Hough tranform for line detection with feedback
         Increase by 25 for the next frame if we found some lines.
         This is so we don't miss other lines that may crop up in the next frame
         but at the same time we don't want to start the feed back loop from scratch.
         */
        std::vector<Vec2f> lines;
        if (houghVote < 1 or lines.size() > 2) { // we lost all lines. reset
            houghVote = 300;
        }
        else{ houghVote += 25;}
        while(lines.size() < 4 && houghVote > 0){
            HoughLines(contours,lines,1,PI/180, houghVote);
            houghVote -= 5;
        }
        std::cout << houghVote << "\n";
        Mat result(imgROI.size(),CV_8U,Scalar(255));
        imgROI.copyTo(result);

        // Draw the lines
        std::vector<Vec2f>::const_iterator it= lines.begin();
        Mat hough(imgROI.size(),CV_8U,Scalar(0));
        while (it!=lines.end()) {

            float rho= (*it)[0];   // first element is distance rho
            float theta= (*it)[1]; // second element is angle theta

            if ( (theta > 0.09 && theta < 1.48) || (theta < 3.14 && theta > 1.66) ) { // filter to remove vertical and horizontal lines

                // point of intersection of the line with first row
                Point pt1(rho/cos(theta),0);
                // point of intersection of the line with last row
                Point pt2((rho-result.rows*sin(theta))/cos(theta),result.rows);
                // draw a line: Color = Scalar(R, G, B), thickness
                line( result, pt1, pt2, Scalar(255,255,255), 1);
                line( hough, pt1, pt2, Scalar(255,255,255), 1);
            }

            //std::cout << "line: (" << rho << "," << theta << ")\n";
            ++it;
        }

        if(showHough)
            imshow("Detected Lines with Hough",result);

        // Create LineFinder instance
        LineFinder ld;

        // Set probabilistic Hough parameters
        ld.setLineLengthAndGap(10,60); // min accepted length and gap
        ld.setMinVote(15); // sit > 3 to get rid of "spiderweb"

        // Detect lines
        std::vector<Vec4i> li= ld.findLines(contours);
        Mat houghP(imgROI.size(),CV_8U,Scalar(0));
        ld.setShift(0,0);
        ld.drawDetectedLines(houghP);
        std::cout << "First Hough" << "\n";

        if(showHoughP)
            imshow("Detected Lines with HoughP", houghP);

        // bitwise AND of the two hough images
        bitwise_and(houghP,hough,houghP);
        Mat houghPinv(imgROI.size(),CV_8U,Scalar(0));
        Mat dst(imgROI.size(),CV_8U,Scalar(0));
        threshold(houghP,houghPinv,150,255,THRESH_BINARY_INV); // threshold and invert to black lines

        if(showHoughP)
            imshow("Detected Lines with Bitwise", houghP);

        Canny(houghPinv,contours,100,350);
        li = ld.findLines(contours);

        // Test to draw point
        //ld.drawPoint(image, Point(320,130));

        // Set probabilistic Hough parameters
        // more strict than above HoughP
        ld.setLineLengthAndGap(5,2);
        ld.setMinVote(1);
        ld.setShift(top, left);

        // draw point on image where line intersection occurs
        int yShift = 25;
        int allowableFrameSkip = 5;
        ld.drawDetectedLines(image);
        cv::Point iPnt = ld.drawIntersectionPunto(image, 2);

        // track hill crest
        int gap = 20;
        cv::Point lptl(0, image.rows / 2 + yShift);
        cv::Point lptr(gap, image.rows / 2 + yShift);
        line(image, lptl, lptr, Scalar(255, 255, 255), 1);// left mid line

        cv::Point rptl(image.cols - gap, image.rows / 2 + yShift);
        cv::Point rptr(image.cols, image.rows / 2 + yShift);
        line(image, rptl, rptr, Scalar(255, 255, 255), 1);// right mid line

        cv::Point ulpt(0, image.rows / 2 - 50 + yShift);
        cv::Point urpt(image.cols, image.rows / 2 - 50 + yShift);
   //     line(image, ulpt, urpt, Scalar(255, 255, 255), 1);// upper line

        bool hillCrestFound = (iPnt.y < (image.rows / 2 + yShift)) && (iPnt.y > (image.rows / 2 - 50 + yShift));
        if(hillCrestFound) {
            crestCount++;
            frameSkip = 0;
        } else if(crestCount != 0 && frameSkip < allowableFrameSkip)
            frameSkip++;
        else {
            crestCount = 0;
            frameSkip = 0;
        }

        cv::Point txtPt(image.cols / 2 - 31, image.rows / 2 - 140);
        if(crestCount > 3)
            putText(image, "tracking", txtPt, FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255), 2, 8);

        std::stringstream stream;
        stream << "Lines Segments: " << lines.size();

        putText(image, stream.str(), Point(10,image.rows-10), 1, 0.8, Scalar(0,255,0),0);

        namedWindow("Resulted pic", CV_WINDOW_KEEPRATIO); //resizable window;
        imshow("Resulted pic", image);
        imwrite("processed.bmp", image);

        lines.clear();
    }
}
