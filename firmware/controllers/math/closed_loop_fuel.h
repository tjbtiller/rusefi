// closed_loop_fuel.h

#pragma once

struct stft_s;

struct ClosedLoopFuelResult {
	ClosedLoopFuelResult() {
		// Default is no correction, aka 1.0 multiplier
		for (size_t i = 0; i < FT_BANK_COUNT; i++) {
			banks[i] = 1.0f;
		}
	}

	float banks[FT_BANK_COUNT];
};

ClosedLoopFuelResult fuelClosedLoopCorrection();
size_t computeStftBin(float rpm, float load, stft_s& cfg);
bool shouldUpdateCorrection(SensorType sensor);
bool checkIfTuningVeNow();
