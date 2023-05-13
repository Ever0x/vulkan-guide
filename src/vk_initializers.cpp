#include <iostream>
#include <vk_initializers.h>

#define VK_CHECK(func) {VkResult error = func; if(error) {std::cout << error << '\n'; abort();}}

VkCommandPool vkinit::create_command_pool(VkDevice device, uint32_t queue_family_index, VkCommandPoolCreateFlags flags)
{
	VkCommandPoolCreateInfo command_pool_info{};
	command_pool_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	command_pool_info.queueFamilyIndex = queue_family_index;
	command_pool_info.flags = flags;

	VkCommandPool command_pool;
	VK_CHECK(vkCreateCommandPool(device, &command_pool_info, nullptr, &command_pool));

	return command_pool;
}

VkCommandBuffer vkinit::create_command_buffer(VkDevice device, VkCommandPool command_pool, VkCommandBufferLevel level)
{
	VkCommandBufferAllocateInfo command_buffer_info{};
	command_buffer_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	command_buffer_info.commandPool = command_pool;
	command_buffer_info.commandBufferCount = 1u;
	command_buffer_info.level = level;

	VkCommandBuffer command_buffer;
	VK_CHECK(vkAllocateCommandBuffers(device, &command_buffer_info, &command_buffer));

	return command_buffer;
}
