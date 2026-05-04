#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#include <unistd.h>

// Print formated 'text' to STDERR, displays date time, caller function (__func__), and line number (__LINE__)
void debug(const char *text, bool enabled, const char *func, const int line) {
    time_t now = time(NULL);
    struct tm *t_info = localtime(&now);
    char buf[25];
    if (enabled) {
        strftime(buf, sizeof(buf), "%Y-%m-%dT%H:%M:%Sz", t_info);
        fprintf(stderr, "%s | %s:%d | %s\n", buf, func, line, text);
    }
}

// Returns true if there is a pipe from STDIN
bool isPipe() {
    return !isatty(STDIN_FILENO);
}

// Returns (nbytes + 1) from STDIN
char * readPipe(size_t nbytes) {
    char * buffer = calloc(nbytes, sizeof(char));
    if (buffer && isPipe()) {
        size_t rbytes = fread(buffer, sizeof(char), nbytes, stdin);
    }

    return buffer;
}

char * asciiChar(char byte) {
    char * output = malloc(4);
    if (byte < 33 || byte == 127) {
        switch (byte) {
            case 0:
                output = "NUL";
                break;
            case 1:
                output = "SOH";
                break;
            case 2:
                output = "STX";
                break;
            case 3:
                output = "ETX";
                break;
            case 4:
                output = "EOT";
                break;
            case 5:
                output = "ENQ";
                break;
            case 6:
                output = "ACK";
                break;
            case 7:
                output = "BEL";
                break;
            case 8:
                output = "BS ";
                break;
            case 9:
                output = "HT ";
                break;
            case 10:
                output = "LF ";
                break;
            case 11:
                output = "VT ";
                break;
            case 12:
                output = "FF ";
                break;
            case 13:
                output = "CR ";
                break;
            case 14:
                output = "SO ";
                break;
            case 15:
                output = "SI ";
                break;
            case 16:
                output = "DLE";
                break;
            case 17:
                output = "DC1";
                break;
            case 18:
                output = "DC2";
                break;
            case 19:
                output = "DC3";
                break;
            case 20:
                output = "DC4";
                break;
            case 21:
                output = "NAK";
                break;
            case 22:
                output = "SYN";
                break;
            case 23:
                output = "ETB";
                break;
            case 24:
                output = "CAN";
                break;
            case 25:
                output = "EM ";
                break;
            case 26:
                output = "SUB";
                break;
            case 27:
                output = "ESC";
                break;
            case 28:
                output = "FS ";
                break;
            case 29:
                output = "GS ";
                break;
            case 30:
                output = "RS ";
                break;
            case 31:
                output = "US ";
                break;
            case 32:
                output = "SP ";
                break;
            case 127:
                output = "DEL";
                break;
            
        }
    } else {
        snprintf(output, sizeof(output), " %c ", byte);
    }
    return  output;
}

// Truncate string to length
char * truncString(char *text, size_t length) {
    char * buffer = calloc(length + 1, sizeof(char));
    if (buffer) {
        if (length >= 0) {
            strncpy(buffer, text, length);
            buffer[length] = '\0';
        } 
    }

    return buffer;
}

// Return string of the value of 'number' of bytes in a human readable format (i.e. GB, TiB, MB, etc)
char * humanizeBytes(long long unsigned  number, bool SIuints) {
    static char buffer[200];
    if (SIuints) {
        if (number >= pow(10,18)) {
            snprintf(buffer, sizeof(buffer), "%0.2f EB", number / pow(10,18));
        } else if (number >= pow(10,15)) {
            snprintf(buffer, sizeof(buffer), "%0.2f PB", number / pow(10,15));
        } else if (number >= pow(10,12)) {
            snprintf(buffer, sizeof(buffer), "%0.2f TB", number / pow(10,12));
        } else if (number >= pow(10,9)) {
            snprintf(buffer, sizeof(buffer), "%0.2f GB", number / pow(10,9));
        } else if (number >= pow(10,6)) {
            snprintf(buffer, sizeof(buffer), "%0.2f MB", number / pow(10,6));
        } else if (number >= pow(10,3)) {
            snprintf(buffer, sizeof(buffer), "%0.2f KB", number / pow(10,3));
        } else {
            snprintf(buffer, sizeof(buffer), "%llu B", number);
        }
    } else {
if (number >= pow(2,60)) {
            snprintf(buffer, sizeof(buffer), "%0.2f EiB", number / pow(2,60));
        } else if (number >= pow(2,50)) {
            snprintf(buffer, sizeof(buffer), "%0.2f PiB", number / pow(2,50));
        } else if (number >= pow(2,40)) {
            snprintf(buffer, sizeof(buffer), "%0.2f TiB", number / pow(2,40));
        } else if (number >= pow(2,30)) {
            snprintf(buffer, sizeof(buffer), "%0.2f GiB", number / pow(2,30));
        } else if (number >= pow(2,20)) {
            snprintf(buffer, sizeof(buffer), "%0.2f MiB", number / pow(2,20));
        } else if (number >= pow(2,10)) {
            snprintf(buffer, sizeof(buffer), "%0.2f KiB", number / pow(2,10));
        } else {
            snprintf(buffer, sizeof(buffer), "%llu B", number);
        }
    }

    return buffer;
}

/////////////////
// ANSI CURSOR //
/////////////////

// Move cursor to home position (0,0)
void ansiCursorHome() {
    printf("\033[H]");
}
// Move cursor to position (row,column)
void ansiCursorMove(int row, int column) {
    printf("\033[%d;%dH]", row, column);
}
// Move cursor up 'count' lines
void ansiCursorUp(int count) {
    printf("\0333[%dA", count);
}
// Move cursor down 'count' lines
void ansiCursorDown(int count) {
    printf("\033[%dB", count);
}
// Move cursor right 'count' columns
void ansiCursorRight(int count) {
    printf("\033[%dC", count);
}
// Move cursor left 'count' columns
void ansiCursorLeft(int count) {
    printf("\033[%dD", count);
}
// Move cursor to beginning of next line, 'count' lines down
void ansiDownBeginning(int count) {
    printf("\033[%dE", count);
}
// Move cursor to 'column'
void ansiCursorColumn(int column) {
    printf("\033[%dG", column);
}
// Request cursor position
void ansiCursorPosition() {
    printf("\033[6n");
}
// Move cursor one line up, scrolling if needed
void ansiCursorUpOne() {
    printf("\033 M");
}
// Save cursor position (DEC) (recommended)
void ansiCursorSavePos() {
    printf("\033 7");
}
// Restores the cursor to the last saved position (DEC)
void ansiCursorLoadPos() {
    printf("\033 8");
}
// Save cursor position (SCO)
void ansiCursorSavePosSCO() {
    printf("\033[s");
}
// Restores the cursor to the last saved position (SCO)
void ansiCursorLoadPosSCO() {
    printf("\033[u");
}
// Erase from cursor to beginning of screen
void ansiCursorEraseScreenEnd() {
    printf("\033[0J");
}
// Erase entire screen
void ansiCursorEraseScreenAll() {
    printf("\033[2J");
}
// Erase saved lines
void ansiCursorEraseSavedLines() {
    printf("\033[3J");
}
// Erase from cursor to end of line
void ansiCursorEraseLineEnd() {
    printf("\033[0K");
}
// Erase from start of line to the cursor
void ansiCursorEraseLineBeginning() {
    printf("\033[1K");
}
// Erase the entire line
void ansiCursorEraseLineAll() {
    printf("\033[2K");
}
// Make cursor invisible
void ansiCursorInvisible() {
    printf("\033[?25l");
}
// Make cursor visible
void ansiCursorVisible() {
    printf("\033[?25h");
}
// Restore screen
void ansiScreenRestore() {
    printf("\033[?47l");
}
// Save screen
void ansiScreenSave() {
    printf("\033[?47h");
}

// Enables the alternative buffer
void ansiEnableAltBuffer() {
    printf("\033[?1049h");
}
// Disable the alternative buffer
void ansiDisableAltBuffer() {
    printf("\033[?1049l");
}

///////////////
// ANSI TEXT //
///////////////

// Reset all modes (styles and colors)
void ansiReset() {
    printf("\033[0m");
}
// Set bold mode
void ansiTextBold() {
    printf("\033[1m");
}
// Reset bold mode (and dim/faint modes)
void ansiTextBoldReset() {
    printf("\033[22m");
}
// Set dim/faint mode
void ansiTextDim() {
    printf("\033[2m");
}
// Reset dim/faint mode (and bold mode)
void ansiTextDimReset() {
    ansiTextBoldReset();
}
// Set dim/faint mode
void ansiTextFaint() {
    ansiTextDim();
}
// Reset dim/faint mode (and bold mode)
void ansiTextFaintReset() {
    ansiTextDimReset();
}
// Set italic mode
void ansiTextItalic() {
    printf("\033[3m");
}
// Reset italic mode
void ansiTextItalicReset() {
    printf("\033[23m");
}
// Set underline mode
void ansiTextUnderline() {
    printf("\033[4m");
}
// Reset underline mode
void ansiTextUnderlineReset() {
    printf("\033[24m");
}
// Set blinking mode
void ansiTextBlinking() {
    printf("\033[5m");
}
// Reset blinking mode
void ansiTextBlinkingReset() {
    printf("\033[25m");
}
// Set inverse/reverse mode
void ansiTextInverse() {
    printf("\033[7m");
}
// Reset inverse/reverse mode
void ansiTextInverseReset() {
    printf("\033[27m");
}
// Set inverse/reverse mode
void ansiTextReverse() {
    ansiTextInverse();
}
// Reset inverse/reverse mode
void ansiTextReverseReset() {
    ansiTextInverseReset();
}
// Set hidden/invisible mode
void ansiTextHidden() {
    printf("\033[8m");
}
// Reset hidden/invisible mode
void ansiTextHiddenReset() {
    printf("\033[28m");
}
// Set hidden/invisible mode
void ansiTextInvisible() {
    ansiTextHidden();
}
// Reset hidden/invisible mode
void ansiTextInvisibleReset() {
    ansiTextHiddenReset();
}
// Set strikthrough mode
void ansiTextStrikethrough() {
    printf("\033[9m");
}
// Reset strikethrough mode
void ansiTextStrikethroughReset() {
    printf("\033[29m");
}

////////////////
// ANSI COLOR //
////////////////

// Set foreground color
void ansiColorBlackFG() {
    printf("\033[30m");
}
// Set background color
void ansiColorBlackBG() {
    printf("\033[40m");
}
// Set foreground color
void ansiColorRedFG() {
    printf("\033[31m");
}
// Set background color
void ansiColorRedBG() {
    printf("\033[41m");
}
// Set foreground color
void ansiColorGreenFG() {
    printf("\033[32m");
}
// Set background color
void ansiColorGreenBG() {
    printf("\033[42m");
}
// Set foreground color
void ansiColorYellowFG() {
    printf("\033[33m");
}
// Set background color
void ansiColorYellowBG() {
    printf("\033[43m");
}
// Set foreground color
void ansiColorBlueFG() {
    printf("\033[34m");
}
// Set background color
void ansiColorBlueBG() {
    printf("\033[44m");
}
// Set foreground color
void ansiColorMagentaFG() {
    printf("\033[35m");
}
// Set background color
void ansiColorMagentaBG() {
    printf("\033[45m");
}
// Set foreground color
void ansiColorCyanFG() {
    printf("\033[36m");
}
// Set background color
void ansiColorCyanBG() {
    printf("\033[46m");
}
// Set foreground color
void ansiColorWhiteFG() {
    printf("\033[37m");
}
// Set background color
void ansiColorWhiteBG() {
    printf("\033[47m");
}
// Set foreground color
void ansiColorDefaultFG() {
    printf("\033[39m");
}
// Set background color
void ansiColorDefaultBG() {
    printf("\033[49m");
}
// Set foreground color
void ansiColorBlackBrightFG() {
    printf("\033[90m");
}
// Set background color
void ansiColorBlackBrightBG() {
    printf("\033[100m");
}
// Set foreground color
void ansiColorRedBrightFG() {
    printf("\033[91m");
}
// Set background color
void ansiColorRedBrightBG() {
    printf("\033[101m");
}
// Set foreground color
void ansiColorGreenBrightFG() {
    printf("\033[92m");
}
// Set background color
void ansiColorGreenBrightBG() {
    printf("\033[102m");
}
// Set foreground color
void ansiColorYellowBrightFG() {
    printf("\033[93m");
}
// Set background color
void ansiColorYellowBrightBG() {
    printf("\033[103m");
}
// Set foreground color
void ansiColorBlueBrightFG() {
    printf("\033[94m");
}
// Set background color
void ansiColorBlueBrightBG() {
    printf("\033[104m");
}
// Set foreground color
void ansiColorMagentaBrightFG() {
    printf("\033[95m");
}
// Set background color
void ansiColorMagentaBrightBG() {
    printf("\033[105m");
}
// Set foreground color
void ansiColorCyanBrightFG() {
    printf("\033[96m");
}
// Set background color
void ansiColorCyanBrightBG() {
    printf("\033[106m");
}
// Set foreground color
void ansiColorWhiteBrightFG() {
    printf("\033[97m");
}
// Set background color
void ansiColorWhiteBrightBG() {
    printf("\033[107m");
}
// Set foreground 256-bit color of value 'value'
void ansiColor256FG(char value) {
    printf("\033[38;5;%cm", value);
}
// Set background 256-bit color of value 'value'
void ansiColor256BG(char value) {
    printf("\033[48;5;%cm", value);
}
// Set foreground RBG color
void ansiColorRgbFG(char red, char green, char blue) {
    printf("\033[38;2;%c;%c;%cm", red, green, blue);
}
// Set foreground RBG color
void ansiColorRgbBG(char red, char green, char blue) {
    printf("\033[48;2;%c;%c;%cm", red, green, blue);
}

/////////////////
// ANSI SCREEN //
/////////////////

// Enables line wrapping
void ansiScreenModeLineWrapping() {
    printf("\033[=7h");
}

// Disables line wrapping
void ansiScreenModeLineWrappingReset() {
    printf("\033[=7l");
}








// TESTING
int main() {
    char * testString = humanizeBytes(12345, true);

    ansiColorBlueFG();
    debug("DEBUG TEST", true, __func__, __LINE__);
    debug("DEBUG TEST2", false, __func__, __LINE__);
    ansiColorMagentaFG();
/*
    for (long long i = 0; i < 13; i++) {
        testString = truncString("1234567890", i);
        printf("LEN:%lld  %s\n", i, testString);
    }
    for (long long i = 0; i > -13; i--) {
        testString = truncString("1234567890", i);
        printf("LEN:%lld  %s\n", i, testString);
    }
*/

    printf("IS PIPE: %s\n", isPipe() ? "true" : "false");

    /*
    for (int i = 0; i < 15; i++) {
        //char * testOutput = malloc((i + 1) * sizeof(char));
        char * testOutput = malloc(i * sizeof(char));
        testOutput = readPipe(i);
        //testOutput[sizeof(testOutput)/sizeof(char)] = '\0';
        printf("PIPE[%d]: [%s]\n", i, testOutput);
    }


    size_t n = 1024 * 2;
    char * randomMemory = malloc(n);
    for (int i = 0; i < n; i++) {
        //printf("%03u 0x%hhX [%s]\n", randomMemory[i], randomMemory[i], asciiChar(randomMemory[i]));
        if (randomMemory[i] > 32 && randomMemory[i] != 127) {
            //printf("%s ", asciiChar(randomMemory[i]));
            printf("%c", randomMemory[i]);
        } else {
            printf("\n");
        }
    }
*/

    ansiColorGreenBrightFG();

    int x = 25;
    char * testDebug = calloc(x, sizeof(char));
    testDebug = readPipe(x);

    for (int i = 0; i < x; i++) {
        printf("[%s]  %03d  0x%hhX\n", asciiChar(testDebug[i]),  i, testDebug[i]);
    }

    ansiColorDefaultFG();
}
