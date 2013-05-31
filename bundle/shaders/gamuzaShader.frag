#version 120
#extension GL_ARB_texture_rectangle : enable
#extension GL_EXT_gpu_shader4 : enable

// define our rectangular texture sampler
uniform sampler2DRect tex0;
uniform float tex_w;
uniform float tex_h;

// Projection Border Blending
const float BlendPower = 3.0;
const float projectors = 1;

// color correction
uniform float brightness;
uniform float saturation;
uniform float contrast;
uniform float gamma;

// analog film effect
uniform float filmBleach;
uniform float technicolor;
uniform float whiteDiffusion;
uniform float exposure;
uniform float diffusion;

//constant variables.
const vec4 one = vec4(1.0);	
const vec4 two = vec4(2.0);
const vec4 grayXfer = vec4(0.299,0.587,0.114, 0.0);
const vec3 LumCoeff = vec3(0.2125, 0.7154, 0.0721);
const float sqrtoftwo = 1.41421356237;
const float pi = 3.14159265;
const float sigma = 2.0;
const float numBlurPixelsPerSide = 3.5;
const vec2  blurMultiplyVec = vec2(1.0, 1.0);

const vec4 redfilter 		= vec4(1.0, 0.0, 0.0, 0.0);
const vec4 bluegreenfilter 	= vec4(0.0, 1.0, 1.0, 0.0);
const vec4 cyanfilter		= vec4(0.0, 1.0, 0.5, 0.0);
const vec4 magentafilter	= vec4(1.0, 0.0, 0.25, 0.0);

const float AvgLumR = 0.5;
const float AvgLumG = 0.5;
const float AvgLumB = 0.5;

vec4 drawSmoothEdge(float loc, float extend, float blePow, float lumCon, vec3 gamma)
{
	vec4 edge;
	float curve;

	curve = loc / extend;
	curve = (curve < 0.5) ? 
		lumCon * pow(2.0 * curve, blePow) 
		: 
		1.0 - (1.0 - lumCon) * pow(2.0 * (1.0 - curve), blePow);
	
	edge = vec4(pow(curve, 1.0 / gamma.r), 
				pow(curve, 1.0 / gamma.g),
				pow(curve, 1.0 / gamma.b),
				1.0);
	
	return edge;
}

vec4 drawSmoothEdges(in vec4 overlap, in vec4 blankout, in vec4 color)
{
	vec2 xy = gl_TexCoord[0].xy;
	vec2 texCoordOffset = vec2(0.0,0.0);
	vec2 xy_t = xy + texCoordOffset.xy;
	vec4 blank = vec4(0.0,0.0,0.0,0.0);	
	
	float proj2 = 1.0;//projectors ... this basically defines a limit;
	float thresh = proj2 * tex_w + overlap.x;//(projectors - overlap.x) * tex_w;
	float blnPwr = BlendPower;
	float slc    = 0.0;
	vec3 gamma3   = vec3(4.0, 4.0, 4.0);
	slc += 0.5;
	
	vec4 sebImage = 
		(blankout.x + overlap.x > xy.x) ? 
			(blankout.x > xy.x) ? 	
				blank 							//leftBlankout
			:	(blankout.z + overlap.z > xy.y) ?
					(blankout.z > xy.y) ? 
						blank					//leftBottomBlankOut
					: 	texture2DRect(tex0, xy_t) 	*		//leftBottomBlend
						drawSmoothEdge(xy.x - blankout.x, overlap.x, blnPwr, slc, gamma3) * 
						drawSmoothEdge(xy.y - blankout.z, overlap.z, blnPwr, slc, gamma3)
				: 	(tex_h - blankout.w - overlap.w < xy.y) ?  
						(tex_h - blankout.w < xy.y) ? 
							blank				//leftTopBlankout
						: 	texture2DRect(tex0, xy_t) 	*	//LeftTopBlend
							drawSmoothEdge(xy.x - blankout.x, overlap.x, blnPwr, slc, gamma3) * 
							drawSmoothEdge(tex_h - blankout.w - xy.y, overlap.w, blnPwr, slc, gamma3)					
							:	texture2DRect(tex0, xy_t) *		//leftBlankout
						drawSmoothEdge(xy.x - blankout.x, overlap.x, blnPwr, slc, gamma3)// + vec4(0.5, 0, 0.5, 0)	// debug: magenta
		:	(tex_w - blankout.y - overlap.y < xy.x) ? 
				(tex_w - blankout.y < xy.x) ? 
					blank						//rightBlankout
				:	(blankout.z + overlap.z > xy.y) ?
						(blankout.z > xy.y) ? 
							blank 				//rightBottomBlankout
						: 	texture2DRect(tex0, xy_t) 	*	//rightBottomBlend
							drawSmoothEdge(tex_w - blankout.y - xy.x, overlap.y, blnPwr, slc, gamma3) *
							drawSmoothEdge(xy.y - blankout.z, overlap.z, blnPwr, slc, gamma3)
					:	(tex_h - blankout.w - overlap.w < xy.y) ?
							(tex_h - blankout.w < xy.y) ? 
								blank 			//rightTopBlankout
							:	texture2DRect(tex0, xy_t) * //rightTopBlend
								drawSmoothEdge(tex_w - blankout.y - xy.x, overlap.y, blnPwr, slc, gamma3) * 
								drawSmoothEdge(tex_h - blankout.w - xy.y, overlap.w, blnPwr, slc, gamma3)
						:	texture2DRect(tex0, xy_t) * 	//rightBlend
							drawSmoothEdge(tex_w - blankout.y - xy.x, overlap.y, blnPwr, slc, gamma3)// + vec4(0, 0, 0.5, 0)	// debug: blue
			:	(blankout.z + overlap.z > xy.y) ?
					(blankout.z > xy.y) ? 
						blank 					//BottomBlankout
					: 	texture2DRect(tex0, xy_t) * 		//BottomBlend
						drawSmoothEdge(xy.y - blankout.z, overlap.z, blnPwr, slc, gamma3)
				:	(tex_h - blankout.w - overlap.w < xy.y) ?
						(tex_h - blankout.w < xy.y) ? 
							blank 				//TopBlankout
						:	texture2DRect(tex0, xy_t) * 	//TopBlend
							drawSmoothEdge(tex_h - blankout.w - xy.y, overlap.w, blnPwr, slc, gamma3)		
							:	texture2DRect(tex0, xy_t);// + vec4(0, 0.5, 0.5, 0);	// debug: teal
	
//	if(xy_t.x < thresh) sebImage.rgb += vec3(0, 1.0, 0);	// debug
	
	return sebImage;
}

vec4 drawSolidEdges(vec4 overlap, vec4 blankout, vec4 color)
{	
	
	vec2 xy = gl_TexCoord[0].xy;
	vec2 texCoordOffset = vec2(0.0,0.0);
	vec2 xy_t = xy + texCoordOffset.xy;
	vec4 blank = vec4(0.0,0.0,0.0,0.0);		
	vec4 edgeImage =
			(blankout.x + overlap.x > xy.x) ?
				(blankout.x > xy.x) ?
					blank				//leftBlankout
				:	(blankout.z + overlap.z > xy.y) ?
						(blankout.z > xy.y) ?
							blank			//leftBottomBlankout
						: 	color			//leftBottomColor
					: 	(tex_h - blankout.w - overlap.w < xy.y) ?
							(tex_h - blankout.w < xy.y) ?
								blank 		//leftTop
							: 	color 		//leftTopColor
						:	color			//leftColor
			:	(tex_w - blankout.y - overlap.y < xy.x) ?
					(tex_w - blankout.y < xy.x) ?
						blank				//rightBlankout
					:	(blankout.z + overlap.z > xy.y) ?
							(blankout.z > xy.y) ?
								blank 		//rightBottomBlankout
							: 	color		//rightBottomColor
						:	(tex_h - blankout.w - overlap.w < xy.y) ?
								(tex_h - blankout.w < xy.y) ? 
									blank 	//rightTopBlankout
								:	color 	//rightToColor
							:	color 		//rightColor
				:	(blankout.z + overlap.z > xy.y) ?
						(blankout.z > xy.y) ? 
							blank 			//BottomBlankout
						: 	color			//BottomColor
					:	(tex_h - blankout.w - overlap.w < xy.y) ?
							(tex_h - blankout.w < xy.y) ? 
								blank 		//TopBlankout
							:	color		//TopColor
						:	texture2DRect(tex0, xy_t);		
	return edgeImage;
}

vec4 overlay(vec4 myInput, vec4 previousmix, vec4 amount){

	float luminance = dot(previousmix.rgb,LumCoeff);
	float mixamount = clamp((luminance - 0.45) * 10., 0., 1.);

	vec4 branch1 = two * previousmix * myInput;
	vec4 branch2 = one - (two * (one - previousmix) * (one - myInput));
	
	vec4 result = mix(branch1, branch2, vec4(mixamount) );

	return mix(previousmix, result, amount);
}

vec4 gaussianBlur(void){

	float blurSize = 1.0/tex_w;

	// Incremental Gaussian Coefficent Calculation (See GPU Gems 3 pp. 877 - 889)
  	vec3 incrementalGaussian;
  	incrementalGaussian.x = 1.0 / (sqrt(2.0 * pi) * sigma);
  	incrementalGaussian.y = exp(-0.5 / (sigma * sigma));
  	incrementalGaussian.z = incrementalGaussian.y * incrementalGaussian.y;
	
	vec4 avgValue = vec4(0.0, 0.0, 0.0, 0.0);
  	float coefficientSum = 0.0;

	// Take the central sample first...
  	avgValue += texture2DRect(tex0, gl_TexCoord[0].xy) * incrementalGaussian.x;
  	coefficientSum += incrementalGaussian.x;
  	incrementalGaussian.xy *= incrementalGaussian.yz;

  	// Go through the remaining 8 vertical samples (4 on each side of the center)
  	for (float i = 1.0; i <= numBlurPixelsPerSide; i++) { 
    		avgValue += texture2DRect(tex0, gl_TexCoord[0].xy - i * blurSize * blurMultiplyVec) * incrementalGaussian.x;         
    		avgValue += texture2DRect(tex0, gl_TexCoord[0].xy + i * blurSize * blurMultiplyVec) * incrementalGaussian.x;         
    		coefficientSum += (incrementalGaussian.x * 2.0);
    		incrementalGaussian.xy *= incrementalGaussian.yz;
  	}

	return avgValue / coefficientSum;
}

void main(void){
	
	///////////////////////////////////////////////
	// blending borders of original texture color
	vec4 overlap = vec4 (20.0,20.0,20.0,20.0);
	vec4 blankout = vec4 (0.0,0.0,0.0,0.0);
	vec4 SolidEdgeColor = vec4(0.0,0.0,0.0,1.0);
	vec4 blendingColor = drawSmoothEdges(overlap, blankout, SolidEdgeColor);
	vec4 solidColor = drawSolidEdges(overlap, blankout, SolidEdgeColor);
	vec4 colorBase = blendingColor;

	///////////////////////////////////////////////
	// Gamma correction is the operation that aims
	// to cancel the non-linearity property of a
	// display device (CRT or LCD)
	vec4 gammaColor = vec4(gamma,gamma,gamma,1.0);
	vec4 gammaCorrected = vec4(pow(colorBase,1.0/gammaColor));
	gammaCorrected.a = 1.0;
	
	///////////////////////////////////////////////
	// brightness, saturation, contrast
	vec3 AvgLumin = vec3(AvgLumR, AvgLumG, AvgLumB);
	vec3 brtColor = gammaCorrected.rgb * brightness;
	float intensityf = dot(brtColor, LumCoeff);
	vec3 intensity = vec3(intensityf,intensityf,intensityf);
	vec3 satColor = mix(intensity, brtColor, saturation);
	vec3 conColor = mix(AvgLumin, satColor, contrast);
	vec4 correctedColor = vec4(conColor.rgb,colorBase.a);
	
	///////////////////////////////////////////////
	// analog film bleach effect
	vec4 luma = vec4(vec3(dot(correctedColor.rgb,LumCoeff)),colorBase.a);
	vec4 bleachColor = overlay(luma,correctedColor,vec4(filmBleach));
	
	///////////////////////////////////////////////
	// film technicolor effect
	vec4 redrecord = bleachColor * redfilter;
	vec4 bluegreenrecord = bleachColor * bluegreenfilter;
	vec4 rednegative = vec4(redrecord.r);
	vec4 bluegreennegative = vec4((bluegreenrecord.g + bluegreenrecord.b)/2.0);

	vec4 redoutput = rednegative + cyanfilter;
	vec4 bluegreenoutput = bluegreennegative + magentafilter;

	vec4 techniColor = redoutput * bluegreenoutput;
	techniColor = mix(bleachColor, techniColor, technicolor);
	techniColor.a = bleachColor.a;

	///////////////////////////////////////////////
	// white diffusion
	vec4 origluma = vec4(dot(techniColor, grayXfer));
	vec4 filmLuma = vec4(dot(gaussianBlur(),grayXfer));
	vec4 contrast = mix(origluma, filmLuma, diffusion);
	vec4 exposureresult = log2(vec4(pow(exposure + sqrtoftwo, 2.0))) * filmLuma;
	
	vec4 outputColor = mix(origluma, exposureresult, filmLuma * contrast);
	outputColor = mix(techniColor, outputColor , whiteDiffusion);
	outputColor.a = techniColor.a;	
	
	// final color
	gl_FragColor = outputColor;
	
}
