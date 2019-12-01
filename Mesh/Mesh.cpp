#include "Mesh.hpp" 

Mesh::Mesh(Geometry* geo , Material* mat){
    material = new Material();
    *material = *mat;
    geometry = geo;
}

void Mesh::setScale(glm::vec3 vec){
   scale = vec;
   updateMatrix();
}

glm::vec3 * Mesh::getScale(){
    return &scale;
}

void Mesh::setPosition(glm::vec3 vec){
    position = vec;
    updateMatrix();
}

glm::vec3 * Mesh::getPosition(){
    return &position;
}

void Mesh::setRotation(glm::vec3 vec){
    rotation = vec;
    updateMatrix();
}

glm::vec3* Mesh::getRotation(){
    return &rotation;
}

glm::mat4 Mesh::getLocalMatrix(){
    return localMatrix;
}

void Mesh::setLocalMatrix(glm::mat4 mat){
    localMatrix = mat;
}

glm::mat4 Mesh::getWorldMatrix(){
    return worldMatrix;
}

void Mesh::setWorldMatrix(glm::mat4 mat){
    worldMatrix = mat;
}

void Mesh::add(Mesh* child){
    children.push_back(child);    
    child->setWorldMatrix(localMatrix);
    child->setParent(this);
}

void Mesh::updateMatrix(){
    glm::mat4 translateMat = glm::translate(glm::mat4(1.0f) , position);
    glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f) , scale);
    glm::mat4 rotateX = glm::rotate(glm::mat4(1.0f) , rotation.x, glm::vec3(1.0f,.0f,.0f));
    glm::mat4 rotateY = glm::rotate(glm::mat4(1.0f) , rotation.y, glm::vec3(.0f,1.0f,.0f));
    glm::mat4 rotateZ = glm::rotate(glm::mat4(1.0f) , rotation.z, glm::vec3(.0f,.0f,1.0f));
    localMatrix = translateMat * rotateX  * rotateY * rotateZ * scaleMat;
    
    for(int i= 0; i<children.size(); i++){
        children[i]->setWorldMatrix(localMatrix);        
        //std::cout<< glm::to_string(children[i]->getWorldMatrix()) << std::endl;
    }
}

std::vector<Mesh*> Mesh::getChildren(){
    return children;
}

void Mesh::setParent(Mesh* parent){
    this->parent = parent;
}

Mesh* Mesh::getParent(){
    return parent;
} 

Geometry* Mesh::getGeometry(){
    return geometry;
}

Material* Mesh::getMaterial(){
    return material;
}

void Mesh::render(Shader* shader){
        shader->setMat4("worldMatrix", worldMatrix);
        shader->setMat4("localMatrix", localMatrix);
        shader->setBool("isTextured", geometry->isTextured());
        material->sendToShader(shader);


        if (geometry->isTextured())
        {

            glBindBuffer(GL_ARRAY_BUFFER, *geometry->getVbo());
            glVertexAttribPointer(0,                 // attribute 0 matches aPos in Vertex Shader
                                  3,                 // size
                                  GL_FLOAT,          // type
                                  GL_FALSE,          // normalized?
                                  8 * sizeof(float), // stride - each vertex contain 2 vec3 (position, color)
                                  (void *)0          // array buffer offset
            );
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1,                          // attribute 0 matches aPos in Vertex Shader
                                  3,                          // size
                                  GL_FLOAT,                   // type
                                  GL_FALSE,                   // normalized?
                                  8 * sizeof(float),          // stride - each vertex contain 2 vec3 (position, color)
                                  (void *)(3 * sizeof(float)) // array buffer offset
            );
            glEnableVertexAttribArray(1);

            glBindTexture(GL_TEXTURE_2D, *geometry->getTexture());

            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
            glEnableVertexAttribArray(2);

            if (geometry->isIndexed())
            {
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *geometry->getEbo());
                glDrawElements(geometry->getDrawEnum(), geometry->getIndecies()->size(), GL_UNSIGNED_INT, 0);
            }
            else
            {
                glDrawArrays(geometry->getDrawEnum(), 0, geometry->getVertices()->size() / 8);
            }
        }
        else
        {
            glBindBuffer(GL_ARRAY_BUFFER, *geometry->getVbo());
            glVertexAttribPointer(0,                 // attribute 0 matches aPos in Vertex Shader
                                  3,                 // size
                                  GL_FLOAT,          // type
                                  GL_FALSE,          // normalized?
                                  6 * sizeof(float), // stride - each vertex contain 2 vec3 (position, color)
                                  (void *)0          // array buffer offset
            );
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1,                          // attribute 0 matches aPos in Vertex Shader
                                  3,                          // size
                                  GL_FLOAT,                   // type
                                  GL_FALSE,                   // normalized?
                                  6 * sizeof(float),          // stride - each vertex contain 2 vec3 (position, color)
                                  (void *)(3 * sizeof(float)) // array buffer offset
            );
            glEnableVertexAttribArray(1);

            if (geometry->isIndexed())
            {
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *geometry->getEbo());
                glDrawElements(geometry->getDrawEnum(), geometry->getIndecies()->size(), GL_UNSIGNED_INT, 0);
            }
            else
            {
                glDrawArrays(geometry->getDrawEnum(), 0, geometry->getVertices()->size() / 6);
            }
        }
}