#include "MaxRectanglePack.h"

MaxRectanglePack::MaxRectanglePack: binWidth(0) , binHeight(0) {}

MaxRectanglePack::MaxRectanglePack(int width, int height, bool allowFlip = true) 
        {   Init(width,height,allowFlip);   }

void MaxRectanglePack::Init(int width, int height, bool allowFlip = true){
        binWidth = width;
        binHeight = height;
        binAllowFlip = allowFlip;
        freeRectangles.clean();
        usedrectangles.clean();
        freeRectangles.push_back(Rect{0,0,width,height});
}
Rect FindPositionForNewNodeBottomLeft(int width, int height)
{    
    int bestY=__INT_MAX__;
    int bestX=__INT_MAX__;
 for(int i=0;i<freeRectangles.size();i++ )
 {
     if(freeRectangles[i].height>=height && freeRectangles[i].width>=width)
     {
         int topsideY=freeRectangles[i].y+height;
         int rightsideX=freeRectangles[i].x+width;
         if(topsideY<bestY || topsideY==bestY && rightsideX<bestX)
         { bestNode.x=freeRectangles[i].x;
         bestNode.y=freeRectangles[i].y;
         bestNode.width=width;
         bestNode.height=height;
         bestY=topsideY;
         bestX=rightsideX;
         }
    }
    if(binAllowFlip && freeRectangles[i].height>=width && freeRectangles[i].width>=height)
    {
        int topsideY=freeRectangles[i].y+width;
        int rightsideX=freeRectangles[i].x+height;
        if(topsideY<bestY || topsideY==bestY && rightsideX<bestX)
        {
            bestNode.x=freeRectangles[i].x;
            bestNode.y=freeRectangles[i].y;
            bestNode.width=width;
            bestNode.height=height;
            bestY=topsideY;
            bestX=rightsideX;
        }
    }
 }
 return bestNode;
}
void Insert(std::vector<RectSize> &rects, std::vector<Rect> &dst, FreeRectChoiceHeuristic method)
{
        /*  Something To Be Done Here   */
}

