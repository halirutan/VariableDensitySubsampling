#define CATCH_CONFIG_RUNNER
#include "PoissonSubsampling.h"
#include "SamplingMask.h"
#include "StdoutRedirector.h"
#include "VDSamplingUpper.h"
#include "catch2/matchers/catch_matchers.hpp"
#include <catch2/catch_session.hpp>
#include <catch2/catch_test_macros.hpp>
#include <stdexcept>
#include <cmath>

int main(int argc, char *argv[])
{
	int result = Catch::Session().run(argc, argv);
	return result;
}

TEST_CASE("Redirecting stdout")
{
	SECTION("Nothing gets thrown")
	{
		REQUIRE_NOTHROW(StdoutRedirector::redirectStdout(true));
		printf("This message should not appear");
		REQUIRE_NOTHROW(StdoutRedirector::redirectStdout(false));
	}


	SECTION("Double closing the redirect")
	{
		StdoutRedirector::redirectStdout(true);
		printf("This message should not appear");
		StdoutRedirector::redirectStdout(false);
		REQUIRE_THROWS_WITH(
			StdoutRedirector::redirectStdout(false),
			"Don't turn off redirecting twice.");
	}

	SECTION("Double redirecting")
	{
		REQUIRE_NOTHROW(StdoutRedirector::redirectStdout(true));
		REQUIRE_THROWS_WITH(
			StdoutRedirector::redirectStdout(true),
			"Already redirecting. Don't call it twice.");
		printf("This message should not appear");
		REQUIRE_NOTHROW(StdoutRedirector::redirectStdout(false));
	}
}

TEST_CASE("Sampling Mask Test")
{
	SECTION("Create and assign")
	{
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

TEST_CASE("VDSamplingUpper creation and destruction")
{
	SECTION("No Segfault on deleting the object")
	{
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
			25760);
		delete object;
	}
}

TEST_CASE("Poisson Subsampling")
{

	SECTION("Default parameters")
	{
		SamplingMask
			mask = poissonSubsampling(32, 16, 2.0, 0.065, 1.0, true, 10, 4, 1, true, 2.0, 2.0, true, 1, 1.0, 0, false);
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

	SECTION("Different outcomes with random seed")
	{
		unsigned int seed = 7919;
		SamplingMask
			mask = poissonSubsampling(32, 16, 2.0, 0.065, 1.0, true, 10, 4, 1, true, 2.0, 2.0, true, 1, 1.0, seed, false);
		SamplingMask maskComparison =
			poissonSubsampling(32, 16, 2.0, 0.065, 1.0, true, 10, 4, 1, true, 2.0, 2.0, true, 1, 1.0, seed, false);

		for (size_t p = 0; p < mask.phases(); p++) {
			for (size_t h = 0; h < mask.height(); h++) {
				for (size_t w = 0; w < mask.width(); w++) {
					REQUIRE(mask.get(w, h, p) == maskComparison.get(w, h, p));
				}
			}
		}
	}


	SECTION("Equal outcomes with fixed random seed")
	{
		unsigned int seed1 = 7919;
		unsigned int seed2 = 541;
		SamplingMask
			mask = poissonSubsampling(32, 16, 2.0, 0.065, 1.0, true, 10, 4, 1, true, 2.0, 2.0, true, 1, 1.0, seed1, false);
		SamplingMask maskComparison =
			poissonSubsampling(32, 16, 2.0, 0.065, 1.0, true, 10, 4, 1, true, 2.0, 2.0, true, 1, 1.0, seed2, false);

		for (size_t p = 0; p < mask.phases(); p++) {
			for (size_t h = 0; h < mask.height(); h++) {
				for (size_t w = 0; w < mask.width(); w++) {
					if (mask.get(w, h, p) != maskComparison.get(w, h, p)) {
						return;
					}
				}
			}
		}

		INFO("Got exactly the same sampling masks with different seeds");
		FAIL();
	}
}

TEST_CASE("Comparison to original implementation")
{
	SECTION("Comparison to original implementation")
	{
		unsigned int seed = 123456789;
		SamplingMask
			mask = poissonSubsampling(256, 128, 3.0, 0.065, 1.0, false, 1, 4, 1, false, 2.0, 2.0, true, 1, 1.0, seed, false);
		double sum = 0.0;
		for (size_t x = 0; x < mask.width(); x++) {
			for (size_t y = 0; y < mask.height(); y++) {
				sum += mask.get(x, y, 0);
			}
		}
		REQUIRE(std::abs(sum / (mask.width() * mask.height()) - 0.350006103515625) < 10E-5);
	}
}

// The library code really contains so much weird code that I start to
// question my own abilities.
TEST_CASE("Patrick's sanity check")
{

	// Here's one example where they use casts and ceil to calculate the
	// center of an integer. That should not be necessary and can be replaced
	// by a simple integer division. Or can it?
	SECTION("Find the center of interval (0, max)") {
		for (int i = 1; i < 2048; ++i) {
			REQUIRE(long(std::ceil(float(i) / 2)) - 1 == (i+1)/2 - 1);
		}
	}

}