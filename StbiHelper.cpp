#include "StbiHelper.h"

glm::vec4 StbiHelper::getRgba(unsigned char *pixels, int width, int height, int channels, unsigned int x, unsigned int y)
{
	glm::vec4 res;
	if(x<width && y<height)
	{
		//image width, row, channels (rgba=4) - col, channels, rgba (0123)
		for(int i=0; i<channels; i++)
		{
			res[i]=(int)pixels[width*y*channels+x*channels+i];
		}

		//original code: reading color from image with 256px width, 4 channels at position (228, 239)
		//cout << (int)pixels[256*239*4+228*4+0] << endl;
		//cout << (int)pixels[256*239*4+228*4+1] << endl;
		//cout << (int)pixels[256*239*4+228*4+2] << endl;
		//cout << (int)pixels[256*239*4+228*4+3] << endl;
	}
	return res;
}

unsigned char *StbiHelper::flipY(unsigned char *pixels, int width, int height, int channels)
{
	unsigned char *res=new unsigned char[width*height*channels];
	for(int y=0; y<height; y++)
	{
		for(int x=0; x<width*channels; x++)
		{
			res[width*(height-1-y)*channels+x]=pixels[width*y*channels+x];
		}
	}
	return res;
}