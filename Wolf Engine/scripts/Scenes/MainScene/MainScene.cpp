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


    if (m_Input->IsKeyboardBPressed(we::KEY_ESCAPE))
    {
        return WE_FORCE_EXIT;
    }

    std::cout << glm::degrees(camera.GetUpDirrection()).y << "\n";
}

void MainScene::Render()
{
   
   /* glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(0.0f, 1.0f);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(1.0f, -1.0f);
    glEnd();*/
  
   /*glVertex2f(0.0f, -1.0f);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(-1.0f, 1.0f);*/
 
    we::Transform transform;
    shader.Bind();
    shader.Update(transform, camera);
    mesh.Draw();
}

void MainScene::Prepare()
{
    m_Display->SetClearColor(0.5444f, 0.62f, 0.69f, 1.0f);

    we::Vertex f(0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.f, 0.0f, 0.0f, 0);
    we::Vertex s(-1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.f, 0.0f, 0.0f, 0);
    we::Vertex t(1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.f, 0.0f, 0.0f, 0);

    std::vector<unsigned int> i = { 0, 1, 2 };

    mesh = we::Mesh(std::vector<we::Vertex>{f, s, t}, i);
    

    //TODO: Loading shaders, some basic textures, objects and other things that necessary for the first run and rendering
}

