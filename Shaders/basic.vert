#version 120

uniform Transformation {
    mat4 projection_matrix;
    mat4 modelview_matrix;
};

uniform vec3 vertex;

void main() {
    gl_Position = projection_matrix * modelview_matrix * vec4(vertex, 1.0);
}