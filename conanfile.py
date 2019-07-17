from conans import ConanFile, CMake, tools

class SvdAliasConan(ConanFile):
    name = "svd-alias"
    version = "0.1"
    license = "<Put the package license here>"
    author = "<Put your name here> <And your email here>"
    url = "<Package recipe repository url here, for issues about the package>"
    description = "<Description of Svdalias here>"
    topics = ("embedded", "mcu")
    export_sources = "include"

    def build(self):
        self.copy("*", dst=".")

    def package(self):
        self.copy("*", dst=".")

    def package_info(self):
        self.cpp_info.cxxflags = ["-std=c++17"]
