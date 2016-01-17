#version 420

// World Matrix
uniform mat4 world;
// View Matrix
uniform mat4 view;
// Projection Matrix
uniform mat4 projection;

layout (location = 1) in vec3 position; //inputs. Locations are just numbers that bridge gap between shader and c++ programs.
layout (location = 2) in vec3 colour;//we also need to pass in colour (rgb) values between 0.0 and 1.0

out vec3 v_colour;//we need to define an output value since there is no predefined one like for position.

void main() //shader program's entry point
{
	//gl_Position is a special GLSL variable for the vertex shader program.
	//It is compulsory to assign this variable in the vertex shader!!!
	//gl_Position is a vec4, so we need to fill in missing ones.
	//vec4(position, depth, point=1.0 or vector=0.0)
	gl_Position = projection * view * world * vec4(position, 1.0f);
	
	v_colour = colour;//send colour on its way since this is just a Pass-through Shader.
	//v_colour = vec3(1.0f, 1.0f, 1.0f);
}

/* Vertex Shader.
	
	Must:
		-Accept a single vertex as input
		-Provide a single vertex as output
	
	i.e. Per Vertex Shader.

*/
