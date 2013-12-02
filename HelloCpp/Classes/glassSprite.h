

#ifndef __HelloCpp__glassSprite__
#define __HelloCpp__glassSprite__

#include <iostream>
#include <string>
using namespace std;
#include "cocos2d.h"
#include "my_Delaunay.h"
#include "triSprite.h"
#include "quadTree.h"
using namespace cocos2d;
class Cvertex
{
public:
    CCPoint pos;
    CCPoint disp;
    Cvertex(){
        pos=CCPoint(0,0);
        disp=CCPoint(0,0);
    }
    ~Cvertex(){};
};

enum eGlassState{
    eGlassState_perfect=0,
    eGlassState_crack,
    eGlassState_fall,
};
enum eBreakMode{
    eBreakMode_even=0,
    eBreakMode_density,
};
class CglassSprite:public CCSprite
{
public:
    CglassSprite(){
        state=eGlassState_perfect;
        fallTime=0;
        invisibleMeButNotAffectChildren=false;
        breakMode=eBreakMode_even;
    }
    virtual ~CglassSprite(){}
    void visit();
    void draw();
    void update(float t);
    bool init(string texFileName,CCPoint _lightDir);
    void debugDraw_triangularizationResult();
    void reset();
public:
    vector<CCPoint> pointList;
    vector<delaunay::CIDTriangle> IDtriList;
    vector<CtriSprite*> triSpriteList;
    quadTree::CquadTree quadTree;
    CCPoint touchPoint;
    bool invisibleMeButNotAffectChildren;
    eGlassState state;
    int fallTime;
    void doCrack();
    void updateState();
    eBreakMode breakMode;
    CCPoint lightDir;//light direction unit vector
};
#endif /* defined(__HelloCpp__glassSprite__) */
