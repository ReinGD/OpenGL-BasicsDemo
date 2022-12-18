/*====================
	MADE BY REINGD
====================*/
#include "VBOData.h"
#include <cassert>

VBOData::VBOData()
	:enabled(0), glIndex(0), attributeIndex(0),count(0), dataSize(0), dataWidth(0), pData(nullptr)
{
}

VBOData::~VBOData()
{
	delete[] this->pData;
	this->pData = nullptr;
}

VBOData::VBOData(bool enabled, unsigned int count, unsigned int attributeIndex, unsigned int datasize, unsigned int dataWidth, void* pData)
	:enabled(enabled), glIndex(0), attributeIndex(attributeIndex), count(count), dataSize(datasize), dataWidth(dataWidth)
{
	this->pData = new unsigned char[this->dataSize]();
	assert(this->pData);
	memcpy_s(this->pData, this->dataSize, pData, datasize);
}

void VBOData::Clean()
{
	enabled = false;
	glIndex = 0;
	attributeIndex = 0;
	count = 0;
	dataSize = 0;
	dataWidth = 0;
	delete[] this->pData;
	this->pData = nullptr;
}


VBOData::VBOData(const VBOData& in)
{
	this->enabled = in.enabled;
	this->glIndex = in.glIndex;
	this->attributeIndex = in.attributeIndex;
	this->count = in.count;
	this->dataSize = in.dataSize;
	this->dataWidth = in.dataWidth;

	this->pData = new unsigned char[this->dataSize]();
	assert(this->pData);
	memcpy_s(this->pData, this->dataSize, in.pData, in.dataSize);
}

VBOData& VBOData::operator=(const VBOData& in)
{
	if (this != &in)
	{
		delete[] this->pData;
		this->pData = nullptr;

		this->enabled = in.enabled;
		this->glIndex = in.glIndex;
		this->attributeIndex = in.attributeIndex;
		this->count = in.count;
		this->dataSize = in.dataSize;
		this->dataWidth = in.dataWidth;

		this->pData = new unsigned char[this->dataSize]();
		assert(this->pData);
		memcpy_s(this->pData, this->dataSize, in.pData, in.dataSize);
	}

	return *this;
}
