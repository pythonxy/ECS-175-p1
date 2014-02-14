
// positions and colors are 4 component vectors (opengl will fill in the 4th component)
attribute vec4 position;
attribute vec4 color;

void main()
{
  //output the position for the fragment shader
   position.x -= 1.0;
   position.y -= 1.0;
  gl_Position = position;

  //output the color for the fragment shader
  gl_FrontColor = color;
}
