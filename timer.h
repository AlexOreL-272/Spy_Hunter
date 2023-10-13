class Timer {
private:
	unsigned int time;

public:
	Timer();
	~Timer();
	unsigned int GetTime() const;
	void UpdateTime();
};