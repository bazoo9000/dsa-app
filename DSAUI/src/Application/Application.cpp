#include "Application.h"
#include "DSACore.h"
#include "Widget/Button.h"

Application::Application()
{
	// TODO: Make window builder, too many params :(
	const char* title = "Data Structures and Algorithms the app";
	m_Window = new Window(title, 1280, 720);	// GLFW init
	initGLAD();									// GLAD init
	initImGUI("#version 130");					// ImGUI init
	m_I18N = I18NFactory::GetI18N("ro-RO");		// I18N init

	LOG_GUI_DEBUG("Application CREATED succesfully");
}

Application::~Application()
{
	destroyImGUI();
	delete m_Window;
	m_Window = nullptr;

	LOG_GUI_DEBUG("Application DESTROYED succesfully");
}

void Application::Run()
{
	LOG_GUI_TRACE("Application run begin");
	GLFWwindow* window = m_Window->GetWindow(); // to avoid overhead
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		imguiCreateFrame();

		// WIDGETS GO HERE
		bool close = false;
		ImVec2 windowSize = m_Window->GetWindowSize();

		// TODO: somehow cache, to avoid reinit of all ui objects
		ImGui::SetNextWindowPos({ 0, 0 });
		ImGui::SetNextWindowSize(windowSize);
		ImGui::Begin("##main", nullptr,
			ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoTitleBar
		);

		static int pos[2] = { 0, 75 };
		static float scale = 1.0f;
		ImGui::SliderInt2("Move button by", pos, 75, (int)(m_Window->GetWindowSize().y / 2));
		ImGui::SliderFloat("Scale button by", &scale, 0.1f, 5.0f);

		Button but("but_back", m_I18N->GetText("GUI.BACK"));
		but.SetCallback(
			[&close]() 
			{ 
				LOG_GUI_DEBUG("Closing"); 
				close = true; 
			}
		);
		but.MoveTo({ (float)pos[0], (float)pos[1] });
		but.ScaleTo({ 50.0f, 50.0f });
		but.ScaleBy(scale);
		but.Draw();
		ImGui::End();

		ImGui::ShowDemoWindow();
		// WIDGETS END HERE

		if (close)
		{
			break;
		}

		render(window, windowSize);
	}
	LOG_GUI_TRACE("Application run end");
}

void Application::initImGUI(const char* glslVersion)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(m_Window->GetWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 130");

	LOG_GUI_DEBUG("ImGUI initialized succesfully");
}

void Application::initGLAD()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		LOG_GUI_FATAL("(GLAD) Failed to initialize");
		exit(1);
	}
	LOG_GUI_DEBUG("GLAD Loader initialized succesfully");
}

void Application::destroyImGUI()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	LOG_GUI_DEBUG("ImGUI DESTROYED succesfully");
}

void Application::imguiCreateFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void Application::render(GLFWwindow* window, ImVec2 windowSize)
{
	ImGui::Render();
	glViewport(0, 0, windowSize.x, windowSize.y);
	glClearColor(0.45f, 0.55f, 0.60f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(window);
}
