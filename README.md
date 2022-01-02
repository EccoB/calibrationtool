# Calibration Tool for DinA4-sheet

Simple calibration tool that lets the user set position of four corners of an DinA4 in an image and calculates the position of the camera in relation to the corners of the sheet.
That means:


## Getting Started

### Dependencies

```
apt-get install -y \
    build-essential \
    cmake \
    qtbase5-dev \
    libopencv-dev
```

### Building
Use cmake, change directory into the repository and run

```
mkdir build
    cd build
    cmake -S ../ -B ./
    make
```

### Running
Start the program, click the load image button, load the image with the DinA4-sheet.
Click on the corners of the DinA4-sheet. If all four corners are marked, the coordinate zero point is displayed in the image and in the bottom right, the position of the camera is shown.

You may click the Reset-Button to again position the corners.
You may load the image directly by providing the path to the image directly as an argument at startup.
