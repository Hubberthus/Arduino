#ifndef AVR_EEPROM_H
#define AVR_EEPROM_H

#include <EEPROM.h>

class EEPROM_HANDLER {
public:
	EEPROM_HANDLER() {
		EEPROM.begin(4096);
		_eeprom_is_ready = true;
	}

	bool _eeprom_is_ready = false;
};

EEPROM_HANDLER _EEPROM_HANDLER; // TODO: There can be multiple instances of this!

#ifdef __cplusplus
extern "C" {
#endif

bool eeprom_is_ready() {
	return _EEPROM_HANDLER._eeprom_is_ready;
}

#define eeprom_busy_wait() do { yield(); } while (!eeprom_is_ready())

inline uint8_t eeprom_read_byte (const uint8_t *__p) {
	return EEPROM.read((int)__p);
}

uint16_t eeprom_read_word (const uint16_t *__p) {
	uint16_t retVal = 0;
	return EEPROM.get((int)__p, retVal);
}

uint32_t eeprom_read_dword (const uint32_t *__p) {
	uint32_t retVal = 0;
	return EEPROM.get((int)__p, retVal);
}

float eeprom_read_float (const float *__p) {
	float retVal = 0;
	return EEPROM.get((int)__p, retVal);
}

void eeprom_read_block (void *__dst, const void *__src, size_t __n) {
	int i;

	for(i = 0; i < __n; i++){
		((uint8_t*)__dst)[i] = EEPROM.read((int)__src + i);
	}
}

void eeprom_write_byte (uint8_t *__p, uint8_t __value) {
	EEPROM.write((int)__p, __value);
	EEPROM.commit();
}

void eeprom_write_word (uint16_t *__p, uint16_t __value) {
	EEPROM.put((int)__p, __value);
	EEPROM.commit();
}

void eeprom_write_dword (uint32_t *__p, uint32_t __value) {
	EEPROM.put((int)__p, __value);
	EEPROM.commit();
}

void eeprom_write_float (float *__p, float __value) {
	EEPROM.put((int)__p, __value);
	EEPROM.commit();
}

void eeprom_write_block (const void *__src, void *__dst, size_t __n) {
	int i;

	for(i = 0; i < __n; i++){
		EEPROM.write((int)__dst + i, ((uint8_t*)__src)[i]);
	}
	EEPROM.commit();
}

#define eeprom_update_byte(__p, __value) eeprom_write_byte(__p, __value)
#define eeprom_update_word (__p, __value) eeprom_write_word(__p, __value)
#define eeprom_update_dword (__p, __value) eeprom_write_dword(__p, __value)
#define eeprom_update_float (__p, __value) eeprom_write_float(__p, __value)
#define eeprom_update_block (__src, __dst, __n) eeprom_write_block(__src, __dst, __n)


/** IAR C compatibility defines	*/

#define _EEPUT(addr, val) eeprom_write_byte ((uint8_t *)(addr), (uint8_t)(val))
#define __EEPUT(addr, val) eeprom_write_byte ((uint8_t *)(addr), (uint8_t)(val))
#define _EEGET(var, addr) (var) = eeprom_read_byte ((const uint8_t *)(addr))
#define __EEGET(var, addr) (var) = eeprom_read_byte ((const uint8_t *)(addr))

#ifdef __cplusplus
}
#endif

#endif	/* AVR_EEPROM_H */
