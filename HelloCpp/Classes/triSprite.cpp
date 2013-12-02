

#include "triSprite.h"
void CtriSprite::update(float t){
    vy+=gravityFactor;
    CCPoint pos=this->getPosition();
    this->setPosition(pos+ccp(0,-vy));
    
}
bool CtriSprite::init(CCTexture2D*texture,
          CCPoint v0,CCPoint v1,CCPoint v2,
          CCPoint texCoord0,CCPoint texCoord1,CCPoint texCoord2)
{
    //save v0~2 to vlist and texCoord0~2 to texCoordList
    vlist[0]=v0;vlist[1]=v1;vlist[2]=v2;
    texCoordList[0]=texCoord0;texCoordList[1]=texCoord1;texCoordList[2]=texCoord2;
    //init sprite
    this->initWithTexture(texture);//do not use setTexture()
    //create indexVBO
    indexVBO->genBuffers();
    // create model
    float posArray[6]={vlist[0].x,vlist[0].y,
        vlist[1].x,vlist[1].y,
        vlist[2].x,vlist[2].y};
    int indexArray[3]={0,1,2};
    float texCoordArray[6]={texCoordList[0].x,texCoordList[0].y,
        texCoordList[1].x,texCoordList[1].y,
        texCoordList[2].x,texCoordList[2].y};
    //submit data to VBO
    indexVBO->submitPos(posArray,6,GL_STATIC_DRAW);
    indexVBO->submitIndex(indexArray,3,GL_STATIC_DRAW);
    indexVBO->submitTexCoord(texCoordArray,6,GL_STATIC_DRAW);
    //check gl error
    CHECK_GL_ERROR_DEBUG();
    //texture antiAlias
    this->getTexture()->setAntiAliasTexParameters();
    return true;
}
void CtriSprite::draw(){
    //----change shader
    this->setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTexture));
    ccGLEnable(m_eGLServerState);
    //pass values for cocos2d-x build-in uniforms
    getShaderProgram()->use();
    getShaderProgram()->setUniformsForBuiltins();
    //----enable attribute arrays (must do every frame)
    CindexVBO::enableAttribArrays();
    //----bindTexture
    ccGLBindTexture2D( this->getTexture()->getName());//do not use glBindTexture2D, or next sprite use cocos2d-x default draw may be affected
    //----draw
    indexVBO->setPointers();
    indexVBO->draw(GL_TRIANGLES);
    //----unbindTexture
    ccGLBindTexture2D(0);//do not use glBindTexture2D, or next sprite use cocos2d-x default draw may be affected
    //----draw lines
    //no need to set shader, because ccDrawLine will do this job for us
    
    glLineWidth(2);
    float ambientColor[]={213.0/255*0.5,178.0/255*0.5,78.0/255*0.5,1};
    for(int edgeID=0;edgeID<3;edgeID++){
        CCPoint startPoint=vlist[edgeID];
        CCPoint endPoint=vlist[(edgeID+1)%3];
        //calculate normal of edge
        CCPoint startToEnd=endPoint-startPoint;
        CCPoint normal=ccpNormalize(CCPoint(startToEnd.y,-startToEnd.x));
        float diffuse=MAX(0,ccpDot(-lightDir, normal));
        float diffuseColor[]={diffuse,diffuse,diffuse,1};
        float color[]={MIN(1,diffuseColor[0]+ambientColor[0]),
            MIN(1,diffuseColor[1]+ambientColor[1]),
            MIN(1,diffuseColor[2]+ambientColor[2]),
            diffuseColor[3]};
        ccDrawColor4B(255*color[0], 255*color[1], 255*color[2], 255*color[3]);
        ccDrawLine(startPoint,endPoint);
    }
    ccDrawColor4B(255, 255, 255, 255);
    glLineWidth(1);
}

