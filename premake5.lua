workspace "unit_test"
  location "build"
  cppdialect "C++latest"

  configurations {
    "Debug",
    "Release"
  }

  filter "configurations:Debug"
    symbols "Full"

    flags {
      "MultiProcessorCompile"
    }

  filter "configurations:Release"
    optimize "Full"

    flags {
      "LinkTimeOptimization",
      "MultiProcessorCompile"
    }

  project "swapper"
    kind "SharedLib"

    files {
      "sndth/swapper.hpp",
	  "unit_test/dll/*.cpp"
	}

  project "unit_test"
    kind "ConsoleApp"

    files {
	  "unit_test/exe/*.cpp"
    } includedirs {
      "sndth"
    }
