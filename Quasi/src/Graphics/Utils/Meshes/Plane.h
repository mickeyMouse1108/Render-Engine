#pragma once

#include "Mesh.h"
#include "MeshConstructor.h"

namespace Quasi::Graphics::MeshUtils {
    struct PlaneCreator;

    template <> struct OptionsFor<PlaneCreator> {};

    struct PlaneCreator : MeshConstructor<PlaneCreator> {
        using MData = VertexBuilder::MeshConstructData3D;
        PlaneCreator(Options) {}

        template <FnArgs<MData> F>
        auto CreateImpl(F&& f) -> Mesh<decltype(f(MData {}))> {
            using T = decltype(f(MData {}));
            Vec<T> vert;
            vert.reserve(4);
            vert.emplace_back(f(MData { .Position = { +1, 0, +1 }, .VertexIndex = 0 }));
            vert.emplace_back(f(MData { .Position = { +1, 0, -1 }, .VertexIndex = 1 }));
            vert.emplace_back(f(MData { .Position = { -1, 0, +1 }, .VertexIndex = 2 }));
            vert.emplace_back(f(MData { .Position = { -1, 0, -1 }, .VertexIndex = 3 }));

            return { std::move(vert), Vec<TriIndices> { { 0, 1, 2 }, { 1, 2, 3 } } };
        }
    };

    inline static MeshConstructor<PlaneCreator> Plane {};
} // Graphics::MeshUtils
