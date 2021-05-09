/*
  EventTimer.h - Library untuk Sequence Timer
  Dibuat Oleh : Sam May 08, 2021
*/
#ifndef EventTimer_h
#define EventTimer_h

	#include <Arduino.h>
	#include "../ioDevices/digitalInput.h"
	#include "../ioDevices/digitalOutput.h"

	const int A_SECOND = 1000;
	const int A_MINUTE = A_SECOND * 60;
	const int A_HOUR = A_MINUTE * 60;
	const int A_DAY = A_HOUR * 24;
	const int A_WEEK = A_DAY * 7;

	class EventTimer{
		public:
			EventTimer(String );
			void info();
			void init();
			void init(boolean);
			void setEnable(boolean);
			void setCyclic(boolean);
			void setOneShoot(boolean);
			boolean execute();
			void attachInput(DigitalInput*);
			void attachOutput(DigitalOutput*);

			void setDelay(unsigned long);
			void setDelay(int, int);
			void setDelay(int, int, int);

			void setDuration(unsigned long);
			void setDuration(int, int);
			void setDuration(int, int, int);

		private:
			String _id;
			boolean _isEnable, _isCyclic, _isOneShoot;
			boolean _isInputAvailable, _isOutputAvailable;
			boolean _prevStatus;
			unsigned long _delayMilli, _durationMilli;
			unsigned long _prevDelayMilli, _prevDurationMilli;
			int _delayHour, _delayMinute, _delaySecond;
			int _durationHour, _durationMinute, _durationSecond;
			DigitalInput *_digInput;
			DigitalOutput *_digOutput;

			void _setOutput(boolean);
	};

#endif