#include "menger.h"

namespace {
	const int kMinLevel = 0;
	const int kMaxLevel = 4;
};

Menger::Menger()
{
	// Add additional initialization if you like
}

Menger::~Menger()
{
}

void
Menger::set_nesting_level(int level)
{
	nesting_level_ = level;
	dirty_ = true;
}

bool
Menger::is_dirty() const
{
	return dirty_;
}

void
Menger::set_clean()
{
	dirty_ = false;
}

// FIXME generate Menger sponge geometry
void
Menger::generate_geometry(std::vector<glm::vec4>& obj_vertices,
			  			std::vector<glm::vec4>& vtx_normals,
                          std::vector<glm::uvec3>& obj_faces) const
{
	obj_vertices.clear();
	vtx_normals.clear();
	obj_faces.clear();
	if (nesting_level_ > 0) {
		generate_geometry_helper(obj_vertices, vtx_normals, obj_faces, -0.5f, -0.5f, -0.5f,
			1.0f / 3.0f, nesting_level_, 0);
	} else {
		draw_cube(obj_vertices, vtx_normals, obj_faces, -0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f)
	}
}

int
Menger::generate_geometry_helper(std::vector<glm::vec4>& obj_vertices,
			  std::vector<glm::vec4>& vtx_normals,
                          std::vector<glm::uvec3>& obj_faces,
                          float xmin, float ymin, float zmin, float length, int depth, int first) const {
	float x, y, z;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				if (i % 2 + j % 2 + k % 2 < 2) {
					x = xmin + (float)i * length;
					y = ymin + (float)j * length;
					z = zmin + (float)k * length;
					if (depth > 1) {
						first = generate_geometry_helper(obj_vertices, vtx_normals, obj_faces,
                       x, y, z, length / 3.0f, depth - 1, start);
					} else {
						draw_cube(obj_vertices, vtx_normals, obj_faces,
                       		x, y, z, x + length, y + length, z + length, first);
						first = first + 36;
					}
				}
			}
		}
	}
	return first;
}


void
Menger::draw_cube(std::vector<glm::vec4>& obj_vertices,
			  		std::vector<glm::vec4>& vtx_normals,
                    std::vector<glm::uvec3>& obj_faces,
                    float xmin, float ymin, float zmin, float xmax, float ymax, float zmax, int first) const {
	obj_vertices.push_back(glm::vec4(xmin, ymin, zmax, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
	obj_vertices.push_back(glm::vec4(xmax, ymin, zmax, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
	obj_vertices.push_back(glm::vec4(xmax, ymax, zmax, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
	obj_faces.push_back(glm::uvec3(start, start + 1, start + 2));

	obj_vertices.push_back(glm::vec4(xmin, ymin, zmax, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
	obj_vertices.push_back(glm::vec4(xmax, ymax, zmax, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
	obj_vertices.push_back(glm::vec4(xmin, ymax, zmax, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
	obj_faces.push_back(glm::uvec3(start + 3, start + 4, start + 5));

	obj_vertices.push_back(glm::vec4(xmin, ymin, zmax, 1.0f));
	vtx_normals.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
	obj_vertices.push_back(glm::vec4(xmin, ymin, zmin, 1.0f));
	vtx_normals.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
	obj_vertices.push_back(glm::vec4(xmin, ymax, zmax, 1.0f));
	vtx_normals.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
	obj_faces.push_back(glm::uvec3(start + 6, start + 7, start + 8));

	obj_vertices.push_back(glm::vec4(xmin, ymax, zmax, 1.0f));
	vtx_normals.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
	obj_vertices.push_back(glm::vec4(xmin, ymin, zmin, 1.0f));
	vtx_normals.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
	obj_vertices.push_back(glm::vec4(xmin, ymax, zmin, 1.0f));
	vtx_normals.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
	obj_faces.push_back(glm::uvec3(start + 9, start + 10, start + 11));

	obj_vertices.push_back(glm::vec4(xmin, ymin, zmin, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
	obj_vertices.push_back(glm::vec4(xmax, ymin, zmin, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
	obj_vertices.push_back(glm::vec4(xmax, ymax, zmin, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
	obj_faces.push_back(glm::uvec3(start + 12, start + 13, start + 14));

	obj_vertices.push_back(glm::vec4(xmin, ymin, zmin, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
	obj_vertices.push_back(glm::vec4(xmax, ymax, zmin, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
	obj_vertices.push_back(glm::vec4(xmin, ymax, zmin, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
	obj_faces.push_back(glm::uvec3(start + 15, start + 16, start + 17));

	obj_vertices.push_back(glm::vec4(xmax, ymin, zmax, 1.0f));
	vtx_normals.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
	obj_vertices.push_back(glm::vec4(xmax, ymin, zmin, 1.0f));
	vtx_normals.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
	obj_vertices.push_back(glm::vec4(xmax, ymax, zmax, 1.0f));
	vtx_normals.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
	obj_faces.push_back(glm::uvec3(start + 18, start + 19, start + 20));

	obj_vertices.push_back(glm::vec4(xmax, ymax, zmax, 1.0f));
	vtx_normals.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
	obj_vertices.push_back(glm::vec4(xmax, ymin, zmin, 1.0f));
	vtx_normals.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
	obj_vertices.push_back(glm::vec4(xmax, ymax, zmin, 1.0f));
	vtx_normals.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
	obj_faces.push_back(glm::uvec3(start + 21, start + 22, start + 23));

	obj_vertices.push_back(glm::vec4(xmin, ymax, zmax, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
	obj_vertices.push_back(glm::vec4(xmax, ymax, zmax, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
	obj_vertices.push_back(glm::vec4(xmax, ymax, zmin, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
	obj_faces.push_back(glm::uvec3(start + 24, start + 25, start + 26));

	obj_vertices.push_back(glm::vec4(xmin, ymax, zmax, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
	obj_vertices.push_back(glm::vec4(xmin, ymax, zmin, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
	obj_vertices.push_back(glm::vec4(xmax, ymax, zmin, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
	obj_faces.push_back(glm::uvec3(start + 27, start + 28, start + 29));

	obj_vertices.push_back(glm::vec4(xmin, ymin, zmax, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
	obj_vertices.push_back(glm::vec4(xmax, ymin, zmax, 1.0f));//
	vtx_normals.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
	obj_vertices.push_back(glm::vec4(xmax, ymin, zmin, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
	obj_faces.push_back(glm::uvec3(start + 30, start + 31, start + 32));

	obj_vertices.push_back(glm::vec4(xmin, ymin, zmax, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
	obj_vertices.push_back(glm::vec4(xmin, ymin, zmin, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
	obj_vertices.push_back(glm::vec4(xmax, ymin, zmin, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
	obj_faces.push_back(glm::uvec3(start + 33, start + 34, start + 35));
}
	