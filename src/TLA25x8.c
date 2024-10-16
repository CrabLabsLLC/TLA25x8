/**
 * @file TLA25x8.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-10-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "TLA25x8.h"
#include "TLA25x8LowLevel.h"
#include "TLA25x8Registers.h"

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <strings.h>

TLA25x8* TLA2528_Init(const TLA2528HAL* const hal, const uint8_t address, TLA25x8* const device)
{
    if(hal == NULL || device == NULL)
        return NULL;

    device->tla2528.hal = *hal;
    device->tla2528.address = address;
    device->id = TLA25x8_ID_TLA2528;
    device->initialized = true;

    return device;
}

TLA25x8* TLA2518_Init(const TLA2518HAL* const hal, 
                      void (*spi_chip_select)(const bool is_selected),
                      TLA25x8* const device)
{

    if(hal == NULL || device == NULL)
        return NULL;
    
    device->tla2518.hal = *hal;
    device->tla2518.spi_select_chip = spi_chip_select;
    device->id = TLA25x8_ID_TLA2518;
    device->initialized = true;

    return device;
}

uint8_t TLA25x8_SetPinConfiguration(const TLA25x8* const device, const uint8_t gpio_mask)
{
    return TLA25x8_WriteRegister(device, TLA25x8_REG_PIN_CFG, gpio_mask);
}

uint8_t TLA25x8_SetGPIODirection(const TLA25x8* const device, const uint8_t output_mask)
{
    return TLA25x8_Write(device, TLA25x8_REG_GPIO_CONFIG, output_mask);
}

uint8_t TLA25x8_SetGPIOOutputType(const TLA25x8* const device, const uint8_t push_pull_mask)
{
    return TLA25x8_WriteRegister(device, TLA25x8_REG_GPIO_DRIVE_CFG, push_pull_mask);
}

uint8_t TLA25x8_SetGPIOOutputValue(const TLA25x8* const device, const uint8_t value)
{
    return TLA25x8_WriteRegister(device, TLA25x8_REG_GPO_VALUE, value);
}

uint8_t TLA25x8_GetGPIOInputValue(const TLA25x8* const device, uint8_t* const value_buffer)
{
    return TLA25x8_ReadRegister(device, TLA25x8_REG_GPI_VALUE, value_buffer);
}

uint8_t TLA25x8_SetADCScanMode(const TLA25x8* const device, const TLA25x8ScanMode mode)
{
    uint8_t reg;
    uint8_t err = TLA25x8_ReadRegister(device, TLA25x8_REG_SEQUENCE_CFG, &reg);
    if(err)
        return err;
    
    reg &= ~TLA25x8_SEQ_MODE_MASK;
    reg |= ((uint8_t)mode << TLA25x8_SEQ_MODE_SHIFT);
    
    return TLA52x8_WriteRegister(device, TLA25x8_REG_SEQUENCE_CFG, &reg);
}                                

uint8_t TLA25x8SetADCAutoScanChannels(const TLA25x8* const device, const uint8_t channel_mask)
{
    return TLA25x8_WriteRegister(device, TLA25x8_REG_AUTO_SEQ_CH_SEL, channel_mask);
}

uint8_t TLA25x8StartADCAutoScan(const TLA25x8* const device)
{
    return TLA25x8_SetRegisterBits(device, TLA25x8_REG_SEQUENCE_CFG, TLA25x8_SEQ_START_MASK);
}

uint8_t TLA25x8StopADCAutoScan(const TLA25x8* const device)
{
    return TLA25x8_ClearRegisterBits(device, TLA25x8_REG_SEQUENCE_CFG, TLA25x8_SEQ_START_MASK);
}

uint8_t TLA25x8SetADCChannel(const TLA25x8* const device, const uint8_t channel)
{
    return TLA25x8_WriteRegister(device, TLA25x8_REG_CHANNEL_SEL, (channel << TLA25x8_MANUAL_CHIPID_SHIFT) & TLA25x8_MANUAL_CHIPID_MASK);
}

uint8_t TLA25x8ReadADC(const TLA25x8* const device, const uint16_t* reading, const uint8_t num_readings)
{
    return TLA25x8_Read(device, reading, 2 * num_readings);
}

uint8_t TLA25x8_WriteRegister(const TLA25x8* const device, const TLA25x8Register reg, const uint8_t value)
{
    assert(reg < TLA25x8_REG_NUM_REGISTERS);

    const uint8_t write_buffer[] = {(uint8_t)TLA25x8_OP_REGISTER_WRITE, (uint8_t)reg, value};
    return TLA25x8_Write(device, write_buffer, sizeof(write_buffer));
}

uint8_t TLA25x8_WriteRegisters(const TLA25x8* const device, const TLA25x8Register base_reg, void* const buffer, const uint8_t length)
{
    assert(length < TLA25x8_REG_NUM_REGISTERS - base_reg);
    assert(base_reg < TLA25x8_REG_NUM_REGISTERS);

    uint8_t write_buffer[0x14] = {(uint8_t)TLA25x8_OP_REGISTERS_WRITE, (uint8_t)base_reg};
    memcpy(buffer, &write_buffer[2], length);
    return TLA25x8_Write(device, write_buffer, 2 + length);
}

uint8_t TLA25x8_ReadRegister(const TLA25x8* const device, const TLA25x8Register reg, void* const buffer)
{
    assert(reg < TLA25x8_REG_NUM_REGISTERS);

    const uint8_t write_buffer[] = {(uint8_t)TLA25x8_OP_REGISTER_READ, (uint8_t)reg};
    uint8_t err = TLA25x8_Write(device, write_buffer, sizeof(write_buffer));
    if (err)
        return err;

    err = TLA25x8_Read(device, buffer, 1);
    return err;
}

uint8_t TLA25x8_ReadRegisters(const TLA25x8* const device, const TLA25x8Register base_reg, void* const buffer, const uint8_t length)
{
    assert(base_reg < TLA25x8_REG_NUM_REGISTERS);
    assert(length < TLA25x8_REG_NUM_REGISTERS - base_reg);

    const uint8_t write_buffer[] = {(uint8_t)TLA25x8_OP_REGISTERS_READ, (uint8_t)base_reg};
    uint8_t err = TLA25x8_Write(device, write_buffer, sizeof(write_buffer));
    if (err)
        return err;

    err = TLA25x8_Read(device, buffer, length);
    return err;
}

uint8_t TLA25x8_SetRegisterBits(const TLA25x8* const device, const TLA25x8Register reg, const uint8_t bit_mask)
{
    const uint8_t buffer[3] = {(uint8_t)TLA25x8_OP_BIT_SET, (uint8_t)reg, bit_mask};
    return TLA25x8_Write(device, buffer, sizeof(buffer));
}

uint8_t TLA25x8_ClearRegisterBits(const TLA25x8* const device, const TLA25x8Register reg, const uint8_t bit_mask)
{
    const uint8_t buffer[3] = {(uint8_t)TLA25x8_OP_BIT_CLEAR, (uint8_t)reg, bit_mask};
    return TLA25x8_Write(device, buffer, sizeof(buffer));
}

// ~~~~~~~~~~~~ Bare Bones API ~~~~~~~~~~~ //


uint8_t TLA25x8_Read(const TLA25x8* const device, void* const buffer, const uint8_t length)
{
    assert(device != NULL);
    assert(buffer != NULL);
    assert(device->initialized);

    if(device->id == TLA25x8_ID_TLA2518)
    {
        const TLA2518* const dev = &device->tla2518;
        if(dev->spi_select_chip != NULL)
            dev->spi_select_chip(true);

        uint8_t ret = dev->hal.spi_read(buffer, length);

        if(dev->spi_select_chip != NULL)
            dev->spi_select_chip(false);

        return ret;

    }
    else if (device->id == TLA25x8_ID_TLA2528)
    {
        const TLA2528* const dev = &device->tla2528;
        return dev->hal.i2c_read(dev->address, buffer, length);
    }
    
    return 0xff;
}

uint8_t TLA25x8_Write(const TLA25x8* const device, const void* const buffer, uint8_t length)
{
    assert(device != NULL);
    assert(buffer != NULL);
    assert(device->initialized);

    uint8_t err = 0;

    if(device->id == TLA25x8_ID_TLA2518)
    {
        const TLA2518* const dev = &device->tla2518;
        if(dev->spi_select_chip != NULL)
            dev->spi_select_chip(true);

        err = dev->hal.spi_write(buffer, length);

        if(dev->spi_select_chip != NULL)
            dev->spi_select_chip(false);

        return err;

    }
    else if (device->id == TLA25x8_ID_TLA2528)
    {
        const TLA2528* const dev = &device->tla2528;
        return dev->hal.i2c_write(dev->address, buffer, length);
    }

    return 0xff;
}