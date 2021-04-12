#pragma once
#include <zel_mesh.h>
#include <glad\glad.h>

//#TODO: Create a zel_mesh_t out of these buffers (is needed for deletion of mesh)
// Also add destroy function(s) to free the memory of the mesh
// Create Vertex Attributes API in another dedicated file

uint32_t zel_vertexbuffer_create(float* vertices_data, uint32_t vertices_size)
{
	uint32_t VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices_data, GL_STATIC_DRAW);

	//#TODO: replace this with an API to set vertex attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	return VBO;
}

uint32_t zel_indexbuffer_create(uint32_t* indices_data, uint32_t indices_size)
{
	uint32_t EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size, indices_data, GL_STATIC_DRAW);

	return EBO;
}

uint32_t zel_mesh_create(float* vertices_data, uint32_t vertices_size, uint32_t* indices_data, uint32_t indices_size)
{
	uint32_t VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	zel_vertexbuffer_create(vertices_data, vertices_size);
	zel_indexbuffer_create(indices_data, indices_size);

	glBindVertexArray(0);

	return VAO;
}

void zel_mesh_bind(zel_mesh_t* mesh)
{
	glBindVertexArray(mesh->VAO);
}