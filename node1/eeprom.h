/**
 * @file eeprom.h
 * @brief Communicates with eeprom  
 * @date 2021-11-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <stdint.h>
/**
 * @brief This funtion disables interrupts temporarily and writes to the eeprom memory.
 * 
 * @param adress represents the address to which you will write @c data
 * @param data represents the data written to the choesen address.
 */
void eeprom_write(uint8_t adress, uint8_t data);
/**
 * @brief This funtion disables interrupts temporarily and reads the eeprom memory.
 * 
 * @param adress Decides where in the eeprom memory to read from.
 * @return uint8_t, the data at the specified address. 
 */
uint8_t eeprom_read(uint8_t adress);

