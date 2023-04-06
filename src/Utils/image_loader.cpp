#include "image_loader.h"
#define STB_IMAGE_IMPLEMENTATION 
#include "stb_image.h"

image util::load_image_from_file(const char* fname, int dc ) {
	image result; 
	result.pixels = stbi_load(fname, &(result.w), &(result.h), &(result.chnls), dc);
	return result;
}

void util::free_image_mem(image img) {
	stbi_image_free(img.pixels);
}