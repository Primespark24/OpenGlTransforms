/*
 * Based on work by Graham Sellers and OpenGL SuperBible7
 * 
 * Example of loading shaders from files
 * Reference to Kent Jones
 * 
 */

#include <sb7.h>
#include <shader.h>
#include <vmath.h>

// For error checking
#include <vector>
#include <cassert>
#define GL_CHECK_ERRORS assert(glGetError()== GL_NO_ERROR);

class test_app : public sb7::application{

    public:
    
    void startup(){
        // Placeholders for loaded shaders
        GLuint shaders[2];

        //Load respective shaders
        //These need to be co-located with main.cpp in src
        shaders[0] = sb7::shader::load(".\\src\\vs.glsl", GL_VERTEX_SHADER);
        compiler_error_check(shaders[0]);
        shaders[1] = sb7::shader::load(".\\src\\fs.glsl", GL_FRAGMENT_SHADER);
        compiler_error_check(shaders[1]);

        //Put together program from the two loaded shaders
        rendering_program = sb7::program::link_from_shaders(shaders, 2, true);

        GL_CHECK_ERRORS

        glCreateVertexArrays(1, &vertex_array_object);
        glBindVertexArray(vertex_array_object);

        matrixID = glGetUniformLocation(rendering_program,"transform");

        //Depth Test Enable (only render things 'forward' of other things)
        glEnable(GL_DEPTH_TEST);
        // Passes if the fragment's depth values is less than stored value
        glDepthFunc(GL_LEQUAL);
        

    }

    void shutdown(){
        glDeleteVertexArrays(1, &vertex_array_object);
        glDeleteProgram(rendering_program);
    }

    void render(double curTime){

        //Depth Mask Reset
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        static const GLfloat green[] = { 0.0f, 0.25f, 0.0f, 1.0f };
        glClearBufferfv(GL_COLOR, 0, green);

        glUseProgram(rendering_program);

        if(glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS){
        //Transform 1 - Translation (w) all have a perception double of 4
        
        vmath::mat4 translation { vmath::vec4(1.0f, 0.0f, 0.0f, 0.0f), //X Col
                                vmath::vec4(0.0f, 1.0f, 0.0f, 0.0f), //Y Col
                                vmath::vec4(0.0f, 0.0f, 1.0f, 0.0f), //Z Col
                                vmath::vec4(1.0f, 1.0f, 1.0f, 1.0f) }; //W Col
        
        glUniformMatrix4fv(matrixID, 1, GL_FALSE, &translation[0][0]);             
        
        }else if(glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS){
        //Transform 2 - Scale 2x
        
        vmath::mat4 scale { vmath::vec4(2.0f, 0.0f, 0.0f, 0.0f), //X Col
                                vmath::vec4(0.0f, 2.0f, 0.0f, 0.0f), //Y Col
                                vmath::vec4(0.0f, 0.0f, 2.0f, 0.0f), //Z Col
                                vmath::vec4(1.0f, 1.0f, 1.0f, 1.0f) }; //W Col
        
        glUniformMatrix4fv(matrixID, 1, GL_FALSE, &scale[0][0]);             
                
        }else if(glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS){
        // Transform 3 - rotation z axis 
                
        GLfloat angle = curTime;
                                //This is a z rotation
        vmath::mat4 rotation { vmath::vec4(cos(angle), sin(angle), 0.0f, 0.0f), //X Col
                                vmath::vec4(-sin(angle), cos(angle), 0.0f, 0.0f), //Y Col
                                vmath::vec4(0.0f, 0.0f, 1.0f, 0.0f), //Z Col
                                vmath::vec4(0.35f, 0.35f, 0.35f, 1.0f) }; //W Col
                            /*
                                //This is a x rotation
                                vmath::vec4(1.0f, 0.0f, 0.0f, 0.0f), //X Col
                                vmath::vec4(0.0f, cos(angle), sin(angle), 0.0f), //Y Col
                                vmath::vec4(0.0f, -sin(angle), cos(angle), 0.0f), //Z Col
                                vmath::vec4(0.35f, 0.35f, 0.35f, 1.0f) }; //W Col
                            
                                //this is a y rotation
                                vmath::vec4(cos(angle), 0.0f, -sin(angle), 0.0f), //X Col
                                vmath::vec4(0.0f, 1.0f, 0.0f, 0.0f), //Y Col
                                vmath::vec4(sin(angle), 0.0f, cos(angle), 0.0f), //Z Col
                                vmath::vec4(0.35f, 0.35f, 0.35f, 1.0f) }; //W Col
                            */

        glUniformMatrix4fv(matrixID, 1, GL_FALSE, &rotation[0][0]);
        
        }else if(glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS){
        //Transform 4 - reflection inverse x,y,z
        
        vmath::mat4 reflection { vmath::vec4(-1.0f, 0.0f, 0.0f, 0.0f), //X Col
                                vmath::vec4(0.0f, -1.0f, 0.0f, 0.0f), //Y Col
                                vmath::vec4(0.0f, 0.0f, -1.0f, 0.0f), //Z Col
                                vmath::vec4(1.0f, 1.0f, 1.0f, 1.0f) }; //W Col
        
        glUniformMatrix4fv(matrixID, 1, GL_FALSE, &reflection[0][0]);             
        
        }else if(glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS){
        //Transform 5 - shear on z col
        
        vmath::mat4 shear { vmath::vec4(1.0f, 0.0f, 0.0f, 0.0f), //X Col
                                vmath::vec4(0.0f, 1.0f, 0.0f, 0.0f), //Y Col
                                vmath::vec4(2.0f, 3.0f, 1.0f, 0.0f), //Z Col
                                vmath::vec4(1.0f, 1.0f, 1.0f, 1.0f) }; //W Col
        
        glUniformMatrix4fv(matrixID, 1, GL_FALSE, &shear[0][0]);             
        
        }else if(glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS){
        //Transform 6 - Inversion with a rotation
        
        GLfloat angle = curTime;
                                //This is a z rotation with an inversion
        vmath::mat4 inversion { vmath::vec4(-cos(angle), sin(angle), 0.0f, 0.0f), //X Col
                                vmath::vec4(-sin(angle), -cos(angle), 0.0f, 0.0f), //Y Col
                                vmath::vec4(0.0f, 0.0f, 1.0f, 0.0f), //Z Col
                                vmath::vec4(0.35f, 0.35f, 0.35f, 1.0f) }; //W Col
        
        glUniformMatrix4fv(matrixID, 1, GL_FALSE, &inversion[0][0]);             
        
        }else if(glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS){
        //Transform 7 - Inversion with a rotation and a scale
        
        GLfloat angle = curTime;
                                //This is a z rotation with an inversion and scale 3
        vmath::mat4 multi { vmath::vec4(3 * -cos(angle), sin(angle), 0.0f, 0.0f), //X Col
                                vmath::vec4(-sin(angle), 3 * -cos(angle), 0.0f, 0.0f), //Y Col
                                vmath::vec4(0.0f, 0.0f, 2.0f, 0.0f), //Z Col
                                vmath::vec4(0.35f, 0.35f, 0.35f, 1.0f) }; //W Col
        
        glUniformMatrix4fv(matrixID, 1, GL_FALSE, &multi[0][0]);             
        
        }else if(glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS){
         
        GLfloat angle = curTime;
                                //This is a z rotation 
        vmath::mat4 multi { vmath::vec4(-cos(angle), sin(angle), 0.0f, 0.0f), //X Col
                                vmath::vec4(-sin(angle), -cos(angle), 0.0f, 0.0f), //Y Col
                                vmath::vec4(0.0f, sin(angle), cos(angle), 0.0f), //Z Col
                                vmath::vec4(0.35f, 0.35f, 0.35f, 1.0f) }; //W Col
        
        glUniformMatrix4fv(matrixID, 1, GL_FALSE, &multi[0][0]);             
            
        }
        //Will always attempt to draw 16 triangles (3 points each)
        // Points 1-24 origin triangle
        // 25-48 modified by matrix
        glDrawArrays(GL_TRIANGLES, 0, 48);

        runtime_error_check();
    }

    void runtime_error_check()
    {
        GLenum err = glGetError();
        
        if (err) {
            char buf[50];
            sprintf(buf, "Error = %x", err);
            MessageBoxA(NULL, buf, "Error in shader", MB_OK);
        }
    }

    void compiler_error_check(GLuint shader)
    {
        GLint isCompiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> errorLog(maxLength);
            glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);

            if(maxLength == 0){
                char buf[50];
                sprintf(buf, "Possibly shaders not found!", maxLength);
                MessageBoxA(NULL, buf, "Error in shader compilation", MB_OK);
            } else {
                // Provide the infolog in whatever manor you deem best.
                MessageBoxA(NULL, &errorLog[0], "Error in shader compilation", MB_OK);
            }

            // Exit with failure.
            glDeleteShader(shader); // Don't leak the shader.
        }
    }

    private:
        GLuint rendering_program;
        GLuint vertex_array_object;

        GLuint matrixID;

};


DECLARE_MAIN(test_app);
