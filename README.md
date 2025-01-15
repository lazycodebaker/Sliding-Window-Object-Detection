# Sliding Window Object Detection with OpenCV

This repository demonstrates object detection using a sliding window approach with the **MobileNet-SSD** model and OpenCV's deep learning module. The sliding window method scans an image at different positions and scales to detect objects.

---

## Features

- Sliding window implementation for object detection.
- Pre-trained MobileNet-SSD for detecting 20 different classes.
- Visualization of sliding windows and detected objects.
- Saves the output image with bounding boxes and labels.

---

## Prerequisites

Ensure you have the following installed:

- OpenCV (`opencv-python` and `opencv-python-headless`)
- OpenCV DNN module
- C++ compiler with C++11 support

---

## Classes Detected

The following classes are detectable with the MobileNet-SSD model:

`background`, `aeroplane`, `bicycle`, `bird`, `boat`, `bottle`, `bus`, `car`, `cat`, `chair`, `cow`, `diningtable`, `dog`, `horse`, `motorbike`, `person`, `pottedplant`, `sheep`, `sofa`, `train`, `tvmonitor`

---

## File Structure

- `main.cpp`: Core logic for sliding window object detection.
- `MobileNetSSD_deploy.prototxt.txt`: Network architecture of MobileNet-SSD.
- `MobileNetSSD_deploy.caffemodel`: Pre-trained weights for MobileNet-SSD.
- `1.jpg`: Sample image for testing.

---

## How to Run

### 1. Clone the Repository

```bash
git clone https://github.com/lazycodebaker/Sliding-Window-Object-Detection
cd Sliding-Window-Object-Detection


## Ouput Image
 ![Output with Detections](https://github.com/lazycodebaker/Sliding-Window-Object-Detection/blob/main/image.png)
