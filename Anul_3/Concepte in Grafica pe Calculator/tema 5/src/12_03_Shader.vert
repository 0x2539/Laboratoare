// Shader-ul de varfuri  
 
 #version 400


layout(location=0) in vec3 in_Position;
layout(location=1) in vec3 in_Normal;
 

out vec4 gl_Position; 
out vec3 Normal;
out vec3 FragPos;
 
uniform mat4 myMatrix;
uniform mat4 view;
uniform mat4 projection;
 


void main(void)
  {
    gl_Position = projection*view*myMatrix*vec4(in_Position, 1.0);
    Normal=mat3(transpose(inverse(myMatrix))) *in_Normal; 
	FragPos = vec3(myMatrix * vec4(in_Position, 1.0f));
   } 
 
