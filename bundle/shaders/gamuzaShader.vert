#version 120
uniform float tex_w;
uniform float tex_h;

void main() {
	
	gl_Position = ftransform();
	gl_TexCoord[0] = gl_MultiTexCoord0;

}