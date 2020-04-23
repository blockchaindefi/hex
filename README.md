# Hex help tools

## What is this

Here are two programs that are useful along with Hex

* hex_stake2day - ReStake your Hex to the same day, to take advantage of bigger pays better

* hex_percentage_growth - Calculates how much X amount increases in Y days, on a Z year(365 days) base interest rate


### What is Hex

A short summary of Hex.

Hex is a ERC20 coin on Ethereum blockchain, the project where you get more Hex Coin by locking them(stake them) for a fixed amount of time, see it as interest.
All is done through a smart contract in the Etherium network, and you do all the interaction yourself, and you do not have to trust anyone.

Read more at: [www.hex.win](https://www.hex.win/) [![Hex website](https://hex.win/img/logo.png)](https://hex.win/)


## hex_stake2day - ReStake your Hex for bigger pays better

A partly overlooked fact with Hex is that we can raise the interest rate from the normal 20% to a maximum of 30% by stake more at once, to reach the maximum 30% you need at least 150 million Hex.

This is unattainable for many, as most have bought in significantly smaller sums.
So the goal I propose is to have all new Hex Stake closed on the same day, so they can re-stake together as a big jumbo stake.

hex_stake2day  is a program to facilitate this.

Just enter the Endday you want to stack for, and you get the number of days and what date this is.

This is a simple C program. And I assume you use or at least have access to some Linux/Unix.
If you only use Windows, you are probably beyond all help anyway and do not deserve to use this program :)

Easiest build like:
```bash
gcc -o hex_stake2day hex_stake2day.c
```

And put it in your PATH, there are no dependency. Hopefully you know how this works :)


Or just run from where you built, in one line:
```bash
gcc -o hex_stake2day hex_stake2day.c && ./hex_stake2day 468
```


### A "real" example

You have since before **stake that ends the day 468 (2021-03-14)**  and now you want to stake your new Hex to the same day, to then be able to use the benefit from bigger pays better on day 468.

```bash
hex_stake2day 468
```

**This example would today (2020-03-02) result in:**
"Lock for   376  days.  The release date is: 2021-03-14"


#### But is this relevant, interest rate / "Longer Pays Better" and shares

Keep in mind that you get paid according to how many shares you have, and the inflation is in shares. Which gives a clear advantage to keep the stake for longer!

My guess is that the closer you can get to 150 million, the more benefit you have. So if you will never(within a reasonable time) have access to more than 10-50 million Hex, the advantage is probably quite low.

And as always. **Draw your own conclusions!**

**Don't trust anyone just because they can write 20 lines of C code :)**

## hex_percentage_growth

This is just a simple program to calculate how much an amount increases with something depending on the amount and percentage.

Easiest build like:
```bash
g++ -o hex_percentage_growth hex_percentage_growth.cpp
```

And put it in your PATH, there are no dependency. Hopefully you know how this works :)


Or just run from where you built, in one line:
```bash
g++ -o hex_percentage_growth hex_percentage_growth.cpp && ./hex_percentage_growth 365
```

Output:
For the whole time (365):       12,000  diff: 2,000  16.67 %  20.00 %

You can get help by starting the program with --help or -h, (or just one h)
```bash
hex_percentage_growth --help
```

```text
The help
 Count the percentage growth. The arg are:
Argument 1
 Number of days.
 Or --help/-h for for the help (or just a h)
Argument 2
 Value amount. Default value: 10000
 All, and 'ignored. And you can also expand a thousand and a million respectively with T and M. Ex 10T = 10000 and 2M = 2000000.
 But this is just a quick fix, where M and T are replaced with 0's, so 1.2T becomes 1.2000
Argument 3
 Percentage /year. Default value: 0.08
 If you set the percentage it will be used. Otherwise there is a sloppy calculation of the increase of the percent depending on the amount added.
Argument 4
 Year days used in the percent calculation. Default value: 365
 I suspect you will never want to change this, but you can do.
```

A example, stake for 730 days  for 6 million hex  at a 23 percentage interest:
```bash
hex_percentage_growth 730 6M 0.23
```

A example, stake for 350 days  for 55 thousand hex  at a 40 percentage interest:
```bash
hex_percentage_growth 350 55T 0.4
```



## FAQ

### Wouldn't this have been better as a web service.

Yes, but I'm a lowlevel programmer, and so don't do web solutions.
I create this because I had the need myself, and thought others with maybe


## Likes / dislikes, suggestions for improvements etc.

And if this helped you, send some HEX or ETH to:
0xc48AFd489CBB8Cd9F87f20152A3aE2e556734ad6

Or use my referral link
[https://go.hex.win/?r=0xc48AFd489CBB8Cd9F87f20152A3aE2e556734ad6](https://go.hex.win/?r=0xc48AFd489CBB8Cd9F87f20152A3aE2e556734ad6)

Contact me:
myhex2020@gmail.com

Cheers Rickard

