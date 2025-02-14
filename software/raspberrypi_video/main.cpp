#include <iostream>
#include <unistd.h>
#include "SPI.h"
#include "LeptonThread.h"

#define FRAME_COUNT 100  // Number of frames to capture before exiting

int main() {
    std::cout << "Starting FLIR Lepton Capture..." << std::endl;

    // Open SPI port
    SpiOpenPort(0, 20000000);  // Open SPI at 20MHz

    LeptonThread lepton;
    lepton.useLepton(3);  // Set to Lepton 3.x mode (160x120)
    
    for (int frame = 0; frame < FRAME_COUNT; frame++) {
        lepton.run();  // Capture frame
        
        // Print frame data
        for (int i = 0; i < 120; i++) {  // 120 rows
            for (int j = 0; j < 160; j++) {  // 160 cols
                printf("%04X ", lepton.getPixel(i, j));  // Print as 16-bit hex
            }
            printf("\n");
        }
        printf("\n------ Frame %d ------\n", frame);
        usleep(33000);  // 33ms delay (~30 FPS)
    }

    // Close SPI port
    SpiClosePort(0);
    return 0;
}
