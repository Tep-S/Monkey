#include "sequence.h"
//#include "opencv2/opencv_modules.hpp"
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

void CheckBorder(int* param, int* val, int step){
    for(int i = 0; i < 3; i++){
        param[i] = val[i] + step;
        if(param[i] > 255)
            param[i] = 255;
        if(param[i] < 0)
            param[i] = 0;
    }
}

int Sequence::GetHP(cv::Point pix){
    using namespace cv;
    using namespace std;
    int debug  = 1;
    Mat hsv, hsvMask;
    Mat in = imread( "log/statusbar.jpg");
    cvtColor(in,hsv, COLOR_BGR2HSV);
    //circle(in,Point(76,18),10,Scalar(0,255,0));//x, y
    namedWindow("input");
    imshow("input",in);
    Vec3b pixel = hsv.at<Vec3b>(pix.y, pix.x);//y, x
    //qInfo("%d %d %d", pixel.val[0], pixel.val[1], pixel.val[2]);
    int hsvPixel[3] = {pixel.val[0], pixel.val[1], pixel.val[2]};
    int low[3], high[3];
    int step = 15;
    CheckBorder(low, hsvPixel, -step);
    CheckBorder(high, hsvPixel, step);

    inRange(hsv, Scalar(low[0], low[1], low[2]), Scalar(high[0], high[1], high[2]), hsvMask);
    if(debug){
        namedWindow("red");
        imshow("red",hsvMask);
    }
    vector<vector<Point>> contours;
        vector<Vec4i> hierarchy;
        findContours(hsvMask,contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

        int biggestContourIdx = -1;
        float biggestContourArea = 0;
        Mat drawing = Mat::zeros( hsvMask.size(), CV_8UC3 );
        Scalar color = Scalar(255, 0, 0);
        for( int i = 0; i< contours.size(); i++ ){
            //drawContours( drawing, contours, i, color, 1, 8, hierarchy, 0, cv::Point() );
            float ctArea= contourArea(contours[i]);
            if(ctArea > biggestContourArea){
                biggestContourArea = ctArea;
                biggestContourIdx = i;
            }
        }
        RotatedRect rRect = minAreaRect(contours[biggestContourIdx]);
        cv::Point2f points[4];
        rRect.points(points);
        int minX = 10000;
        int maxX = 0;
        for(int i = 0; i < 4; ++i){
            if (points[i].x > maxX)
                maxX = points[i].x;
            if (points[i].x < minX)
                minX = points[i].x;
            if(debug)
                line(drawing, points[i], points[(i+1)%4], cv::Scalar(0,0,255), 2);
        }
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
    recLong[0] = GetHP(cv::Point(76,18));
    recLong[1] = GetHP(cv::Point(76,49));
    recLong[2] = GetHP(cv::Point(76,80));
    qInfo("%.f %.f %.f", recLong[0]/197*50, recLong[1]/197*1000, recLong[2]/197*204);

}

void Sequence::FindRect(cv::Mat input){
    using namespace cv;
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
    qInfo("%d %d %d", pixel.val[0], pixel.val[1], pixel.val[2]);
    inRange(inHSV, cv::Scalar(0,140,150), cv::Scalar(30,255,200), redMask);
    namedWindow("allout");
    imshow("allout", in);
    namedWindow("redout");
    imshow("redout", redMask);


    waitKey(0);
    //imshow("smth", inCropped);

}

cv::Mat Sequence::ColorMask(cv::Mat input, cv::Scalar low, cv::Scalar high){

    using namespace cv;
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

void Sequence::MotionMask(cv::Mat input, cv::Mat outputMask){
/*    cv::Mat inputTest[3];
    for(int i = 0; i < 3; i++){
        inputTest[i]
    }
    cv::Mat diff1, diff2;
    cv::Mat threshOut;
    cv::absdiff(input, input2, diff1);
    cv::absdiff(input2, input3, diff2);
    cv::threshold(diff1,threshOut,40,255,THRESH_BINARY);
    */
}

int Sequence::FlannMatching(cv::Mat input, cv::Mat templateIn)
{
    using namespace cv;
    using namespace cv::xfeatures2d;
    //Mat img_1   = input;//IMREAD_GRAYSCALE
   //Mat img_2 = templateIn;//IMREAD_GRAYSCALE
    Mat img_1 = imread( "log/la2.jpg", IMREAD_GRAYSCALE );
    Mat img_2 = imread( "log/la2cropp.jpg", IMREAD_GRAYSCALE );

  if( !img_1.data || !img_2.data ){
      qInfo("read error");
    return -1;
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

  Point roiCenter(pAvg.x / matchSize, pAvg.y / matchSize);
  circle(img_matches, roiCenter, 50, Scalar(255,0,0));
  imshow( "Good Matches", img_matches );
  waitKey(0);

/*
  return 0;
  */
}

cv::Point Sequence::TemplateCoord(cv::Mat img, cv::Mat templ, double thresh){
    using namespace std;
    using namespace cv;
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
    if (maxVal < thresh){
        //matchLoc.x = matchLoc.y = 0;
        return matchLoc;
    }

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

using namespace cv;
using namespace std;

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
