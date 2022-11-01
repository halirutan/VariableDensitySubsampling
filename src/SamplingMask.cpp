#include "../include/SamplingMask.h"
#include <cassert>
#include <iostream>
#include <sstream>

SamplingMask::SamplingMask(size_t w, size_t h, size_t phases)
	: m_width(w), m_height(h), m_phases(phases), m_data_size(m_width * m_height * m_phases), m_data(new int[m_data_size])
{}

std::shared_ptr<int[]> SamplingMask::data()
{ return m_data; }

size_t SamplingMask::height() const
{ return m_height; }

size_t SamplingMask::width() const
{ return m_width; }

size_t SamplingMask::phases() const
{
	return m_phases;
}

void SamplingMask::setLine(size_t height, size_t phase, const int *dataPointer)
{
	// Copy m_width number of elements from dataPointer to data[phase*(m_width*m_height) + height*(m_width)]
	//	std::memcpy(m_data + phase*(m_width*m_height) + height*(m_width), dataPointer, m_width*sizeof(int));
	for (size_t i = 0; i < m_width; ++i) {

		// x - width
		// y - height
		// z - phase
		// z * nx * ny + y * nx + i


		std::ptrdiff_t ptr = phase * (m_width * m_height) + height * m_width + i;
		m_data[ptr] = dataPointer[i];
	}
}

std::string SamplingMask::toDebugString() const
{
	std::stringstream result;
	for (size_t p = 0; p < m_phases; p++) {
		result << "phase " << p << "[" << std::endl;
		for (size_t h = 0; h < m_height; h++) {
			for (size_t w = 0; w < m_width; w++) {
				result << (get(w, h, p) == 1 ? "■" : "□");
			}
			result << std::endl;
		}
		result << "]" << p << std::endl;
	}
	return result.str();
}

int SamplingMask::get(size_t w, size_t h, size_t p) const
{
	size_t ptr = p * (m_width * m_height) + h * m_width + w;
	assert(ptr < m_data_size);
	return m_data[ptr];
}
