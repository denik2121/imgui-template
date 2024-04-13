// main.cpp : Entry point for the ImGui template
//

#include "imgui.h"
#include "OpenGLDriver.h"

void DrawHelloWorldWindow(OpenGLDriver& ogld);

int main()
{
	OpenGLDriver ogl(1600, 900, "ImGui Template");

	if (!ogl.IsInitialized())
		return -1;

	while (!ogl.WindowShouldClose())
	{
		ogl.StartFrame();
		ogl.EnableDockspace();

		// Do stuff
		DrawHelloWorldWindow(ogl);

		// Rendering
		ogl.EndFrame();
	}

	return 0;
}

void DrawHelloWorldWindow(OpenGLDriver& ogld)
{
	static bool show_demo_window = true;
	static bool show_another_window = false;


	// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	if (show_demo_window)
	{
		ImGui::ShowDemoWindow(&show_demo_window);
	}

	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
	{
		static float f = 0.0f;
		static int counter = 0;

		ImGui::GetForegroundDrawList()->AddRect(ImVec2(100, 100), ImVec2(200, 200), IM_COL32(255, 0, 0, 255));
     	        ImVec2 screenCenter = ImGui::GetIO().DisplaySize * 0.5f;
                float circleRadius = 50.0f;
                ImGui::GetForegroundDrawList()->AddCircleFilled(screenCenter, circleRadius, IM_COL32(255, 255, 255, 255), 32);
		if (ImGui::Button("Button"))								// Buttons return true when clicked (most widgets return true when edited/activated)
		{
			counter++;
		}

		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

	// 3. Show another simple window.
	if (show_another_window)
	{
		ImGui::Begin("Another Window", &show_another_window);	// Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		ImGui::Text("Hello from another window!");
		if (ImGui::Button("Close Me"))
		{
			show_another_window = false;
		}

		ImGui::End();
	}
}
