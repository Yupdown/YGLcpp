#pragma once
#include "pch.h"

namespace ygl
{
	class Object
	{
	protected:
		Vector3		position;
		Quaternion	rotation;
		Vector3		scale;

		Matrix4x4	matrixTRSLocal;
		Matrix4x4	matrixTRSWorld;

		bool matrixDirty;

		Object* parentObject;
		std::vector<Object*> childObjects;

	public:
		Object();
		virtual ~Object();

	public:
		void UpdateMatrix();
		void Redraw();

		void AddChild(Object* obj);
		bool RemoveChild(Object* obj);
		void RemoveFromParent();
		
	public:
		Vector3		GetPosition() const;
		Quaternion	GetRotation() const;
		Vector3		GetScale() const;

	public:
		void SetPosition(const Vector3& v);
		void SetRotation(const Quaternion& v);
		void SetScale(const Vector3& v);

	protected:
		virtual void OnRedraw();
	};
}