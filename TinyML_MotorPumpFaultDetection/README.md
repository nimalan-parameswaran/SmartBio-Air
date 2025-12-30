# TinyML Motor Pump Fault Detection  
**Normal vs Fault Classification using Edge Impulse**

https://github.com/user-attachments/assets/3eb5bc1c-ce33-423c-a051-8dfc26945e4b


---

## 1. Project Overview

This project implements a TinyML-based classification system to detect **Normal** and **Fault** operating conditions of a **6V DC Motor Air Pump**.  
The model is trained and deployed using **Edge Impulse**, enabling real-time inference on microcontroller-class devices without internet connectivity.

The solution is designed for embedded fault monitoring and predictive maintenance scenarios.

---

## 2. Dataset Description

The dataset contains sensor readings collected from the air pump under two operating conditions.

### Dataset Size

| Class  | Samples |
|------|---------|
| Normal | 4000 |
| Fault  | 4000 |
| **Total** | **8000** |

### Data Split

- **Training + Validation:** 80%
- **Testing:** 20%

Training data distribution:
- **Training:** 70%
- **Validation:** 10%

The dataset is perfectly balanced, supporting unbiased classification.

---

## 3. Data Upload to Edge Impulse

### Procedure

1. A new Edge Impulse project was created.
2. Sensor data files were uploaded via the **Data Acquisition** section.
3. Labels (`normal`, `fault`) were assigned during upload.
4. Data integrity and class balance were verified.
5. Automatic train–test separation was applied.
   
<p align="left">
  <img src="https://github.com/nimalan-parameswaran/SmartBio-Air/blob/main/TinyML_MotorPumpFaultDetection/src/1.png" width="600">
</p>

## 4. Impulse Design
### Create impulse 

<p align="left">
  <img src="https://github.com/nimalan-parameswaran/SmartBio-Air/blob/main/TinyML_MotorPumpFaultDetection/src/2.png" width="600">
</p>

### Raw data

- **Parameters**
<p align="left">
  <img src="https://github.com/nimalan-parameswaran/SmartBio-Air/blob/main/TinyML_MotorPumpFaultDetection/src/3.png" width="600">
</p>

- **Generate features**
<p align="left">
  <img src="https://github.com/nimalan-parameswaran/SmartBio-Air/blob/main/TinyML_MotorPumpFaultDetection/src/4.png" width="600">
</p>

### Classifiers
<p align="left">
  <img src="https://github.com/nimalan-parameswaran/SmartBio-Air/blob/main/TinyML_MotorPumpFaultDetection/src/Screenshot 2025-12-30 132800.png" width="600">
</p>

---

## 5. Model Training Results

### Training Metrics

- **Training Accuracy:** 98.1%
- **Training Loss:** 0.06

<p align="left">
  <img src="https://github.com/nimalan-parameswaran/SmartBio-Air/blob/main/TinyML_MotorPumpFaultDetection/src/5.png" width="600">
</p>

### Class-wise Performance

| Class | Precision | Recall | F1 Score |
|-----|----------|--------|----------|
| Normal | 0.97 | 0.98 | 0.97 |
| Fault | 0.98 | 0.98 | 0.98 |

<p align="left">
  <img src="https://github.com/nimalan-parameswaran/SmartBio-Air/blob/main/TinyML_MotorPumpFaultDetection/src/6.png" width="600">
</p>


### Aggregate Metrics

- **Area under ROC Curve:** 0.98  
- **Weighted Precision:** 0.98  
- **Weighted Recall:** 0.98  
- **Weighted F1 Score:** 0.98  

### Confusion Matrix (%)

| Actual \ Predicted | Normal | Fault | Uncertain |
|------------------|--------|-------|-----------|
| Normal | 95.9% | 2.5% | 1.6% |
| Fault | 1.0% | 98.5% | 0.5% |

---

## 6. Model Testing Results

- **Test Accuracy:** 97.23%

<p align="left">
  <img src="https://github.com/nimalan-parameswaran/SmartBio-Air/blob/main/TinyML_MotorPumpFaultDetection/src/7.png" width="600">
</p>

### Test Metrics

- **Area under ROC Curve:** 0.98  
- **Weighted Precision:** 0.98  
- **Weighted Recall:** 0.98  
- **Weighted F1 Score:** 0.98  

<p align="left">
  <img src="https://github.com/nimalan-parameswaran/SmartBio-Air/blob/main/TinyML_MotorPumpFaultDetection/src/8.png" width="600">
</p>

The testing results confirm consistent performance on unseen data.

---

## 7. Deployment Configuration

### Selected Deployment

- **Arduino Library**
- Runs fully offline
- Low latency and low power consumption

<p align="left">
  <img src="https://github.com/nimalan-parameswaran/SmartBio-Air/blob/main/TinyML_MotorPumpFaultDetection/src/Screenshot 2025-12-30 134339.png" width="600">
</p>
---

## 8. TensorFlow Lite Model Export

<p align="center">
  <img src="https://github.com/nimalan-parameswaran/SmartBio-Air/blob/main/TinyML_MotorPumpFaultDetection/src/Screenshot 2025-12-30 134339.png" width="600">
</p>

### Quantized Model (INT8)

| Parameter | Value |
|--------|------|
| Inference Time | 1 ms |
| RAM | 3.0 KB |
| Flash | 34.4 KB |
| Accuracy | 97.60% |

### Float Model (FP32)

| Parameter | Value |
|--------|------|
| Inference Time | 1 ms |
| RAM | 3.1 KB |
| Flash | 35.0 KB |
| Accuracy | 97.23% |

**Target Device Estimate:** Cortex-M4F @ 80 MHz

---

## 9. Arduino Deployment

<p align="left">
  <img src="https://github.com/nimalan-parameswaran/SmartBio-Air/blob/main/TinyML_MotorPumpFaultDetection/src/9.png" width="600">
</p>

### Steps

1. Downloaded the Arduino library from Edge Impulse.
2. Imported the library into Arduino IDE.
3. Loaded the inference example.
4. Connected the motor and sensor setup.
5. Observed classification output via Serial Monitor.

---

## 10. Directory Structure

TinyML_MotorPumpFaultDetection/
├── src/
│ ├── 1.png
│ ├── 2.png
│ ├── ...
├── arduino_library/
├── model_export/
└── README.md
