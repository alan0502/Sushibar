#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
// #include <iostream>

#include <bits/stdc++.h>

#include "./header/Object.h"
#include "./header/stb_image.h"

// using namespace std

void framebufferSizeCallback(GLFWwindow *window, int width, int height);
void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
unsigned int createShader(const string &filename, const string &type);
unsigned int createProgram(unsigned int vertexShader, unsigned int fragmentShader);
unsigned int modelVAO(Object &model);
unsigned int loadTexture(const char *tFileName);
void init();
void calculateColor(float hueDegree, glm::vec3 &color);

// settings
int SCR_WIDTH = 800;
int SCR_HEIGHT = 600;

// Shader
unsigned int vertexShader, fragmentShader, shaderProgram;

// Texture
unsigned int plateTexture, plateTexture1, plateTexture2, plateTexture3, riceTexture, tunaTexture, omelleteTexture, salmonTexture, scallopTexture, trackTexture;

// VAO, VBO
unsigned int plateVAO, riceVAO, tunaVAO, omelleteVAO, salmonVAO, scallopVAO, trackVAO;

// Objects to display
Object *riceObject, *tunaObject, *plateObject, *omelleteObject, *salmonObject, *scallopObject, *trackObject;

// Variables
bool wTexture = 0, isLRotate = 0, isGRotate = 0, isAdvance = 0;
// Movement
bool moveUp = false, moveDown = false, moveLeft = false, moveRight = false;

float plateLRotation = 0.0f, plateGRotation; 
int sushiType = 1;

enum ModelType{
    PLATE, 
    RICE,
    TUNA, 
    OMELLETE, 
    SALMON,
    SCALLOP,
    OTHER
};

void drawModel(ModelType modelType, Object* object, unsigned int texture, unsigned int modelVAO, glm::mat4 model){

    glUniform1i(glGetUniformLocation(shaderProgram, "wTexture"), wTexture);

    unsigned int mLoc = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(mLoc, 1, GL_FALSE, glm::value_ptr(model));
    
    if(!wTexture){
        glUniform1i(glGetUniformLocation(shaderProgram, "type"), modelType);
        glBindVertexArray(modelVAO);
        glDrawArrays(GL_TRIANGLES, 0, object->positions.size());
        glBindVertexArray(0);
    }
    else{
        // TODO#2-2: draw the sushi with texture 
        // The above draws the sushi without its texture
        // For part2, please apply the loaded texture to your model 
        // Hint:
        //  glActiveTexture, glBindTexture
        //  wTexture will force the shader to render the model with texture
        glUniform1i(glGetUniformLocation(shaderProgram, "wTexture"), wTexture);

        glActiveTexture(GL_TEXTURE0);                      // 啟用 Texture unit 0
        glBindTexture(GL_TEXTURE_2D, texture);             // 綁定對應貼圖
        glUniform1i(glGetUniformLocation(shaderProgram, "tex"), 0); // shader 的 uniform sampler2D

        glBindVertexArray(modelVAO);
        glDrawArrays(GL_TRIANGLES, 0, object->positions.size());
        glBindVertexArray(0);
    }
}


// TODO#1-2: 
//  Applying transformation to make your sushi
//  In this part, you should firt obtain the model matrix (i.e the transformation matrix)
//  Then you can simply pass the model matrix the drawModel function.
// Hint: 
//  glm::translate, glm::scale, glm::rotate, drawModel()
//  Example of how to use the drawModel function: 
//  drawModel(PLATE, plateObject, plateTexture, plateVAO, glm::mat4 model matrix)
void drawSushi(unsigned int mLoc){
    // For plate
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(plateGRotation), glm::vec3(0, 1, 0));
    model = glm::translate(model, glm::vec3(1.0f, 1.0f, 1.0f));
    drawModel(PLATE, plateObject, plateTexture, plateVAO, model);

    // For rice
    glm::mat4 riceModel = glm::translate(model, glm::vec3(0.0f, 0.35f, 0.0f));
    riceModel = glm::rotate(riceModel, glm::radians(plateLRotation), glm::vec3(0, 1, 0));
    drawModel(RICE, riceObject, riceTexture, riceVAO, riceModel);

    // For topping
    glm::mat4 toppingModel;
    switch (sushiType) {
        case 1:
            toppingModel = glm::translate(riceModel, glm::vec3(0.0f, 0.6f, 0.0f));
            toppingModel = glm::scale(toppingModel, glm::vec3(2.0f, 2.5f, 2.0f));
            drawModel(SCALLOP, scallopObject, scallopTexture, scallopVAO, toppingModel);
            break;
        case 2:
            toppingModel = glm::translate(riceModel, glm::vec3(0.0f, 0.35f, 0.0f));
            toppingModel = glm::rotate(toppingModel, glm::radians(-60.0f), glm::vec3(0, 1, 0));
            toppingModel = glm::scale(toppingModel, glm::vec3(0.5f, 0.4f, 0.5f));
            drawModel(TUNA, tunaObject, tunaTexture, tunaVAO, toppingModel);
            break;
        case 3:
            //glm::mat4 toppingModel = riceModel;
            toppingModel = glm::translate(riceModel, glm::vec3(-0.2f, 0.25f, -0.4f));
            toppingModel = glm::scale(toppingModel, glm::vec3(1.0f/2.0f, 1.0f/1.25f, 1.0f/4.0f));
            toppingModel = glm::rotate(toppingModel, glm::radians(45.0f), glm::vec3(1, 0, 0));
            toppingModel = glm::translate(toppingModel, glm::vec3(0.8f, -0.6f, -0.7f));
            drawModel(SALMON, salmonObject, salmonTexture, salmonVAO, toppingModel);
            break;
    }

}

// TODO3: 
//  Implement the logic of sushi formula here
// Hint: Basic requirements is that you can move the object using the AWSD key
//       You can use the cube.obj as a simple track, or use your own design
// Note: Please remember to put the additional assets in the my_assets folder and hand it in
void sushiFormula(){
    glm::mat4 trackModel = glm::mat4(1.0f);
    trackModel = glm::translate(trackModel, glm::vec3(0, 0, 0));
    trackModel = glm::scale(trackModel, glm::vec3(10.0f, 0.1f, 10.0f)); // 拉成地板
    drawModel(OTHER, trackObject, trackTexture, trackVAO, trackModel);

    static glm::vec3 sushiPos = glm::vec3(0.0f, 0.0f, 0.0f); // 位置
    static float sushiAngle = 0.0f;   

    float moveSpeed = 0.1f;
    //float rotateSpeed = 3.0f;
    if (moveUp)    sushiPos += glm::vec3(0.0f, 0.0f, -1.0f) * moveSpeed;  // W
    if (moveDown)  sushiPos += glm::vec3(0.0f, 0.0f, 1.0f) * moveSpeed;   // S
    if (moveLeft)  sushiPos += glm::vec3(-1.0f, 0.0f, 0.0f) * moveSpeed;  // A
    if (moveRight) sushiPos += glm::vec3(1.0f, 0.0f, 0.0f) * moveSpeed;   // D

    // 計算壽司的模型矩陣
    glm::mat4 sushiModel = glm::mat4(1.0f);
    sushiModel = glm::translate(sushiModel, sushiPos);
    sushiModel = glm::rotate(sushiModel, glm::radians(sushiAngle), glm::vec3(0, 1, 0));

    glm::mat4 model = sushiModel;
    model = glm::rotate(model, glm::radians(plateGRotation), glm::vec3(0, 1, 0));
    model = glm::translate(model, glm::vec3(1.0f, 1.0f, 1.0f));
    drawModel(PLATE, plateObject, plateTexture, plateVAO, model);

    // For rice
    float t = glfwGetTime();
    float riceOffset = sin(t * 3.0f) * 0.03f; // 幅度與頻率可自己調
    glm::mat4 riceModel = glm::translate(model, glm::vec3(0.0f, 0.35f + riceOffset, 0.0f));
    riceModel = glm::rotate(riceModel, glm::radians(plateLRotation), glm::vec3(0, 1, 0));
    drawModel(RICE, riceObject, riceTexture, riceVAO, riceModel);

    // For topping
    glm::mat4 toppingModel;
    //float t = glfwGetTime();
    float offset = sin(t * 4.5f) * 0.02f;
    switch (sushiType) {
        case 1:
            toppingModel = glm::translate(riceModel, glm::vec3(0.0f, 0.6f, 0.0f));
            toppingModel = glm::scale(toppingModel, glm::vec3(2.0f, 2.5f, 2.0f));
            toppingModel = glm::translate(toppingModel, glm::vec3(0.0f, offset, 0.0f));
            drawModel(SCALLOP, scallopObject, scallopTexture, scallopVAO, toppingModel);
            break;
        case 2:
            toppingModel = glm::translate(riceModel, glm::vec3(0.0f, 0.35f, 0.0f));
            toppingModel = glm::rotate(toppingModel, glm::radians(-60.0f), glm::vec3(0, 1, 0));
            toppingModel = glm::scale(toppingModel, glm::vec3(0.5f, 0.4f, 0.5f));
            toppingModel = glm::translate(toppingModel, glm::vec3(0.0f, offset, 0.0f));
            drawModel(TUNA, tunaObject, tunaTexture, tunaVAO, toppingModel);
            break;
        case 3:
            //glm::mat4 toppingModel = riceModel;
            toppingModel = glm::translate(riceModel, glm::vec3(-0.2f, 0.25f, -0.4f));
            toppingModel = glm::scale(toppingModel, glm::vec3(1.0f/2.0f, 1.0f/1.25f, 1.0f/4.0f));
            toppingModel = glm::rotate(toppingModel, glm::radians(45.0f), glm::vec3(1, 0, 0));
            toppingModel = glm::translate(toppingModel, glm::vec3(0.8f, -0.6f, -0.7f));
            toppingModel = glm::translate(toppingModel, glm::vec3(0.0f, offset, 0.0f));
            drawModel(SALMON, salmonObject, salmonTexture, salmonVAO, toppingModel);
            break;
    }
}



int main() {
    // glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
   
    // TODO#0-1: setting the window title 
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "HW1-A132525", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetKeyCallback(window, keyCallback);
    glfwSwapInterval(1);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Initialize Object, Shader, Texture, VAO, VBO
    init();

    // Enable depth test, face culling
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);

    // Set viewport
    glfwGetFramebufferSize(window, &SCR_WIDTH, &SCR_HEIGHT);
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    // render loop variables
    double dt;
    double lastTime = glfwGetTime();
    double currentTime;

    // get uniform location
    unsigned int mLoc, vLoc, pLoc;
    mLoc = glGetUniformLocation(shaderProgram, "model");
    vLoc = glGetUniformLocation(shaderProgram, "view");
    pLoc = glGetUniformLocation(shaderProgram, "projection");

    // render loop
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0 / 255.0, 0 / 255.0, 0 / 255.0, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);

        
        // TODO#1-1: Setting the perspective and viewing matrix
        //           In this part we would obtain the projection and viewing matrix
        //           and pass it in to the shader.
        // Hint: 
        //      glm::lookAt, glm::perspecitive, glUniformMatrix4fv

        // glm::mat4 view = ?
        // glm::mat4 projection = ?
        glm::mat4 view = glm::lookAt(
            glm::vec3(1, 8.5, 13), // camera position
            glm::vec3(1, 1, 1),    // target
            glm::vec3(0, 1, 0)     // up vector
        );
        float aspect = (float)SCR_WIDTH / (float)SCR_HEIGHT;  // 你的視窗寬高比
        glm::mat4 projection = glm::perspective(
            glm::radians(45.0f),
            aspect,
            0.1f,
            1000.0f
        );
        
        glUniformMatrix4fv(vLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(pLoc, 1, GL_FALSE, glm::value_ptr(projection));

        if(!isAdvance){
            drawSushi(mLoc);
            plateLRotation = plateLRotation < 355 ? plateLRotation + 5 * isLRotate: 0;
            plateGRotation = plateGRotation < 355 ? plateGRotation + 5 * isGRotate: 0;
        }
        else{
            sushiFormula();
        }
        
        // Status update
        currentTime = glfwGetTime();
        dt = currentTime - lastTime;
        lastTime = currentTime;

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

// TODO#0-3: 
//  Add the needed key 

//  When ESC is pressed: Should close the window
//  When T is pressed: Should be able to swith between the texture, and untextured mode
//  When R is pressed: Should be able to start and stop rotating the plate locally
//  When G is pressed: Should be able to start and stop rotating the plate globally
//  When 1/2/3 is pressed: Should swith between toppings 1, 2, 3
//  When TAB is pressed: Should switch to advance mode 
//  (for the sushi formula, if you do not implement part3 you do not need to implement this)
//  ADWS: Control the movement of the sushi plate 
//  (for the sushi formula, if you do not implement part3 you do not need to implement this)
// Hint:
//  wTexture: control the texture mode (with/without)
//  isLRotate: control whether the plate is rotating locally
//  isGRotate: control whether the plate is rotating globally
//  sushiType: control the type of sushi topping
//  isAdvance: control whether to use the drawSushi() or the sushiFormula() 

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {

    // The action is one of GLFW_PRESS, GLFW_REPEAT or GLFW_RELEASE.
    // Events with GLFW_PRESS and GLFW_RELEASE actions are emitted for every key press.
    // Most keys will also emit events with GLFW_REPEAT actions while a key is held down.
    // https://www.glfw.org/docs/3.3/input_guide.html
    if (action == GLFW_PRESS){
        switch(key){
            case GLFW_KEY_ESCAPE:
                glfwSetWindowShouldClose(window, true);
                std::cout<<"ESCAPE"<<std::endl;
                break;
            case GLFW_KEY_T:
                wTexture = !wTexture;
                std::cout<<"Switch texture mode"<<std::endl;
                break;
            case GLFW_KEY_R:
                isLRotate = !isLRotate;
                std::cout<<"Switch rotate locally"<<std::endl;
                break;
            case GLFW_KEY_G:
                isGRotate = !isGRotate;
                std::cout<<"Switch rotate globally"<<std::endl;
                break;
            case GLFW_KEY_1:
                sushiType = 1;
                std::cout<<"Type 1: Scallop"<<std::endl;
                break;
            case GLFW_KEY_2:
                sushiType = 2;
                std::cout<<"Type 2: Tuna"<<std::endl;
                break;
            case GLFW_KEY_3:
                sushiType = 3;
                std::cout<<"Type 3: Salmon"<<std::endl;
                break;
            case GLFW_KEY_TAB:
                isAdvance = !isAdvance;
                std::cout<<"Switch advance"<<std::endl;
                break;
            case GLFW_KEY_W:
                moveUp = true;
                std::cout<<"W"<<std::endl;
                break;
            case GLFW_KEY_A:
                moveLeft = true;
                std::cout<<"A"<<std::endl;
                break;
            case GLFW_KEY_S:
                moveDown = true;
                std::cout<<"S"<<std::endl;
                break;
            case GLFW_KEY_D:
                moveRight = true;
                std::cout<<"D"<<std::endl;
                break;
            case GLFW_KEY_4:
                plateTexture = plateTexture1;
                std::cout << "Plate Texture: 1" << std::endl;
                break;
            case GLFW_KEY_5:
                plateTexture = plateTexture2;
                std::cout << "Plate Texture: 2" << std::endl;
                break;
            case GLFW_KEY_6:
                plateTexture = plateTexture3;
                std::cout << "Plate Texture: 3" << std::endl;
                break;
        }
    }
    if (action == GLFW_RELEASE) {
        switch (key) {
            case GLFW_KEY_W:
                moveUp = false;
                break;
            case GLFW_KEY_A:
                moveLeft = false;
                break;
            case GLFW_KEY_S:
                moveDown = false;
                break;
            case GLFW_KEY_D:
                moveRight = false;
                break;
        }
    }

        //glfwSetWindowShouldClose(window, true);

    
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebufferSizeCallback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
    SCR_WIDTH = width;
    SCR_HEIGHT = height;
}


// createShader
//  input:
//       filename: shader file name
//       type: shader type, "vert" means vertex shader, "frag" means fragment shader
//  output: shader object
unsigned int createShader(const string &filename, const string &type) {
    unsigned int shader;
    if (type == "vert")
        shader = glCreateShader(GL_VERTEX_SHADER);
    else if (type == "frag")
        shader = glCreateShader(GL_FRAGMENT_SHADER);
    else {
        cout << "Unknown Shader Type.\n";
        return 0;
    }

    ifstream fs(filename);
    stringstream ss;
    string s;
    while (getline(fs, s)) {
        ss << s << "\n";
    }
    string temp = ss.str();
    const char *source = temp.c_str();

    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        cout << "ERROR::SHADER::" << type << "::COMPLIATION_FAILED\n"
             << infoLog << endl;
        return 0;
    }

    return shader;
}

// createProgram
// input:
//      vertexShader: vertex shader object
//      fragmentShader: fragment shader object
// output: shader program
unsigned int createProgram(unsigned int vertexShader, unsigned int fragmentShader) {
    unsigned int program = glCreateProgram();

    // Attach our shaders to our program
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    // Link our program
    glLinkProgram(program);

    // Note the different functions here: glGetProgram* instead of glGetShader*.
    int success = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if (!success) {
        int maxLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        char *infoLog = (char *)malloc(sizeof(char) * (maxLength));
        glGetProgramInfoLog(program, maxLength, &maxLength, infoLog);

        // We don't need the program anymore.
        glDeleteProgram(program);
        // Don't leak shaders either.
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        puts(infoLog);
        free(infoLog);

        return -1;
    }

    // Always detach shaders after a successful link.
    glDetachShader(program, vertexShader);
    glDetachShader(program, fragmentShader);

    return program;
}

unsigned int modelVAO(Object &model) {
    unsigned int VAO, VBO[3];
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(3, VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT) * (model.positions.size()), &(model.positions[0]), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 3, 0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT) * (model.normals.size()), &(model.normals[0]), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 3, 0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT) * (model.texcoords.size()), &(model.texcoords[0]), GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 2, 0);
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    return VAO; 
}

// TODO#2-1
//  Load the texture image and return the texture handle
//  Simply return 0, since for part1 the shader will not use the texture
// Hint: 
//  glActiveTexture, glGenTexture, glBindTexture, glTexParameteri
//
unsigned int loadTexture(const string &filename) {
    unsigned int textureID;
    glGenTextures(1, &textureID); 
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
        GLenum format = (nrChannels == 3) ? GL_RGB : GL_RGBA;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture: " << filename << std::endl;
    }
    stbi_image_free(data);
    return textureID;



    return 0;
}

void init() {
#if defined(__linux__) || defined(__APPLE__)
    string dirShader = "../../src/shaders/";
    string dirAsset = "../../src/asset/obj/";
    string dirTexture = "../../src/asset/texture/";
#else
    string dirShader = "..\\..\\src\\shaders\\";
    string dirAsset = "..\\..\\src\\asset\\obj\\";
    string dirTexture = "..\\..\\src\\asset\\texture\\";
#endif

    // Shader
    vertexShader = createShader(dirShader + "easy.vert", "vert");
    fragmentShader = createShader(dirShader + "easy.frag", "frag");
    shaderProgram = createProgram(vertexShader, fragmentShader);
    glUseProgram(shaderProgram);



    // TODO#0-2: load the needed assets
    // Hint: 
    //  Object* obj = new Object(object_path)
    //  unsigned int VAO = modelVAO(Object* object)
    //  unsigned int texture = loadTexture(texture_path)
    //  You can refer to lines 28, 31, 34 to get and idea of what may be needed
    // Plate
    plateObject = new Object(dirAsset + "plate.obj");
    plateVAO = modelVAO(*plateObject);
    plateTexture1 = loadTexture(dirTexture + "plate.jpg");
    plateTexture2 = loadTexture(dirTexture + "plate_red.jpg");
    plateTexture3 = loadTexture(dirTexture + "plate_white.jpg");
    plateTexture = plateTexture1;

    // Rice
    riceObject = new Object(dirAsset + "rice.obj");
    riceVAO = modelVAO(*riceObject);
    riceTexture = loadTexture(dirTexture + "rice.jpg");

    // Topping: 
    scallopObject = new Object(dirAsset + "scallop.obj");
    scallopVAO = modelVAO(*scallopObject);
    scallopTexture = loadTexture(dirTexture + "scallop.jpg");

    tunaObject = new Object(dirAsset + "tuna.obj");
    tunaVAO = modelVAO(*tunaObject);
    tunaTexture = loadTexture(dirTexture + "tuna.jpg");

    salmonObject = new Object(dirAsset + "salmon.obj");
    salmonVAO = modelVAO(*salmonObject);
    salmonTexture = loadTexture(dirTexture + "salmon.jpg");

    trackObject = new Object(dirAsset + "cube.obj");
    trackVAO = modelVAO(*trackObject);
    trackTexture = loadTexture(dirTexture + "track.jpg"); // 可自選

        
    // Debug: 
    //  Just in case you run into problems and you have no idea what went wrong :)
    
    // glEnable(GL_DEBUG_OUTPUT);
    // glDebugMessageCallback([](  GLenum source, GLenum type, GLuint id, GLenum severity, 
    //                             GLsizei length, const GLchar* message, const void* userParam) {

    // std::cerr << "GL CALLBACK: " << (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "") 
    //           << "type = " << type 
    //           << ", severity = " << severity 
    //           << ", message = " << message << std::endl;
    // }, nullptr);
}