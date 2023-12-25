//#pragma once
//
//#include <SFML/Graphics.hpp>
//
//#include "SuperEllipse.hpp"
//#include "misc_functions.hpp"
//
//namespace shader_src {
//    constexpr char vertex[] =
//    "void main() {                                                \
//	    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0; \
//        gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;   \
//    }";
//
//    constexpr char gaussian_blur[] =
//    "uniform sampler2D texture;                                                       \
//    uniform vec3 data;                                                                \
//    const float quality = 4.0;                                                        \
//    const float dir = 13.0;                                                           \
//    const float dPI = 6.28318530718;                                                  \
//    void main() {                                                                     \
//        vec2 pos = gl_TexCoord[0].xy;                                                 \
//        vec2 radius = data.z / data.xy;                                               \
//        vec4 pixel = texture2D(texture, pos);                                         \
//        for (float d = 0.0; d < dPI; d += dPI / dir) {                                \
//            for (float i = 1.0 / quality; i <= 1.0; i += 1.0 / quality) {             \
//                pixel += texture2D(texture, pos + vec2(cos(d), sin(d)) * radius * i); \
//            }                                                                         \
//        }                                                                             \
//        gl_FragColor = pixel / (quality * dir + 1.0);                                 \
//    }";
//}
//
//class Blur final {
//private:
//	sf::Shader shader;
//    SuperEllipse shape;
//
//public:
//    Blur(size_t x, size_t y, size_t w, size_t h, int blur_strength, size_t rounding = 0);
//    void draw(sf::RenderTexture& render_buffer);
//};