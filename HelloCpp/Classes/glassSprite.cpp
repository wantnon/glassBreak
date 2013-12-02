

#include "glassSprite.h"
#include "myFunc.h"
void CglassSprite::updateState(){
    switch(state){
        case eGlassState_perfect:
        {
            state=eGlassState_crack;
            doCrack();
            invisibleMeButNotAffectChildren=true;
        }
            break;
        case eGlassState_crack:
        {
            state=eGlassState_fall;
            fallTime=0;
            scheduleUpdate();
        }
            break;
        case eGlassState_fall:
        {
            state=eGlassState_perfect;
            reset();
        }
            break;
        default:
            CCAssert(false, "should not be here!");
            break;
    }
}

bool CglassSprite::init(string texFileName,CCPoint _lightDir){
    lightDir=_lightDir;
    this->initWithFile(texFileName.c_str());
    
    return true;
}
void CglassSprite::debugDraw_triangularizationResult(){
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
        delaunay::CIDTriangle IDtri=IDtriList[i];
        CCPoint vertices[]={pointList[IDtri.vID[0]],pointList[IDtri.vID[1]],pointList[IDtri.vID[2]]};
        ccDrawPoly(vertices, 3, true);
    }
}
void CglassSprite::visit(){
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    CCRect rect=this->boundingBox();//world space rect
    glEnable(GL_SCISSOR_TEST);
    //glScissor receive world space rect, not local space.
    glScissor(rect.getMinX()-origin.x, rect.getMinY(), rect.getMaxX()-rect.getMinX(), rect.getMaxY()-rect.getMinY());
    CCSprite::visit();
    glDisable(GL_SCISSOR_TEST);
}
void CglassSprite::draw(){
    if(invisibleMeButNotAffectChildren)return;
    CCSprite::draw();
 //   debugDraw_triangularizationResult();
  //  quadTree.debugDraw();
}
void CglassSprite::doCrack(){
   
    //get contentSize
    CCSize contentSize=this->getContentSize();
    //init quadTree
    {
        quadTree.clearTree();
        float L=MAX(contentSize.width,contentSize.height);
        float margin=1;
        quadTree::Crect rect(contentSize.width/2-L/2-margin,contentSize.width/2+L/2+margin,
                             contentSize.height/2-L/2-margin,contentSize.height/2+L/2+margin);
        quadTree.initTree(rect,quadTree::Cv2(touchPoint.x,touchPoint.y),7,180,2.5);
    }
    //generate pointList
    if(breakMode==eBreakMode_density){
        vector<float> _eList;//temp edge length list
        vector<CCPoint> _pointList;//temp point list
        vector<quadTree::CqNode*> leafList=quadTree.getLeafList();
        int nLeaf=(int)leafList.size();
        for(int i=0;i<nLeaf;i++){
            quadTree::CqNode*leaf=leafList[i];
            CCPoint ld(leaf->rect.xmin,leaf->rect.ymin);
            CCPoint rd(leaf->rect.xmax,leaf->rect.ymin);
            CCPoint ru(leaf->rect.xmax,leaf->rect.ymax);
            CCPoint lu(leaf->rect.xmin,leaf->rect.ymax);
            CCPoint points[4]={ld,rd,ru,lu};
            for(int i=0;i<4;i++){
                CCPoint&curPoint=points[i];
                int existedPointIndex=findPointInPointList(curPoint,_pointList,0.001);
                if(existedPointIndex==-1){//if not exist
                    //add point to _pointList and add e to eList
                    _pointList.push_back(curPoint);
                    _eList.push_back(leaf->rect.getWidth());
                }else{//if exist
                    //compare the existed point's e with curPoint's e
                    //if curPoint's e is smaller than existed point's e, use curPoint's e replace existed point's e
                    float e_curPoint=leaf->rect.getWidth();
                    float e_existedPoint=_eList[existedPointIndex];
                    if(e_curPoint<e_existedPoint)_eList[existedPointIndex]=e_curPoint;
                }
            }
        }//got _elist and _pointList
        //generate pointList based on _elist and _pointList
        CCRect rect(0,0,contentSize.width,contentSize.height);
        int nPoint=(int)_pointList.size();
        for(int i=0;i<nPoint;i++){
            float A=rand()%360;
            float r=_eList[i]/4;
            float dx=r*cosf(A*M_PI/180);
            float dy=r*sinf(A*M_PI/180);
            CCPoint point;
            if(rect.containsPoint(_pointList[i])){
                point=CCPoint(_pointList[i]+ccp(dx,dy));
            }else{
                point=CCPoint(_pointList[i]);
            }
            pointList.push_back(point);
        }
        
    }else if(breakMode==eBreakMode_even){
        float step=50;
        for(float x=-step;x<=contentSize.width+step;x+=step){
            for(float y=-step;y<contentSize.height+step;y+=step){
                float A=rand()%360;
                float r=step/4;
                float dx=r*cosf(A*M_PI/180);
                float dy=r*sinf(A*M_PI/180);
                CCPoint point(x+dx,y+dy);
                pointList.push_back(point);
            }
        }
    }else{
        CCAssert(false, "should not be here!");
    }
    //Delaunay triangularization
    {
        //convert pointList to vector<Cv2>
        vector<delaunay::Cv2> vlist;
        int nPoint=(int)pointList.size();
        for(int i=0;i<nPoint;i++){
            delaunay::Cv2 v(pointList[i].x,pointList[i].y);
            vlist.push_back(v);
        }
        IDtriList=Delaunay(vlist);
        
        CCPoint v0=pointList[IDtriList[0].vID[0]];
        CCPoint v1=pointList[IDtriList[0].vID[1]];
        CCPoint v2=pointList[IDtriList[0].vID[2]];

    }
    //remove IDtriList which is out of win
    {
        int nTri=(int)IDtriList.size();
        for(int i=0;i<nTri;i++){
            CCPoint v0=pointList[IDtriList[i].vID[0]];
            CCPoint v1=pointList[IDtriList[i].vID[1]];
            CCPoint v2=pointList[IDtriList[i].vID[2]];
            //if v0,v1,v2 are all on one side of upline or dnline or leftline or rightline, we can ensure triangle is out of screen
            //(this method is not accurate, some triangles which is truely out of win may not be spotted)
            bool outOfWin=false;
            if(v0.x<0&&v1.x<0&&v2.x<0)outOfWin=true;
            if(v0.y<0&&v1.y<0&&v2.y<0)outOfWin=true;
            if(v0.x>contentSize.width&&v1.x>contentSize.width&&v2.x>contentSize.width)outOfWin=true;
            if(v0.y>contentSize.height&&v1.y>contentSize.height&&v2.y>contentSize.height)outOfWin=true;
            if(outOfWin){
                IDtriList.erase(IDtriList.begin()+i);
                i--;
                nTri--;
            }
        }
    }
    //use pointList and IDtriList make triSprites
    {
        //generate triSprites
        {
            int nTri=(int)IDtriList.size();
            for(int i=0;i<nTri;i++){
                CCPoint v0_world=pointList[IDtriList[i].vID[0]];
                CCPoint v1_world=pointList[IDtriList[i].vID[1]];
                CCPoint v2_world=pointList[IDtriList[i].vID[2]];
                CCPoint c_world=ccpMult(v0_world+v1_world+v2_world, 1.0/3);
                CCPoint texCoord0=CCPoint(v0_world.x/contentSize.width,1-v0_world.y/contentSize.height);
                CCPoint texCoord1=CCPoint(v1_world.x/contentSize.width,1-v1_world.y/contentSize.height);
                CCPoint texCoord2=CCPoint(v2_world.x/contentSize.width,1-v2_world.y/contentSize.height);
                CCPoint v0_loc=v0_world-c_world;
                CCPoint v1_loc=v1_world-c_world;
                CCPoint v2_loc=v2_world-c_world;
                //make trangle a little smaller
                vector<CCPoint> vlist=makeTriangleSmaller(v0_loc, v1_loc, v2_loc, 1);
                if((int)vlist.size()==1){
                    //the triangle shrink to a point, no need to make triSprite for it, so continue
                    continue;
                }
                v0_loc=vlist[0];
                v1_loc=vlist[1];
                v2_loc=vlist[2];
                CtriSprite*triSprite=new CtriSprite();
                triSprite->autorelease();
                CCTexture2D*texture=this->getTexture();
                triSprite->init(texture,v0_loc,v1_loc,v2_loc,texCoord0,texCoord1,texCoord2);
                triSprite->setPosition(c_world);
                triSprite->setAnchorPoint(ccp(0,0));
                triSprite->setLightDir(lightDir);
                //    CCLOG("zOrder:%i",triSprite->getZOrder());
                triSpriteList.push_back(triSprite);
            }
            //note: now IDtriList and CtriSprite may be different on triangle number, means IDtriList is outdated.
        }
        //add triSprites to *this
        {
            int nTri=(int)triSpriteList.size();
            for(int i=0;i<nTri;i++){
                CtriSprite*triSprite=triSpriteList[i];
                this->addChild(triSprite,100);
            }
        }

        
    }
    

    
}
void CglassSprite::reset(){
    //release pointList and IDtriList
    pointList.clear();
    IDtriList.clear();
    //release triSprites
    int nTriSprite=(int)triSpriteList.size();
    for(int i=0;i<nTriSprite;i++){
        CtriSprite*triSprite=triSpriteList[i];
        triSprite->removeFromParentAndCleanup(true);
    }
    triSpriteList.clear();
    //do not invisible
    invisibleMeButNotAffectChildren=false;
    //unschedule
    unscheduleUpdate();
}
void CglassSprite::update(float t){
    //every once in a while a glass fragment disapear
    fallTime++;
    if(fallTime>1000000)fallTime=0;
    if(fallTime%1==0){
        //make not inAction triSprite list
        vector<CtriSprite*> notInActionTriSpriteList;
        int nTriSprite=(int)triSpriteList.size();
        for(int i=0;i<nTriSprite;i++){
            if(triSpriteList[i]->getInAction()==false)notInActionTriSpriteList.push_back(triSpriteList[i]);
        }//got notInActionTriSpriteList
        if(notInActionTriSpriteList.empty())return;
        //calculate area for each triSprite in notInActionTriSpriteList
        vector<float> areaList;
        {
            int nNotInActionTriSprite=(int)notInActionTriSpriteList.size();
            for(int i=0;i<nNotInActionTriSprite;i++){
                CtriSprite*triSprite=notInActionTriSpriteList[i];
                vector<CCPoint> vlist=triSprite->getVlist();
                areaList.push_back(calculateArea(vlist[0], vlist[1], vlist[2]));
            }
        }
        //calculate probability for each triSprite in notInActionTriSpriteList, small triSprite have higher probability
        vector<float> probilityList;
        {
            int nNotInActionTriSprite=(int)notInActionTriSpriteList.size();
            float sum=0;
            for(int i=0;i<nNotInActionTriSprite;i++){
                CtriSprite*triSprite=notInActionTriSpriteList[i];
                vector<CCPoint> vlist=triSprite->getVlist();
                probilityList.push_back(1.0/(areaList[i]*areaList[i]));
                sum+=probilityList[i];
            }
            //normalize probabilityList
            for(int i=0;i<(int)probilityList.size();i++){
                probilityList[i]/=sum;
            }//got probilityList
        }
        //select  some not-in-action triSprite by probility
        float areaSum=0;
        while (1) {
            int index=randomSelectByProbility(probilityList);
            CtriSprite*triSprite=notInActionTriSpriteList[index];
            if(triSprite->getInAction())continue;
            triSprite->startAction();
            //triSprite->setZOrder(triSprite->getZOrder()+1000) is not work
            //use below instead. see: http://blog.csdn.net/chenli0741/article/details/9257719
            triSprite->getParent()->reorderChild(triSprite,triSprite->getZOrder()+1000);
           // CCLOG("zOrder:%i",triSprite->getZOrder());
            areaSum+=areaList[index];
            if(areaSum>100)break;
        }
        
        
    }
    
    
}