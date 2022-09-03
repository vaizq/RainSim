#pragma once
#include <al.h>
#include <string>

template <typename T>
class AlSound
{
public:
	static AlSound& instance() {
		static AlSound instance;
		return instance;
	}
	
	void loadSound(const T& id, const std::string& filePath);
	void playSound(const T& id);
private:
	AlSound();
};
