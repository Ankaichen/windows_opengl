#version 330 core

out vec4 FragColor;

in vec2 uv;
in vec3 normal;
in vec3 worldPosition;

uniform sampler2D samplerDiffuse;
uniform sampler2D samplerSpecularMask;
uniform vec3 lightDirection;
uniform vec3 lightColor;
uniform vec3 cameraPosition;
uniform float specularIntensity;
uniform vec3 ambientColor;
uniform float shiness;

void main() {
    vec3 objectColor = texture(samplerDiffuse, uv).xyz;
    vec3 normalN = normalize(normal);
    vec3 lightDirectionN = normalize(lightDirection);
    vec3 viewDirectionN = normalize(worldPosition - cameraPosition); // 世界坐标系下的视线方向
    // 漫反射
    float diffuse = clamp(dot(-lightDirectionN, normalN), 0.f, 1.f); // 计算夹角作为光的吸收率
    vec3 diffuseColor = lightColor * diffuse * objectColor;
    // 镜面反射
    // 防止背面光
    float dotResult = dot(-lightDirectionN, normalN);
    float flag = step(0.000000001f, dotResult);
    vec3 lightRef = normalize(reflect(lightDirectionN, normalN));
    float specular = clamp(dot(lightRef, -viewDirectionN), 0.f, 1.f);
    specular = pow(specular, shiness); // 控制光斑大小
    float specularMask = texture(samplerSpecularMask, uv).r;
    vec3 specularColor = flag * specularIntensity * specularMask * specular * lightColor;
    // 环境光

    vec3 finalColor = diffuseColor + specularColor + objectColor * ambientColor;
    FragColor = vec4(finalColor, 1.f);
}
