#pragma once

#include <GL/glew.h>

class Mesh
{
public:
	Mesh();
	~Mesh();

	void create_mesh(float* _vertices, unsigned int* _indices, unsigned int _num_of_vertices, unsigned int _num_of_indices);
	void render_mesh();
	void clear_mesh();

private:
	unsigned int vao_, vbo_, ibo_;
	int index_count_;

};

