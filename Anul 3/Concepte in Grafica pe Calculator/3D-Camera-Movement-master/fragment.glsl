#version 420

//We ignore the position output from Vertex Shader (for now) since we don't need it.

in vec3 v_colour; //The colour output from the Vertex Shader. NB: Name is same as output from Vertex Shader.

//Final colour is a vector with 4 components. The last one is the transparency of the colour (alpha) where 1.0 is opaque (solid) and 0.0 is totally transparent.
//Since we don't want all of our colours to be completely opaque, we don't specify an alpha value as part of our input.
out vec4 f_colour;//final colour of any given fragment.

void main() //shader program's entry point
{
	f_colour = vec4(v_colour, 1.0f); //with alpha value added. For now it is left to completely opaque.
}

/* Fragment Shader.

	MUST: - Provide a single output (A final colour for a fragment

	CAN: - Receive multiple inputs. Everything that is output from previous shader is an input for the Fragment Shader Program

	NB: No LAYOUT section since the Fragment Shader has no interface to our program - it only has interface with shader programs before it.
*/