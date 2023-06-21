
#include <iostream>
#include "OpenGLDriver.h"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

constexpr int32_t VIEWPORTS_ENABLE = 1;

OpenGLDriver::OpenGLDriver(int32_t InWidth, int32_t InHeight, const char* InWindowTitle)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	Window = glfwCreateWindow(InWidth, InHeight, InWindowTitle, nullptr, nullptr);
	if (!Window)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(Window);
	glfwSwapInterval(1); // Enable vsync
	glfwSetFramebufferSizeCallback(Window, (OpenGLDriver::FramebufferSizeCallback));

	if (!gladLoadGL(glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD" << std::endl;
		return;
	}

	constexpr char glsl_version[] = "#version 330 core";
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking

	if constexpr (VIEWPORTS_ENABLE)
	{
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
	}

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(Window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
	bInitialized = true;
}

OpenGLDriver::~OpenGLDriver()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
}

void OpenGLDriver::StartFrame()
{
	glfwPollEvents();

	// Input Processing -- move this somewhere else.
	if (glfwGetKey(Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(Window, true);

	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void OpenGLDriver::EndFrame()
{
	ImGui::Render();
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClearColor(ClearColor.x * ClearColor.w, ClearColor.y * ClearColor.w, ClearColor.z * ClearColor.w, ClearColor.w);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	// Update and Render additional Platform Windows
	// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
	//  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
	if constexpr (VIEWPORTS_ENABLE)
	{
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	}

	glfwSwapBuffers(Window);
}

void OpenGLDriver::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	(void*)window; // suppress warning
	glViewport(0, 0, width, height);
}

void OpenGLDriver::EnableDockspace()
{
	constexpr ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_AutoHideTabBar | ImGuiDockNodeFlags_PassthruCentralNode;
	ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), dockspace_flags);
}
