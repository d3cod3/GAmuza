//setup for 2 texture
varying vec2 texcoord0;
varying vec2 texdim0;
uniform vec2 origin;
uniform vec2 scale;
uniform sampler2DRect tex0;
const float pi=3.1415926;


void main()
{
	vec2 point = abs(mod((texcoord0/texdim0)*scale+origin,1.));//normalize coordinates
    
	// cartesian to polar conversion
	vec2 dt = 2.*(point-0.5);
	float radius = sqrt(dot(dt,dt)); //hypot
	float theta = atan(dt.y,dt.x)+pi;
	vec2 topol = vec2(radius,theta/(2.*pi))*texdim0;
	vec4 a = texture2DRect(tex0,topol);
	// output texture
	gl_FragColor = a;
}