#include "Body.h"

CBody::CBody(std::string type)
	:m_type(type),
	m_parent(nullptr)
{

};

CBody* CBody::GetParent() const
{
	return m_parent;
};

void CBody::SetParent(CBody* parent)
{
	m_parent = parent;
}

std::string CBody::GetType() const
{
	return m_type;
};

std::string CBody::ToString() const
{
	/*Выводит ниформацию о теле: тип тела, масса, объем, плотность*/
	std::ostringstream info;
	info << "Body type is " << m_type << ". "
		 << "Massa is " << round(GetMass() * 1000) / 1000 << ". "
	     << "Volume is " << round(GetVolume() * 1000) / 1000 << ". "
		 << "Density is " << round(GetDensity() * 1000) / 1000 << ". ";
	/*Реализовать строковое представление о каждом объекте(индивидуальные свойства), избавиться от enum*/
	AppendProperties(info);

	return info.str();
};