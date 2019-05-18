#include <ForceKey.h>
#include <Arduino.h>

ForceKey::ForceKey(int pin, int value, int maxValue, int delta)
{
    this->pin = pin;
    this->value = value;
    this->maxValue = maxValue;
    this->delta = delta;
}

void ForceKey::setup()
{
    pinMode(pin, OUTPUT);
}

void ForceKey::setRatio(float ratio)
{
    if (ratio > 1.0f)
        ratio = 1.0f;
    else if (ratio < 0.0f)
        ratio = 0.0f;
    float x = maxValue * ratio;
    target = (int) x;
    currentDelta = value < target ? delta : -delta;
    updatePin();
}

float ForceKey::getRatio() const
{
    return (float) value / maxValue;
}

void ForceKey::setHigh()
{
    setRatio(1.0f);
    updatePin();
}

void ForceKey::setLow()
{
    setRatio(0.0f);
    updatePin();
}

bool ForceKey::isLow() const
{
    return target == 0;
}

bool ForceKey::isHigh() const
{
    return target == maxValue;
}

bool ForceKey::finished() const
{
    return value == target;
}

void ForceKey::toggle()
{
    if (value == maxValue)
        setLow();
    else if (value == 0)
        setHigh();
    else if (currentDelta > 0)
        setLow();
    else
        setHigh();
}

void ForceKey::update()
{
    if (finished())
        return;
    value += currentDelta;
    updatePin();
}

void ForceKey::updatePin()
{
    if (currentDelta > 0 && value > target)
        value = target;
    else if (currentDelta < 0 && value < target)
        value = target;

    if (value >= maxValue)
    {
        value = maxValue;
        digitalWrite(pin, HIGH);
    }
    else if (value <= 0)
    {
        value = 0;
        digitalWrite(pin, LOW);
    }
    else
    {
        analogWrite(pin, value);
    }
}
