﻿#include "VertexArray.h"

#include "../Debugging.h"

namespace Graphics {
    VertexArray::VertexArray() {
        GLCALL(glGenVertexArrays(1, &rendererID));
    }

    VertexArray::~VertexArray() {
        GLCALL(glDeleteVertexArrays(1, &rendererID));
    }

    void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {
        Bind();
        vb.Bind();
        const std::vector<VertexBufferElement>& elements = layout.GetElements();
        uint offset = 0;
        for (uint i = 0; i < elements.size(); i++)
        {
            const auto& elem = elements[i];
            GLCALL(glEnableVertexAttribArray(i));
            GLCALL(glVertexAttribPointer(i, elem.count, elem.type, elem.normalized, layout.GetStride(), (const void*)offset));  // NOLINT(performance-no-int-to-ptr)
            offset += elem.count * VertexBufferElement::sizeofType(elem.type);
        }
    }

    template <>
    void VertexArray::AddBuffer(VBO<float> vb) {
        Bind();
        vb.Bind();
        
        GLCALL(glEnableVertexAttribArray(0));
        GLCALL(glVertexAttribPointer(0, 1, GL_FLOAT, GL_FALSE, sizeof(float), nullptr));
    }

    template <>
    void VertexArray::AddBuffer(VBO<VertexColorTexture3D> vb) {
        Bind();
        vb.Bind();

        typedef VertexColorTexture3D Vertex;
        
        GLCALL(glEnableVertexAttribArray(0));
        GLCALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Position)));
        
        GLCALL(glEnableVertexAttribArray(1));
        GLCALL(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Color)));
        
        GLCALL(glEnableVertexAttribArray(2));
        GLCALL(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, TextureCoordinate)));
        
        GLCALL(glEnableVertexAttribArray(3));
        GLCALL(glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, TextureID)));
    }

    template <>
    void VertexArray::AddBuffer(VBO<VertexColorTextureAtlas3D> vb) {
        Bind();
        vb.Bind();

        typedef VertexColorTextureAtlas3D Vertex;
        
        GLCALL(glEnableVertexAttribArray(0));
        GLCALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Position)));
        
        GLCALL(glEnableVertexAttribArray(1));
        GLCALL(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Color)));
        
        GLCALL(glEnableVertexAttribArray(2));
        GLCALL(glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, TextureAtlID)));

        GLCALL(glEnableVertexAttribArray(3));
        GLCALL(glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, TextureCorner)));
    }

    template <>
    void VertexArray::AddBuffer(VBO<VertexColor3D> vb) {
        Bind();
        vb.Bind();

        typedef VertexColor3D Vertex;
        
        GLCALL(glEnableVertexAttribArray(0));
        GLCALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Position)));

        GLCALL(glEnableVertexAttribArray(1));
        GLCALL(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Color)));
    }

    void VertexArray::Bind() const {
        GLCALL(glBindVertexArray(rendererID));
    }

    void VertexArray::Unbind() const {
        GLCALL(glBindVertexArray(0));
    }
}
