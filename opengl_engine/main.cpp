#define STB_IMAGE_IMPLEMENTATION

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Mesh.h"
#include <vector>
#include "Shader.h"
#include "Window.h"
#include "Camera.h"

#include "Texture.h"
#include "DirectionalLight.h"
#include "Material.h"


const GLint WIDTH = 800, HEIGHT = 600;
const float to_radians = 3.14159265f / 180.0f;

std::vector<std::unique_ptr<Mesh>> mesh_list;
std::vector<std::unique_ptr<Shader>> shader_list;
Camera camera;

Texture brick_texture;
Texture dirt_texture;

Material shiny_material;
Material dull_material;

DirectionalLight main_light;

float delta_time = 0.0f;
float last_time = 0.0f;


bool direction_is_right = true;
float tri_offset = 0.0f;
float tri_max_offset = 0.7f;
float tri_increment = 0.0005f;

float cur_angle = 0.0f;

bool size_direction = true;
float cur_size = 0.4f;
float max_size = 0.8f;
float min_size = 0.1f;

// vertex shader

void create_shaders()
{
    auto shader1 = std::make_unique<Shader>();
    shader1->create_from_file("Shaders/", std::make_pair("shader.vert","shader.frag"));

    shader_list.emplace_back(std::move(shader1));
}

void calc_average_normal(unsigned int* _indices, unsigned int _indice_count, float* _vertices,
    unsigned int _vertices_count, unsigned int _vert_length, unsigned int _normal_offset)
{
    for (std::size_t i = 0; i < _indice_count; i+=3)
    {
        unsigned int in0 = _indices[i] * _vert_length; // one vertex has 8 length (x,y,z,u,v,nx,ny,nz) by getting index value (for example 3) we multiply it by vertex length and we get 24 which is 0.0f from vertices[]
        unsigned int in1 = _indices[i + 1] * _vert_length;
        unsigned int in2 = _indices[i + 2] * _vert_length;

        // compute the edges (vectors) from triangle points
        glm::vec3 v1(_vertices[in1] - _vertices[in0], _vertices[in1 + 1] - _vertices[in0 + 1], _vertices[in1 + 2] - _vertices[in0 + 2]);
        glm::vec3 v2(_vertices[in2] - _vertices[in0], _vertices[in2 + 1] - _vertices[in0 + 1], _vertices[in2 + 2] - _vertices[in0 + 2]);

        // dot product the edges -> perpendicular vector to edges
        glm::vec3 normal = glm::cross(v2, v1);
        normal = glm::normalize(normal);

        // get the positions of normals for vertex offsetting from the current point (x,y,z) end of the vertex
        in0 += _normal_offset;
        in1 += _normal_offset;
        in2 += _normal_offset;

        _vertices[in0] += normal.x;
        _vertices[in0+1] += normal.y;
        _vertices[in0+2] += normal.z;

        _vertices[in1] += normal.x;
        _vertices[in1+1] += normal.y;
        _vertices[in1+2] += normal.z;

        _vertices[in2] += normal.x;
        _vertices[in2+1] += normal.y;
        _vertices[in2+2] += normal.z;

    }

    // for every row in vertices
    for (size_t i = 0; i < _vertices_count / _vert_length; i++)
    {
        // get the absolute offset
        unsigned int n_offset = i * _vert_length + _normal_offset;
        glm::vec3 vec(_vertices[n_offset], _vertices[n_offset+1], _vertices[n_offset+2]);
        vec = glm::normalize(vec);
        _vertices[n_offset] = vec.x;
        _vertices[n_offset+1] = vec.y;
        _vertices[n_offset+2] = vec.z;
    }
}

void create_objects() 
{
    unsigned int indices[] = {
        0, 3, 1,
        1, 3, 2,
        2, 3, 0,
        0, 1, 2
    };

    GLfloat vertices[] = {
    //  x       y       z         u     v       nx    ny   nz
        -1.0f, -1.0f, -0.6f,     0.0f, 0.0f,     0.0f, 0.0f,0.0f,
        0.0f, -1.0f, 1.0f,      0.5f, 0.0f,     0.0f, 0.0f,0.0f,
        1.0f, -1.0f, -0.6f,      1.0f, 0.0f,     0.0f, 0.0f,0.0f,
        0.0f, 1.0f, 0.0f,       0.5f, 1.0f,     0.0f, 0.0f,0.0f
    };

    calc_average_normal(indices, 12, vertices, 32, 8, 5);
    
    auto mesh_ptr = std::make_unique<Mesh>();
    mesh_ptr->create_mesh(vertices, indices, 32, 12);

    mesh_list.emplace_back(std::move(mesh_ptr));


    auto mesh_ptr2 = std::make_unique<Mesh>();
    mesh_ptr2->create_mesh(vertices, indices, 32, 12);

    mesh_list.emplace_back(std::move(mesh_ptr2));

}

int main()
{
    auto main_window = Window(800, 600);
    std::cout << "after projection" << '\n';
    main_window.initialise();
    

    create_objects();
    create_shaders();

    camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 90.0f, 0.0f, 5.0f, 1.0f);

    brick_texture = Texture("Textures/brick.png");
    brick_texture.load_texture();

    dirt_texture = Texture("Textures/dirt.png");
    dirt_texture.load_texture();

    shiny_material = Material(1.0f, 32.0f);
    dull_material = Material(1.0f, 2.0f);

    main_light = DirectionalLight(1.0f,1.0f,1.0f,0.1f,0.3f,2.0f,-3.5f,7.0f);

    //compile_shaders();

    unsigned int uniform_projection = 0, uniform_model = 0, uniform_view = 0, uniform_eye_position = 0,
        uniform_specular_intensity, uniform_shininess = 0;

    // projection matrix

    glm::mat4 projection = glm::perspective(45.0f, main_window.get_buffer_width()/main_window.get_buffer_height(), 0.1f, 100.0f);
   
    // Loop until window closed
    while (!main_window.get_should_close())
    {
        float now = glfwGetTime();
        delta_time = now - last_time;
        last_time = now;

        // get + handle user input events

        glfwPollEvents();

        auto keys_array = main_window.get_keys();
        camera.key_control(std::span{keys_array},delta_time);
        camera.mouse_control(main_window.get_x_change(), main_window.get_y_change());

        if (direction_is_right)
        {
            tri_offset += tri_increment;
        }
        else {
            tri_offset -= tri_increment;
        }

        if (std::abs(tri_offset) >= tri_max_offset)
        {
            direction_is_right = !direction_is_right;
        }

        cur_angle += 0.01f;

        if (cur_angle >= 360)
        {
            cur_angle = 0.0f;
        }

        if (size_direction)
        {
            cur_size += 0.0001f;
        }
        else
        {
            cur_size -= 0.0001f;
        }

        if (cur_size >= max_size || cur_size <= min_size)
        {
            size_direction = !size_direction;
        }

        // clear window
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        //glUseProgram(shader);

        shader_list[0]->use_shader();
        uniform_model = shader_list[0]->get_model_location();
        uniform_projection = shader_list[0]->get_projection_location();
        uniform_view = shader_list[0]->get_view_location();
        uniform_eye_position = shader_list[0]->get_eye_position_location();
        uniform_specular_intensity = shader_list[0]->get_specular_intensity_location();
        uniform_shininess = shader_list[0]->get_shininess_location();


        main_light.rotate_light(now);
        shader_list[0]->set_directional_light(&main_light);


        //main_light.rotate_light(now);
        //main_light.use_light(uniform_ambient_intensity,uniform_ambient_colour,uniform_diffuse_intensity, uniform_direction);
        

        glUniformMatrix4fv(uniform_projection, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(uniform_view, 1, GL_FALSE, glm::value_ptr(camera.calculate_view_matrix()));
        glUniform3f(uniform_eye_position, camera.get_camera_position().x, camera.get_camera_position().y, camera.get_camera_position().z);

        glm::mat4 model(1.0f);
        
        //model = glm::translate(model, glm::vec3(tri_offset, tri_offset, -2.5f));
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
        // model = glm::rotate(model, cur_angle * to_radians, glm::vec3(0.0f, 1.0f, 0.0f));
        
        //model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
        glUniformMatrix4fv(uniform_model, 1, GL_FALSE, glm::value_ptr(model));

        brick_texture.use_texture();
        shiny_material.use_material(uniform_specular_intensity, uniform_shininess);
        mesh_list[0]->render_mesh();


        model = glm::mat4(1.0f);


        //model = glm::translate(model, glm::vec3(-tri_offset, 1.0f, -2.5f));
        model = glm::translate(model, glm::vec3(0.0f, 4.0f, -2.5f));
        // model = glm::rotate(model, cur_angle * to_radians, glm::vec3(0.0f, 1.0f, 0.0f));

        //model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
        glUniformMatrix4fv(uniform_model, 1, GL_FALSE, glm::value_ptr(model));
        dirt_texture.use_texture();
        dull_material.use_material(uniform_specular_intensity, uniform_shininess);
        //glUniformMatrix4fv(uniform_projection, 1, GL_FALSE, glm::value_ptr(projection));
        mesh_list[1]->render_mesh();

        glUseProgram(0);

        main_window.swap_buffers();
    }

    return 0;
}