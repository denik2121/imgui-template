#pragma once

#include "glad/gl.h"
#include "GLFW/glfw3.h"
#include "imgui.h"

class OpenGLDriver
{
public:
	OpenGLDriver(int32_t InWidth, int32_t InHeight, const char* InWindowTitle);
	~OpenGLDriver();

	OpenGLDriver() = delete;
	OpenGLDriver(const OpenGLDriver& other) = delete;
	OpenGLDriver& operator=(const OpenGLDriver& other) = delete;

	bool IsInitialized()		{ return bInitialized; }
	bool WindowShouldClose()	{ return glfwWindowShouldClose(Window); }
	void StartFrame();
	void EndFrame();
	GLFWwindow* GetWindow()		{ return Window; }

	static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

	// Add a dockspace overlay on top the main viewport
	void EnableDockspace();

	ImVec4 ClearColor = ImVec4(0.22f, 0.33f, 0.33f, 1.0f);
protected:
	bool bInitialized = false;
	GLFWwindow* Window = nullptr;
};