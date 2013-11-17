

#ifndef __HelloCpp__glassSprite__
#define __HelloCpp__glassSprite__

#include <iostream>
#include <string>
using namespace std;
#include "cocos2d.h"
#include "my_Delaunay.h"
using namespace cocos2d;
class CglassSprite:public CCSprite
{
public:
    CglassSprite(){
        
    }
    virtual ~CglassSprite(){
    
    }
    void draw();
    bool init(string texFileName);
    vector<CCPoint> pointList;
    vector<CIDTriangle> IDtriList;
};
#endif /* defined(__HelloCpp__glassSprite__) */
