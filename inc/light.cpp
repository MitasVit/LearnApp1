#include "light.h"

glm::vec3 col2vec(int r, int g, int b){
	return glm::vec3(r/255.0f, g/255.0f, b/255.0f);
}

glm::vec3 fcol2vec(float col[4]){
	return glm::vec3(col[0], col[1], col[2]);
}

glm::fvec3 col2vecf(int r, int g, int b){
	return glm::fvec3(r/255.0f, g/255.0f, b/255.0f);
}

glm::fvec3 fcol2vecf(float col[4]){
	return glm::fvec3(col[0], col[1], col[2]);
}

glm::fvec4 genFcol4(int r, int g, int b, int a){
	return glm::fvec4(r/255.0f, g/255.0f, b/255.0f, a/255.0f);
}
glm::fvec3 genFcol3(int r, int g, int b){
	return glm::fvec3(r/255.0f, g/255.0f, b/255.0f);
}

glm::fvec4 genFcol4(float col[4]){
	return glm::fvec4(col[0], col[1], col[2], col[3]);
}
/*
float * vec3float4(glm::vec3 c){
    float f[4] = {c.x,c.y,c.z, 1.0f};
    return f;
}*/