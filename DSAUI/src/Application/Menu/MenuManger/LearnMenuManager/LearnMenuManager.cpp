#include "../../../../dsa_pch.h"

#include "LearnMenuManager.h"

#include "../../MenuAppSignaler.h"

#include "../../../Widget/TextBox.h"
#include "../../../Widget/Canvas.h"
#include "../../../Widget/Button.h"
#include "../../../Widget/CustomWidget.h"
#include "../../../Widget/Shape/DrawableRectangle.h"

#include "../../Animator/SortAnimator.h"

#include "LearnMenuUtils.h"

#include "Logger/Logger.h"

std::string LearnMenuManager::s_LearnPath = "learntabs/";
Animator* LearnMenuManager::s_CanvasAnimator = nullptr;

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
        LOG_GUI_FATAL("Can't open file %s", path.c_str());
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

    std::string id = "textbox_" + panel->GetId() + "_" + std::to_string(index);
    TextBox* text = new TextBox(id, MenuAppSignaler::SignalRequestToken(token));
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

    std::string id = "canvas_" + panel->GetId() + "_" + std::to_string(index);
    Canvas* canvas = new Canvas(id);
    canvas->ScaleTo({ width, height });
    canvas->SetBgColor(IM_COL32_BLACK);

    float offset = 0.0f;
    int max = data["maxValue"];
    float deltaWidth = (width - 2 * offset) / max;
    float deltaHeight = (height - 2 * offset) / max;
    std::vector<uint32_t> vals = CreateVector(max);
    for (int i = 0; i < max; i++)
    {
        DrawableRectangle* rect = new DrawableRectangle(
            { offset + deltaWidth * i, height - offset },
            { offset + deltaWidth * (i + 1), height - (deltaHeight * (vals[i] + 1)) - offset }
        );
        rect->SetColor(IM_COL32_WHITE);
        rect->SetFilled(true);

        canvas->AddDrawableShape(rect);
    }

    Button* stopBut = new Button("button_stop_canvas_" + std::to_string(index), "Stop");
    Button* beginBut = new Button("button_begin_canvas_" + std::to_string(index), "Begin");

    // begin button
    beginBut->SetCallback( [canvas, beginBut, stopBut]
        {
            if (s_CanvasAnimator == nullptr || !s_CanvasAnimator->IsPlaying())
            {
                BeginCanvasAnimation(canvas);
                // beginBut->Disable(); // TODO: make it work after animation is done
                // stopBut->Enable();
            }
        });
    beginBut->MoveTo({ 5.0f, height + 5.0f});
    beginBut->ScaleTo({ 50.0f, 20.0f });

    // stop button
    stopBut->SetCallback( [beginBut, stopBut]
        {
            if (s_CanvasAnimator != nullptr && s_CanvasAnimator->IsPlaying())
            {
                s_CanvasAnimator->Stop();
                // beginBut->Enable();
                // stopBut->Disable();
            }
        });
    stopBut->MoveTo({125.0f, height + 5.0f});
    stopBut->ScaleTo({ 50.0f, 20.0f });
    // stopBut->Disable();

    // Output panel
    Panel* sub = new Panel("subpanel_canvas_" + panel->GetId());
    sub->MoveTo({ posX, posY });
    sub->ScaleTo({ width, height + 300.0f });
    sub->HideBorder();
    sub->HideScrollBar();

    sub->AddWidget(canvas);
    sub->AddWidget(beginBut);
    sub->AddWidget(stopBut);

    panel->AddWidget(sub);
}

std::vector<uint32_t> LearnMenuManager::CreateVector(uint32_t max, bool shuffle)
{
    if (max == 0)
    {
        LOG_GUI_FATAL("Can't create vector, max value is 0");
        exit(1);
    }

    std::vector<uint32_t> ret;
    ret.resize(max);

    std::iota(ret.begin(), ret.end(), 0);
    if (shuffle)
    {
        static std::mt19937 rng(std::random_device{}());
        std::shuffle(ret.begin(), ret.end(), rng);
    }

    return ret;
}

void LearnMenuManager::BeginCanvasAnimation(Canvas *canvas)
{
    // shuffle begin
    std::vector<DrawableShape*>& shapes = canvas->GetAllDrawableShapes();
    std::vector<uint32_t> indexes = CreateVector(shapes.size(), true);
    std::vector<uint32_t> currentOrder = CreateVector(indexes.size());
    for (int i = 0; i < indexes.size(); i++)
    {
        for (int j = i; j < indexes.size(); j++)
        {
            if (currentOrder[j] == indexes[i])
            {
                LearnMenuUtils::SwapRectangles(shapes, i, j);
                std::swap(currentOrder[i], currentOrder[j]);
                break;
            }
        }
    }

    std::vector<Step> steps;
    // shuffle end

    // sort begin
    // bubble sort as an example
    // TODO: move this in core
    for (int i = 0; i < indexes.size(); i++)
    {
        bool ok = true;
        for (int j = i + 1 ; j < indexes.size(); j++)
        {
            steps.emplace_back(i, j, SortActionType::COMPARE);
            if (indexes[i] > indexes[j])
            {
                ok = false;
                std::swap(indexes[i], indexes[j]);
                steps.emplace_back(i, j, SortActionType::SWAP);
            }
        }

        steps.emplace_back(i, 0, SortActionType::DONE);
    }
    // sort end

    delete s_CanvasAnimator;
    s_CanvasAnimator = new SortAnimator(canvas, currentOrder, steps);
    s_CanvasAnimator->Start();
}

void LearnMenuManager::UpdateCanvasAnimation()
{
    s_CanvasAnimator->Update();
}

bool LearnMenuManager::IsCanvasAnimationInProgress()
{
    return s_CanvasAnimator != nullptr && s_CanvasAnimator->IsPlaying();
}
