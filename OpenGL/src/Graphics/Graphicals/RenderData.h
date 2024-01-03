#pragma once
#include "VertexArray.h"
#include "DynamicVertexBuffer.h"
#include "DynamicIndexBuffer.h"
#include "GenericMesh.h"

namespace Graphics {
	class GraphicsDevice;

	class RenderData {
		VertexArray varray;
		DynamicVertexBuffer vbo;
		DynamicIndexBuffer ibo;

		std::vector<GenericMesh> meshes {};

		GraphicsDevice* device = nullptr;
		uint deviceIndex = 0;
		friend GraphicsDevice;
	public:
		RenderData(uint vsize, uint isize, uint vertSize,
				   std::type_index vertType, const VertexBufferLayout& layout) :
			varray(), vbo(vsize, vertSize, vertType), ibo(isize) {
			varray.Bind();
			varray.AddBuffer(layout);
		}

		RenderData(const RenderData&) = delete;
		RenderData& operator=(const RenderData&) = delete;

		static void Transfer(RenderData& dest, RenderData&& from);
		RenderData(RenderData&& rd) noexcept { Transfer(*this, std::move(rd)); }
		RenderData& operator=(RenderData&& rd) noexcept { Transfer(*this, std::move(rd)); return *this; }

		~RenderData();

		template <class T> static RenderData Create(uint vsize, uint isize);

		OPENGL_API void Bind() const;
		OPENGL_API void Unbind() const;

		[[nodiscard]] std::type_index GetType() const { return vbo.GetType(); }

		template <class T> void SetVert(const T* data, uint count) { vbo.SetData(data, count); }
		template <class T> void SetVert(const T& arr)              { vbo.SetData(arr); }
		template <class T> void AddVert(const T* data, uint count) { vbo.AddData(data, count); }
		template <class T> void AddVert(const T& arr)              { vbo.AddData(arr); }
		void ClearVert(bool shallowClear = true) { vbo.ClearData(shallowClear); }
		[[nodiscard]] uint GetVertLength() const { return vbo.GetLength(); }

		template <class T> void SetInd(const T* data, uint count) { ibo.SetData(data, count); }
		template <class T> void SetInd(const T& arr)              { ibo.SetData(arr); }
		template <class T> void AddInd(const T* data, uint count) { ibo.AddData(data, count); }
		template <class T> void AddInd(const T& arr)              { ibo.AddData(arr); }
		void ClearInd(bool shallowClear = true) { ibo.ClearData(shallowClear); }
		[[nodiscard]] uint GetIndLength() const { return ibo.GetLength(); }

		DynamicVertexBuffer& GetVertObj() { return vbo; }
		[[nodiscard]] const DynamicVertexBuffer& GetVertObj() const { return vbo; }
		DynamicIndexBuffer& GetIndObj() { return ibo; }
		[[nodiscard]] const DynamicIndexBuffer& GetIndObj() const { return ibo; }
		VertexArray& GetVertArr() { return varray; }
		[[nodiscard]] const VertexArray& GetVertArr() const { return varray; }
		GraphicsDevice& GetGraphicsDevice() { return *device; }
		[[nodiscard]] const GraphicsDevice& GetGraphicsDevice() const { return *device; }
		std::vector<GenericMesh>& GetMeshes() { return meshes; }
		[[nodiscard]] const std::vector<GenericMesh>& GetMeshes() const { return meshes; }

		OPENGL_API void ClearData(bool shallowClear = true);
		template <class T> void BindMeshes(Mesh<T>* meshes, uint count);
		template <class T> void BindMeshes(T& ms) { BindMeshes(ms.begin(), (uint)ms.size()); }
		OPENGL_API void Render();
		template <class T> void AddNewMeshes(const Mesh<T>* meshes, uint count);
		template <class T> void AddNewMeshes(const T& arr) { AddNewMeshes(arr.begin(), (uint)arr.size()); }
		template <class T> void AddBoundMeshes() { AddNewMeshes(&meshes.begin()->As<T>(), (uint)meshes.size()); }
		template <class T> void ResetData(bool shallowClear = true) { ClearData(shallowClear); AddBoundMeshes<T>(); }
		OPENGL_API void UnbindMesh(int index);
		OPENGL_API void UnbindMeshes(int indexStart, int indexEnd);
		OPENGL_API void UpdateMeshIndicies();
		OPENGL_API void Destroy();
	};

	template <class T>
	RenderData RenderData::Create(uint vsize, uint isize) {
		// times 3 to account for triangles
		return RenderData(vsize, isize * 3, sizeof(T), typeid(T), VERTEX_LAYOUT_OF(T));
	}

	template <class T>
	void RenderData::BindMeshes(Mesh<T>* meshes, uint count) {
		for (uint i = 0; i < count; ++i) {
			meshes[i].Bind(*this);
		}
	}

	template<class T>
	void RenderData::AddNewMeshes(const Mesh<T>* meshes, uint count) {
		for (uint i = 0; i < count; ++i)
			meshes[i].AddTo(vbo, ibo);
	}
}