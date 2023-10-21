#pragma once
#include <cstdint>
#include "dma.h"

namespace offsets {
    inline uint64_t ref_def_ptr = 0x11CEE758;
    inline uint64_t name_array = 0x11D0E6A8;
    inline uint64_t name_array_pos = 0x5E80;
    inline uint64_t loot_ptr = 0x47716C68;
    inline uint64_t camera_base = 0x124947F0;
    inline uint64_t camera_pos = 0x208;
    inline uint64_t local_index = 0xA5370;
    inline uint64_t local_index_pos = 0x02F0;
    inline uint64_t game_mode = 0x0EF4ED90;
    inline uint64_t weapon_definitions = 0x11C215A0;
    inline uint64_t distribute = 0x0AA729A8;
    namespace player {
        inline uint64_t size = 0x6470;
        inline uint64_t valid = 0x0A40;
        inline uint64_t pos = 0x0FC8;
        inline uint64_t team = 0x08C8;
        inline uint64_t weapon_index = 0xD7C;
        inline uint64_t dead_1 = 0x0E62;
        inline uint64_t dead_2 = 0x0E06;
    }
    namespace bone {
        inline uint64_t bone_base = 0x174A90;
        inline uint64_t size = 0x0188;
        inline uint64_t offset = 0x00D8;
    }
}

inline uintptr_t decrypt_client_info()
{
    uint64_t mb = DMA::BaseAddress;
    uint64_t rax = mb, rbx = mb, rcx = mb, rdx = mb, rdi = mb, rsi = mb, r8 = mb, r9 = mb, r10 = mb, r11 = mb, r12 = mb, r13 = mb, r14 = mb, r15 = mb;

    rbx = DMA::ReadPtr<uintptr_t>(DMA::BaseAddress + 0x11CECAF8);
    if (!rbx)
        return rbx;

    rcx = DMA::PebAddress;              //mov rcx, gs:[rax]
    rbx -= rcx;             //sub rbx, rcx
    rax = 0;                //and rax, 0xFFFFFFFFC0000000
    rdx = 0x693186CC4D1F9DB;                //mov rdx, 0x693186CC4D1F9DB
    rbx *= rdx;             //imul rbx, rdx
    rax = _rotl64(rax, 0x10);               //rol rax, 0x10
    rdx = 0x57548B4D82F080EE;               //mov rdx, 0x57548B4D82F080EE
    rax ^= DMA::ReadPtr<uintptr_t>(DMA::BaseAddress + 0x94D60E6);             //xor rax, [0x000000000735768D]
    rbx += rdx;             //add rbx, rdx
    rax = _byteswap_uint64(rax);            //bswap rax
    rbx *= DMA::ReadPtr<uintptr_t>(rax + 0x13);             //imul rbx, [rax+0x13]
    rax = rbx;              //mov rax, rbx
    rbx >>= 0x20;           //shr rbx, 0x20
    rbx ^= rax;             //xor rbx, rax
    rbx += rcx;             //add rbx, rcx
    return rbx;
};
inline uintptr_t decrypt_client_base(uintptr_t client_info)
{
    const uint64_t mb = DMA::BaseAddress;
    uint64_t rax = mb, rbx = mb, rcx = mb, rdx = mb, rdi = mb, rsi = mb, r8 = mb, r9 = mb, r10 = mb, r11 = mb, r12 = mb, r13 = mb, r14 = mb, r15 = mb;
    rax = DMA::ReadPtr<uintptr_t>(client_info + 0x1828e8);
    if (!rax)
        return rax;
    r11 = ~DMA::PebAddress;              //mov r11, gs:[rcx]
    rcx = r11;              //mov rcx, r11
    //failed to translate: mov [rsp+0x3D0], r13
    rcx = _rotl64(rcx, 0x21);               //rol rcx, 0x21
    rcx &= 0xF;
    switch (rcx) {
    case 0:
    {
        r9 = DMA::ReadPtr<uintptr_t>(DMA::BaseAddress + 0x94D610E);               //mov r9, [0x000000000672F471]
        rbx = DMA::BaseAddress;           //lea rbx, [0xFFFFFFFFFD259350]
        rcx = 0x9141C45BFD5B39F7;               //mov rcx, 0x9141C45BFD5B39F7
        rax ^= rcx;             //xor rax, rcx
        rcx = rax + rbx * 1;            //lea rcx, [rax+rbx*1]
        rax = 0xF605A67470E7C53D;               //mov rax, 0xF605A67470E7C53D
        rcx *= rax;             //imul rcx, rax
        rax = r11;              //mov rax, r11
        uintptr_t RSP_0x50;
        RSP_0x50 = DMA::BaseAddress + 0x6E33AF72;                 //lea rcx, [0x000000006B5942CE] : RSP+0x50
        rax ^= RSP_0x50;                //xor rax, [rsp+0x50]
        rcx -= rax;             //sub rcx, rax
        rax = r11 + 0xffffffffd10685d8;                 //lea rax, [r11-0x2EF97A28]
        rcx -= rbx;             //sub rcx, rbx
        rax += rcx;             //add rax, rcx
        rcx = DMA::BaseAddress + 0x526CB4F4;              //lea rcx, [0x000000004F924777]
        rcx = ~rcx;             //not rcx
        rcx -= r11;             //sub rcx, r11
        rax += rcx;             //add rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x1A;           //shr rcx, 0x1A
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x34;           //shr rcx, 0x34
        rax ^= rcx;             //xor rax, rcx
        rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
        rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
        rcx ^= r9;              //xor rcx, r9
        rcx = ~rcx;             //not rcx
        rax *= DMA::ReadPtr<uintptr_t>(rcx + 0x19);             //imul rax, [rcx+0x19]
        return rax;
    }
    case 1:
    {
        r10 = DMA::ReadPtr<uintptr_t>(DMA::BaseAddress + 0x94D610E);              //mov r10, [0x000000000672EFD8]
        rbx = DMA::BaseAddress;           //lea rbx, [0xFFFFFFFFFD258EC3]
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x24;           //shr rcx, 0x24
        rax ^= rcx;             //xor rax, rcx
        rcx = 0xE570A6F93EC9464F;               //mov rcx, 0xE570A6F93EC9464F
        rax *= rcx;             //imul rax, rcx
        rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
        rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
        rcx ^= r10;             //xor rcx, r10
        rcx = ~rcx;             //not rcx
        rax *= DMA::ReadPtr<uintptr_t>(rcx + 0x19);             //imul rax, [rcx+0x19]
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x24;           //shr rcx, 0x24
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x11;           //shr rcx, 0x11
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x22;           //shr rcx, 0x22
        rax ^= rcx;             //xor rax, rcx
        rax -= rbx;             //sub rax, rbx
        rax += r11;             //add rax, r11
        rcx = 0x14F095F380F9EB43;               //mov rcx, 0x14F095F380F9EB43
        rax += rcx;             //add rax, rcx
        return rax;
    }
    case 2:
    {
        r10 = DMA::ReadPtr<uintptr_t>(DMA::BaseAddress + 0x94D610E);              //mov r10, [0x000000000672EB27]
        rcx = 0x8ADB88DACDCF2087;               //mov rcx, 0x8ADB88DACDCF2087
        rax *= rcx;             //imul rax, rcx
        rcx = 0x7962CBE13BD24CEA;               //mov rcx, 0x7962CBE13BD24CEA
        rax += rcx;             //add rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x10;           //shr rcx, 0x10
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x20;           //shr rcx, 0x20
        rax ^= rcx;             //xor rax, rcx
        rax += r11;             //add rax, r11
        rax += r11;             //add rax, r11
        rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
        rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
        rcx ^= r10;             //xor rcx, r10
        rcx = ~rcx;             //not rcx
        rax *= DMA::ReadPtr<uintptr_t>(rcx + 0x19);             //imul rax, [rcx+0x19]
        rax -= r11;             //sub rax, r11
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x1D;           //shr rcx, 0x1D
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x3A;           //shr rcx, 0x3A
        rax ^= rcx;             //xor rax, rcx
        return rax;
    }
    case 3:
    {
        r10 = DMA::ReadPtr<uintptr_t>(DMA::BaseAddress + 0x94D610E);              //mov r10, [0x000000000672E747]
        rbx = DMA::BaseAddress;           //lea rbx, [0xFFFFFFFFFD258632]
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x25;           //shr rcx, 0x25
        rcx ^= rax;             //xor rcx, rax
        rax = 0x99B04B837FD2242B;               //mov rax, 0x99B04B837FD2242B
        rax += rcx;             //add rax, rcx
        rax += rbx;             //add rax, rbx
        rax ^= r11;             //xor rax, r11
        rax -= rbx;             //sub rax, rbx
        rcx = DMA::BaseAddress + 0x11751E8B;              //lea rcx, [0x000000000E9AA129]
        rcx = ~rcx;             //not rcx
        rcx -= r11;             //sub rcx, r11
        rax += rcx;             //add rax, rcx
        rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
        rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
        rcx ^= r10;             //xor rcx, r10
        rcx = ~rcx;             //not rcx
        rax *= DMA::ReadPtr<uintptr_t>(rcx + 0x19);             //imul rax, [rcx+0x19]
        rcx = 0xDA47FAB853EFDBF7;               //mov rcx, 0xDA47FAB853EFDBF7
        rax *= rcx;             //imul rax, rcx
        return rax;
    }
    case 4:
    {
        r10 = DMA::ReadPtr<uintptr_t>(DMA::BaseAddress + 0x94D610E);              //mov r10, [0x000000000672E28C]
        rbx = DMA::BaseAddress;           //lea rbx, [0xFFFFFFFFFD25816B]
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x2;            //shr rcx, 0x02
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x4;            //shr rcx, 0x04
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x8;            //shr rcx, 0x08
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x10;           //shr rcx, 0x10
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x20;           //shr rcx, 0x20
        rax ^= rcx;             //xor rax, rcx
        rcx = 0x718CFE6D52D76081;               //mov rcx, 0x718CFE6D52D76081
        rax *= rcx;             //imul rax, rcx
        rcx = r11;              //mov rcx, r11
        rcx ^= rax;             //xor rcx, rax
        rdx = 0;                //and rdx, 0xFFFFFFFFC0000000
        rax = DMA::BaseAddress + 0x746D9936;              //lea rax, [0x0000000071931827]
        rcx ^= rax;             //xor rcx, rax
        rdx = _rotl64(rdx, 0x10);               //rol rdx, 0x10
        rdx ^= r10;             //xor rdx, r10
        rax = 0x6A0BA8494B6820F5;               //mov rax, 0x6A0BA8494B6820F5
        rdx = ~rdx;             //not rdx
        rcx *= DMA::ReadPtr<uintptr_t>(rdx + 0x19);             //imul rcx, [rdx+0x19]
        rax += rcx;             //add rax, rcx
        rax ^= rbx;             //xor rax, rbx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x15;           //shr rcx, 0x15
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x2A;           //shr rcx, 0x2A
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x1C;           //shr rcx, 0x1C
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x38;           //shr rcx, 0x38
        rax ^= rcx;             //xor rax, rcx
        return rax;
    }
    case 5:
    {
        r9 = DMA::ReadPtr<uintptr_t>(DMA::BaseAddress + 0x94D610E);               //mov r9, [0x000000000672DD12]
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x15;           //shr rcx, 0x15
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x2A;           //shr rcx, 0x2A
        rax ^= rcx;             //xor rax, rcx
        rcx = 0x6B4D10E3FCFC0235;               //mov rcx, 0x6B4D10E3FCFC0235
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x3;            //shr rcx, 0x03
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x6;            //shr rcx, 0x06
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0xC;            //shr rcx, 0x0C
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x18;           //shr rcx, 0x18
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x30;           //shr rcx, 0x30
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x1A;           //shr rcx, 0x1A
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x34;           //shr rcx, 0x34
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x1C;           //shr rcx, 0x1C
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x38;           //shr rcx, 0x38
        rax ^= rcx;             //xor rax, rcx
        uintptr_t RSP_0x70;
        RSP_0x70 = 0x9FE7D7D2C91086EF;          //mov rcx, 0x9FE7D7D2C91086EF : RSP+0x70
        rax *= RSP_0x70;                //imul rax, [rsp+0x70]
        uintptr_t RSP_0x48;
        RSP_0x48 = 0x3B044E06AA0DC65D;          //mov rcx, 0x3B044E06AA0DC65D : RSP+0x48
        rax += RSP_0x48;                //add rax, [rsp+0x48]
        rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
        rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
        rcx ^= r9;              //xor rcx, r9
        rcx = ~rcx;             //not rcx
        rax *= DMA::ReadPtr<uintptr_t>(rcx + 0x19);             //imul rax, [rcx+0x19]
        return rax;
    }
    case 6:
    {
        r9 = DMA::ReadPtr<uintptr_t>(DMA::BaseAddress + 0x94D610E);               //mov r9, [0x000000000672D7AD]
        rbx = DMA::BaseAddress;           //lea rbx, [0xFFFFFFFFFD257698]
        rcx = rax;              //mov rcx, rax
        rcx >>= 0xF;            //shr rcx, 0x0F
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x1E;           //shr rcx, 0x1E
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x3C;           //shr rcx, 0x3C
        rax ^= rcx;             //xor rax, rcx
        rax -= r11;             //sub rax, r11
        rax ^= r11;             //xor rax, r11
        rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
        rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
        rcx ^= r9;              //xor rcx, r9
        rcx = ~rcx;             //not rcx
        rcx = DMA::ReadPtr<uintptr_t>(rcx + 0x19);              //mov rcx, [rcx+0x19]
        uintptr_t RSP_0x40;
        RSP_0x40 = 0xB64C05FA8BB41ED5;          //mov rcx, 0xB64C05FA8BB41ED5 : RSP+0x40
        rcx *= RSP_0x40;                //imul rcx, [rsp+0x40]
        rax *= rcx;             //imul rax, rcx
        rax -= rbx;             //sub rax, rbx
        rcx = 0xA1839DE961442277;               //mov rcx, 0xA1839DE961442277
        rax *= rcx;             //imul rax, rcx
        return rax;
    }
    case 7:
    {
        r10 = DMA::ReadPtr<uintptr_t>(DMA::BaseAddress + 0x94D610E);              //mov r10, [0x000000000672D325]
        rcx = DMA::BaseAddress + 0x7E9B;          //lea rcx, [0xFFFFFFFFFD25ECA7]
        rdx = r11;              //mov rdx, r11
        rax += rcx;             //add rax, rcx
        rdx = ~rdx;             //not rdx
        rax += rdx;             //add rax, rdx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0xD;            //shr rcx, 0x0D
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x1A;           //shr rcx, 0x1A
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x34;           //shr rcx, 0x34
        rax ^= rcx;             //xor rax, rcx
        rcx = r11;              //mov rcx, r11
        uintptr_t RSP_0x50;
        RSP_0x50 = DMA::BaseAddress + 0x2B12;             //lea rcx, [0xFFFFFFFFFD259D22] : RSP+0x50
        rcx ^= RSP_0x50;                //xor rcx, [rsp+0x50]
        rax -= rcx;             //sub rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x27;           //shr rcx, 0x27
        rax ^= rcx;             //xor rax, rcx
        rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
        rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
        rcx ^= r10;             //xor rcx, r10
        rcx = ~rcx;             //not rcx
        rax *= DMA::ReadPtr<uintptr_t>(rcx + 0x19);             //imul rax, [rcx+0x19]
        rcx = 0x6B0468CD6B4B36F5;               //mov rcx, 0x6B0468CD6B4B36F5
        rax *= rcx;             //imul rax, rcx
        rcx = 0x67D32343BA582459;               //mov rcx, 0x67D32343BA582459
        rax -= rcx;             //sub rax, rcx
        rcx = 0x2AB381DC49040AEF;               //mov rcx, 0x2AB381DC49040AEF
        rax ^= rcx;             //xor rax, rcx
        return rax;
    }
    case 8:
    {
        r10 = DMA::ReadPtr<uintptr_t>(DMA::BaseAddress + 0x94D610E);              //mov r10, [0x000000000672CE27]
        rbx = DMA::BaseAddress;           //lea rbx, [0xFFFFFFFFFD256D12]
        rcx = 0xF27764D7BCC134E1;               //mov rcx, 0xF27764D7BCC134E1
        rax *= rcx;             //imul rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x7;            //shr rcx, 0x07
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0xE;            //shr rcx, 0x0E
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x1C;           //shr rcx, 0x1C
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x38;           //shr rcx, 0x38
        rax ^= rcx;             //xor rax, rcx
        rax ^= rbx;             //xor rax, rbx
        rcx = 0xC3107C6F6CB6AAB7;               //mov rcx, 0xC3107C6F6CB6AAB7
        rax *= rcx;             //imul rax, rcx
        rcx = 0xD1B5E7C8461A7E03;               //mov rcx, 0xD1B5E7C8461A7E03
        rax ^= rcx;             //xor rax, rcx
        rcx = DMA::BaseAddress + 0x4977696C;              //lea rcx, [0x00000000469CD4B1]
        rcx = ~rcx;             //not rcx
        rcx += r11;             //add rcx, r11
        rax += rcx;             //add rax, rcx
        rax += 0xFFFFFFFFFFFF4E09;              //add rax, 0xFFFFFFFFFFFF4E09
        rcx = r11;              //mov rcx, r11
        rcx -= rbx;             //sub rcx, rbx
        rax += rcx;             //add rax, rcx
        rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
        rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
        rcx ^= r10;             //xor rcx, r10
        rcx = ~rcx;             //not rcx
        rax *= DMA::ReadPtr<uintptr_t>(rcx + 0x19);             //imul rax, [rcx+0x19]
        return rax;
    }
    case 9:
    {
        r10 = DMA::ReadPtr<uintptr_t>(DMA::BaseAddress + 0x94D610E);              //mov r10, [0x000000000672C983]
        rbx = DMA::BaseAddress;           //lea rbx, [0xFFFFFFFFFD25686E]
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x23;           //shr rcx, 0x23
        rax ^= rcx;             //xor rax, rcx
        rcx = 0xA7B0F0AA378850A7;               //mov rcx, 0xA7B0F0AA378850A7
        rax *= rcx;             //imul rax, rcx
        rax ^= rbx;             //xor rax, rbx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x1B;           //shr rcx, 0x1B
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x36;           //shr rcx, 0x36
        rax ^= rcx;             //xor rax, rcx
        rcx = rbx + 0xd85;              //lea rcx, [rbx+0xD85]
        rcx += r11;             //add rcx, r11
        rax += rcx;             //add rax, rcx
        rax -= rbx;             //sub rax, rbx
        uintptr_t RSP_0x60;
        RSP_0x60 = 0x4E5E1AE762C3863A;          //mov rcx, 0x4E5E1AE762C3863A : RSP+0x60
        rax ^= RSP_0x60;                //xor rax, [rsp+0x60]
        rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
        rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
        rcx ^= r10;             //xor rcx, r10
        rcx = ~rcx;             //not rcx
        rax *= DMA::ReadPtr<uintptr_t>(rcx + 0x19);             //imul rax, [rcx+0x19]
        return rax;
    }
    case 10:
    {
        r9 = DMA::ReadPtr<uintptr_t>(DMA::BaseAddress + 0x94D610E);               //mov r9, [0x000000000672C4C0]
        rbx = DMA::BaseAddress;           //lea rbx, [0xFFFFFFFFFD2563AB]
        r13 = DMA::BaseAddress + 0xF084;          //lea r13, [0xFFFFFFFFFD265417]
        rcx = 0x98CD10A39FEEABC3;               //mov rcx, 0x98CD10A39FEEABC3
        rax *= rcx;             //imul rax, rcx
        rcx = rbx + 0x8af0;             //lea rcx, [rbx+0x8AF0]
        rcx += r11;             //add rcx, r11
        rax += rcx;             //add rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x10;           //shr rcx, 0x10
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x20;           //shr rcx, 0x20
        rax ^= rcx;             //xor rax, rcx
        rcx = r11;              //mov rcx, r11
        rcx = ~rcx;             //not rcx
        rcx ^= r13;             //xor rcx, r13
        rax += rcx;             //add rax, rcx
        rcx = 0xDF8A1660CBF5F30F;               //mov rcx, 0xDF8A1660CBF5F30F
        rax *= rcx;             //imul rax, rcx
        rcx = 0xA829D63D19635A8D;               //mov rcx, 0xA829D63D19635A8D
        rax ^= rcx;             //xor rax, rcx
        rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
        rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
        rcx ^= r9;              //xor rcx, r9
        rcx = ~rcx;             //not rcx
        rax *= DMA::ReadPtr<uintptr_t>(rcx + 0x19);             //imul rax, [rcx+0x19]
        rax ^= r11;             //xor rax, r11
        return rax;
    }
    case 11:
    {
        r10 = DMA::ReadPtr<uintptr_t>(DMA::BaseAddress + 0x94D610E);              //mov r10, [0x000000000672C03D]
        rbx = DMA::BaseAddress;           //lea rbx, [0xFFFFFFFFFD255F28]
        rdx = rax;              //mov rdx, rax
        rdx >>= 0x23;           //shr rdx, 0x23
        rcx = DMA::BaseAddress + 0x17E7D121;              //lea rcx, [0x00000000150D2D05]
        rdx ^= rcx;             //xor rdx, rcx
        rcx = r11 + 0x1;                //lea rcx, [r11+0x01]
        rdx ^= r11;             //xor rdx, r11
        rdx ^= rax;             //xor rdx, rax
        rax = DMA::BaseAddress + 0x7D39B186;              //lea rax, [0x000000007A5F0D56]
        rax *= rcx;             //imul rax, rcx
        rax += rdx;             //add rax, rdx
        rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
        rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
        rcx ^= r10;             //xor rcx, r10
        rcx = ~rcx;             //not rcx
        rax *= DMA::ReadPtr<uintptr_t>(rcx + 0x19);             //imul rax, [rcx+0x19]
        rcx = rbx + 0x8cb1;             //lea rcx, [rbx+0x8CB1]
        rcx += r11;             //add rcx, r11
        rax ^= rcx;             //xor rax, rcx
        rax ^= r11;             //xor rax, r11
        rcx = 0x71B5B118240CFD7D;               //mov rcx, 0x71B5B118240CFD7D
        rax *= rcx;             //imul rax, rcx
        rcx = rbx + 0x2611654c;                 //lea rcx, [rbx+0x2611654C]
        rcx += r11;             //add rcx, r11
        rax += rcx;             //add rax, rcx
        return rax;
    }
    case 12:
    {
        r10 = DMA::ReadPtr<uintptr_t>(DMA::BaseAddress + 0x94D610E);              //mov r10, [0x000000000672BC56]
        rbx = DMA::BaseAddress;           //lea rbx, [0xFFFFFFFFFD255B41]
        rdx = DMA::BaseAddress + 0x4291859E;              //lea rdx, [0x000000003FB6E085]
        rax -= rbx;             //sub rax, rbx
        rcx = rdx;              //mov rcx, rdx
        rcx = ~rcx;             //not rcx
        rcx ^= r11;             //xor rcx, r11
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x10;           //shr rcx, 0x10
        rax ^= rcx;             //xor rax, rcx
        rdx = 0;                //and rdx, 0xFFFFFFFFC0000000
        rdx = _rotl64(rdx, 0x10);               //rol rdx, 0x10
        rdx ^= r10;             //xor rdx, r10
        rcx = rax;              //mov rcx, rax
        rdx = ~rdx;             //not rdx
        rcx >>= 0x20;           //shr rcx, 0x20
        rax ^= rcx;             //xor rax, rcx
        rcx = 0x6A01EB295C695943;               //mov rcx, 0x6A01EB295C695943
        rax *= rcx;             //imul rax, rcx
        rcx = 0x9BBE6575DCB15C28;               //mov rcx, 0x9BBE6575DCB15C28
        rax ^= rcx;             //xor rax, rcx
        rax *= DMA::ReadPtr<uintptr_t>(rdx + 0x19);             //imul rax, [rdx+0x19]
        rcx = 0x9A76A1C3B04C8361;               //mov rcx, 0x9A76A1C3B04C8361
        rax *= rcx;             //imul rax, rcx
        rax -= rbx;             //sub rax, rbx
        return rax;
    }
    case 13:
    {
        r10 = DMA::ReadPtr<uintptr_t>(DMA::BaseAddress + 0x94D610E);              //mov r10, [0x000000000672B7B5]
        rbx = DMA::BaseAddress;           //lea rbx, [0xFFFFFFFFFD2556A0]
        rax ^= rbx;             //xor rax, rbx
        rcx = 0x424E7D3CE7A4BDA3;               //mov rcx, 0x424E7D3CE7A4BDA3
        rax *= rcx;             //imul rax, rcx
        rcx = DMA::BaseAddress + 0x1A767856;              //lea rcx, [0x00000000179BCAC2]
        rcx = ~rcx;             //not rcx
        rcx ^= r11;             //xor rcx, r11
        rax += rcx;             //add rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0xF;            //shr rcx, 0x0F
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x1E;           //shr rcx, 0x1E
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x3C;           //shr rcx, 0x3C
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x1;            //shr rcx, 0x01
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x2;            //shr rcx, 0x02
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x4;            //shr rcx, 0x04
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x8;            //shr rcx, 0x08
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x10;           //shr rcx, 0x10
        rax ^= rcx;             //xor rax, rcx
        rdx = 0;                //and rdx, 0xFFFFFFFFC0000000
        rdx = _rotl64(rdx, 0x10);               //rol rdx, 0x10
        rcx = rax;              //mov rcx, rax
        rdx ^= r10;             //xor rdx, r10
        rcx >>= 0x20;           //shr rcx, 0x20
        rdx = ~rdx;             //not rdx
        rax ^= rcx;             //xor rax, rcx
        rax *= DMA::ReadPtr<uintptr_t>(rdx + 0x19);             //imul rax, [rdx+0x19]
        rdx = DMA::BaseAddress + 0x31EB9108;              //lea rdx, [0x000000002F10E547]
        rdx += r11;             //add rdx, r11
        rcx = rax;              //mov rcx, rax
        rax = 0x8DB30096C278A251;               //mov rax, 0x8DB30096C278A251
        rcx *= rax;             //imul rcx, rax
        rax = rdx;              //mov rax, rdx
        rax ^= rcx;             //xor rax, rcx
        return rax;
    }
    case 14:
    {
        r10 = DMA::ReadPtr<uintptr_t>(DMA::BaseAddress + 0x94D610E);              //mov r10, [0x000000000672B2A1]
        rbx = DMA::BaseAddress;           //lea rbx, [0xFFFFFFFFFD255181]
        rdx = DMA::BaseAddress + 0xA832;          //lea rdx, [0xFFFFFFFFFD25F5DE]
        rdx += r11;             //add rdx, r11
        rdx ^= rax;             //xor rdx, rax
        rax = r11;              //mov rax, r11
        rax = ~rax;             //not rax
        rax += rdx;             //add rax, rdx
        rax -= rbx;             //sub rax, rbx
        rax -= 0x2FECE2F9;              //sub rax, 0x2FECE2F9
        rcx = DMA::BaseAddress + 0x4948;          //lea rcx, [0xFFFFFFFFFD25971D]
        rcx += r11;             //add rcx, r11
        rax += rcx;             //add rax, rcx
        rcx = 0xE986304E17E64F7D;               //mov rcx, 0xE986304E17E64F7D
        rax *= rcx;             //imul rax, rcx
        rcx = DMA::BaseAddress + 0x5BB7;          //lea rcx, [0xFFFFFFFFFD25ABA7]
        rcx = ~rcx;             //not rcx
        rcx -= r11;             //sub rcx, r11
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x1A;           //shr rcx, 0x1A
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x34;           //shr rcx, 0x34
        rax ^= rcx;             //xor rax, rcx
        rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
        rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
        rcx ^= r10;             //xor rcx, r10
        rcx = ~rcx;             //not rcx
        rax *= DMA::ReadPtr<uintptr_t>(rcx + 0x19);             //imul rax, [rcx+0x19]
        rcx = r11;              //mov rcx, r11
        rcx = ~rcx;             //not rcx
        uintptr_t RSP_0xFFFFFFFFFFFFFF88;
        RSP_0xFFFFFFFFFFFFFF88 = DMA::BaseAddress + 0x30A5920C;           //lea rcx, [0x000000002DCAE398] : RBP+0xFFFFFFFFFFFFFF88
        rcx ^= RSP_0xFFFFFFFFFFFFFF88;          //xor rcx, [rbp-0x78]
        rax += rcx;             //add rax, rcx
        return rax;
    }
    case 15:
    {
        r10 = DMA::ReadPtr<uintptr_t>(DMA::BaseAddress + 0x94D610E);              //mov r10, [0x000000000672AD52]
        rbx = DMA::BaseAddress;           //lea rbx, [0xFFFFFFFFFD254C3D]
        rdx = DMA::BaseAddress + 0x56C36699;              //lea rdx, [0x0000000053E8B22D]
        rcx = 0x14288A7031FA1D2A;               //mov rcx, 0x14288A7031FA1D2A
        rax += rcx;             //add rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0xA;            //shr rcx, 0x0A
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x14;           //shr rcx, 0x14
        rax ^= rcx;             //xor rax, rcx
        rcx = rax;              //mov rcx, rax
        rcx >>= 0x28;           //shr rcx, 0x28
        rax ^= rcx;             //xor rax, rcx
        rcx = 0xF471F0FE111CB275;               //mov rcx, 0xF471F0FE111CB275
        rax *= rcx;             //imul rax, rcx
        rcx = rdx;              //mov rcx, rdx
        rcx = ~rcx;             //not rcx
        rcx *= r11;             //imul rcx, r11
        rax ^= rcx;             //xor rax, rcx
        rax -= r11;             //sub rax, r11
        rax -= rbx;             //sub rax, rbx
        rax -= 0x57EC1422;              //sub rax, 0x57EC1422
        rcx = DMA::BaseAddress + 0xF4C;           //lea rcx, [0xFFFFFFFFFD2558D2]
        rcx *= r11;             //imul rcx, r11
        rax += rcx;             //add rax, rcx
        rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
        rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
        rcx ^= r10;             //xor rcx, r10
        rcx = ~rcx;             //not rcx
        rax *= DMA::ReadPtr<uintptr_t>(rcx + 0x19);             //imul rax, [rcx+0x19]
        rcx = DMA::BaseAddress + 0x1793;          //lea rcx, [0xFFFFFFFFFD256087]
        rcx -= r11;             //sub rcx, r11
        rax ^= rcx;             //xor rax, rcx
        return rax;
    }
    }
}
inline uintptr_t decrypt_bone_base()
{
    const uint64_t mb = DMA::BaseAddress;
    uint64_t rax = mb, rbx = mb, rcx = mb, rdx = mb, rdi = mb, rsi = mb, r8 = mb, r9 = mb, r10 = mb, r11 = mb, r12 = mb, r13 = mb, r14 = mb, r15 = mb;
    rdx = DMA::ReadPtr<uintptr_t>(DMA::BaseAddress + 0xCED09C0);
    if (!rdx)
        return rdx;
    r11 = DMA::PebAddress;              //mov r11, gs:[rax]
    rax = r11;              //mov rax, r11
    rax = _rotr64(rax, 0x15);               //ror rax, 0x15
    rax &= 0xF;
    switch (rax) {
    case 0:
    {
        r9 = DMA::ReadPtr<uintptr_t>(DMA::BaseAddress + 0x94D61FC);               //mov r9, [0x00000000070AAE68]
        r15 = DMA::BaseAddress + 0x629DAB46;              //lea r15, [0x00000000605AF7AB]
        r13 = DMA::BaseAddress + 0x9895;          //lea r13, [0xFFFFFFFFFDBDE4EE]
        rax = 0xAC145E023332D189;               //mov rax, 0xAC145E023332D189
        rdx ^= rax;             //xor rdx, rax
        rax = r15;              //mov rax, r15
        rax = ~rax;             //not rax
        rax *= r11;             //imul rax, r11
        rdx += rax;             //add rdx, rax
        rax = 0xFDEBD2F07B05670D;               //mov rax, 0xFDEBD2F07B05670D
        rdx *= rax;             //imul rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x3;            //shr rax, 0x03
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x6;            //shr rax, 0x06
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0xC;            //shr rax, 0x0C
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x18;           //shr rax, 0x18
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x30;           //shr rax, 0x30
        rdx ^= rax;             //xor rdx, rax
        rax = 0xF0805972B46E082;                //mov rax, 0xF0805972B46E082
        rdx -= rax;             //sub rdx, rax
        rax = r11;              //mov rax, r11
        rax ^= r13;             //xor rax, r13
        rdx += rax;             //add rdx, rax
        rax = 0;                //and rax, 0xFFFFFFFFC0000000
        rax = _rotl64(rax, 0x10);               //rol rax, 0x10
        rax ^= r9;              //xor rax, r9
        rax = _byteswap_uint64(rax);            //bswap rax
        rdx *= DMA::ReadPtr<uintptr_t>(rax + 0x11);             //imul rdx, [rax+0x11]
        rax = rdx;              //mov rax, rdx
        rax >>= 0x4;            //shr rax, 0x04
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x8;            //shr rax, 0x08
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x10;           //shr rax, 0x10
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x20;           //shr rax, 0x20
        rdx ^= rax;             //xor rdx, rax
        return rdx;
    }
    case 1:
    {
        r9 = DMA::ReadPtr<uintptr_t>(DMA::BaseAddress + 0x94D61FC);               //mov r9, [0x00000000070AA7ED]
        rax = 0;                //and rax, 0xFFFFFFFFC0000000
        rax = _rotl64(rax, 0x10);               //rol rax, 0x10
        rax ^= r9;              //xor rax, r9
        rax = _byteswap_uint64(rax);            //bswap rax
        rdx *= DMA::ReadPtr<uintptr_t>(rax + 0x11);             //imul rdx, [rax+0x11]
        rax = 0x3ECBF33498144A56;               //mov rax, 0x3ECBF33498144A56
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0xA;            //shr rax, 0x0A
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x14;           //shr rax, 0x14
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x28;           //shr rax, 0x28
        rdx ^= rax;             //xor rdx, rax
        rax = 0x87F19886B363B05B;               //mov rax, 0x87F19886B363B05B
        rdx *= rax;             //imul rdx, rax
        rdx -= r11;             //sub rdx, r11
        rax = 0x6303659E1F345AFF;               //mov rax, 0x6303659E1F345AFF
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x15;           //shr rax, 0x15
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x2A;           //shr rax, 0x2A
        rdx ^= rax;             //xor rdx, rax
        rdx += r11;             //add rdx, r11
        return rdx;
    }
    case 2:
    {
        r10 = DMA::ReadPtr<uintptr_t>(DMA::BaseAddress + 0x94D61FC);              //mov r10, [0x00000000070AA36D]
        r13 = DMA::BaseAddress + 0x6F7AC17A;              //lea r13, [0x000000006D3802D8]
        rdx += r11;             //add rdx, r11
        rax = rdx;              //mov rax, rdx
        rax >>= 0x13;           //shr rax, 0x13
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x26;           //shr rax, 0x26
        rdx ^= rax;             //xor rdx, rax
        rax = DMA::BaseAddress + 0x62BA;          //lea rax, [0xFFFFFFFFFDBDA121]
        rax -= r11;             //sub rax, r11
        rdx += rax;             //add rdx, rax
        rax = 0x6367F6E201B667AF;               //mov rax, 0x6367F6E201B667AF
        rdx *= rax;             //imul rdx, rax
        rax = 0x7EA109C91958478C;               //mov rax, 0x7EA109C91958478C
        rdx -= rax;             //sub rdx, rax
        rdx ^= r11;             //xor rdx, r11
        rdx ^= r13;             //xor rdx, r13
        rax = 0x79658B29969CD86A;               //mov rax, 0x79658B29969CD86A
        rdx -= rax;             //sub rdx, rax
        rax = 0;                //and rax, 0xFFFFFFFFC0000000
        rax = _rotl64(rax, 0x10);               //rol rax, 0x10
        rax ^= r10;             //xor rax, r10
        rax = _byteswap_uint64(rax);            //bswap rax
        rdx *= DMA::ReadPtr<uintptr_t>(rax + 0x11);             //imul rdx, [rax+0x11]
        return rdx;
    }
    case 3:
    {
        r9 = DMA::ReadPtr<uintptr_t>(DMA::BaseAddress + 0x94D61FC);               //mov r9, [0x00000000070A9EBD]
        r14 = DMA::BaseAddress + 0xF8CE;          //lea r14, [0xFFFFFFFFFDBE357C]
        rax = rdx;              //mov rax, rdx
        rax >>= 0x20;           //shr rax, 0x20
        rdx ^= rax;             //xor rdx, rax
        rax = 0xEA0A19EF431520D;                //mov rax, 0xEA0A19EF431520D
        rdx ^= rax;             //xor rdx, rax
        rax = 0xFFFFFFFF93B5ED93;               //mov rax, 0xFFFFFFFF93B5ED93
        rax -= r11;             //sub rax, r11
        rax -= DMA::BaseAddress;          //sub rax, [rsp+0xA0] -- didn't find trace -> use base
        rdx += rax;             //add rdx, rax
        rax = r11;              //mov rax, r11
        rax *= r14;             //imul rax, r14
        rdx -= rax;             //sub rdx, rax
        rax = 0x39F863E9187B3F65;               //mov rax, 0x39F863E9187B3F65
        rdx *= rax;             //imul rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x1F;           //shr rax, 0x1F
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x3E;           //shr rax, 0x3E
        rdx ^= rax;             //xor rdx, rax
        rax = 0x44AFB2020B72DD38;               //mov rax, 0x44AFB2020B72DD38
        rdx += rax;             //add rdx, rax
        rax = 0;                //and rax, 0xFFFFFFFFC0000000
        rax = _rotl64(rax, 0x10);               //rol rax, 0x10
        rax ^= r9;              //xor rax, r9
        rax = _byteswap_uint64(rax);            //bswap rax
        rdx *= DMA::ReadPtr<uintptr_t>(rax + 0x11);             //imul rdx, [rax+0x11]
        return rdx;
    }
    case 4:
    {
        r9 = DMA::ReadPtr<uintptr_t>(DMA::BaseAddress + 0x94D61FC);               //mov r9, [0x00000000070A99A2]
        r15 = DMA::BaseAddress + 0xD76E;          //lea r15, [0xFFFFFFFFFDBE0F01]
        rax = r15;              //mov rax, r15
        rax = ~rax;             //not rax
        rax ^= r11;             //xor rax, r11
        rdx -= rax;             //sub rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x24;           //shr rax, 0x24
        rdx ^= rax;             //xor rdx, rax
        rax = 0x2690031C441C94ED;               //mov rax, 0x2690031C441C94ED
        rdx *= rax;             //imul rdx, rax
        rdx ^= r11;             //xor rdx, r11
        rax = 0xA3A6498F1C56BC17;               //mov rax, 0xA3A6498F1C56BC17
        rdx ^= rax;             //xor rdx, rax
        rdx -= r11;             //sub rdx, r11
        rax = 0;                //and rax, 0xFFFFFFFFC0000000
        rax = _rotl64(rax, 0x10);               //rol rax, 0x10
        rax ^= r9;              //xor rax, r9
        rax = _byteswap_uint64(rax);            //bswap rax
        rdx *= DMA::ReadPtr<uintptr_t>(rax + 0x11);             //imul rdx, [rax+0x11]
        return rdx;
    }
    case 5:
    {
        r10 = DMA::ReadPtr<uintptr_t>(DMA::BaseAddress + 0x94D61FC);              //mov r10, [0x00000000070A9555]
        rax = DMA::BaseAddress;           //lea rax, [0xFFFFFFFFFDBD318C]
        rdx += rax;             //add rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x19;           //shr rax, 0x19
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x32;           //shr rax, 0x32
        rdx ^= rax;             //xor rdx, rax
        rax = 0;                //and rax, 0xFFFFFFFFC0000000
        rax = _rotl64(rax, 0x10);               //rol rax, 0x10
        rax ^= r10;             //xor rax, r10
        rax = _byteswap_uint64(rax);            //bswap rax
        rcx = DMA::ReadPtr<uintptr_t>(rax + 0x11);              //mov rcx, [rax+0x11]
        rax = r11;              //mov rax, r11
        uintptr_t RSP_0x48;
        RSP_0x48 = DMA::BaseAddress + 0x598F00A5;                 //lea rax, [0x00000000574C33A4] : RSP+0x48
        rax *= RSP_0x48;                //imul rax, [rsp+0x48]
        rax -= DMA::BaseAddress;          //sub rax, [rsp+0xA0] -- didn't find trace -> use base
        rdx += rax;             //add rdx, rax
        rax = 0xC6D870371839E04D;               //mov rax, 0xC6D870371839E04D
        rdx *= rax;             //imul rdx, rax
        rax = 0x2435BC22D4E2922B;               //mov rax, 0x2435BC22D4E2922B
        rdx -= rax;             //sub rdx, rax
        rdx *= rcx;             //imul rdx, rcx
        rax = 0xBBD9DF3CECEEFE74;               //mov rax, 0xBBD9DF3CECEEFE74
        rdx ^= rax;             //xor rdx, rax
        rax = 0x23B4F504FA125955;               //mov rax, 0x23B4F504FA125955
        rdx *= rax;             //imul rdx, rax
        return rdx;
    }
    case 6:
    {
        r10 = DMA::ReadPtr<uintptr_t>(DMA::BaseAddress + 0x94D61FC);              //mov r10, [0x00000000070A9119]
        rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
        rax = r11;              //mov rax, r11
        rax -= DMA::BaseAddress;          //sub rax, [rsp+0xA0] -- didn't find trace -> use base
        rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
        rax += 0xFFFFFFFFA7D1474C;              //add rax, 0xFFFFFFFFA7D1474C
        rdx += rax;             //add rdx, rax
        rcx ^= r10;             //xor rcx, r10
        rcx = _byteswap_uint64(rcx);            //bswap rcx
        rdx *= DMA::ReadPtr<uintptr_t>(rcx + 0x11);             //imul rdx, [rcx+0x11]
        rax = 0xFFFFFFFFC0CD4EE3;               //mov rax, 0xFFFFFFFFC0CD4EE3
        rax -= r11;             //sub rax, r11
        rax -= DMA::BaseAddress;          //sub rax, [rsp+0xA0] -- didn't find trace -> use base
        rdx += rax;             //add rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x23;           //shr rax, 0x23
        rax ^= rdx;             //xor rax, rdx
        rdx = 0x5A8397EF69EB3410;               //mov rdx, 0x5A8397EF69EB3410
        rax += r11;             //add rax, r11
        rax += rdx;             //add rax, rdx
        rdx = DMA::BaseAddress;           //lea rdx, [0xFFFFFFFFFDBD2C26]
        rdx += rax;             //add rdx, rax
        rax = 0x94B908816CF2DBE1;               //mov rax, 0x94B908816CF2DBE1
        rdx *= rax;             //imul rdx, rax
        return rdx;
    }
    case 7:
    {
        r10 = DMA::ReadPtr<uintptr_t>(DMA::BaseAddress + 0x94D61FC);              //mov r10, [0x00000000070A8D08]
        r15 = DMA::BaseAddress + 0x6B60;          //lea r15, [0xFFFFFFFFFDBD9659]
        rax = DMA::BaseAddress;           //lea rax, [0xFFFFFFFFFDBD280F]
        rax += 0xC77B;          //add rax, 0xC77B
        rax += r11;             //add rax, r11
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x9;            //shr rax, 0x09
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x12;           //shr rax, 0x12
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x24;           //shr rax, 0x24
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x13;           //shr rax, 0x13
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x26;           //shr rax, 0x26
        rdx ^= rax;             //xor rdx, rax
        rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
        rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
        rcx ^= r10;             //xor rcx, r10
        rax = r15;              //mov rax, r15
        rax = ~rax;             //not rax
        rax *= r11;             //imul rax, r11
        rcx = _byteswap_uint64(rcx);            //bswap rcx
        rdx += rax;             //add rdx, rax
        rax = 0x3BAB7EE1C2FB5485;               //mov rax, 0x3BAB7EE1C2FB5485
        rdx *= DMA::ReadPtr<uintptr_t>(rcx + 0x11);             //imul rdx, [rcx+0x11]
        rdx += rax;             //add rdx, rax
        rax = 0xD64310FF7669DED5;               //mov rax, 0xD64310FF7669DED5
        rdx *= rax;             //imul rdx, rax
        rax = 0xC9A0080E2B52320A;               //mov rax, 0xC9A0080E2B52320A
        rdx ^= rax;             //xor rdx, rax
        return rdx;
    }
    case 8:
    {
        r10 = DMA::ReadPtr<uintptr_t>(DMA::BaseAddress + 0x94D61FC);              //mov r10, [0x00000000070A8735]
        rax = r11;              //mov rax, r11
        rax -= DMA::BaseAddress;          //sub rax, [rsp+0xA0] -- didn't find trace -> use base
        rax += 0xFFFFFFFF954B94E9;              //add rax, 0xFFFFFFFF954B94E9
        rdx += rax;             //add rdx, rax
        rax = 0;                //and rax, 0xFFFFFFFFC0000000
        rax = _rotl64(rax, 0x10);               //rol rax, 0x10
        rax ^= r10;             //xor rax, r10
        rax = _byteswap_uint64(rax);            //bswap rax
        rdx *= DMA::ReadPtr<uintptr_t>(rax + 0x11);             //imul rdx, [rax+0x11]
        rax = rdx;              //mov rax, rdx
        rax >>= 0xE;            //shr rax, 0x0E
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x1C;           //shr rax, 0x1C
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x38;           //shr rax, 0x38
        rdx ^= rax;             //xor rdx, rax
        rax = 0x28853EAC80AAB90;                //mov rax, 0x28853EAC80AAB90
        rdx -= rax;             //sub rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x21;           //shr rax, 0x21
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0xB;            //shr rax, 0x0B
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x16;           //shr rax, 0x16
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x2C;           //shr rax, 0x2C
        rdx ^= rax;             //xor rdx, rax
        rax = 0x9ED615C5A516F48D;               //mov rax, 0x9ED615C5A516F48D
        rdx *= rax;             //imul rdx, rax
        rax = 0x4A5451CFD1051B0F;               //mov rax, 0x4A5451CFD1051B0F
        rdx *= rax;             //imul rdx, rax
        return rdx;
    }
    case 9:
    {
        r10 = DMA::ReadPtr<uintptr_t>(DMA::BaseAddress + 0x94D61FC);              //mov r10, [0x00000000070A821C]
        r13 = DMA::BaseAddress + 0x9F7F;          //lea r13, [0xFFFFFFFFFDBDBF8C]
        rcx = DMA::BaseAddress + 0x590B7B0F;              //lea rcx, [0x0000000056C89AA7]
        rax = rdx;              //mov rax, rdx
        rax >>= 0x25;           //shr rax, 0x25
        rdx ^= rax;             //xor rdx, rax
        rax = 0;                //and rax, 0xFFFFFFFFC0000000
        rax = _rotl64(rax, 0x10);               //rol rax, 0x10
        rax ^= r10;             //xor rax, r10
        rax = _byteswap_uint64(rax);            //bswap rax
        rdx *= DMA::ReadPtr<uintptr_t>(rax + 0x11);             //imul rdx, [rax+0x11]
        rax = 0xE41AAE0B4978C7A7;               //mov rax, 0xE41AAE0B4978C7A7
        rdx *= rax;             //imul rdx, rax
        rax = 0x4884ED1EDA36D9B2;               //mov rax, 0x4884ED1EDA36D9B2
        rdx -= rax;             //sub rdx, rax
        rax = r11;              //mov rax, r11
        rax ^= r13;             //xor rax, r13
        rdx ^= rax;             //xor rdx, rax
        rax = 0xA5F46429036B04E5;               //mov rax, 0xA5F46429036B04E5
        rdx *= rax;             //imul rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x27;           //shr rax, 0x27
        rdx ^= rax;             //xor rdx, rax
        rdx -= r11;             //sub rdx, r11
        rdx += rcx;             //add rdx, rcx
        return rdx;
    }
    case 10:
    {
        r9 = DMA::ReadPtr<uintptr_t>(DMA::BaseAddress + 0x94D61FC);               //mov r9, [0x00000000070A7D8E]
        rdx -= DMA::BaseAddress;          //sub rdx, [rsp+0xA0] -- didn't find trace -> use base
        rax = 0;                //and rax, 0xFFFFFFFFC0000000
        rax = _rotl64(rax, 0x10);               //rol rax, 0x10
        rax ^= r9;              //xor rax, r9
        rax = _byteswap_uint64(rax);            //bswap rax
        rdx *= DMA::ReadPtr<uintptr_t>(rax + 0x11);             //imul rdx, [rax+0x11]
        rax = r11;              //mov rax, r11
        rax -= DMA::BaseAddress;          //sub rax, [rsp+0xA0] -- didn't find trace -> use base
        rax += 0xFFFFFFFFFFFF88EC;              //add rax, 0xFFFFFFFFFFFF88EC
        rdx += rax;             //add rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x12;           //shr rax, 0x12
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x24;           //shr rax, 0x24
        rdx ^= rax;             //xor rdx, rax
        rax = 0x4DBC160E13E56349;               //mov rax, 0x4DBC160E13E56349
        rdx *= rax;             //imul rdx, rax
        rax = DMA::BaseAddress;           //lea rax, [0xFFFFFFFFFDBD1A64]
        rdx ^= rax;             //xor rdx, rax
        rax = DMA::BaseAddress;           //lea rax, [0xFFFFFFFFFDBD1936]
        rdx += rax;             //add rdx, rax
        return rdx;
    }
    case 11:
    {
        r10 = DMA::ReadPtr<uintptr_t>(DMA::BaseAddress + 0x94D61FC);              //mov r10, [0x00000000070A78E8]
        rax = 0;                //and rax, 0xFFFFFFFFC0000000
        rax = _rotl64(rax, 0x10);               //rol rax, 0x10
        rax ^= r10;             //xor rax, r10
        rax = _byteswap_uint64(rax);            //bswap rax
        rdx *= DMA::ReadPtr<uintptr_t>(rax + 0x11);             //imul rdx, [rax+0x11]
        rax = DMA::BaseAddress + 0x73A4FAE9;              //lea rax, [0x0000000071620F0D]
        rax = ~rax;             //not rax
        rdx -= r11;             //sub rdx, r11
        rdx += rax;             //add rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x16;           //shr rax, 0x16
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x2C;           //shr rax, 0x2C
        rdx ^= rax;             //xor rdx, rax
        rax = 0x861DF3431C84C629;               //mov rax, 0x861DF3431C84C629
        rdx *= rax;             //imul rdx, rax
        rax = 0x714B44E8CE73C4F0;               //mov rax, 0x714B44E8CE73C4F0
        rdx -= rax;             //sub rdx, rax
        rax = DMA::BaseAddress;           //lea rax, [0xFFFFFFFFFDBD1388]
        rcx = rax * 0xFFFFFFFFFFFFFFFE;                 //imul rcx, rax, 0xFFFFFFFFFFFFFFFE
        rax = 0x6F9175143B9ED737;               //mov rax, 0x6F9175143B9ED737
        rdx += rax;             //add rdx, rax
        rdx += rcx;             //add rdx, rcx
        return rdx;
    }
    case 12:
    {
        r10 = DMA::ReadPtr<uintptr_t>(DMA::BaseAddress + 0x94D61FC);              //mov r10, [0x00000000070A7529]
        r15 = DMA::BaseAddress + 0xD3DA;          //lea r15, [0xFFFFFFFFFDBDE6F4]
        rcx = r11;              //mov rcx, r11
        rcx = ~rcx;             //not rcx
        rax = DMA::BaseAddress + 0x1F86111B;              //lea rax, [0x000000001D4320F8]
        rax = ~rax;             //not rax
        rcx *= rax;             //imul rcx, rax
        rax = r15;              //mov rax, r15
        rax -= r11;             //sub rax, r11
        rax += rdx;             //add rax, rdx
        rdx = rcx;              //mov rdx, rcx
        rdx ^= rax;             //xor rdx, rax
        rax = 0;                //and rax, 0xFFFFFFFFC0000000
        rax = _rotl64(rax, 0x10);               //rol rax, 0x10
        rax ^= r10;             //xor rax, r10
        rax = _byteswap_uint64(rax);            //bswap rax
        rdx *= DMA::ReadPtr<uintptr_t>(rax + 0x11);             //imul rdx, [rax+0x11]
        rcx = DMA::BaseAddress;           //lea rcx, [0xFFFFFFFFFDBD118D]
        rax = r11;              //mov rax, r11
        rax -= rcx;             //sub rax, rcx
        rcx = rax + 0xffffffffca7be9d9;                 //lea rcx, [rax-0x35841627]
        rcx += rdx;             //add rcx, rdx
        rax = rcx;              //mov rax, rcx
        rax >>= 0x18;           //shr rax, 0x18
        rcx ^= rax;             //xor rcx, rax
        rax = 0xFBA7ABC8BBB4629D;               //mov rax, 0xFBA7ABC8BBB4629D
        rdx = rcx;              //mov rdx, rcx
        rdx >>= 0x30;           //shr rdx, 0x30
        rdx ^= rcx;             //xor rdx, rcx
        rdx *= rax;             //imul rdx, rax
        rax = 0x1FE6307AA1F54B4D;               //mov rax, 0x1FE6307AA1F54B4D
        rdx *= rax;             //imul rdx, rax
        rax = 0x57A7A919AF723E1B;               //mov rax, 0x57A7A919AF723E1B
        rdx -= rax;             //sub rdx, rax
        return rdx;
    }
    case 13:
    {
        r9 = DMA::ReadPtr<uintptr_t>(DMA::BaseAddress + 0x94D61FC);               //mov r9, [0x00000000070A712F]
        rax = rdx;              //mov rax, rdx
        rax >>= 0x1A;           //shr rax, 0x1A
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x34;           //shr rax, 0x34
        rdx ^= rax;             //xor rdx, rax
        rax = 0x525F068BC2643DF7;               //mov rax, 0x525F068BC2643DF7
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0xD;            //shr rax, 0x0D
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x1A;           //shr rax, 0x1A
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x34;           //shr rax, 0x34
        rdx ^= rax;             //xor rdx, rax
        rax = 0;                //and rax, 0xFFFFFFFFC0000000
        rax = _rotl64(rax, 0x10);               //rol rax, 0x10
        rax ^= r9;              //xor rax, r9
        rax = _byteswap_uint64(rax);            //bswap rax
        rdx *= DMA::ReadPtr<uintptr_t>(rax + 0x11);             //imul rdx, [rax+0x11]
        rax = 0x75DFF140FA1FB5BC;               //mov rax, 0x75DFF140FA1FB5BC
        rdx += rax;             //add rdx, rax
        rax = DMA::BaseAddress;           //lea rax, [0xFFFFFFFFFDBD0B66]
        rdx += rax;             //add rdx, rax
        rax = 0xE5945E699002C625;               //mov rax, 0xE5945E699002C625
        rdx *= rax;             //imul rdx, rax
        rax = DMA::BaseAddress;           //lea rax, [0xFFFFFFFFFDBD0B4E]
        rdx ^= rax;             //xor rdx, rax
        return rdx;
    }
    case 14:
    {
        r10 = DMA::ReadPtr<uintptr_t>(DMA::BaseAddress + 0x94D61FC);              //mov r10, [0x00000000070A6CCA]
        r15 = DMA::BaseAddress + 0x73A4A654;              //lea r15, [0x000000007161B10F]
        rax = 0x75736E13202430E1;               //mov rax, 0x75736E13202430E1
        rdx *= rax;             //imul rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x26;           //shr rax, 0x26
        rdx ^= rax;             //xor rdx, rax
        rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
        rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
        rcx ^= r10;             //xor rcx, r10
        rcx = _byteswap_uint64(rcx);            //bswap rcx
        rdx *= DMA::ReadPtr<uintptr_t>(rcx + 0x11);             //imul rdx, [rcx+0x11]
        rax = rdx;              //mov rax, rdx
        rax >>= 0x9;            //shr rax, 0x09
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x12;           //shr rax, 0x12
        rdx ^= rax;             //xor rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x24;           //shr rax, 0x24
        rdx ^= rax;             //xor rdx, rax
        rdx += r11;             //add rdx, r11
        rax = r11;              //mov rax, r11
        rax = ~rax;             //not rax
        rax *= r15;             //imul rax, r15
        rdx ^= rax;             //xor rdx, rax
        rax = 0xABD8E138F25E5687;               //mov rax, 0xABD8E138F25E5687
        rdx ^= rax;             //xor rdx, rax
        return rdx;
    }
    case 15:
    {
        r10 = DMA::ReadPtr<uintptr_t>(DMA::BaseAddress + 0x94D61FC);              //mov r10, [0x00000000070A6919]
        rsi = 0xB656FAE057EB613B;               //mov rsi, 0xB656FAE057EB613B
        rdx *= rsi;             //imul rdx, rsi
        rax = rdx;              //mov rax, rdx
        rax >>= 0x21;           //shr rax, 0x21
        rdx ^= rax;             //xor rdx, rax
        rax = 0;                //and rax, 0xFFFFFFFFC0000000
        rax = _rotl64(rax, 0x10);               //rol rax, 0x10
        rax ^= r10;             //xor rax, r10
        rax = _byteswap_uint64(rax);            //bswap rax
        rdx *= DMA::ReadPtr<uintptr_t>(rax + 0x11);             //imul rdx, [rax+0x11]
        rax = 0x5CA0A4447C245D90;               //mov rax, 0x5CA0A4447C245D90
        rdx -= rax;             //sub rdx, rax
        rdx -= r11;             //sub rdx, r11
        rax = 0xF071D0312866EB9D;               //mov rax, 0xF071D0312866EB9D
        rdx *= rax;             //imul rdx, rax
        rax = 0xFFFFFFFFFFFFF34A;               //mov rax, 0xFFFFFFFFFFFFF34A
        rax -= r11;             //sub rax, r11
        rax -= DMA::BaseAddress;          //sub rax, [rsp+0xA0] -- didn't find trace -> use base
        rdx += rax;             //add rdx, rax
        rax = rdx;              //mov rax, rdx
        rax >>= 0x21;           //shr rax, 0x21
        rdx ^= rax;             //xor rdx, rax
        return rdx;
    }
    }
}
inline uint16_t get_bone_index(uint32_t bone_index)
{
    const uint64_t mb = DMA::BaseAddress;
    uint64_t rax = mb, rbx = mb, rcx = mb, rdx = mb, rdi = mb, rsi = mb, r8 = mb, r9 = mb, r10 = mb, r11 = mb, r12 = mb, r13 = mb, r14 = mb, r15 = mb;
    rdi = bone_index;
    rcx = rdi * 0x13C8;
    rax = 0xD73F3E9D2DBEC8E7;               //mov rax, 0xD73F3E9D2DBEC8E7
    rax = _umul128(rax, rcx, (uintptr_t*)&rdx);             //mul rcx
    r11 = 0xCCCCCCCCCCCCCCCD;               //mov r11, 0xCCCCCCCCCCCCCCCD
    rbx = DMA::BaseAddress;           //lea rbx, [0xFFFFFFFFFD6DE45B]
    rdx >>= 0xD;            //shr rdx, 0x0D
    r10 = 0xE98285CCFA0AE387;               //mov r10, 0xE98285CCFA0AE387
    rax = rdx * 0x260F;             //imul rax, rdx, 0x260F
    rcx -= rax;             //sub rcx, rax
    rax = 0xC388D5333BAA90CD;               //mov rax, 0xC388D5333BAA90CD
    r8 = rcx * 0x260F;              //imul r8, rcx, 0x260F
    rax = _umul128(rax, r8, (uintptr_t*)&rdx);              //mul r8
    rax = r8;               //mov rax, r8
    rax -= rdx;             //sub rax, rdx
    rax >>= 0x1;            //shr rax, 0x01
    rax += rdx;             //add rax, rdx
    rax >>= 0xE;            //shr rax, 0x0E
    rax = rax * 0x4892;             //imul rax, rax, 0x4892
    r8 -= rax;              //sub r8, rax
    rax = r11;              //mov rax, r11
    rax = _umul128(rax, r8, (uintptr_t*)&rdx);              //mul r8
    rax = 0xBAA551EE51D6FD2D;               //mov rax, 0xBAA551EE51D6FD2D
    rdx >>= 0x3;            //shr rdx, 0x03
    rcx = rdx + rdx * 4;            //lea rcx, [rdx+rdx*4]
    rax = _umul128(rax, r8, (uintptr_t*)&rdx);              //mul r8
    rdx >>= 0xB;            //shr rdx, 0x0B
    rax = rdx + rcx * 2;            //lea rax, [rdx+rcx*2]
    rcx = rax * 0x15F2;             //imul rcx, rax, 0x15F2
    rax = r8 * 0x15F4;              //imul rax, r8, 0x15F4
    rax -= rcx;             //sub rax, rcx
    rax = DMA::Read<uint16_t>(rax + rbx * 1 + 0x95AC060, sizeof(rax));                //movzx eax, word ptr [rax+rbx*1+0x95AC060]
    r8 = rax * 0x13C8;              //imul r8, rax, 0x13C8
    rax = r10;              //mov rax, r10
    rax = _umul128(rax, r8, (uintptr_t*)&rdx);              //mul r8
    rax = r10;              //mov rax, r10
    rdx >>= 0xD;            //shr rdx, 0x0D
    rcx = rdx * 0x2315;             //imul rcx, rdx, 0x2315
    r8 -= rcx;              //sub r8, rcx
    r9 = r8 * 0x351B;               //imul r9, r8, 0x351B
    rax = _umul128(rax, r9, (uintptr_t*)&rdx);              //mul r9
    rax = r11;              //mov rax, r11
    rdx >>= 0xD;            //shr rdx, 0x0D
    rcx = rdx * 0x2315;             //imul rcx, rdx, 0x2315
    r9 -= rcx;              //sub r9, rcx
    rax = _umul128(rax, r9, (uintptr_t*)&rdx);              //mul r9
    rax = 0x18AB083902BDAB95;               //mov rax, 0x18AB083902BDAB95
    rdx >>= 0x4;            //shr rdx, 0x04
    rcx = rdx + rdx * 4;            //lea rcx, [rdx+rdx*4]
    rax = _umul128(rax, r9, (uintptr_t*)&rdx);              //mul r9
    rax = r9;               //mov rax, r9
    rax -= rdx;             //sub rax, rdx
    rax >>= 0x1;            //shr rax, 0x01
    rax += rdx;             //add rax, rdx
    rax >>= 0x8;            //shr rax, 0x08
    rax = rax + rcx * 4;            //lea rax, [rax+rcx*4]
    rcx = rax * 0x3A6;              //imul rcx, rax, 0x3A6
    rax = r9 * 0x3A8;               //imul rax, r9, 0x3A8
    rax -= rcx;             //sub rax, rcx
    r12 = DMA::Read<uint16_t>(rax + rbx * 1 + 0x95B9BE0, sizeof(r12));                //movsx r12d, word ptr [rax+rbx*1+0x95B9BE0]
    return r12;
}