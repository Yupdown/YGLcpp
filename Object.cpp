#include "pch.h"
#include "Object.h"

namespace ygl
{
	Object::Object()
	{
		position = Vector3(0.0f, 0.0f, 0.0f);
		rotation = Quaternion(1.0f, 0.0f, 0.0f, 0.0f);
		scale = Vector3(1.0f, 1.0f, 1.0f);

		matrixTRSLocal = Matrix4x4(1.0f);
		matrixTRSWorld = Matrix4x4(1.0f);

		matrixDirty = true;

		parentObject = nullptr;
	}

	Object::~Object()
	{

	}

	void Object::ValidateMatrix()
	{
		Matrix4x4 matrixT = glm::translate(Matrix4x4(1.0f), position);
		Matrix4x4 matrixR = glm::mat4_cast(rotation);
		Matrix4x4 matrixS = glm::scale(Matrix4x4(1.0f), scale);
		matrixTRSLocal = matrixT * matrixR * matrixS;
		
		if (parentObject != nullptr)
			matrixTRSWorld = parentObject->matrixTRSWorld * matrixTRSLocal;
		else
			matrixTRSWorld = matrixTRSLocal;

		matrixDirty = false;
	}

	void Object::Redraw(bool forceValidate)
	{
		bool validate = matrixDirty || forceValidate;

		if (validate)
			ValidateMatrix();
		OnRedraw();

		for (Object* childObject : childObjects)
			childObject->Redraw(validate);
	}

	void Object::AddChild(Object* obj)
	{
		obj->parentObject = this;
		childObjects.push_back(obj);
	}

	bool Object::RemoveChild(Object* obj)
	{
		auto iter = std::find(childObjects.begin(), childObjects.end(), obj);
		if (iter == childObjects.end())
			return false;
		childObjects.erase(iter);
		return true;
	}

	void Object::RemoveFromParent()
	{
		if (parentObject == nullptr)
			return;
		parentObject->RemoveChild(this);
	}

	Vector3 Object::GetPosition() const
	{
		return position;
	}

	Quaternion Object::GetRotation() const
	{
		return rotation;
	}

	Vector3 Object::GetScale() const
	{
		return scale;
	}

	void Object::SetPosition(const Vector3& v)
	{
		position = v;
		matrixDirty = true;
	}

	void Object::SetRotation(const Quaternion& v)
	{
		rotation = v;
		matrixDirty = true;
	}

	void Object::SetScale(const Vector3& v)
	{
		scale = v;
		matrixDirty = true;
	}

	void Object::OnRedraw()
	{

	}
}