#pragma once
#include <zel_base.h>
#include <zel_ecs.h>
#include <zel_level.h>
#include <zel_component_builtin.h>
#include <zel_profiling_timer.h>
#include <zel_math.h>
#include <zel_material.h>
#include <zel_mesh.h>
#include <zel_entity_collection.h>

const char* zel_renderer_general_name = "general_renderer";

void zel_renderer_general_update(zel_level_t* level, float delta_time)
{
	PROFILE_FUNCTION();

	//for (zel_entity_id entity : zel_entities_list<zel_transform_t>(level))
	//{
	//	zel_level_get_component<zel_transform_t>(level, entity)->position.x += 1;

	//	float biggest_value = -FLT_MAX;
	//	uint32_t biggest_index = render_entities.size();
	//	for (int32_t array_indexer = render_entities.size() - 1; array_indexer >= 0; --array_indexer)
	//	{
	//		for (size_t i = 0; i <= array_indexer; i++)
	//		{
	//			float z_value = transform_entities[render_entities[i].transform_id].position.z;
	//			if (z_value >= biggest_value)
	//			{
	//				biggest_value = z_value;
	//				biggest_index = i;
	//			}
	//		}

	//		render_entity entity_biggest = render_entities[biggest_index];
	//		render_entities[biggest_index] = render_entities[array_indexer];
	//		render_entities[array_indexer] = entity_biggest;

	//		biggest_value = -FLT_MAX;
	//		biggest_index = array_indexer;
	//	}
	//}

	std::vector<zel_entity_id> entity1_collection = zel_entity_collection_create_single<zel_camera_t>(level);
	for (size_t collection_index = 0; collection_index < entity1_collection.size(); collection_index++)
	{
		zel_entity_id camera_entity = entity1_collection[collection_index];
		zel_camera_t* camera = zel_level_get_component<zel_camera_t>(level, camera_entity);
		zel_framebuffer_bind(camera->framebuffer_id);
		zel_set_viewport(0, 0, game_resolution_x, game_resolution_y);
		zel_clear_screen(0.03f, 0.07f, 0.21f, 1.0f);
		zel_clear_depth();

		std::vector<zel_entity_id> entity_collection = zel_entity_collection_create<zel_transform_t, zel_material_t, zel_mesh_t>(level);
		for (size_t collection_index = 0; collection_index < entity_collection.size(); collection_index++)
		{
			zel_entity_id entity = entity_collection[collection_index];

			zel_transform_t* transform_of_entity = zel_level_get_component<zel_transform_t>(level, entity);
			glm::vec3 position = glm::vec3(
				transform_of_entity->position.x,
				transform_of_entity->position.y,
				transform_of_entity->position.z
			);
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, position);

			model = glm::rotate(model, glm::radians(transform_of_entity->rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::rotate(model, glm::radians(transform_of_entity->rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::rotate(model, glm::radians(transform_of_entity->rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::scale(model, glm::vec3(
				glm::floor(transform_of_entity->scale.x),
				glm::floor(transform_of_entity->scale.y),
				glm::floor(transform_of_entity->scale.z)
			));

			zel_material_t* material_of_entity = zel_level_get_component<zel_material_t>(level, entity);
			zel_material_set_camera_uniforms(material_of_entity, camera->view, camera->projection);
			zel_material_set_model(material_of_entity, model);

			zel_mesh_t* mesh = zel_level_get_component<zel_mesh_t>(level, entity);
			zel_mesh_bind(mesh);

			zel_render_elements(0x0004/*GL_TRIANGLES*/, 6, 0x1405/*GL_UNSIGNED_INT*/, 0);
		}
	}
}
