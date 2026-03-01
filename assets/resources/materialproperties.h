#include <glad/glad.h>  
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

Material gold = {vec3(1.0f, 0.5f, 0.31f), vec3(1.0f, 0.5f, 0.31f), vec3(0.5f, 0.5f, 0.5f), 32.0f};
Material emerald = {vec3(0.0f, 0.5f, 0.31f), vec3(0.0f, 0.5f, 0.31f), vec3(0.0f, 0.5f, 0.5f), 32.0f};

Material materials[] = {gold, emerald};