#include "MainScene.h"
//#include <Core/Engine/Engine.h>

MainScene::MainScene()
	:Scene(),
    m_Camera(glm::vec3(0.0, 0.0, -10.0), 70.0f, float(1000) / float(800), 0.01f, 3000.0f)
{
    Prepare();
}

MainScene::~MainScene()
{
    //we::ResourceManager::GetInstance().ResourceFree("BasicModel", we::SHADER);
    //we::ResourceManager::GetInstance().ResourceFree("cube", we::MODEL3D);
    we::ResourceManager::GetInstance().Truncate();

    for (auto object : m_pObject3d)
    {
        delete object;
    }
    m_pObject3d.clear();
}

int MainScene::Process()
{
   
   if (m_Input->IsKeyboardBPressed(we::KEY_W))
        m_Camera.MoveForward(0.05f * m_Display->GetDeltaTime());

    if (m_Input->IsKeyboardBPressed(we::KEY_S))
        m_Camera.MoveBack(0.05f * m_Display->GetDeltaTime());

    if (m_Input->IsKeyboardBPressed(we::KEY_A))
        m_Camera.MoveLeft(0.05f * m_Display->GetDeltaTime());

    if (m_Input->IsKeyboardBPressed(we::KEY_D))
        m_Camera.MoveRight(0.05f * m_Display->GetDeltaTime());

    if (m_Input->IsKeyboardBPressed(we::KEY_UP))
        m_Camera.RotatePitch(0.05f * m_Display->GetDeltaTime());

    if (m_Input->IsKeyboardBPressed(we::KEY_DOWN))
        m_Camera.RotatePitch(-0.05f * m_Display->GetDeltaTime());

    if (m_Input->IsKeyboardBPressed(we::KEY_LEFT))
        m_Camera.RotateYaw(0.05f * m_Display->GetDeltaTime());

    if (m_Input->IsKeyboardBPressed(we::KEY_RIGHT))
        m_Camera.RotateYaw(-0.05f * m_Display->GetDeltaTime());

    if (m_Input->IsKeyboardBPressed(we::KEY_INSERT))
    {
        for (auto object : m_pObject3d)
        {
            delete object;
        }
        m_pObject3d.clear();
    }

  
    if (m_Input->IsKeyboardBPressed(we::KEY_END))
    {
           m_pObject3d.push_back(new we::Object3D());
            m_pObject3d.back()->SetModel3D(
                we::ResourceManager::GetInstance().Hold("model", we::MODEL3D, m_pObject3d.back())
            );

            float x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX / 150);
            float y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX / 150);
            float z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX / 150);

            float rx = static_cast <float> (rand()) / static_cast <float> (RAND_MAX / 360);
            float ry = static_cast <float> (rand()) / static_cast <float> (RAND_MAX / 360);
            float rz = static_cast <float> (rand()) / static_cast <float> (RAND_MAX / 360);

            m_pObject3d.back()->SetPossition(x, y, z);
            m_pObject3d.back()->SetRotation(rx, ry, rz);
    

      
    }


    if (m_Input->IsKeyboardBPressed(we::KEY_DELETE))
    {
     
        if (m_pObject3d.size() > 0)
        {
            delete m_pObject3d.back();
            m_pObject3d.pop_back();
        }
    }
      
    if (m_Input->IsKeyboardBPressed(we::KEY_ESCAPE))
    {
        return WE_FORCE_EXIT;
    }


    // set light position
    float lightX = glm::sin((float)(SDL_GetPerformanceCounter()) / 10000000.0f);
    float lightZ = glm::cos((float)(SDL_GetPerformanceCounter()) / 10000000.0f);
   
    m_GeneralLight.SetDirection(lightX,0.0, lightZ);
   /*for (unsigned int i = 0; i < 5000000; i++)
    {
        int x = 10;
        int y = x / 2;
    }*/

    return WE_RUNNING;


}

void MainScene::Render()
{
   
    for (auto object : m_pObject3d)
    {
        object->Draw(m_Camera, m_GeneralLight);
    }
   
}

void MainScene::Prepare()
{
    //TODO: Loading shaders, some basic textures, objects and other things that necessary for the first run and rendering
    m_Display->SetClearColor(0.5444f, 0.62f, 0.69f, 1.0f);

    const static unsigned intnumObjects = 1000;

   

    for (unsigned int i = 0; i < 1; i++)
    {
        float x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX / 300);
        float y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX / 300);
        float z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX / 300);

        float rx = static_cast <float> (rand()) / static_cast <float> (RAND_MAX / 360);
        float ry = static_cast <float> (rand()) / static_cast <float> (RAND_MAX / 360);
        float rz = static_cast <float> (rand()) / static_cast <float> (RAND_MAX / 360);

        m_pObject3d.push_back(new we::Object3D());
        m_pObject3d.back()->SetModel3D(
            we::ResourceManager::GetInstance().Hold("model", we::MODEL3D, m_pObject3d.back())
            );
        m_pObject3d.back()->SetPossition(0 ,0, 0);
        m_pObject3d.back()->SetRotation(-90, 0,0);
        //m_pObject3d.back()->SetScale(10, 10,10);
   

    }
   
}

