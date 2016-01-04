
// Shader-ul de fragment / Fragment shader  
 
 #version 400

in vec4 ex_Color;
uniform int codCol;
 
out vec4 out_Color;

void main(void)
  {
	if ( codCol==0 )
		//out_Color = ex_Color;
		out_Color=vec4 (1.0, 0.5, 0.0, 0.0);
	if ( codCol==5 )
		out_Color=vec4 (0.3, 0.3, 0.7, 0.0);
	if ( codCol==4 )
		out_Color=vec4 (0.6, 0.6, 0.6, 0.0);

  }
 
