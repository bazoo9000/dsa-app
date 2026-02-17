#include "Application.h"
#include "DSACore.h"

#include "Widget/Button.h"
#include "Widget/Panel.h"
#include "Widget/BasicText.h"
#include "Widget/TextLabel.h"
#include "Widget/TextBox.h"
#include "Widget/ComboBox.h"

Application::Application()
{
	// TODO: Make window builder, too many params :(
	const char* title = "Data Structures and Algorithms the app";
	m_Window = new Window(title, 1280, 720);	// GLFW init
	initGLAD();									// GLAD init
	initImGUI("#version 130");					// ImGUI init
	m_I18N = I18NFactory::GetI18N("ro-RO");		// I18N init
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	LoadFonts(io);								// Load all basic fonts
	
	// TODO: dereferencing these looks utterly terrible, probably move it somewhere else, maybe in I18N class
	auto misses = m_TextCache.GetMissingKeys(
		{ "GUI.BACK", "GUI.OPTIONS", "GUI.WELCOME", "GUI.NU_EXISTA" }
	);

	if (misses.size() != 0)
	{
		std::vector<TV> tvs = m_I18N->GetTexts(misses);
		for (auto tv : tvs)
		{
			m_TextCache.Cache(tv.first, tv.second);
		}
	}

	Screen::SetApp(this); // set listener
	initScreens();
	ChangeScreen("screen_main");
	
	m_TextCache = CacheManager<std::string>(250);
	m_WidgetCache = CacheManager<Widget*>(10);

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

	while (!glfwWindowShouldClose(window) && !m_ShouldClose)
	{
		glfwPollEvents();
		imguiCreateFrame();

		// WIDGETS GO HERE
		ImVec2 windowSize = m_Window->GetWindowSize();

		// TODO: cache all ui elements to avoid reinits
		ImGui::SetNextWindowPos({ 0, 0 });
		ImGui::SetNextWindowSize(windowSize);
		ImGui::Begin("##main", nullptr,
			ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoTitleBar
		);

		m_CrtScreen->Draw();

		ImGui::End();

		ImGui::ShowDemoWindow();
		// WIDGETS END HERE

		render(window, windowSize);
	}
	LOG_GUI_TRACE("Application run end");
}

void Application::ChangeScreen(std::string id)
{
	m_CrtScreen = &m_Screens[id]; // or nullptr if id not found
}

void Application::Close()
{
	m_ShouldClose = true;
}

void Application::initScreens()
{
	// screen inits go here

	// TODO: hide implementation of screen, its gonna get crowded real fast
	Button* but = new Button("but_back", *m_TextCache.Get("GUI.BACK"));
	but->SetCallback(
		[]()
		{
			LOG_GUI_DEBUG("Closing");
			// yes i can also use Close() method, this will be moved
			Screen::SignalCloseApp();
		}
	);
	but->MoveTo({ 100.0f, 100.0f });
	but->ScaleTo({ 50.0f, 20.0f });

	Button* opt = new Button("but_options", *m_TextCache.Get("GUI.OPTIONS"));
	opt->SetCallback(
		[]()
		{
			Screen::SignalChangeScreen("screen_options");
		}
	);
	opt->MoveTo({ 100.0f, 130.0f });
	opt->ScaleTo({ 50.0f, 20.0f });

	TextLabel* title = new TextLabel("title", *m_TextCache.Get("GUI.WELCOME"), FONT_H1);
	title->MoveTo({ 520.0f, 10.0f });
	title->ScaleTo({ 300.0f, 300.0f });

	TextLabel* test = new TextLabel("test", *m_TextCache.Get("GUI.NU_EXISTA"));
	test->MoveTo({ 100.0f, 200.0f });

	std::vector<Widget*> widgets = { but, title, opt, test };
	Panel* p = new Panel("panel_main", widgets);

	Screen main("screen_main", p);

	// SEPARATOR //

	TextLabel* title_options = new TextLabel("title", *m_TextCache.Get("GUI.OPTIONS"), FONT_H1);
	title_options->MoveTo({ 520.0f, 10.0f });
	title_options->ScaleTo({ 300.0f, 300.0f });

	std::vector<Widget*> widgets1 = { but, title_options };
	Panel* p1 = new Panel("panel_options", widgets1);

	Screen options("screen_options", p1);

	m_Screens["screen_main"] = main;
	m_Screens["screen_options"] = options;
}

void Application::initImGUI(const char* glslVersion)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

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
