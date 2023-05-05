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

/**
 * @brief Constructs a VertexBuffer object.
 * @details Generates a buffer object name.
 * mRendererID is the renderer in our case is openGL.
 */
VertexBuffer::VertexBuffer() {
    mRendererID = 0;
    glGenBuffers(1, &mRendererID);
}

/**
 * @brief Copies data to the buffer.
 * @param data pointer to the first element of the array
 * @param size size of the array in bytes
 */
void VertexBuffer::SetData(const void *data, unsigned int size) {
    glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

/**
 * @brief Binds the buffer.
 * @details Binds the buffer to the GL_ARRAY_BUFFER target.
 */
void VertexBuffer::Bind() const {
    // we us bind buffer so that open
    // if we don't bind the buffer, openGL will not know which buffer to use and
    glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
}
