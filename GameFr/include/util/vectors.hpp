#pragma once
namespace GameFr{
	struct Vector2{
		float X;
		float Y;

		Vector2(const float& x, const float& y);
		Vector2();

		static float GetDistance(const Vector2& first, const Vector2& second);
		static Vector2 GetDiference(const Vector2& first, const Vector2& second);
		void Normalize();
	};

	struct Vector3{
		float X;
		float Y;
		float Z;
	};
}
