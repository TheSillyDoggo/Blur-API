#version 120

varying vec2 TexCoords;

const float weight = 1;
const float kernel = 5;

uniform sampler2D screen;
uniform vec2 screenSize;
uniform bool fast;
uniform bool first;
uniform float radius;

void main()
{
    vec2 uv = TexCoords.xy;// / screenSize.xy;
	vec3 sum = vec3(0);
    float pixelSize = 1.0 / screenSize.x; 
    
    vec3 accumulation = vec3(0);
    vec3 weightsum = vec3(0);

    if (first)
    {
        for (float i = -kernel; i <= kernel; i++){
            accumulation += texture2D(screen, uv + vec2(i * pixelSize, 0.0)).xyz * weight;
            weightsum += weight;
        }
    }
    else
    {
        for (float i = -kernel; i <= kernel; i++){
            accumulation += texture2D(screen, uv + vec2(0.0, i * pixelSize)).xyz * weight;
            weightsum += weight;
        }
    }
    
    sum = accumulation / weightsum;
    
    gl_FragColor = vec4(sum, 1.0);
}