//
// Created by Sandro Duarte on 18/03/2023.
//

#ifndef ENGINE_VERTEXBUFFER_H
#define ENGINE_VERTEXBUFFER_H

/**
 * Vertex Buffer class that abstracts vbo.
 */
class VertexBuffer {
public:
    VertexBuffer();
    virtual ~VertexBuffer() = default;

    /**
     * Copies data to buffer.
     * @param data
     * @param size in bytes
    */
    void SetData(const void *data, unsigned int size);

    /**
     * Binds buffer for use.
    */
    void Bind() const;
private:

    unsigned int mRendererID;
};


#endif //ENGINE_VERTEXBUFFER_H
