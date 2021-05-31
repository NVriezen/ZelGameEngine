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

	// Registering Components
	zel_level_register_component<zel_transform_t>(active_level);
	zel_level_register_component<zel_camera_t>(active_level);
	zel_level_register_component_with_destroy<zel_material_t>(active_level, zel_material_destroy);
	zel_level_register_component_with_destroy<zel_mesh_t>(active_level, zel_mesh_destroy);

	//Entities
	zel_entity_id background_entity		= zel_level_create_entity(active_level);
	zel_entity_id enemy1_entity			= zel_level_create_entity(active_level);
	zel_entity_id enemy2_entity			= zel_level_create_entity(active_level);
	zel_entity_id enemy1_shadow_entity	= zel_level_create_entity(active_level);
	zel_entity_id enemy2_shadow_entity	= zel_level_create_entity(active_level);
	zel_entity_id player_entity			= zel_level_create_entity(active_level);

	// Transform
	zel_transform_t background_transform{ { 0.0f, 0.0f, 0.0f },{ 0.0f, 0.0f, 0.0f },{ 1.0f, 1.0f, 1.0f } };
	zel_level_add_component(active_level, background_entity, background_transform);

	zel_transform_t enemy1_transform{ { -64.0f, 32.0f, 0.0f },{ 0.0f, 0.0f, 0.0f },{ 1.0f, 1.0f, 1.0f } };
	zel_transform_t enemy2_transform{ { 64.0f, 32.0f, 0.0f },{ 0.0f, 0.0f, 0.0f },{ 1.0f, 1.0f, 1.0f } };
	zel_level_add_component(active_level, enemy1_entity, enemy1_transform);
	zel_level_add_component(active_level, enemy2_entity, enemy2_transform);

	zel_transform_t enemy1_shadow_transform{ { -64.0f, -32.0f, 0.0f },{ 0.0f, 0.0f, 0.0f },{ 1.0f, 1.0f, 1.0f } };
	zel_transform_t enemy2_shadow_transform{ { 64.0f, -32.0f, 0.0f },{ 0.0f, 0.0f, 0.0f },{ 1.0f, 1.0f, 1.0f } };
	zel_level_add_component(active_level, enemy1_shadow_entity, enemy1_shadow_transform);
	zel_level_add_component(active_level, enemy2_shadow_entity, enemy2_shadow_transform);

	zel_transform_t player_transform{ { 0.0f, 0.0f, 0.0f },{ 0.0f, 0.0f, 0.0f },{ 1.0f, 1.0f, 1.0f } };
	zel_level_add_component(active_level, player_entity, player_transform);

	// Camera
	zel_entity_id camera_entity = zel_level_create_entity(active_level);
	zel_camera_t camera;
	camera.transform = { { 0.0f, 0.0f, 200.0f },{ 0.0f, 0.0f, 0.0f },{ 1.0f, 1.0f, 1.0f } };
	camera.up = { 0.0f, 1.0f, 0.0f };
	camera.forward = { 0.0f, 0.0f, -1.0f };
	camera.projection = glm::ortho(-(float)game_resolution_x * 0.5f, (float)game_resolution_x * 0.5f, -(float)game_resolution_y * 0.5f, (float)game_resolution_y * 0.5f, 0.1f, 1000.0f);
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
	zel_level_add_component<zel_mesh_t>(active_level, background_entity,	mesh);
	zel_level_add_component<zel_mesh_t>(active_level, enemy1_entity,		mesh);
	zel_level_add_component<zel_mesh_t>(active_level, enemy2_entity,		mesh);
	zel_level_add_component<zel_mesh_t>(active_level, enemy1_shadow_entity, mesh);
	zel_level_add_component<zel_mesh_t>(active_level, enemy2_shadow_entity, mesh);
	zel_level_add_component<zel_mesh_t>(active_level, player_entity, mesh);

	//Material
	//We need all these shaders because otherwise the textures won't be used properly.
	//Everything would then use the same texture.
	//When textures are not correct, try to rerun the game or to add one or two more shaders.
	//Try to skip one shader per 2 shaders in that case
	//TODO: fix uniform system for shaders, so we can set textures on same shader.
	//TODO: Fix resources manager not always returning the already exisiting resource/shader
	zel_resource_id default_shader = zel_shader_load("shaders/default.vertex", "shaders/default.fragment");
	zel_resource_id default1_shader = zel_shader_load("shaders/default.vertex", "shaders/default.fragment");
	zel_resource_id default2_shader = zel_shader_load("shaders/default.vertex", "shaders/default.fragment");
	zel_resource_id default3_shader = zel_shader_load("shaders/default.vertex", "shaders/default.fragment");
	zel_material_t background_material = zel_material_create(default_shader);
	zel_material_t enemy_material = zel_material_create(default1_shader);
	zel_material_t enemy_shadow_material = zel_material_create(default2_shader);
	zel_material_t player_material = zel_material_create(default3_shader);
	zel_level_add_component<zel_material_t>(active_level, background_entity,	background_material);
	zel_level_add_component<zel_material_t>(active_level, enemy1_entity,		enemy_material);
	zel_level_add_component<zel_material_t>(active_level, enemy2_entity,		enemy_material);
	zel_level_add_component<zel_material_t>(active_level, enemy1_shadow_entity, enemy_shadow_material);
	zel_level_add_component<zel_material_t>(active_level, enemy2_shadow_entity, enemy_shadow_material);
	zel_level_add_component<zel_material_t>(active_level, player_entity,		player_material);
	zel_resources_unload(default_shader);
	zel_resources_unload(default1_shader);
	zel_resources_unload(default2_shader);
	zel_resources_unload(default3_shader);

	//Texture
	zel_texture_t background = zel_texture_load("textures/background.png");
	zel_material_set_texture(&background_material, "texture0", 0);
	zel_level_get_component<zel_transform_t>(active_level, background_entity)->scale.x *= background.width;
	zel_level_get_component<zel_transform_t>(active_level, background_entity)->scale.y *= background.height;

	zel_texture_t enemy_sprite = zel_texture_load("textures/enemy_sprite_top.png");
	zel_material_set_texture(&enemy_material, "texture0", 1);
	zel_level_get_component<zel_transform_t>(active_level, enemy1_entity)->scale.x *= enemy_sprite.width;
	zel_level_get_component<zel_transform_t>(active_level, enemy1_entity)->scale.y *= enemy_sprite.height;
	zel_level_get_component<zel_transform_t>(active_level, enemy2_entity)->scale.x *= enemy_sprite.width;
	zel_level_get_component<zel_transform_t>(active_level, enemy2_entity)->scale.y *= enemy_sprite.height;

	zel_texture_t enemy_shadow_sprite = zel_texture_load("textures/enemy_sprite_bottom.png");
	zel_material_set_texture(&enemy_shadow_material, "texture0", 2);
	zel_level_get_component<zel_transform_t>(active_level, enemy1_shadow_entity)->scale.x *= enemy_shadow_sprite.width;
	zel_level_get_component<zel_transform_t>(active_level, enemy1_shadow_entity)->scale.y *= enemy_shadow_sprite.height;
	zel_level_get_component<zel_transform_t>(active_level, enemy2_shadow_entity)->scale.x *= enemy_shadow_sprite.width;
	zel_level_get_component<zel_transform_t>(active_level, enemy2_shadow_entity)->scale.y *= enemy_shadow_sprite.height;

	zel_texture_t player_sprite = zel_texture_load("textures/player_sprite.png");
	zel_material_set_texture(&player_material, "texture0", 3);
	zel_level_get_component<zel_transform_t>(active_level, player_entity)->scale.x *= player_sprite.width;
	zel_level_get_component<zel_transform_t>(active_level, player_entity)->scale.y *= player_sprite.height;
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