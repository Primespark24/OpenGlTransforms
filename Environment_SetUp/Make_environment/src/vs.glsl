#version 450 core  

out vec4 vs_color;

uniform mat4 transform;
                                                                  
void main(void)                                                   
{
    //Create four triangles, all oriented around orgin, and 'pointing' towards camera                                            
    const vec4 vertices[] = vec4[](vec4( 0.2, 0.2, 0.0, 1.0),  
                                   vec4( 0.2, -0.2, 0.0, 1.0),  
                                   vec4( 0.0,  0.0, 0.2, 1.0),
                                   vec4( -0.2, 0.2, 0.0, 1.0),  
                                   vec4( 0.2,  0.2, 0.0, 1.0), 
                                   vec4( 0.0,  0.0, 0.2, 1.0),
                                   vec4( -0.2,  0.2, 0.0, 1.0), 
                                   vec4( -0.2, -0.2, 0.0, 1.0),  
                                   vec4( 0.0,  0.0, 0.2, 1.0),
                                   vec4( 0.2, -0.2, 0.0, 1.0),  
                                   vec4( -0.2, -0.2, 0.0, 1.0),  
                                   vec4( 0.0,  0.0, 0.2, 1.0),
                                   vec4( 0.2,  0.2,  0.0, 1.0), 
                                   vec4( 0.2, -0.2,  0.0, 1.0),
                                   vec4( 0.0,  0.0, -0.2, 1.0),
                                   vec4( -0.2, -0.2, 0.0, 1.0), 
                                   vec4( -0.2, 0.2,  0.0, 1.0),
                                   vec4( 0.0,  0.0, -0.2, 1.0),
                                   vec4( 0.2,  -0.2,  0.0, 1.0), 
                                   vec4( -0.2, -0.2,  0.0, 1.0),
                                   vec4( 0.0,   0.0, -0.2, 1.0),
                                   vec4( -0.2, 0.2,  0.0, 1.0), 
                                   vec4( 0.2,  0.2,  0.0, 1.0),
                                   vec4( 0.0,  0.0, -0.2, 1.0)
                                   ); 
    
    //First triangle is blue
    //Second is Green
    //Third red
    //Fourth should be Purple
    //Five is Cyan
    //Six is Yellow
    //Seven is black
    //Eight is White
    //White is added to give the basic illusion of depth
    const vec4 colors[] = vec4[](  vec4( 0.0,  0.0, 1.0, 1.0),  
                                   vec4( 0.0,  0.0, 1.0, 1.0),
                                   vec4( 1.0,  1.0, 1.0, 1.0), //White
                                   
                                   vec4( 0.0,  1.0, 0.0, 1.0), 
                                   vec4( 0.0,  1.0, 0.0, 1.0),
                                   vec4( 1.0,  1.0, 1.0, 1.0), //White
                                   
                                   vec4( 1.0,  0.0, 0.0, 1.0),
                                   vec4( 1.0,  0.0, 0.0, 1.0),
                                   vec4( 1.0,  1.0, 1.0, 1.0), //White

                                   vec4( 1.0,  0.0, 1.0, 1.0),  
                                   vec4( 1.0,  0.0, 1.0, 1.0),
                                   vec4( 1.0,  1.0, 1.0, 1.0), //White

                                   vec4( 1.0,  1.0, 0.0, 1.0),  
                                   vec4( 1.0,  1.0, 0.0, 1.0),
                                   vec4( 1.0,  1.0, 1.0, 1.0), //White
                                   
                                   vec4( 0.0,  1.0, 1.0, 1.0), 
                                   vec4( 0.0,  1.0, 1.0, 1.0),
                                   vec4( 1.0,  1.0, 1.0, 1.0), //White
                                   
                                   vec4( 1.0,  1.0, 1.0, 1.0),
                                   vec4( 1.0,  1.0, 1.0, 1.0),
                                   vec4( 1.0,  1.0, 1.0, 1.0), //White 

                                   vec4( 0.0,  0.0, 0.0, 1.0),  
                                   vec4( 0.0,  0.0, 0.0, 1.0),
                                   vec4( 1.0,  1.0, 1.0, 1.0)  //White
                                   );

    float d = 4.0; //Projection plane defintion
        // Perspective project matrix
        mat4 persp = mat4(
            1.0, 0.0, 0.0, 0.0,   //x col
            0.0, 1.0, 0.0, 0.0,   //y col
            0.0, 0.0, 1.0, 1.0/d, //z col This is kind of like shearing in the z/w axis
            0.0, 0.0, 0.0, 1.0);  //w col

        float angle_x = 1.31; // ~75 degres
        //Rotational matrix (kind of a simple camera transform)
        mat4 rot_x = mat4(
            1.0, 0.0, 0.0, 0.0,                     //x col
            0.0, cos(angle_x), sin(angle_x), 0.0,   //y col
            0.0, -sin(angle_x), cos(angle_x), 0.0,  //z col
            0.0, 0.0, 0.0, 1.0);                    //w col
    

        // Used to add an additional movement to our object
        // Used to observe effects of projection
        mat4 translate = mat4(
            1.0, 0.0, 0.0, 0.0,      //x col
            0.0, 1.0, 0.0, 0.0,      //y col
            0.0, 0.0, 1.0, 0.0,      //z col
            0.0, 0.0, 0.0, 1.0);     //w col
        //       ^^^ Modify this as we go forward!

        //Resulting point, dependent on if we apply external transform or not
        vec4 base;

        //Define base depending on which vertex we are currently in
        if(gl_VertexID < 24){                            
            //Original Triangles
            //We can think of this as object space
            //origin at world origin, colinear axes
            base = vertices[gl_VertexID%24];
        } else {
            //Transform Triangles
            //We can think of this as our translation into (or through) world coordinates
            //We are functionally 'placing' our object into the world
            //     internal    external
            base = translate * transform * vertices[gl_VertexID%24];
        }

        //gl_Position = base;
        gl_Position = persp * rot_x  * base;

        vs_color = colors[gl_VertexID%24];                          
}                                                                 
