/*
 * More information about Hex
 * https://hex.com
 *
 * This code is strongly inspired by the function _stakeStartBonusHearts() in the Hex solidity contract
 * See:
 * https://etherscan.io/address/0x2b591e99afe9f32eaa6214f7b7629768c40eeb39#code
 *
 * Therefore this is NOT GPL licens code!
 */

#ifndef _STAKE_BONUS_H
#define _STAKE_BONUS_H

const my_double_t  HEARTS_PER_HEX = 1e8;

/* Stake shares Longer Pays Better bonus constants used by _stakeStartBonusHearts() */
const my_double_t LPB_BONUS_PERCENT = 20;
const my_double_t LPB_BONUS_MAX_PERCENT = 200;
const my_double_t LPB = 364 * 100 / LPB_BONUS_PERCENT;
const my_double_t LPB_MAX_DAYS = LPB * LPB_BONUS_MAX_PERCENT / 100;

/* Stake shares Bigger Pays Better bonus constants used by _stakeStartBonusHearts() */
const my_double_t  BPB_BONUS_PERCENT = 10;
const my_double_t  BPB_MAX_HEX = 150 * 1e6;
const my_double_t  BPB_MAX_HEARTS = BPB_MAX_HEX * HEARTS_PER_HEX;
const my_double_t  BPB = BPB_MAX_HEARTS * 100 / BPB_BONUS_PERCENT;

/**
* @dev Calculate bonus Hearts for a new stake, if any
* @param newStakedHex Number of Hex to stake
* @param newStakedDays Number of days to stake
*/
static my_double_t stakeStartBonusHex(my_double_t newStakedHex, my_double_t newStakedDays)
{
	my_double_t cappedExtraDays = 0;
	my_double_t newStakedHearts = newStakedHex * HEARTS_PER_HEX;

	/* Must be more than 1 day for Longer-Pays-Better */
	if (newStakedDays > 1) {
		cappedExtraDays = newStakedDays <= LPB_MAX_DAYS ? newStakedDays - 1 : LPB_MAX_DAYS;
	}

	my_double_t cappedStakedHearts = newStakedHearts <= BPB_MAX_HEARTS ? newStakedHearts : BPB_MAX_HEARTS;

	my_double_t bonusHearts = cappedExtraDays * BPB + cappedStakedHearts * LPB;
	bonusHearts = newStakedHearts * bonusHearts / (LPB * BPB);

	return bonusHearts / HEARTS_PER_HEX;
}

#endif // _STAKE_BONUS_H
