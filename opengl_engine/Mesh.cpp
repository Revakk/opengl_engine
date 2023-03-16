#include "Mesh.h"

Mesh::Mesh()
{
	vao_ = 0;
	vbo_ = 0;
	ibo_ = 0;
	index_count_ = 0;
}

Mesh::~Mesh()
{
    clear_mesh();
}

void Mesh::create_mesh(float* _vertices, unsigned int* _indices, unsigned int _num_of_vertices, unsigned int _num_of_indices)
{
	index_count_ = _num_of_indices;
    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);

    glGenBuffers(1, &ibo_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices[0]) * _num_of_indices, _indices, GL_STATIC_DRAW);

    glGenBuffers(1, &vbo_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices[0])*_num_of_vertices, _vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(_vertices[0])*5, 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(_vertices[0]) * 5, (void*)(sizeof(_vertices[0])*3));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    // unbind after unbinding the VAO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::render_mesh()
{
    glBindVertexArray(vao_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements(GL_TRIANGLES, index_count_, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::clear_mesh()
{
    if (ibo_ != 0)
    {
        glDeleteBuffers(1, &ibo_);
        ibo_ = 0;
    }

    if (vbo_ != 0)
    {
        glDeleteBuffers(1, &vbo_);
        vbo_ = 0;
    }

    if (vao_ != 0)
    {
        glDeleteVertexArrays(1, &vao_);
        vao_ = 0;
    }

    index_count_ = 0;
}

