#if LEGACY
#include "Standard.h"

namespace Window {

    GLFWwindow* window;

    void tweakBarInit();

    void create() {

	if(!glfwInit()) {
	    std::cerr << "Failed to initialize glfw!" << std::endl;
	    exit(-1);
	    return;
	}

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_SAMPLES, 4);
	window = glfwCreateWindow(WIDTH*SCALE, HEIGHT*SCALE, NAME, NULL, NULL);
	if (!window) {
	    std::cerr << "Failed to create window!" << std::endl;
	    terminate();
	    exit(-1);
	    return;
	}

	glfwMakeContextCurrent(window);

	GLFWmonitor *monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	glfwSetWindowPos(window, (mode->width-WIDTH*SCALE)/2, (mode->height-HEIGHT*SCALE)/2);

	glfwSetKeyCallback(window, Input::keyCallback);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);
	glDepthFunc(GL_LESS);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, WIDTH, HEIGHT, 0, 1, -1);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glfwSwapInterval(0);

	tweakBarInit();
    }

    void tweakBarInit() {
	TwInit(TW_OPENGL_CORE, NULL);
	TwWindowSize(WIDTH, HEIGHT);

	// after GLFW initialization
	// directly redirect GLFW events to AntTweakBar
	glfwSetMouseButtonCallback((GLFWmousebuttonfun)TwEventMouseButtonGLFW);
	glfwSetMousePosCallback((GLFWmouseposfun)TwEventMousePosGLFW);
	glfwSetMouseWheelCallback((GLFWmousewheelfun)TwEventMouseWheelGLFW);
	glfwSetKeyCallback((GLFWkeyfun)TwEventKeyGLFW);
	glfwSetCharCallback((GLFWcharfun)TwEventCharGLFW);

	// send window size events to AntTweakBar
	glfwSetWindowSizeCallback(MyResize); // and call TwWindowSize in the function MyResize
    }

    bool shouldClose() {

	return glfwWindowShouldClose(window);
    }

    void terminate() {

	glfwTerminate();
    }

    void destroy() {

	glfwDestroyWindow(window);
    }

    void swap() {

	glfwSwapBuffers(window);
    }

    void poll() {

	glfwPollEvents();
    }
}
#endif