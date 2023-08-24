#include "MultiRC.h"

MultiRC::MultiRC(std::shared_ptr<RenderComponent> rc) : rc(rc){

}

void MultiRC::push(Sprite& parent, PixelDim pos, float rot, bool flipX, bool flipY) const{
	rc->push(parent, pos, rot, flipX, flipY);
}


