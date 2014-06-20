//
//  myFunc.cpp
//  HelloCpp
//
//  Created by apple on 13-10-26.
//
//

#include "myFunc.h"
#include "support/ccUtils.cpp"//if we use #include "support/ccUtils.cpp", in vs2010 cause linking error "unsolved external symbol".

CCTexture2D* createCCTexture2DWithSize(const CCSize&size,CCTexture2DPixelFormat eFormat,
                                       float r=0,float g=0,float b=0,float a=0)//r,g,b,a are range form 0 to 1
{
    //the code below is copied from CCRenderTexture::initWithWidthAndHeight, with some modification.
    CCTexture2D* pTexture=NULL;
    void *data = NULL;
    do{
        int w = (int)(size.width * CC_CONTENT_SCALE_FACTOR());
        int h = (int)(size.height * CC_CONTENT_SCALE_FACTOR());
        
        // textures must be power of two squared
        unsigned int powW = 0;
        unsigned int powH = 0;
        
        if (CCConfiguration::sharedConfiguration()->supportsNPOT())
        {
            powW = w;
            powH = h;
        }
        else
        {
            powW = ccNextPOT(w);
            powH = ccNextPOT(h);
        }
        
        data = malloc((int)(powW * powH * 4));
        CC_BREAK_IF(! data);
        
        memset(data, 0, (int)(powW * powH * 4));
        
        //fill data with color value
        int _r=r*255;
        int _g=g*255;
        int _b=b*255;
        int _a=a*255;
        for(int i=0;i<powH;i++){
            for(int j=0;j<powW;j++){
                ((char*)data)[(i*powW+j)*4+0]=_r;
                ((char*)data)[(i*powW+j)*4+1]=_g;
                ((char*)data)[(i*powW+j)*4+2]=_b;
                ((char*)data)[(i*powW+j)*4+3]=_a;
            }
        }
        
        pTexture = new CCTexture2D();
        if (pTexture)
        {
            pTexture->initWithData(data, eFormat, powW, powH, CCSizeMake((float)w, (float)h));
        }
    }while (0);
    return pTexture;

}

float calculateIncircleR2(CCPoint v0,CCPoint v1,CCPoint v2)
//calculate the square of triangle v0v1v2's Incircle's radius
{
    float Len_v0v1=ccpDistance(v0, v1);
    float Len_v1v2=ccpDistance(v1, v2);
    float Len_v2v0=ccpDistance(v2, v0);
    float a=Len_v0v1;
    float b=Len_v1v2;
    float c=Len_v2v0;
    float temp=2*(a+b+c);
    float r2=((a+b+c)*(b+c-a)*(a+c-b)*(a+b-c))/(temp*temp);//square of triangle v0v1v2's Incircle's radius
    return MAX(0,r2);//r2 should be no negative
}
vector<CCPoint> makeTriangleSmaller(CCPoint v0,CCPoint v1,CCPoint v2,float d)
//return a smaller triangle p0p1p2
//satisfy:
//distance between edge v0v1 and p0p1 is d
//distance between edge v1v2 and p1p2 is d
//distance between edge v2v0 and p2p0 is d
//if the p0p1p2 shrink to a point, the return vector just contain one element (the point),
//otherwise the return vector will contain three element (p0,p1,p2)
{
    float incircleR2=calculateIncircleR2(v0, v1, v2);
    bool shrinkToPoint=(d*d>=incircleR2);
    if(shrinkToPoint){//if shrink to a point, then use incircleR as d
        d=sqrtf(incircleR2);
    }
    //base on geometry, p0 should on the angular bisector of angle v1v0v2, and the length of v0p0 is d/sin(0.5*angle_v1v0v2)
    //simlar conclusion for v1 and v2
    vector<CCPoint> plist;
    CCPoint vlist[3]={v0,v1,v2};
    for(int i=0;i<3;i++){
        //calculate p[i] (cur p)
        CCPoint v=vlist[i];//cur v
        CCPoint vn=vlist[(i+1)%3];//next v
        CCPoint vf=vlist[(i-1+3)%3];//foe v
        CCPoint dir_vvn=ccpNormalize(vn-v);
        CCPoint dir_vvf=ccpNormalize(vf-v);
        CCPoint dir_vp=ccpNormalize(dir_vvn+dir_vvf);//direction of vp
        float cos_vnvvf=ccpDot(dir_vvn, dir_vvf);
        float sin_halfvnvvf=sqrtf(MAX(0,0.5*(1-cos_vnvvf)));//sin(0.5*angle_vnvvf)
        float len_vp=d/sin_halfvnvvf;//length of vp
        CCPoint vp=ccpMult(dir_vp, len_vp);
        CCPoint p=v+vp;//got p
        plist.push_back(p);
        if(shrinkToPoint)break;//if shrink to a point, now we got the point, no need more calculation
    }
    return plist;
}
int findPointInPointList(const CCPoint&point,const vector<CCPoint>&pointList,float eps)
//return the index of match point.
//if no match, return -1
{
    int nPoint=(int)pointList.size();
    for(int i=0;i<nPoint;i++){
        const CCPoint&_point=pointList[i];
        if(fabsf(point.x-_point.x)<eps&&fabsf(point.y-_point.y)<eps)return i;
    }
    return -1;
}
float calculateArea(CCPoint v0,CCPoint v1,CCPoint v2)//xxxx need to check!!!
//calculateArea of triangle v0v1v2
//ref to: http://zhidao.baidu.com/link?url=zQUSnOMZK_hGlSDVy5kWXDRraAbedjUoNtav83p1fdmoCJvaSADSc5bJ1Wr0kmzFFewuDevYQ2fFOqX1vIJaja
{
    const float x1=v0.x;
    const float y1=v0.y;
    const float x2=v1.x;
    const float y2=v1.y;
    const float x3=v2.x;
    const float y3=v2.y;
    float Area=0.5*fabsf(x1*y2+x2*y3+x3*y1-x1*y3-x2*y1-x3*y2);
    return Area;
    
}
int randomSelectByProbility(const vector<float>&probilityList){//return the selected one's index
    int n=(int)probilityList.size();
    assert(n!=0);
    float random=rand()*1.0/RAND_MAX;//this is the best method to generate random value in [0,1] in c++
    float sum=0;
    int index=-1;
    for(int i=0;i<n;i++){
        sum+=probilityList[i];
        if(sum>random){
            index=i;
            break;
        }
    }
    if(index==-1){
        CCLOG("warning: index==-1, return the last one's index");
        return n-1;
    }
    return index;
}
