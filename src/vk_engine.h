// vulkan_guide.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <vk_types.h>
#include <vector>

class VulkanEngine 
{
public:
	//initializes everything in the engine
	void init();

	//shuts down the engine
	void cleanup();

	//draw loop
	void draw();

	//run main loop
	void run();

private:
	bool _isInitialized{};
	int _frameNumber{};

	VkExtent2D _windowExtent{ 1600 , 900 };
	struct SDL_Window* _window{};

	VkInstance _instance;
	VkDebugUtilsMessengerEXT _debug_messenger;
	VkPhysicalDevice _physical_device;
	VkDevice _device;
	VkSurfaceKHR _surface;

	VkSwapchainKHR _swapchain;
	VkFormat _swapchain_image_format;
	std::vector<VkImage> _swapchain_images;
	std::vector<VkImageView> _swapchain_image_views;

	VkQueue _graphics_queue;
	uint32_t _graphics_queue_family;
	VkCommandPool _command_pool;
	VkCommandBuffer _command_buffer;

	void init_vulkan();
	void init_swapchain();
	void init_commands();
};
