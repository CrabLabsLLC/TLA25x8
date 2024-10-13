/**
 * @file TLA25x8.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-09-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#ifndef TLA25X8_H
#define TLA25X8_H

#include <stdint.h>
#include <stdbool.h>

#include "TLA25x8Types.h" 
#include "TLA25x8Registers.h"

/**
 * @brief 
 * 
 * @param hal 
 * @param device 
 * @return TLA25x8* 
 */
TLA25x8* TLA2528_Init(const TLA2528HAL* const hal, const uint8_t address, TLA25x8* const device);

/**
 * @brief       
 * 
 * @param hal 
 * @param device 
 * @return TLA25x8* 
 */
TLA25x8* TLA2518_Init(const TLA2518HAL* const hal, 
                      void (*spi_chip_select)(const bool is_selected),
                      TLA25x8* const device);

/**
 * @brief 
 * 
 * @param device 
 * @param config 
 * @return TLA25x8* 
 */
TLA25x8* TLA25x8_Configure(const TLA25x8* const device, const TLA25x8Config* const config);


uint8_t TLA25x8_ReadGeneralConfig(const TLA25x8* const device, const bool)

/**
 * @brief 
 * 
 * @param device 
 * @return uint8_t 
 */
uint8_t TLA25x8_SetPinConfiguration(const TLA25x8* const device, const uint8_t gpio_mask);

/**
 * @brief 
 * 
 * @param device 
 * @param output_mask 
 * @return uint8_t 
 */
uint8_t TLA25x8_SetGPIODirection(const TLA25x8* const device, const uint8_t output_mask);

/**
 * @brief 
 * @note
 * @param device 
 * @param push_pull_mask 
 * @return uint8_t 
 */
uint8_t TLA25x8_SetGPIOOutputType(const TLA25x8* const device, const uint8_t push_pull_mask);


/**
 * @brief 
 * @note
 * @param device 
 * @param value 
 * @return uint8_t 
 */
uint8_t TLA25x8_SetGPIOOutputValue(const TLA25x8* const device, const uint8_t value);

/**
 * @brief 
 * @note
 * @param device 
 * @param value_buffer 
 * @return uint8_t 
 */
uint8_t TLA25x8_GetGPIOInputValue(const TLA25x8* const device, uint8_t* const value_buffer);

/**
 * @brief   
 * 
 * @param device 
 * @param mode 
 * @return uint8_t 
 */
uint8_t TLA25x8_SetADCScanMode(const TLA25x8* const device, const TLA25x8ScanMode mode);                                  

/**
 * @brief 
 * 
 * @param device 
 * @param channel_mask 
 * @return uint8_t 
 */
uint8_t TLA25x8SetADCAutoScanChannels(const TLA25x8* const device, const uint8_t channel_mask);

/**
 * @brief 
 * 
 * @param device 
 * @return uint8_t 
 */
uint8_t TLA25x8StartADCAutoScan(const TLA25x8* const device);

/**
 * @brief 
 * 
 * @param device 
 * @return uint8_t 
 */
uint8_t TLA25x8StopADCAutoScan(const TLA25x8* const device);

/**
 * @brief Set the channel for the next manual conversion
 * 
 * @param device 
 * @param channel 
 * @return uint8_t 
 */
uint8_t TLA25x8SetADCChannel(const TLA25x8* const device, const uint8_t channel);


/**
 * @brief 
 * 
 * @param device 
 * @param channel 
 * @return uint8_t 
 */
uint8_t TLA25x8ReadADC(const TLA25x8* const device, const uint8_t* channel);


#endif