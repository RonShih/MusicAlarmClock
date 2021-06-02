#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>
#include <time.h>
#include <typeinfo>
#include <iomanip>
typedef unsigned int ui;
using namespace std;

struct AlarmClock
{
	ui hour;
	ui minute;
};

void setAlarm(AlarmClock*);
void getCurrentTime(AlarmClock*);
void showCurrentTime(ui,ui,ui,ui,ui,ui,ui);
void showAlarmClock(ui, ui);
void startMusic();
bool time_is_up();

ui hours, minutes;
int main()
{
	AlarmClock myclock;
	setAlarm(&myclock);
	getCurrentTime(&myclock);
	//ShellExecute(0, 0, "https://www.youtube.com/watch?v=LIIDh-qI9oI", 0, 0, SW_SHOW);
	return 0;
}

void setAlarm(AlarmClock *myclock)
{
	cout << "Set your clock" << endl;
	cout << "hour(0-23): "; 	cin >> myclock->hour;
	cout << "minute(0-59): "; cin >> myclock->minute;
}

void getCurrentTime(AlarmClock *myclock)
{
	ui seconds, minutes, hours, year, month, mday, wday;
	while(true)
	{ 
		time_t rawtime = time(0);
		struct tm *timeinfo;
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		seconds = timeinfo->tm_sec;
		minutes = timeinfo->tm_min;
		hours = timeinfo->tm_hour;
		year = timeinfo->tm_year;
		month = timeinfo->tm_mon;
		mday = timeinfo->tm_mday;
		wday = timeinfo->tm_wday;
		showCurrentTime(year, month, mday, hours, minutes, seconds, wday);
		showAlarmClock(myclock->hour, myclock->minute);
		if (myclock->hour == hours && myclock->minute == minutes)
		{
			startMusic();
			break;
		}
		system("CLS");
	}
}

void showCurrentTime(ui year, ui month, ui mday, ui hours, ui minutes, ui seconds, ui wday)
{
	cout << year + 1900 << "/" << month + 1 << "/" << mday << " " << hours << ":" << minutes << ":" << seconds << " day" << wday << endl << endl;
}
void showAlarmClock(ui hour, ui minute)
{
	cout << "Alarm Clock: " << setw(2) << setfill('0') << hour << ":" << setw(2) << setfill('0') << minute << endl;
}

void startMusic()
{
	ifstream fp;
	char buffer[256];
	vector<string> playlist;
	ui rdm;
	srand(time(NULL));
	fp.open("playlist.txt");
	if (!fp.is_open())
		cout << "Failed to open playlist" << endl;
	else
	{
		while (!fp.eof())
		{
			fp.getline(buffer, sizeof(buffer));
			playlist.push_back(buffer);
		}
	}
	rdm = rand() % playlist.size();
	ShellExecute(0, 0, playlist[rdm].c_str(), 0, 0, SW_SHOW);
}
