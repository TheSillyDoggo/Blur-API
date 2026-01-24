attribute vec4 aPosition;
attribute vec2 aTexCoords;

varying vec2 TexCoords;

void main()
{
    TexCoords = aTexCoords;
    gl_Position = aPosition;
}