#include "Model.hpp"

std::vector<VkVertexInputBindingDescription> Vertex::getBindingDescriptions() {
	std::vector<VkVertexInputBindingDescription> bindingDescription(1);
	bindingDescription[0].binding = 0;
	bindingDescription[0].stride = sizeof(Vertex);
	bindingDescription[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

	return bindingDescription;
}

std::vector<VkVertexInputAttributeDescription> Vertex::getAttributeDescriptions() {
	std::vector<VkVertexInputAttributeDescription> attributeDescriptions(2);
	attributeDescriptions[0].binding = 0;
	attributeDescriptions[0].location = 0;
	attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
	attributeDescriptions[0].offset = offsetof(Vertex, position);

	attributeDescriptions[1].binding = 0;
	attributeDescriptions[1].location = 1;
	attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
	attributeDescriptions[1].offset = offsetof(Vertex, color);

	return attributeDescriptions;
}

Model::Model(Device& device, const std::vector<Vertex>& vertices) : mDevice{device} {
	mVertexCount = static_cast<uint32_t>(vertices.size());

	VkDeviceSize bufferSize = sizeof(vertices[0]) * mVertexCount;
	mDevice.createBuffer(
		bufferSize,
		VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
		mVertexBuffer,
		mVertexBufferMemory);

	void* data;
	vkMapMemory(mDevice.device(), mVertexBufferMemory, 0, bufferSize, 0, &data);
	memcpy(data, vertices.data(), static_cast<size_t>(bufferSize));
	vkUnmapMemory(mDevice.device(), mVertexBufferMemory);
}

Model::~Model() {
	vkDestroyBuffer(mDevice.device(), mVertexBuffer, nullptr);
	vkFreeMemory(mDevice.device(), mVertexBufferMemory, nullptr);
}

void Model::bind(VkCommandBuffer commandBuffer) {
	VkBuffer buffers[] = { mVertexBuffer };
	VkDeviceSize offsets[] = { 0 };
	vkCmdBindVertexBuffers(commandBuffer, 0, 1, buffers, offsets);
}

void Model::draw(VkCommandBuffer commandBuffer) {
	vkCmdDraw(commandBuffer, mVertexCount, 1, 0, 0);
}
