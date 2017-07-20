#ifndef _CAMERA_2D_H
#define _CAMERA_2D_H

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

namespace burek
{

	class Camera2D
	{
	public:
		Camera2D();
		~Camera2D();

		void Initialize(int screenWidth, int screenHeight);

		void Update();

		//getters and setters
		void SetPosition(const glm::vec2& position) { m_position = position; m_matrixUpdate = true; }
		const glm::vec2& GetPosition()const { return m_position; }

		void SetScale(float scale) { m_scale = scale; m_matrixUpdate = true; }
		float GetScale()const { return m_scale; }

		const glm::mat4& GetCameraMatrix()const { return m_cameraMatrix; }

	private:
		glm::vec2 m_position;
		glm::mat4 m_cameraMatrix;
		glm::mat4 m_orthoMatrix;
		float m_scale;
		bool m_matrixUpdate;
		int m_screenWidth, m_screenHeight;

	};

}

#endif //_CAMERA_2D_H
