from conans import ConanFile, CMake, tools

class TestPackage(ConanFile):
    name = "test_package"
    version = "0.2"
    exports_sources = "*"
    requires = "svd-alias/0.2@matt1795/testing"
    generators = "virtualenv", "cmake_find_package"
    build_requires = "gcc-arm-none-eabi_installer/8-2018-q4-major@matt1795/testing"

    def build(self):
        cmake = CMake(self)
        cmake.configure(source_folder=self.source_folder)
        cmake.build()

    def test(self):
        pass
