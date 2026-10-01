#pragma once
namespace MyGl
{
	class Vec2
	{
	public:
		union
		{
			struct { float x, y; };
			struct { float u, v; };
			struct { float width, height; };
			float elements[2];
		};
		Vec2();
		Vec2(float x, float y);

		Vec2 operator+(const Vec2& other)const;
		Vec2 operator-(const Vec2& other)const;

		Vec2& operator+=(const Vec2& other);
		Vec2& operator-=(const Vec2& other);

		float Length()const;
		Vec2& Normalize();
	};
	class Vec3
	{
	public:
		union
		{
			struct { float x, y, z; };
			struct { float r, g, b; };
			struct { Vec2 xy; float z; };
			float elements[3];
		};
		Vec3();
		Vec3(float x, float y, float z);
		Vec3(const float datas[3]);


		Vec3 operator+(const Vec3& other)const;
		Vec3 operator-(const Vec3& other)const;
		Vec3 operator*(const float& other) const;

		Vec3& operator+=(const Vec3& other);
		Vec3& operator-=(const Vec3& other);
		Vec3& operator*=(const float& other);

		float Length()const;
		Vec3& Normalize();
		float Dot(const Vec3& v1, const Vec3& v2);
		Vec3 Cross(const Vec3& v1, const Vec3& v2);
	};

	class Vec4
	{
	public:
		union
		{
			
			struct { float x, y, z, w; };
			struct { float r, g, b, a; };
			struct { Vec3 xyz; float w; };
			struct { Vec2 xy;  Vec2 zw; };
			float elements[4];
		};

		Vec4();
		Vec4(float x, float y, float z, float w);
		Vec4(const float datas[4]);
		Vec4 operator+(const Vec4& other)const;
		Vec4 operator-(const Vec4& other)const;
		Vec4& operator+=(const Vec4& other);
		Vec4& operator-=(const Vec4& other);
	};
	class Mat4 {
	public:
		union
		{
			float Elements[16];
			float M[4][4];
			Vec4 Columns[4];
			struct
			{
				Vec4 Right;    // Cột 0
				Vec4 Up;       // Cột 1
				Vec4 Forward;  // Cột 2
				Vec4 Position; // Cột 3
			};
		};
		Mat4();
		Mat4& Identity(float diagonal = 1.0f);
		Mat4 operator*(const Mat4& other) const;
		Vec4 operator*(const Vec4& vec4) const;
		Vec3 TransformPoint(const Vec3& v)const;
		Vec3 TransformVector(const Vec3& v) const;
		Mat4& Translate(const Vec3& translation);
		Mat4& Scale(const Vec3& scale);
		//Mat4& Rotate(float angleInDegrees, Vec3 axis);
		Mat4& Ortho(float left, float right, float bottom, float top, float near, float far);
		Mat4& Perspective(float FOVx,float FOVy,float near);
		//Mat4 Inverse();

	};

}
