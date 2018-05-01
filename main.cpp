#include "headers/MaxRectsBinPack.h"
#include <cstdio>

int main(int argc, char **argv)
{
        // Bin's width and height to be taken from command line argument	
	if (argc != 3)
	{
		printf("Usage:   MaxRectsBinPackTest binWidth binHeight \n");
		printf("         where binWidth and binHeight define the size of the bin.\n");
		printf("Example: BinPack 256 256 \n");
		return 0;
	}
	
	MaxRectsBinPack bin;
	int binWidth = atoi(argv[1]);
	int binHeight = atoi(argv[2]);
	printf("Initializing bin to size %dx%d.\n", binWidth, binHeight);
	bin.Init(binWidth, binHeight);
	
        int N;
        cout << "Number of Rectagles:   ";
        cin >> N;
	for(int i=0;i<N;i++){
		int rectWidth, rectHeigh;
		scanf("Packing rectangle of size :  %d %d", &rectWidth, &rectHeight);

		MaxRectsBinPack::FreeRectChoiceHeuristic method = MaxRectsBinPack::RectBestShortSideFit; // This can be changed individually even for each rectangle packed.
		Rect packedRect = bin.Insert(rectWidth, rectHeight, method);

		if (packedRect.height > 0)
			printf("Packed to (x,y)=(%d,%d), (w,h)=(%d,%d). Free space left: %.2f%%\n", packedRect.x, packedRect.y, packedRect.width, packedRect.height, 100.f - bin.Occupancy()*100.f);
		else
			cout << "Failed! Could not find a proper position to pack this rectangle into. Skipping this one.\n";
	}
	cout << "Done. All rectangles packed.\n";
}
