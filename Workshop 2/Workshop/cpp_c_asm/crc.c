/* CRC calculations in C
 * https://en.wikipedia.org/wiki/Cyclic_redundancy_check
 * Based on https://web.archive.org/web/20190108202303/www.hackersdelight.org/hdcodetxt/crc.c.txt
 *
 */
#include <stdio.h>
#include <stdlib.h>
#ifdef _MSC_FULL_VER
#pragma warning (disable : 4146) // disable warning about unary minus on unsigned type
#endif

#if defined(_MSC_VER)
#define FUNC_NAME __FUNCTION__
#else
#define FUNC_NAME __func__
#endif


#define BUFFER_SIZE  256

static unsigned int crc32b(const unsigned char* buf, int length);   // function prototype
static void logBuffer(const unsigned char* buf, unsigned int length);

void testcrc(void)
{
    unsigned char* buffer;
    buffer = (unsigned char*)malloc(BUFFER_SIZE + 1);// allocate memory for buffer
    if (buffer == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }
    else
    {
        int crc;
        for (int i = 0; i < BUFFER_SIZE; i++)
        {
            buffer[i] = (unsigned char)(i & 0xFF); // fill buffer with some data
        };
        printf("%s input buffer:\n", FUNC_NAME);
        logBuffer(buffer, BUFFER_SIZE);

        crc = crc32b(buffer, BUFFER_SIZE);
        printf("CRC32 = 0x%08X\n", crc);

        free(buffer);// free allocated memory
        buffer = NULL; // Setting pointer NULL avoids dangling pointer issues.
    }
}

// CRC-32 algorithm (Ethernet, ZIP, etc.)
static unsigned int crc32b(const unsigned char* buf, int length) {
    int i, j;
    unsigned int byte, crc, mask;

    i = 0;
    crc = 0xFFFFFFFF;
    while (i < length) {
        byte = buf[i];            // Get next byte.
        crc = crc ^ byte;
        for (j = 7; j >= 0; j--) {    // Do eight times.
            mask = -(crc & 1);
            crc = (crc >> 1) ^ (0xEDB88320 & mask);
        }
        i = i + 1;
    }
    return ~crc;
}

// Log buffer content in hex format to console
static void logBuffer(const unsigned char* buf, unsigned int length)
{
    const unsigned int bytesPerLine = 16;

    for (unsigned int idx = 0; idx < length; idx += bytesPerLine)
    {
        // Print the offset
        printf("0x%08x: ", idx);

        // Print up to 16 bytes (or fewer if at end)
        for (unsigned int j = 0; j < bytesPerLine; j++)
        {
            if (idx + j < length)
                printf("%02x ", buf[idx + j]);
            else
                printf("   "); // padding for alignment

            // Add extra space after 8 bytes
            if (j == 7) printf(" ");
        }

        printf("\n");
    }
}