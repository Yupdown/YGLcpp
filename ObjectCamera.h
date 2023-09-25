#pragma once
#include "pch.h"
#include "Object.h"

namespace ygl
{
	class ObjectCamera : public Object
	{
	private:
		Matrix4x4 matrixView;
		Matrix4x4 matrixProj;

	public:
		ObjectCamera();
		~ObjectCamera() override;

	public:
		virtual void UpdateViewMatrix();
		virtual void UpdateProjMatrix();
		void UpdateUniformMatrix(int shaderProgramID);
	};
}