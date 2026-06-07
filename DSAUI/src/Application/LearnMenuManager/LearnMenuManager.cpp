#include "../../dsa_pch.h"

#include <random>

#include "LearnMenuManager.h"

#include "../Widget/TextBox.h"
#include "../Widget/Canvas.h"
#include "../Widget/Button.h"
#include "../Widget/CustomWidget.h"
#include "../Widget/Shape/DrawableCircle.h"
#include "../Widget/Shape/DrawableRectangle.h"

#include "Logger/Logger.h"

std::string LearnMenuManager::s_LearnPath = "learntabs/";

Panel* LearnMenuManager::CreateLearnPanel(std::string learnTabName)
{
    json learnTabData = readJSON(learnTabName);

    Panel* ret = new Panel("panel_" + learnTabName);
    ret->SetAutoPositioning(true);
    ret->ScaleBy(0.0f);
    ret->HideBorder();

    parseJSON(learnTabData, ret);

    return ret;
}

std::map<std::string, std::string> LearnMenuManager::GetAllTitles()
{
    // filename -> title token
    std::map<std::string, std::string> ret;

    namespace fs = std::filesystem;
    for (const auto& entry : fs::directory_iterator(s_LearnPath))
    {
        std::string fileName = entry.path().stem().string();

        json data = json::parse(std::ifstream(entry.path()));
        ret[fileName] = data["title"];
    }

    return ret;
}

json LearnMenuManager::readJSON(std::string jsonFileName)
{
    std::string path = s_LearnPath + jsonFileName + ".json";
    std::ifstream dataFile(path.c_str());

    if (!dataFile)
    {
        LOG_GUI_FATAL("Can't open file %s", path);
        exit(1);
    }

    json learnTabData = json::parse(dataFile);

    dataFile.close();

    return learnTabData;
}

Panel* LearnMenuManager::parseJSON(json jsonData, Panel* panel)
{
    json show = jsonData["show"];
    for (int i = 0; i < show.size(); i++)
    {
        // TODO: Validate json data!!!!
        const json data = show[i]["data"];
        std::string type = show[i]["type"];

        if (type == "paragraph")
        {
            setText(panel, data, i);
            continue;
        }

        if (type == "canvas")
        {
            setCanvas(panel, data, i);
            continue;
        }
    }
    return nullptr;
}

void LearnMenuManager::setText(Panel* panel, const json& data, int index)
{
    std::string token = data["token"];
    int yClamp = data["yClamp"];

    std::string id = std::to_string(index) + "_textbox_" + panel->GetId();
    TextBox* text = new TextBox(id, token);
    text->ScaleTo({ 0.0f, (float)yClamp });
    text->SetAutoPositioning(true);

    panel->AddWidget(text);
}

void LearnMenuManager::setCanvas(Panel* panel, const json& data, int index)
{
    float width = data["size"]["width"];
    float height = data["size"]["height"];

    float posX = data["position"]["x"];
    float posY = data["position"]["y"];

    std::string id = std::to_string(index) + "_canvas_" + panel->GetId();
    Canvas* canvas = new Canvas(id);
    //canvas->MoveTo({ posX, posY });
    canvas->ScaleTo({ width, height });
    canvas->SetBgColor(IM_COL32_BLACK);

    float offset = 0.0f;
    int max = data["maxValue"];
    float deltaWidth = (float)(width - 2 * offset) / max;
    float deltaHeight = (float)(height - 2 * offset) / max;
    std::vector<uint32_t> vals = LearnMenuManager::createVector(max);
    for (int i = 0; i < max; i++)
    {
        // TODO: parse based on type of canvas
        DrawableRectangle* rect = new DrawableRectangle(
            { offset + deltaWidth * i, height - offset },
            { offset + deltaWidth * (i + 1), height - (deltaHeight * vals[i]) - offset }
        );
        rect->SetColor(IM_COL32_WHITE);
        rect->SetFilled(true);

        canvas->AddDrawableShape(rect);
    }

    int* in = new int[2];
    in[0] = 1;
    in[1] = 100;

    // TODO: maybe add input widget
    CustomWidget* input = new CustomWidget("custom_input");
    input->AddCustomScript([in]()
        {
            ImGui::InputInt2("Swap x with y", in);
        }
    );

    Button* but = new Button("button_swap_" + panel->GetId(), "Swap");
    but->MoveTo({ 0.0f, canvas->GetTransform().scale.y + 5.0f });
    but->ScaleTo({ 50.0f, 20.0f});
    but->SetCallback([canvas, in]()
        {
            // TODO: move all of this into a function so that it can be called when sorter begins sorting
            ImU32 colorDone = IM_COL32(0, 255, 0, 255);
            ImU32 colorSelected = IM_COL32(255, 0, 0, 255);
            ImU32 colorNeutral = IM_COL32_WHITE;

            const std::vector<DrawableShape*>& shapes = canvas->GetAllDrawableShapes();

            int i1 = in[0] - 1;
            int i2 = in[1] - 1;

            if (i1 == i2)
            {
                return;
            }

            if (i1 < 0 || i2 < 0 || i1 > 99 || i2 > 99)
            {
                return;
            }

            DrawableRectangle* rect1 = (DrawableRectangle*)shapes[i1];
            DrawableRectangle* rect2 = (DrawableRectangle*)shapes[i2];

            ImVec2 r1Origin = rect1->GetOrigin();
            ImVec2 r2Origin = rect2->GetOrigin();
            ImVec2 r1End = rect1->GetEnd();
            ImVec2 r2End = rect2->GetEnd();

            rect1->SetColor(colorSelected);
            rect2->SetColor(colorSelected);

            rect1->SetOrigin(r2Origin);
            rect2->SetOrigin(r1Origin);
            rect1->SetEnd({ r2End.x, r1End.y });
            rect2->SetEnd({ r1End.x, r2End.y });

            rect1->SetColor(colorNeutral);
            rect2->SetColor(colorNeutral);
        }
    );

    Panel* sub = new Panel("subpanel_canvas_" + panel->GetId());
    sub->MoveTo({ posX, posY });
    sub->ScaleTo({ width, height + 60.0f });
    sub->HideBorder();
    sub->HideScrollBar();

    sub->AddWidget(canvas);
    sub->AddWidget(but);
    sub->AddWidget(input);

    panel->AddWidget(sub);
}

std::vector<uint32_t> LearnMenuManager::createVector(uint32_t max, bool shuffle)
{
    if (max == 0)
    {
        LOG_GUI_FATAL("Can't create vector, max value is 0");
        exit(1);
    }

    std::vector<uint32_t> ret;
    ret.resize(max);

    std::iota(ret.begin(), ret.end(), 1);
    if (shuffle)
    {
        std::shuffle(ret.begin(), ret.end(), std::mt19937());
    }

    return ret;
}
