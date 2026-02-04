/**
  ******************************************************************************
  *
  * @file    macro_def.h
  * @author  
  * @brief   Header file of macro definition module.
  *
  ******************************************************************************
  **/
  
#ifndef _MACRO_DEF_H
#define _MACRO_DEF_H


#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include <stdint.h>
#include <string.h>
/*********************
 *      DEFINES
 *********************/
#define MAX_VAL(x, y)      ((x) < (y)? (y) : (x))
#define MIN_VAL(x, y)      ((x) < (y)? (x) : (y))
#define ABS_VAL(d)         (((d) > 0)? (d) : 0 - (d))

#define REG8(x)             (*((volatile uint8_t*)(x)))
#define REG16(x)            (*((volatile uint16_t*)(x)))
#define REG32(x)            (*((volatile uint32_t*)(x)))

#define READ_REG8(x)        REG8(x)
#define READ_REG16(x)       REG16(x)
#define READ_REG32(x)       REG32(x)
#define WRITE_REG8(x,d)     do { REG8(x)  = (d); } while (0)
#define WRITE_REG16(x,d)    do { REG16(x) = (d); } while (0)
#define WRITE_REG32(x,d)    do { REG32(x) = (d); } while (0)
#define SET_REG8_BIT(x,b)  do { REG8(x)  |= (b); } while (0)
#define SET_REG16_BIT(x,b) do { REG16(x) |= (b); } while (0)
#define SET_REG32_BIT(x,b) do { REG32(x) |= (b); } while (0)
#define CLR_REG8_BIT(x,b)  do { REG8(x)  &= ~(b); } while (0)
#define CLR_REG16_BIT(x,b) do { REG16(x) &= ~(b); } while (0)
#define CLR_REG32_BIT(x,b) do { REG32(x) &= ~(b); } while (0)

#define ARRAY_SIZE(arr)      (sizeof(arr) / sizeof((arr)[0]))

#define OFFSET_OF(type, member) ((size_t)&(((type *)0)->member))

#define CONTAINER_OF(ptr, type, member) \
    ((type *)((uintptr_t)(ptr) - OFFSET_OF(type, member)))

/* 设置指定位为1 */
#define SET_BIT(REG, BIT)     ((REG) |= (1 << (BIT)))

/* 清除指定位 */
#define CLR_BIT(REG, BIT)     ((REG) &= ~(1 << (BIT)))

/* 翻转指定位 */
#define TOG_BIT(REG, BIT)     ((REG) ^= (1 << (BIT)))

/* 测试指定位是否为1 */
#define BIT_IS_SET(reg, bit)    ((reg) & (1 << (bit)))

/* 测试指定位是否为0 */
#define BIT_IS_CLR(reg, bit)    (!((reg) & (1 << (bit))))

#define BYTE0(x)    ((uint8_t)( (uint32_t)(x)         & 0xFF))

#define BYTE1(x)    ((uint8_t)(((uint32_t)(x) >>  8) & 0xFF))

#define BYTE2(x)    ((uint8_t)(((uint32_t)(x) >> 16) & 0xFF))

#define BYTE3(x)    ((uint8_t)(((uint32_t)(x) >> 24) & 0xFF))

#define MASK_BYTE(data,byte)  (((data)>>((byte)<<3))&0xff)

/* 2个uint8_t 合并成 uint16_t（高字节在前） */
#define MAKE_U16(high, low) \
    ((uint16_t)(((uint16_t)(high) << 8) | ((uint16_t)(low) & 0xFF)))


/* 4个uint8_t 合并成 uint32_t（最高字节在前） */
#define MAKE_U32(b3, b2, b1, b0) \
    ((uint32_t)(((uint32_t)(b3) << 24) | \
                ((uint32_t)(b2) << 16) | \
                ((uint32_t)(b1) <<  8) | \
                ((uint32_t)(b0)       )))

/* 16位字节序交换（高低字节对调） */
#define SWAP_U16(x) \
    ((uint16_t)((((uint16_t)(x) & 0xFF00) >> 8) | \
                (((uint16_t)(x) & 0x00FF) << 8)))

/* 主机序转网络序（32位，假设网络为big-endian） */
#define HTONL(x) \
    ((uint32_t)((((x) & 0x000000FFUL) << 24) | \
                (((x) & 0x0000FF00UL) <<  8) | \
                (((x) & 0x00FF0000UL) >>  8) | \
                (((x) & 0xFF000000UL) >> 24)))

#define HTONS(x) SWAP_U16(x)

/* 将位数转换为所需的字节数（向上取整，例如 1~8位 → 1字节，9~16位 → 2字节） */
#define BITS_TO_BYTES(n)    (((n) + 7u) >> 3)

/* 将字节数转换为位数（精确，例如 1字节 → 8位） */
#define BYTES_TO_BITS(n)    ((n) << 3)

// 通用宏：向下取整到 align 的倍数（floor）
#define ROUND_DOWN(x, align)    ((uint32_t)(x) & ~((uint32_t)(align) - 1u))

// 通用宏：向上取整到 align 的倍数（ceiling）
#define ROUND_UP(x, align)      ((uint32_t)(x) + (uint32_t)(align) - 1u) & ~((uint32_t)(align) - 1u)

// 常用特化版本
#define ROUND_DOWN_2(x)         ROUND_DOWN(x, 2)    // 向下对齐到 2 字节（word）
#define ROUND_DOWN_4(x)         ROUND_DOWN(x, 4)    // 向下对齐到 4 字节（dword）
#define ROUND_UP_2(x)           ROUND_UP(x, 2)      // 向上对齐到 2 字节
#define ROUND_UP_4(x)           ROUND_UP(x, 4)      // 向上对齐到 4 字节

#define MEM_CPY(d,s,n)      memcpy((d),(s),(n))
#define MEM_SET(addr,d,n)    memset((addr),(d),(n))
#define MEM_CMP(addr,d,n)    memcmp((addr),(d),(n))
#define STR_CPY(d,s)        strcpy((d),(s))
#define STR_LEN(s)          strlen(s)
#define STR_CMP(s1,s2)      strcmp(s1,s2)
#define STR_STR(s1,s2)      strstr(s1,s2)


#ifdef __cplusplus
}
#endif

#endif /*_MACRO_DEF_H*/


/******************************* (END OF FILE) *********************************/


