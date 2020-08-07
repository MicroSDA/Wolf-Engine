#include "MainScene.h"
//#include <Core/Engine/Engine.h>

MainScene::MainScene()
	:Scene(),
    shader("basicShader"),
    camera(glm::vec3(2.0, 0.0, -10.0), 70.0f, float(800) / float(600), 0.01f, 3000.0f)
{
    Prepare();
}

MainScene::~MainScene()
{
    delete model;
}

int MainScene::Process()
{
    //camera.RotatePitch(0.1f);

    if (m_Input->IsKeyboardBPressed(we::KEY_W))
        camera.MoveForward(0.01f);

    if (m_Input->IsKeyboardBPressed(we::KEY_S))
        camera.MoveBack(0.01f);

    if (m_Input->IsKeyboardBPressed(we::KEY_A))
        camera.MoveLeft(0.01f);

    if (m_Input->IsKeyboardBPressed(we::KEY_D))
        camera.MoveRight(0.01f);

    if (m_Input->IsKeyboardBPressed(we::KEY_UP))
        camera.RotatePitch(0.1f);

    if (m_Input->IsKeyboardBPressed(we::KEY_DOWN))
        camera.RotatePitch(-0.1f);

    if (m_Input->IsKeyboardBPressed(we::KEY_LEFT))
        camera.RotateYaw(0.1f);

    if (m_Input->IsKeyboardBPressed(we::KEY_RIGHT))
        camera.RotateYaw(-0.1f);

    if (m_Input->IsKeyboardBPressed(we::KEY_DELETE))
    {
        if (model != nullptr)
        {
            delete model;
            model = nullptr;
        }
    }
        


    if (m_Input->IsKeyboardBPressed(we::KEY_ESCAPE))
    {
        return WE_FORCE_EXIT;
    }

    //std::cout << glm::degrees(camera.GetUpDirrection()).y << "\n";
}

void MainScene::Render()
{
   
 
    we::Transform transform;
    shader.Bind();
    shader.Update(transform, camera);
    if (model != nullptr)
    {
        model->Draw();
    }

   
}

void MainScene::Prepare()
{
    m_Display->SetClearColor(0.5444f, 0.62f, 0.69f, 1.0f);

    we::ResourceLoader loader;
    model = loader.LoadModel("./Resources/Models/cube.bin");

    //TODO: Loading shaders, some basic textures, objects and other things that necessary for the first run and rendering
}

