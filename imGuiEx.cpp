// imGuiEx.cpp : Defines the entry point for the application.
//

#include "imGuiEx.h"

using namespace std;

class CustomImGui : public UseImGui {
public:

	virtual void Update() override {

	static float f = 0.0f;
	static int counter = 0;

	ImGui::Begin("Joor Se Bolo");
	ImGui::Text(" Jai Shree Ram!");

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
	{
		std::cout <<"Failed to initialise GLFW" << std::endl;
		return 1;
	}


	// GL 3.0 + GLSL 130
	const char* glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only

	GLFWmonitor* MyMonitor = glfwGetPrimaryMonitor();

	// Create window with graphics context
	//GLFWwindow* window = glfwCreateWindow(1280, 720, "Dear ImGui - Example", NULL, NULL);
	GLFWwindow* window = glfwCreateWindow(glfwGetVideoMode(glfwGetPrimaryMonitor())->width,
										  glfwGetVideoMode(glfwGetPrimaryMonitor())->height,
								   	"JAI SHREE RAM MAIN WINDOW",
									NULL, NULL);
	
	if (window == NULL)
	{
		glfwTerminate();
		return 1;
	}

	glfwMakeContextCurrent(window);
	gladLoadGL();
	glfwSwapInterval(1); // Enable vsync

	// Displaying Image
	// 
	if (gl3wInit())
	{
		std::cout << "Failed to initialize openGL" << std::endl;
		return 1;
	}

	int screen_width, screen_height;
	glfwGetFramebufferSize(window, &screen_width, &screen_height);
	glViewport(0, 0, screen_width, screen_height);

	// There are two implementations of this: 1) UseImGui Class 2) CustomImGui Class
	// Just comment one and uncomment other 
	UseImGui myimgui;
	//CustomImGui myimgui; 
	myimgui.Init(window, glsl_version);


	int my_image_width = 0;
	int my_image_height = 0;
	GLuint my_image_texture = 0;
	bool ret = LoadTexutreFromFile("C:/Users/jaisw/OneDrive - University of Florida/Documents/VS_projects/imGuiEx/fruitImage.jpg", &my_image_texture, &my_image_width, &my_image_height);
	if (!ret)
	{
		std::cout << "Unable to load the image file" << std::endl;
		return 1;
	}

	// Initialize OpenGL rendering context

	

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
		glClear(GL_COLOR_BUFFER_BIT);
		myimgui.NewFrame();

		myimgui.Update();
		ImGui::Begin("OpenGL JSR Texture");
		ImGui::Text("pointer = %p", my_image_texture);
		ImGui::Text("size = %d X %d", my_image_width, my_image_height);
		ImGui::Image((void*)(intptr_t)my_image_texture, ImVec2(my_image_width, my_image_height));
		ImGui::End();

		ImGui::Begin("JSR Background Texture");
		ImGui::Text("pointer = %p", my_image_texture);
		ImGui::Text("size = %d X %d", my_image_width, my_image_height);
		int win_width = glfwGetVideoMode(glfwGetPrimaryMonitor())->width;
		int win_height = glfwGetVideoMode(glfwGetPrimaryMonitor())->height;
		ImGui::GetBackgroundDrawList()->AddImage((void*)(intptr_t)my_image_texture, ImVec2(0,0), ImVec2(win_width,win_height), ImVec2(0,0), ImVec2(1,1));
		ImGui::End();


		myimgui.Render();
		glfwSwapBuffers(window);
	}

	myimgui.Shutdown();

	return 0;
}

bool LoadTexutreFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height)
{

	int image_width = 0;
	int image_height = 0;
	unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);

	if (image_data == NULL)
	{
		return false;
	}

	// Create a openGL texture identifier
	GLuint image_texture;
	glGenTextures(1, &image_texture);
	glBindTexture(GL_TEXTURE_2D, image_texture);

	// Setup filtering 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same


	// Upload pixels into texture

	#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
	#endif

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
	stbi_image_free(image_data);

	*out_texture = image_texture;
	*out_width = image_width;
	*out_height = image_height;

	return true;
}

