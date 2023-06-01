#include "Parallelepiped.h"

CParallelepiped::CParallelepiped(double density, double height, double width, double depth)
	: CSolidBody("parallelepiped", density),
	m_height(height),
	m_width(width),
	m_depth(depth)
{
};

double CParallelepiped::GetDepth() const
{
	return m_depth;
};

double CParallelepiped::GetHeight() const
{
	return m_height;
};

double CParallelepiped::GetWidth() const
{
	return m_width;
};

double CParallelepiped::GetVolume() const
{
	return m_depth * m_height * m_width;
};

void CParallelepiped::AppendProperties(std::ostream& strm) const
{
	strm << "Height is " << round(GetHeight() * 1000) / 1000 << ". "
		<< "Width is " << round(GetWidth() * 1000) / 1000 << ". "
		<< "Depth is " << round(GetDepth() * 1000) / 1000 << ".";

};