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

void Insert(std::vector<RectSize> &rects, std::vector<Rect> &dst, FreeRectChoiceHeuristic method){
        /*  Something To Be Done Here   */
}

