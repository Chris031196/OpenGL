uniform sampler2D refractTex;
uniform sampler2D reflectTex;
uniform sampler2D bumpMap;

uniform float refractRatio;

uniform float reflectRatio;

uniform float mappingRatio;

uniform int extendedBlending;

varying mat4 texMat;

void main(void)
{
  vec4 refractcoord;
  vec4 reflectcoord;
  vec4 offsetColor = (texture2D(bumpMap, vec2(gl_TexCoord[1])) + 
    texture2D(bumpMap, vec2(gl_TexCoord[1]) * 4.0)) / 2.0;
  vec4 origOffset = offsetColor;
  vec4 color;
  vec4 reflectColor = vec4(1.0, 1.0, 1.0, 1.0);
  vec4 refractColor = vec4(1.0, 1.0, 1.0, 1.0);
  vec4 blendedColor;
  
  offsetColor -= 0.5;
  offsetColor *= 2.0;

  refractcoord = texMat * gl_TexCoord[0];
  refractColor = texture2DProj(refractTex, refractcoord);
  refractcoord = gl_TexCoord[0];
  refractcoord.x += offsetColor[0] * refractColor[3] * refractRatio;
  refractcoord.z += offsetColor[1] * refractColor[3] * refractRatio;
  refractcoord = texMat * refractcoord;

  reflectcoord = texMat * gl_TexCoord[0];
  reflectColor = texture2DProj(reflectTex, reflectcoord);
  reflectcoord = gl_TexCoord[0];
  reflectcoord.x -= offsetColor[0] * reflectColor[3] * reflectRatio;
  reflectcoord.z -= offsetColor[1] * reflectColor[3] * reflectRatio;
  reflectcoord = texMat * reflectcoord;
  
  reflectColor = texture2DProj(reflectTex, reflectcoord);
  refractColor = texture2DProj(refractTex, refractcoord);

  reflectColor[3] = 1.0;
  refractColor[3] = 1.0;
  
  if (extendedBlending == 0)
  {
    float mappingRefract, mappingReflect;
    mappingRefract = mappingRatio * 255.0;
    mappingReflect = 255.0 - mappingRefract;
    mappingRefract /= 255.0;
    mappingReflect /= 255.0;
    blendedColor = refractColor * mappingRefract + reflectColor * mappingReflect;
    blendedColor.a = 1.0;
  }
  else
  {
    float Alpha, reflectAlpha, refractAlpha;
    Alpha = (refractColor.r + refractColor.g + refractColor.b) / 3.0;
    if (Alpha > 1.0)
      Alpha = 1.0;
    if (Alpha < 0.0)
      Alpha = 0.0;
      
    refractAlpha = Alpha * 255.0;
    reflectAlpha = 255.0 - refractAlpha;
    refractAlpha /= 255.0;
    reflectAlpha /= 255.0;
    blendedColor = reflectColor * reflectAlpha + refractColor * refractAlpha;
  }
  
  gl_FragColor = blendedColor;
}