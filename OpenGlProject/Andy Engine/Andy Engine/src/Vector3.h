#ifndef VECTOR3_H
#define VECTOR3_H

struct Vector3 {
	float x, y, z;

	Vector3()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}

	Vector3(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	Vector3 operator+(const Vector3& v) const {
		Vector3 result;
		result = Vector3(x + v.x, y + v.y, z + v.z);
		return result;
	}

	Vector3 operator-(const Vector3& v) const {
		Vector3 result;
		result = Vector3(x - v.x, y - v.y, z - v.z);
		return result;
	}

	Vector3 operator*(const Vector3& v) const {
		Vector3 result;
		result = Vector3(x * v.x, y * v.y, z * v.z);
		return result;
	}

	Vector3 operator/(const Vector3& v) const {
		Vector3 result;
		result = Vector3(x / v.x, y / v.y, z / v.z);
		return result;
	}

	bool operator==(const Vector3& v) {
		return (x == v.x && y == v.y && z == v.z);
	}

	bool operator!=(const Vector3& v) {
		return (x != v.x || y != v.y || z != v.z);
	}

	friend std::ostream& operator<<(std::ostream& os, const Vector3& v) {
		os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
		return os;
	}


};

#endif // !1

