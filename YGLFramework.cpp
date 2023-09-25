#include "pch.h"
#include "YGLFramework.h"
#include "Scene.h"

namespace ygl
{
	void YGLFramework::Initialize(int argc, char** argv)
	{
		glutInit(&argc, argv);

		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
		glutInitWindowPosition(100, 100);
		glutInitWindowSize(640, 480);

		glutCreateWindow("OpenGLExperiment");
		// glutFullScreen();

		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
		{
			std::cerr << "Unable to initialize GLEW" << std::endl;
			exit(EXIT_FAILURE);
		}
		else
			std::cout << "GLEW Initialization" << std::endl;

		glutDisplayFunc(DrawScene);
		glutReshapeFunc(Reshape);

		YGLFramework::currentScene = new Scene();

		glutMainLoop();
	}

	void YGLFramework::DrawScene()
	{
		currentScene->Redraw();
	}

	void YGLFramework::Reshape(int x, int y)
	{

	}
}