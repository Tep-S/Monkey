#include "sequence.h"

Sequence::Sequence()
{

}

void Sequence::ImgAct(int command){
    cv::Mat img;
    int param1, param2;
    enum{
        Do_Gray,
        Do_Thresh,
        Do_Canny,
        Do_Contours,
        Do_Bgr2Hsv,
        Do_Blur
    };

    switch(command){
    case Do_Gray:{
        cv::cvtColor(img, img, CV_BGR2GRAY);
    }
        break;
    case Do_Thresh:{
        //need gray in
        threshold( img, img, param1, param2, CV_THRESH_BINARY );//p1 20 p2 150
    }
        break;
    case Do_Canny:{
        Canny( img, img, param1, param2, 3 );//check param!
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
    }

}

void Sequence::OpenImage(QString imageName){
    if (imageName.isEmpty()) // Do nothing if filename is empty
        return;
    cv::Mat img = cv::imread(imageName.toStdString().c_str(), 1);
    if (img.empty())
        return;
    cv::namedWindow("My Image");
        // show the image on window
    cv::imshow("My Image", img);
}
QString Sequence::SaveCommand(){
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
    return str;
//which command
//params
//add to string
}
void Sequence::RemoveCommand(){

}
void Sequence::SaveSequence(QString filename){
    SaveCmd cmd[10];
    QSettings settings( filename, QSettings::IniFormat );
    for(int i = 0; i < 10; i++){
        settings.beginGroup( QString::number(cmd[i].cmd) );
        for(int j = 0; j < cmd[i].len; j++)
            settings.setValue(QString::number(j), QString::number(cmd[i].param[j]));
    }
//save all rows to file
}

void Sequence::LoadSequence(){

}
