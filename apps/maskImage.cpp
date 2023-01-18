#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <cxxopts.hpp>
#include "PoissonSubsampling.h"


bool isOutputDirectoryUsable(const std::string &dir)
{
	using namespace std::filesystem;
	path outputPath(dir);
	if (!exists(outputPath)) {
		return false;
	}
	return true;
}

void writeImage(const SamplingMask &mask, const std::string &dir){
	std::filesystem::path outputFile = std::filesystem::path(dir) / "mask.pnm";
	std::basic_ofstream<char> fs(outputFile, std::ios::out);
	fs << "P1" << std::endl;
	fs << mask.width() << " " << mask.height() << std::endl;
	for (size_t y = 0; y < mask.height(); ++y) {
		for (size_t x = 0; x < mask.width(); ++x) {
			fs << mask.get(x, y, 0) << " ";
		}
		fs << std::endl;
	}
	fs.close();
}

/**
 * Small helper program to visualize the sampling pattern.
 * It takes the arguments you would usually provide to the Subsample program and writes out a PNM image
 * that shows the sampling pattern.
 */
int main(int argc, char **argv)
{
	cxxopts::Options options("maskImage", "Create PNM image(s) from a subsampling mask");
	options.add_options()
			   ("h,help", "Print help message")
			   ("width", "Width of the sampling mask", cxxopts::value<long>()->default_value("256"))
			   ("height", "Height of the sampling mask", cxxopts::value<long>()->default_value("128"))
			   ("acceleration", "Acceleration factor", cxxopts::value<float>()->default_value("2.0"))
			   ("fully-sampled-fraction",
				"Fraction of the mask that is set to 1",
				cxxopts::value<float>()->default_value("0.065"))
			   ("espresso-factor", "ESPReSSo factor", cxxopts::value<float>()->default_value("1.0"))
			   ("espresso-direction", "ESPReSSo direction", cxxopts::value<bool>()->default_value("true"))
			   ("phases", "Number of phases", cxxopts::value<int>()->default_value("1"))
			   ("variable-density-type",
				"Type of the variable density sampling",
				cxxopts::value<short>()->default_value("4"))
			   ("sampling-type",
				"Poisson disc type. (0) 2D disk, (1) 3D disc, (2) pseudo 3D disc",
				cxxopts::value<short>()->default_value("1"))
			   ("elliptical-mask", "Sample mask in an elliptical shape", cxxopts::value<bool>()->default_value("true"))
			   ("power", "Power of the variable density scaling", cxxopts::value<float>()->default_value("2.0"))
			   ("root", "Root of the variable density scaling", cxxopts::value<float>()->default_value("2.0"))
			   ("random-seed",
				"Initialization of the random generator if larger than 0",
				cxxopts::value<unsigned int>()->default_value("0"))
			   ("remove-kspace-center", "Whether to exclude the KSpace center from the mask",
				   cxxopts::value<bool>()->default_value("true"))
			   ("logging", "Log library messages", cxxopts::value<bool>()->default_value("false"))
			   ("o, output-path", "Path to output images", cxxopts::value<std::string>()->default_value("false"));

	options.parse_positional("output-path");
	auto result = options.parse(argc, argv);
	options.positional_help("output-path");

	if (result.count("o") != 1 || result.count("h") > 0) {
		std::cout << options.help() << std::endl;
		return 0;
	}

	if (!isOutputDirectoryUsable(result["o"].as<std::string>())) {
		std::cout << "Output path does not exists";
		return -1;
	}

	std::cout << "Non-default values:" << std::endl;
	for (const auto &item: result.arguments()) {
		std::cout << item.key() << ":\t\t" << item.value() << std::endl;
	}

	long lLines = result["width"].as<long>();
	long lPartitions = result["height"].as<long>();
	float dAccel = result["acceleration"].as<float>();
	float fully_sampled = result["fully-sampled-fraction"].as<float>();
	float pF_val = result["espresso-factor"].as<float>();
	bool pFx = result["espresso-direction"].as<bool>();
	int lPhases = result["phases"].as<int>();
	short v_type = result["variable-density-type"].as<short>();
	short s_type = result["sampling-type"].as<short>();
	bool ellipticalMask = result["elliptical-mask"].as<bool>();
	float power = result["power"].as<float>();
	float root = result["root"].as<float>();
	unsigned int random_seed = result["random-seed"].as<unsigned int>();
	bool removeKSpaceCenter = result["remove-kspace-center"].as<bool>();
	bool logging = result["logging"].as<bool>();
	SamplingMask mask = poissonSubsampling(lLines,
										   lPartitions,
										   dAccel,
										   fully_sampled,
										   pF_val,
										   pFx,
										   lPhases,
										   v_type,
										   s_type,
										   ellipticalMask,
										   power,
										   root,
										   removeKSpaceCenter,
										   0, // body part
										   1.0, //iso factor
										   random_seed,
										   logging);

	writeImage(mask, result["o"].as<std::string>());
	return 0;
}