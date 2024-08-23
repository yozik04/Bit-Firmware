#ifndef BIT_FIRMWARE_ALLOCATOR_H
#define BIT_FIRMWARE_ALLOCATOR_H


#include <cstddef>
#include <cstdint>

class Allocator{
public:
	explicit Allocator(const size_t dataSize);

	void* malloc(size_t size);
	void reset();

	size_t freeSize();

private:
	const size_t dataSize;
	uint8_t* data;
	size_t pointer = 0;

};


#endif //BIT_FIRMWARE_ALLOCATOR_H
