# Welcome to the lighting chapter in the LearnOpenGL tutorial!
### This is an OpenGL built with GLFW, GLAD, and GLM


#### This lesson is designed to teach the math behind how light is simulated to imitate the real world.
#### There are three parts to Phong lighting.
#### Ambient light is just the color of the light multiplied by a small scaling factor (like 0.2) in the fragment shader
#### Diffuse lighting is more complicated, it's calculated with the dot product between the ray of light's vector and a vector normal to the fragment's surface. To calculate this, we need 3 things. The position vector of the light source, the position vector of each fragment calculated in the vertex shader by multiplying the model matrix by the object's input position data, and vectors normal to each vertex for each face. The vector pointing from the light to the fragment is calculated by subtracting the vectors. Then the dot product is taken with the direction vector and the normal vector. The dot product is multiplied against the light's color to get the diffuse light on that fragment.
#### Specular lighting is similar to diffuse lighting. We just need to calculate a vector pointing from the fragment to the camera, and reflect the light direction vector across the normal vector. By calculating the dot product between the reflection and the vector pointing to the camera, we recieve the strength of the specular light to the camera. All we need to do then is alter the shininess of the specular light by adding an exponent to the dot product's result and scale the light's strength with multiplication, then multiply by the light's color.
#### Once we have all the Phong lights calculated, we simply need to add them together and multiply by the object's color, which becomes the color of the fragment.


## Requirements:
#### CMake - 4.0.0
#### A C++17 Compiler


## Build Instructions:
### This project is designed to be run from the root directory.
### Build CMake with cmake -B build
### Build the program with 'cmake --build build'
### Run the executable with './build/Debug/Lighting.exe'
#### Note that the executable's location may be different for you, mine happens to be in 
#### the './build/Debug' directory.
