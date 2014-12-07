uniform vec2 width;

varying vec2 texcoordM;
varying vec2 texcoordB0;
varying vec2 texcoordF0;
varying vec2 texcoordB1;
varying vec2 texcoordF1;
varying vec2 texcoordB2;
varying vec2 texcoordF2;


void main()
{
	// perform standard transform on vertex
	gl_Position = ftransform();
    
	// transform texcoord
	vec2 texcoord = vec2(gl_TextureMatrix[0] * gl_MultiTexCoord0);
	
	// get sample positions
    texcoordM = texcoord;
    texcoordB0 = texcoord - width;
    texcoordF0 = texcoord + width;
    texcoordB1 = texcoord - width * 2.0;
    texcoordF1 = texcoord + width * 2.0;
    texcoordB2 = texcoord - width * 3.0;
    texcoordF2 = texcoord + width * 3.0;
}