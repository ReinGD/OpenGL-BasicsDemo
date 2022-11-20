#ifndef MODEL_PROPERTIES_H
#define MODEL_PROPERTIES_H

class ModelProperties
{
public:
	struct vertex
	{
		float x;
		float y;
		float z;

		vertex(float in_x, float in_y, float in_z)
		{
			x = in_x;
			y = in_y;
			z = in_z;
		};
	};

	struct index
	{
		unsigned int a;
		unsigned int b;
		unsigned int c;

		index(unsigned int in_a, unsigned int in_b, unsigned int in_c)
		{
			a = in_a;
			b = in_b;
			c = in_c;
		};
	};

};

#endif // !MODEL_PROPERTIES_H
