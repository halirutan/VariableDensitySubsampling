#pragma once

#include <cstddef>

/**
 * Simple volume class for interfacing with pybind11.
 * The original implementation uses nested pointers to represent a matrix, but
 * numpy expects flat memory representation.
 */
class SamplingMask
{
public:
    SamplingMask(size_t w, size_t h, size_t phases);

	~SamplingMask();
	/**
	 * The memory for data is not deleted on destruction of the object!
	 * The reason is that is only for interfacing with Python/numpy and Python
	 * should take over the ownership of this memory.
	 * @return Pointer to the sampling mask memory
	 */
    int *data();

    [[nodiscard]] size_t height() const;
    [[nodiscard]] size_t width() const;
    [[nodiscard]] size_t phases() const;
	void setLine(size_t height, size_t phase, const int *dataPointer);
private:
    size_t m_width, m_height, m_phases;
    int *m_data;

};
