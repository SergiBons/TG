#pragma once

#include "Test.h"
#include "Texture.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "objLoader.h"
#include "board/Board.h"
#include "entities/MC.h"
#include "entities/Enemy1.h"


#include <SFML/Audio.hpp>
#include <memory>
namespace test {

	class TestPlayground : public Test
	{
	public:
		TestPlayground(GLFWwindow* window, sf::Sound* sound, sf::Sound* sound2);
		~TestPlayground();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		sf::Sound* m_sound;
		sf::Sound* m_sound2;
		int m_sizeSlide;
		int m_random[100];
		int m_ReadCheck = 0;
		int m_damage;
		LLUM m_Lumin[8];
		int m_Slider;
		glm::vec3 m_Rotation;
		glm::vec3 m_Translation;
		glm::vec3 m_ViewTranslation;
		std::unique_ptr<Board> m_Board;
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_Texture[9];
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		COBJModel m_ObOBJ[13];
		COBJModel m_Effects[2];
		COBJModel m_Skybox[9];
		MC m_MainChar;
		std::vector<Enemy*> m_EnemyVector;
		glm::mat4 m_Proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
		glm::mat4 m_View = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
		glm::mat4 m_View2 = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
		GLFWwindow* m_Window;
	};


}
