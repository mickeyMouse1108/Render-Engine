#pragma once
#include "NumTypes.h"
#include <utility>
#include <core.h>
#include <span>

namespace Graphics {
	template <class T> class Mesh;

	class GenericMesh {
		// used so that 'singlebyte' is a custom defined type, unlike char
		struct singlebyte { char _; };
		Mesh<singlebyte>* ptr; // using the fact that mesh<T> is always 104 bytes
	public:
		GenericMesh(void* m) : ptr((Mesh<singlebyte>*)m) {}
		OPENGL_API ~GenericMesh();

		GenericMesh(const GenericMesh&) = delete;
		GenericMesh& operator=(const GenericMesh&) = delete;

		OPENGL_API static void Transfer(GenericMesh& dest, GenericMesh&& from);
		GenericMesh(GenericMesh&& mesh) noexcept { Transfer(*this, std::move(mesh)); }
		GenericMesh& operator=(GenericMesh&& mesh) noexcept { Transfer(*this, std::move(mesh)); return *this; }

		template <class T> static GenericMesh From(Mesh<T>* m) {
			return GenericMesh { (Mesh<singlebyte>*)m };
		}

		template <class T> Mesh<T>& As() {
			return *reinterpret_cast<Mesh<T>*>(ptr);
		}

		template <class T> const Mesh<T>& As() const {
			return *reinterpret_cast<const Mesh<T>*>(ptr);
		}

		OPENGL_API void Set(void* mesh);
		template <class T> void Set(Mesh<T>* mesh) {
			Set((void*)mesh);
		}

		OPENGL_API uint& deviceIndex();
		[[nodiscard]] OPENGL_API uint deviceIndex() const;

		[[nodiscard]] OPENGL_API usize vSizeBytes() const;
		[[nodiscard]] OPENGL_API std::span<const byte> vDataBytes() const;
		[[nodiscard]] OPENGL_API usize iSize() const;
	};
}
