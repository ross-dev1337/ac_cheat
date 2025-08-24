#pragma once

template<typename T, typename... args> static T call(uint32_t address, args... _args) {
    T(*fn)(args...) = (T(*)(args...))address;
    return fn(_args...);
}


namespace structs {
    struct vector3 {
        float x, y, z;

        vector3() {
            x = y = z = 0;
        }

        vector3(float x_, float y_, float z_) {
            x = x_, y = y_, z = z_;
        }

        vector3 operator+(vector3 v) {
            return vector3(x + v.x, y + v.y, z + v.z);
        }

        vector3 operator-(vector3 v) {
            return vector3(x - v.x, y - v.y, z - v.z);
        }

        vector3 operator*(vector3 v) {
            return vector3(x * v.x, y * v.y, z * v.z);
        }

        static vector3 scale(vector3 v, float num) {
            return vector3(v.x * num, v.y * num, v.z * num);
        }

        float get_distance(vector3 v) {
            float dis_x = x - v.x, dis_y = y - v.y, dis_z = z - v.z;
            return sqrt((dis_x * dis_x) + (dis_y * dis_y) + (dis_z * dis_z) * 1.f);
        }

        float dot_product(vector3 v) {
            return (x * v.x) + (y * v.y) + (z * v.z);
        }
    };

    struct vector2 {
        float x, y; 
    };

    struct vector4 {
        float x, y, z, w; 
    };



}