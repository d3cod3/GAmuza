// texcoords
varying vec2 texcoord0;
varying vec2 texcoord1;

// samplers
uniform sampler2DRect tex0;
uniform sampler2DRect tex1;

// blend amount
uniform float luma;
uniform float tol;
uniform float fade;
uniform float invert;
uniform float mode;
uniform float binary;
uniform vec4 lumcoeff;

// entry point
void main()
{
	vec4 one = vec4(1.0);
    
	vec4 a = texture2DRect(tex0, texcoord0);
	vec4 b = texture2DRect(tex1, texcoord1);
    
	// calculate our luminance
	float luminance = dot(a,lumcoeff);
    
	// measure distance from target
	float delta = abs(luminance-luma);
    
	// determine scaling coefficient witin our fade range
	float scale = smoothstep(abs(tol),abs(tol)+abs(fade),delta);
    
	// invert if necessary
	float mixamount = mix(scale,1.-scale,invert);
    
	// blend between sources based on mixamount
	vec4 result = mix(b,a,vec4(mixamount));
    
	// if not binary just set alpha value
	a.a = mixamount;
	result = mix(a,result,vec4(binary));
	
	// result either blend or mask based on mode
	gl_FragColor = mix(result,vec4(mixamount),vec4(mode));
	
	// setting the fragment color is a useful means of debugging
	//gl_FragColor = vec4(luminance);
}
