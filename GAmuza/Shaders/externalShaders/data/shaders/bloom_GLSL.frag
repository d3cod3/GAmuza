    //#version 120  
//#extension GL_EXT_gpu_shader4: enable
//#extension GL_ARB_texture_rectangle : enable
      
    // define our varying texture coordinates   
    varying vec2 texCoord;  
    uniform sampler2DRect tex0;
    uniform float bloom;  
      
      
    void main()  
    {  
        vec4 sum, dry;   
        int i, j;    
          
        for( i = -3 ;i <= 3; i++)    
        {    
            for (j = -3; j <= 3; j++)    
            {    
                sum += texture2DRect(tex0, gl_TexCoord[0].st  + vec2(j, i) * 2.0) * 0.25;  // 2.0 = "radius step"
            }    
        }    
          
        sum = sum * sum * 0.012; // 0.012 = arbitrary value   
        dry = texture2DRect(tex0, gl_TexCoord[0].st );
        gl_FragColor = bloom * (1.0 - ((1.0 - sum) * (1.0 - dry))) +  ((1.0 - bloom) * dry); // screen mode blending  
       
    }