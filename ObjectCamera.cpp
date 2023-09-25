#include "pch.h"
#include "ObjectCamera.h"

namespace ygl
{
    ObjectCamera::ObjectCamera()
    {
        matrixView = Matrix4x4(1.0f);
        matrixProj = Matrix4x4(1.0f);
    }

    ObjectCamera::~ObjectCamera()
    {

    }

    void ObjectCamera::UpdateViewMatrix()
    {

    }

    void ObjectCamera::UpdateProjMatrix()
    {

    }

    void ObjectCamera::UpdateUniformMatrix(int shaderProgramID)
    {
        unsigned int modelLocation;
        modelLocation = glGetUniformLocation(shaderProgramID, "ygl_mView");
        glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(matrixView));
        modelLocation = glGetUniformLocation(shaderProgramID, "ygl_mProj");
        glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(matrixProj));
    }
}