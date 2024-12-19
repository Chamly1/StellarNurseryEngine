#ifndef MODEL_HPP
#define MODEL_HPP

#include "Device.hpp"

#include "glm/glm.hpp"

struct Vertex {
	glm::vec2 position;
	glm::vec3 color;

	static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();
	static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();
};

class Model {
private:
	Device& mDevice;
	VkBuffer mVertexBuffer;
	VkDeviceMemory mVertexBufferMemory;
	uint32_t mVertexCount;

	void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

public:
	Model(Device& device, const std::vector<Vertex>& vertices);
	~Model();

	void bind(VkCommandBuffer commandBuffer);
	void draw(VkCommandBuffer commandBuffer);

	Model(const Model& other) = delete;
	Model& operator=(const Model& other) = delete;
	Model(Model&& other) = delete;
	Model& operator=(Model&& other) = delete;
};

#endif // MODEL_HPP
