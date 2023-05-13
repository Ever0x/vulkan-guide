#include "vk_engine.h"
#include <iostream>

#include <SDL.h>
#include <SDL_vulkan.h>

#include <vk_types.h>
#include <vk_initializers.h>

#include <VkBootstrap.h>

void VulkanEngine::init()
{
	// We initialize SDL and create a window with it. 
	SDL_Init(SDL_INIT_VIDEO);

	SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_VULKAN);
	
	_window = SDL_CreateWindow(
		"Vulkan Engine",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		_windowExtent.width,
		_windowExtent.height,
		window_flags
	);
	
	init_vulkan();
	init_swapchain();
	init_commands();

	//everything went fine
	_isInitialized = true;
}
void VulkanEngine::cleanup()
{	
	if (_isInitialized) 
	{	
		vkDestroyCommandPool(_device, _command_pool, nullptr);

		vkDestroySwapchainKHR(_device, _swapchain, nullptr);

		for (auto image_view : _swapchain_image_views)
			vkDestroyImageView(_device, image_view, nullptr);

		vkDestroyDevice(_device, nullptr);
		vkDestroySurfaceKHR(_instance, _surface, nullptr);
		vkb::destroy_debug_utils_messenger(_instance, _debug_messenger);
		vkDestroyInstance(_instance, nullptr);

		SDL_DestroyWindow(_window);
	}
}

void VulkanEngine::draw()
{
	//nothing yet
}

void VulkanEngine::run()
{
	SDL_Event e;
	bool bQuit = false;

	//main loop
	while (!bQuit)
	{
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			switch (e.type)
			{
				case SDL_QUIT: bQuit = true; break;
				case SDL_KEYDOWN: std::cout << e.key.keysym.scancode << '\n'; break;
				default: break;
			}
		}

		draw();
	}
}

void VulkanEngine::init_vulkan()
{
	auto vkbInstance = vkb::InstanceBuilder{}.set_app_name("Vulkan App").request_validation_layers().require_api_version(1u, 1u)
		.use_default_debug_messenger().build().value();

	_instance = vkbInstance.instance;
	_debug_messenger = vkbInstance.debug_messenger;

	SDL_Vulkan_CreateSurface(_window, _instance, &_surface);

	auto vkb_physical_device = vkb::PhysicalDeviceSelector{ vkbInstance }.set_minimum_version(1u, 1u).set_surface(_surface)
		.select().value();

	auto vkb_device = vkb::DeviceBuilder{ vkb_physical_device }.build().value();

	_physical_device = vkb_physical_device.physical_device;
	_device = vkb_device.device;

	_graphics_queue = vkb_device.get_queue(vkb::QueueType::graphics).value();
	_graphics_queue_family = vkb_device.get_queue_index(vkb::QueueType::graphics).value();
}

void VulkanEngine::init_swapchain()
{
	auto vkb_swapchain = vkb::SwapchainBuilder{ _physical_device, _device, _surface }.use_default_format_selection()
		.set_desired_present_mode(VK_PRESENT_MODE_FIFO_KHR).set_desired_extent(_windowExtent.width, _windowExtent.height)
		.build().value();

	_swapchain = vkb_swapchain.swapchain;
	_swapchain_image_format = vkb_swapchain.image_format;
	_swapchain_images = vkb_swapchain.get_images().value();
	_swapchain_image_views = vkb_swapchain.get_image_views().value();
}

void VulkanEngine::init_commands()
{
	_command_pool = vkinit::create_command_pool(_device, _graphics_queue_family, VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT);
	_command_buffer = vkinit::create_command_buffer(_device, _command_pool, VK_COMMAND_BUFFER_LEVEL_PRIMARY);


}
