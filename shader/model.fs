#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_normal1;
uniform sampler2D texture_specular1;

void main()
{
    //vec4 texColor = texture(texture_diffuse1, TexCoords);
    //if(texColor.a < 0.1)
    //    discard;
        
    FragColor = texture(texture_diffuse1, TexCoords);
    if(FragColor.a < 0.1)
        discard;
    //FragColor = vec4(fract(TexCoords), 0.0, 1.0);
   // FragColor = vec4(texture(texture_normal1, TexCoords).rgb, 1.0);
    //FragColor = vec4(texture(texture_specular1, TexCoords).rgb, 1.0);
    //FragColor = texture(texture_diffuse1, TexCoords);

 
}