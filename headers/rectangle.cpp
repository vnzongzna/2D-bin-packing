#include"rectangle.h"

bool IsContainedIn(const Rect &a, const Rect &b)
{
	return a.x >= b.x && a.y >= b.y 
		&& a.x+a.width <= b.x+b.width 
		&& a.y+a.height <= b.y+b.height;
}

 //int CompareRectShortSide(const Rect &a, const Rect &b){
        /* Nothing to be declared yet   */
 //}
 
 //int NodeSortCmp(const Rect &a, const Rect &b){
        /* NOthing to be declared yet   */
 //}
