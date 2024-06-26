#include "TestLightCasters.h"

#include "imgui.h"
#include "lambdas.h"
#include "ModelLoading/OBJModelLoader.h"
#include "Meshes/CubeNormless.h"

namespace Test {
    void TestLightCasters::OnInit(Graphics::GraphicsDevice& gdevice) {
        scene = gdevice.CreateNewRender<Vertex>();
        lightScene = gdevice.CreateNewRender<Graphics::VertexColor3D>();

        Graphics::OBJModelLoader mloader;
        mloader.LoadFile(res("lights.obj"));
        Graphics::OBJModel model = mloader.RetrieveModel();

        materials = std::move(model.materials);
        meshes.reserve(model.objects.size());
        for (const Graphics::OBJObject& obj : model.objects) {
            meshes.emplace_back(
                obj.mesh.Convert<Vertex>(
                    LAMB(const Graphics::OBJVertex& v, (Vertex { v.Position, v.Normal, obj.materialIndex })
            )));
        }
        scene.BindMeshes(meshes);

        scene.UseShaderFromFile(res("shader.vert"), res("shader.frag"));
        scene.SetProjection(Math::Matrix3D::perspective_fov(90.0f, gdevice.GetAspectRatio(), 0.01f, 100.0f));

        camera.position = { 10.506737, 11.603662, 6.2335258 };
        camera.yaw = -3.6930802f; camera.pitch = -0.64090014f;
        camera.speed = 5;
        camera.sensitivity = 0.12f;
        camera.fov = 90;
        camera.fovRange = { 1, 90 };
        camera.zoomRatio = 0.5f;
        camera.smoothZoom = 120;

        lights.reserve(MAX_LIGHTS);
        AddPointLight({
            .position = { -0, 7, 0 },
            .constant = 1,
            .linear = 0,
            .quadratic = 0
        }, { 1, 1, 1 });

        AddPointLight({
            .position = { 12, 3, -14 },
            .constant = 1,
            .linear = 0,
            .quadratic = 0.001f,
         }, { 1, 0, 0 });

        AddPointLight({
            .position = { -9, 3, 6 },
            .constant = 1,
            .linear = 0,
            .quadratic = 0.001f,
         }, { 0, 0.6176472f, 1 });

        AddPointLight({
            .position = { 12, 3, 16 },
            .constant = 1,
            .linear = 0,
            .quadratic = 0.001f,
         }, { 0.2647059f, 1, 0 });

        lightScene.UseShader(Graphics::Shader::StdColored);
    }

    void TestLightCasters::OnUpdate(Graphics::GraphicsDevice& gdevice, float deltaTime) {
        camera.Update(gdevice, deltaTime);
    }

    void TestLightCasters::OnRender(Graphics::GraphicsDevice& gdevice) {
        lightScene.SetProjection(camera.GetProjMat());
        lightScene.SetCamera(camera.GetViewMat());
        lightScene.ResetData();
        lightScene.Render();

        scene->shader.Bind();
        for (u32 i = 0; i < materials.size(); ++i) {
            UniformMaterial(std::format("materials[{}]", i), materials[i]);
        }

        for (u32 i = 0; i < lights.size(); ++i) {
            UniformLight(std::format("lights[{}]", i), lights[i]);
        }

        scene.SetProjection(camera.GetProjMat());
        scene.SetCamera(camera.GetViewMat());
        scene.ResetData();
        scene.Render({
            { "ambientStrength",   ambientStrength },
            { "viewPosition",      camera.position },
            { "specularIntensity", specularStrength },
        });
    }

    void TestLightCasters::OnImGuiRender(Graphics::GraphicsDevice& gdevice) {
        ImGui::DragFloat("Ambient Strength", &ambientStrength, 0.01f);
        ImGui::DragFloat("Specular Strength", &specularStrength, 0.01f);

        camera.ImGuiEdit();

        if (ImGui::TreeNode("Lights")) {
            if (ImGui::Button("+") && lights.size() < MAX_LIGHTS) {
                AddPointLight({
                    .position = 0,
                    .constant = 1, .linear = 0, .quadratic = 0
                }, 1);
            }
            ImGui::SameLine();
            if (ImGui::Button("-") && !lights.empty()) {
                lights.pop_back();
            }

            for (u32 i = 0; i < lights.size(); ++i) {
                lights[i].ImGuiEdit(std::format("Light {}", i + 1).c_str());
                lightMeshes[i].ApplyMaterial(&Graphics::VertexColor3D::Color, lights[i].color);
                lightMeshes[i].SetTransform(Math::Matrix3D::translate_mat(lights[i].Position()));
            }
            ImGui::TreePop();
        }
    }

    void TestLightCasters::OnDestroy(Graphics::GraphicsDevice& gdevice) {
        scene.Destroy();
        lightScene.Destroy();
    }

    void TestLightCasters::UniformMaterial(const std::string& name, const Graphics::MTLMaterial& material) {
        Graphics::Shader& shader = scene->shader;
        shader.SetUniformArgs({
            { name + ".ambient",   material.Ka },
            { name + ".diffuse",   material.Kd },
            { name + ".specular",  material.Ks },
            { name + ".shininess", material.Ns },
        });
    }

    void TestLightCasters::UniformLight(const std::string& name, const Graphics::Light& light) {
        Graphics::Shader& shader = scene->shader;
        Math::fVector3 top, bottom;
        light.Visit(
            [&] (const Graphics::SunLight& sun) { top = sun.direction; },
            [&] (const Graphics::PointLight& point) {
                top = point.position;
                bottom = { point.constant, point.linear, point.quadratic };
            },
            [&] (const Graphics::FlashLight& flash) {
                top = flash.position;
                bottom = { flash.yaw, flash.pitch, flash.innerCut };
            }
        );
        shader.SetUniformArgs({
            { name + ".lightId", (int)light.ID() + 1 },
            { name + ".d1", top },
            { name + ".d2", bottom },
            { name + ".d3", light.Is<Graphics::FlashLight>() ? light.As<Graphics::FlashLight>()->outerCut : 0 },
            { name + ".color", light.color },
        });
    }

    void TestLightCasters::AddPointLight(const Graphics::PointLight& point, const Math::fColor& color) {
        lights.emplace_back();
        lights.back() = { point };
        lights.back().color = color;

        using namespace Graphics::VertexBuilder;
        lightMeshes.emplace_back(
            Graphics::MeshUtils::CubeNormless(Graphics::VertexColor3D::Blueprint {
                .Position = GetPosition {},
                .Color = Constant { color }
            })
        );
        lightMeshes.back().SetTransform(Math::Matrix3D::translate_mat(point.position));
        lightMeshes.back().Bind(lightScene);
    }
}
