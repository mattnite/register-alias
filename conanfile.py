from conans import ConanFile, CMake, tools
from register_alias_tools import create_register_alias_cmake, create_register_alias_header
import os

class RegisterAliasConan(ConanFile):
    name = "register-alias"
    version = "0.3"
    license = "MIT"
    author = "Matthew Knight <mgk1795@gmail.com>"
    url = "https://github.com/matt1795/register-alias"
    description = "ARM C++ register abstraction using SVD"
    topics = ("embedded", "mcu")
    exports_sources = "include/*", "cmake/*"
    exports = "register_alias_tools.py", "LICENSE"
    build_requires = "svd-data/0.1@matt1795/stable"

    def _create_dir(self, path):
        if not os.path.exists(path):
            try:
                os.makedirs(path)
            except OSError as e:
                if e.errno != errno.EEXIST:
                    raise

    def imports(self):
        self.copy("data/*", ".", root_package="svd-data")

    def build(self):
        data_path = self.build_folder + "/data"
        include_path = self.build_folder + "/include"
        register_alias_include_path = include_path + "/register-alias"
        master_include_file = register_alias_include_path + "/register-alias.hpp"
        cmake_path = self.build_folder + "/cmake"
        include_str = "#include \"{}\"\n"

        for root, subdirs, files in os.walk(data_path):
            if root is not data_path:
                vendor_path = os.path.join(register_alias_include_path, os.path.relpath(root, start=data_path))
                vendor_include = os.path.join(vendor_path, os.path.relpath(root, start=data_path)) + ".hpp"
                vendor_cmake = os.path.join(cmake_path, os.path.relpath(vendor_path, start=register_alias_include_path))

                self._create_dir(vendor_path)
                self._create_dir(vendor_cmake)
                with open(master_include_file, "a") as f:
                    f.write(include_str.format(os.path.relpath(vendor_include, start=include_path)))

                for file in [x for x in files if x.endswith(".svd")]:
                    file_path = "{}/{}".format(root, file)
                    rel_path = os.path.relpath(os.path.dirname(file_path), start=data_path)
                    create_register_alias_cmake(file_path, os.path.join(cmake_path, rel_path))
                    header_file = create_register_alias_header(file_path, os.path.join(register_alias_include_path, rel_path))

                    with open(vendor_include, "a") as f:
                        f.write(include_str.format(os.path.relpath(header_file, start=include_path)))

    def package(self):
        self.copy("*", dst=".")

    def package_info(self):
        self.cpp_info.cxxflags = ["-std=c++17"]
        self.env_info.SVD_MODULE_PATH = self.package_folder + "/cmake"
