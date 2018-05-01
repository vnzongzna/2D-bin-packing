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


 Rect MaxRectsBinPack::FindPositionForNewNodeBestAreaFit(int width, int height,
	int &bestAreaFit, int &bestShortSideFit) const
{
	Rect bestNode;
	memset(&bestNode, 0, sizeof(Rect));

	bestAreaFit = std::numeric_limits<int>::max();
	bestShortSideFit = std::numeric_limits<int>::max();

	for(size_t i = 0; i < freeRectangles.size(); ++i)
	{
		//int areaFit = freeRectangles[i].width * freeRectangles[i].height - width * height;
          int areaFit = freeRectangles[i].width * freeRectangles[i].height;
		// Try to place the rectangle in upright (non-flipped) orientation.
		if (freeRectangles[i].width >= width && freeRectangles[i].height >= height)
		{
			int leftoverHoriz = abs(freeRectangles[i].width - width);
			int leftoverVert = abs(freeRectangles[i].height - height);
			int shortSideFit = min(leftoverHoriz, leftoverVert);

			if (areaFit < bestAreaFit || (areaFit == bestAreaFit && shortSideFit < bestShortSideFit))
			{
				bestNode.x = freeRectangles[i].x;
				bestNode.y = freeRectangles[i].y;
				bestNode.width = width;
				bestNode.height = height;
				bestShortSideFit = shortSideFit;
				bestAreaFit = areaFit;
			}
		}

		if (binAllowFlip && freeRectangles[i].width >= height && freeRectangles[i].height >= width)
		{
			int leftoverHoriz = abs(freeRectangles[i].width - height);
			int leftoverVert = abs(freeRectangles[i].height - width);
			int shortSideFit = min(leftoverHoriz, leftoverVert);

			if (areaFit < bestAreaFit || (areaFit == bestAreaFit && shortSideFit < bestShortSideFit))
			{
				bestNode.x = freeRectangles[i].x;
				bestNode.y = freeRectangles[i].y;
				bestNode.width = height;
				bestNode.height = width;
				bestShortSideFit = shortSideFit;
				bestAreaFit = areaFit;
			}
		}
	}
	return bestNode;
}

/// Returns 0 if the two intervals i1 and i2 are disjoint, or the length of their overlap otherwise.
int CommonIntervalLength(int i1start, int i1end, int i2start, int i2end)
{
	if (i1end < i2start || i2end < i1start)
		return 0;
	return min(i1end, i2end) - max(i1start, i2start);
}

int MaxRectsBinPack::ContactPointScoreNode(int x, int y, int width, int height) const
{
	int score = 0;

	if (x == 0 || x + width == binWidth)
		score += height;
	if (y == 0 || y + height == binHeight)
		score += width;

	for(size_t i = 0; i < usedRectangles.size(); ++i)
	{
		if (usedRectangles[i].x == x + width || usedRectangles[i].x + usedRectangles[i].width == x)
			score += CommonIntervalLength(usedRectangles[i].y, usedRectangles[i].y + usedRectangles[i].height, y, y + height);
		if (usedRectangles[i].y == y + height || usedRectangles[i].y + usedRectangles[i].height == y)
			score += CommonIntervalLength(usedRectangles[i].x, usedRectangles[i].x + usedRectangles[i].width, x, x + width);
	}
	return score;
}

Rect MaxRectsBinPack::FindPositionForNewNodeContactPoint(int width, int height, int &bestContactScore) const
{
	Rect bestNode;
	memset(&bestNode, 0, sizeof(Rect));

	bestContactScore = -1;

	for(size_t i = 0; i < freeRectangles.size(); ++i)
	{
		// Try to place the rectangle in upright (non-flipped) orientation.
		if (freeRectangles[i].width >= width && freeRectangles[i].height >= height)
		{
			int score = ContactPointScoreNode(freeRectangles[i].x, freeRectangles[i].y, width, height);
			if (score > bestContactScore)
			{
				bestNode.x = freeRectangles[i].x;
				bestNode.y = freeRectangles[i].y;
				bestNode.width = width;
				bestNode.height = height;
				bestContactScore = score;
			}
		}
		if (freeRectangles[i].width >= height && freeRectangles[i].height >= width)
		{
			int score = ContactPointScoreNode(freeRectangles[i].x, freeRectangles[i].y, height, width);
			if (score > bestContactScore)
			{
				bestNode.x = freeRectangles[i].x;
				bestNode.y = freeRectangles[i].y;
				bestNode.width = height;
				bestNode.height = width;
				bestContactScore = score;
			}
		}
	}
	return bestNode;
=======
Rect MaxRectsBinPack::Insert(int width, int height, FreeRectChoiceHeuristic method)
        Rect temp;
        switch(method){
                case RectBestShortSideFit: Node = FindPositionForNewNodeBestShortSideFit(width, height, score1, score2); break;
		case RectBottomLeftRule: Node = FindPositionForNewNodeBottomLeft(width, height); break;
		case RectContactPointRule: Node = FindPositionForNewNodeContactPoint(width, height, score1); break;
		case RectBestLongSideFit: Node = FindPositionForNewNodeBestLongSideFit(width, height, score2, score1); break;
		case RectBestAreaFit: Node = FindPositionForNewNodeBestAreaFit(width, height, score1, score2); break;
       }
        if(Node.height == 0)
                return Node;
       size_t rectangleToProcess = freeRectangles.size();
       for(int i=0;i<rectangleToProcess;i++){
                if(SplitFreeRectangle(i,Node)){
                        freeRectangles.erase(freeRectangles.begin()+i);
                        --i;
                        --rectangleToProcess;
                }
        }
        FixFreeList();
        usedrectangles.push_back(Node);
        return Node;

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

bool MaxRectanglePack::SplitFreeRectangle(int freeIndex,Rect Node){
        Rect free=freeRectangles[freeIndex];
        if(free.x >= Node.x+Node.height || free.x + free.height <= Node.x ||
                        free.y >= Node.y+Node.height || free.y + free.height =< Node.y)
                return false;
        if(free.x < Node.x + Node.width && free.x+free.width > Node.x){
                // case of split by bottom of rectangle
                if(Node.y > free.y && Node.y < free.y+free.height){
                        Rect C = free;
                        C.height=Node.y - C.y;
                        freeRectangles.push_back(C);
                }
                //case of split by ceiling of rectangle
                if(Node.y < free.y && Node.y+Node.height > free.y){
                        Rect C = free;
                        C.y = Node.y+Node.height
                                C.height=free.y+free.height - C.y;
                        freeRectangles.push_back(C);
                }
        }
        if(free.y < Node.y + Node.height && free.y+free.height > Node.y){
                // case of split by left side of rectangle
                if(Node.x > free.x && Node.x < free.x+free.width){
                        Rect C = free;
                        C.width=Node.x - C.x;
                        freeRectangles.push_back(C);
                }
                //case of split by right side of rectangle
                if(Node.x < free.x && Node.x+Node.width > free.x){
                        Rect C = free;
                        C.x = Node.x+Node.width
                                C.width=free.x+free.width - C.x;
                        freeRectangles.push_back(C);
                }
        }
        return true;
}

void MaxRectsBinPack::FixFreeList(){
	for(size_t i = 0; i < freeRectangles.size(); ++i)
		for(size_t j = i+1; j < freeRectangles.size(); ++j)
		{
			if (IsContainedIn(freeRectangles[i], freeRectangles[j]))
			{
				freeRectangles.erase(freeRectangles.begin()+i);
				--i;
				break;
			}
			if (IsContainedIn(freeRectangles[j], freeRectangles[i]))
			{
				freeRectangles.erase(freeRectangles.begin()+j);
				--j;
			}
		}
}
