#include "pch.h"
#include "YGLFramework.h"
#include "Scene.h"

namespace ygl
{
	std::string YGLFramework::applicationTitle = "YGLcpp Application";
	Scene* YGLFramework::currentScene = nullptr;
	void (*YGLFramework::updateCallback)() = nullptr;

	void YGLFramework::Initialize(int argc, char** argv)
	{
		glutInit(&argc, argv);

		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
		glutInitWindowPosition(100, 100);
		glutInitWindowSize(640, 480);

		glutCreateWindow(applicationTitle.c_str());
		// glutFullScreen();

		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
		{
			std::cerr << "Unable to initialize GLEW" << std::endl;
			exit(EXIT_FAILURE);
		}
		else
			std::cout << "GLEW Initialization" << std::endl;

		glutIdleFunc(Update);
		glutDisplayFunc(DrawScene);
		glutReshapeFunc(Reshape);

		YGLFramework::currentScene = new Scene();

		glutMainLoop();
	}

	void YGLFramework::SetUpdateHandler(void (*callback)())
	{
		updateCallback = callback;
	}

	void YGLFramework::Update()
	{
#ifdef _DEBUG
		constexpr int REFRESH_RATE = 20;
		static int frameCounts[REFRESH_RATE];
		static clock_t lc;
		clock_t c = clock();
		int p = c * REFRESH_RATE / 1000 % REFRESH_RATE;
		if (lc * REFRESH_RATE / 1000 != c * REFRESH_RATE / 1000)
		{
			int fps = 0;
			for (int i = 0; i < REFRESH_RATE; ++i)
				fps += frameCounts[i];
			glutSetWindowTitle((applicationTitle + std::format(" @ {} FPS", fps)).c_str());
			frameCounts[p] = 0;
		}
		frameCounts[p] += 1;
		lc = c;
#endif

		if (YGLFramework::updateCallback != nullptr)
			YGLFramework::updateCallback();
		glutPostRedisplay();
	}

	void YGLFramework::DrawScene()
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (currentScene != nullptr)
			currentScene->Redraw();

		glutSwapBuffers();
	}

	void YGLFramework::Reshape(int x, int y)
	{

	}
}