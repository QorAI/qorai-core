/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/sandbox/win/src/module_file_name_interception.h"

#include <string.h>

#include <algorithm>
#include <optional>
#include <string>
#include <string_view>

#include "base/compiler_specific.h"
#include "base/strings/string_util.h"
#include "base/win/windows_types.h"

namespace {

void ReplaceAt(char* dest, size_t dest_size, std::string_view src) {
  UNSAFE_TODO(::strncpy_s(dest, dest_size, src.data(),
                          std::min(dest_size - 1, src.length())));
}

void ReplaceAt(wchar_t* dest, size_t dest_size, std::wstring_view src) {
  UNSAFE_TODO(::wcsncpy_s(dest, dest_size, src.data(),
                          std::min(dest_size - 1, src.length())));
}

template <typename CharT>
struct QoraiToChrome;

template <>
struct QoraiToChrome<char> {
  static constexpr const std::string_view kQorai = "qorai.exe";
  static constexpr const std::string_view kChrome = "chrome.exe";
};

template <>
struct QoraiToChrome<wchar_t> {
  static constexpr const std::wstring_view kQorai = L"qorai.exe";
  static constexpr const std::wstring_view kChrome = L"chrome.exe";
};

template <typename CharT>
struct TestQoraiToChrome;

template <>
struct TestQoraiToChrome<char> {
  static constexpr const std::string_view kQorai = "qorai_browser_tests.exe";
  static constexpr const std::string_view kChrome = "chrome_browser_tests.exe";
};

template <>
struct TestQoraiToChrome<wchar_t> {
  static constexpr const std::wstring_view kQorai = L"qorai_browser_tests.exe";
  static constexpr const std::wstring_view kChrome =
      L"chrome_browser_tests.exe";
};

template <template <class T> class FromTo, typename CharT>
std::optional<DWORD> PatchFilenameImpl(CharT* filename,
                                       DWORD length,
                                       DWORD size) {
  if (!base::EndsWith(std::basic_string_view<CharT>(filename, length),
                      FromTo<CharT>::kQorai,
                      base::CompareCase::INSENSITIVE_ASCII)) {
    return std::nullopt;
  }

  constexpr DWORD kQoraiLen = FromTo<CharT>::kQorai.length();
  constexpr DWORD kChromeLen = FromTo<CharT>::kChrome.length();
  static_assert(kQoraiLen <= kChromeLen);
  constexpr DWORD kLenDiff = kChromeLen - kQoraiLen;

  --size;  // space for null-terminator

  const size_t qorai_pos = length - kQoraiLen;
  ReplaceAt(UNSAFE_TODO(filename + qorai_pos), size - qorai_pos,
            FromTo<CharT>::kChrome);
  if (size < length + kLenDiff) {
    ::SetLastError(ERROR_INSUFFICIENT_BUFFER);
  }
  length = std::min(size, length + kLenDiff);
  UNSAFE_TODO(filename[length]) = 0;
  return length;
}

template <typename CharT>
DWORD PatchFilename(CharT* filename, DWORD length, DWORD size) {
  if (auto r = PatchFilenameImpl<QoraiToChrome>(filename, length, size)) {
    return *r;
  }
  if (auto r = PatchFilenameImpl<TestQoraiToChrome>(filename, length, size)) {
    return *r;
  }
  return length;
}

}  // namespace

namespace sandbox {

SANDBOX_INTERCEPT DWORD WINAPI
TargetGetModuleFileNameA(GetModuleFileNameAFunction orig,
                         HMODULE hModule,
                         LPSTR lpFilename,
                         DWORD nSize) {
  const auto result = orig(hModule, lpFilename, nSize);
  if (result != 0) {
    return PatchFilename(lpFilename, result, nSize);
  }
  return result;
}

SANDBOX_INTERCEPT DWORD WINAPI
TargetGetModuleFileNameW(GetModuleFileNameWFunction orig,
                         HMODULE hModule,
                         LPWSTR lpFilename,
                         DWORD nSize) {
  const auto result = orig(hModule, lpFilename, nSize);
  if (result != 0) {
    return PatchFilename(lpFilename, result, nSize);
  }
  return result;
}

SANDBOX_INTERCEPT DWORD WINAPI
TargetGetModuleFileNameExA(GetModuleFileNameExAFunction orig,
                           HANDLE hProcess,
                           HMODULE hModule,
                           LPSTR lpFilename,
                           DWORD nSize) {
  const auto result = orig(hProcess, hModule, lpFilename, nSize);
  if (result != 0) {
    return PatchFilename(lpFilename, result, nSize);
  }
  return result;
}

SANDBOX_INTERCEPT DWORD WINAPI
TargetGetModuleFileNameExW(GetModuleFileNameExWFunction orig,
                           HANDLE hProcess,
                           HMODULE hModule,
                           LPWSTR lpFilename,
                           DWORD nSize) {
  const auto result = orig(hProcess, hModule, lpFilename, nSize);
  if (result != 0) {
    return PatchFilename(lpFilename, result, nSize);
  }
  return result;
}

}  // namespace sandbox
