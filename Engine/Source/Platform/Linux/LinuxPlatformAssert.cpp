#include <Platform/Linux/LinuxBase.h>

#include <Base/Assert.h>
#include <Base/Diagnostics.h>

namespace Neowise {
    namespace {
        char* itoa(int value, char* result, int base) {
            // check that the base if valid
            if (base < 2 || base > 36) { *result = '\0'; return result; }

            char* ptr = result, * ptr1 = result, tmp_char;
            int tmp_value;

            do {
                tmp_value = value;
                value /= base;
                *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + (tmp_value - value * base)];
            } while (value);

            // Apply negative sign
            if (tmp_value < 0) *ptr++ = '-';
            *ptr-- = '\0';

            // Reverse the string
            while (ptr1 < ptr) {
                tmp_char = *ptr;
                *ptr-- = *ptr1;
                *ptr1++ = tmp_char;
            }
            return result;
        }
    }

	bool GIgnoreAssertation = false;

	void Assert(const char* msg, const char* fnName, const char* file, const int line) {
        char buffer[32]{};
        itoa(line, buffer, 10);

        if (GDiag) {
            GDiag << file << ":" << buffer << ":" << fnName << "(): '" << msg << "'\n";
        }

		if (!GIgnoreAssertation) {
			Platform::Linux::_BreakProcess();
		}
		else {
			GIgnoreAssertation = false;
		}
	}
}
