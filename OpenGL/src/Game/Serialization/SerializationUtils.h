﻿#pragma once
#include <optional>
#include <nlohmann/json.hpp>

#pragma region Optional

template <class T>
struct nlohmann::adl_serializer<std::optional<T>> {
    using opt_T = std::optional<T>;
    static void from_json(const json& js, opt_T& opt) {
        if (js.is_null()) opt = std::nullopt;
        else js.get_to(opt);
    }

    static void to_json(json& js, const opt_T& opt) {
        if (opt.has_value()) js = opt.value();
        else js = nullptr;
    }
};

#pragma endregion

#pragma region Array

template <class T, std::size_t N>
struct nlohmann::adl_serializer<std::array<T, N>> {
    using array = std::array<T, N>;
    static void from_json(const json& js, array& arr) {
        for (uint i = 0; i < N; ++i) {
            js[i].get_to(arr[i]);
        }
    }

    static void to_json(json& js, const array& arr) {
        for (uint i = 0; i < N; ++i) {
            js[i] = arr[i];
        }
    }
};

#pragma endregion