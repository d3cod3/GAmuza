#extension GL_ARB_texture_rectangle : enable
uniform sampler2DRect tex0;

void main( void )
{

    vec2 st = gl_TexCoord[0].st;
    vec4 colorBase = texture2DRect(tex0, st);

    gl_FragColor = colorBase;
}

