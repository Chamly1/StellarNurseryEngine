#include <vulkan/vulkan.h>

#include <string>

std::string severityToString(VkDebugUtilsMessageSeverityFlagBitsEXT severity);
std::string typeToString(VkDebugUtilsMessageTypeFlagsEXT messageType);

VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);