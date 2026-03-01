# Welcome to the materials chapter in the LearnOpenGL tutorial!
### This is an OpenGL project built with GLFW, GLAD, and GLM


#### This lesson is designed to teach how different materials react differently to light, and how light can have different properties as well. This lesson displays how this is represented and used in an OpenGL program.
#### We can use a struct in the object shader to represent the material's distinct ambient, diffuse, specular and shininess values. By replacing *materialColor* with each calculation's corresponding phong light value, we can change the way the object reflects absorbs color and reflects light.
#### This isn't enough, though. Beforehand we were scaling the phong values with constants and leaving the light source alone, but now that won't work. To fix this, we create a struct for the light's phong values in the shader and replace all the *lightColor* values with each calculation's corresponding phong value. By doing this we can not only control the object's material, but also the phong values of the light. Ambient light stays the same as a scaled down white vector to copy the object's color. Diffuse is where the light's color comes into play, and specular stays at solid white.


#### I have also added an additional header file in the resources folder of assets that contains 2 different materials. While it isn't perfect, pressing *m* will rapidly switch between 2 colors. Pray you can land on the one you want!


## Requirements:
#### CMake - 4.0.0
#### A C++17 Compiler


## Build Instructions:
#### This project is designed to be run from the root directory.
#### Build CMake with cmake -B build
#### Build the program with 'cmake --build build'
#### Run the executable with './build/Debug/Materials.exe'
##### *Note that the executable's location may be different for you, mine happens to be in the './build/Debug' directory.*
