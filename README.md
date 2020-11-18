# Hex help tools

## What is this

Here are two programs that are useful along with Hex

* hex_stake2day - ReStake your Hex to the same day, to take advantage of bigger pays better

* hex_percentage_growth - Calculates how much X amount increases in Y days, and other options

* hex_get_percentage_growth.sh - A script that call hex_percentage_growth, but downloads and set the total and locked options


### What is Hex

A short summary of Hex.

Hex is a ERC20 coin on Ethereum blockchain, the project where you get more Hex Coin by locking them(stake them) for a fixed amount of time, see it as interest.
All is done through a smart contract on the Ethereum network, and you do all the interaction yourself, and you do not have to trust anyone.

Read more at: [www.hex.com](https://www.hex.com/) [![Hex website](https://hex.com/img/logo.png)](https://hex.com/)


## hex_stake2day - ReStake your Hex for bigger pays better

A partly overlooked fact with Hex is that we can raise the interest rate from the normal 20% to a maximum of 30% by stake more at once, to reach the maximum 30% you need at least 150 million Hex.

This is unattainable for many, as most have bought in significantly smaller amounts.
So the goal I propose is to have all new Hex Stake closed on the same day, so they can re-stake together as a big jumbo stake.

hex_stake2day  is a program to facilitate this.

Just enter the Endday you want to stack for, and you get the number of days and what date this is.


### A "real" example

You have since before **stake that ends the day 468 (2021-03-14)**  and now you want to stake your new Hex to the same day, to then be able to use the benefit from bigger pays better on day 468.

```bash
hex_stake2day 468
```

**This example would today (2020-03-02) result in:**
"Lock for   376  days.  The release date is: 2021-03-14"


#### But is this relevant, interest rate / "Longer Pays Better" and shares

Keep in mind that you get paid according to how many shares you have, and the inflation is in shares. Which gives a clear advantage to keep the stake for longer!

My guess is that the closer you can get to 150 million, the more you'll benefit. So if you will never(within a reasonable time) have access to more than 10-50 million Hex, the advantage is probably quite low.

**Update: After improvements in the hex_percentage_growth program, it is clearer that longer pays better affects the increase significantly more than bigger pays better.**

And as always. **Draw your own conclusions!**

**Don't trust anyone just because they can write 20 lines of C code :)**

## hex_percentage_growth

This is just a simple program to calculate how much an amount increases with something depending on the amount and percentage.

Run for ex
```bash
hex_percentage_growth 365
```
Output:
Stake: 10,000  for days 365 (1.0 years)  should have increased to: 10,738  Hex

You can get help by starting the program with -h
```bash
hex_percentage_growth -h
```

```text
 Count the percentage growth. The arg are:
 arg1  Number of days to stake.
 arg2  Value amount. You can use T M B (or t m b) as thousand, million and billion. All , and ' will be removed
Settings opt:
 -p  Percentage /year  Default is: 9.225  That is based on that 40 % of all Hex are staked
 -t  The total Hex amont. Used to calculate the percentages, both this and -l must be used
 -l  The lock  Hex amont. Used to calculate the percentages, both this and -t must be used
 -d  Year days used in the percent calculation. Default value: 365  (Probably nothing you want to change)
 -n  Do not calculate with the Hex bonus
 -v  Verbose = print more, can use twice for even more info
 -h  This help

And of course these are just guesses!
Even with a perfect calculation, there is much else that affects the "interest rate" in Hex
```

A example, stake 200 thousand hex for 1000 days, at the defult 6.15 percentage interest:
```bash
hex_percentage_growth 1000 200t
```

Stake 6 million hex for 730 days, at a 23 percentage interest:
```bash
hex_percentage_growth -p 23 730 6M
```

Stake 55 thousand hex for 350 days, at a 40 percentage interest:
```bash
hex_percentage_growth -p 40 350 55T
```


## hex_get_percentage_growth.sh

This is a bash script that calls hex_percentage_growth to use the current staking percentage.
It downloads and sets the total and locked options on hex_percentage_growth.
Total and locked amount is saved for reuse, after 2 hours the latest data is downloaded again.

Same example as above, but now with current percentage automatically calculated.

A example, stake 6 million hex for 730 days:
```bash
hex_get_percentage_growth.sh 730 6M
```

Stake 55 thousand hex for 350 days, with maximum verbose formation:
```bash
hex_get_percentage_growth.sh -v -v 350 55T
```

Of course this is based on the staking level right now, this will of course change.



## Basic setup

This are simple C respective C++ programs. And I assume you use or at least have access to some Linux/Unix.

This should work on other unix machines, and a Mac as well.

But if you only use Windows, you are probably beyond all help :)

Install gcc and git, git clone this, build and setup(add hex/bin to your PATH):
```bash
sudo apt-get install build-essential git
git clone https://github.com/blockchaindefi/hex.git
cd hex
make
PATH=$PATH:$(pwd)/bin
```

There are no other dependency. Hopefully you know how this works :)


## FAQ

### Wouldn't this have been better as a web service.

Yes, but I'm a lowlevel programmer, and so don't do web solutions.
I created this because I had the need myself, and thought others might appreciate it.


## Likes / dislikes, suggestions for improvements etc.

And if this helped you, send some HEX or ETH to:
0xc48AFd489CBB8Cd9F87f20152A3aE2e556734ad6

Contact me:
myhex2020@gmail.com

Cheers Rickard

