/*
 * More information about Hex
 * https://hex.win
 *
 * This code is strongly inspired by the function _stakeStartBonusHearts() in the Hex solidity contract
 * See:
 * https://etherscan.io/address/0x2b591e99afe9f32eaa6214f7b7629768c40eeb39#code
 *
 * Therefore this is NOT GPL licens code!
 */

#ifndef _STAKE_BONUS_H
#define _STAKE_BONUS_H

const double  HEARTS_PER_HEX = 1e8;

/* Stake shares Longer Pays Better bonus constants used by _stakeStartBonusHearts() */
const double LPB_BONUS_PERCENT = 20;
const double LPB_BONUS_MAX_PERCENT = 200;
const double LPB = 364 * 100 / LPB_BONUS_PERCENT;
const double LPB_MAX_DAYS = LPB * LPB_BONUS_MAX_PERCENT / 100;

/* Stake shares Bigger Pays Better bonus constants used by _stakeStartBonusHearts() */
const double  BPB_BONUS_PERCENT = 10;
const double  BPB_MAX_HEX = 150 * 1e6;
const double  BPB_MAX_HEARTS = BPB_MAX_HEX * HEARTS_PER_HEX;
const double  BPB = BPB_MAX_HEARTS * 100 / BPB_BONUS_PERCENT;

/**
* @dev Calculate bonus Hearts for a new stake, if any
* @param newStakedHex Number of Hex to stake
* @param newStakedDays Number of days to stake
*/
static double stakeStartBonusHex(double newStakedHex, double newStakedDays)
{
	double cappedExtraDays = 0;
	double newStakedHearts = newStakedHex * HEARTS_PER_HEX;

	/* Must be more than 1 day for Longer-Pays-Better */
	if (newStakedDays > 1) {
		cappedExtraDays = newStakedDays <= LPB_MAX_DAYS ? newStakedDays - 1 : LPB_MAX_DAYS;
	}

	double cappedStakedHearts = newStakedHearts <= BPB_MAX_HEARTS ? newStakedHearts : BPB_MAX_HEARTS;

	double bonusHearts = cappedExtraDays * BPB + cappedStakedHearts * LPB;
	bonusHearts = newStakedHearts * bonusHearts / (LPB * BPB);

	return bonusHearts / HEARTS_PER_HEX;
}

#endif // _STAKE_BONUS_H
