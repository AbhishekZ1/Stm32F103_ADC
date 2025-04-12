# STM32 ADC Driver (STM32F103C8T6)

This project provides a basic ADC driver for STM32 microcontrollers, particularly STM32F103C8T6 ("Blue Pill") using ADC1 and ADC2. It includes functions to initialize ADC channels, read analog data, use ADC interrupts, and configure the analog watchdog.

## 🧾 File Descriptions

- `adc.h` — Header file declaring the ADC-related functions.
- `adc.c` — Contains the implementation of ADC initialization, reading, interrupts, and watchdog configuration.
- `main.c` — Your main application file that uses the ADC driver.

---

## 🔄 ADC Flow Overview (`adc.c`)

### 1. `char ADC_INIT(short port, short pin, short adc)`
**Purpose:**  
Initializes a specific ADC channel connected to a GPIO pin.

**Flow:**
1. Convert `port` and `pin` into ADC channel number.
2. Configure the GPIO pin as analog input using `Gpio_init`.
3. Enable the ADC (either ADC1 or ADC2).
4. Configure basic ADC registers:
   - `CR2` for enabling ADC.
   - `SQR3` to set channel.
   - Start ADC conversion.

---

### 2. `char ADC_check(short adc)`
**Purpose:**  
Checks if ADC conversion is complete.

**Flow:**
- Read the ADC status register `SR` to see if the EOC (End Of Conversion) flag is set.
- Returns `1` if data is ready, `0` otherwise.

---

### 3. `int Read_ADC(short port, short pin, short adc)`
**Purpose:**  
Reads analog data from the specified channel.

**Flow:**
- Reads the ADC data register `DR`.
- Converts raw 12-bit value to a millivolt approximation (0–1000 mV scale).

---

### 4. `void Enable_ADC_interupt(short *ADCST, short adc)`
**Purpose:**  
Enables ADC end-of-conversion interrupt.

**Flow:**
- Sets the EOC interrupt enable bit in `CR1`.
- Enables `ADC1_2_IRQn` interrupt in the NVIC.
- Sets `*ADCST = 1` to indicate interrupt is enabled.

---

### 5. `void Enable_ADC_Watchdog(short adc, long LTR, long HTR, short *WDT)`
**Purpose:**  
Configures analog watchdog to monitor ADC values within a range.

**Flow:**
- Sets high (`HTR`) and low (`LTR`) threshold registers.
- Enables analog watchdog interrupt in `CR1`.
- Enables NVIC interrupt.
- Sets `*WDT = 1` to indicate watchdog is active.

---

### 6. `void adc_multi_ch_init(char adc, char channels, char *adc_channels)`
**Purpose:**  
Initializes multiple ADC channels.

**Flow:**
1. Loop over each channel and configure corresponding GPIO pins.
2. Enable ADC1/ADC2, and set `CR2` and `SQR3` to prepare for conversion.
3. Set to continuous conversion mode.

---

### 7. `void adc_multi_ch_rx(char adc, char channels, char *adc_channels, int *analog_rx)`
**Purpose:**  
Reads from multiple ADC channels sequentially.

**Flow:**
1. Wait for conversion to complete (`ADC_check`).
2. Read from `DR`, convert to millivolts, and store in `analog_rx[i]`.
3. Switch to the next channel using `SQR3`.
4. Repeat until all channels are read.

---

## 📌 Port and Channel Mapping

```c
PA0 - ADC12_IN0      PA1 - ADC12_IN1
PA2 - ADC12_IN2      PA3 - ADC12_IN3
PA4 - ADC12_IN4      PA5 - ADC12_IN5
PA6 - ADC12_IN6      PA7 - ADC12_IN7

PB0 - ADC12_IN8      PB1 - ADC12_IN9

PC0 - ADC12_IN10     PC1 - ADC12_IN11
PC2 - ADC12_IN12     PC3 - ADC12_IN13
PC4 - ADC12_IN14     PC5 - ADC12_IN15

