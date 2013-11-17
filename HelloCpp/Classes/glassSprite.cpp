

#include "glassSprite.h"
bool CglassSprite::init(string texFileName){
    CCSize winSize=CCDirector::sharedDirector()->getWinSize();
    
    this->initWithFile(texFileName.c_str());
    CCSize texSize=this->getContentSize();
    //pointList
    {

        
        for(int i=0;i<200;i++){
            float n=max(winSize.width/2, winSize.height/2)*1.5;
            float randm=(rand()%10000)*1.0/10000;
      //      float r=(2*n-1-sqrtf(4*n*n*(1-randm)-4*n*(1-randm)+1))/2;
            float r=n-n*sqrtf(1-randm);
            float randA=rand()%360;
            float x=r*cosf(randA*M_PI/180);
            float y=r*sinf(randA*M_PI/180);
            CCPoint point(x+winSize.width/2,y+winSize.height/2);
            pointList.push_back(point);
            CCLOG("%f,%f",x,y);
        }
   /*     //add four corner points of *this to pointList
        CCSize contentSize=this->getContentSize();
        CCPoint leftUpPos=CCPoint(0,contentSize.height);
        CCPoint leftDnPos=CCPoint(0,0);
        CCPoint rightDnPos=CCPoint(contentSize.width,0);
        CCPoint rightUpPos=CCPoint(contentSize.width,contentSize.height);
        pointList.push_back(leftUpPos);
        pointList.push_back(leftDnPos);
        pointList.push_back(rightDnPos);
        pointList.push_back(rightUpPos);
*/
    }
    //Delaunay triangularization
    {
        //convert pointList to vector<Cv2>
        vector<Cv2> vlist;
        int nPoint=(int)pointList.size();
        for(int i=0;i<nPoint;i++){
            Cv2 v(pointList[i].x,pointList[i].y);
            vlist.push_back(v);
        }
        IDtriList=Delaunay(vlist);
    }
    return true;
}
void CglassSprite::draw(){
    CCSize winSize=CCDirector::sharedDirector()->getWinSize();
    //call father draw
    CCSprite::draw();
    //draw wire box
    ccDrawColor4B(255,255,255,255);//instead of glColor4f
    glLineWidth(2);
    ccPointSize(5);
    for(int i=0;i<(int)pointList.size();i++){
        ccDrawPoint( pointList[i] );
    }
    //draw all triangles in IDtri
    int nTri=(int)IDtriList.size();
    for(int i=0;i<nTri;i++){
        CIDTriangle IDtri=IDtriList[i];
        CCPoint vertices[]={pointList[IDtri.vID[0]],pointList[IDtri.vID[1]],pointList[IDtri.vID[2]]};
        ccDrawPoly(vertices, 3, true);
    }
    
}