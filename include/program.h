#ifndef PROGRAM_H
#define PROGRAM_H

#include "shader.h"
#include "glm_transform.hpp"
#include <glm/gtc/type_ptr.hpp>

class Program{

      unsigned int        VBO, VAO, EBO;
      GLFWwindow          *win;
      GLFWmonitor         *monitor;
      const GLFWvidmode   *vid_mode;
      shader              *shader_object;

      float x,y,z;
      int angle;

      glm::vec3 rotate_axis;

      glm::mat4 transform;
      
      void  drawmesh(float deltax, float deltay, float deltaz, int delta_angle),
            redraw();
            
      static void framebuffer_size_callback(GLFWwindow* window, int width, int height),
                  key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
      
      public:

      void  createmesh(int vertices_size, int indices_size, float vertex_cordinates[], unsigned int indices[]),
            Event_Loop(float speed);

      Program();
      ~Program();
};

#endif