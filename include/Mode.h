#pragma once

#include <vector>
#include <ForceKey.h>
#include <Color.h>

class Mode
{
public:
	struct Phase
	{
		Color color;
		unsigned long time;
		bool instant;
		int delta;

		inline Phase(const Color &color, unsigned long time, bool instant, int delta) : color(color), time(time), instant(instant), delta(delta) {}
	};

	Mode(ForceKey *red, ForceKey *green, ForceKey *blue, const std::vector<Phase> &phases);
	void onEnter();
	void update();

	std::vector<Phase> phases;
private:
	ForceKey *red;
	ForceKey *green;
	ForceKey *blue;
	int phaseIndex;
	unsigned long lastTime;

	void setPhase(int index);
};