﻿#include "Mesh.h"

namespace Graphics::MeshUtils {
    Mesh<VertexColor3D> CubeMesh(Vec3 origin, float x, float y, float z) {
        float hx = x / 2;
        float hy = y / 2;
        float hz = z / 2;
        VertexColor3D vertices[8] = {
            { origin + Maths::fvec3(-hx, -hy, -hz), { 0.0f, 0.0f, 0.0f, 1.0f } }, 
            { origin + Maths::fvec3(-hx, -hy, +hz), { 0.0f, 0.0f, 1.0f, 1.0f } }, 
            { origin + Maths::fvec3(-hx, +hy, -hz), { 0.0f, 1.0f, 0.0f, 1.0f } }, 
            { origin + Maths::fvec3(-hx, +hy, +hz), { 0.0f, 1.0f, 1.0f, 1.0f } }, 
            { origin + Maths::fvec3(+hx, -hy, -hz), { 1.0f, 0.0f, 0.0f, 1.0f } }, 
            { origin + Maths::fvec3(+hx, -hy, +hz), { 1.0f, 0.0f, 1.0f, 1.0f } }, 
            { origin + Maths::fvec3(+hx, +hy, -hz), { 1.0f, 1.0f, 0.0f, 1.0f } }, 
            { origin + Maths::fvec3(+hx, +hy, +hz), { 1.0f, 1.0f, 1.0f, 1.0f } }, 
        };
            
        return Mesh(
            std::vector(vertices, vertices + 8),
            std::vector<TriIndices>(
                { { 0, 1, 2 },
                  { 1, 2, 3 },
                  { 4, 5, 6 },
                  { 5, 6, 7 },
                  { 0, 1, 4 },
                  { 1, 4, 5 },
                  { 2, 3, 6 },
                  { 3, 6, 7 },
                  { 0, 2, 4 },
                  { 2, 4, 6 },
                  { 1, 3, 5 },
                  { 3, 5, 7 } }
            )
        );
    }
}
