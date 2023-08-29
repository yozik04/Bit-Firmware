#ifndef BIT_FIRMWARE_BLOCK_H
#define BIT_FIRMWARE_BLOCK_H

#include "Color.h"
#include "GameEngine/GameObject.h"

class Block {
public:
	enum class Type {
		Line = 1,
		Cube = 2,
		T = 3,
		L = 4,
		ReverseL = 5,
		S = 6,
		ReverseS = 7
	} type;
	File file;
	GameObjPtr segments[4];
	PixelDim gridPos;
	uint8_t rotation = 0;

	Block(Type type, File f, const PixelDim& gridPos);
	void setPos(PixelDim gridPos);
	PixelDim getPos() const;
	void rotate(const bool* blocksMatrix);
	void placed(File placed);
	void clearSegment(GameObjPtr segment);
private:
	void rotate();
};

#endif //BIT_FIRMWARE_BLOCK_H
