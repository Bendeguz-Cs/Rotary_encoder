# Rotary_encoder

Reads the position of a rotary encoder and outputs it with a simple function.

## Description

Simple Arduino library used to read the position of an incremental rotary encoder.

> [!NOTE]
> Version [2.0.0](https://github.com/Bendeguz-Cs/Rotary_encoder/releases/tag/v2.0.0) and newer use interrupts, if an **AVR** chip is selected then the [PinChangeInterrupt](https://github.com/NicoHood/PinChangeInterrupt) library by @NicoHood will be used, for all other chips **Hardware interrupts** will be used 

## Hardware

Recommended hardware debouncing using a 10 KΩ resistor between the MCU pin and the CLK pin of the encoder(the pin defined first in the initialization) and a 100nF(0.1μF) capacitor between the MCU pin and GND. See below.

> [!NOTE]
> The KY-040 has the resistors built in, you don't need to add external ones

<img width="500" height="480" alt="image" src="https://github.com/user-attachments/assets/a9f15062-2125-424d-ad24-a0ce12119c01" />

---

I've designed my own board with 20 NeoPixel LEDs, the pullup resistors and the debounce capacitors built in, you can order it or download the design files from [PCBWay](https://www.pcbway.com/project/shareproject/Rotary_encoder_w_LED_ring_6f54efc7.html).

<img width="500" height="375" alt="IMG_0918" src="https://github.com/user-attachments/assets/013f8fd3-0ebf-4416-8a27-0f070234232f" />

## Sponsorship

Special thanks to PCBWay for sponsoring the production of the prototype boards used in this project.
The boards would have cost 6.88$ a piece including the 20 WS2812 SMD LEDs(NeoPixels), assembly and shipping costs, which was approx. 20$ for all 10 boards, coming to a total of approx 4.8$ per board. I am very happy with the quality of the boards, they turned out great and have made it a lot easier to make most experiments, as they provide the already very versatile rotary encoder and a useful display around it, without requiring any external components, everything is on the board so you can make prototyping a lot faster.
Make sure to check out their services at [pcbway.com](https://www.pcbway.com/).

<img width="169" height="51" alt="image" src="https://github.com/user-attachments/assets/cadc9b50-77c6-4b7f-9263-1af4391e1b8d" />

---

<details><summary>Compatibility</summary>
<p>

This library is compatible with **AVR** and all other **MCU**s that have **Hardware interrupts**.
The library was tested on:

- Arduino NANO

- Arduino UNO R3

- Arduino UNO R4 MINIMA

- Arduino UNO R4 WiFi

- Seeeduino XIAO SAMD21

- Seeeduino XIAO ESP32-S3

</p>
</details>


## License
MIT License
