#include "MainScene.h"
//#include <Core/Engine/Engine.h>

MainScene::MainScene()
	:Scene(),
    m_Camera(glm::vec3(0.0, 0.0, -10.0), 70.0f, float(800) / float(600), 0.01f, 3000.0f)
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
    //camera.RotatePitch(0.1f);
   

   /* if (m_Input->IsKeyboardBPressed(we::KEY_W))
        m_Camera.MoveForward(0.05f * m_Display->GetDeltaTime());

    if (m_Input->IsKeyboardBPressed(we::KEY_S))
        m_Camera.MoveBack(0.05f * m_Display->GetDeltaTime());

    if (m_Input->IsKeyboardBPressed(we::KEY_A))
        m_Camera.MoveLeft(0.01f);

    if (m_Input->IsKeyboardBPressed(we::KEY_D))
        m_Camera.MoveRight(0.01f);

    if (m_Input->IsKeyboardBPressed(we::KEY_UP))
        m_Camera.RotatePitch(0.1f);

    if (m_Input->IsKeyboardBPressed(we::KEY_DOWN))
        m_Camera.RotatePitch(-0.1f);

    if (m_Input->IsKeyboardBPressed(we::KEY_LEFT))
        m_Camera.RotateYaw(0.1f);

    if (m_Input->IsKeyboardBPressed(we::KEY_RIGHT))
        m_Camera.RotateYaw(-0.1f);

    if (m_Input->IsKeyboardBPressed(we::KEY_HOME))
        m_Object3d[0].SetRotation(1.0, 0.0, 0.0);*/


    if (m_Input->IsKeyboardBPressed(we::KEY_DELETE))
    {
       /*std::map<std::string, std::map<we::Model3D*, std::vector<we::Drawable*>>> ref = we::ResourceManager::GetInstance().GetRefers();
       std::map<we::Model3D*, std::vector<we::Drawable*>> ob = ref["model"];
       we::Object3D* o = reinterpret_cast<we::Object3D*>(ob.begin()->second[0]);*/
      
       delete m_pObject3d[0];
       m_pObject3d.erase(m_pObject3d.begin());

       //we::ResourceManager::GetInstance().ResourceFree("model", we::MODEL3D);
       //we::ResourceManager::GetInstance().ResourceFree("cube", we::WE_RESOURCE::MODEL3D);
    }
      
    if (m_Input->IsKeyboardBPressed(we::KEY_ESCAPE))
    {
        return WE_FORCE_EXIT;
    }

   /*for (unsigned int i = 0; i < 5000000; i++)
    {
        int x = 10;
        int y = x / 2;
    }*/

    //std::cout << m_Display->GetDeltaTime() << "\n";
    return WE_RUNNING;

}

void MainScene::Render()
{
   
    for (auto object : m_pObject3d)
    {
        object->Draw(m_Camera);
    }
  
}

void MainScene::Prepare()
{
    //TODO: Loading shaders, some basic textures, objects and other things that necessary for the first run and rendering
    m_Display->SetClearColor(0.5444f, 0.62f, 0.69f, 1.0f);

    //TODO: find out how to get poinert to element which was initialized, back() isnt working

    //�������� ������ ������� ����, ������ �������� �������� ����������;
    //m_pObject3d.push_back(new we::Object3D());


    m_pObject3d.push_back(new we::Object3D());
    m_pObject3d.back()->SetModel3D(reinterpret_cast<we::Model3D*>(
        we::ResourceManager::GetInstance().GetResource("model", m_pObject3d[0])
        ));

    m_pObject3d.push_back(new we::Object3D());
    m_pObject3d.back()->SetModel3D(reinterpret_cast<we::Model3D*>(
        we::ResourceManager::GetInstance().GetResource("model", m_pObject3d[1])
        ));
    m_pObject3d.push_back(new we::Object3D());
    m_pObject3d.back()->SetModel3D(reinterpret_cast<we::Model3D*>(
        we::ResourceManager::GetInstance().GetResource("model", m_pObject3d[2])
        ));
  
    


}

