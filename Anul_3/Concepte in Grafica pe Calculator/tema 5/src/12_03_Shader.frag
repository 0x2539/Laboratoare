
// Shader-ul de fragment / Fragment shader  
 
 #version 400

in vec4 ex_Color;
in vec3 FragPos;  
in vec3 Normal; 

out vec4 out_Color;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos; 
uniform vec3 viewPos;



void main(void)
  {
  	// Ambient
    float ambientStrength = 0.2f;
    vec3 ambient = ambientStrength * lightColor;
  	
    // Diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // Specular
    float specularStrength = 0.5f;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;  
        
    vec3 result = (ambient + diffuse + specular) * objectColor;
	out_Color = vec4(result, 1.0f);
  }
 