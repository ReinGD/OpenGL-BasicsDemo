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

	struct normals 
	{
		float x;
		float y;
		float z;

		normals() = default;

		normals(const float in_x, const float in_y, const float in_z)
		{
			x = in_x;
			y = in_y;
			z = in_z;
		};

		normals(const normals& norm)
		{
			this->x = norm.x;
			this->y = norm.y;
			this->z = norm.z;
		};
		normals& operator=(const normals& norm)
		{
			this->x = norm.x;
			this->y = norm.y;
			this->z = norm.z;
		};

	};

	struct vertex 
	{
		position pos;
		textureUV uv;
		normals norm;

		vertex() 
			:pos(),uv(),norm()
		{};

		vertex(const position in_pos, const textureUV in_uv, const normals in_normals)
			:pos(), uv(), norm()
		{
			pos = in_pos;
			uv = in_uv;
			norm = in_normals;
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
