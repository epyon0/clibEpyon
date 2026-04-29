#include <stdio.h>
#include <string.h>
#include <time.h>

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
