#include "../../dsa_pch.h"

#include "LearnParser.h"

#include "../Widget/TextBox.h"
#include "../Widget/Canvas.h"
#include "../Widget/Shape/DrawableCircle.h"

#include "Logger/Logger.h"

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

json LearnParser::readJSON(std::string jsonFileName)
{
    std::string path = "learntabs/" + jsonFileName + ".json";
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

    json vals = data["values"];
    for (int j = 0; j < vals.size(); j++)
    {
        // TODO: parse based on type of canvas
        DrawableCircle* circle = new DrawableCircle({ 50.0f * (j + 1), 100.0f }, 20.0f);
        circle->SetColor(IM_COL32(0 + (40 * j), 0, 0, 255));

        canvas->AddDrawableShape(circle);
    }

    panel->AddWidget(canvas);
}
