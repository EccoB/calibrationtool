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

