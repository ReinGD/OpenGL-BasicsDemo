#ifndef MESH_PROPERTIES_H
#define MESH_PROPERTIES_H

//will be moving this elsewhere

class MeshProperties
{
public:
	struct position
	{
		float x;
		float y;
		float z;

		position() = default;

		position(const float in_x, const float in_y, const float in_z)
		{
			x = in_x;
			y = in_y;
			z = in_z;
		};

		position(const position& pos)
		{
			this->x = pos.x;
			this->y = pos.y;
			this->z = pos.z;
		};

		position& operator= (const position& pos)
		{
			this->x = pos.x;
			this->y = pos.y;
			this->z = pos.z;
		};
	};

	struct textureUV 
	{
		float u;
		float v;

		textureUV() = default;

		textureUV(const float in_u, const float in_v)
		{
			u = in_u;
			v = in_v;
		};

		textureUV(const textureUV& in_texture)
		{
			this->u = in_texture.u;
			this->v = in_texture.v;
		};
		textureUV& operator=(const textureUV& in_texture)
		{
			this->u = in_texture.u;
			this->v = in_texture.v;
		};

	};

	struct normal 
	{
		float x;
		float y;
		float z;

		normal() = default;

		normal(const float in_x, const float in_y, const float in_z)
		{
			x = in_x;
			y = in_y;
			z = in_z;
		};

		normal(const normal& norm)
		{
			this->x = norm.x;
			this->y = norm.y;
			this->z = norm.z;
		};
		normal& operator=(const normal& norm)
		{
			this->x = norm.x;
			this->y = norm.y;
			this->z = norm.z;
		};

	};

	struct color
	{
		float r;
		float g;
		float b;
		float a;

		color() = default;

		color(const float in_r, const float in_g, const float in_b, const float in_a)
		{
			r = in_r;
			g = in_g;
			b = in_b;
			a = in_a;
		};

		color(const color& color)
		{
			this->r = color.r;
			this->g = color.g;
			this->b = color.b;
			this->a = color.a;
		};

		color& operator= (const color& color)
		{
			this->r = color.r;
			this->g = color.g;
			this->b = color.b;
			this->a = color.a;
		};
	};
	struct vertex 
	{
		position	pos;
		textureUV	uv;
		normal		norm;
		color		col;

		vertex() 
			:pos(),uv(),norm(), col()
		{};

		vertex(float x, float y, float z, float u, float v, float nx, float ny, float nz, float r, float g, float b, float a) 
			:pos(x,y,z),uv(u,v),norm(nx,ny,nz), col(r,g,b,a)
		{
			
		};
		vertex(const position in_pos, const textureUV in_uv, const normal in_normals, const color in_color)
			:pos(), uv(), norm(), col()
		{
			pos = in_pos;
			uv = in_uv;
			norm = in_normals;
			col = in_color;
		};
	};

	struct index
	{
		unsigned int a;
		unsigned int b;
		unsigned int c;

		index(const unsigned int in_a, const unsigned int in_b, const unsigned int in_c)
		{
			a = in_a;
			b = in_b;
			c = in_c;
		};
	};


};

#endif // !MESH_PROPERTIES_H
