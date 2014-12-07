//varying float lightintensity;
uniform vec3 lightpos;

const float ks = 0.1;
const float kd  = 1.0 - ks;

void main(void)
{
    
    //vec3 lightpos = (0.0,0.0,0.0); //Unused Used to be applicable, but leaving it in case someone finds it useful.
    vec3 pos = vec3 (gl_ModelViewMatrix * gl_Vertex);
    vec3 tnorm      = normalize(gl_NormalMatrix * gl_Normal);
    vec3 lightVec   = normalize(lightpos - pos);
    vec3 reflectVec = reflect(-lightVec, tnorm);
    vec3 viewVec    = normalize(-pos);
    
    float spec      = max(dot(reflectVec, viewVec), 0.0);
    spec            = pow(spec, 16.0);
    
     //lightintensity  = kd * max(dot(lightVec, tnorm), 0.0)+ ks * spec;
    
    gl_TexCoord[0]  = gl_TextureMatrix[0] * gl_MultiTexCoord0;
    gl_Position     = ftransform();
}
