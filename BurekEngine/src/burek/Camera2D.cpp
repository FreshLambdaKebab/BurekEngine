#include "Camera2D.h"

namespace burek
{

	Camera2D::Camera2D() :
		m_position(0.0f, 0.0f),
		m_cameraMatrix(1.0f),
		m_orthoMatrix(1.0f),
		m_scale(1.0f),
		m_matrixUpdate(true),
		m_screenWidth(800),
		m_screenHeight(600)
	{
	}

	Camera2D::~Camera2D()
	{
	}

	void Camera2D::Initialize(int screenWidth, int screenHeight)
	{
		m_screenWidth = screenWidth;
		m_screenHeight = screenHeight;
		m_orthoMatrix = glm::ortho(0.0f, static_cast<float>(m_screenWidth), 0.0f, static_cast<float>(m_screenHeight));

	}

	void Camera2D::Update()
	{
		if (m_matrixUpdate)
		{
			//setup camera matrix translation
			glm::vec3 translate(-m_position.x + m_screenWidth / 2, -m_position.y + m_screenHeight / 2, 0.0f);
			m_cameraMatrix = glm::translate(m_orthoMatrix, translate);

			//camera scaling
			glm::vec3 scale(m_scale, m_scale, 0.0f);
			m_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * m_cameraMatrix;

			m_matrixUpdate = false;
		}
	}

}
