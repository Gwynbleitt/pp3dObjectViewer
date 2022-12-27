#ifndef PROGRAM_H
#define PROGRAM_H
#define PI 3.14159265359f

#include "shader.h"
#include "camera.h"
#include <glm/gtc/type_ptr.hpp>

class Program{

      unsigned int        VBO, VAO, EBO;
      GLFWmonitor         *monitor;
      const GLFWvidmode   *vid_mode;
      shader              *shader_object;
      int                 n_vertices;
      double              cx, cy;
      double              sx, sy;

      glm::vec3 translation;
      glm::vec3 direction;
      glm::vec2 direction2d;
      glm::vec2 rotation; //yaw, pitch

      glm::vec3 light_src;

      glm::mat4 view_matrix;
      glm::mat4 projection_matrix;

      camera* cam1;
      
      void  drawmesh(glm::vec3 translate, glm::vec2 rotate);
            
      static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods),
                  framebuffer_size_callback(GLFWwindow* window, int width, int height);
      
      public:

      
      GLFWwindow *win;
      int fbwidth, fbheight;

      void  createmesh(int vertices_size, int indices_size, float* vertex_cordinates, unsigned int* indices),
            Event_Loop(float speed);

      Program();
      ~Program();
};

#endif