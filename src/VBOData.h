#ifndef VBO_DATA_H
#define VBO_DATA_H

//this class will be expanded to include types for now basic functionality

class VBOData
{
public:
	VBOData();
	VBOData(const VBOData&);
	VBOData& operator = (const VBOData&);
	~VBOData();

	VBOData(bool enabled,
			unsigned int count,
			unsigned int attributeIndex,
			unsigned int datasize,
			unsigned int dataWitdh,
			void* pData);

	void Clean();

public:
	bool enabled;
	unsigned int glIndex;			//index used for opengl
	unsigned int attributeIndex;	//index o
	unsigned int count;
	unsigned int dataSize;
	unsigned int dataWidth;
	void* pData;
};

#endif // !VBO_DATA_H
