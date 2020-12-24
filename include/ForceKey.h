#ifndef ForceKey_h
#define ForceKey_h

class ForceKey
{
public:
    ForceKey(int pin, int value, int maxValue, int delta);
    void setup();
    void setRatio(float ratio);
    float getRatio() const;
    void setHigh();
    void setLow();
    bool isLow() const;
    bool isHigh() const;
    bool finished() const;
    void toggle();
    void update();
    inline int getValue() const { return value; }
	inline void setInstant(bool value) { instant = value; }
	inline void setDelta(int value) { delta = delta; }
private:
    int pin;
    int value;
    int maxValue;
    int delta;
    int currentDelta;
    int target;
	bool instant;

    void updatePin();
};

#endif

