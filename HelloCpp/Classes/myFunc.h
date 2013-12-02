//
//  myFunc.h
//  HelloCpp
//
//  Created by apple on 13-10-26.
//
//

#ifndef __HelloCpp__myFunc__
#define __HelloCpp__myFunc__

#include <iostream>
using namespace std;
#include "cocos2d.h"
#include "cocos-ext.h"
using namespace cocos2d;
CCTexture2D* createCCTexture2DWithSize(const CCSize&size,CCTexture2DPixelFormat eFormat,float r,float g,float b,float a);
vector<CCPoint> makeTriangleSmaller(CCPoint v0,CCPoint v1,CCPoint v2,float d);
float calculateIncircleR2(CCPoint v0,CCPoint v1,CCPoint v2);
int findPointInPointList(const CCPoint&point,const vector<CCPoint>&pointList,float eps);
float calculateArea(CCPoint v0,CCPoint v1,CCPoint v2);
int randomSelectByProbility(const vector<float>&probilityList);
#endif /* defined(__HelloCpp__myFunc__) */
