#ifdef GL_ES
precision mediump float;
#endif

varying vec2 TexCoords;

uniform sampler2D screen;
uniform vec2 screenSize;
uniform int pass;
uniform float radius;

void main()
{
    vec2 uv = TexCoords;
    vec2 res = screenSize;

    float i = float(pass) + 0.5;

    vec3 col = texture2D(screen, uv + vec2(i, i) / res).rgb;
    col += texture2D(screen, uv + vec2(i, -i) / res).rgb;
    col += texture2D(screen, uv + vec2(-i, i) / res).rgb;
    col += texture2D(screen, uv + vec2(-i, -i) / res).rgb;
    col /= 4.0;

    gl_FragColor = vec4(col, 1.0);
}