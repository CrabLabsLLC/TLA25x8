/**
 * @file TLA25x8Types.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-09-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#ifndef TLS25X8_TYPES_H
#define TLA25x8_TYPES_H

#include <stdint.h>

// ~~~~~~~~~~~~~~~~ Enums ~~~~~~~~~~~~~~~~ //

typedef enum tla25x8_id_t
{
    TLA25x8_ID_TLA2518,
    TLA25x8_ID_TLA2528,
} TLA25x8ID;

/**
 * @brief The devices operation codes, must be sent before any operations
 * 
 */
typedef enum tla25x8_opcode_e
{
    TLA25x8_OP_REGISTER_READ    = 0x10,
    TLA25x8_OP_REGISTER_WRITE   = 0x08,
    TLA25x8_OP_BIT_SET          = 0x18,
    TLA25x8_OP_BIT_CLEAR        = 0x20,
    TLA25x8_OP_REGISTERS_READ   = 0x30,
    TLA25x8_OP_REGISTERS_WRITE  = 0x28 
} TLA25x8OpCode;

/**
 * @brief 
 * 
 */
typedef enum tls25x8_scan_mode_t
{
    TLA25x8_SCAN_MODE_MANUAL        = 0x0,
    TLA25x8_SCAN_MODE_AUTO          = 0x1,
    TLA25x8_SCAN_MODE_ON_THE_FLY    = 0x2
} TLA25x8ScanMode;

/**
 * @brief 
 * 
 */
typedef enum tla25x8_oversampling_t
{
    TLA25x8_OVERSAMPLING_NONE   = 0x0,
    TLA25x8_OVERSAMPLING_2X     = 0x1,
    TLA25x8_OVERSAMPLING_4X     = 0x2,
    TLA25x8_OVERSAMPLING_8X     = 0x3,
    TLA25x8_OVERSAMPLING_16X    = 0x4,
    TLA25x8_OVERSAMPLING_32X    = 0x5,
    TLA25x8_OVERSAMPLING_64X    = 0x6,    
    TLA25x8_OVERSAMPLING_128X   = 0x7
} TLA25x8Oversampling;

/**
 * @brief 
 * 
 */
typedef enum tla25x8_clock_speed_t
{
    TLA25x8_CLOCK_SPEED_1MHZ,
    TLA25x8_CLOCK_SPEED_31250Hz
} TLA25x8ClockSpeed;

/**
 * @brief 
 * 
 */
typedef enum tla25x8_clock_div_t
{
    TLA25x8_CLOCK_DIV_1     = 0x0,
    TLA25x8_CLOCK_DIV_3_2   = 0x1,
    TLA25x8_CLOCK_DIV_2     = 0x2,
    TLA25x8_CLOCK_DIV_3     = 0x3,
    TLA25x8_CLOCK_DIV_4     = 0x4,
    TLA25x8_CLOCK_DIV_6     = 0x5,
    TLA25x8_CLOCK_DIV_8     = 0x6,
    TLA25x8_CLOCK_DIV_12    = 0x7,
    TLA25x8_CLOCK_DIV_16    = 0x8,
    TLA25x8_CLOCK_DIV_24    = 0x9,
    TLA25x8_CLOCK_DIV_32    = 0xA,
    TLA25x8_CLOCK_DIV_48    = 0xB,
    TLA25x8_CLOCK_DIV_64    = 0xC,
    TLA25x8_CLOCK_DIV_128   = 0xD,
    TLA25x8_CLOCK_DIV_192   = 0xE

} TLA25x8ClockDiv;

// ~~~~~~~~~~~~~~~ Structs ~~~~~~~~~~~~~~~ //

/**
 * @brief Hardware Abstraction for the TLA2528
 * 
 */
typedef struct tla2528_hal_t
{
    /**
     * @brief Generic I2C read function
     * 
     * @param[in] dev_address: Address of the device to read from 
     * @param[out] buffer: Buffer to read into 
     * @param[in] length: Amount of bytes to read in to the buffer 
     * @return uint8_t: Generic user defined error code, 0 for no error
     */
    uint8_t (*i2c_read)(const uint8_t dev_address, void* const buffer, const uint8_t length); 

    /**
     * @brief Generic I2C write register function
     * 
     * @param[in] dev_address 
     * @param[in] buffer 
     * @param[in] length 
     * @return uint8_t: User defined error codes 
     */
    uint8_t (*i2c_write)(const uint8_t dev_address, const void* const buffer, const uint8_t length);

} TLA2528HAL;

/**
 * @brief The Hardware abstraction interface for the TLA2518
 * 
 */
typedef struct tla2518_hal_t
{
    /**
     * @brief Reads from the SPI Bus that the device is connected to
     * 
     * @param[out] buffer: Buffer to read into 
     * @param[in] length: How many bytes to read 
     * @return uint8_t: User defined error codes, 0 for no error 
     */
    uint8_t (*spi_read)(void* const buffer, const uint8_t length);

    /**
     * @brief Writes to the SPI bus that the device is connected to
     * 
     * @param[in] buffer: Buffer to write to the device 
     * @param[in] length: Number of bytes to write
     * @return uint8_t: User defined error codes, 0 for no error
     */
    uint8_t (*spi_write)(const void* const buffer, const uint8_t length);

} TLA2518HAL;

/**
 * @brief Represents everything needed for a TLA2518 Device
 * @note Messy but ensures portability and efficiency
 * 
 */
typedef struct tla2518_t
{
    TLA2518HAL hal; ///< The necessary hardware abstraction interface for communicating with the device
    /**
     * @brief A function to select the device if not already done in the HAL functions
     * @note Can be NULL if the selection is done in the HAL functions
     * 
     * @param[in] is_selected: If the device is selected for communication (if CS line is low) 
     */
    void (*spi_select_chip)(const bool is_selected);
} TLA2518;

/**
 * @brief Represents everything for a TLA2528 device
 * 
 */
typedef struct tla2528_t
{
    TLA2528HAL hal;     ///< The hardware abstraction interface for the device
    uint8_t address;    ///< I2C address of the device so communication can be facilitated
} TLA2528;

typedef struct tls25x8_t
{
    TLA25x8ID id; ///< which device it is
    union ///< can be either of the devices so store both in the same location
    {
        TLA2528 tla2528; //
        TLA2518 tla2518;
    };
    bool initialized;
} TLA25x8;

typedef struct tla25x8_config_t
{
    TLA25x8Oversampling oversampling;

    TLA25x8ClockSpeed base_clock_speed;
    TLA25x8ClockDiv clock_divider;
    
    bool calibrate;
    bool append_channel_to_data;

    uint8_t gpio_enable_mask;
    uint8_t gpio_output_mask;
    uint8_t gpio_output_open_drain_mask;

} TLA25x8Config;

#endif