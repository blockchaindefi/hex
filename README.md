# Hex help tools

### Short summary of Hex

Hex is a project where you get more Hex Coin by locking them(stake them) for a fixed amount of time, see it as interest.
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

And put it in your PATH, there are no dependency.

Or just run from where you built, in one line:
```bash
gcc -o hex_stake2day hex_stake2day.c && ./hex_stake2day 468
```

Hopefully you know how this works :)


### A "real" example

You have since before **stake that ends the day 468 (2021-03-14)**  and now you want to stake your new Hex to the same day, to then be able to use the benefit from bigger pays better on day 468.

```bash
hex_stake2day 468
```

**This example would today (2020-03-02) result in:**
"Lock for   376  days.  The release date is: 2021-03-14"


#### Regarding interest rate / "Longer Pays Better" and shares

Keep in mind that you get paid according to how many shares you have, and the inflation is in shares. Which gives a clear advantage to keep the stake for longer!

My guess is that the closer you can get to 150 million, the more benefit you have. So if you will never(within a reasonable time) have access to more than 10-50 million Hex, the advantage is probably quite low.

And as always. **Draw your own conclusions!**

**Don't trust anyone just because they can write 20 lines of C code :)**


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

