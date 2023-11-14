class Vector2
{
public:
	Vector2(int _x, int _y){
		x = _x;
		y = _y;
	}
	
	int x;
	int y;
	// Overloading unary - operator
	Vector2 operator-() const {
		return Vector2(-x, -y);
	}
	Vector2 Copy(){
		return Vector2(x,y);
	}
	// Overloading += operator
	Vector2& operator+=(const Vector2& other) {
		x += other.x;
		y += other.y;
		return *this;
	}

	// Overloading -= operator
	Vector2& operator-=(const Vector2& other) {
		x -= other.x;
		y -= other.y;
		return *this;
	}

	// Overloading + operator
	Vector2 operator+(const Vector2& other) const {
		return Vector2(x + other.x, y + other.y);
	}
	// Overloading - operator
	Vector2 operator-(const Vector2& other) const {
		return Vector2(x - other.x, y - other.y);
	}
};