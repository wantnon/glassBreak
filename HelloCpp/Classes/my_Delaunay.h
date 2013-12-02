#ifndef my_Delaunay_H_H
#define my_Delaunay_H_H
#include <vector>
#include <iostream>
using namespace std;
#include "math.h"
namespace delaunay {
    static const float inf=1000000;
    static const int X=0;
    static const int Y=1;
    static const int Z=2;
    template<class T>
    class myvector:public vector<T>
    {
    public:
        myvector():vector<T>(){};
        void grow(){
            this->resize((int)this->size()+1);
        }
    };
    class Cv2{
    public:
        float v[2];//坐标
        Cv2(){}
        Cv2(float x,float y){
            init(x,y);
        }
        void init(float x,float y){
            v[0]=x;
            v[1]=y;
        }
    };
    
    class Cv4{
    public:
        float v[4];//坐标
        bool added;//连通性测试时的访问标记
        Cv4(){
            added=false;
        }
        Cv4(float x,float y,float z,float w){
            init(x,y,z,w);
        }
        void init(float x,float y,float z,float w){
            v[0]=x;
            v[1]=y;
            v[2]=z;
            v[3]=w;
            
        }
    };
    class CIDedge{//索引边
    public:
        int ID1;//起点索引
        int ID2;//终点索引
        bool added;
        CIDedge(){
            added=false;
        }
        void setvID(int _ID1,int _ID2){
            ID1=_ID1;
            ID2=_ID2;
        }
    };
    
    
    class CIDTriangle{
    public:
        int vID[3];
        CIDTriangle*p[3];
        bool removed;//标记是否已被替换下来了
        double r2;//外接圆半径的平方
        float x,z;//外接圆圆心
        bool circleAlreadyGet;//指明此三角形的外接圆是否已求过
        myvector<CIDTriangle*>q;//Delaunay三角树孩子指针
        CIDTriangle(){
            circleAlreadyGet=false;
            removed=false;
            p[0]=NULL;
            p[1]=NULL;
            p[2]=NULL;
        }
        void setp(CIDTriangle*p0,CIDTriangle*p1,CIDTriangle*p2){
            p[0]=p0;
            p[1]=p1;
            p[2]=p2;
        }
        void setvID(int ID0,int ID1,int ID2){
            vID[0]=ID0;
            vID[1]=ID1;
            vID[2]=ID2;
        }
        
        
    };
    
    float pow2(float x);
    void init4(float vec[4],float x,float y,float z,float w);
    void veccopy(float src[4],float dest[4]);
    double calCircle(float _x1,float _y1,float _x2,float _y2,float _x3,float _y3,
                     float &x,float &y);
    int getIndexOfp_IDtri1ToIDtri2(CIDTriangle*pIDtri1,CIDTriangle*pIDtri2);
    int getIndexOfVert_inIDtri1notinIDtri2(CIDTriangle*pIDtri1,CIDTriangle*pIDtri2);
    int pointInIDtri(float v[4],CIDTriangle*pIDtri,myvector<Cv4>&vlist,int&edgeID);
    void flip(CIDTriangle*pAdjIDtri,CIDTriangle*pnewIDtri,const int ID,float v[4],
              myvector<Cv4>&vlist,myvector<CIDTriangle*>&pIDtriList,int&count);
    void locIDPoint(float v[4],CIDTriangle*pIDtri,myvector<Cv4>&vlist,CIDTriangle*&pTagIDtri,int&judge,int&edgeID);
    void Delaunay(myvector<Cv4>&vlist,
                  float xmin,float xmax,float zmin,float zmax,
                  myvector<CIDTriangle*>&pIDtriList);
    vector<CIDTriangle> Delaunay(vector<Cv4>&vlist);
    vector<CIDTriangle> Delaunay(vector<delaunay::Cv2>&vlist);

}
#endif