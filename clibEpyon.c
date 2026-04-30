#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

// Print formated 'text' to STDERR, displays date time, caller function (__func__), and line number (__LINE__)
void debug(const char *text, const char *func, const int line) {
    time_t now = time(NULL);
    struct tm *t_info = localtime(&now);
    char buf[25];
    strftime(buf, sizeof(buf), "%Y-%m-%dT%H:%M:%Sz", t_info);
    
    fprintf(stderr, "%s | %s:%d | %s\n", buf, func, line, text);
}

// Truncate string to length, negative values truncate from begining of string
void truncString(char *text, int length) {
    if (length < strlen(text) && length >= 0) {
        text[length] = '\0';
    }

    if (length < 0) {
        length = length * -1;
        for (int i = 0; i < length; i++) {
            for (int j = 1; j <= strlen(text); j++) {
                text[j-1] = text[j];
            }
        }
    }
}

// Return string of the value of 'number' of bytes in a human readable format (i.e. GB, TiB, MB, etc)
char * humanizeBytes(unsigned long long number, bool SIuints) {
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
void AnsiCursorHome() {
    printf("\033[H]");
}
// Move cursor to position (row,column)
void AnsiCursorMove(int row, int column) {
    printf("\033[%d;%dH]", row, column);
}
// Move cursor up 'count' lines
void AnsiCursorUp(int count) {
    printf("\0333[%dA", count);
}
// Move cursor down 'count' lines
void AnsiCursorDown(int count) {
    printf("\033[%dB", count);
}
// Move cursor right 'count' columns
void AnsiCursorRight(int count) {
    printf("\033[%dC", count);
}
// Move cursor left 'count' columns
void AnsiCursorLeft(int count) {
    printf("\033[%dD", count);
}
// Move cursor to beginning of next line, 'count' lines down
void AnsiDownBeginning(int count) {
    printf("\033[%dE", count);
}
// Move cursor to 'column'
void AnsiCursorColumn(int column) {
    printf("\033[%dG", column);
}
// Request cursor position
void AnsiCursorPosition() {
    printf("\033[6n");
}
// Move cursor one line up, scrolling if needed
void AnsiCursorUpOne() {
    printf("\033 M");
}
// Save cursor position (DEC) (recommended)
void AnsiCursorSavePos() {
    printf("\033 7");
}
// Restores the cursor to the last saved position (DEC)
void AnsiCursorLoadPos() {
    printf("\033 8");
}
// Save cursor position (SCO)
void AnsiCursorSavePosSCO() {
    printf("\033[s");
}
// Restores the cursor to the last saved position (SCO)
void AnsiCursorLoadPosSCO() {
    printf("\033[u");
}
// Erase from cursor to beginning of screen
void AnsiCursorEraseScreenEnd() {
    printf("\033[0J");
}
// Erase entire screen
void AnsiCursorEraseScreenAll() {
    printf("\033[2J");
}
// Erase saved lines
void AnsiCursorEraseSavedLines() {
    printf("\033[3J");
}
// Erase from cursor to end of line
void AnsiCursorEraseLineEnd() {
    printf("\033[0K");
}
// Erase from start of line to the cursor
void AnsiCursorEraseLineBeginning() {
    printf("\033[1K");
}
// Erase the entire line
void AnsiCursorEraseLineAll() {
    printf("\033[2K");
}
// Make cursor invisible
void AnsiCursorInvisible() {
    printf("\033[?25l");
}
// Make cursor visible
void AnsiCursorVisible() {
    printf("\033[?25h");
}
// Restore screen
void AnsiScreenRestore() {
    printf("\033[?47l");
}
// Save screen
void AnsiScreenSave() {
    printf("\033[?47h");
}

// Enables the alternative buffer
void AnsiEnableAltBuffer() {
    printf("\033[?1049h");
}
// Disable the alternative buffer
void AnsiDisableAltBuffer() {
    printf("\033[?1049l");
}

///////////////
// ANSI TEXT //
///////////////

// Reset all modes (styles and colors)
void AnsiReset() {
    printf("\033[0m");
}
// Set bold mode
void AnsiTextBold() {
    printf("\033[1m");
}
// Reset bold mode (and dim/faint modes)
void AnsiTextBoldReset() {
    printf("\033[22m");
}
// Set dim/faint mode
void AnsiTextDim() {
    printf("\033[2m");
}
// Reset dim/faint mode (and bold mode)
void AnsiTextDimReset() {
    AnsiTextBoldReset();
}
// Set dim/faint mode
void AnsiTextFaint() {
    AnsiTextDim();
}
// Reset dim/faint mode (and bold mode)
void AnsiTextFaintReset() {
    AnsiTextDimReset();
}
// Set italic mode
void AnsiTextItalic() {
    printf("\033[3m");
}
// Reset italic mode
void AnsiTextItalicReset() {
    printf("\033[23m");
}
// Set underline mode
void AnsiTextUnderline() {
    printf("\033[4m");
}
// Reset underline mode
void AnsiTextUnderlineReset() {
    printf("\033[24m");
}
// Set blinking mode
void AnsiTextBlinking() {
    printf("\033[5m");
}
// Reset blinking mode
void AnsiTextBlinkingReset() {
    printf("\033[25m");
}
// Set inverse/reverse mode
void AnsiTextInverse() {
    printf("\033[7m");
}
// Reset inverse/reverse mode
void AnsiTextInverseReset() {
    printf("\033[27m");
}
// Set inverse/reverse mode
void AnsiTextReverse() {
    AnsiTextInverse();
}
// Reset inverse/reverse mode
void AnsiTextReverseReset() {
    AnsiTextInverseReset();
}
// Set hidden/invisible mode
void AnsiTextHidden() {
    printf("\033[8m");
}
// Reset hidden/invisible mode
void AnsiTextHiddenReset() {
    printf("\033[28m");
}
// Set hidden/invisible mode
void AnsiTextInvisible() {
    AnsiTextHidden();
}
// Reset hidden/invisible mode
void AnsiTextInvisibleReset() {
    AnsiTextHiddenReset();
}
// Set strikthrough mode
void AnsiTextStrikethrough() {
    printf("\033[9m");
}
// Reset strikethrough mode
void AnsiTextStrikethroughReset() {
    printf("\033[29m");
}

////////////////
// ANSI COLOR //
////////////////

// Set foreground color
void AnsiColorBlackFG() {
    printf("\033[30m");
}
// Set background color
void AnsiColorBlackBG() {
    printf("\033[40m");
}
// Set foreground color
void AnsiColorRedFG() {
    printf("\033[31m");
}
// Set background color
void AnsiColorRedBG() {
    printf("\033[41m");
}
// Set foreground color
void AnsiColorGreenFG() {
    printf("\033[32m");
}
// Set background color
void AnsiColorGreenBG() {
    printf("\033[42m");
}
// Set foreground color
void AnsiColorYellowFG() {
    printf("\033[33m");
}
// Set background color
void AnsiColorYellowBG() {
    printf("\033[43m");
}
// Set foreground color
void AnsiColorBlueFG() {
    printf("\033[34m");
}
// Set background color
void AnsiColorBlueBG() {
    printf("\033[44m");
}
// Set foreground color
void AnsiColorMagentaFG() {
    printf("\033[35m");
}
// Set background color
void AnsiColorMagentaBG() {
    printf("\033[45m");
}
// Set foreground color
void AnsiColorCyanFG() {
    printf("\033[36m");
}
// Set background color
void AnsiColorCyanBG() {
    printf("\033[46m");
}
// Set foreground color
void AnsiColorWhiteFG() {
    printf("\033[37m");
}
// Set background color
void AnsiColorWhiteBG() {
    printf("\033[47m");
}
// Set foreground color
void AnsiColorDefaultFG() {
    printf("\033[39m");
}
// Set background color
void AnsiColorDefaultBG() {
    printf("\033[49m");
}
// Set foreground color
void AnsiColorBlackBrightFG() {
    printf("\033[90m");
}
// Set background color
void AnsiColorBlackBrightBG() {
    printf("\033[100m");
}
// Set foreground color
void AnsiColorRedBrightFG() {
    printf("\033[91m");
}
// Set background color
void AnsiColorRedBrightBG() {
    printf("\033[101m");
}
// Set foreground color
void AnsiColorGreenBrightFG() {
    printf("\033[92m");
}
// Set background color
void AnsiColorGreenBrightBG() {
    printf("\033[102m");
}
// Set foreground color
void AnsiColorYellowBrightFG() {
    printf("\033[93m");
}
// Set background color
void AnsiColorYellowBrightBG() {
    printf("\033[103m");
}
// Set foreground color
void AnsiColorBlueBrightFG() {
    printf("\033[94m");
}
// Set background color
void AnsiColorBlueBrightBG() {
    printf("\033[104m");
}
// Set foreground color
void AnsiColorMagentaBrightFG() {
    printf("\033[95m");
}
// Set background color
void AnsiColorMagentaBrightBG() {
    printf("\033[105m");
}
// Set foreground color
void AnsiColorCyanBrightFG() {
    printf("\033[96m");
}
// Set background color
void AnsiColorCyanBrightBG() {
    printf("\033[106m");
}
// Set foreground color
void AnsiColorWhiteBrightFG() {
    printf("\033[97m");
}
// Set background color
void AnsiColorWhiteBrightBG() {
    printf("\033[107m");
}
// Set foreground 256-bit color of value 'value'
void AnsiColor256FG(char value) {
    printf("\033[38;5;%cm", value);
}
// Set background 256-bit color of value 'value'
void AnsiColor256BG(char value) {
    printf("\033[48;5;%cm", value);
}
// Set foreground RBG color
void AnsiColorRgbFG(char red, char green, char blue) {
    printf("\033[38;2;%c;%c;%cm", red, green, blue);
}
// Set foreground RBG color
void AnsiColorRgbBG(char red, char green, char blue) {
    printf("\033[48;2;%c;%c;%cm", red, green, blue);
}

/////////////////
// ANSI SCREEN //
/////////////////

// Set screen mode to 40 x 25 monochrome (text)
void AnsiScreenMode40x25Monochrome() {
    printf("\033[=0h");
}













// TESTING
int main() {
    printf("TEST1\n");
    AnsiTextBlinking();
    printf("TEST2\n");
    AnsiTextBlinkingReset();
    AnsiTextBold();
    printf("TEST3\n");
    AnsiTextBoldReset();
    AnsiTextItalic();
    printf("TEST4\n");
    AnsiTextItalicReset();
    AnsiTextUnderline();
    printf("TEST5\n");
    AnsiTextUnderlineReset();
    printf("TEST6");
    AnsiTextStrikethrough();
    AnsiColorRedFG();
    printf("TEST7");
    AnsiTextStrikethroughReset();
    printf("TEST8\n");

    char * testString = humanizeBytes(12345, true);
    printf("%s\n", testString);
    testString = humanizeBytes(333333333, false);
    printf("%s\n", testString);
    testString = humanizeBytes(345234535345345, true);
    printf("%s\n", testString);
    testString = humanizeBytes(3452343452533345324, false);
    printf("%s\n", testString);
    testString = humanizeBytes(234, false);
    printf("%s\n", testString);
}