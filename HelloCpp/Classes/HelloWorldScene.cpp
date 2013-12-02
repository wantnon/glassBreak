#include "HelloWorldScene.h"
#include "AppMacros.h"
USING_NS_CC;
#include "CCControlButton.h"
using namespace cocos2d;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

 /*   /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);
*/
    /////////////////////////////
    // 3. add your codes below...
    //enable touch
	setTouchEnabled( true );
    //set projection to 2D (default is 3D). if use 3D projection, may cause tiny projection error, in some situation, if the error accumulated across frames, may cause effect wrong.
    CCDirector::sharedDirector()->setProjection(kCCDirectorProjection2D);
    //sinSize
    CCSize winSize=CCDirector::sharedDirector()->getWinSize();//winSize equals to designResolutionSize
    //show frame rate info
    CCDirector::sharedDirector()->setDisplayStats(true);
    //back ground sprite
    CCSprite*backGround=new CCSprite();
    backGround->autorelease();
    backGround->initWithFile("wall.png");
    backGround->setPosition(ccp(winSize.width/2, winSize.height/2));
    this->addChild(backGround,0);
    //frame sprite
    CCSprite*frameSprite=new CCSprite();
    frameSprite->autorelease();
    frameSprite->initWithFile("frame.png");
    frameSprite->setPosition(ccp(winSize.width/2, winSize.height/2));
    this->addChild(frameSprite,3);
    //glassSprite
    glassSprite=new CglassSprite();
    glassSprite->autorelease();
    glassSprite->init("pic.png",CCPoint(cosf(-60*M_PI/180),sinf(-60*M_PI/180)));
    glassSprite->setAnchorPoint(ccp(0.5, 0.5));
    glassSprite->setPosition(ccp(winSize.width/2, winSize.height/2));
    this->addChild(glassSprite,2);
    //wood base sprite
    CCSprite*woodBase=new CCSprite();
    woodBase->autorelease();
    woodBase->initWithFile("woodBase.png");
    woodBase->setPosition(ccp(winSize.width/2, winSize.height/2));
    this->addChild(woodBase,1);
    
/*    //slider
	{
		CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
		CCControlSlider *slider = CCControlSlider::create("sliderTrack.png","sliderProgress.png" ,"sliderThumb.png");
		slider->setAnchorPoint(ccp(0.5f, 0.5f));
		slider->setMinimumValue(0.0f); // Sets the min value of range
		slider->setMaximumValue(1.0f); // Sets the max value of range
		slider->setValue(0);
		slider->setPosition(ccp(screenSize.width / 2.0f, screenSize.height / 4.0f));
		slider->addTargetWithActionForControlEvents(this, cccontrol_selector(HelloWorld::sliderAction), CCControlEventValueChanged);
		m_pSliderCtl=slider;
		this->addChild(m_pSliderCtl,100);
		//title
		CCLabelTTF* pLabel = CCLabelTTF::create("R ", "Arial", 30);
		pLabel->setPosition(ccp(slider->getPositionX()-slider->getContentSize().width/2-pLabel->getContentSize().width/2, slider->getPositionY()));
        this->addChild(pLabel, 1);
	}
	  */
    //----menu0
    {
        CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
        
        CCLabelTTF* pLabel0 = CCLabelTTF::create("even", "Arial", 25);
        CCLabelTTF* pLabel1 = CCLabelTTF::create("density", "Arial", 25);
        
        pMenuItem0 = CCMenuItemImage::create("btn.png","btn_dn.png",this,menu_selector(HelloWorld::menuItem0Callback));
        pMenuItem0->setPosition(CCPointZero);
        pMenuItem0->addChild(pLabel0,10);
        pLabel0->setPosition(ccp(pMenuItem0->getContentSize().width/2,pMenuItem0->getContentSize().height/2));
        
        pMenuItem1 = CCMenuItemImage::create("btn.png","btn_dn.png",this,menu_selector(HelloWorld::menuItem1Callback));
        pMenuItem1->setPosition(pMenuItem0->getPosition()-ccp(0,pMenuItem0->getContentSize().height));
        pMenuItem1->addChild(pLabel1,10);
        pLabel1->setPosition(ccp(pMenuItem1->getContentSize().width/2,pMenuItem1->getContentSize().height/2));
        
        pMenu0 = CCMenu::create(pMenuItem0, pMenuItem1,NULL);
        pMenu0->setPosition(ccp(screenSize.width*(5.0/6), screenSize.height*(3.0/4)));
        this->addChild(pMenu0, 10);
        
        checkPic = CCSprite::create();
        checkPic->initWithFile("check.png");
        checkPic->setPosition(ccp(pMenuItem0->getContentSize().width+checkPic->getContentSize().width/2,pMenuItem0->getContentSize().height/2));
        
        pMenuItem0->addChild(checkPic);
    }

    
    // author info
    {
        CCLabelTTF* pLabel = CCLabelTTF::create("by yang chao (wantnon) 2013-12-1", "Arial", 30);
        pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - pLabel->getContentSize().height-59));
        this->addChild(pLabel, 10);
    }
    
    // add a label shows "Hello World"
    // create and initialize a label
 
    CCLabelTTF* pLabel = CCLabelTTF::create("Glass Break Demo", "Arial", 45);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 10);
  
   
    
    return true;
}

void HelloWorld::menuItem0Callback(CCObject* pSender){
    checkPic->retain();
    checkPic->removeFromParentAndCleanup(false);
    pMenuItem0->addChild(checkPic);
    checkPic->release();
    checkPic->setPosition(ccp(pMenuItem0->getContentSize().width+checkPic->getContentSize().width/2,pMenuItem0->getContentSize().height/2));
    //
    glassSprite->breakMode=eBreakMode_even;
    
    
    
}

void HelloWorld::menuItem1Callback(CCObject* pSender){
    checkPic->retain();
    checkPic->removeFromParentAndCleanup(false);
    pMenuItem1->addChild(checkPic);
    checkPic->release();
    checkPic->setPosition(ccp(pMenuItem1->getContentSize().width+checkPic->getContentSize().width/2,pMenuItem1->getContentSize().height/2));
    //
    glassSprite->breakMode=eBreakMode_density;
    
}

void HelloWorld::sliderAction(CCObject* sender, CCControlEvent controlEvent)
{
    CCControlSlider* pSlider = (CCControlSlider*)sender;
    float value=pSlider->getValue();
    CCLOG("slider value:%f",value);
    
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}


void HelloWorld::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSetIterator it;
    CCTouch* touch;
    
    for( it = touches->begin(); it != touches->end(); it++)
    {
        touch = (CCTouch*)(*it);
        
        if(!touch)
            break;
        
        CCPoint loc_winSpace = touch->getLocationInView();
        CCPoint loc_GLSpace = CCDirector::sharedDirector()->convertToGL(loc_winSpace);

        break;
    }
}
void HelloWorld::ccTouchesMoved(cocos2d::CCSet* touches , cocos2d::CCEvent* event)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSetIterator it;
    CCTouch* touch;
    for( it = touches->begin(); it != touches->end(); it++)
    {
        touch = (CCTouch*)(*it);
        
        if(!touch)
            break;
        
        CCPoint loc_winSpace = touch->getLocationInView();
        CCPoint loc_GLSpace = CCDirector::sharedDirector()->convertToGL(loc_winSpace);

    
        
		break;
    }
    
}

void HelloWorld::ccTouchesBegan(CCSet* touches, CCEvent* event)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSetIterator it;
    CCTouch* touch;
	for( it = touches->begin(); it != touches->end(); it++)
    {
        touch = (CCTouch*)(*it);
        if(!touch)
            break;
        
        CCPoint loc_winSpace = touch->getLocationInView();
        CCPoint loc_GLSpace = CCDirector::sharedDirector()->convertToGL(loc_winSpace);
        //CCLOG("loc_GLSpace:%f,%f",loc_GLSpace.x,loc_GLSpace.y);
        if(this->glassSprite->boundingBox().containsPoint(loc_GLSpace)){
            this->glassSprite->touchPoint=this->glassSprite->convertToNodeSpace(loc_GLSpace);
            this->glassSprite->updateState();
            if(glassSprite->state!=eGlassState_perfect){
                this->pMenuItem0->setVisible(false);
                this->pMenuItem1->setVisible(false);
            }else{
                this->pMenuItem0->setVisible(true);
                this->pMenuItem1->setVisible(true);
            }
        }
        break;
    }
}

