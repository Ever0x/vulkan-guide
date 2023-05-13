// vulkan_guide.h : Include file for standard system include files,
// or project specific include files.

#pragma once
#include <vk_types.h>

namespace vkinit 
{
	VkCommandPool create_command_pool(VkDevice device, uint32_t queue_family_index, VkCommandPoolCreateFlags flags);
	VkCommandBuffer create_command_buffer(VkDevice device, VkCommandPool command_pool, VkCommandBufferLevel level);
}

