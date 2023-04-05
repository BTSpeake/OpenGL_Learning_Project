#include "lighting.h"

Light::Light(LightCreateInfo* createInfo) {
	this->pos = createInfo->pos;
	this->col = createInfo->col;
	this->strength = createInfo->strength;
}

Light::~Light() {

}