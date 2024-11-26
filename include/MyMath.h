#if !defined(__MYMATH_H__)
#define __MYMATH_H__

#include <ostream>

template <typename VECTOR_TEMP> class Vector2
{
    public:
        VECTOR_TEMP x;
        VECTOR_TEMP y;
        Vector2() : x(0), y(0){}
        Vector2(VECTOR_TEMP X, VECTOR_TEMP Y) : x(X), y(Y){}

        float AngleTo(Vector2<VECTOR_TEMP> OtherVec)
        {
            return Vector2<VECTOR_TEMP>(); // temp
        }
        //Overloading
        //cant add float with int
        Vector2<VECTOR_TEMP> operator+(Vector2<VECTOR_TEMP> const& vec)
        {
            Vector2<VECTOR_TEMP> new_vec = Vector2<VECTOR_TEMP>(x + vec.x, y + vec.y);
            return new_vec;
        }
        
        Vector2 operator*(int const num)
        {
            Vector2 new_vec = Vector2(x * num, y * num);
            return new_vec;
        }
        Vector2<float> operator*(float const num)
        {
            Vector2<float> new_vec = Vector2<float>(x * num, y * num);
            return new_vec;
        }

        Vector2<VECTOR_TEMP> operator+=(const Vector2<VECTOR_TEMP> & vec)
        {
            x += vec.x;
            y += vec.y;
            return *this;
        }

        friend std::ostream& operator<<(std::ostream &out, Vector2 const & vec)
        {
            out << '(' << vec.x << ", " << vec.y << ')';
            return out;
        }
};


#endif // __MYMATH_H__
