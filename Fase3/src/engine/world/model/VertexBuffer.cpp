//
// Created by Sandro Duarte on 18/03/2023.
//

#include "world/model/VertexBuffer.h"


#ifdef __APPLE__
#include <glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

VertexBuffer::VertexBuffer() {
    mRendererID = 0;
    glGenBuffers(1, &mRendererID);
}

/**
 * Copies data to buffer.
 * @param data
 * @param size in bytes
 */
void VertexBuffer::SetData(const void *data, unsigned int size) {
    glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

/**
 * Binds buffer for use.
 */
void VertexBuffer::Bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
}
