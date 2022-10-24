#ifndef PROGRAM_H
#define PROGRAM_H

#include "shader.h"

class Program{

      unsigned int        VBO, VAO, EBO;
      GLFWwindow          *win;
      GLFWmonitor         *monitor;
      const GLFWvidmode   *vid_mode;
      shader              *shader_object;
      
      void  drawmesh(),
            redraw();
            
      static void framebuffer_size_callback(GLFWwindow* window, int width, int height),
                  key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
      
      public:

      void  createmesh(int vertices_size, int indices_size, float vertex_cordinates[], unsigned int indices[]),
            Event_Loop();

      Program();
      ~Program();
};

#endif