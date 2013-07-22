#include "StbImage.h"

#include "stb_image.c"

StbImage::StbImage(string name)
{
	unsigned char *pixels = stbi_load(name.c_str(), &size_.x, &size_.y, &channels_, 0);
	for(int i=0; i<size_.y*size_.x*channels_; i++)
	{
		pixels_.push_back(pixels[i]);
	}
	stbi_image_free(pixels);
}

vector<unsigned char> StbImage::getPixels()
{
	return pixels_;
}

glm::ivec2 StbImage::getSize()
{
	return size_;
}

void StbImage::flipY()
{
	vector<unsigned char> res=pixels_;
	for(int y=0; y<size_.y; y++)
	{
		for(int x=0; x<size_.x*channels_; x++)
		{
			pixels_[size_.x*(size_.y-1-y)*channels_+x]=res[size_.x*y*channels_+x];
		}
	}
}

glm::vec4 StbImage::getRgba(glm::ivec2 position)
{
	glm::vec4 res;
	if(position.x<size_.x && position.y<size_.y)
	{
		//image width, row, channels (rgba=4) - col, channels, rgba (0123)
		for(int i=0; i<channels_; i++)
		{
			res[i]=(int)pixels_[size_.x*position.y*channels_+position.x*channels_+i];
		}

		//original code: reading color from image with 256px width, 4 channels at position (228, 239)
		//cout << (int)pixels[256*239*4+228*4+0] << endl;
		//cout << (int)pixels[256*239*4+228*4+1] << endl;
		//cout << (int)pixels[256*239*4+228*4+2] << endl;
		//cout << (int)pixels[256*239*4+228*4+3] << endl;
	}
	return res;
}