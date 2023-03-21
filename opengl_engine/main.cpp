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
#include "Light.h"


const GLint WIDTH = 800, HEIGHT = 600;
const float to_radians = 3.14159265f / 180.0f;

std::vector<std::unique_ptr<Mesh>> mesh_list;
std::vector<std::unique_ptr<Shader>> shader_list;
Camera camera;

Texture brick_texture;
Texture dirt_texture;

Light main_light;

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

void create_objects() 
{
    unsigned int indices[] = {
        0, 3, 1,
        1, 3, 2,
        2, 3, 0,
        0, 1, 2
    };

    GLfloat vertices[] = {
    //  x       y       z         u     v
        -1.0f, -1.0f, 0.0f,     0.0f, 0.0f,
        0.0f, -1.0f, 1.0f,      0.5f, 0.0f,
        1.0f, -1.0f, 0.0f,      1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,       0.5f, 1.0f
    };
    
    auto mesh_ptr = std::make_unique<Mesh>();
    mesh_ptr->create_mesh(vertices, indices, 20, 12);

    mesh_list.emplace_back(std::move(mesh_ptr));


    auto mesh_ptr2 = std::make_unique<Mesh>();
    mesh_ptr2->create_mesh(vertices, indices, 20, 12);

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

    main_light = Light(1.0f,1.0f,1.0f,0.8f);

    //compile_shaders();

    unsigned int uniform_projection = 0, uniform_model = 0, uniform_view = 0, uniform_ambient_intensity = 0, uniform_ambient_colour = 0;

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
        uniform_ambient_colour = shader_list[0]->get_ambient_colour_location();
        uniform_ambient_intensity = shader_list[0]->get_ambient_intensity_location();

        main_light.use_light(uniform_ambient_intensity,uniform_ambient_colour);

        glm::mat4 model(1.0f);
        
        
        //model = glm::translate(model, glm::vec3(tri_offset, tri_offset, -2.5f));
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
        // model = glm::rotate(model, cur_angle * to_radians, glm::vec3(0.0f, 1.0f, 0.0f));
        
        model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
        glUniformMatrix4fv(uniform_model, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniform_projection, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(uniform_view, 1, GL_FALSE, glm::value_ptr(camera.calculate_view_matrix()));
        brick_texture.use_texture();
        mesh_list[0]->render_mesh();


        model = glm::mat4(1.0f);


        //model = glm::translate(model, glm::vec3(-tri_offset, 1.0f, -2.5f));
        model = glm::translate(model, glm::vec3(0.0f, 1.0f, -2.5f));
        // model = glm::rotate(model, cur_angle * to_radians, glm::vec3(0.0f, 1.0f, 0.0f));

        model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
        glUniformMatrix4fv(uniform_model, 1, GL_FALSE, glm::value_ptr(model));
        dirt_texture.use_texture();
        //glUniformMatrix4fv(uniform_projection, 1, GL_FALSE, glm::value_ptr(projection));
        mesh_list[1]->render_mesh();

        glUseProgram(0);

        main_window.swap_buffers();
    }

    return 0;
}