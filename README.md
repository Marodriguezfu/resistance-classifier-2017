# Resistance Classifier (2017)

This repository contains the complete work of the **Resistance Classifier Project**, developed in 2017 as part of an engineering workshop at the **Universidad Nacional de Colombia**.  
The goal was to design and implement a device capable of **measuring and classifying resistors automatically** using **Arduino-based circuits**, **stepper motors**, and **3D-printed components**.

---

## 📖 Project Overview

Classifying resistors manually can be tedious due to their color bands and prone to human error (especially for people with visual impairments such as color blindness).  
This project proposed a compact device that could **feed, measure, and sort resistors** into dedicated containers:

1. **Feeding system** – a roller mechanism controlled by a motor that allows one resistor at a time to enter the measurement unit.  
2. **Measuring system** – based on an **Arduino ohmmeter** using voltage dividers and Ohm’s law.  
3. **Classification system** – a rotating rail controlled by a stepper motor, which directs the resistor into the correct bin according to its value.

---

## 🛠️ Features

- Arduino-based ohmmeter to calculate resistor values.  
- Automatic range detection (100 Ω – 820 kΩ).  
- Stepper motor precision control for classification.  
- Mechanical design of roller, rail, and box using **SolidWorks** and intended for 3D printing.  
- LCD display for showing measured resistance and assigned bin.  

---

## 📂 Repository Structure
```
resistance-classifier-2017/
│
├── src/ # Arduino source code
├── docs/ # Reports, guides, and project proposal (PDFs)
├── cad/ # CAD designs (SolidWorks)
├── figures/ # Images, diagrams, and results
├── README.md # Project documentation
└── .gitignore
```

## 📑 Documentation

The full documentation is provided in the `docs/` folder:
- **Project Proposal** – initial justification, design, and planning.  
- **Guides 1–3** – experimental steps with Arduino ohmmeter, CAD design, and stepper.  
- **Reports 1–3** – results of each stage (measurement ranges, CAD design, motor control).  
- **Final Report** – complete description of the device, final assembly, and conclusions.
---

## ⚙️ Hardware & Software Requirements

- **Hardware**
  - Arduino UNO (or compatible board)
  - Breadboard, jumpers, and resistors
  - Stepper motor (28BYJ-48) + ULN2003 driver
  - LCD display
  - 3D-printed mechanical parts (roller, box, rail)

- **Software**
  - Arduino IDE
  - SolidWorks (for CAD design)

---

## 🚀 How to Run

1. Connect the circuit as described in the `docs/Informe Final.pdf`.  
2. Open the Arduino IDE and upload the source code from `src/`.  
3. Place resistors into the roller mechanism.  
4. The system will measure and classify each resistor, showing results on the LCD.  

---

## 📊 Results

- Achieved automatic classification in ranges from **100 Ω up to 820 kΩ** with predefined tolerance.  
- Demonstrated integration of electronics, programming, and mechanical design.  
- Highlighted the importance of cost optimization in 3D printing (not all parts were fabricated).  

---

## 👥 Authors

- Julián Camilo Casallas Villamil  
- José Fernando Murcia Rincón  
- Daniel Camilo Peña Pabón  
- **Miguel Ángel Rodríguez Fuentes**  

Universidad Nacional de Colombia, 2017.

