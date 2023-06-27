#include "imgui/imgui.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "TestPlayground.h"
#include "Renderer.h"
#include <string>




namespace test {

    test::TestPlayground::TestPlayground(GLFWwindow* window)
        :m_Proj(glm::perspective(1.0f, 960.0f / 540.0f, 0.1f, 100.0f)),
        m_View(glm::rotate(glm::mat4(1.0f), glm::radians(60.0f), glm::vec3(1.0f, 0.0f, 0.0f))),
        m_Rotation(glm::vec3(0.0f, 0.0f, 0.0f)), m_Slider(0), m_Window(window)
    {
        m_View = glm::translate(m_View, glm::vec3(-2.0f , -7.0f ,-22.0f ));
        m_MainChar.m_ModelMatrix = glm::translate(m_MainChar.m_ModelMatrix, glm::vec3(1.2f, 2.0f, 17.6f));
        m_MainChar.m_ModelMatrix = glm::scale(m_MainChar.m_ModelMatrix, glm::vec3(0.30f, 0.30f, 0.30f));
        
        m_MainChar.m_CenterPos.x = 1;
        m_MainChar.m_CenterPos.y = 1;
        m_MainChar.m_CenterPos.z = 18;
        float w = 960.0f;
        float h = 540.0f;
        for (int i = 0; i < sizeof(m_random) / 4; i++)
        {

            int aux = rand() % 14 + 1;
            if (aux > 8)
                m_random[i] = 0;
            else
                m_random[i] = aux;
        }
        m_Texture = std::make_unique<Texture>("res/textures/Testure.png");
        std::string nomFitxer = "res/Models/Tile1_11/Tile1_11.obj";

        m_ObOBJ[0].LoadModel(const_cast<char*>(nomFitxer.c_str()));
        nomFitxer = "res/Models/Tile1_12/Tile1_12.obj";
        m_ObOBJ[1].LoadModel(const_cast<char*>(nomFitxer.c_str()));
        nomFitxer = "res/Models/Tile1_13/Tile1_13.obj";
        m_ObOBJ[2].LoadModel(const_cast<char*>(nomFitxer.c_str()));
        nomFitxer = "res/Models/Tile1_14/Tile1_14.obj";
        m_ObOBJ[3].LoadModel(const_cast<char*>(nomFitxer.c_str()));
        nomFitxer = "res/Models/Tile1_21/Tile1_21.obj";
        m_ObOBJ[4].LoadModel(const_cast<char*>(nomFitxer.c_str()));
        nomFitxer = "res/Models/Tile1_22/Tile1_22.obj";
        m_ObOBJ[5].LoadModel(const_cast<char*>(nomFitxer.c_str()));
        nomFitxer = "res/Models/Tile1_23/Tile1_23.obj";
        m_ObOBJ[6].LoadModel(const_cast<char*>(nomFitxer.c_str()));
        nomFitxer = "res/Models/Tile1_24/Tile1_24.obj";
        m_ObOBJ[7].LoadModel(const_cast<char*>(nomFitxer.c_str()));
        nomFitxer = "res/Models/Tile1_B/Tile1_B.obj";
        m_ObOBJ[8].LoadModel(const_cast<char*>(nomFitxer.c_str()));
        nomFitxer = "res/Models/Tile1_M/Tile1_M.obj";
        m_ObOBJ[9].LoadModel(const_cast<char*>(nomFitxer.c_str()));
        nomFitxer = "res/Models/Tile1_R/Readable.obj";
        m_ObOBJ[10].LoadModel(const_cast<char*>(nomFitxer.c_str()));
        nomFitxer = "res/Models/ReadableText/ReadableText.obj";
        m_ObOBJ[11].LoadModel(const_cast<char*>(nomFitxer.c_str()));
        /*
        VertexBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(2);
        m_VAO->AddBuffer(*m_VertexBuffer, layout);
        m_VAO1->AddBuffer(*m_VertexBuffer1, layout);
        */
        //m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 12);



        GLCall(glEnable(GL_BLEND));

        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
        GLCall(glShadeModel(GL_SMOOTH));
        //lights

        GLfloat position[] = { 0.0,0.0,200.0,1.0 };

        int i = 0;
        for (i = 1; i < 8; i++) m_Lumin[i].encesa = false;
        for (i = 0; i < 8; i++) {
            m_Lumin[i].encesa = false;
            m_Lumin[i].difusa[0] = 1.0f;	m_Lumin[i].difusa[1] = 1.0f;	m_Lumin[i].difusa[2] = 1.0f;	m_Lumin[i].difusa[3] = 1.0f;
            m_Lumin[i].especular[0] = 1.0f; m_Lumin[i].especular[1] = 1.0f; m_Lumin[i].especular[2] = 1.0f; m_Lumin[i].especular[3] = 1.0f;
        }

        // LLum 0: Atenuaci� constant (c=1), sobre l'eix Z, no restringida.
        m_Lumin[0].encesa = true;
        m_Lumin[0].difusa[0] = 1.0f;			m_Lumin[0].difusa[1] = 1.0f;			m_Lumin[0].difusa[2] = 1.0f;		m_Lumin[0].difusa[3] = 1.0f;
        m_Lumin[0].especular[0] = 1.0f;		m_Lumin[0].especular[1] = 1.0f;		m_Lumin[0].especular[2] = 1.0f;	m_Lumin[0].especular[3] = 1.0f;

        m_Lumin[0].posicio.R = 200.0;		m_Lumin[0].posicio.alfa = 90.0;		m_Lumin[0].posicio.beta = 0.0;		// Posici� llum (x,y,z)=(0,0,200)
        m_Lumin[0].atenuacio.a = 0.0;		m_Lumin[0].atenuacio.b = 0.0;		m_Lumin[0].atenuacio.c = 1.0;		// Llum sense atenuaci� per dist�ncia (a,b,c)=(0,0,1)
        m_Lumin[0].restringida = false;
        m_Lumin[0].spotdirection[0] = 0.0;	m_Lumin[0].spotdirection[1] = 0.0;	m_Lumin[0].spotdirection[2] = 0.0;
        m_Lumin[0].spotcoscutoff = 0.0;		m_Lumin[0].spotexponent = 0.0;

        // LLum 1: Atenuaci� constant (c=1), sobre l'eix X, no restringida.
        m_Lumin[1].encesa = false;
        m_Lumin[1].difusa[0] = 1.0f;			m_Lumin[1].difusa[1] = 1.0f;			m_Lumin[1].difusa[2] = 1.0f;		m_Lumin[1].difusa[3] = 1.0f;
        m_Lumin[1].especular[0] = 1.0f;		m_Lumin[1].especular[1] = 1.0f;		m_Lumin[1].especular[2] = 1.0f;	m_Lumin[1].especular[3] = 1;

        m_Lumin[1].posicio.R = 75.0;			m_Lumin[1].posicio.alfa = 0.0;		m_Lumin[1].posicio.beta = 0.0;// (x,y,z)=(75,0,0)
        m_Lumin[1].atenuacio.a = 0.0;		m_Lumin[1].atenuacio.b = 0.0;		m_Lumin[1].atenuacio.c = 1.0;
        m_Lumin[1].restringida = false;
        m_Lumin[1].spotdirection[0] = 0.0;	m_Lumin[1].spotdirection[1] = 0.0;	m_Lumin[1].spotdirection[2] = 0.0;
        m_Lumin[1].spotcoscutoff = 0.0;		m_Lumin[1].spotexponent = 0.0;

        // LLum 2: Atenuaci� constant (c=1), sobre l'eix Y, no restringida.
        m_Lumin[2].encesa = false;
        m_Lumin[2].difusa[1] = 1.0f;			m_Lumin[2].difusa[1] = 1.0f;			m_Lumin[2].difusa[2] = 1.0f;		m_Lumin[2].difusa[3] = 1.0f;
        m_Lumin[2].especular[1] = 1.0f;		m_Lumin[2].especular[1] = 1.0f;		m_Lumin[2].especular[2] = 1.0f;	m_Lumin[2].especular[3] = 1;

        m_Lumin[2].posicio.R = 75.0;			m_Lumin[2].posicio.alfa = 0.0;		m_Lumin[2].posicio.beta = 90.0;	// (x,y,z)=(0,75,0)
        m_Lumin[2].atenuacio.a = 0.0;		m_Lumin[2].atenuacio.b = 0.0;		m_Lumin[2].atenuacio.c = 1.0;
        m_Lumin[2].restringida = false;
        m_Lumin[2].spotdirection[0] = 0.0;	m_Lumin[2].spotdirection[1] = 0.0;	m_Lumin[2].spotdirection[2] = 0.0;
        m_Lumin[2].spotcoscutoff = 0.0;		m_Lumin[2].spotexponent = 0.0;

        // LLum 3: Atenuaci� constant (c=1), sobre l'eix Y=X, no restringida.
        m_Lumin[3].encesa = false;
        m_Lumin[3].difusa[0] = 1.0f;			m_Lumin[2].difusa[1] = 1.0f;			m_Lumin[3].difusa[2] = 1.0f;		m_Lumin[3].difusa[3] = 1.0f;
        m_Lumin[3].especular[0] = 1.0f;		m_Lumin[2].especular[1] = 1.0f;		m_Lumin[3].especular[2] = 1.0f;	m_Lumin[3].especular[3] = 1;

        m_Lumin[3].posicio.R = 75.0;			m_Lumin[3].posicio.alfa = 45.0;		m_Lumin[3].posicio.beta = 45.0;// (x,y,z)=(75,75,75)
        m_Lumin[3].atenuacio.a = 0.0;		m_Lumin[3].atenuacio.b = 0.0;		m_Lumin[3].atenuacio.c = 1.0;
        m_Lumin[3].restringida = false;
        m_Lumin[3].spotdirection[0] = 0.0;	m_Lumin[3].spotdirection[1] = 0.0;	m_Lumin[3].spotdirection[2] = 0.0;
        m_Lumin[3].spotcoscutoff = 0.0;		m_Lumin[3].spotexponent = 0.0;

        // LLum 4: Atenuaci� constant (c=1), sobre l'eix -Z, no restringida.
        m_Lumin[4].encesa = false;
        m_Lumin[4].difusa[0] = 1.0f;			m_Lumin[4].difusa[1] = 1.0f;			m_Lumin[4].difusa[2] = 1.0f;		m_Lumin[4].difusa[3] = 1.0f;
        m_Lumin[4].especular[0] = 1.0f;		m_Lumin[4].especular[1] = 1.0f;		m_Lumin[4].especular[2] = 1.0f;	m_Lumin[4].especular[3] = 1;

        m_Lumin[4].posicio.R = 75.0;			m_Lumin[4].posicio.alfa = -90.0;		m_Lumin[4].posicio.beta = 0.0;// (x,y,z)=(0,0,-75)
        m_Lumin[4].atenuacio.a = 0.0;		m_Lumin[4].atenuacio.b = 0.0;		m_Lumin[4].atenuacio.c = 1.0;
        m_Lumin[4].restringida = false;
        m_Lumin[4].spotdirection[0] = 0.0;	m_Lumin[4].spotdirection[1] = 0.0;	m_Lumin[4].spotdirection[2] = 0.0;
        m_Lumin[4].spotcoscutoff = 0.0;		m_Lumin[4].spotexponent = 0.0;

        // LLum #5:
        m_Lumin[5].encesa = false;
        m_Lumin[5].difusa[0] = 1.0f;			m_Lumin[5].difusa[1] = 1.0f;			m_Lumin[5].difusa[2] = 1.0f;		m_Lumin[5].difusa[3] = 1.0f;
        m_Lumin[5].especular[0] = 1.0f;		m_Lumin[5].especular[1] = 1.0f;		m_Lumin[5].especular[2] = 1.0f;	m_Lumin[5].especular[3] = 1;

        m_Lumin[5].posicio.R = 0.0;			m_Lumin[5].posicio.alfa = 0.0;		m_Lumin[5].posicio.beta = 0.0; // Cap posici� definida
        m_Lumin[5].atenuacio.a = 0.0;		m_Lumin[5].atenuacio.b = 0.0;		m_Lumin[5].atenuacio.c = 1.0;
        m_Lumin[5].restringida = false;
        m_Lumin[5].spotdirection[0] = 0.0;	m_Lumin[5].spotdirection[1] = 0.0;	m_Lumin[5].spotdirection[2] = 0.0;
        m_Lumin[5].spotcoscutoff = 0.0;		m_Lumin[5].spotexponent = 0.0;

        // LLum #6: Llum Vaixell, configurada a la funci� vaixell() en escena.cpp.
        m_Lumin[6].encesa = false;
        m_Lumin[6].difusa[0] = 1.0f;			m_Lumin[6].difusa[1] = 1.0f;			m_Lumin[6].difusa[2] = 1.0f;		m_Lumin[6].difusa[3] = 1.0f;
        m_Lumin[6].especular[0] = 1.0f;		m_Lumin[6].especular[1] = 1.0f;		m_Lumin[6].especular[2] = 1.0f;	m_Lumin[6].especular[3] = 1;

        m_Lumin[6].posicio.R = 0.0;			m_Lumin[6].posicio.alfa = 0.0;		m_Lumin[6].posicio.beta = 0.0; // Cap posici� definida, definida en funci� vaixell() en escena.cpp
        m_Lumin[6].atenuacio.a = 0.0;		m_Lumin[6].atenuacio.b = 0.0;		m_Lumin[6].atenuacio.c = 1.0;
        m_Lumin[6].restringida = false;
        m_Lumin[6].spotdirection[0] = 0.0;	m_Lumin[6].spotdirection[1] = 0.0;	m_Lumin[6].spotdirection[2] = 0.0;
        m_Lumin[6].spotcoscutoff = 0.0;		m_Lumin[6].spotexponent = 0.0;

        // LLum #7: Llum Far, configurada a la funci� faro() en escena.cpp.
        m_Lumin[7].encesa = false;
        m_Lumin[7].difusa[0] = 1.0f;			m_Lumin[7].difusa[1] = 1.0f;			m_Lumin[7].difusa[2] = 1.0f;		m_Lumin[7].difusa[3] = 1.0f;
        m_Lumin[7].especular[0] = 1.0f;		m_Lumin[7].especular[1] = 1.0f;		m_Lumin[7].especular[2] = 1.0f;	m_Lumin[7].especular[3] = 1;

        m_Lumin[7].posicio.R = 0.0;			m_Lumin[7].posicio.alfa = 0.0;		m_Lumin[7].posicio.beta = 0.0; // Cap posici� definida, definida en funci� faro() en escena.cpp
        m_Lumin[7].atenuacio.a = 0.0;		m_Lumin[7].atenuacio.b = 0.0;		m_Lumin[7].atenuacio.c = 1.0;
        m_Lumin[7].restringida = false;
        m_Lumin[7].spotdirection[0] = 0.0;	m_Lumin[7].spotdirection[1] = 0.0;	m_Lumin[7].spotdirection[2] = 0.0;
        m_Lumin[7].spotcoscutoff = 0.0;		m_Lumin[7].spotexponent = 0.0;

        //m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 12);

        std::vector<char*> presets;
        char a1[192] =
        {

            '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',
            '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',
            '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',
            '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',
            '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',
            '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',
            '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',
            '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',

            '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',
            '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',
            '0',  '0',  '0',  '0',  '0',  '1',  '0',  '0',
            '0',  '0',  '0',  '0',  '0',  '1',  '0',  '0',
            '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',
            '0',  '0',  '0',  '0',  '0',  '1',  '0',  '0',
            '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',
            '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',

            '1',  '1',  '1',  '1',  '1',  '1',  '1',  '1',
            '1',  '1',  '1',  '1',  '1',  '1',  '1',  '1',
            '1',  '1',  '1',  '1',  '1',  '1',  '1',  '1',
            '1',  '1',  '1',  '4',  '5',  '1',  '1',  '1',
            '1',  '1',  '1',  '1',  '1',  '1',  '1',  '1',
            '1',  '1',  '1',  '1',  '1',  '1',  '1',  '1',
            '1',  '1',  '1',  '1',  '1',  '1',  '1',  '1',
            '1',  '1',  '1',  '1',  '1',  '1',  '1',  '1'

        };
        presets.push_back(a1);
        /*
        char a2[192] = {

            '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',
            '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',
            '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',
            '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',
            '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',
            '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',
            '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',
            '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0'
        ,

            '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',
            '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',
            '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',
            '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',
            '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',
            '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',
            '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',
            '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0'
        ,

            '0',  '0',  '0',  '1',  '0',  '0',  '0',  '0',
            '0',  '0',  '0',  '1',  '0',  '0',  '0',  '0',
            '0',  '0',  '0',  '1',  '0',  '0',  '0',  '0',
            '1',  '1',  '1',  '1',  '1',  '0',  '0',  '0',
            '0',  '0',  '0',  '1',  '1',  '1',  '1',  '1',
            '0',  '0',  '0',  '1',  '0',  '0',  '0',  '0',
            '0',  '0',  '0',  '1',  '0',  '0',  '0',  '0',
            '0',  '0',  '0',  '1',  '0',  '0',  '0',  '0'

        };
        
        presets.push_back(a2);
        
        char a3[192] = {

            '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',
            '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',
            '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',
            '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',
            '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',
            '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',
            '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',
            '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0'
        ,

            '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',
            '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',
            '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',
            '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',
            '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',
            '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',
            '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',
            '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0'
        ,

            '1',  '1',  '1',  '1',  '1',  '1',  '1',  '1',
            '1',  '0',  '0',  '0',  '0',  '0',  '0',  '1',
            '1',  '0',  '0',  '0',  '0',  '0',  '0',  '1',
            '1',  '0',  '0',  '1',  '1',  '0',  '0',  '1',
            '1',  '0',  '0',  '1',  '1',  '0',  '0',  '1',
            '1',  '0',  '0',  '0',  '0',  '0',  '0',  '1',
            '1',  '0',  '0',  '0',  '0',  '0',  '0',  '1',
            '1',  '1',  '1',  '1',  '1',  '1',  '1',  '1'

        };
        presets.push_back(a3);
        */
        char a4[192] = {

        '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',
        '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',
        '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',
        '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',
        '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',
        '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',
        '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',
        '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0'
    ,

        '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',
        '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',
        '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',
        '0',  '0',  '0',  '1',  '6',  '0',  '0',  '0',
        '0',  '0',  '0',  '1',  '1',  '0',  '0',  '0',
        '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',
        '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',
        '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0'
    ,

        '1',  '1',  '0',  '0',  '0',  '0',  '1',  '1',
        '1',  '0',  '0',  '0',  '0',  '0',  '0',  '1',
        '2',  '0',  '0',  '0',  '0',  '0',  '0',  '0',
        '2',  '4',  '5',  '1',  '1',  '3',  '0',  '0',
        '2',  '4',  '5',  '1',  '1',  '3',  '0',  '0',
        '2',  '0',  '0',  '0',  '0',  '0',  '0',  '0',
        '1',  '0',  '0',  '0',  '0',  '0',  '0',  '1',
        '1',  '1',  '0',  '0',  '0',  '0',  '1',  '1'

        };


        presets.push_back(a4);

        m_Board = std::make_unique<Board>('0', ((char*)malloc((2 * 25 * 10) * 10 * 3 * sizeof(char))), presets);
        m_Board->genBoard(); //<3
        m_Shader = std::make_unique<Shader>("res/Shaders/Phong.shader");
        m_Shader->Bind();
        GLfloat ambientg[] = { .5,.5,.5,1.0 };

        GLCall(glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientg));
        m_Shader->SetUniform1i("fixedLight", true);
        m_Shader->SetUniform1i("textur", true);
        m_Shader->SetUniform1i("flag_invert_y", false);
        m_Shader->SetUniform1i("fixedLight", true); //
        m_Shader->SetUniform4f("LightModelAmbient", ambientg[0], ambientg[1], ambientg[2], ambientg[3]);
    }

    test::TestPlayground::~TestPlayground()
    {

    }

    void test::TestPlayground::OnUpdate(float deltaTime)
    {
    }

    void test::TestPlayground::OnRender()
    {
        m_Shader->Bind();
        GLCall(glClearColor(0.4f, 0.4f, 0.8f, 1.0f));
        GLCall(glEnable(GL_DEPTH_TEST));
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
        Renderer renderer;
        GLdouble angv, angh;
        GLfloat position[] = { 0.0,0.0,200.0,1.0 };
        angv = m_Lumin[0].posicio.alfa * 3.14159 / 180;
        angh = m_Lumin[0].posicio.beta * 3.14159 / 180;

        // Conversi� Coord. esf�riques -> Coord. cartesianes per a la posici� de la llum
        position[0] = m_Lumin[0].posicio.R * cos(angh) * cos(angv);
        position[1] = m_Lumin[0].posicio.R * sin(angh) * cos(angv);
        position[2] = m_Lumin[0].posicio.R * sin(angv);
        position[3] = 1.0;

        glUniform4f(glGetUniformLocation(m_Shader->GetID(), "LightSource[0].position"), position[0], position[1], position[2], position[3]);
        glUniform4f(glGetUniformLocation(m_Shader->GetID(), "LightSource[0].diffuse"), m_Lumin[0].difusa[0], m_Lumin[0].difusa[1], m_Lumin[0].difusa[2], m_Lumin[0].difusa[3]);
        glUniform4f(glGetUniformLocation(m_Shader->GetID(), "LightSource[0].specular"), m_Lumin[0].especular[0], m_Lumin[0].especular[1], m_Lumin[0].especular[2], m_Lumin[0].especular[3]);
        glUniform3f(glGetUniformLocation(m_Shader->GetID(), "LightSource[0].attenuation"), m_Lumin[0].atenuacio.a, m_Lumin[0].atenuacio.b, m_Lumin[0].atenuacio.c);
        glUniform1i(glGetUniformLocation(m_Shader->GetID(), "LightSource[0].restricted"), m_Lumin[0].restringida);
        glUniform3f(glGetUniformLocation(m_Shader->GetID(), "LightSource[0].spotDirection"), m_Lumin[0].spotdirection[0], m_Lumin[0].spotdirection[1], m_Lumin[0].spotdirection[2]);
        glUniform1f(glGetUniformLocation(m_Shader->GetID(), "LightSource[0].spotCosCutoff"), m_Lumin[0].spotcoscutoff);
        glUniform1f(glGetUniformLocation(m_Shader->GetID(), "LightSource[0].spotExponent"), m_Lumin[0].spotexponent);
        glUniform1i(glGetUniformLocation(m_Shader->GetID(), "LightSource[0].sw_light"), m_Lumin[0].encesa);

        angv = m_Lumin[1].posicio.alfa * 3.14159 / 180;
        angh = m_Lumin[1].posicio.beta * 3.14159 / 180;

        // Conversi� Coord. esf�riques -> Coord. cartesianes per a la posici� de la llum
        position[0] = m_Lumin[1].posicio.R * cos(angh) * cos(angv);
        position[1] = m_Lumin[1].posicio.R * sin(angh) * cos(angv);
        position[2] = m_Lumin[1].posicio.R * sin(angv);
        position[3] = 1.0;

        glUniform4f(glGetUniformLocation(m_Shader->GetID(), "LightSource[1].position"), position[0], position[1], position[2], position[3]);
        glUniform4f(glGetUniformLocation(m_Shader->GetID(), "LightSource[1].diffuse"), m_Lumin[1].difusa[0], m_Lumin[1].difusa[1], m_Lumin[1].difusa[2], m_Lumin[1].difusa[3]);
        glUniform4f(glGetUniformLocation(m_Shader->GetID(), "LightSource[1].specular"), m_Lumin[1].especular[0], m_Lumin[1].especular[1], m_Lumin[1].especular[2], m_Lumin[1].especular[3]);
        glUniform3f(glGetUniformLocation(m_Shader->GetID(), "LightSource[1].attenuation"), m_Lumin[1].atenuacio.a, m_Lumin[1].atenuacio.b, m_Lumin[1].atenuacio.c);
        glUniform1i(glGetUniformLocation(m_Shader->GetID(), "LightSource[1].restricted"), m_Lumin[1].restringida);
        glUniform3f(glGetUniformLocation(m_Shader->GetID(), "LightSource[1].spotDirection"), m_Lumin[1].spotdirection[0], m_Lumin[1].spotdirection[1], m_Lumin[1].spotdirection[2]);
        glUniform1f(glGetUniformLocation(m_Shader->GetID(), "LightSource[1].spotCosCutoff"), m_Lumin[1].spotcoscutoff);
        glUniform1f(glGetUniformLocation(m_Shader->GetID(), "LightSource[1].spotExponent"), m_Lumin[1].spotexponent);
        glUniform1i(glGetUniformLocation(m_Shader->GetID(), "LightSource[1].sw_light"), m_Lumin[1].encesa);

        angv = m_Lumin[2].posicio.alfa * 3.14159 / 180;
        angh = m_Lumin[2].posicio.beta * 3.14159 / 180;

        // Conversi� Coord. esf�riques -> Coord. cartesianes per a la posici� de la llum
        position[0] = m_Lumin[2].posicio.R * cos(angh) * cos(angv);
        position[1] = m_Lumin[2].posicio.R * sin(angh) * cos(angv);
        position[2] = m_Lumin[2].posicio.R * sin(angv);
        position[3] = 1.0;

        glUniform4f(glGetUniformLocation(m_Shader->GetID(), "LightSource[2].position"), position[0], position[1], position[2], position[3]);
        glUniform4f(glGetUniformLocation(m_Shader->GetID(), "LightSource[2].diffuse"), m_Lumin[2].difusa[0], m_Lumin[2].difusa[1], m_Lumin[2].difusa[2], m_Lumin[2].difusa[3]);
        glUniform4f(glGetUniformLocation(m_Shader->GetID(), "LightSource[2].specular"), m_Lumin[2].especular[0], m_Lumin[2].especular[1], m_Lumin[2].especular[2], m_Lumin[2].especular[3]);
        glUniform3f(glGetUniformLocation(m_Shader->GetID(), "LightSource[2].attenuation"), m_Lumin[2].atenuacio.a, m_Lumin[2].atenuacio.b, m_Lumin[2].atenuacio.c);
        glUniform1i(glGetUniformLocation(m_Shader->GetID(), "LightSource[2].restricted"), m_Lumin[2].restringida);
        glUniform3f(glGetUniformLocation(m_Shader->GetID(), "LightSource[2].spotDirection"), m_Lumin[2].spotdirection[0], m_Lumin[2].spotdirection[1], m_Lumin[2].spotdirection[2]);
        glUniform1f(glGetUniformLocation(m_Shader->GetID(), "LightSource[2].spotCosCutoff"), m_Lumin[2].spotcoscutoff);
        glUniform1f(glGetUniformLocation(m_Shader->GetID(), "LightSource[2].spotExponent"), m_Lumin[2].spotexponent);
        glUniform1i(glGetUniformLocation(m_Shader->GetID(), "LightSource[2].sw_light"), m_Lumin[2].encesa);

        angv = m_Lumin[3].posicio.alfa * 3.14159 / 180;
        angh = m_Lumin[3].posicio.beta * 3.14159 / 180;

        // Conversi� Coord. esf�riques -> Coord. cartesianes per a la posici� de la llum
        position[0] = m_Lumin[3].posicio.R * cos(angh) * cos(angv);
        position[1] = m_Lumin[3].posicio.R * sin(angh) * cos(angv);
        position[2] = m_Lumin[3].posicio.R * sin(angv);
        position[3] = 1.0;

        glUniform4f(glGetUniformLocation(m_Shader->GetID(), "LightSource[3].position"), position[0], position[1], position[2], position[3]);
        glUniform4f(glGetUniformLocation(m_Shader->GetID(), "LightSource[3].diffuse"), m_Lumin[3].difusa[0], m_Lumin[3].difusa[1], m_Lumin[3].difusa[2], m_Lumin[3].difusa[3]);
        glUniform4f(glGetUniformLocation(m_Shader->GetID(), "LightSource[3].specular"), m_Lumin[3].especular[0], m_Lumin[3].especular[1], m_Lumin[3].especular[2], m_Lumin[3].especular[3]);
        glUniform3f(glGetUniformLocation(m_Shader->GetID(), "LightSource[3].attenuation"), m_Lumin[3].atenuacio.a, m_Lumin[3].atenuacio.b, m_Lumin[3].atenuacio.c);
        glUniform1i(glGetUniformLocation(m_Shader->GetID(), "LightSource[3].restricted"), m_Lumin[3].restringida);
        glUniform3f(glGetUniformLocation(m_Shader->GetID(), "LightSource[3].spotDirection"), m_Lumin[3].spotdirection[0], m_Lumin[3].spotdirection[1], m_Lumin[3].spotdirection[2]);
        glUniform1f(glGetUniformLocation(m_Shader->GetID(), "LightSource[3].spotCosCutoff"), m_Lumin[3].spotcoscutoff);
        glUniform1f(glGetUniformLocation(m_Shader->GetID(), "LightSource[3].spotExponent"), m_Lumin[3].spotexponent);
        glUniform1i(glGetUniformLocation(m_Shader->GetID(), "LightSource[3].sw_light"), m_Lumin[3].encesa);

        angv = m_Lumin[4].posicio.alfa * 3.14159 / 180;
        angh = m_Lumin[4].posicio.beta * 3.14159 / 180;

        // Conversi� Coord. esf�riques -> Coord. cartesianes per a la posici� de la llum
        position[0] = m_Lumin[4].posicio.R * cos(angh) * cos(angv);
        position[1] = m_Lumin[4].posicio.R * sin(angh) * cos(angv);
        position[2] = m_Lumin[4].posicio.R * sin(angv);
        position[3] = 1.0;

        glUniform4f(glGetUniformLocation(m_Shader->GetID(), "LightSource[4].position"), position[0], position[1], position[2], position[3]);
        glUniform4f(glGetUniformLocation(m_Shader->GetID(), "LightSource[4].diffuse"), m_Lumin[4].difusa[0], m_Lumin[4].difusa[1], m_Lumin[4].difusa[2], m_Lumin[4].difusa[3]);
        glUniform4f(glGetUniformLocation(m_Shader->GetID(), "LightSource[4].specular"), m_Lumin[4].especular[0], m_Lumin[4].especular[1], m_Lumin[4].especular[2], m_Lumin[4].especular[3]);
        glUniform3f(glGetUniformLocation(m_Shader->GetID(), "LightSource[4].attenuation"), m_Lumin[4].atenuacio.a, m_Lumin[4].atenuacio.b, m_Lumin[4].atenuacio.c);
        glUniform1i(glGetUniformLocation(m_Shader->GetID(), "LightSource[4].restricted"), m_Lumin[4].restringida);
        glUniform3f(glGetUniformLocation(m_Shader->GetID(), "LightSource[4].spotDirection"), m_Lumin[4].spotdirection[0], m_Lumin[4].spotdirection[1], m_Lumin[4].spotdirection[2]);
        glUniform1f(glGetUniformLocation(m_Shader->GetID(), "LightSource[4].spotCosCutoff"), m_Lumin[4].spotcoscutoff);
        glUniform1f(glGetUniformLocation(m_Shader->GetID(), "LightSource[4].spotExponent"), m_Lumin[4].spotexponent);
        glUniform1i(glGetUniformLocation(m_Shader->GetID(), "LightSource[4].sw_light"), m_Lumin[4].encesa);

        angv = m_Lumin[5].posicio.alfa * 3.14159 / 180;
        angh = m_Lumin[5].posicio.beta * 3.14159 / 180;

        // Conversi� Coord. esf�riques -> Coord. cartesianes per a la posici� de la llum
        position[0] = m_Lumin[5].posicio.R * cos(angh) * cos(angv);
        position[1] = m_Lumin[5].posicio.R * sin(angh) * cos(angv);
        position[2] = m_Lumin[5].posicio.R * sin(angv);
        position[3] = 1.0;

        glUniform4f(glGetUniformLocation(m_Shader->GetID(), "LightSource[5].position"), position[0], position[1], position[2], position[3]);
        glUniform4f(glGetUniformLocation(m_Shader->GetID(), "LightSource[5].diffuse"), m_Lumin[5].difusa[0], m_Lumin[5].difusa[1], m_Lumin[5].difusa[2], m_Lumin[5].difusa[3]);
        glUniform4f(glGetUniformLocation(m_Shader->GetID(), "LightSource[5].specular"), m_Lumin[5].especular[0], m_Lumin[5].especular[1], m_Lumin[5].especular[2], m_Lumin[5].especular[3]);
        glUniform3f(glGetUniformLocation(m_Shader->GetID(), "LightSource[5].attenuation"), m_Lumin[5].atenuacio.a, m_Lumin[5].atenuacio.b, m_Lumin[5].atenuacio.c);
        glUniform1i(glGetUniformLocation(m_Shader->GetID(), "LightSource[5].restricted"), m_Lumin[5].restringida);
        glUniform3f(glGetUniformLocation(m_Shader->GetID(), "LightSource[5].spotDirection"), m_Lumin[5].spotdirection[0], m_Lumin[5].spotdirection[1], m_Lumin[5].spotdirection[2]);
        glUniform1f(glGetUniformLocation(m_Shader->GetID(), "LightSource[5].spotCosCutoff"), m_Lumin[5].spotcoscutoff);
        glUniform1f(glGetUniformLocation(m_Shader->GetID(), "LightSource[5].spotExponent"), m_Lumin[5].spotexponent);
        glUniform1i(glGetUniformLocation(m_Shader->GetID(), "LightSource[5].sw_light"), m_Lumin[5].encesa);

        angv = m_Lumin[6].posicio.alfa * 3.14159 / 180;
        angh = m_Lumin[6].posicio.beta * 3.14159 / 180;

        // Conversi� Coord. esf�riques -> Coord. cartesianes per a la posici� de la llum
        position[0] = m_Lumin[6].posicio.R * cos(angh) * cos(angv);
        position[1] = m_Lumin[6].posicio.R * sin(angh) * cos(angv);
        position[2] = m_Lumin[6].posicio.R * sin(angv);
        position[3] = 1.0;

        glUniform4f(glGetUniformLocation(m_Shader->GetID(), "LightSource[6].position"), position[0], position[1], position[2], position[3]);
        glUniform4f(glGetUniformLocation(m_Shader->GetID(), "LightSource[6].diffuse"), m_Lumin[6].difusa[0], m_Lumin[6].difusa[1], m_Lumin[6].difusa[2], m_Lumin[6].difusa[3]);
        glUniform4f(glGetUniformLocation(m_Shader->GetID(), "LightSource[6].specular"), m_Lumin[6].especular[0], m_Lumin[6].especular[1], m_Lumin[6].especular[2], m_Lumin[6].especular[3]);
        glUniform3f(glGetUniformLocation(m_Shader->GetID(), "LightSource[6].attenuation"), m_Lumin[6].atenuacio.a, m_Lumin[6].atenuacio.b, m_Lumin[6].atenuacio.c);
        glUniform1i(glGetUniformLocation(m_Shader->GetID(), "LightSource[6].restricted"), m_Lumin[6].restringida);
        glUniform3f(glGetUniformLocation(m_Shader->GetID(), "LightSource[6].spotDirection"), m_Lumin[6].spotdirection[0], m_Lumin[6].spotdirection[1], m_Lumin[6].spotdirection[2]);
        glUniform1f(glGetUniformLocation(m_Shader->GetID(), "LightSource[6].spotCosCutoff"), m_Lumin[6].spotcoscutoff);
        glUniform1f(glGetUniformLocation(m_Shader->GetID(), "LightSource[6].spotExponent"), m_Lumin[6].spotexponent);
        glUniform1i(glGetUniformLocation(m_Shader->GetID(), "LightSource[6].sw_light"), m_Lumin[6].encesa);

        angv = m_Lumin[6].posicio.alfa * 3.14159 / 180;
        angh = m_Lumin[6].posicio.beta * 3.14159 / 180;

        // Conversi� Coord. esf�riques -> Coord. cartesianes per a la posici� de la llum
        position[0] = m_Lumin[0].posicio.R * cos(angh) * cos(angv);
        position[1] = m_Lumin[0].posicio.R * sin(angh) * cos(angv);
        position[2] = m_Lumin[0].posicio.R * sin(angv);
        position[3] = 1.0;

        glUniform4f(glGetUniformLocation(m_Shader->GetID(), "LightSource[7].position"), position[0], position[1], position[2], position[3]);
        glUniform4f(glGetUniformLocation(m_Shader->GetID(), "LightSource[7].diffuse"), m_Lumin[0].difusa[0], m_Lumin[0].difusa[1], m_Lumin[0].difusa[2], m_Lumin[0].difusa[3]);
        glUniform4f(glGetUniformLocation(m_Shader->GetID(), "LightSource[7].specular"), m_Lumin[0].especular[0], m_Lumin[0].especular[1], m_Lumin[0].especular[2], m_Lumin[0].especular[3]);
        glUniform3f(glGetUniformLocation(m_Shader->GetID(), "LightSource[7].attenuation"), m_Lumin[0].atenuacio.a, m_Lumin[0].atenuacio.b, m_Lumin[0].atenuacio.c);
        glUniform1i(glGetUniformLocation(m_Shader->GetID(), "LightSource[7].restricted"), m_Lumin[0].restringida);
        glUniform3f(glGetUniformLocation(m_Shader->GetID(), "LightSource[7].spotDirection"), m_Lumin[0].spotdirection[0], m_Lumin[0].spotdirection[1], m_Lumin[0].spotdirection[2]);
        glUniform1f(glGetUniformLocation(m_Shader->GetID(), "LightSource[7].spotCosCutoff"), m_Lumin[0].spotcoscutoff);
        glUniform1f(glGetUniformLocation(m_Shader->GetID(), "LightSource[7].spotExponent"), m_Lumin[0].spotexponent);
        glUniform1i(glGetUniformLocation(m_Shader->GetID(), "LightSource[7].sw_light"), m_Lumin[0].encesa);
        
        int stateZ = glfwGetKey(m_Window, GLFW_KEY_W);
        if (stateZ == GLFW_PRESS)
        {
            if (m_MainChar.Move(0))
                m_ViewTranslation.z = 0.075f;
            else
                m_ViewTranslation.z = 0.0f;
        }
        else
        {
            stateZ = glfwGetKey(m_Window, GLFW_KEY_S);
            if (stateZ == GLFW_PRESS)
            {
                if (m_MainChar.Move(2))
                    m_ViewTranslation.z = -0.075f;
                else
                    m_ViewTranslation.z = 0.0f;
            }
            else
                m_ViewTranslation.z = 0.0f;
        }
        int stateX = glfwGetKey(m_Window, GLFW_KEY_D);
        if (stateX == GLFW_PRESS)
        {
            if (m_MainChar.Move(3))
                m_ViewTranslation.x = -0.075f;
            else
                m_ViewTranslation.x = 0.0f;
        }
        else
        {
            stateX = glfwGetKey(m_Window, GLFW_KEY_A);
            if (stateX == GLFW_PRESS)
            {
                if (m_MainChar.Move(1))
                    m_ViewTranslation.x = 0.075f;
                else
                    m_ViewTranslation.x = 0.0f;
            }
            else
                m_ViewTranslation.x = 0.0f;
        }

        int state_ = glfwGetKey(m_Window, GLFW_KEY_SPACE);
        if (state_ == GLFW_PRESS)
        {
            m_MainChar.Jump();
        }
        


        
        float sz = 2.0f;




        //UpdateMC
        m_MainChar.UpdateStates(m_Board->m_BoardLayout, m_View);
        m_Shader->SetUniformMat4f("modelMatrix", m_MainChar.m_ModelMatrix);
        glm::mat4 normalMC = glm::mat4(1.0f);
        normalMC = glm::transpose(glm::inverse(m_View * m_MainChar.m_ModelMatrix));
        m_Shader->SetUniformMat4f("normalMatrix", normalMC);
        m_View = glm::translate(m_View, m_ViewTranslation);
        m_Shader->SetUniformMat4f("viewMatrix", m_View);
        m_Shader->SetUniformMat4f("projectionMatrix", m_Proj); //
        m_MainChar.DrawMC(m_Shader->GetID());

        for (int  y = 0;  y < 3; y++)
            for (int z= 0; z< 20; z++)
                for (int x = m_Slider; x < (m_Slider + 30); x++)
                {
                    glm::mat4 model = glm::mat4(1.0f);
                    glm::mat4 modelU1 = glm::mat4(1.0f);
                    glm::mat4 modelU2 = glm::mat4(1.0f);
                    glm::mat4 normal = glm::mat4(1.0f);
                    
                    model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
                    model = glm::translate(model, m_Translation);
                    model = glm::translate(model, glm::vec3(sz * x, 0, 0));
                    model = glm::translate(model, glm::vec3(0, (2 - y) * sz * 3, 0));
                    model = glm::translate(model, glm::vec3(0, 0, z* sz));
                    normal = glm::transpose(glm::inverse(m_View * model));
                    m_Shader->SetUniformMat4f("normalMatrix", normal);
                    
                    int value = (int)m_Board->m_BoardLayout[x + z* 250 +  y * 250 * 20] - 48;
                    int random = m_random[(x + z+ y) % 100];
                    switch (value) {
                    case 0:
                        break;
                    case 1:

                        m_Shader->SetUniformMat4f("modelMatrix", model);
                        m_ObOBJ[m_random[random]].draw_TriVAO_OBJ(m_Shader->GetID());
                        break;
                    case 2:
                        //breakable
                        m_Shader->SetUniformMat4f("modelMatrix", model);
                        m_ObOBJ[m_random[random]].draw_TriVAO_OBJ(m_Shader->GetID());
                        modelU1 = glm::translate(model, glm::vec3(0, sz, 0));
                        m_Shader->SetUniformMat4f("modelMatrix", modelU1);
                        m_ObOBJ[8].draw_TriVAO_OBJ(m_Shader->GetID());
                        modelU2 = glm::translate(model, glm::vec3(0, 2 * sz, 0));
                        m_Shader->SetUniformMat4f("modelMatrix", modelU2);
                        m_ObOBJ[8].draw_TriVAO_OBJ(m_Shader->GetID());
                        break;
                    case 3:
                        //Mobil
                        m_Shader->SetUniformMat4f("modelMatrix", model);
                        m_ObOBJ[m_random[random]].draw_TriVAO_OBJ(m_Shader->GetID());
                        modelU1 = glm::translate(model, glm::vec3(0, sz, 0));
                        m_Shader->SetUniformMat4f("modelMatrix", modelU1);
                        m_ObOBJ[9].draw_TriVAO_OBJ(m_Shader->GetID());
                        break;
                    case 4:
                        //+1
                        m_Shader->SetUniformMat4f("modelMatrix", model);
                        m_ObOBJ[m_random[random]].draw_TriVAO_OBJ(m_Shader->GetID());
                        modelU1 = glm::translate(model, glm::vec3(0, sz, 0));
                        m_Shader->SetUniformMat4f("modelMatrix", modelU1);
                        m_ObOBJ[m_random[(random + 1) % 100]].draw_TriVAO_OBJ(m_Shader->GetID());
                        break;
                    case 5:
                        //+2
                        m_Shader->SetUniformMat4f("modelMatrix", model);
                        m_ObOBJ[m_random[random]].draw_TriVAO_OBJ(m_Shader->GetID());
                        modelU2 = glm::translate(model, glm::vec3(0, 2 * sz, 0));
                        m_Shader->SetUniformMat4f("modelMatrix", modelU2);
                        m_ObOBJ[m_random[(random + 1) % 100]].draw_TriVAO_OBJ(m_Shader->GetID());
                        break;
                    case 6:
                        //Readable
                        m_Shader->SetUniformMat4f("modelMatrix", model);
                        m_ObOBJ[m_random[random]].draw_TriVAO_OBJ(m_Shader->GetID());
                        modelU1 = glm::translate(model, glm::vec3(1, sz, -1));
                        modelU1 = glm::rotate(modelU1, glm::radians(90.0f), glm::vec3(0, 1.0f, 0));
                        m_Shader->SetUniformMat4f("modelMatrix", modelU1);
                        m_ObOBJ[10].draw_TriVAO_OBJ(m_Shader->GetID());
                        break;
                    case 7:
                        m_Shader->SetUniformMat4f("modelMatrix", model);
                        m_Board->m_BoardLayout[x + z* 250 + y * 250 * 20] = 1;
                        //call enemy creation
                        m_ObOBJ[m_random[random]].draw_TriVAO_OBJ(m_Shader->GetID());
                        break;
                    }
                    //renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
                    //renderer.DrawRaw(*m_VAO, *m_Shader, 12);
                }
        
        int stateE = glfwGetKey(m_Window, GLFW_KEY_E);
        if (stateE == GLFW_PRESS)
        {
            if (m_MainChar.m_stagger <= 10 && m_ReadCheck == 0)
            {
                m_ReadCheck = 1;
                m_View2 = m_View;
                m_MainChar.m_stagger += 20;
            }
            m_MainChar.m_stagger += 1;
        }
        if (m_ReadCheck == 2 && m_MainChar.m_stagger <= 5)
        {
            m_ReadCheck = 1;
        }
        if (m_ReadCheck == 1 && m_MainChar.m_stagger <= 5)
        {
            m_ReadCheck = 0;
            m_View = m_View2;
        }
        if (m_ReadCheck == 1)
        {
            m_ReadCheck = 2;
            glm::mat4 auxGUI = glm::translate(m_MainChar.m_ModelMatrix, glm::vec3(0.0f, 8.0f, -3.0f));
            auxGUI = glm::rotate(auxGUI, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            m_View = glm::translate(m_View2, glm::vec3(0.0f, -2.0f, 1.0f));
            m_Shader->SetUniformMat4f("modelMatrix", auxGUI);
            m_ObOBJ[11].draw_TriVAO_OBJ(m_Shader->GetID());
        }
        if (m_ReadCheck == 2)
        {
            glm::mat4 auxGUI = glm::translate(m_MainChar.m_ModelMatrix, glm::vec3(0.0f, 8.0f, -3.0f));
            auxGUI = glm::rotate(auxGUI, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            auxGUI = glm::scale(auxGUI, glm::vec3(5.0f, 5.0f, 0.0f));
            m_View = glm::translate(m_View2, glm::vec3(0.0f, -4.0f, 0.0f));

            m_Shader->SetUniformMat4f("modelMatrix", auxGUI);
            m_ObOBJ[11].draw_TriVAO_OBJ(m_Shader->GetID());
        }
        int stateR = glfwGetKey(m_Window, GLFW_KEY_R);
        if (stateR == GLFW_PRESS)
        {
            glm::mat4 auxGUI = glm::translate(m_MainChar.m_ModelMatrix, glm::vec3(-1.0f, 3.0f, -0.25f));
            auxGUI = glm::scale(auxGUI, glm::vec3(0.5f, 0.5f, 0.5f));
            m_Shader->SetUniformMat4f("modelMatrix", auxGUI);
            m_ObOBJ[3].draw_TriVAO_OBJ(m_Shader->GetID());
            auxGUI = glm::translate(auxGUI, glm::vec3(2.0f, 0.0f, 0.0f));
            m_Shader->SetUniformMat4f("modelMatrix", auxGUI);
            m_ObOBJ[3].draw_TriVAO_OBJ(m_Shader->GetID());
            auxGUI = glm::translate(auxGUI, glm::vec3(2.0f, 0.0f, 0.0f));
            m_Shader->SetUniformMat4f("modelMatrix", auxGUI);
            m_ObOBJ[3].draw_TriVAO_OBJ(m_Shader->GetID());
        }
        int stateT = glfwGetKey(m_Window, GLFW_KEY_T);
        if (stateT == GLFW_PRESS)
        {
            glm::mat4 auxGUI = glm::translate(m_MainChar.m_ModelMatrix, glm::vec3(-1.0f, 3.0f, -0.25f));
            auxGUI = glm::scale(auxGUI, glm::vec3(0.5f, 0.5f, 0.5f));
            m_Shader->SetUniformMat4f("modelMatrix", auxGUI);
            m_ObOBJ[2].draw_TriVAO_OBJ(m_Shader->GetID());
            auxGUI = glm::translate(auxGUI, glm::vec3(2.0f, 0.0f, 0.0f));
            m_Shader->SetUniformMat4f("modelMatrix", auxGUI);
            m_ObOBJ[2].draw_TriVAO_OBJ(m_Shader->GetID());
        }
        int stateY = glfwGetKey(m_Window, GLFW_KEY_Y);
        if (stateY == GLFW_PRESS)
        {
            glm::mat4 auxGUI = glm::translate(m_MainChar.m_ModelMatrix, glm::vec3(-1.0f, 3.0f, -0.25f));
            auxGUI = glm::scale(auxGUI, glm::vec3(0.5f, 0.5f, 0.5f));
            m_Shader->SetUniformMat4f("modelMatrix", auxGUI);
            m_ObOBJ[1].draw_TriVAO_OBJ(m_Shader->GetID());
        }

    }

    void test::TestPlayground::OnImGuiRender()
    {
        ImGui::SliderFloat3("Translation", &m_Translation.x, -50.0f, 50.0f);
        ImGui::SliderInt("Slider", &m_Slider, 0.0f, 50.0f);
        ImGui::SliderFloat3("CenterPos", &m_MainChar.m_CenterPos.x, 0.0f, 100.0f);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

    }
}