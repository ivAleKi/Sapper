#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "GameOverScene.h"

USING_NS_CC;

int HelloWorld::score = 0;

CCScene* HelloWorld::scene() {
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
bool HelloWorld::init() {
     bool bRet = false;
	 do {
         //////////////////////////////////////////////////////////////////////////
         // super init first
         //////////////////////////////////////////////////////////////////////////
 
        CC_BREAK_IF(! CCLayer::init());

		if ( !CCLayerColor::initWithColor( ccc4(255,255,255,255) ) )
		{
			return false;
		}
		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
		CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

		/////////////////////////////
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

		/////////////////////////////
		// 3. add your codes below...

		// add a label shows "Hello World"
		// create and initialize a label
    
		CCLabelTTF* pLabel = CCLabelTTF::create("", "Arial", 24);
    
		// position the label on the center of the screen
		pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
								origin.y + visibleSize.height - pLabel->getContentSize().height));

		// add the label as a child to this layer
		this->addChild(pLabel, 1);

		// add "HelloWorld" splash screen"
		CCSprite* pSprite = CCSprite::create("background.png");

		// position the sprite on the center of the screen
		pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

		// add the sprite as a child to this layer
		this->addChild(pSprite, 0);

	        bRet = true;
    } while (0);

	this->setTouchEnabled(true);

	_ScoreLabel = new CCArray;

	this->schedule( schedule_selector(HelloWorld::update) );  

	//CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(
	//"background-music-aac.wav", true);
    
    return bRet;
}


void HelloWorld::menuCloseCallback(CCObject* pSender) {
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::ccTouchesEnded(CCSet* touches, CCEvent* event) {

	//CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(
	//"pew-pew-lei.wav");

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	// Set up initial location of ScoreLabel
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCLabelTTF *ScoreLabel = CCLabelTTF::create("0", "Arial", 24);
    ScoreLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - ScoreLabel->getContentSize().height));
	this->addChild(ScoreLabel);

    score++;
	CCString * scoreb = CCString::createWithFormat("%i", score); 
	ScoreLabel->setString(scoreb->getCString());
	
	// Надо исправить
	/*
	ScoreLabel->runAction(
		CCCallFuncN::create(this, 
		callfuncN_selector(HelloWorld::spriteMoveFinished)));
	*/

	// Add to projectiles array
	ScoreLabel->setTag(1);
	_ScoreLabel->addObject(ScoreLabel);
}

void HelloWorld::spriteMoveFinished(CCNode* sender)
{
	CCLabelTTF *label = (CCLabelTTF *)sender;
	this->removeChild(label, false);
	if (label->getTag() == 1) // ScoreLabel
	{
		_ScoreLabel->removeObject(label);
		GameOverScene *gameOverScene = GameOverScene::create();
		gameOverScene->getLayer()->getLabel()->setString("You Lose :[");
		CCDirector::sharedDirector()->replaceScene(gameOverScene);
	}
}

HelloWorld::~HelloWorld()
{
	if (_ScoreLabel)
	{
		_ScoreLabel->release();
		_ScoreLabel = NULL;
	}
  // cpp don't need to call super dealloc
  // virtual destructor will do this
}

HelloWorld::HelloWorld():_ScoreLabel(NULL) {}

void HelloWorld::update(float dt) {
	CCArray *ScoreToDelete = new CCArray;
    CCObject* sc = NULL;

	CCARRAY_FOREACH(ScoreToDelete, sc) {
        CCLabelTTF* ScoreLabel = dynamic_cast<CCLabelTTF*>(sc);
        _ScoreLabel->removeObject(ScoreLabel);
        this->removeChild(ScoreLabel, true);
    }

	ScoreToDelete->release();
}