#include <Mode.h>

Mode::Mode(ForceKey *red, ForceKey *green, ForceKey *blue, const std::vector<Phase> &phases)
{
	this->red = red;
	this->green = green;
	this->blue = blue;
	this->phases = phases;
}

void Mode::onEnter()
{
	lastTime = millis();
	setPhase(0);
}

void Mode::update()
{
	if (phaseIndex < 0 || (size_t) phaseIndex >= phases.size())
		return;

	auto currentTime = millis();
	if (currentTime - lastTime < phases[phaseIndex].time)
		return;
	
	lastTime = millis();
	setPhase((phaseIndex + 1) % phases.size());
}

void Mode::setPhase(int index)
{
	phaseIndex = index;

	if (index < 0 || (size_t) index >= phases.size())
		return;

	auto &phase = phases[index];

	red->setInstant(phase.instant);
	green->setInstant(phase.instant);
	blue->setInstant(phase.instant);

	red->setDelta(phase.delta);
	green->setDelta(phase.delta);
	blue->setDelta(phase.delta);
	
	red->setRatio(phase.color.getRed());
	green->setRatio(phase.color.getGreen());
	blue->setRatio(phase.color.getBlue());
}