//
//  SelectorProtocol.h
//  cocos2dxTest2
//
//  Created by Ilseob lee on 28/10/13.
//
//

#ifndef __cocos2dxTest2__SelectorProtocol__
#define __cocos2dxTest2__SelectorProtocol__

#include "ccTypes.h"
#include "CCObject.h"



namespace cocos2d{
    class CCNode;
    class CCEvent;
    
    class CC_DLL SelectorProtocol
    {
    public:
        virtual void update(ccTime dt){CC_UNUSED_PARAM(dt);};
        virtual void tick(ccTime dt){CC_UNUSED_PARAM(dt);};
        virtual void callfunc(){};
        virtual void callfunc(CCNode* pSender){CC_UNUSED_PARAM(pSender);};
		virtual void callfunc(CCNode* pSender, void* pData){CC_UNUSED_PARAM(pSender);CC_UNUSED_PARAM(pData);};
		virtual void menuHandler(CCObject* pSender){CC_UNUSED_PARAM(pSender);};
		virtual void eventHandler(CCEvent* pEvent) {CC_UNUSED_PARAM(pEvent);};
        
		// the child call responding retain/release function
		virtual void selectorProtocolRetain(void) {};
		virtual void selectorProtocolRelease(void) {};
	};
    
	class CCNode;
	typedef void (SelectorProtocol::*SEL_SCHEDULE)(ccTime);
    
	typedef void (SelectorProtocol::*SEL_CallFunc)();
	typedef void (SelectorProtocol::*SEL_CallFuncN)(CCNode*);
	typedef void (SelectorProtocol::*SEL_CallFuncND)(CCNode*, void*);
	typedef void (SelectorProtocol::*SEL_CallFuncO)(CCObject*);
	typedef void (SelectorProtocol::*SEL_MenuHandler)(CCObject*);
	typedef void (SelectorProtocol::*SEL_EventHandler)(CCEvent*);
    
#define schedule_selector(_SELECTOR) (SEL_SCHEDULE)(&_SELECTOR)
#define callfunc_selector(_SELECTOR) (SEL_CallFunc)(&_SELECTOR)
#define callfuncN_selector(_SELECTOR) (SEL_CallFuncN)(&_SELECTOR)
#define callfuncND_selector(_SELECTOR) (SEL_CallFuncND)(&_SELECTOR)
#define callfuncO_selector(_SELECTOR) (SEL_CallFuncO)(&_SELECTOR)
#define menu_selector(_SELECTOR) (SEL_MenuHandler)(&_SELECTOR)
#define event_selector(_SELECTOR) (SEL_EventHandler)(&_SELECTOR)
}
#endif /* defined(__cocos2dxTest2__SelectorProtocol__) */
