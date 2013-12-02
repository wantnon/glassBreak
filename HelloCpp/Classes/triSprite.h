

#ifndef __HelloCpp__triSprite__
#define __HelloCpp__triSprite__

#include <iostream>
#include <string>
using namespace std;
#include "cocos2d.h"
using namespace cocos2d;
#include "indexVBO.h"
class CtriSprite:public CCSprite
{
private:
    bool inAction;
    float vy;
    float gravityFactor;
    CCPoint vlist[3];
    CCPoint texCoordList[3];
    CCPoint lightDir;//light direction unit vector
public:
    CindexVBO*indexVBO;
    CtriSprite(){
        vy=0;
        gravityFactor=1.0;
        inAction=false;
        indexVBO=new CindexVBO();
    }
    virtual~CtriSprite(){
        if(indexVBO)delete indexVBO;
    }
    void setLightDir(CCPoint _lightDir){
        lightDir=_lightDir;
    }
    vector<CCPoint>  getVlist()const {
        return vector<CCPoint> (vlist,vlist+3);
    }
    void update(float t);
    bool getInAction()const {return inAction;}
    void startAction(){
        inAction=true;
        scheduleUpdate();
    }
    void stopAction(){
        inAction=false;
        unscheduleUpdate();
    }
    bool init(CCTexture2D*texture,CCPoint v0,CCPoint v1,CCPoint v2,CCPoint texCoord0,CCPoint texCoord1,CCPoint texCoord2);
    void draw();
};
#endif /* defined(__HelloCpp__triSprite__) */
