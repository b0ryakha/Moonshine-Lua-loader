//#include "Blur.hpp"
//
//Blur::Blur(size_t x, size_t y, size_t w, size_t h, int blur_strength, size_t rounding) {
//	if (!shader.loadFromMemory(shader_src::vertex, shader_src::gaussian_blur))
//		throw_error("[Blur] Shader loading error!");
//
//	shader.setUniform("data", sf::Vector3f(w, h, std::min(std::max(blur_strength, 0), 100) / 10.f));
//
//	shape = SuperEllipse(x, y, w, h, rounding);
//	shape.setTextureRect(sf::IntRect(x, y, w, h));
//}
//
//void Blur::draw(sf::RenderTexture& render_buffer) {
//	shape.setTexture(&render_buffer.getTexture());
//	render_buffer.draw(shape, &shader);
//}