

#define SAFE_NEW new
#define SAFE_DELETE(ptr) {if (ptr != NULL) {delete ptr; ptr = NULL;}}
#define SAFE_DELETEARRAY(ptr) {if (ptr != NULL) {delete[] ptr; ptr = NULL;}}

#define SafeMalloc(iSize) malloc(iSize)
#define SafeFree(pObj)  {if(pObj) {free(pObj); pObj = NULL;}}
#define SafeNew new
#define SafeDelete(pobj) {if (pobj){delete pobj;pobj = NULL;}}

#define  ID_TIMER 1

#define TIMERID_GAME 1
#define MOMENT_TIME 30
#define MAX_MOMENT_TIME 1000

#define ASCII_NUM 256 // the keyboard's ascii code



#define MAX_SCREEN_W 1600 
#define MAX_SCREEN_H 1200


//#define SCREEN_W 1280 //800 // 屏幕的逻辑宽度 screen's logic width
//#define SCREEN_H 800 //600 屏幕的逻辑高度 screen's logic height
//853.492

#define GAME_SCREEN_W 800 // 屏幕的逻辑宽度 screen's logic width
#define GAME_SCREEN_H 600 // 屏幕的逻辑高度 screen's logic height
//533.369

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 640


#define ENABLE_CONSOLE
#define DEBUG_INFOS
#define ENABLE_PRINTLOG

#ifdef ENABLE_PRINTLOG
#define PRINTLOG printf
#else
#define PRINTLOG //;
#endif
