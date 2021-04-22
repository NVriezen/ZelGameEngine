#include "zel_api.h"
#include "../include/example_system.h"

//TODO game version going up when hitting build

#define ZEL_MAX_ENTITIES 0xFFFE //TODO fix this!!

zel_level_t* active_level;

// Called before the very first frame of the application.
void zel_initialization()
{
	PROFILE_FUNCTION();

	// Main Initialization
	zel_io_initialization();
	zel_resources_init();

	// Level Initialization - TODO: put this somewhere else (Level manager?)
	zel_print("Hello World\n");
	zel_level_t* example_level = zel_level_create("Example Level");
	active_level = example_level;

	zel_entity_id entity = zel_level_create_entity(active_level);

	// Registering Components
	zel_level_register_component<zel_transform_t>(active_level);
	zel_level_register_component<zel_camera_t>(active_level);
	zel_level_register_component_with_destroy<zel_material_t>(active_level, zel_material_destroy);//zel_level_register_component<zel_material_t>(active_level);
	zel_level_register_component_with_destroy<zel_mesh_t>(active_level, zel_mesh_destroy);

	// Transform
	zel_transform_t transform{ {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f} };
	zel_level_add_component(active_level, entity, transform);

	// Camera
	zel_entity_id camera_entity = zel_level_create_entity(active_level);
	zel_camera_t camera;
	camera.transform = { { 0.0f, 0.0f, 10.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f } };
	camera.up = {0.0f, 1.0f, 0.0f};
	camera.forward = { 0.0f, 0.0f, -1.0f };
	camera.projection = glm::ortho(-(float)360 * 0.5f, (float)360 * 0.5f, -(float)240 * 0.5f, (float)240 * 0.5f, 0.1f, 100.0f);
	camera.framebuffer_id = zel_framebuffer_create(game_resolution_x, game_resolution_y);

	glm::vec3 camera_position = glm::vec3(camera.transform.position.x, camera.transform.position.y, camera.transform.position.z);
	glm::vec3 camera_forward = glm::vec3(camera.forward.x, camera.forward.y, camera.forward.z);
	glm::vec3 camera_up = glm::vec3(camera.up.x, camera.up.y, camera.up.z);
	camera.view = glm::lookAt(camera_position, camera_position + camera_forward, camera_up);
	zel_level_add_component<zel_camera_t>(active_level, camera_entity, camera);

	// Mesh
	float vertices[] = {
		// positions				// texture coords
		 0.5f,  0.5f,  0.0f,		1.0f, 1.0f,   // top right
		 0.5f, -0.5f,  0.0f,		1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f,  0.0f,		0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f,  0.0f,		0.0f, 1.0f    // top left 
	};

	uint32_t indices[] = {
		0, 1, 3,
		1, 2, 3,
	};

	zel_mesh_t mesh = zel_mesh_create(vertices, (sizeof(float) * 20), indices, sizeof(uint32_t) * 6);
	zel_level_add_component<zel_mesh_t>(active_level, entity, mesh);

	//Material
	zel_resource_id default_shader = zel_shader_load("shaders/default.vertex", "shaders/default.fragment");
	zel_material_t material = zel_material_create(default_shader);
	zel_level_add_component<zel_material_t>(active_level, entity, material);
	zel_resources_unload(default_shader);

	//Texture
	zel_texture_t sprite = zel_texture_load("textures/test_image.png");
	zel_material_set_texture(&material, "texture0", 0);
	zel_level_get_component<zel_transform_t>(active_level, entity)->scale.x *= 32;
	zel_level_get_component<zel_transform_t>(active_level, entity)->scale.y *= 32;

	zel_level_register_system(active_level, example_system_update, example_system_name);
}

// Called every frame. Put your logic here.
void zel_logic(float delta_time)
{
	PROFILE_FUNCTION();

	for (std::pair<std::string, zel_system_t> system : active_level->systems)
	{
		system.second(active_level, delta_time);
	}
}

// Called every frame. Put your render code here.
void zel_render()
{
	PROFILE_FUNCTION();

	zel_clear_screen(0.03f, 0.07f, 0.21f, 1.0f);

	zel_renderer_general_update(active_level, 0);

	zel_framebuffer_bind_default();
}

// Called when the user wants to close the application
void zel_termination()
{
	zel_level_destroy(active_level);

	zel_print("Shutting down...");
}