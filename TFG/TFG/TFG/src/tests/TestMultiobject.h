#pragma once

#include "Test.h"
#include "Texture.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"


#include <memory>
namespace test {

	class TestMultiobject : public Test
	{
	public:
		TestMultiobject();
		~TestMultiobject();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		glm::vec3 m_Rotation;
		glm::vec3 m_Translation;
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;		
		std::unique_ptr<VertexArray> m_VAO1;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_Texture;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<VertexBuffer> m_VertexBuffer1;

		glm::mat4 m_Proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
		glm::mat4 m_View = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

	};


}
