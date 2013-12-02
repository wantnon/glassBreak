//
//  quadTree.h
//  HelloCpp
//
//  Created by ck02-084 on 13-11-29.
//
//

#ifndef __HelloCpp__quadTree__
#define __HelloCpp__quadTree__

#include <iostream>
#include <vector>
using namespace std;
#include "cocos2d.h"
using namespace cocos2d;
#include "math.h"
namespace quadTree
{
    class Cv2
    {
    public:
        float x,y;
        Cv2()
        {
            x=y=0;
        }
        Cv2(float _x,float _y)
        {
            init(_x,_y);
        }
        virtual~Cv2(){}
        void init(float _x,float _y)
        {
            x=_x;
            y=_y;
        };
        Cv2 operator+(Cv2&v)
        {
            Cv2 rs(x+v.x,y+v.y);
            return rs;
        }
        Cv2 operator-(Cv2&v)
        {
            Cv2 rs(x-v.x,y-v.y);
            return rs;
        }
    };
    Cv2 mul(float k,Cv2&v);
    float distance(Cv2&v1,Cv2&v2);
    class Crect
    {
    public:
        float xmin,xmax,ymin,ymax;
        Crect(){
            xmin=xmax=ymin=ymax=0;
        }
        Crect(float _xmin,float _xmax,float _ymin,float _ymax){
            init(_xmin,_xmax,_ymin,_ymax);
        }
        virtual~Crect(){}
        void init(float _xmin,float _xmax,float _ymin,float _ymax){
            assert(_xmax>=_xmin);
            assert(_ymax>=_ymin);
            xmin=_xmin;
            xmax=_xmax;
            ymin=_ymin;
            ymax=_ymax;
        }
        Cv2 getCenter()const {
            Cv2 v((xmin+xmax)/2,(ymin+ymax)/2);
            return v;
        }
        float getWidth()const {
            return xmax-xmin;
        }
        float getHeight()const {
            return ymax-ymin;
        }
    };

    
    class CqNode
    {
    public:
        Crect rect;
        CqNode(){}
        virtual~CqNode(){}
        vector<CqNode*> children;
    };
    

    class CquadTree
    {
    private:
        CqNode*root;
        float C1;//distance resolution of quadTree
        Cv2 tgPoint;
        float e_min,e_max;
    public:
        CquadTree(){
            root=NULL;
            C1=3;//because d<e*C1 => continue divide, so larger C1 cause easier division
            e_min=1;
            e_max=100;
        }
        virtual~CquadTree(){
            clearTree();
        }
        void setDistanceResolution(float _C1){C1=_C1;}
        float getDistanceResolution()const {return C1;}
        CqNode*getRoot()const{return root;}
        void initTree(const Crect&rect,const Cv2&_tgPoint,float _e_min,float _e_max,float distanceResolution);
        vector<CqNode*> getLeafList();
        void clearTree();
        void debugDraw();
    private:
        void getLeafList_inn(CqNode*&node,vector<CqNode*>&leafList);
        void clearTree_inn(CqNode*&node);
        void debugDraw_inn(CqNode*&node);
        void initTree_inn(CqNode*&node);
    };
}
#endif /* defined(__HelloCpp__quadTree__) */
