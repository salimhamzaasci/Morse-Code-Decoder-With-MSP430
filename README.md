# MSP430 Morse Code Decoder 🔊📟

This project is a **Morse Code Decoder** developed using the **MSP430 microcontroller**.  
Incoming Morse-coded audio signals are analyzed, decoded into text, and displayed on a **16x2 LCD screen** in real time.

## 🎯 Project Objective
- Detect Morse-coded audio signals  
- Analyze dot (.) and dash (-) durations  
- Convert Morse sequences into characters and words  
- Display the decoded text on an LCD screen  

## 🧠 Technologies Used
- **Microcontroller:** MSP430G2553  
- **Programming Language:** Embedded C  
- **Audio Input:** Sound sensor / frequency detection circuit  
- **Display:** 16x2 LCD (Parallel / I2C)  
- **IDE:** Code Composer Studio  

## 🔌 Hardware Connections
### LCD – MSP430 Pin Mapping
| LCD Pin | MSP430 Pin |
|--------|------------|
| RS     | P1.5       |
| EN     | P1.4       |
| D4     | P1.0       |
| D5     | P1.1       |
| D6     | P1.2       |
| D7     | P1.3       |

## ⚙️ Working Principle
1. The audio sensor detects the Morse signal  
2. The MSP430 measures signal durations using timers  
3. Dot and dash classification is performed  
4. Characters are decoded using a Morse lookup table  
5. The decoded text is displayed on the LCD  


## 🧪 Features
- Real-time Morse code decoding  
- Word wrapping and scrolling text  
- Low power consumption  
- Modular and readable code structure  

## 🚀 Future Improvements
- UART output support  
- SD card logging  
- Adaptive decoding speed  
- OLED display integration  

## 👤 Author
**Salim Hamza Aşçı**  
Kocaeli University  

## 📜 License
This project is intended for educational and personal use.
