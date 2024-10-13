/**
 * @file TLA25x8Registers.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-09-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#ifndef TLA25X8_REGISTERS_H
#define TLA25X8_REGISTERS_H


/**
 * @brief The device's registers, can be read and written to
 * 
 */
typedef enum tla25x8_reg_e
{
    TLA25x8_REG_SYSTEM_STATUS   = 0x00,
    TLA25x8_REG_GENERAL_CFG     = 0x01,
    TLA25x8_REG_DATA_CFG        = 0x02,
    TLA25x8_REG_OSR_CONFIG      = 0x03,
    TLS25x8_REG_OPMODE_CONFIG   = 0x04,
    TLA25x8_REG_PIN_CFG         = 0x05,
    TLA25x8_REG_GPIO_CONFIG     = 0x07,
    TLA25x8_REG_GPIO_DRIVE_CFG  = 0x09,
    TLA25x8_REG_GPO_VALUE       = 0x0B,
    TLA25x8_REG_GPI_VALUE       = 0x0D,
    TLA25x8_REG_SEQUENCE_CFG    = 0x10,
    TLA25x8_REG_CHANNEL_SEL     = 0x11,
    TLA25x8_REG_AUTO_SEQ_CH_SEL = 0x12,
    TLA25x8_REG_NUM_REGISTERS   = 0x13
} TLA25x8Register;


#endif