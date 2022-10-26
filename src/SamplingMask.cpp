#include "../include/SamplingMask.h"
#include <cstring>

SamplingMask::SamplingMask(size_t w, size_t h, size_t phases)
	: m_width(w), m_height(h), m_phases(phases)
{
	m_data = new int[m_width * m_height * m_phases];
}

SamplingMask::~SamplingMask()
{
	delete m_data;
}

int *SamplingMask::data()
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
		m_data[phase*(m_width*m_height) + height*m_width + i] = dataPointer[i];
	}
}
