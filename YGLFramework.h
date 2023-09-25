#pragma once

namespace ygl
{
	class Scene;

	class YGLFramework
	{
	private:
		static Scene* currentScene;

	public:
		static void Initialize(int argc, char** argv);

	private:
		static void DrawScene();
		static void Reshape(int x, int y);
	};
}