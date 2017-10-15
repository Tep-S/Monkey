#include "sequence.h"

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
