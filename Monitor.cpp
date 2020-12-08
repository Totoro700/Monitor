// Include
#include <iostream>
#include <Windows.h>
#include <string>

#pragma warning(disable : 4996)

// Std
using namespace std;


class Main
{
public:

    // Calculate CPU
    static float CalculateCPU(unsigned long long idleTicks, unsigned long long totalTicks)
    {
        // Set up variables
        static unsigned long long prevTotalTicks = 0;
        static unsigned long long prevIdleTicks = 0;

        // Calculate variables
        unsigned long long totalTicksSinceLastTime = totalTicks - prevTotalTicks;
        unsigned long long idleTicksSinceLastTime = idleTicks - prevIdleTicks;

        // Set value
        float finalValue = 1.0f - ((totalTicksSinceLastTime > 0) ? ((float)idleTicksSinceLastTime) / totalTicksSinceLastTime : 0);

        // Update variables
        prevTotalTicks = totalTicks;
        prevIdleTicks = idleTicks;

        // Return value
        return finalValue;
    }

    static unsigned long long FtToInt(const FILETIME& ft)
    {
        return (((unsigned long long)(ft.dwHighDateTime)) << 32) | ((unsigned long long)ft.dwLowDateTime);
    }

    float GetCPULoad()
    {
        FILETIME idleTime, kernelTime, userTime;

        // Return CPU as float
        return GetSystemTimes(&idleTime, &kernelTime, &userTime) ? CalculateCPU(FtToInt(idleTime), FtToInt(kernelTime) + FtToInt(userTime)) : -1.0f;
    }

    void getCpu()
    {
        // Get CPU and turn it into percentage (int)
        int cpu = GetCPULoad() * 100;

        // Get current time and date
        time_t now = time(0);

        // Print
        cout << "CPU Usage on -> " << ctime(&now) << "-> " << to_string(cpu) << "%" << endl;

        // Check if CPU == 100
        if (cpu == 100)
        {
            // Set text color to red
            system("Color 0C");
        }
        else
        {
            // Set color to green
            system("Color 0A");
        }

        // Wait for key ENTER
        cin.ignore();
    }
};

// Main
int main()
{
    // Include class
    Main m;

    // Welcome
    cout << "Welcome to CPU Monitor!" << endl;
    cout << "Press enter to start monitoring\n" << endl;

    // Wait for key ENTER
    cin.ignore();

    // Clear
    system("CLS");

    // Forever loop
    while (1 == 1)
    {
        // Get CPU
        m.getCpu();
    }
}