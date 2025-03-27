#include "Object.h"

void Object::setVertices(const std::vector<float>& data) {
    m_vertices = std::move(data);
}

const float* Object::getVertexBuffer() const {
    return m_vertices.data();
}

size_t Object::getVertexCount() const {
    return m_vertices.size() / 3;  // x, y, z
}

QVector3D Object::getGeometricCenter() const {

}