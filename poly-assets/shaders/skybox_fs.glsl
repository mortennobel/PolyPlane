uniform vec4 mainColor;
uniform sampler2D mainTexture;

in vec3 vPos;
out vec4 fragColor;

void main(void)
{
    vec3 vNorm = normalize(vPos);
    fragColor = texture(mainTexture,vNorm.xy*0.5+vec2(0.5))*mainColor;
}