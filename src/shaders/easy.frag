#version 330 core
out vec4 FragColor;

in vec2 texCoord;

uniform int type;
uniform bool wTexture;
uniform sampler2D ourTexture;

void main()
{
    if(wTexture){
        FragColor = texture(ourTexture, texCoord);
    }
    else{
        if(type == 0)    
            FragColor = vec4(0.5, 0, 0, 1);
        else if(type == 1)
            FragColor = vec4(1, 1, 1, 1);
        else if(type == 2)   
            FragColor = vec4(0.8, 0.36, 0.33, 1);
        else if(type == 3)
            FragColor = vec4(1, 0.95, 0.6, 1);
        else if(type == 4)
            FragColor = vec4(1, 0.65, 0.07, 1);
        else if(type == 5)  
            FragColor = vec4(1, 0.945, 0.88, 1);
        else    
            FragColor = vec4(0, 1, 0, 1);
    }

} 