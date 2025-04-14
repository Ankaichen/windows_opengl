#version 330 core

out vec4 FragColor;

in vec2 uv;
in vec3 normal;
in vec3 worldPosition;

uniform sampler2D samplerDiffuse;
uniform sampler2D samplerSpecularMask;

uniform vec3 cameraPosition;
uniform vec3 ambientColor;
uniform float shiness;

struct DirectionalLight {
    vec3 direction;
    vec3 color;
    float specularIntensity;
};

struct PointLight {
    vec3 position;
    vec3 color;
    float specularIntensity;
    float k2, k1, kc;
};

struct SpotLight {
    vec3 position;
    vec3 targetDirection;
    vec3 color;
    float innerLine;
    float outerLine;
    float specularIntensity;
};

uniform SpotLight spotLights[1];
uniform DirectionalLight directionalLights[1];
uniform PointLight pointLights[3];

// 计算漫反射Diffuse
vec3 calculateDiffuse(vec3 lightColor, vec3 objectColor, vec3 lightDirection, vec3 objectNormal) {
    float diffuse = clamp(dot(-lightDirection, objectNormal), 0.f, 1.f);// 计算夹角作为光的吸收率
    vec3 diffuseColor = lightColor * diffuse * objectColor;
    return diffuseColor;
}

// 计算镜面反射Specular
vec3 calculateSpecular(vec3 lightColor, vec3 lightDirection, vec3 objectNormal, vec3 viewDirection, float intensity) {
    // 防止背面光
    float dotResult = dot(-lightDirection, objectNormal);
    float flag = step(0.000000001f, dotResult);
    vec3 lightRef = normalize(reflect(lightDirection, objectNormal));
    float specular = clamp(dot(lightRef, -viewDirection), 0.f, 1.f);
    specular = pow(specular, shiness);// 控制光斑大小
    // float specularMask = texture(samplerSpecularMask, uv).r;
    vec3 specularColor = flag * intensity * specular * lightColor;
    return specularColor;
}

vec3 calculateSpotLight(SpotLight spotLight, vec3 normal, vec3 viewDirection) {
    // 准备数据
    vec3 objectColor = texture(samplerDiffuse, uv).xyz;
    vec3 lightDirection = normalize(worldPosition - spotLight.position);
    vec3 targetDirection = normalize(spotLight.targetDirection);
    // 计算spotlight的照射范围
    float cGamma = dot(lightDirection, targetDirection);
    float intensity = clamp((cGamma - spotLight.outerLine) / (spotLight.innerLine - spotLight.outerLine), 0.f, 1.f);
    // 计算漫反射
    vec3 diffuseColor = calculateDiffuse(spotLight.color, objectColor, lightDirection, normal);
    // 计算镜面反射
    vec3 specularColor = calculateSpecular(spotLight.color, lightDirection, normal, viewDirection, spotLight.specularIntensity);
    return intensity * (diffuseColor + specularColor);
}

vec3 calculateDirectionLight(DirectionalLight directionalLight, vec3 normal, vec3 viewDirection) {
    vec3 objectColor = texture(samplerDiffuse, uv).xyz;
    vec3 lightDirection = normalize(directionalLight.direction);
    vec3 diffuseColor = calculateDiffuse(directionalLight.color, objectColor, lightDirection, normal);
    vec3 specularColor = calculateSpecular(directionalLight.color, lightDirection, normal, viewDirection, directionalLight.specularIntensity);
    return diffuseColor + specularColor;
}

vec3 calculatePointLight(PointLight pointLight, vec3 normal, vec3 viewDirection) {
    vec3 objectColor = texture(samplerDiffuse, uv).xyz;
    vec3 lightDirection = normalize(worldPosition - pointLight.position);
    float dist = length(worldPosition - pointLight.position);// 计算衰减
    float attenuation = 1.f / (pointLight.k2 * dist * dist + pointLight.k1 * dist + pointLight.kc);
    vec3 diffuseColor = calculateDiffuse(pointLight.color, objectColor, lightDirection, normal);
    vec3 specularColor = calculateSpecular(pointLight.color, lightDirection, normal, viewDirection, pointLight.specularIntensity);
    return attenuation * (diffuseColor + specularColor);
}

void main() {
    vec3 result = vec3(0.f, 0.f, 0.f);
    vec3 objectColor = texture(samplerDiffuse, uv).xyz;
    vec3 normalN = normalize(normal);
    vec3 viewDirectionN = normalize(worldPosition - cameraPosition);// 世界坐标系下的视线方向
    result += calculateSpotLight(spotLights[0], normalN, viewDirectionN);
    result += calculateDirectionLight(directionalLights[0], normalN, viewDirectionN);
    result += calculatePointLight(pointLights[0], normalN, viewDirectionN);
    result += calculatePointLight(pointLights[1], normalN, viewDirectionN);
    result += calculatePointLight(pointLights[2], normalN, viewDirectionN);
    vec3 finalColor = result + objectColor * ambientColor;
    FragColor = vec4(finalColor, 1.f);
}
