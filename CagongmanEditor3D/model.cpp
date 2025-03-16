#include "model.h"
#include <QOpenGLBuffer>
#include <QDebug>

Model::Model(const std::string& path) {
    initializeOpenGLFunctions();
    LoadModel(path);
}

Model::~Model() {
}

void Model::LoadModel(const std::string& path) {
}

void Model::Draw() {
}