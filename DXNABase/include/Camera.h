#include "../Common.h"

#pragma once

using namespace DirectX;

class Camera
{
	private:
		Vector3 position;
		Vector3 target;
		Vector3 up;
		float aspectRatio;
		float fov;
		float nearPlane;
		float farPlane;

		bool updateView;
		bool updateProjection;
		Matrix view;
		Matrix projection;

		inline Camera() {}

	public:
		inline Camera(const Vector3& pos, const Vector3& tgt) : 
			position(pos), target(tgt), aspectRatio(640.0f / 480.0f), 
			fov(3.14159f / 4.0f), nearPlane(0.01f), farPlane(1000.0f), 
			updateView(true), updateProjection(true), up(Vector3(0, 1, 0))
		{
		}

		inline Vector3 getPosition() const
		{
			return position;
		}
		inline void setPosition(const Vector3& pos)
		{
			position = pos;
			updateView = true;
		}
		inline void setPosition(const float& x, const float& y, const float& z)
		{
			position.X = x;
			position.Y = y;
			position.Z = z;
			updateView = true;
		}

		inline Vector3 getTarget() const
		{
			return target;
		}
		inline void setTarget(const Vector3& tar)
		{
			target = tar;
			updateView = true;
		}
		inline void setTarget(const float& x, const float& y, const float& z)
		{
			target.X = x;
			target.Y = y;
			target.Z = z;
			updateView = true;
		}

		inline Vector3 getUp() const { return up; }
		inline void setUp(const Vector3& u) 
		{ 
			up = u;
			updateView = true;
		}
		inline void setUp(const float& x, const float& y, const float& z)
		{
			up.X = x;
			up.Y = y;
			up.Z = z;
			updateView = true;
		}

		inline float getFov() const { return fov; }
		inline void setFov(const float& f)
		{
			fov = f;
			updateProjection = true;
		}

		inline float getAspectRatio() const { return aspectRatio; }
		inline void setAspectRatio(const float& ar) 
		{
			aspectRatio = ar;
			updateProjection = true;
		}

		inline float getNearPlane() const { return nearPlane; }
		inline void setNearPlane(const float& n) 
		{
			nearPlane = n;
			updateProjection = true;
		}

		inline float getFarPlane() const { return farPlane; }
		inline void setFarPlane(const float& f)
		{
			farPlane = f;
			updateProjection = true;
		}


		inline Matrix getView()
		{
			if (updateView)
			{
				view = Matrix::CreateLookAt(position, target, up);//XMMatrixLookAtLH(position, target, up);
				updateView = false;
			}
			return view;
		}

		inline Matrix getProjection()
		{
			if (updateProjection)
			{
				projection = Matrix::CreatePerspectiveFieldOfView(fov, aspectRatio, nearPlane, farPlane);
				updateProjection = false;
			}

			return projection;
		}
};