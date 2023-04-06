#pragma once 
#include "../config.h"

struct image {
	unsigned char* pixels;
	int w, h, chnls;
};

namespace util {
	image load_image_from_file(const char* fname, int dc);
	void free_image_mem(image img);
}