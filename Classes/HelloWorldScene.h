#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::CCLayerColor
{
public:
	HelloWorld();
	~HelloWorld();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);

	void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
	
	void update(float dt);

	void spriteMoveFinished(CCNode* sender);

private:
	static int score;

protected:
	    cocos2d::CCArray *_ScoreLabel;
};

#endif // __HELLOWORLD_SCENE_H__
