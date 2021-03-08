# CPP-Project

It's a simple console simulation of cars racing on a circuit. You will get to manage 2 cars and tweak them during the race so that they will have less chance to breakdown. The information will be presented like this:

```
---------------------
            46
         47    45
         48    44 43 42 41 40 39 38
         49                         37
       P  0          32 33 34 35 36
          1       31
          2          30 29 28 27
    5  4  3                   26
 6                            25
    7  8  9 10 11 12 13 14    24
                        15    23
                        16    22
                        17    21
                        18    20
                           19
ILK: 1:6; BMR: 1:5; DUH: 1:5; WLH: 1:5; FMK: 1:5; EAC: 1:5; NQD: 1:5; KGP: 1:5; ANM: 1:5; WAS: 1:7; TBD: 1:5; MYO: 1:5;
QIH: 1:5; ULX: 1:5; XMB: 1:5; BMY: 1:5; ROM: 1:5; MBK: 1:5; VOT: 1:5; EOH: 1:5;
LEC:
lap: 1, position: 5
fuel: 17.45L, speed: 85
engineWear: 0.01%, engineTemp: 246.006C, turbo pressure: 2.96904
brakeWear: 0.23%, brakeTemp: 417.484C
Tyre Wear: 0.132%, Tyre pressure: 21.4966psi
ABS status: 0, DRS status: 0
MEK:
lap: 1, position: 5
fuel: 7.45001L, speed: 85
engineWear: 0.005%, engineTemp: 242.415C, turbo pressure: 2.9257
brakeWear: 0.22%, brakeTemp: 390.723C
Tyre Wear: 0.127%, Tyre pressure: 21.4966psi
ABS status: 0, DRS status: 0
---------------------
```
The circuit will be printed as number (50) which represents sections of the circuit (positions). Under the circuit, we can see the different competitors with 3 letters that represent their names. The first number is the lap and the second number is the section of the circuit where they are. Then we can see 2 cars with a lot of information. They are your cars and you'll need to watch the different telemetries so that at each end of lap you'll be able to change some parts of your car so that it can race in the best conditions.
