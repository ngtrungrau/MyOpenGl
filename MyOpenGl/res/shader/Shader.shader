#shader vertex
#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec4 aColor;
layout(location = 2) in vec2 aTexCoord;
out vec4 vColor;
out vec2 vTexCoord;
void main()
{
    gl_Position = position;
    vColor = aColor;
    vTexCoord = aTexCoord;
}

#shader fragment
#version 330 core
in vec4 vColor;
in vec2 vTexCoord;
layout(location = 0) out vec4 color;
void main(){
    color = vColor;
}

