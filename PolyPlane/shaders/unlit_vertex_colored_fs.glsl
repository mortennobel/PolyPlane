in vec2 vUv;
in vec3 vNormal;
in vec3 vEcPosition;
in vec4 vShadowMapCoord;
in vec4 vColor;

out vec4 fragColor;

uniform vec4 mainColor;
uniform sampler2D mainTexture;

#pragma include "assets/shaders/light.glsl"
#pragma include "assets/shaders/shadowmap.glsl"

void main(void)
{

    float dist = min(100,length(vEcPosition));
    float distGradient = pow((dist/100),0.1)*0.2;
    vec3 color = vColor.xyz * mainColor.xyz - vec3 (distGradient);

    fragColor = vec4(texture(mainTexture,vUv).xyz*color, 1.0);
}
 