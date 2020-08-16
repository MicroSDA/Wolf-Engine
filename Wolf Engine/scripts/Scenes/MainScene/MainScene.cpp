#include "MainScene.h"
//#include <Core/Engine/Engine.h>

MainScene::MainScene()
	:Scene(),
    m_Camera(glm::vec3(0.0, 0.0, 0.0), 70.0f, float(1000) / float(800), 0.01f, 3000.0f)
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

    for (auto l : m_LightSources)
    {
        delete l;
    }
    m_LightSources.clear();

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

   
    float rotate = glm::sin((float)SDL_GetPerformanceCounter() / 1000000);
    //m_pObject3d[0]->SetRotation(glm::vec3(0.0, rotate, 0.0));
    //reinterpret_cast<we::SpotLight*>(m_LightSources[0])->SetDirection(0, -rotate, 0);
    //reinterpret_cast<we::SpotLight*>(m_LightSources[2])->SetDiffuseColor(1, rotate, 1);
  


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


  
    return WE_RUNNING;


}

void MainScene::Render()
{
   
    for (auto object : m_pObject3d)
    {
        object->Draw(m_Camera, m_LightSources);
    }

    we::Shader::Unbind();
   
}

void MainScene::Prepare()
{
    //TODO: Loading shaders, some basic textures, objects and other things that necessary for the first run and rendering
    m_Display->SetClearColor(0.5444f, 0.62f, 0.69f, 1.0f);

    we::GeneralLight* generalLight = new we::GeneralLight();
    we::PointLight*   pointlLight  = new we::PointLight(0);
    we::SpotLight*    spotLight    = new we::SpotLight(0);


    generalLight->SetDiffuseColor(1.0, 1.0, 1.0);
    generalLight->SetAmbientColor(0.0f, 0.0f, 0.0f);
    pointlLight->SetPosition(0, 0, -100);
    pointlLight->SetConstant(0.1f);
    pointlLight->SetLinear(0.1);
    pointlLight->SetQaudratic(0.01);

    spotLight->SetPosition(0, 0, -9);
    spotLight->SetConstant(0.1f);
    spotLight->SetLinear(0.01);
    spotLight->SetQaudratic(0.001);

   
    m_LightSources.push_back(generalLight);
    //m_LightSources.push_back(pointlLight);
    //m_LightSources.push_back(spotLight);

    //reinterpret_cast<we::PointLight*>(m_LightSources[0])->SetPosition(0, 0, -20);
   
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
            we::ResourceManager::GetInstance().Hold("cube", we::MODEL3D, m_pObject3d.back())
            );
        m_pObject3d.back()->SetPossition(0, 0, 5);
        m_pObject3d.back()->SetRotation(0, 180,0);
        //m_pObject3d.back()->SetScale(10, 10, 10);
   

    }
   
}

