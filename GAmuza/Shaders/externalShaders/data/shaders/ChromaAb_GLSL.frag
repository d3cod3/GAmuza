uniform sampler2DRect tex;
uniform vec2 windowSize;
uniform float offsetALL;

varying vec2 texcoord0;


void main()
{
	//vec2 offset			= ( gl_FragCoord.xy/windowSize - vec2( 0.5 ) ) * 0.005;
    vec2 offset			= ( gl_FragCoord.xy/windowSize - vec2( 0.5 ) ) * offsetALL;

	float rChannel		= texture2DRect( tex, texcoord0 ).r;
	float gChannel		= texture2DRect( tex, texcoord0 + offset ).g;
	float bChannel		= texture2DRect( tex, texcoord0 + offset * 2.0 ).b;
	vec3 finalCol		= vec3( rChannel, gChannel, bChannel );
	
	gl_FragColor.rgb	= finalCol;
	gl_FragColor.a		= 1.0;
}