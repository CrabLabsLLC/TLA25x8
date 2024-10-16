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

/// System Status Register (SYSTEM_STATUS)

#define TLA25x8_SEQ_STATUS_SHIFT    (0x6)
#define TLA25x8_SEQ_STATUS_MASK     (0x1 << TLA25x8_SEQ_STATUS_SHIFT)

#define TLA25x8_OSR_DONE_SHIFT      (0x3)
#define TLA25x8_OSR_DONE_MASK       (0x1 << TLA25x8_OSR_DONE_SHIFT)

#define TLA25x8_CRCERR_FUSE_SHIFT   (0x2)
#define TLA25x8_CRCERR_FUSE_MASK    (0x1 << TLA25x8_CRCERR_FUSE_SHIFT)

#define TLA25x8_BOR_SHIFT           (0x0)
#define TLA25x8_BOR_MASK            (0x1 << TLA25x8_BOR_SHIFT)

/// General Config Register (GENERAL_CFG)

#define TLA25x8_CH_RST_SHIFT        (0x2)
#define TLA25x8_CH_RST_MASK         (0x1 << TLA25x8_CH_RST_SHIFT)

#define TLA25x8_CAL_SHIFT           (0x1)
#define TLA25x8_CAL_MASK            (0x1 << TLA25x8_CAL_SHIFT)

#define TLA25x8_RST_SHIFT           (0x0)
#define TLA25x8_RST_MASK            (0x1 << TLA25x8_RST_SHIFT)

/// Data Configuration Register (DATA_CFG)

#define TLA25x8_FIX_PAT_SHIFT       (0x7)
#define TLA25x8_FIX_PAT_MASK        (0x1 << TLA25x8_FIX_PAT_SHIFT)

#define TLA25x8_APPEND_STATUS_SHIFT (0x4)
#define TLA25x8_APPEND_STATUS_MASK  (0x3 << TLA25x8_CAL_SHIFT)

#define TLA25x8_CPOL_CPHA_SHIFT     (0x0)
#define TLA25x8_CPOL_CPHA_MASK      (0x3 << TLA25x8_COL_CPHA_SHIFT)

/// Oversampling Configuration Register (OSR_CFG)

#define TLA25x8_OSR_SHIFT           (0x0)
#define TLA25x8_OSR_MASK            (0x7 << TLA25x8_OSR_SHIFT)

/// Operating Mode Register (OPMODE_CFG)

#define TLA25x8_OSC_SEL_SHIFT       (0x4)
#define TLA25x8_OSC_SEL_MASK        (0x1 << TLA25x8_OSC_SEL_SHIFT)

#define TLA25x8_CLK_DIV_SHIFT       (0x0)
#define TLA25x8_CLK_DIV_MASK        (0xf << TLA25x8_CLK_DIV_SHIFT)

/// Sequence Configuration Register

#define TLA25x8_SEQ_START_SHIFT     (0x4)
#define TLA25x8_SEQ_START_MASK      (0x1 << TLA25x8_SEQ_START_SHIFT)

#define TLA25x8_SEQ_MODE_SHIFT      (0x0)
#define TLA25x8_SEQ_MODE_MASK       (0x3 << TLA25x8_SEQ_MODE_SHIFT)

/// Channel Select Register

#define TLA25x8_MANUAL_CHIPID_SHIFT (0x0)
#define TLA25x8_MANUAL_CHIPID_MASK  (0x1 << TLA25x8_MANUAL_CHIPID_SHIFT)

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