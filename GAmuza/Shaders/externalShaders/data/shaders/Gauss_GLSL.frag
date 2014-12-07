//Gauss blur
uniform sampler2DRect image;

varying vec2 texcoordM;
varying vec2 texcoordB0;
varying vec2 texcoordF0;
varying vec2 texcoordB1;
varying vec2 texcoordF1;
varying vec2 texcoordB2;
varying vec2 texcoordF2;

void main(){
    vec4 sampleM  = texture2DRect(image, texcoordM);
    vec4 sampleB0 = texture2DRect(image, texcoordB0);
    vec4 sampleF0 = texture2DRect(image, texcoordF0);
    vec4 sampleB1 = texture2DRect(image, texcoordB1);
    vec4 sampleF1 = texture2DRect(image, texcoordF1);
    vec4 sampleB2 = texture2DRect(image, texcoordB2);
    vec4 sampleF2 = texture2DRect(image, texcoordF2);

    gl_FragColor = 0.1752 * sampleM + 0.1658 * (sampleB0 + sampleF0) + 0.1403 * (sampleB1 + sampleF1) + 0.1063 * (sampleB2 + sampleF2);
}