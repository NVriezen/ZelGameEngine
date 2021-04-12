#pragma once
#include <zel_base.h>
#include <zel_component_builtin.h>

uint32_t zel_vertexbuffer_create(float* vertices_data, uint32_t vertices_size);
uint32_t zel_indexbuffer_create(uint32_t* indices_data, uint32_t indices_size);
uint32_t zel_mesh_create(float* vertices_data, uint32_t vertices_size, uint32_t* indices_data, uint32_t indices_size);
void zel_mesh_bind(zel_mesh_t* mesh)
{

}