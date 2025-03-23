# My Robot Strategy - Search and Destroy

## Project Structure

- `RobotStrategy.ino`: My standard implementation using Arduino built-in functions
- `RobotStrategy_Baremetal.ino`: My optimized baremetal implementation

## Hardware Setup

### Components
- 4 DC motors with H-Bridge driver
- 3 HC-SR04 ultrasonic sensors (front, left, right)
- 2 IR sensors (downward-facing)
- Arduino Uno/Nano

### Pin Connections
| Component       | Pin |
|-----------------|-----|
| Front US Trigger| D2  |
| Front US Echo   | D3  |
| Left US Trigger | D4  |
| Left US Echo    | D5  |
| Right US Trigger| D6  |
| Right US Echo   | D7  |
| IR Left         | D8  |
| IR Right        | D9  |
| Motor 1         | D10 |
| Motor 2         | D11 |
| Motor 3         | D12 |
| Motor 4         | D13 |

## Features

### Core Behavior
- Autonomous opponent detection
- Search and destroy strategy
- Edge detection and avoidance

### Advanced Features
- Robust edge detection (resistant to white paper)
- Continuous scanning mode
- Baremetal optimization
