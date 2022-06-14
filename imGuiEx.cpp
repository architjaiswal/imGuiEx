// imGuiEx.cpp : Defines the entry point for the application.
//

#include "imGuiEx.h"
#include "UseImGui.h"

//#include "opencv2"

using namespace std;
//using namespace cv;

class CustomImGui : public UseImGui {
public:

	virtual void Update() override {

	static float f = 0.0f;
	static int counter = 0;

	ImGui::Begin("Joor thi Bolo Jai Shree Ram");
	ImGui::Text("Man ma Ram!");

	ImGui::SliderFloat("float", &f, 0.0f, 1.0f);   	// Edit 1 float using a slider from 0.0f to 1.0f

	
	static float clear_color[3];
	ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

	if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
		counter++;
	ImGui::SameLine();
	ImGui::Text("counter = %d", counter);

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

	ImGui::End();
	}

};

int main()
{

	// Setup window
	if (!glfwInit())
		return 1;


	// GL 3.0 + GLSL 130
	const char* glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only


	// Create window with graphics context
	GLFWwindow* window = glfwCreateWindow(1280, 720, "Dear ImGui - Example", NULL, NULL);
	if (window == NULL)
		return 1;
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glfwSwapInterval(1); // Enable vsync


	int screen_width, screen_height;
	glfwGetFramebufferSize(window, &screen_width, &screen_height);
	glViewport(0, 0, screen_width, screen_height);

	// There are two implementations of this: 1) UseImGui Class 2) CustomImGui Class
	// Just comment one and uncomment other 
	//UseImGui myimgui;
	CustomImGui myimgui; 
	myimgui.Init(window, glsl_version);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
		glClear(GL_COLOR_BUFFER_BIT);
		myimgui.NewFrame();
		myimgui.Update();
		myimgui.Render();
		glfwSwapBuffers(window);
	}

	myimgui.Shutdown();


	return 0;
}
