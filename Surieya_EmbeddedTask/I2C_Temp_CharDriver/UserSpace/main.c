#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define DEVICE_PATH "/dev/i2c_temp"  // device file

int main() {
    int fd;
    char buffer[20];  // Buffer to store temperature readout
    ssize_t bytes_read;

    // Open the device file
    fd = open(DEVICE_PATH, O_RDONLY);
    if (fd < 0) {
        perror("Failed to open device file");
        return 1;
    }

    // Read temperature data from the driver
    bytes_read = read(fd, buffer, sizeof(buffer) - 1);
    if (bytes_read < 0) {
        perror("Failed to read from device");
        close(fd);
        return 1;
    }

    // Null-terminate the string and print it
    buffer[bytes_read] = '\0';
    printf("Temperature: %s°C\n", buffer);

    // Close the device file
    close(fd);
    return 0;
}