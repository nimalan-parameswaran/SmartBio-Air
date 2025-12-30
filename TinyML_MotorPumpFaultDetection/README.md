# TinyML-Based Fault Detection for 6V DC Motor Air Pump  
**Edge Impulse | TensorFlow Lite | Arduino Deployment**

<p align="center">
📷 **[Insert Project Overview Image Here]**
</p>

---

## 1. Project Description

This project presents a TinyML-based classification system for identifying **Normal** and **Fault** operating conditions of a **6V DC Motor Air Pump**.  
The solution is implemented using **Edge Impulse**, enabling offline inference with low latency and minimal memory usage on microcontroller-class devices.

The trained model distinguishes motor health conditions based on sensor data and is suitable for real-time embedded deployment.

---

## 2. Dataset Description

<p align="center">
📷 **[Insert Dataset Structure Image Here]**
</p>

The dataset consists of time-series samples collected from the DC motor air pump under two operating conditions.

### Dataset Summary

| Class   | Samples |
|--------|---------|
| Normal | 4000    |
| Fault  | 4000    |
| **Total** | **8000** |

### Data Split Strategy

- **Training + Validation:** 80%
- **Testing:** 20%

Further division of training data:
- **Training:** 70%
- **Validation:** 10%

This balanced distribution supports stable learning and unbiased evaluation.

---

## 3. Data Upload to Edge Impulse

<p align="center">
📷 **[Insert Edge Impulse Data Upload Screen Image Here]**
</p>

### Steps Followed

1. Created a new Edge Impulse project.
2. Uploaded all raw data files into the **Data Acquisition** section.
3. Assigned correct labels (`normal`, `fault`) during upload.
4. Verified sample balance and signal integrity using Edge Impulse tools.
5. Confirmed correct train–test separation.

---

## 4. Impulse Design

<p align="center">
📷 **[Insert Impulse Design Image Here]**
</p>

The impulse pipeline includes:

- **Input Block:** Raw sensor signal
- **Processing Block:** Feature extraction suitable for motor vibration patterns
- **Learning Block:** Neural network classifier

The impulse configuration was validated before training.

---

## 5. Model Training Results

<p align="center">
📷 **[Insert Training Performance Graph Image Here]**
</p>

### Training Performance

- **Training Accuracy:** 98.1%
- **Training Loss:** 0.06

### Class-wise Metrics

| Class | Precision | Recall | F1 Score |
|------|-----------|--------|----------|
| Normal | 0.97 | 0.98 | 0.97 |
| Fault  | 0.98 | 0.98 | 0.98 |

### Overall Metrics

- **Area under ROC Curve:** 0.98  
- **Weighted Precision:** 0.98  
- **Weighted Recall:** 0.98  
- **Weighted F1 Score:** 0.98  

### Confusion Matrix (Percentage)

| Actual \ Predicted | Normal | Fault | Uncertain |
|-------------------|--------|-------|-----------|
| Normal | 95.9% | 2.5% | 1.6% |
| Fault  | 1.0%  | 98.5% | 0.5% |

---

## 6. Model Testing Results

<p align="center">
📷 **[Insert Model Testing Result Image Here]**
</p>

- **Test Accuracy:** 97.23%

### Test Metrics

- **Area under ROC Curve:** 0.98  
- **Weighted Precision:** 0.98  
- **Weighted Recall:** 0.98  
- **Weighted F1 Score:** 0.98  

The testing results confirm consistent behavior between training and unseen data.

---

## 7. Model Deployment

<p align="center">
📷 **[Insert Deployment Configuration Image Here]**
</p>

### Selected Deployment Option

- **Arduino Library**
- Compatible with Arm-based Arduino and ESP32-class boards

This deployment allows the model to execute fully offline with minimal delay and reduced energy consumption.

---

## 8. TensorFlow Lite Export Details

<p align="center">
📷 **[Insert TensorFlow Lite Export Image Here]**
</p>

### Quantized Model (INT8)

| Parameter | Value |
|---------|-------|
| Inference Time | 1 ms |
| RAM Usage | 3.0 KB |
| Flash Usage | 34.4 KB |
| Accuracy | 97.60% |

### Float Model (FP32)

| Parameter | Value |
|---------|-------|
| Inference Time | 1 ms |
| RAM Usage | 3.1 KB |
| Flash Usage | 35.0 KB |
| Accuracy | 97.23% |

**Target Hardware Estimate:**  
Cortex-M4F @ 80 MHz

---

## 9. Arduino Integration

<p align="center">
📷 **[Insert Arduino Library Usage Image Here]**
</p>

### Integration Steps

1. Downloaded the Arduino library from Edge Impulse.
2. Added the library to Arduino IDE.
3. Loaded example inference sketch.
4. Connected sensor and motor setup.
5. Observed real-time classification results via Serial Monitor.

---

## 10. Folder Structure

