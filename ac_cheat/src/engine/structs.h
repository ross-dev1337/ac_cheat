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


   // <ac_client.exe>+0x0018AC00
    struct player {
        char _0x0000[0x4]; //0x0000
        vector3 head_origin; //0x0004
        char _0x0010[0x18]; //0x0010
        vector3 root_origin; //0x0028
        char _0x0034[0xB8]; //0x0034
        int32_t current_health; //0x00EC
        int32_t armour; //0x00F0
        char _0x00F4[0x111];
        char name[15]; // 0x0205
        char _0x0214[0xF8];
        int32_t team; // 0x030C
    };
    inline player* local_player;
    

    // <ac_client.exe>+0x18AC04
    struct entity {
        char _0x0000[0x4];
        player* ents[32];
    };
    inline entity* ent; 
 
    // <ac_client.exe>+0x00191ED8
    struct screen_dimensions {
        int32_t screen_width; // 0x0000
        int32_t screen_height; // 0x0004
    };
    inline screen_dimensions* screen;
  
   

  

}