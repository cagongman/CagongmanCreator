#pragma once

#ifndef OBJECT_H
#define OBJECT_H

#include <QVector3D>
#include <vector>

class Object {
public:
	void setVertices(std::vector<float>&& data);
	const float* getVertexBuffer() const;
	size_t getVertexCount() const;
	QVector3D getGeometricCenter() const;

private:
	QVector3D m_center;
	std::vector<float> m_vertices;
};

#endif // OBJECT_H