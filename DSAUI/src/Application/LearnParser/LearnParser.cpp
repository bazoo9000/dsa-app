#include "../../dsa_pch.h"

#include <random>

#include "LearnParser.h"

#include "../Widget/TextBox.h"
#include "../Widget/Canvas.h"
#include "../Widget/Shape/DrawableCircle.h"
#include "../Widget/Shape/DrawableRectangle.h"

#include "Logger/Logger.h"

std::string LearnParser::s_LearnPath = "learntabs/";

Panel* LearnParser::CreateLearnPanel(std::string learnTabName)
{
    json learnTabData = readJSON(learnTabName);

    Panel* ret = new Panel("panel_" + learnTabName);
    ret->SetAutoPositioning(true);
    ret->ScaleBy(0.0f);
    ret->HideBorder();

    parseJSON(learnTabData, ret);

    return ret;
}

std::map<std::string, std::string> LearnParser::GetAllTitles()
{
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

json LearnParser::readJSON(std::string jsonFileName)
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

Panel* LearnParser::parseJSON(json jsonData, Panel* panel)
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

void LearnParser::setText(Panel* panel, const json& data, int index)
{
    std::string token = data["token"];
    int yClamp = data["yClamp"];

    std::string id = std::to_string(index) + "_textbox_" + panel->GetId();
    TextBox* text = new TextBox(id, token);
    text->ScaleTo({ 0.0f, (float)yClamp });
    text->SetAutoPositioning(true);

    panel->AddWidget(text);
}

void LearnParser::setCanvas(Panel* panel, const json& data, int index)
{
    float width = data["size"]["width"];
    float height = data["size"]["height"];

    float posX = data["position"]["x"];
    float posY = data["position"]["y"];

    std::string id = std::to_string(index) + "_canvas_" + panel->GetId();
    Canvas* canvas = new Canvas(id);
    canvas->MoveTo({ posX, posY });
    canvas->ScaleTo({ width, height });

    float offset = 2.0f;
    int max = data["maxValue"];
    float deltaWidth = (float)(width - 2 * offset) / max;
    float deltaHeight = (float)(height - 2 * offset) / max;
    std::vector<uint32_t> vals = LearnParser::createVector(max);
    for (int i = 0; i < max; i++)
    {
        // TODO: parse based on type of canvas
        DrawableRectangle* rect = new DrawableRectangle(
            { offset + deltaWidth * i, height - offset },
            { offset + deltaWidth * (i + 1), height - (deltaHeight * vals[i]) - offset}
        );
        rect->SetColor(IM_COL32(0 + (40 * i), 0, 0, 255));
        rect->SetFilled(true);

        canvas->AddDrawableShape(rect);
    }

    panel->AddWidget(canvas);
}

std::vector<uint32_t> LearnParser::createVector(uint32_t max, bool shuffle)
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
