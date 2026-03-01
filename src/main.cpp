#include <glad/glad.h>  
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <shaders/shader_s.h>
#include <camera/camera.h>
#include <resources/materialproperties.h>

#include <string>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

float deltaTime = 0.0f;
float lastTime = 0.0f;

float movementSpeed = 3.0f;

float yaw = -90.0f;
float pitch = 0.0f;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = 400, lastY = 300;
bool firstMouse = true;

int materialIterator = 0;

int main() {

	// Initialize functions
	void framebufferSizeCallback(GLFWwindow * window, int width, int height);
    void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	void processInput(GLFWwindow* window);
    void mouseCallback(GLFWwindow* window, double xpos, double ypos);

	// Initialize glfw
	if (!glfwInit()) {
		cout << "Failure initializing glfw\n";
	}
	else {
		cout << "Initialized successfully!\n";
	}

	// Set hints for version and profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	float SCR_WIDTH = 800;
	float SCR_HEIGHT = 600;

	// Create window and set it as current
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

    

    // Hide the cursor and lock it in the center of the window
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    // Set the mouse callback
    glfwSetCursorPosCallback(window, mouseCallback);
    // Set scroll callback
    glfwSetScrollCallback(window, scroll_callback);

	// Start Glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;
		return -1;
	}

	// Give our window it's coordinates, width, and height

	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

	// Create our shaders
	Shader lightingShader = Shader("assets/shaders/colors.vs", "assets/shaders/colors.fs");
    Shader lightCubeShader = Shader("assets/shaders/light_cube.vs", "assets/shaders/light_cube.fs");

    

    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };



    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    

    // Vertex attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Light Cube VAO
    unsigned int lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    // We can use the same VBO as we are using the same vertexes
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Vertex attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window)) {
        // input
        // -----
        processInput(window);

        float currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Clear the depth buffer every frame
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Light Cube's position
        float time = glfwGetTime();
        glm::vec3 lightPos(cos(time) * 1.3, -1.0f, sin(time) * 1.3);
  
        // activate shader
        lightingShader.use();
        lightingShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
    
        glm::mat4 projection = glm::mat4(1.0f);
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = camera.GetViewMatrix();
        
        projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));

        lightingShader.setMat4("model", model);
        lightingShader.setMat4("view", view);
        lightingShader.setMat4("projection", projection);
        lightingShader.setVec3("lightPos", lightPos);
        lightingShader.setVec3("viewPos", camera.Position); 

        int materialID = materialIterator % (sizeof(materials) / sizeof(Material));
        lightingShader.setVec3("material.ambient", materials[materialID].ambient);
        lightingShader.setVec3("material.diffuse", materials[materialID].diffuse);
        lightingShader.setVec3("material.specular", materials[materialID].specular);
        lightingShader.setFloat("material.shininess", materials[materialID].shininess);

        lightingShader.setVec3("light.ambient",  0.2f, 0.2f, 0.2f);
        lightingShader.setVec3("light.diffuse",  0.5f, 0.5f, 0.5f); // darken diffuse light a bit
        lightingShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f); 

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        lightCubeShader.use();
        lightCubeShader.setMat4("projection", projection);
        lightCubeShader.setMat4("view", view);
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f));
        lightCubeShader.setMat4("model", model);

        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        camera.UpdateJump(deltaTime);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
	}
}


/* frameBufferSizeCallback(GLFWwindow* window, int width, int height)
*  Updates the gl window dimensions. glfw calls this function whenever it recognizes it's window has changed size.
*  GLFWwindow* window: Pointer to the window we are updating.
*  int width: The new width of the window.
*  int height: The new height of the window.
*/
void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
        materialIterator++;

    if ((glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && camera.Jumping == 0))
        camera.Jumping = 1;
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos) {

    
    if (firstMouse) // initially set to true
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = ypos - lastY;

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset
    );
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}