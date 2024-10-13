/**
 * @file TLA25x8LowLevel.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-09-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#ifndef TLA25X28_LOW_LEVEL_H
#define TLS25X28_LOW_LEVEL_H

#include <stdint.h>

#include "TLA25x8Types.h"
#include "TLA25x8Registers.h"

// ~~~~~~~~~~~~ Low Level API ~~~~~~~~~~~~ //

/**
 * @brief 
 * 
 * @param device 
 * @param reg 
 * @param value 
 * @return uint8_t 
 */
uint8_t TLA25x8_WriteRegister(const TLA25x8* const device, const TLA25x8Register reg, const uint8_t value);

/**
 * @brief 
 * 
 * @param device 
 * @param base_reg 
 * @param buffer 
 * @param length 
 * @return uint8_t 
 */
uint8_t TLA25x8_WriteRegisters(const TLA25x8* const device, const TLA25x8Register base_reg, void* const buffer, const uint8_t length);

/**
 * @brief 
 * 
 * @param device 
 * @param reg 
 * @param buffer 
 * @return uint8_t 
 */
uint8_t TLA25x8_ReadRegister(const TLA25x8* const device, const TLA25x8Register reg, void* const buffer);

/**
 * @brief 
 * 
 * @param device 
 * @param base_reg 
 * @param buffer 
 * @param length 
 * @return uint8_t 
 */
uint8_t TLA25x8_ReadRegisters(const TLA25x8* const device, const TLA25x8Register base_reg, void* const buffer, const uint8_t length);

/**
 * @brief 
 * 
 * @param device 
 * @param reg 
 * @param bit_mask 
 * @return uint8_t 
 */
uint8_t TLA25x8_SetRegisterBits(const TLA25x8* const device, const TLA25x8Register reg, const uint8_t bit_mask);


/**
 * @brief 
 * 
 * @param device 
 * @param reg 
 * @param bit_mask 
 * @return uint8_t 
 */
uint8_t TLA25x8_ClearRegisterBits(const TLA25x8* const device, const TLA25x8Register reg, const uint8_t bit_mask);

// ~~~~~~~~~~~~ Bare Bones API ~~~~~~~~~~~ //

/**
 * @brief 
 * 
 * @param device 
 * @param buffer 
 * @param length 
 * @return uint8_t 
 */
uint8_t TLA25x8_Read(const TLA25x8* const device, void* const buffer, const uint8_t length);

/**
 * @brief 
 * 
 * @param device 
 * @param buffer 
 * @param length 
 * @return uint8_t 
 */
uint8_t TLA25x8_Write(const TLA25x8* const device, const void* const buffer, uint8_t length);

#endif
