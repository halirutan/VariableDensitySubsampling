#define CATCH_CONFIG_RUNNER
#include <catch2/catch_session.hpp>
#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include "SamplingMask.h"
#include "PoissonSubsampling.h"
#include "VDSamplingUpper.h"

int main(int argc, char *argv[])
{
	int result = Catch::Session().run(argc, argv);
	return result;
}

TEST_CASE("Sampling Mask Test") {
	SECTION("Create and assign") {
		int data[20];
		for (int i = 0; i < 20; i++) {
			data[i] = i;
		}

		SamplingMask mask{20, 10, 1};
		for (size_t h = 0; h < mask.height(); h++) {
			mask.setLine(h, 0, data);
		}

	}
}

TEST_CASE("VDSamplingUpper creation and destruction") {
	SECTION("Destruction segfault") {
		VDSamplingUpper *object = new VDSamplingUpper(
			true,
			4,
			1,
			256,
			128,
			2.0,
			1.0,
			true,
			2.0,
			20,
			0.95,
			25760
		);
		delete object;
	}
}

TEST_CASE("Poisson Subsampling") {

	SECTION("Default parameters") {
		SamplingMask mask = poissonSubsampling(32, 16, 2.0, 0.065, 1.0, true, 10, 4, 1, true, 2.0, 2.0, 1, 1.0);
		size_t ones = 0;
		size_t zeroes = 0;
		for (size_t p = 0; p < mask.phases(); p++) {
			for (size_t h = 0; h < mask.height(); h++) {
				for (size_t w = 0; w < mask.width(); w++) {
					auto value = mask.get(w, h, p);
					if (value == 1) {
						ones++;
					}
					else if (value == 0) {
						zeroes++;
					}
					else {
						// There should only be 1s and 0s in the data
						FAIL();
					}
				}
			}
		}
		CHECK(zeroes > ones);
	}
}