// Utility types/funtions
//
// Author: Matthew Knight
// File Name: util.hpp
// Date: 2019-08-06

#pragma once

#include <cstdint>

namespace Svd {
	template <typename FieldType, auto val>
	struct FieldPair {
		using Field = FieldType;
		static const auto value = val;
	};

	template <typename FieldType>
	using FieldClear = FieldPair<FieldType, 0>;

	template <typename FieldType, typename T = std::uint32_t>
	struct FieldValue {
		using Field = FieldType;
		T value;
	};
}