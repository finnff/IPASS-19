#ifndef TRUERANDOM_HPP
#define TRUERANDOM_HPP

// #include "sam3.h"
#include "hwlib.hpp" //No need to include sam3.h if using hwlib.

/** trueRandom(); checks if trng is already enabled, if not it will enable on
   the TRNG peripheral, disabling the interupt register and enabling the TRNG
   chip with the "RNG" key
    @return Return a random 32 Bit integer.
    */

uint_fast32_t trueRandom() {
  static bool enable = false;
  if (!enable) {
    PMC->PMC_PCER1 =
        (0x01 << (41 - 32));     /**< enables clock on peripheral 41(TRNG) */
    TRNG->TRNG_IDR = 0xFFFFFFFF; /**< disable interupt register */
    TRNG->TRNG_CR =
        TRNG_CR_KEY(0x524e47) |
        TRNG_CR_ENABLE; /**< enables TRNG key with "RNG" key (in hex)*/
    enable = true;
  }

  while (
      !(TRNG->TRNG_ISR &
        TRNG_ISR_DATRDY)) /**< wait till data is ready after 84 clock cycles */
    ;
  return TRNG->TRNG_ODATA; /**< returns random 32bit unsigned int */
};

/** Returns a random value between a given range, if no parameters are given,
   the range is 0-100.
    @param lo Minimum/Low value of given range
    @param hi Maximum/High value of given range
    @return random value bewtween Minimum and Maximum
    */

u_int32_t RandomRange(const uint_fast32_t &lo = 0,
                      const uint_fast32_t &hi = 100) {
  uint_fast32_t rand = trueRandom();
  rand = rand % (hi - lo + 1);
  return rand + lo;
}

#endif // TRUERANDOM_HPP
