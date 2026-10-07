#include "../dsa_pch.h"

#include "Application.h"
#include "DSACore.h"

#include "Settings.h"

#include "Time.h"

#include "Widget/BasicText.h"
#include "Menu/MenuAppSignaler.h"
#include "Menu/MainMenu.h"
#include "Menu/OptionsMenu.h"
#include "Menu/LearnMenu.h"

Application::Application()
{
	SettingsData settingsData = Settings::LoadSettings();

	const char* title = "Data Structures and Algorithms the app";
	m_Window = new Window(title, settingsData.resolution.x, settingsData.resolution.y, settingsData.isVsync);
	initGLAD();
	initImGUI("#version 130");
	m_I18N = I18NFactory::GetI18N(settingsData.language);
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	LoadFonts(io);

	m_TextCache = CacheManager<std::string>(250);

	MenuAppSignaler::SetAppRef(this); // set listener
	initMenus();
	ChangeMenu("menu_main");

	LOG_GUI_DEBUG("Application CREATED succesfully");
}

Application::~Application()
{
	destroyImGUI();
	delete m_Window;
	m_Window = nullptr;

	LOG_GUI_DEBUG("Application DESTROYED succesfully");
}

// BIG TODO: make datastructures have to return a static c array and create a translator to shapes in DSAUI
void Application::Run()
{
	LOG_GUI_TRACE("Application run begin");
	GLFWwindow* window = m_Window->GetWindow(); // to avoid overhead

	while (!glfwWindowShouldClose(window) && !m_ShouldClose)
	{
		glfwPollEvents();
		imguiCreateFrame();

		Time::CalculateTime();

		// WIDGETS GO HERE
		ImVec2 windowSize = m_Window->GetWindowSize();

		ImGui::SetNextWindowPos({ 0, 0 });
		ImGui::SetNextWindowSize(windowSize);
		ImGui::Begin("##main", nullptr,
			ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoTitleBar |
			ImGuiWindowFlags_NoScrollbar |
			ImGuiWindowFlags_NoSavedSettings
		);

		m_CrtMenu->Draw();

		ImGui::End();

		ImGui::ShowDemoWindow(); // REMOVE THIS WHEN NOT NEEDED!! better yet check for _DEBUG macro
		// WIDGETS END HERE

		render(window, windowSize);
	}
	LOG_GUI_TRACE("Application run end");
}

void Application::ChangeMenu(std::string id)
{
	if (m_Menus.find(id) == m_Menus.end())
	{
		LOG_GUI_ERROR("Can't change menu, %s doesn't exist", id.c_str());
		return;
	}

	// this may look dirty but it allows dynamic loading instead of loading all at startup
	if (m_Menus[id] == nullptr)
	{
		if (id == "menu_main")         { m_Menus[id] = new MainMenu("menu_main"); }
		else if (id == "menu_options") { m_Menus[id] = new OptionsMenu("menu_options"); }
		else if (id == "menu_learn")   { m_Menus[id] = new LearnMenu("menu_learn"); }

		// this will be executed only when a valid id is given and hasnt been initialized yet
		m_Menus[id]->InitMenu();
	}

	m_CrtMenu = m_Menus[id];
}

void Application::Close()
{
	m_ShouldClose = true;
}

std::unordered_map<std::string, std::string> Application::RequestTokens(std::vector<std::string> tokens)
{
	std::unordered_map<std::string, std::string> ret;
	ret.reserve(tokens.size());

	// Get missed keys and translate them and then cache translated text
	auto misses = m_TextCache.GetMissingKeys(tokens);
	if (misses.size() != 0)
	{
		auto missedTokens = m_I18N->GetTexts(misses);
		for (auto tok : missedTokens)
		{
		    if (tok.first == tok.second) { continue; } // wont cache non-existent tokens
			m_TextCache.Cache(tok.first, tok.second);
		}
	}

	for (auto tok : tokens)
	{
		std::string* text = m_TextCache.Get(tok);
		ret[tok] = (text != nullptr) ? *text : tok;
	}

	return ret;
}

std::string Application::RequestToken(std::string token)
{
    return RequestTokens({ token }).begin()->second;
}

ImVec2 Application::GetWindowSize()
{
	return m_Window->GetWindowSize();
}

void Application::initMenus()
{
	// These are the default menus for this app
	// for this UI app is enough, but if i extend this wrapper this should be loaded from somewhere else
	// and should be loaded
	m_Menus["menu_main"] = nullptr;
	m_Menus["menu_options"] = nullptr;
	m_Menus["menu_learn"] = nullptr;
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
