ILI9341 TFT Display Driver – STM32 (Internship Project)

This project implements a fully functional driver for the ILI9341-based TFT LCD Display using STM32 microcontrollers. It was developed as part of a Summer Internship project in 2023, focusing on embedded display interfacing and graphical rendering. The primary objective of the work was to enable a reliable SPI communication link between the microcontroller and the 2.4–2.8 inch ILI9341 TFT display and build the required low-level functions to visualize information on screen.

The driver initializes the display in multiple orientations and allows pixel-level access for drawing operations. Throughout the internship, several core graphical utilities were implemented, including routines to draw basic shapes, display strings using custom fonts, refresh specific areas of the screen, and create simple UI components. A demonstration firmware was developed to showcase text rendering and colored graphical elements on hardware.

The project also included configuration of GPIO pins, SPI settings, and reset sequences according to the official ILI9341 command structure, ensuring correct behavior across power cycles. The driver is organized into modular source files so that it can be reused and expanded easily in future embedded applications. The code has been tested on STM32 development hardware with successful display performance.

Future scope for the driver includes enabling DMA for faster data transfers, touch panel integration (XPT2046), optimized double-buffering for animations, and inclusion of bitmap image rendering to enhance UI capability.

This repository reflects practical learning in the fields of embedded software development, display interfacing, protocol handling, and graphics programming during the 2023 industrial internship experience.

One of my most significant engineering contributions is the development of a complete SDK that integrates the XCVR driver, the raw-PCM/IEC60958 application, and a set of APIs and testing tools. This SDK enables reliable transmission of IEC 60958 frames from the i.MX8MP-AB2 platform to the i.MX8MM-AB2 platform through an SPDIF line using the XCVR module. I built this system entirely from scratch, spanning hardware bring-up, firmware, driver logic, application layer development, and validation.

Today, my focus is on embedded C/C++, board bring-up, digital audio interfaces, low-level debugging, and real-time hardware-software integration. I enjoy taking complex hardware requirements and turning them into clean, maintainable, and reliable embedded systems.
