#pragma once
#include "pch.h"

namespace ygl
{
	class Mesh
	{
	private:
		vector<float> positions;
		vector<float> normals;
		vector<float> uvs;
		vector<unsigned int> indices;
	};
}