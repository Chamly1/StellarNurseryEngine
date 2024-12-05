#ifndef PIPELINE_HPP
#define PIPELINE_HPP

#include "Device.hpp"

#include "vulkan/vulkan.h"

#include <string>
#include <memory>

struct PipelineConfigInfo {
	VkViewport viewport;
	VkRect2D scissor;
	VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
	VkPipelineRasterizationStateCreateInfo rasterizationInfo;
	VkPipelineMultisampleStateCreateInfo multisampleInfo;
	VkPipelineColorBlendAttachmentState colorBlendAttachment;
	VkPipelineColorBlendStateCreateInfo colorBlendInfo;
	VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
	VkPipelineLayout pipelineLayout = nullptr;
	VkRenderPass renderPass = nullptr;
	uint32_t subpass = 0;

	PipelineConfigInfo() = default;

	// Delete default copy/move constructor/asigne operator beacuse colorBlendInfo
	// field contains pointer to colorBlendAttachment field which became invalid
	// after shallow copy
	PipelineConfigInfo(const PipelineConfigInfo& other) = delete;
	PipelineConfigInfo& operator=(const PipelineConfigInfo& other) = delete;
	PipelineConfigInfo(PipelineConfigInfo&& other) = delete;
	PipelineConfigInfo& operator=(PipelineConfigInfo&& other) = delete;
};

class Pipeline {
private:
	Device& mDevice;
	VkPipeline mGraphicsPipeline;

	VkShaderModule createShaderModule(const std::vector<char>& code);

public:
	Pipeline(Device& device, 
		const std::string& vertFilepath, 
		const std::string& fragFilepath,
		const PipelineConfigInfo& configInfo);
	~Pipeline();

	void bind(VkCommandBuffer commandBuffer);

	static std::unique_ptr<PipelineConfigInfo> getDefaultPipelineConfigInfo(uint32_t width, uint32_t height);

	Pipeline(const Pipeline& other) = delete;
	Pipeline& operator=(const Pipeline& other) = delete;
	Pipeline(Pipeline&& other) = delete;
	Pipeline& operator=(Pipeline&& other) = delete;
};

#endif // PIPELINE_HPP
