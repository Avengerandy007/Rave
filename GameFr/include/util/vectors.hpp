#pragma once
namespace GameFr{
	struct Vector2{
		float X;
		float Y;

		Vector2(const float& x, const float& y);
		Vector2();

		friend bool operator==(const Vector2& l, const Vector2& r);
		friend Vector2 operator+(const Vector2& a, const float& b);
		friend Vector2 operator+(const Vector2& a, const Vector2& b);
		friend Vector2 operator-(const Vector2& a, const float& b);
		friend Vector2 operator-(const Vector2& a, const Vector2& b);
		friend Vector2 operator*(const Vector2& a, const float& b);
		friend Vector2 operator/(const Vector2& a, const float& b);

		static float GetDistance(const Vector2& first, const Vector2& second);
		static Vector2 GetDiference(const Vector2& first, const Vector2& second);
		static float DotProduct(const Vector2& first, const Vector2& second);
		
		void Normalize();
		float Magnitude() const;
	};

	struct Vector3{
		float X;
		float Y;
		float Z;
	};
}
